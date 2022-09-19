#pragma once
#include <map>
#include <string>
#include <vector>

#include "function.h"

class ShuntingYardConfigSet
{
public:
	static std::map<std::string, Func> UnaryFunctions;
	// binary functions
	static std::map<std::string, Func> BinaryFunctions;


	static std::vector<std::string> FunctionNames;

	// constant names
	static std::vector<std::string> ConstantNames;

	// constants
	static std::map<std::string, double> Constants;

	// variables
	static std::map<std::string, double> Variables;

	// operators
	static std::vector<char> Operators;
	// left brackets
	static std::vector<char> LeftBrackets;
	// right brackets
	static std::vector<char> RightBrackets;



	// obtain key list
	template<typename T>
	static std::vector<std::string> getKeys(const std::map<std::string, T>& m)
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
	static std::vector<std::string> getCombinedKeys(std::map<std::string, T> keyMap1, std::map<std::string, T> keyMap2)
	{
		// get keys from each map
		std::vector<std::string> keySet1 = getKeys<T>(keyMap1);
		std::vector<std::string> keySet2 = getKeys<T>(keyMap2);

		// insert the second list into first
		keySet1.insert(keySet1.end(), keySet2.begin(), keySet2.end());

		// return result
		return keySet1;
	}
};

