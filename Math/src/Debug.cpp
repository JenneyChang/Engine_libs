#include "Debug.h"
#include "MathEngine.h"

namespace Azul
{
	void Azul::Debug::Print(const char* pName, const Vec4& r)
	{
		Trace::out("%s\n", pName);
		Trace::out("Vec4(%9.6g, %9.6g, %9.6g, %9.6g)\n\n", r[x], r[y], r[z], r[w]);
	}

	void Azul::Debug::Print(const char* pName, const Vec3& r)
	{
		Trace::out("%s\n", pName);
		Trace::out("Vec3(%9.6g, %9.6g, %9.6g)\n\n", r[x], r[y], r[z]);
	}

	void Azul::Debug::Print(const char* pName, const Mat4& r)
	{
		Trace::out("%s : Mat4\n", pName);
		Trace::out("v0[%9.6g, %9.6g, %9.6g, %9.6g]\n", r[m0], r[m1], r[m2], r[m3]);
		Trace::out("v1[%9.6g, %9.6g, %9.6g, %9.6g]\n", r[m4], r[m5], r[m6], r[m7]);
		Trace::out("v2[%9.6g, %9.6g, %9.6g, %9.6g]\n", r[m8], r[m9], r[m10], r[m11]);
		Trace::out("v3[%9.6g, %9.6g, %9.6g, %9.6g]\n\n", r[m12], r[m13], r[m14], r[m15]);
	}

	void Azul::Debug::Print(const char* pName, const Mat3& r)
	{
		Trace::out("%s : Mat3\n", pName);
		Trace::out("v0[%9.6g, %9.6g, %9.6g]\n", r[m0], r[m1], r[m2]);
		Trace::out("v1[%9.6g, %9.6g, %9.6g]\n", r[m4], r[m5], r[m6]);
		Trace::out("v2[%9.6g, %9.6g, %9.6g]\n", r[m8], r[m9], r[m10]);
	}

	void Azul::Debug::Print(const char* pName, const Quat& r)
	{
		Trace::out("%s\n", pName);
		Trace::out("Quat(%9.6g, %9.6g, %9.6g, %9.6g)\n\n", r[x], r[y], r[z], r[w]);
	}
}