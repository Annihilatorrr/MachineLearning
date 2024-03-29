#pragma once
#include <string>
#include <vector>

#include "shuntingyardconfigset.h"


class Utility
{
public:

	// determine if character is number
	static bool isNumber(char c, bool acceptDecimal, bool acceptNegative);

	// determine if vector contains values
	template<typename T>
	static bool contains(const std::vector<T>& v, const T& x)
	{
		return std::find(v.begin(), v.end(), x) != v.end();
	}

	static	bool containsNumbers(const char* str);

	// find element from list in the equation starting at index i
	static std::string findElement(const char* eqn, const std::vector<std::string>& list);


	static bool isFunction(std::string str);

	// determine if function is left associative
	static bool isLeftAssociative(const std::string& str);

	// get function precedence
	static short getPrecedence(const std::string& str);

	static bool isNumber(const char* str)
	{
		return contains<std::string>(ShuntingYardConfigSet::ConstantNames, str) ||
			contains<std::string>(ShuntingYardConfigSet::getKeys<double>(ShuntingYardConfigSet::Variables), str) ||
			std::strcmp(str, ".") == 0 ||
			containsNumbers(str);
	}
};

