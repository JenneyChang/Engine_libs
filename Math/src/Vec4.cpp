#include "Vec4.h"
#include "MathEngine.h"

namespace Azul
{
	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//-----------------------------------------------------------------------------

	Azul::Vec4::Vec4()
		: _vx(0.0f), _vy(0.0f), _vz(0.0f), _vw(0.0f)
	{ }

	Azul::Vec4::~Vec4()
	{ }

	Azul::Vec4::Vec4(const Vec4& inV)
		: _vx(inV._vx), _vy(inV._vy), _vz(inV._vz), _vw(inV._vw)
	{ }

	Vec4& Azul::Vec4::operator=(const Vec4& v)
	{
		if (this != &v)
		{
			this->_vx = v._vx;
			this->_vy = v._vy;
			this->_vz = v._vz;
			this->_vw = v._vw;
		}

		return *this;
	}

	Azul::Vec4::Vec4(const float in_x, const float in_y, const float in_z, const float in_w)
		: _vx(in_x), _vy(in_y), _vz(in_z), _vw(in_w)
	{ }

	Azul::Vec4::Vec4(const Vec3& v, const float w)
		: _vx(v._vx), _vy(v._vy), _vz(v._vz), _vw(w)
	{ }


	//-----------------------------------------------------------------------------
	//	OPERATORS: ADD
	//----------------------------------------------------------------------------- 

	Vec4 Azul::Vec4::operator+(void) const
	{
		return Vec4(+_vx, +_vy, +_vz, +_vw);
	}

	Vec4 Azul::Vec4::operator+(const Vec4& inV) const
	{
		return Vec4(_vx + inV._vx, _vy + inV._vy, _vz + inV._vz, _vw + inV._vw);
	}

	void Azul::Vec4::operator+=(const Vec4& inV)
	{
		_vx += inV._vx;
		_vy += inV._vy;
		_vz += inV._vz;
		_vw += inV._vw;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SUB
	//----------------------------------------------------------------------------- 

	Vec4 Azul::Vec4::operator-(void) const
	{
		return Vec4(-_vx, -_vy, -_vz, -_vw);
	}

	Vec4 Azul::Vec4::operator-(const Vec4& inV) const
	{
		return Vec4(_vx - inV._vx, _vy - inV._vy, _vz - inV._vz, _vw - inV._vw);
	}

	void Azul::Vec4::operator-=(const Vec4& inV)
	{
		_vx -= inV._vx;
		_vy -= inV._vy;
		_vz -= inV._vz;
		_vw -= inV._vw;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SCALE
	//----------------------------------------------------------------------------- 

	Vec4 Azul::Vec4::operator*(const float scale) const
	{
		return Vec4(_vx * scale, _vy * scale, _vz * scale, _vw * scale);
	}

	Vec4 Azul::operator*(const float scale, const Vec4& inV)
	{
		return Vec4(scale * inV._vx, scale * inV._vy, scale * inV._vz, scale * inV._vw);
	}

	void Azul::Vec4::operator*=(const float scale)
	{
		_vx *= scale;
		_vy *= scale;
		_vz *= scale;
		_vw *= scale;
	}

	Vec4 Azul::Vec4::operator*(const Mat4& m) const
	{
		return Vec4((_vx * m[m0]) + (_vy * m[m4]) + (_vz * m[m8]) + (_vw * m[m12]),
					(_vx * m[m1]) + (_vy * m[m5]) + (_vz * m[m9]) + (_vw * m[m13]),
					(_vx * m[m2]) + (_vy * m[m6]) + (_vz * m[m10]) + (_vw * m[m14]),
					(_vx * m[m3]) + (_vy * m[m7]) + (_vz * m[m11]) + (_vw * m[m15]));
	}

	Vec4 Azul::Vec4::operator*=(const Mat4& m)
	{
		Vec4 vOut((_vx * m[m0]) + (_vy * m[m4]) + (_vz * m[m8]) + (_vw * m[m12]),
				  (_vx * m[m1]) + (_vy * m[m5]) + (_vz * m[m9]) + (_vw * m[m13]),
				  (_vx * m[m2]) + (_vy * m[m6]) + (_vz * m[m10]) + (_vw * m[m14]),
				  (_vx * m[m3]) + (_vy * m[m7]) + (_vz * m[m11]) + (_vw * m[m15]));

		_vx = vOut._vx;
		_vy = vOut._vy;
		_vz = vOut._vz;
		_vw = vOut._vw;

		return *this;
	}

	Vec4 Azul::operator*(const Vec3& v, const Mat4& m)
	{
		//promote vec3 to vec4? (v.x, v.y, v.z, 1.0f)
		return Vec4((v[vx] * m[m0]) + (v[vy] * m[m4]) + (v[vz] * m[m8]) +  (1.0f * m[m12]),
					(v[vx] * m[m1]) + (v[vy] * m[m5]) + (v[vz] * m[m9]) +  (1.0f * m[m13]),
					(v[vx] * m[m2]) + (v[vy] * m[m6]) + (v[vz] * m[m10]) + (1.0f * m[m14]),
					(v[vx] * m[m3]) + (v[vy] * m[m7]) + (v[vz] * m[m11]) + (1.0f * m[m15]));
	}

	Vec4 Azul::operator*=(const Vec3& v, const Mat4& m)
	{
		Vec4 vIn((v[vx] * m[m0]) + (v[vy] * m[m4]) + (v[vz] * m[m8]) + (1.0f * m[m12]),
				 (v[vx] * m[m1]) + (v[vy] * m[m5]) + (v[vz] * m[m9]) + (1.0f * m[m13]),
				 (v[vx] * m[m2]) + (v[vy] * m[m6]) + (v[vz] * m[m1]) + (1.0f * m[m14]),
				 (v[vx] * m[m3]) + (v[vy] * m[m7]) + (v[vz] * m[m1]) + (1.0f * m[m15]));

		return Vec4(vIn._vx, vIn._vy, vIn._vz, vIn._vw);
	}


	//-----------------------------------------------------------------------------
	//	VECTOR FUNCTIONS
	//----------------------------------------------------------------------------- 

	Vec4& Azul::Vec4::norm(void)
	{
		float inverseMag = 1 / this->len();

		this->_vx *= inverseMag;
		this->_vy *= inverseMag;
		this->_vz *= inverseMag;
		this->_vw *= inverseMag;

		return *this;
	}

	Vec4 Azul::Vec4::getNorm(void) const
	{
		float inverseMag = 1 / this->len();
		return Vec4((_vx * inverseMag), (_vy * inverseMag), (_vz * inverseMag), (_vw * inverseMag));
	}

	/*const*/ float Azul::Vec4::dot(const Vec4& vIn) const
	{
		return ((_vx * vIn._vx) + (_vy * vIn._vy) + (_vz * vIn._vz) + (_vw * vIn._vw));
	}

	/*const*/ float Azul::Vec4::len() const
	{
		return Trig::sqrt((_vx * _vx) + (_vy * _vy) + (_vz * _vz) + (_vw * _vw));
	}

	bool Azul::Vec4::isEqual(const Vec4& v, const float epsilon) const
	{
		return (Util::isEqual(_vx, v._vx, epsilon) &&
				Util::isEqual(_vy, v._vy, epsilon) &&
				Util::isEqual(_vz, v._vz, epsilon) &&
				Util::isEqual(_vw, v._vw, epsilon));
	}

	bool Azul::Vec4::isZero(const float epsilon) const
	{
		return (Util::isZero(_vx, epsilon) &&
				Util::isZero(_vy, epsilon) &&
				Util::isZero(_vz, epsilon) &&
				Util::isZero(_vw, epsilon));
	}

	void Azul::Vec4::Print(const char* pName) const
	{
		Debug::Print(pName, *this);
	}


	//-----------------------------------------------------------------------------
	//	SETTERS
	//----------------------------------------------------------------------------- 

	void Azul::Vec4::set(const float inX, const float inY, const float inZ, const float inW)
	{
		this->_vx = inX;
		this->_vy = inY;
		this->_vz = inZ;
		this->_vw = inW;
	}

	void Azul::Vec4::set(const Vec4& A)
	{
		this->_vx = A._vx;
		this->_vy = A._vy;
		this->_vz = A._vz;
		this->_vw = A._vw;
	}

	void Azul::Vec4::set(const Vec3& v, const float w)
	{
		this->_vx = v._vx;
		this->_vy = v._vy;
		this->_vz = v._vz;
		this->_vw = w;
	}


}