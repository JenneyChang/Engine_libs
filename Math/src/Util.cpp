#include "Util.h"

namespace Azul
{
	bool Azul::Util::isEqual(const float a, const float b, const float epsilon)
	{
		return ((a - b >= -epsilon) && (a - b <= epsilon));
	}

	bool Azul::Util::isNotEqual(const float a, const float b, const float epsilon)
	{
		return ((a - b < -epsilon) || (a - b > epsilon));
	}

	bool Azul::Util::isOne(const float a, const float epsilon)
	{
		return ((a - 1.0f >= -epsilon) && (a - 1.0f <= epsilon));
	}

	bool Azul::Util::isNonZero(const float a, const float epsilon)
	{
		return ((a < -epsilon) || (a > epsilon));
	}

	bool Azul::Util::isZero(const float a, const float epsilon)
	{
		return ((a >= -epsilon) && (a <= epsilon));
	}
}