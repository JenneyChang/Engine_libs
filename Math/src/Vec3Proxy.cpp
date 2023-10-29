#include "Vec3Proxy.h"
#include "Trig.h"

namespace Azul
{
	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------- 

	Azul::Vec3Proxy::Vec3Proxy(float a, float b, float c)
		: x(a), y(b), z(c)
	{ }

	Azul::Vec3Proxy::operator float() const
	{
		return 0.0f;
	}

	float Azul::Vec3Proxy::operator*(const Vec3Proxy& r) const
	{
		return 0.0f;
	}

	bool Azul::Vec3Proxy::operator>(const Vec3Proxy& r) const
	{
		return false;
	}

	bool Azul::Vec3Proxy::operator<(const Vec3Proxy& r) const
	{
		return false;
	}

	bool Azul::Vec3Proxy::operator==(const Vec3Proxy& r) const
	{
		return false;
	}

	bool Azul::Vec3Proxy::operator>=(const Vec3Proxy& r) const
	{
		return false;
	}

	bool Vec3Proxy::operator<=(const Vec3Proxy& r) const
	{
		return false;
	}

	bool Vec3Proxy::operator!=(const Vec3Proxy& r) const
	{
		return false;
	}

	
}