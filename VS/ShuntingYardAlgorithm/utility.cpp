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

bool Utility::isFunction(std::string str)
{
	return contains<std::string>(ShuntingYardConfigSet::FunctionNames, str);
}

bool Utility::isLeftAssociative(const std::string& str)
{
	return ShuntingYardConfigSet::BinaryFunctions[str]._isLeftAssociative;
}

short Utility::getPrecedence(const std::string& str)
{
	if (contains<std::string>(ShuntingYardConfigSet::getKeys(ShuntingYardConfigSet::BinaryFunctions), str))
	{
		return ShuntingYardConfigSet::BinaryFunctions[str]._precedence;
	}

	return 0;
}
