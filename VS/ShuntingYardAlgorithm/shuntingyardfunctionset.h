#pragma once
#include <map>
#include <string>
#include <vector>

#include "function.h"

class ShuntingYardFunctionSet
{
public:
	static std::map<std::string, Func> unary_functions;
	// binary functions
	static std::map<std::string, Func> binary_functions;



	static std::vector<std::string> functionNames;

	// constant names
	static std::vector<std::string> constantNames;

	// constants
	static std::map<std::string, double> constants;

	// variables
	static std::map<std::string, double> variables;

	// operators
	static std::vector<char> operators;
	// left brackets
	static std::vector<char> leftBrackets;
	// right brackets
	static std::vector<char> rightBrackets;



	// obtain key list
	template<typename T>
	static std::vector<std::string> keys(const std::map<std::string, T>& m)
	{
		std::vector<std::string> ret;

		// push each key from each pair
		ret.reserve(m.size());
		for (auto const& element : m)
		{
			ret.push_back(element.first);
		}

		return ret;
	}

	// obtain combined key list
	template<typename T>
	static std::vector<std::string> keys(std::map<std::string, T> m1, std::map<std::string, T> m2)
	{
		// get keys from each map
		std::vector<std::string> keySet1 = keys<T>(m1);
		std::vector<std::string> keySet2 = keys<T>(m2);

		// insert the second list into first
		keySet1.insert(keySet1.end(), keySet2.begin(), keySet2.end());

		// return result
		return keySet1;
	}
};

