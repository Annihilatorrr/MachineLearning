#pragma once
#include <map>
#include <string>
#include <cmath>
#include <vector>

#include "definitions.h"
#include "functionnode.h"
#include "numericnode.h"
#include "shuntingyardfunctionset.h"
#include "utility.h"

class ShuntingYard
{
public:


	// determine if string matches a function


	// determine if entire string is number


	// parse infix notation into reverse polish notation (Shunting Yard)
	std::vector<std::string> reversePolishNotation(const char* equation)
	{
		std::vector<std::string> queue;
		std::stack<std::string> stack;

		std::string obj;
		Algo::TokenTypes type = Algo::TokenTypes::Undefined;

		bool acceptDecimal = true;
		bool acceptNegative = true;

		// token reading and detection
		const auto equationLength = static_cast<int>(strlen(equation));
		for (int i = 0; i < equationLength; i++)
		{
			const char currentCharacter = equation[i];

			// skip spaces and commas
			if (currentCharacter == ' ' || currentCharacter == ',') {
				//prevType = TokenTypes::ELSE;
				continue;
			}

			// classify token
			if (Utility::isNumber(currentCharacter, true, true))
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
					while (Utility::isNumber(equation[i + 1], acceptDecimal, acceptNegative))
					{
						i++;
						if (i >= equationLength - 1)
						{
							break;
						}
					}
				}
				obj = std::string(equation + startI, i - startI + 1);

				// subtraction sign detection
				if (obj == "-")
				{
					type = Algo::TokenTypes::Operator;
				}
			}
			else
			{
				obj = Utility::findElement(equation + i, ShuntingYardFunctionSet::functionNames);
				if (!obj.empty())
				{
					// found valid object
					type = Utility::contains<char>(ShuntingYardFunctionSet::operators, obj[0]) ? Algo::TokenTypes::Operator : Algo::TokenTypes::Function;
				}
				else
				{
					obj = Utility::findElement(equation + i, ShuntingYardFunctionSet::constantNames);
					if (!obj.empty())
					{
						// found valid object
						type = Algo::TokenTypes::Constant;
					}
					else
					{
						obj = Utility::findElement(equation + i, ShuntingYardFunctionSet::keys<double>(ShuntingYardFunctionSet::variables));
						if (!obj.empty())
						{
							type = Algo::TokenTypes::Constant;
						}
						else if (Utility::contains<char>(ShuntingYardFunctionSet::leftBrackets, currentCharacter))
						{
							type = Algo::TokenTypes::LeftParenth;
							obj = "(";
						}
						else if (Utility::contains<char>(ShuntingYardFunctionSet::rightBrackets, currentCharacter))
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
							(Utility::contains<std::string>(ShuntingYardFunctionSet::functionNames, last_stack) &&
								!Utility::contains<char>(ShuntingYardFunctionSet::operators, last_stack[0])) ||
							Utility::getPrecedence(last_stack) > Utility::getPrecedence(obj) ||
							((Utility::getPrecedence(last_stack) == Utility::getPrecedence(obj)) &&
								Utility::isLeftAssociative(last_stack))
							) &&
						!Utility::contains<char>(ShuntingYardFunctionSet::leftBrackets, last_stack[0])
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

		}

		while (!stack.empty()) {
			queue.push_back(stack.top());
			stack.pop();
		}

		return queue;
	}

	// parse RPN to tree
	Node* parse(const std::vector<std::string>& rpn)
	{
		std::stack<Node*> stack;

		for (std::string item : rpn) {
			if (Utility::isNumber(item.c_str()) && item != "-") {
				// push number node
				stack.push(new NumNode(item));
			}
			else {
				// function
				FuncNode* f = new FuncNode(item);
				if (Utility::contains<std::string>(ShuntingYardFunctionSet::keys(ShuntingYardFunctionSet::binary_functions), item)) {
					f->setUnary(false);
					// set children of node
					f->_right = stack.top();
					stack.pop();
					f->_left = stack.top();
					stack.pop();
				}
				else if (Utility::contains<std::string>(ShuntingYardFunctionSet::keys(ShuntingYardFunctionSet::unary_functions), item)) {
					f->setUnary(true);
					// set child of node
					f->_left = stack.top();
					stack.pop();
				}
				stack.push(f);
			}
		}

		if (stack.empty()) {
			return nullptr;
		}

		return stack.top();
	}

	// evaluate tree
	double eval(Node* tree) {
		if (tree->_isFunc) {
			FuncNode* ftree = (FuncNode*)tree;
			if (ftree->_isUnary) {
				// evaluate child recursively and then evaluate with return value
				return ftree->eval(eval(tree->_left));
			}
			else {
				// evaluate each child recursively and then evaluate with return value
				return ftree->eval(eval(tree->_left), eval(tree->_right));
			}
		}
		else {
			// number node
			return ((NumNode*)tree)->eval();
		}
	}
};

