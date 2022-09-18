#pragma once
#include "definitions.h"

class Func
{
public:
	// default constructor
	Func()
		: _unFunCallback(nullptr), _binFunCallback(nullptr), _tokenType(Algo::TokenTypes::Operator), _precedence(0), _isLeftAssociative(true), _isUnary(true) {}

	// constructor for unary functions
	Func(Algo::UnaryFunctionCallback eval, Algo::TokenTypes type = Algo::TokenTypes::Function, short prec = 0, bool left = true);

	// constructor for binary functions
	Func(Algo::BinaryFunctionCallback eval, Algo::TokenTypes type = Algo::TokenTypes::Function, short prec = 0, bool left = true);

	double eval(double x, double y = 0) const;

	Algo::UnaryFunctionCallback _unFunCallback;	// unary function evaluation callback
	Algo::BinaryFunctionCallback _binFunCallback;	// binary function evaluation callback

	Algo::TokenTypes _tokenType;
	short _precedence;
	bool _isLeftAssociative;
	bool _isUnary;

private:
	Func(Algo::TokenTypes type, short precedence, bool isLeftAssociative, bool isUnary);
};
