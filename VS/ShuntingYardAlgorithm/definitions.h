#pragma once

namespace Algo
{

	using UnaryFunctionCallback = double(*)(double x);

	using BinaryFunctionCallback = double(*)(double x, double y);

	enum class TokenTypes
	{
		Operator,
		Constant,
		Function,
		LeftParenth,
		RightPrenth,
		Undefined
	};
}