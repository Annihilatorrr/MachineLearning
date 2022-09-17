#ifndef SHUNTING_YARD
#define SHUNTING_YARD

#include <utility>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <cmath>

#include "utility.h"

namespace ShuntingYard
{

	using UnaryFunctionCallback = double(*)(double x);

	using BinaryFunctionCallback = double(*)(double x, double y);

	enum class TokenTypes
    {
		Operator,
		Constant,
		Function,
		LeftParenth,
		RightPrenth,
		Undefined
	};

	// determine if vector contains values
	template<typename T>
	bool contains(const std::vector<T>& v, const T& x);

	// obtain key list
	template<typename T>
	std::vector<std::string> keys(const std::map<std::string, T>& m);

	// obtain combined key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2);

	// determine if entire string is number
	bool isNumber(const char* str);

	// determine if string only contains numerical characters
	bool containsNumbers(const char* str);

	// get numerical value of string
	double getNumericalVal(const char* str);

	// determine if string matches a function
	bool isFunction(std::string str);

	// determine if function is left associative
	bool isLeftAssociative(const std::string& str);

	// get function precedence
	short getPrecedence(const std::string& str);

	// find element from list in the equation starting at index i
	std::string findElement(const char* eqn, const std::vector<std::string>& list);

	/*
		Function class definition
	*/
	class Func {
	public:
		// default constructor
		Func()
			: _unFunCallback(nullptr), _binFunCallback(nullptr), _tokenType(TokenTypes::Operator), _precedence(0), _isLeftAssociative(true), _isUnary(true) {}

		// constructor for unary functions
		Func(UnaryFunctionCallback eval, TokenTypes type = TokenTypes::Function, short prec = 0, bool left = true)
			: Func(type, prec, left, true)
	    {
			_unFunCallback = eval;
		}

		// constructor for binary functions
		Func(BinaryFunctionCallback eval, TokenTypes type = TokenTypes::Function, short prec = 0, bool left = true)
			: Func(type, prec, left, false) {
			_binFunCallback = eval;
		}

		double eval(double x, double y = 0)
	    {
			return _isUnary ? _unFunCallback(x) : _binFunCallback(x, y);
		}

		UnaryFunctionCallback _unFunCallback;	// unary function evaluation callback
		BinaryFunctionCallback _binFunCallback;	// binary function evaluation callback

		TokenTypes _tokenType;
		short _precedence;
		bool _isLeftAssociative;
		bool _isUnary;

	private:
		Func(TokenTypes type, short precedence, bool isLeftAssociative, bool isUnary)
			: _unFunCallback(nullptr), _binFunCallback(nullptr), _tokenType(type), _precedence(precedence), _isLeftAssociative(isLeftAssociative), _isUnary(isUnary) {}
	};

	/*
		Reference
	*/

	// unary functions
	std::map<std::string, Func> unary_functions = {
		{ "sin", Func(std::sin) }
	};
	// binary functions
	std::map<std::string, Func> binary_functions = {
		{ "+", Func([](double x, double y) -> double { return x + y; }, TokenTypes::Operator, 2) },
		{ "-", Func([](double x, double y) -> double { return x - y; }, TokenTypes::Operator, 2) },
		{ "*", Func([](double x, double y) -> double { return x * y; }, TokenTypes::Operator, 3) },
		{ "/", Func([](double x, double y) -> double { return x / y; }, TokenTypes::Operator, 3) },
		{ "^", Func(std::pow, TokenTypes::Operator, 4, false) }
	};

	// function names
	std::vector<std::string> functionNames = keys<Func>(unary_functions, binary_functions);

	// constants
	std::map<std::string, double> constants = {
		{ "pi", std::atan(1) * 4 },
		{ "e", std::exp(1) }
	};

	// constant names
	std::vector<std::string> constantNames = keys<double>(constants);

	// variables
	std::map<std::string, double> variables;

	// operators
	std::vector<char> operators = { '+', '-', '/', '*', '^' };
	// left brackets
	std::vector<char> leftBrackets = { '(', '{', '[' };
	// right brackets
	std::vector<char> rightBrackets = { ')', '}', ']' };

	/*
		Node class definitions
	*/

	// base node class
	class Node {
	public:
		Node(std::string name, bool isFunc)
			: _name(std::move(name)), _isFunc(isFunc) {}

		double eval(double x = 0, double y = 0);

		std::string _name;
		bool _isFunc;

		Node* _right;
		Node* _left;
	};

	// function node class
	class FuncNode : public Node
    {
	public:
        explicit FuncNode(std::string name)
			: Node(std::move(name), true) {}

		// set type of function and then assign callback
		void setUnary(bool isUnary)
	    {
			_isUnary = isUnary;
			_func = isUnary ? unary_functions[_name] : binary_functions[_name];
		}

		// evaluate
		double eval(double x, double y = 0)
	    {
			return _func.eval(x, y);
		}

		bool _isUnary;
		Func _func;
	};

	// number node class
	class NumNode : public Node {
	public:
		NumNode(std::string name)
			: Node(std::move(name), false) {}

		// return numerical value
		double eval() const
        {
			return getNumericalVal(_name.c_str());
		}
	};

	/*
		Main functions
	*/

	// parse infix notation into reverse polish notation (Shunting Yard)
	std::vector<std::string> reversePolishNotation(const char* equation)
    {
		std::vector<std::string> queue;
		std::stack<std::string> stack;

		std::string obj;
		TokenTypes type = TokenTypes::Undefined;

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
				type = TokenTypes::Constant;
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
					type = TokenTypes::Operator;
				}
			}
			else 
			{
				obj = findElement(equation + i, functionNames);
				if (!obj.empty())
				{
					// found valid object
					type = contains<char>(operators, obj[0]) ? TokenTypes::Operator : TokenTypes::Function;
				}
				else 
				{
					obj = findElement(equation + i, constantNames);
					if (!obj.empty()) 
					{
						// found valid object
						type = TokenTypes::Constant;
					}
					else 
					{
						obj = findElement(equation + i, keys<double>(variables));
						if (!obj.empty()) 
						{
							type = TokenTypes::Constant;
						}
						else if (contains<char>(leftBrackets, currentCharacter)) 
						{
							type = TokenTypes::LeftParenth;
							obj = "(";
						}
						else if (contains<char>(rightBrackets, currentCharacter))
						{
							type = TokenTypes::RightPrenth;
							obj = ")";
						}
						else
						{
							type = TokenTypes::Undefined;
						}
					}
				}
				i += obj.size() - 1;
			}

			// do something with the token
			const char* last_stack = (!stack.empty()) ? stack.top().c_str() : "";
			switch (type) {
			case TokenTypes::Constant:
				queue.push_back(obj);
				break;
			case TokenTypes::Function:
				stack.push(obj);
				break;
			case TokenTypes::Operator:
				if (!stack.empty()) {
					while (
						(
							(contains<std::string>(functionNames, last_stack) &&
								!contains<char>(operators, last_stack[0])) ||
							getPrecedence(last_stack) > getPrecedence(obj) ||
							((getPrecedence(last_stack) == getPrecedence(obj)) &&
								isLeftAssociative(last_stack))
							) &&
						!contains<char>(leftBrackets, last_stack[0])
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
			case TokenTypes::LeftParenth:
				stack.push(obj);
				break;
			case TokenTypes::RightPrenth:
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
	Node* parse(const std::vector<std::string>& rpn) {
		std::stack<Node*> stack;

		for (std::string item : rpn) {
			if (isNumber(item.c_str()) && item != "-") {
				// push number node
				stack.push(new NumNode(item));
			}
			else {
				// function
				FuncNode* f = new FuncNode(item);
				if (contains<std::string>(keys(binary_functions), item)) {
					f->setUnary(false);
					// set children of node
					f->_right = stack.top();
					stack.pop();
					f->_left = stack.top();
					stack.pop();
				}
				else if (contains<std::string>(keys(unary_functions), item)) {
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
	double eval(Node* tree)
    {
		if (tree->_isFunc) 
		{
			const auto ftree = static_cast<FuncNode*>(tree);
			if (ftree->_isUnary)
			{
				return ftree->eval(eval(tree->_left));
			}
            return ftree->eval(eval(tree->_left), eval(tree->_right));
        }
		else 
		{
			// number node
			return static_cast<NumNode*>(tree)->eval();
		}
	}

	/*
		Utility function definitions
	*/

	// determine if vector contains values
	template<typename T>
	bool contains(const std::vector<T>& v, const T& x)
    {
		return std::find(v.begin(), v.end(), x) != v.end();
	}

	// obtain key list
	template<typename T>
	std::vector<std::string> keys(const std::map<std::string, T>& m)
    {
		std::vector<std::string> ret;

		// push each key from each pair
        ret.reserve(m.size());
        for (auto const& element : m) 
		{
			ret.push_back(element.first);
		}

		return ret;
	}

	// obtain combined key list
	template<typename T>
	std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2)
    {
		// get keys from each map
		std::vector<std::string> keySet1 = keys<T>(m1);
		std::vector<std::string> keySet2 = keys<T>(m2);

		// insert the second list into first
		keySet1.insert(keySet1.end(), keySet2.begin(), keySet2.end());

		// return result
		return keySet1;
	}


	// determine if entire string is number
	bool isNumber(const char* str)
	{
		return contains<std::string>(constantNames, str) ||
			contains<std::string>(keys<double>(variables), str) ||
			std::strcmp(str, ".") == 0 ||
			containsNumbers(str);
	}

	// determine if string only contains numerical characters
	bool containsNumbers(const char* str)
	{
		// try to prove wrong
		bool acceptDecimal = true;
		bool acceptNegative = true;
		for (char c : std::string(str)) 
		{
			if (!Utility::isNumber(c, acceptDecimal, acceptNegative)) 
			{
				return false;
			}

			if (c == '.') 
			{
				acceptDecimal = false;
			}
		    if (c == '-') 
			{
				acceptNegative = false;
			}
		}

		return true;
	}

	// get numerical value of string
	double getNumericalVal(const char* str)
	{
		if (contains<std::string>(constantNames, str)) 
		{
			return constants[str];
		}
		if (contains<std::string>(keys<double>(variables), str)) 
		{
			return variables[str];
		}
		return std::stod(str);
	}

	// determine if string matches a function
	bool isFunction(std::string str)
	{
		return contains<std::string>(functionNames, str);
	}

	// determine if function is left associative
	bool isLeftAssociative(const std::string& str)
    {
		return binary_functions[str]._isLeftAssociative;
	}

	// get function precedence
	short getPrecedence(const std::string& str)
    {
		if (contains<std::string>(keys(binary_functions), str))
        {
            return binary_functions[str]._precedence;
        }

		return 0;
	}

	// find element from list in the equation starting at index i
	std::string findElement(const char* eqn, const std::vector<std::string>& list)
    {
		for (const auto& item : list) 
		{
			const int n = static_cast<int>(item.size());
			if (std::string(eqn, n) == item) 
			{
				return item;
			}
		}

		return "";
	}
}

#endif