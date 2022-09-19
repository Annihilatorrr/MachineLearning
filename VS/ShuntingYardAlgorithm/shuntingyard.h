#pragma once
#include <map>
#include <string>
#include <cmath>
#include <vector>

#include "numericnode.h"

class ShuntingYard
{
public:

	std::vector<std::string> reversePolishNotation(const char* equation) const;

	// parse RPN to tree
	Node* parse(const std::vector<std::string>& rpn) const;

	// evaluate tree
	double eval(Node* tree);
};

