#include "Trig.h"
#include <math.h>

namespace Azul
{
	float Azul::Trig::cos(const float angle_radians)
	{
		return cosf(angle_radians);
	}

	float Azul::Trig::sin(const float angle_radians)
	{
		return sinf(angle_radians);
	}

	float Azul::Trig::tan(const float val)
	{
		return tanf(val);
	}


	float Azul::Trig::acos(const float val)
	{
		return acosf(val);
	}

	float Azul::Trig::asin(const float val)
	{
		return asinf(val);
	}

	float Azul::Trig::atan(const float val)
	{
		return atanf(val);
	}

	float Azul::Trig::atan2(const float x, const float y)
	{
		return atan2f(x, y);
	}


	void Azul::Trig::cossin(float& cos, float& sin, const float angle_radians)
	{
		cos = Trig::cos(angle_radians);
		sin = Trig::sin(angle_radians);
	}

	float Azul::Trig::sqrt(const float val)
	{
		return sqrtf(val);
	}

	float Azul::Trig::rsqrt(const float val)
	{
		return expf(-0.5f * logf(val));
	}
}