#include "shuntingyardfunctionset.h"
#include <cmath>

#include "shuntingyard.h"

std::map<std::string, Func> ShuntingYardFunctionSet::unary_functions =
{
	{ "sin", Func(std::sin) }
};
// binary functions
std::map<std::string, Func> ShuntingYardFunctionSet::binary_functions =
{
	{ "+", Func([](double x, double y) -> double { return x + y; }, Algo::TokenTypes::Operator, 2) },
	{ "-", Func([](double x, double y) -> double { return x - y; }, Algo::TokenTypes::Operator, 2) },
	{ "*", Func([](double x, double y) -> double { return x * y; }, Algo::TokenTypes::Operator, 3) },
	{ "/", Func([](double x, double y) -> double { return x / y; }, Algo::TokenTypes::Operator, 3) },
	{ "^", Func(std::pow, Algo::TokenTypes::Operator, 4, false) }
};




// constants
std::map<std::string, double> ShuntingYardFunctionSet::constants = {
	{ "pi", std::atan(1) * 4 },
	{ "e", std::exp(1) }
};

// variables
std::map<std::string, double> ShuntingYardFunctionSet::variables{};

// operators
std::vector<char> ShuntingYardFunctionSet::operators = { '+', '-', '/', '*', '^' };
// left brackets
std::vector<char> ShuntingYardFunctionSet::leftBrackets = { '(', '{', '[' };
// right brackets
std::vector<char> ShuntingYardFunctionSet::rightBrackets = { ')', '}', ']' };
std::vector<std::string> functionNames = ShuntingYardFunctionSet::keys<Func>(ShuntingYardFunctionSet::unary_functions, ShuntingYardFunctionSet::binary_functions);

// constant names
std::vector<std::string> ShuntingYardFunctionSet::constantNames = ShuntingYardFunctionSet::keys<double>(ShuntingYardFunctionSet::constants);

std::vector<std::string> ShuntingYardFunctionSet::functionNames = ShuntingYardFunctionSet::keys<Func>(ShuntingYardFunctionSet::unary_functions, ShuntingYardFunctionSet::binary_functions);