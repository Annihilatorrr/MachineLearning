#include "shuntingyard.h"


std::vector<std::string> ShuntingYard::reversePolishNotation(const char* equation) const
{
	std::vector<std::string> queue;
	std::stack<std::string> stack;

	std::string obj;
	Algo::TokenTypes type = Algo::TokenTypes::Undefined;
	Algo::TokenTypes prevType = Algo::TokenTypes::Undefined; // negative sign detection

	bool acceptDecimal = true;
	bool acceptNegative = true;

	// token reading and detection
	const auto equationLength = static_cast<int>(strlen(equation));
	for (int i = 0; i < equationLength; i++)
	{
		const char currentCharacter = equation[i];

		// skip spaces and commas
		if (currentCharacter == ' ' || currentCharacter == ',') {
			continue;
		}

		// classify token
		if (Utility::isNumber(currentCharacter, acceptDecimal, acceptNegative && (i == 0 || prevType == Algo::TokenTypes::LeftParenth)))
		{
			type = Algo::TokenTypes::Constant;
			if (currentCharacter == '.')
			{
				acceptDecimal = false;
			}
			else if (currentCharacter == '-')
			{
				acceptNegative = false;
			}

			const int startI = i;
			if (i < equationLength - 1)
			{
				while (Utility::isNumber(equation[i + 1], acceptDecimal, acceptNegative && (prevType == Algo::TokenTypes::LeftParenth)))
				{
					i++;
					if (i >= equationLength - 1)
					{
						break;
					}
				}
			}
			obj = std::string(equation + startI, i - startI + 1);

			// subtraction only sign detection means it is minus operator, not a negative number
			if (obj == "-")
			{
				type = Algo::TokenTypes::Operator;
			}
		}
		else
		{
			obj = Utility::findElement(equation + i, ShuntingYardConfigSet::FunctionNames);
			if (!obj.empty())
			{
				// found valid object
				type = Utility::contains<char>(ShuntingYardConfigSet::Operators, obj[0]) ? Algo::TokenTypes::Operator : Algo::TokenTypes::Function;
			}
			else
			{
				obj = Utility::findElement(equation + i, ShuntingYardConfigSet::ConstantNames);
				if (!obj.empty())
				{
					// found valid object
					type = Algo::TokenTypes::Constant;
				}
				else
				{
					obj = Utility::findElement(equation + i, ShuntingYardConfigSet::getKeys<double>(ShuntingYardConfigSet::Variables));
					if (!obj.empty())
					{
						type = Algo::TokenTypes::Constant;
					}
					else if (Utility::contains<char>(ShuntingYardConfigSet::LeftBrackets, currentCharacter))
					{
						type = Algo::TokenTypes::LeftParenth;
						obj = "(";
					}
					else if (Utility::contains<char>(ShuntingYardConfigSet::RightBrackets, currentCharacter))
					{
						type = Algo::TokenTypes::RightPrenth;
						obj = ")";
					}
					else
					{
						type = Algo::TokenTypes::Undefined;
					}
				}
			}
			i += obj.size() - 1;
		}

		// do something with the token
		const char* last_stack = (!stack.empty()) ? stack.top().c_str() : "";
		switch (type) {
		case Algo::TokenTypes::Constant:
			queue.push_back(obj);
			break;
		case Algo::TokenTypes::Function:
			stack.push(obj);
			break;
		case Algo::TokenTypes::Operator:
			if (!stack.empty()) {
				while (
					(
						(Utility::contains<std::string>(ShuntingYardConfigSet::FunctionNames, last_stack) &&
							!Utility::contains<char>(ShuntingYardConfigSet::Operators, last_stack[0])) ||
						Utility::getPrecedence(last_stack) > Utility::getPrecedence(obj) ||
						((Utility::getPrecedence(last_stack) == Utility::getPrecedence(obj)) &&
							Utility::isLeftAssociative(last_stack))
					) &&
					!Utility::contains<char>(ShuntingYardConfigSet::LeftBrackets, last_stack[0])
				) {
					queue.push_back(stack.top());
					stack.pop();
					if (stack.empty()) {
						break;
					}
					last_stack = stack.top().c_str();
				}
			}
			stack.push(obj);
			break;
		case Algo::TokenTypes::LeftParenth:
			stack.push(obj);
			break;
		case Algo::TokenTypes::RightPrenth:
			while (last_stack[0] != '(') {
				queue.push_back(stack.top());
				stack.pop();
				last_stack = stack.top().c_str();
			}
			stack.pop();
			break;
		default:
			return queue;
		}
		prevType = type;
	}

	while (!stack.empty()) {
		queue.push_back(stack.top());
		stack.pop();
	}

	return queue;
}

Node* ShuntingYard::parse(const std::vector<std::string>& rpn) const
{
	std::stack<Node*> stack;

	for (std::string item : rpn) {
		if (Utility::isNumber(item.c_str()) && item != "-") 
		{
			// push number node
			stack.push(new NumNode(item));
		}
		else {
			// function
			FunctionNode* f = new FunctionNode(item);
			if (Utility::contains<std::string>(ShuntingYardConfigSet::getKeys(ShuntingYardConfigSet::BinaryFunctions), item)) {
				f->setUnary(false);
				// set children of node
				f->_right = stack.top();
				stack.pop();
				f->_left = stack.top();
				stack.pop();
			}
			else if (Utility::contains<std::string>(ShuntingYardConfigSet::getKeys(ShuntingYardConfigSet::UnaryFunctions), item)) {
				f->setUnary(true);
				// set child of node
				f->_left = stack.top();
				stack.pop();
			}
			stack.push(f);
		}
	}

	if (stack.empty()) 
	{
		return nullptr;
	}

	return stack.top();
}

double ShuntingYard::eval(Node* tree)
{
	if (tree->_isFunc) 
	{
		FunctionNode* ftree = (FunctionNode*)tree;
		if (ftree->isUnary()) {
			// evaluate child recursively and then evaluate with return value
			return ftree->eval(eval(tree->_left));
		}
		// evaluate each child recursively and then evaluate with return value
		return ftree->eval(eval(tree->_left), eval(tree->_right));
	}
	// number node
	return ((NumNode*)tree)->eval();
}
