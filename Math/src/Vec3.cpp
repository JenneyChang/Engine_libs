#include "Vec3.h"
#include "MathEngine.h"

namespace Azul
{
	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------- 

	Azul::Vec3::Vec3()
		: _vx(0.0f), _vy(0.0f), _vz(0.0f)
	{ }

	Azul::Vec3::~Vec3()
	{ }

	Azul::Vec3::Vec3(const Vec3& inV)
		: _vx(inV._vx), _vy(inV._vy), _vz(inV._vz)
	{ }

	Vec3& Azul::Vec3::operator=(const Vec3& v)
	{
		if (this != &v)
		{
			this->_vx = v._vx;
			this->_vy = v._vy;
			this->_vz = v._vz;
		}

		return *this;
	}

	Azul::Vec3::Vec3(const float in_x, const float in_y, const float in_z)
		: _vx(in_x), _vy(in_y), _vz(in_z)
	{ }

	// Forces User to explicitly do the cast or constructor call with explicit
	Azul::Vec3::Vec3(const Vec4& v)
		: _vx(v._vx), _vy(v._vy), _vz(v._vz)
	{ }

	Vec3& Azul::Vec3::operator=(const Vec4& v)
	{
		//TODO
		this->_vx = v._vx;
		this->_vy = v._vy;
		this->_vz = v._vz;

		return *this;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: ADD
	//----------------------------------------------------------------------------- 

	Vec3 Azul::Vec3::operator+(void) const
	{
		return Vec3(+_vx, +_vy, +_vz);
	}

	Vec3 Azul::Vec3::operator+(const Vec3& inV) const
	{
		return Vec3(_vx + inV._vx, _vy + inV._vy, _vz + inV._vz);
	}

	void Azul::Vec3::operator+=(const Vec3& inV)
	{
		_vx += inV._vx;
		_vy += inV._vy;
		_vz += inV._vz;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SUB
	//----------------------------------------------------------------------------- 
	
	Vec3 Azul::Vec3::operator-(void) const
	{
		return Vec3(-_vx, -_vy, -_vz);
	}

	Vec3 Azul::Vec3::operator-(const Vec3& inV) const
	{
		return Vec3(_vx - inV._vx, _vy - inV._vy, _vz - inV._vz);
	}

	void Azul::Vec3::operator-=(const Vec3& inV)
	{
		_vx -= inV._vx;
		_vy -= inV._vy;
		_vz -= inV._vz;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SCALE
	//----------------------------------------------------------------------------- 

	Vec3 Azul::Vec3::operator*(const float scale) const
	{
		return Vec3(_vx * scale, _vy * scale, _vz * scale);
	}

	Vec3 Azul::operator*(const float scale, const Vec3& inV)
	{
		return Vec3(scale * inV._vx, scale * inV._vy, scale * inV._vz);
	}

	void Azul::Vec3::operator*=(const float scale)
	{
		_vx *= scale;
		_vy *= scale;
		_vz *= scale;
	}

	Vec3 Azul::Vec3::operator*(const Mat3& m) const
	{
		return Vec3((_vx * m._m0 + _vy * m._m4 + _vz * m._m8),
					(_vx * m._m1 + _vy * m._m5 + _vz * m._m9),
					(_vx * m._m2 + _vy * m._m6 + _vz * m._m10));
	}

	Vec3 Azul::Vec3::operator*=(const Mat3& m)
	{
		Vec3 vOut((_vx * m._m0 + _vy * m._m4 + _vz * m._m8),
				  (_vx * m._m1 + _vy * m._m5 + _vz * m._m9),
				  (_vx * m._m2 + _vy * m._m6 + _vz * m._m10));

		this->_vx = vOut._vx;
		this->_vy = vOut._vy;
		this->_vz = vOut._vz;

		return *this;
	}

	Vec3 Azul::Vec3::operator*(const Quat& q) const
	{
		Quat qOut = Quat(_vx, _vy, _vz, 0.0f);

		//q.conj * v * q
		Quat temp = q.getConj() * qOut * q;

		return Vec3(temp.qx(), temp.qy(), temp.qz());
	}

	Vec3 Azul::Vec3::operator*=(const Quat& q)
	{
		Quat qOut = Quat(_vx, _vy, _vz, 0.0f);

		//q.conj * v * q
		Quat temp = q.getConj() * qOut * q;

		this->_vx = temp.qx();
		this->_vy = temp.qy();
		this->_vz = temp.qz();

		return Vec3(_vx, _vy, _vz);
	}


	//-----------------------------------------------------------------------------
	//	VECTOR FUNCTIONS
	//----------------------------------------------------------------------------- 

	Vec3& Azul::Vec3::norm(void)
	{
		float inverseMagnitude = 1.0f / this->len();

		this->_vx *= inverseMagnitude;
		this->_vy *= inverseMagnitude;
		this->_vz *= inverseMagnitude;

		return *this;
	}
	
	Vec3 Azul::Vec3::getNorm(void) const
	{
		float inverseMagnitude = 1.0f / this->len();
		return Vec3(_vx * inverseMagnitude, _vy * inverseMagnitude, _vz * inverseMagnitude);
	}

	/*const*/ float Azul::Vec3::dot(const Vec3& vIn) const
	{
		return ((_vx * vIn._vx) + (_vy * vIn._vy) + (_vz * vIn._vz));
	}

	const Vec3 Azul::Vec3::cross(const Vec3& vIn) const
	{
		return Vec3( ((_vy * vIn._vz) - (_vz * vIn._vy)),
					-((_vx * vIn._vz) - (_vz * vIn._vx)),
					 ((_vx * vIn._vy) - (_vy * vIn._vx)));
	}

	/*const Vec3Proxy Azul::Vec3::len(void) const
	{
		return Vec3Proxy();
	}*/

	/*const*/ float Azul::Vec3::len(void) const
	{
		return Trig::sqrt((_vx * _vx) + (_vy * _vy) + (_vz * _vz));
	}

	/*const*/ float Azul::Vec3::getAngle(const Vec3& vIn) const
	{
		return Trig::acos(dot(vIn)/(len() * vIn.len()));
	}

	bool Azul::Vec3::isEqual(const Vec3& v, const float epsilon) const
	{
		return (Util::isEqual(_vx, v._vx, epsilon) &&
				Util::isEqual(_vy, v._vy, epsilon) &&
				Util::isEqual(_vz, v._vz, epsilon));
	}

	bool Azul::Vec3::isZero(const float epsilon) const
	{
		return (Util::isZero(_vx, epsilon) && 
				Util::isZero(_vy, epsilon) && 
				Util::isZero(_vz, epsilon));
	}

	void Azul::Vec3::Print(const char* pName) const
	{
		Debug::Print(pName, *this);
	}


	//-----------------------------------------------------------------------------
	//	SETTERS
	//----------------------------------------------------------------------------- 

	void Azul::Vec3::set(const float inX, const float inY, const float inZ)
	{
		this->_vx = inX;
		this->_vy = inY;
		this->_vz = inZ;
	}

	void Azul::Vec3::set(const Vec3& A)
	{
		this->_vx = A._vx;
		this->_vy = A._vy;
		this->_vz = A._vz;
	}

	void Azul::Vec3::set(const Vec4& A)
	{
		this->_vx = A._vx;
		this->_vy = A._vy;
		this->_vz = A._vz;
	}

}