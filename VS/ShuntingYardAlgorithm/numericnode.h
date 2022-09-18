#pragma once
#include "node.h"
#include "shuntingyardalgo.h"

// number node class
class NumNode : public Node
{
public:
	NumNode(std::string name)
		: Node(std::move(name), false) {}

	// return numerical value
	double eval() const
	{
		return Utility::getNumericalVal(_name.c_str());
	}

};