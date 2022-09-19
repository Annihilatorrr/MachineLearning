#pragma once
#include "function.h"
#include "node.h"
#include "shuntingyardconfigset.h"

class FunctionNode : public Node
{
	bool _isUnary;
	Func _func;

public:
	explicit FunctionNode(std::string name)
		: Node(std::move(name), true), _isUnary(false)
	{
	}

	// set type of function and then assign callback
	void setUnary(bool isUnary)
	{
		_isUnary = isUnary;
		_func = isUnary ? ShuntingYardConfigSet::UnaryFunctions[_name] : ShuntingYardConfigSet::BinaryFunctions[_name];
	}

	// evaluate
	double eval(double x, double y = 0)
	{
		return _func.eval(x, y);
	}

	bool isUnary() const
	{
		return _isUnary;
	}

};
