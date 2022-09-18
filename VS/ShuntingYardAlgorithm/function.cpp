#include "function.h"

Func::Func(Algo::UnaryFunctionCallback eval, Algo::TokenTypes type, short prec, bool left): Func(type, prec, left, true)
{
	_unFunCallback = eval;
}

Func::Func(Algo::BinaryFunctionCallback eval, Algo::TokenTypes type, short prec, bool left): Func(type, prec, left, false)
{
	_binFunCallback = eval;
}

double Func::eval(double x, double y) const
{
	return _isUnary ? _unFunCallback(x) : _binFunCallback(x, y);
}

Func::Func(Algo::TokenTypes type, short precedence, bool isLeftAssociative, bool isUnary): _unFunCallback(nullptr), _binFunCallback(nullptr), _tokenType(type), _precedence(precedence), _isLeftAssociative(isLeftAssociative), _isUnary(isUnary)
{}
