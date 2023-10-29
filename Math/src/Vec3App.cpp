#include "Vec3App.h"
#include "MathEngine.h"

namespace Azul
{
	void Azul::Vec3App::Lerp(Vec3& out, const Vec3& a, const Vec3& b, const float t)
	{
		out.set(a[x] + t * (b[x] - a[x]),
				a[y] + t * (b[y] - a[y]),
				a[z] + t * (b[z] - a[z]));
	}

	void Azul::Vec3App::LerpArray(Vec3* out, const Vec3* a, const Vec3* b, const float t, const int numVects)
	{
		for (int i = 0; i < numVects; i++)
		{
			Lerp(out[i], a[i], b[i], t);
		}
	}
}