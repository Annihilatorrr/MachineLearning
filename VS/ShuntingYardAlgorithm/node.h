#pragma once
#include <string>

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