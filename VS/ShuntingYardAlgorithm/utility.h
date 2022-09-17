#pragma once

class Utility
{
public:

	// determine if character is number
	static bool isNumber(char c, bool acceptDecimal, bool acceptNegative)
	{
		return (c >= '0' && c <= '9') || (acceptDecimal && c == '.') || (acceptNegative && c == '-');
	}

	// determine if entire string is number

};

