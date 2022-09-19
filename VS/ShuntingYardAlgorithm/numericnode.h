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
		if (Utility::contains<std::string>(ShuntingYardConfigSet::ConstantNames, _name))
		{
			return ShuntingYardConfigSet::Constants[_name.c_str()];
		}
		if (Utility::contains<std::string>(ShuntingYardConfigSet::getKeys<double>(ShuntingYardConfigSet::Variables),
		                                   _name))
		{
			return ShuntingYardConfigSet::Variables[_name.c_str()];
		}
		return std::stod(_name);
	}

};