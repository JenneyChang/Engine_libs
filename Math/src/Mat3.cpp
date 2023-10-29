#include "Mat3.h"
#include "MathEngine.h"

namespace Azul
{
	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//-----------------------------------------------------------------------------

	Azul::Mat3::Mat3()
		: _m0(0.0f),  _m1(0.0f),  _m2(0.0f),  _m3(0.0f),
		  _m4(0.0f),  _m5(0.0f),  _m6(0.0f),  _m7(0.0f),
		  _m8(0.0f),  _m9(0.0f),  _m10(0.0f), _m11(0.0f),
		  _m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(1.0f)
	{ }

	Azul::Mat3::~Mat3()
	{ }

	Azul::Mat3::Mat3(const Mat3& tM)
		: _m0(tM._m0),  _m1(tM._m1), _m2(tM._m2),  _m3(0.0f),
		  _m4(tM._m4),  _m5(tM._m5), _m6(tM._m6),  _m7(0.0f),
		  _m8(tM._m8),  _m9(tM._m9), _m10(tM._m10),_m11(0.0f),
		  _m12(0.0f),   _m13(0.0f),  _m14(0.0f),   _m15(1.0f)
	{ }

	Mat3& Azul::Mat3::operator=(const Mat3& A)
	{
		if (this != &A)
		{
			this->_m0 = A._m0;
			this->_m1 = A._m1;
			this->_m2 = A._m2;
			this->_m3 = 0.0f;

			this->_m4 = A._m4;
			this->_m5 = A._m5;
			this->_m6 = A._m6;
			this->_m7 = 0.0f;

			this->_m8 = A._m8;
			this->_m9 = A._m9;
			this->_m10 = A._m10;
			this->_m11 = 0.0f;

			this->_m12 = 0.0f;
			this->_m13 = 0.0f;
			this->_m14 = 0.0f;
			this->_m15 = 1.0f;
		}

		return *this;
	}

	Azul::Mat3::Mat3(const Vec3& tV0, const Vec3& tV1, const Vec3& tV2)
		: _m0(tV0[x]), _m1(tV0[y]), _m2(tV0[z]),  _m3(0.0f),
		  _m4(tV1[x]), _m5(tV1[y]), _m6(tV1[z]),  _m7(0.0f),
		  _m8(tV2[x]), _m9(tV2[y]), _m10(tV2[z]), _m11(0.0f),
		  _m12(0.0f),  _m13(0.0f),  _m14(0.0f),   _m15(1.0f)
	{ }

	Azul::Mat3::Mat3(const Mat4& m)
		: _m0(m._m0), _m1(m._m1), _m2(m._m2),   _m3(0.0f),
		  _m4(m._m4), _m5(m._m5), _m6(m._m6),   _m7(0.0f),
		  _m8(m._m8), _m9(m._m9), _m10(m._m10), _m11(0.0f),
		  _m12(0.0f), _m13(0.0f), _m14(0.0f),   _m15(1.0f)
	{ }

	Azul::Mat3::Mat3(const Special type)
	{
		switch (type)
		{
		case Special::Identity:
			this->privSetIdentity();
			break;

		case Special::Zero:
			this->privSetZero();
			break;

		default:
			assert(false);
		}
	}


	//-----------------------------------------------------------------------------
	//	ACCESSORS
	//-----------------------------------------------------------------------------

	Vec3 Azul::Mat3::get(const Row type) const
	{
		switch(type)
		{
		case Row::i0:
			return Vec3(_m0, _m1, _m2);
			break;
		case Row::i1:
			return Vec3(_m4, _m5, _m6);
			break;
		case Row::i2:
			return Vec3(_m8, _m9, _m10);
			break;
		default:
			assert(false);
		}

		return Vec3();
	}

	void Azul::Mat3::set(const Mat3& mIn)
	{
		_m0 = mIn._m0;
		_m1 = mIn._m1;
		_m2 = mIn._m2;

		_m4 = mIn._m4;
		_m5 = mIn._m5;
		_m6 = mIn._m6;

		_m8 = mIn._m8;
		_m9 = mIn._m9;
		_m10 = mIn._m10;
	}

	void Azul::Mat3::set(const Row type, const Vec3& V)
	{
		switch (type)
		{
		case Row::i0:
			this->_m0 = V[x];
			this->_m1 = V[y];
			this->_m2 = V[z];
			break;
		case Row::i1:
			this->_m4 = V[x];
			this->_m5 = V[y];
			this->_m6 = V[z];
			break;
		case Row::i2:
			this->_m8 = V[x];
			this->_m9 = V[y];
			this->_m10 = V[z];
			break;
		default:
			assert(false);
		}
	}

	void Azul::Mat3::set(const Vec3& V0, const Vec3& V1, const Vec3& V2)
	{
		this->_m0 = V0[x];
		this->_m1 = V0[y];
		this->_m2 = V0[z];

		this->_m4 = V1[x];
		this->_m5 = V1[y];
		this->_m6 = V1[z];

		this->_m8 =  V2[x];
		this->_m9 =  V2[y];
		this->_m10 = V2[z];
	}

	void Azul::Mat3::set(const Special type)
	{
		switch (type)
		{
		case Special::Identity:
			this->privSetIdentity();
			break;

		case Special::Zero:
			this->privSetZero();
			break;

		default:
			assert(false);
		}
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: ADD
	//----------------------------------------------------------------------------- 

	Mat3 Azul::Mat3::operator+(void) const
	{
		return Mat3(Vec3(+_m0, +_m1, +_m2), 
					Vec3(+_m4, +_m5, +_m6), 
					Vec3(+_m8, +_m9, +_m10));
	}

	Mat3 Azul::Mat3::operator+(const Mat3& A) const
	{
		return Mat3(Vec3(_m0 + A._m0, _m1 + A._m1, _m2 + A._m2),
					Vec3(_m4 + A._m4, _m5 + A._m5, _m6 + A._m6),
					Vec3(_m8 + A._m8, _m9 + A._m9, _m10 + A._m10));
	}

	void Azul::Mat3::operator+=(const Mat3& A)
	{
		_m0 += A._m0;
		_m1 += A._m1;
		_m2 += A._m2;

		_m4 += A._m4;
		_m5 += A._m5;
		_m6 += A._m6;

		_m8 += A._m8;
		_m9 += A._m9;
		_m10 += A._m10;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SUB
	//----------------------------------------------------------------------------- 

	Mat3 Azul::Mat3::operator-(void) const
	{
		return Mat3(Vec3(-_m0, -_m1, -_m2),
					Vec3(-_m4, -_m5, -_m6),
					Vec3(-_m8, -_m9, -_m10));
	}

	Mat3 Azul::Mat3::operator-(const Mat3& A) const
	{
		return Mat3(Vec3(_m0 - A._m0, _m1 - A._m1, _m2 - A._m2),
					Vec3(_m4 - A._m4, _m5 - A._m5, _m6 - A._m6),
					Vec3(_m8 - A._m8, _m9 - A._m9, _m10 - A._m10));
	}

	void Azul::Mat3::operator-=(const Mat3& A)
	{
		_m0 -= A._m0;
		_m1 -= A._m1;
		_m2 -= A._m2;

		_m4 -= A._m4;
		_m5 -= A._m5;
		_m6 -= A._m6;

		_m8 -= A._m8;
		_m9 -= A._m9;
		_m10 -= A._m10;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SCALE
	//----------------------------------------------------------------------------- 

	Mat3 Azul::Mat3::operator*(const float s) const
	{
		return Mat3(Vec3(_m0 * s, _m1 * s, _m2 * s),
					Vec3(_m4 * s, _m5 * s, _m6 * s),
					Vec3(_m8 * s, _m9 * s, _m10 * s));
	}

	Mat3 Azul::operator*(const float scale, const Mat3& A)
	{
		return Mat3(Vec3(scale * A._m0, scale * A._m1, scale *A._m2),
					Vec3(scale * A._m4, scale * A._m5, scale * A._m6),
					Vec3(scale * A._m8, scale * A._m9, scale * A._m10));
	}

	void Azul::Mat3::operator*=(const float scale)
	{
		_m0	*= scale;
		_m1	*= scale;
		_m2	*= scale;

		_m4	*= scale;
		_m5	*= scale;
		_m6	*= scale;

		_m8	 *= scale;
		_m9	 *= scale;
		_m10 *= scale;
	}

	Mat3 Azul::Mat3::operator*(const Mat3& A) const
	{
		return Mat3(Vec3( (_m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8),  (_m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9),  (_m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10) ),
					Vec3( (_m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8),  (_m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9),  (_m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10) ),
					Vec3( (_m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8), (_m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9), (_m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10) ));
	}

	void Azul::Mat3::operator*=(const Mat3& A)
	{
		Mat3 tmp;

		tmp._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		tmp._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		tmp._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;

		tmp._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		tmp._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		tmp._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;

		tmp._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		tmp._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		tmp._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;

		this->_m0 = tmp._m0;
		this->_m1 = tmp._m1;
		this->_m2 = tmp._m2;

		this->_m4 = tmp._m4;
		this->_m5 = tmp._m5;
		this->_m6 = tmp._m6;

		this->_m8 = tmp._m8;
		this->_m9 = tmp._m9;
		this->_m10 = tmp._m10;
	}


	//-----------------------------------------------------------------------------
	//	VECTOR FUNCTIONS
	//----------------------------------------------------------------------------- 

	/*const*/ float Azul::Mat3::det() const
	{
		//m0(m5m10-m6m9) - m1(m4m10-m6m8) + m2(m4m9 - m5m8)
		return (_m0 * (_m5 * _m10 - _m6 * _m9) - 
				_m1 * (_m4 * _m10 - _m6 * _m8) + 
				_m2 * (_m4 * _m9 - _m5 * _m8));
	}

	Mat3& Azul::Mat3::inv(void)
	{
		float det = (1 / this->det());
		Mat3 adj = this->privGetAdj();

		return (*this = det * adj);
	}

	const Mat3 Azul::Mat3::getInv(void) const
	{
		//|A| = det/adj
		float det = 1/this->det();
		Mat3 adj = this->privGetAdj();
		
		return (det * adj);
	}

	Mat3& Azul::Mat3::T(void)
	{
		Mat3 mOut = this->getT();
		
		this->_v0 = mOut._v0;
		this->_v1 = mOut._v1;
		this->_v2 = mOut._v2;

		return *this;
	}

	const Mat3 Azul::Mat3::getT(void) const
	{
		return Mat3(Vec3(_m0, _m4, _m8), 
					Vec3(_m1, _m5, _m9), 
					Vec3(_m2, _m6, _m10));
	}

	bool Azul::Mat3::isEqual(const Mat3& A, const float epsilon) const
	{
		return (Util::isEqual(_m0, A._m0, epsilon) &&
				Util::isEqual(_m1, A._m1, epsilon) &&
				Util::isEqual(_m2, A._m2, epsilon) &&
				Util::isEqual(_m4, A._m4, epsilon) &&
				Util::isEqual(_m5, A._m5, epsilon) &&
				Util::isEqual(_m6, A._m6, epsilon) &&
				Util::isEqual(_m8, A._m8, epsilon) &&
				Util::isEqual(_m9, A._m9, epsilon) &&
				Util::isEqual(_m10, A._m10, epsilon));
	}

	bool Azul::Mat3::isIdentity(const float epsilon) const
	{
		return (Util::isOne (_m0, epsilon) &&
				Util::isZero(_m1, epsilon) &&
				Util::isZero(_m2, epsilon) &&

				Util::isZero(_m4, epsilon) &&
				Util::isOne (_m5, epsilon) &&
				Util::isZero(_m6, epsilon) &&

				Util::isZero(_m8, epsilon) &&
				Util::isZero(_m9, epsilon) &&
				Util::isOne (_m10, epsilon));
	}

	void Azul::Mat3::Print(const char* pName) const
	{
		Debug::Print(pName, *this);
	}


	//-----------------------------------------------------------------------------
	//	PRIVATE FUNCTIONS
	//----------------------------------------------------------------------------- 

	void Azul::Mat3::privSetZero()
	{
		this->_m0 = 0.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = 0.0f;
		this->_m6 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 0.0f;
	}

	void Azul::Mat3::privSetIdentity()
	{
		this->_m0 = 1.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = 1.0f;
		this->_m6 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 1.0f;
	}

	const Mat3 Azul::Mat3::privGetAdj(void) const
	{
		//find cofactor
		//Mat3 mOut;

		//M_11 = (m5m10) - (m6m9)
		//M_12 = (m4m10) - (m6m8)
		//M_12 = (m4m9) - (m5m8)

		//M_21 = (m1m10) - (m2m9)
		//M_22 = (m0m10) - (m2m8)
		//M_23 = (m0m9) - (m1-m8)

		//M_31 = (m1m6) - (m2m5)
		//M_32 = (m0m6) - (m2m4)
		//M_33 = (m0m5) - (m1m4)

		//get transpose & fix signs?
	/*	return Mat3(Vec3(+mOut._m0, -mOut._m4, +mOut._m8), 
					Vec3(-mOut._m1, +mOut._m5, -mOut._m9), 
					Vec3(+mOut._m2, -mOut._m6, +mOut._m10));*/

		return Mat3(Vec3(+((_m5 * _m10) - (_m6 * _m9)), -((_m1 * _m10) - (_m2 * _m9)), +((_m1 * _m6) - (_m2 * _m5))),
					Vec3(-((_m4 * _m10) - (_m6 * _m8)), +((_m0 * _m10) - (_m2 * _m8)), -((_m0 * _m6) - (_m2 * _m4))),
					Vec3(+((_m4 * _m9) - (_m5 * _m8)),  -((_m0 * _m9) - (_m1 * _m8)),  +((_m0 * _m5) - (_m1 * _m4))));
	}


}