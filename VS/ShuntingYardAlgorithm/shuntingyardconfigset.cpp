#include "shuntingyardconfigset.h"
#include <cmath>

#include "shuntingyard.h"

std::map<std::string, Func> ShuntingYardConfigSet::UnaryFunctions =
{
	{ "sin", Func(std::sin) }
};
// binary functions
std::map<std::string, Func> ShuntingYardConfigSet::BinaryFunctions =
{
	{ "+", Func([](double x, double y) -> double { return x + y; }, Algo::TokenTypes::Operator, 2) },
	{ "-", Func([](double x, double y) -> double { return x - y; }, Algo::TokenTypes::Operator, 2) },
	{ "*", Func([](double x, double y) -> double { return x * y; }, Algo::TokenTypes::Operator, 3) },
	{ "/", Func([](double x, double y) -> double { return x / y; }, Algo::TokenTypes::Operator, 3) },
	{ "^", Func(std::pow, Algo::TokenTypes::Operator, 4, false) }
};




// constants
std::map<std::string, double> ShuntingYardConfigSet::Constants = {
	{ "pi", std::atan(1) * 4 },
	{ "e", std::exp(1) }
};

// variables
std::map<std::string, double> ShuntingYardConfigSet::Variables{};

// operators
std::vector<char> ShuntingYardConfigSet::Operators = { '+', '-', '/', '*', '^' };
// left brackets
std::vector<char> ShuntingYardConfigSet::LeftBrackets = { '(', '{', '[' };
// right brackets
std::vector<char> ShuntingYardConfigSet::RightBrackets = { ')', '}', ']' };
std::vector<std::string> functionNames = ShuntingYardConfigSet::getCombinedKeys<Func>(ShuntingYardConfigSet::UnaryFunctions, ShuntingYardConfigSet::BinaryFunctions);

// constant names
std::vector<std::string> ShuntingYardConfigSet::ConstantNames = ShuntingYardConfigSet::getKeys<double>(ShuntingYardConfigSet::Constants);

std::vector<std::string> ShuntingYardConfigSet::FunctionNames = ShuntingYardConfigSet::getCombinedKeys<Func>(ShuntingYardConfigSet::UnaryFunctions, ShuntingYardConfigSet::BinaryFunctions);