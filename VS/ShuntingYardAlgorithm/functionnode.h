#pragma once
#include "function.h"
#include "node.h"
#include "shuntingyardfunctionset.h"

class FuncNode : public Node
{
public:
	explicit FuncNode(std::string name)
		: Node(std::move(name), true) {}

	// set type of function and then assign callback
	void setUnary(bool isUnary)
	{
		_isUnary = isUnary;
		_func = isUnary ? ShuntingYardFunctionSet::unary_functions[_name] : ShuntingYardFunctionSet::binary_functions[_name];
	}

	// evaluate
	double eval(double x, double y = 0)
	{
		return _func.eval(x, y);
	}

	bool _isUnary;
	Func _func;
};
