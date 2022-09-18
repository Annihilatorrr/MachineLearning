#include "utility.h"

bool Utility::isNumber(char c, bool acceptDecimal, bool acceptNegative)
{
	return (c >= '0' && c <= '9') || (acceptDecimal && c == '.') || (acceptNegative && c == '-');
}

// determine if vector contains values


bool Utility::containsNumbers(const char* str)
{
	// try to prove wrong
	bool acceptDecimal = true;
	bool acceptNegative = true;
	for (char c : std::string(str))
	{
		if (!isNumber(c, acceptDecimal, acceptNegative))
		{
			return false;
		}

		if (c == '.')
		{
			acceptDecimal = false;
		}
		if (c == '-')
		{
			acceptNegative = false;
		}
	}

	return true;
}

// find element from list in the equation starting at index i
std::string Utility::findElement(const char* eqn, const std::vector<std::string>& list)
{
	for (const auto& item : list)
	{
		const int n = static_cast<int>(item.size());
		if (std::string(eqn, n) == item)
		{
			return item;
		}
	}

	return "";
}

double Utility::getNumericalVal(const char* str)
{
	if (Utility::contains<std::string>(ShuntingYardFunctionSet::constantNames, str))
	{
		return ShuntingYardFunctionSet::constants[str];
	}
	if (Utility::contains<std::string>(ShuntingYardFunctionSet::keys<double>(ShuntingYardFunctionSet::variables), str))
	{
		return ShuntingYardFunctionSet::variables[str];
	}
	return std::stod(str);
}

bool Utility::isFunction(std::string str)
{
	return Utility::contains<std::string>(ShuntingYardFunctionSet::functionNames, str);
}

bool Utility::isLeftAssociative(const std::string& str)
{
	return ShuntingYardFunctionSet::binary_functions[str]._isLeftAssociative;
}

short Utility::getPrecedence(const std::string& str)
{
	if (Utility::contains<std::string>(ShuntingYardFunctionSet::keys(ShuntingYardFunctionSet::binary_functions), str))
	{
		return ShuntingYardFunctionSet::binary_functions[str]._precedence;
	}

	return 0;
}
