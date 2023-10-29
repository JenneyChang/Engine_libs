#include "Mat4.h"
#include "MathEngine.h"

namespace Azul
{
	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//-----------------------------------------------------------------------------

	Azul::Mat4::Mat4()
		: _m0(0.0f),  _m1(0.0f),  _m2(0.0f),  _m3(0.0f),
		  _m4(0.0f),  _m5(0.0f),  _m6(0.0f),  _m7(0.0f),
		  _m8(0.0f),  _m9(0.0f),  _m10(0.0f), _m11(0.0f),
		  _m12(0.0f), _m13(0.0f), _m14(0.0f), _m15(0.0f)
	{ }

	Azul::Mat4::~Mat4()
	{ }

	Azul::Mat4::Mat4(const Mat4& tM)
		: _m0(tM._m0),   _m1(tM._m1),   _m2(tM._m2),   _m3(tM._m3),
		  _m4(tM._m4),   _m5(tM._m5),   _m6(tM._m6),   _m7(tM._m7),
		  _m8(tM._m8),   _m9(tM._m9),   _m10(tM._m10), _m11(tM._m11),
		  _m12(tM._m12), _m13(tM._m13), _m14(tM._m14), _m15(tM._m15)
	{ }

	Mat4& Azul::Mat4::operator=(const Mat4& tM)
	{
		if (this != &tM)
		{
			this->_m0 = tM._m0;
			this->_m1 = tM._m1;
			this->_m2 = tM._m2;
			this->_m3 = tM._m3;
			this->_m4 = tM._m4;
			this->_m5 = tM._m5;
			this->_m6 = tM._m6;
			this->_m7 = tM._m7;
			this->_m8 = tM._m8;
			this->_m9 = tM._m9;
			this->_m10 = tM._m10;
			this->_m11 = tM._m11;
			this->_m12 = tM._m12;
			this->_m13 = tM._m13;
			this->_m14 = tM._m14;
			this->_m15 = tM._m15;
		}

		return *this;
	}

	Azul::Mat4::Mat4(const Vec4& tV0, const Vec4& tV1, const Vec4& tV2, const Vec4& tV3)
		: _v0(tV0), _v1(tV1), _v2(tV2), _v3(tV3)
	{ }

	Azul::Mat4::Mat4(const Quat& q)
	{
		this->privSetQuat(q);
	}

	Azul::Mat4::Mat4(const Special type)
	{
		switch (type)
		{
		case Special::Identity:
			this->privSetIdentity();
			break;

		case Special::Zero:
			this->privSetZero();
			break;
		}
	}

	Azul::Mat4::Mat4(const Trans type, const float tx, const float ty, const float tz)
	{
		if (type == Trans::XYZ)
		{
			this->privSetTransXYZ(tx, ty, tz);
			this->privSetTransHint();
		}
	}

	Azul::Mat4::Mat4(const Trans type, const Vec3& vTrans)
	{
		if (type == Trans::XYZ)
		{
			this->privSetTransXYZ(vTrans[x], vTrans[y], vTrans[z]);
			this->privSetTransHint();
		}
	}

	Azul::Mat4::Mat4(const Scale type, const float sx, const float sy, const float sz)
	{
		if (type == Scale::XYZ)
		{
			this->privSetScaleXYZ(sx, sy, sz);
			this->privSetScaleHint();
		}
	}

	Azul::Mat4::Mat4(const Scale type, const Vec3& vScale)
	{
		if (type == Scale::XYZ)
		{
			this->privSetScaleXYZ(vScale[x], vScale[y], vScale[z]);
			this->privSetScaleHint();
		}
	}

	Azul::Mat4::Mat4(const Orient type, const Vec3& dof, const Vec3& up)
	{
		switch (type)
		{
		case Orient::LocalToWorld:
			this->privSetRotOrient(dof, up);
			break;

		case Orient::WorldToLocal:
			this->privSetRotInvOrient(dof, up);
			break;
		}
	}

	Azul::Mat4::Mat4(const Rot r, const Vec3& vAxis, const float angle_radians)
	{
		if (r == Rot::AxisAngle)
		{
			this->privSetAxisAngle(vAxis, angle_radians);
		}
	}

	Azul::Mat4::Mat4(const Rot1 type, const float angle)
	{
		switch (type)
		{
		case Rot1::X:
			this->privSetRotX(angle);
			break;

		case Rot1::Y:
			this->privSetRotY(angle);
			break;

		case Rot1::Z:
			this->privSetRotZ(angle);
			break;
		}

		this->privSetRotHint();
	}

	Azul::Mat4::Mat4(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
	{
		if (mode == Rot3::XYZ)
		{
			this->privSetRotXYZ(angle_0, angle_1, angle_2);
			this->privSetRotHint();
		}
	}


	//-----------------------------------------------------------------------------
	//	ACCESSORS
	//-----------------------------------------------------------------------------

	void Azul::Mat4::set(const Mat4& mIn)
	{
		this->_m0 = mIn._m0;
		this->_m1 = mIn._m1;
		this->_m2 = mIn._m2;
		this->_m3 = mIn._m3;

		this->_m4 = mIn._m4;
		this->_m5 = mIn._m5;
		this->_m6 = mIn._m6;
		this->_m7 = mIn._m7;

		this->_m8 = mIn._m8;
		this->_m9 = mIn._m9;
		this->_m10 = mIn._m10;
		this->_m11 = mIn._m11;

		this->_m12 = mIn._m12;
		this->_m13 = mIn._m13;
		this->_m14 = mIn._m14;
		this->_m15 = mIn._m15;
	}

	void Azul::Mat4::set(const Vec4& V0, const Vec4& V1, const Vec4& V2, const Vec4& V3)
	{
		this->_v0.set(V0);
		this->_v1.set(V1);
		this->_v2.set(V2);
		this->_v3.set(V3);
	}

	void Azul::Mat4::set(const Row type, const Vec4& V)
	{
		switch (type)
		{
		case Row::i0:
			this->_v0.set(V);
			break;
		case Row::i1:
			this->_v1.set(V);
			break;
		case Row::i2:
			this->_v2.set(V);
			break;
		case Row::i3:
			this->_v3.set(V);
			break;
		}
	}

	Vec4 Azul::Mat4::get(const Row type) const
	{
		switch (type)
		{
		case Row::i0:
			return this->_v0;
			break;
		case Row::i1:
			return this->_v1;
			break;
		case Row::i2:
			return this->_v2;
			break;
		case Row::i3:
			return this->_v3;
			break;
		}

		return Vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Azul::Mat4::set(const Trans type, const float tx, const float ty, const float tz)
	{
		if (type == Trans::XYZ)
		{
			this->privSetTransXYZ(tx, ty, tz);
		}

		this->privSetTransHint();
	}

	void Azul::Mat4::set(const Trans type, const Vec3& vTrans)
	{
		if (type == Trans::XYZ)
		{
			this->privSetTransXYZ(vTrans[x], vTrans[y], vTrans[z]);
		}

		this->privSetTransHint();
	}

	void Azul::Mat4::set(const Scale type, const float sx, const float sy, const float sz)
	{
		if (type == Scale::XYZ)
		{
			this->privSetScaleXYZ(sx, sy, sz);
		}

		this->privSetScaleHint();
	}

	void Azul::Mat4::set(const Scale type, const Vec3& vScale)
	{
		if (type == Scale::XYZ)
		{
			this->privSetScaleXYZ(vScale[x], vScale[y], vScale[z]);
		}

		this->privSetScaleHint();
	}

	void Azul::Mat4::set(const Special type)
	{
		switch (type)
		{
		case Special::Identity:
			this->privSetIdentity();
			break;

		case Special::Zero:
			this->privSetZero();
			break;
		}
	}

	void Azul::Mat4::set(const Rot r, const Vec3& vAxis, const float angle_radians)
	{
		if (r == Rot::AxisAngle)
		{
			this->privSetAxisAngle(vAxis, angle_radians);
		}
	}

	void Azul::Mat4::set(const Rot1 type, const float angle)
	{
		switch (type)
		{
		case Rot1::X:
			this->privSetRotX(angle);
			break;

		case Rot1::Y:
			this->privSetRotY(angle);
			break;

		case Rot1::Z:
			this->privSetRotZ(angle);
			break;
		}

		this->privSetRotHint();
	}

	void Azul::Mat4::set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
	{
		if (mode == Rot3::XYZ)
		{
			this->privSetRotXYZ(angle_0, angle_1, angle_2);
			this->privSetRotHint();
		}
	}

	void Azul::Mat4::set(const Orient o, const Vec3& dof, const Vec3& up)
	{
		switch (o)
		{
		case Orient::LocalToWorld:
			this->privSetRotOrient(dof, up);
			break;

		case Orient::WorldToLocal:
			this->privSetRotInvOrient(dof, up);
			break;
		}
	}

	void Azul::Mat4::set(const Quat& q)
	{
		this->privSetQuat(q);
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: ADD
	//----------------------------------------------------------------------------- 

	Mat4 Azul::Mat4::operator+(void) const
	{
		return Mat4(Vec4(+_m0, +_m1, +_m2, +_m3),
					Vec4(+_m4, +_m5, +_m6, +_m7),
					Vec4(+_m8, +_m9, +_m10, +_m11),
					Vec4(+_m12, +_m13, +_m14, +_m15));
	}

	Mat4 Azul::Mat4::operator+(const Mat4& A) const
	{
		return Mat4(Vec4(_m0 + A._m0, _m1 + A._m1, _m2 + A._m2, _m3 + A._m3),
					Vec4(_m4 + A._m4, _m5 + A._m5, _m6 + A._m6, _m7 + A._m7),
					Vec4(_m8 + A._m8, _m9 + A._m9, _m10 + A._m10, _m11 + A._m11),
					Vec4(_m12 + A._m12, _m13 + A._m13, _m14 + A._m14, _m15 + A._m15));
	}

	void Azul::Mat4::operator+=(const Mat4& A)
	{
		this->_m0 += A._m0;
		this->_m1 += A._m1;
		this->_m2 += A._m2;
		this->_m3 += A._m3;

		this->_m4 += A._m4;
		this->_m5 += A._m5;
		this->_m6 += A._m6;
		this->_m7 += A._m7;

		this->_m8 += A._m8;
		this->_m9 += A._m9;
		this->_m10 += A._m10;
		this->_m11 += A._m11;

		this->_m12 += A._m12;
		this->_m13 += A._m13;
		this->_m14 += A._m14;
		this->_m15 += A._m15;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SUB
	//----------------------------------------------------------------------------- 

	Mat4 Azul::Mat4::operator-(void) const
	{
		return Mat4(Vec4(-_m0, -_m1, -_m2, -_m3),
					Vec4(-_m4, -_m5, -_m6, -_m7),
					Vec4(-_m8, -_m9, -_m10, -_m11),
					Vec4(-_m12, -_m13, -_m14, -_m15));
	}

	Mat4 Azul::Mat4::operator-(const Mat4& A) const
	{
		return Mat4(Vec4(_m0 - A._m0, _m1 - A._m1, _m2 - A._m2, _m3 - A._m3),
					Vec4(_m4 - A._m4, _m5 - A._m5, _m6 - A._m6, _m7 - A._m7),
					Vec4(_m8 - A._m8, _m9 - A._m9, _m10 - A._m10, _m11 - A._m11),
					Vec4(_m12 - A._m12, _m13 - A._m13, _m14 - A._m14, _m15 - A._m15));
	}

	void Azul::Mat4::operator-=(const Mat4& A)
	{
		this->_m0 -= A._m0;
		this->_m1 -= A._m1;
		this->_m2 -= A._m2;
		this->_m3 -= A._m3;

		this->_m4 -= A._m4;
		this->_m5 -= A._m5;
		this->_m6 -= A._m6;
		this->_m7 -= A._m7;

		this->_m8 -= A._m8;
		this->_m9 -= A._m9;
		this->_m10 -= A._m10;
		this->_m11 -= A._m11;

		this->_m12 -= A._m12;
		this->_m13 -= A._m13;
		this->_m14 -= A._m14;
		this->_m15 -= A._m15;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: MULTIPLICATION
	//----------------------------------------------------------------------------- 
 
	Mat4 Azul::Mat4::operator*(const float s) const
	{
		return Mat4(Vec4(_m0 * s, _m1 * s, _m2 * s, _m3 * s),
					Vec4(_m4 * s, _m5 * s, _m6 * s, _m7 * s),
					Vec4(_m8 * s, _m9 * s, _m10 * s, _m11 * s),
					Vec4(_m12 * s, _m13 * s, _m14 * s, _m15 * s));
	}

	Mat4 Azul::operator*(const float scale, const Mat4& A)
	{
		return Mat4(Vec4(A._m0 * scale, A._m1 * scale, A._m2 * scale, A._m3 * scale),
					Vec4(A._m4 * scale, A._m5 * scale, A._m6 * scale, A._m7 * scale),
					Vec4(A._m8 * scale, A._m9 * scale, A._m10 * scale , A._m11 * scale),
					Vec4(A._m12 * scale, A._m13 * scale, A._m14 * scale, A._m15 * scale));
	}

	void Azul::Mat4::operator*=(const float scale)
	{
		this->_m0 *= scale;
		this->_m1 *= scale;
		this->_m2 *= scale;
		this->_m3 *= scale;

		this->_m4 *= scale;
		this->_m5 *= scale;
		this->_m6 *= scale;
		this->_m7 *= scale;

		this->_m8 *= scale;
		this->_m9 *= scale;
		this->_m10 *= scale;
		this->_m11 *= scale;

		this->_m12 *= scale;
		this->_m13 *= scale;
		this->_m14 *= scale;
		this->_m15 *= scale;
	}

	Mat4 Azul::Mat4::operator*(const Mat4& A) const
	{
		Hint hA = this->privGetHint();
		Hint hB = A.privGetHint();

		Mat4 mout(  Vec4((_m0 * A._m0) + (_m1 * A._m4) + (_m2 * A._m8) + (_m3 * A._m12),
					     (_m0 * A._m1) + (_m1 * A._m5) + (_m2 * A._m9) + (_m3 * A._m13),
					     (_m0 * A._m2) + (_m1 * A._m6) + (_m2 * A._m10) + (_m3 * A._m14),
					     (_m0 * A._m3) + (_m1 * A._m7) + (_m2 * A._m11) + (_m3 * A._m15)),

					Vec4((_m4 * A._m0) + (_m5 * A._m4) + (_m6 * A._m8) + (_m7 * A._m12),
						(_m4 * A._m1) + (_m5 * A._m5) + (_m6 * A._m9) + (_m7 * A._m13),
						(_m4 * A._m2) + (_m5 * A._m6) + (_m6 * A._m10) + (_m7 * A._m14),
						(_m4 * A._m3) + (_m5 * A._m7) + (_m6 * A._m11) + (_m7 * A._m15)),

					Vec4((_m8 * A._m0) + (_m9 * A._m4) + (_m10 * A._m8) + (_m11 * A._m12),
						(_m8 * A._m1) + (_m9 * A._m5) + (_m10 * A._m9) + (_m11 * A._m13),
						(_m8 * A._m2) + (_m9 * A._m6) + (_m10 * A._m10) + (_m11 * A._m14),
						(_m8 * A._m3) + (_m9 * A._m7) + (_m10 * A._m11) + (_m11 * A._m15)),

					Vec4((_m12 * A._m0) + (_m13 * A._m4) + (_m14 * A._m8) + (_m15 * A._m12),
						(_m12 * A._m1) + (_m13 * A._m5) + (_m14 * A._m9) + (_m15 * A._m13),
						(_m12 * A._m2) + (_m13 * A._m6) + (_m14 * A._m10) + (_m15 * A._m14),
						(_m12 * A._m3) + (_m13 * A._m7) + (_m14 * A._m11) + (_m15 * A._m15)));

		
		mout.privSetNewHint(hA, hB);

		return mout;

		/*return Mat4(Vec4((_m0 * A._m0) + (_m1 * A._m4) + (_m2 * A._m8) + (_m3 * A._m12),
						 (_m0 * A._m1) + (_m1 * A._m5) + (_m2 * A._m9) + (_m3 * A._m13),
						 (_m0 * A._m2) + (_m1 * A._m6) + (_m2 * A._m10) + (_m3 * A._m14),
						 (_m0 * A._m3) + (_m1 * A._m7) + (_m2 * A._m11) + (_m3 * A._m15)),

					Vec4((_m4 * A._m0) + (_m5 * A._m4) + (_m6 * A._m8) + (_m7 * A._m12),
						 (_m4 * A._m1) + (_m5 * A._m5) + (_m6 * A._m9) + (_m7 * A._m13),
						 (_m4 * A._m2) + (_m5 * A._m6) + (_m6 * A._m10) + (_m7 * A._m14),
						 (_m4 * A._m3) + (_m5 * A._m7) + (_m6 * A._m11) + (_m7 * A._m15)),

					Vec4((_m8 * A._m0) + (_m9 * A._m4) + (_m10 * A._m8) +  (_m11 * A._m12),
						 (_m8 * A._m1) + (_m9 * A._m5) + (_m10 * A._m9) +  (_m11 * A._m13),
						 (_m8 * A._m2) + (_m9 * A._m6) + (_m10 * A._m10) + (_m11 * A._m14),
						 (_m8 * A._m3) + (_m9 * A._m7) + (_m10 * A._m11) + (_m11 * A._m15)),
			
					Vec4((_m12 * A._m0) + (_m13 * A._m4) + (_m14 * A._m8) +  (_m15 * A._m12),
						 (_m12 * A._m1) + (_m13 * A._m5) + (_m14 * A._m9) +  (_m15 * A._m13),
						 (_m12 * A._m2) + (_m13 * A._m6) + (_m14 * A._m10) + (_m15 * A._m14),
						 (_m12 * A._m3) + (_m13 * A._m7) + (_m14 * A._m11) + (_m15 * A._m15)));*/
	}

	void Azul::Mat4::operator*=(const Mat4& A)
	{
		Mat4 mOut(Vec4( (_m0 * A._m0) + (_m1 * A._m4) + (_m2 * A._m8) + (_m3 * A._m12),
						(_m0 * A._m1) + (_m1 * A._m5) + (_m2 * A._m9) + (_m3 * A._m13),
						(_m0 * A._m2) + (_m1 * A._m6) + (_m2 * A._m10) + (_m3 * A._m14),
						(_m0 * A._m3) + (_m1 * A._m7) + (_m2 * A._m11) + (_m3 * A._m15)),

				  Vec4( (_m4 * A._m0) + (_m5 * A._m4) + (_m6 * A._m8) + (_m7 * A._m12),
						(_m4 * A._m1) + (_m5 * A._m5) + (_m6 * A._m9) + (_m7 * A._m13),
						(_m4 * A._m2) + (_m5 * A._m6) + (_m6 * A._m10) + (_m7 * A._m14),
						(_m4 * A._m3) + (_m5 * A._m7) + (_m6 * A._m11) + (_m7 * A._m15)),
				  
				  Vec4( (_m8 * A._m0) + (_m9 * A._m4) + (_m10 * A._m8) + (_m11 * A._m12),
						(_m8 * A._m1) + (_m9 * A._m5) + (_m10 * A._m9) + (_m11 * A._m13),
						(_m8 * A._m2) + (_m9 * A._m6) + (_m10 * A._m10) + (_m11 * A._m14),
						(_m8 * A._m3) + (_m9 * A._m7) + (_m10 * A._m11) + (_m11 * A._m15)),

				  Vec4( (_m12 * A._m0) + (_m13 * A._m4) + (_m14 * A._m8) + (_m15 * A._m12),
						(_m12 * A._m1) + (_m13 * A._m5) + (_m14 * A._m9) + (_m15 * A._m13),
						(_m12 * A._m2) + (_m13 * A._m6) + (_m14 * A._m10) + (_m15 * A._m14),
						(_m12 * A._m3) + (_m13 * A._m7) + (_m14 * A._m11) + (_m15 * A._m15)));

		this->_v0 = mOut._v0;
		this->_v1 = mOut._v1;
		this->_v2 = mOut._v2;
		this->_v3 = mOut._v3;
	}

	Mat4 Azul::Mat4::operator*(const Quat& q) const
	{
		//convert quat to mat4
		Mat4 mOut = Mat4(q);

		return Mat4(*this * mOut);
	}

	Mat4 Azul::Mat4::operator*=(const Quat& q)
	{
		Mat4 mOut = Mat4(q);
		*this *= mOut;

		return *this;
	}


	//-----------------------------------------------------------------------------
	//	MAT4 FUNCTIONS
	//-----------------------------------------------------------------------------

	/*const*/ float Azul::Mat4::det() const
	{
		Mat3 A(Vec3(_m5, _m6, _m7), Vec3(_m9, _m10, _m11), Vec3(_m13, _m14, _m15));
		Mat3 B(Vec3(_m4, _m6, _m7), Vec3(_m8, _m10, _m11), Vec3(_m12, _m14, _m15));
		Mat3 C(Vec3(_m4, _m5, _m7), Vec3(_m8, _m9, _m11), Vec3(_m12, _m13, _m15));
		Mat3 D(Vec3(_m4, _m5, _m6), Vec3(_m8, _m9, _m10), Vec3(_m12, _m13, _m14));

		return ((_m0 * A.det()) - (_m1 * B.det()) + (_m2 * C.det()) - (_m3 * D.det()));
	}

	Mat4& Azul::Mat4::T(void)
	{
		Mat4 mOut(Vec4(_m0, _m4, _m8, _m12),
				  Vec4(_m1, _m5, _m9, _m13),
				  Vec4(_m2, _m6, _m10, _m14),
				  Vec4(_m3, _m7, _m11, _m15));

		this->_v0 = mOut._v0;
		this->_v1 = mOut._v1;
		this->_v2 = mOut._v2;
		this->_v3 = mOut._v3;

		return *this;
	}

	const Mat4 Azul::Mat4::getT(void) const
	{
		return Mat4(Vec4(_m0, _m4, _m8 , _m12), 
					Vec4(_m1, _m5, _m9 , _m13), 
					Vec4(_m2, _m6, _m10, _m14), 
					Vec4(_m3, _m7, _m11, _m15));
	}

	const Mat4 Azul::Mat4::getInv(void) const
	{
		Hint h = this->privGetHint();

		if (h == Hint::Rot)
		{
			return this->getT();
		}
		else if (h == Hint::Trans)
		{
			return Mat4(Vec4(_m0, _m1, _m2, _m3),
						Vec4(_m4, _m5, _m6, _m7),
						Vec4(_m8, _m9, _m10, _m11),
						Vec4(-_m12, -_m13, -_m14, _m15));
		}
		else if(h == Hint::Scale)
		{
			return  Mat4(Vec4(1/_m0,   _m1,    _m2, _m3),
						 Vec4(  _m4, 1/_m5,    _m6, _m7),
						 Vec4(  _m8,   _m9, 1/_m10, _m11),
						 Vec4( _m12,  _m13,   _m14, _m15));
		}
		else if (h == Hint::RotTrans)
		{
			return Mat4(Vec4(  _m0,   _m4,   _m8,  _m3),
						Vec4(  _m1,   _m5,   _m9,  _m7),
						Vec4(  _m2,   _m6,  _m10, _m11),
						Vec4(-_m12, -_m13, -_m14, _m15));
		}
		float det = this->det();
		float invdet = 1.0f / det;

		Mat4 adj = this->privGetAdj();

		return (invdet * adj);
	}

	Mat4& Azul::Mat4::inv(void)
	{
		float det = 1 / this->det();
		Mat4 adj = this->privGetAdj();

		return *this = det * adj;
	}

	/*const*/ bool Azul::Mat4::isEqual(const Mat4& A, const float epsilon) const
	{
		return (Util::isEqual(_m0, A._m0, epsilon) &&
				Util::isEqual(_m1, A._m1, epsilon) &&
				Util::isEqual(_m2, A._m2, epsilon) &&
				Util::isEqual(_m3, A._m3, epsilon) &&
				
				Util::isEqual(_m4, A._m4, epsilon) && 
				Util::isEqual(_m5, A._m5, epsilon) && 
				Util::isEqual(_m6, A._m6, epsilon) && 
				Util::isEqual(_m7, A._m7, epsilon) && 
				
				Util::isEqual(_m8,  A._m8, epsilon) && 
				Util::isEqual(_m9,  A._m9, epsilon) && 
				Util::isEqual(_m10, A._m10, epsilon) && 
				Util::isEqual(_m11, A._m11, epsilon) && 
				
				Util::isEqual(_m12, A._m12, epsilon) && 
				Util::isEqual(_m13, A._m13, epsilon) && 
				Util::isEqual(_m14, A._m14, epsilon) && 
				Util::isEqual(_m15, A._m15, epsilon));
	}

	/*const*/ bool Azul::Mat4::isIdentity(const float epsilon) const
	{
		return (Util::isOne(_m0, epsilon)  &&
				Util::isZero(_m1, epsilon) &&
				Util::isZero(_m2, epsilon) &&
				Util::isZero(_m3, epsilon) &&

				Util::isZero(_m4, epsilon) &&
				Util::isOne(_m5, epsilon)  &&
				Util::isZero(_m6, epsilon) &&
				Util::isZero(_m7, epsilon) &&

				Util::isZero(_m8, epsilon) &&
				Util::isZero(_m9, epsilon) &&
				Util::isOne(_m10, epsilon) &&
				Util::isZero(_m11, epsilon) &&

				Util::isZero(_m12, epsilon) &&
				Util::isZero(_m13, epsilon) &&
				Util::isZero(_m14, epsilon) &&
				Util::isOne(_m15, epsilon));
	}

	/*const*/ bool Azul::Mat4::isRotation(const float epsilon) const
	{
		//Mat4 * Mat4_Transpose = Identity (true -- is rotation)
		Mat4 mOut(*this * this->getT());

		return mOut.isIdentity(epsilon);
	}

	void Azul::Mat4::Print(const char* pName) const
	{
		Debug::Print(pName, *this);
	}


	//-----------------------------------------------------------------------------
	//	PRIVATE FUNCTIONS
	//-----------------------------------------------------------------------------

	const Mat4 Azul::Mat4::privGetAdj(void) const
	{
		return Mat4(Vec4((_m6 * _m11 * _m13) - (_m7 * _m10 * _m13) + (_m7 * _m9 * _m14) - (_m5 * _m11 * _m14) - (_m6 * _m9 * _m15) + (_m5 * _m10 * _m15),
						 (_m3 * _m10 * _m13) - (_m2 * _m11 * _m13) - (_m3 * _m9 * _m14) + (_m1 * _m11 * _m14) + (_m2 * _m9 * _m15) - (_m1 * _m10 * _m15),
						 (_m2 * _m7 * _m13) - (_m3 * _m6 * _m13) + (_m3 * _m5 * _m14) - (_m1 * _m7 * _m14) - (_m2 * _m5 * _m15) + (_m1 * _m6 * _m15),
						 (_m3 * _m6 * _m9) - (_m2 * _m7 * _m9) - (_m3 * _m5 * _m10) + (_m1 * _m7 * _m10) + (_m2 * _m5 * _m11) - (_m1 * _m6 * _m11)),
					
					Vec4((_m7 * _m10 * _m12) - (_m6 * _m11 * _m12) - (_m7 * _m8 * _m14) + (_m4 * _m11 * _m14) + (_m6 * _m8 * _m15) - (_m4 * _m10 * _m15),
						 (_m2 * _m11 * _m12) - (_m3 * _m10 * _m12) + (_m3 * _m8 * _m14) - (_m0 * _m11 * _m14) - (_m2 * _m8 * _m15) + (_m0 * _m10 * _m15),
						 (_m3 * _m6 * _m12) - (_m2 * _m7 * _m12) - (_m3 * _m4 * _m14) + (_m0 * _m7 * _m14) + (_m2 * _m4 * _m15) - (_m0 * _m6 * _m15),
						 (_m2 * _m7 * _m8) - (_m3 * _m6 * _m8) + (_m3 * _m4 * _m10) - (_m0 * _m7 * _m10) - (_m2 * _m4 * _m11) + (_m0 * _m6 * _m11)),
					
					Vec4((_m5 * _m11 * _m12) - (_m7 * _m9 * _m12) + (_m7 * _m8 * _m13) - (_m4 * _m11 * _m13) - (_m5 * _m8 * _m15) + (_m4 * _m9 * _m15),
						 (_m3 * _m9 * _m12) - (_m1 * _m11 * _m12) - (_m3 * _m8 * _m13) + (_m0 * _m11 * _m13) + (_m1 * _m8 * _m15) - (_m0 * _m9 * _m15),
						 (_m1 * _m7 * _m12) - (_m3 * _m5 * _m12) + (_m3 * _m4 * _m13) - (_m0 * _m7 * _m13) - (_m1 * _m4 * _m15) + (_m0 * _m5 * _m15),
						 (_m3 * _m5 * _m8) - (_m1 * _m7 * _m8) - (_m3 * _m4 * _m9) + (_m0 * _m7 * _m9) + (_m1 * _m4 * _m11) - (_m0 * _m5 * _m11)),
					
					Vec4((_m6 * _m9 * _m12) - (_m5 * _m10 * _m12) - (_m6 * _m8 * _m13) + (_m4 * _m10 * _m13) + (_m5 * _m8 * _m14) - (_m4 * _m9 * _m14),
						 (_m1 * _m10 * _m12) - (_m2 * _m9 * _m12) + (_m2 * _m8 * _m13) - (_m0 * _m10 * _m13) - (_m1 * _m8 * _m14) + (_m0 * _m9 * _m14),
						 (_m2 * _m5 * _m12) - (_m1 * _m6 * _m12) - (_m2 * _m4 * _m13) + (_m0 * _m6 * _m13) + (_m1 * _m4 * _m14) - (_m0 * _m5 * _m14),
						 (_m1 * _m6 * _m8) - (_m2 * _m5 * _m8) + (_m2 * _m4 * _m9) - (_m0 * _m6 * _m9) - (_m1 * _m4 * _m10) + (_m0 * _m5 * _m10)));
	}

	void Azul::Mat4::privSetQuat(const Quat& q)
	{
		this->_m0 = 1 - 2 * (q._qy * q._qy + q._qz * q._qz);
		this->_m1 = 2 * (q._qx * q._qy + q._qw * q._qz);
		this->_m2 = 2 * (q._qx * q._qz - q._qw * q._qy);
		this->_m3 = 0.0f;

		this->_m4 = 2 * (q._qx * q._qy - q._qw * q._qz);
		this->_m5 = 1 - 2 * (q._qx * q._qx + q._qz * q._qz);
		this->_m6 = 2 * (q._qy * q._qz + q._qw * q._qx);
		this->_m7 = 0.0f;

		this->_m8 = 2 * (q._qx * q._qz + q._qw * q._qy);
		this->_m9 = 2 * (q._qy * q._qz - q._qw * q._qx);
		this->_m10 = 1 - 2 * (q._qx * q._qx + q._qy * q._qy);
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetIdentity()
	{
		this->_m0 = 1.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = 1.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 1.0f;
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetZero()
	{
		this->_m0 = 0.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = 0.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 0.0f;
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 0.0f;
	}

	void Azul::Mat4::privSetTransXYZ(const float tx, const float ty, const float tz)
	{
		this->_m0 = 1.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = 1.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 1.0f;
		this->_m11 = 0.0f;

		this->_m12 = tx;
		this->_m13 = ty;
		this->_m14 = tz;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetScaleXYZ(const float sx, const float sy, const float sz)
	{
		this->_m0 = sx;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = sy;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = sz;
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetRotOrient(const Vec3& vect_dof, const Vec3& vect_vup)
	{
		//local to world
		Vec3 dof = vect_dof.getNorm();
		Vec3 vup = vect_vup.getNorm();

		Vec3 vup_dof = vup.cross(dof);
		Vec3 tmp = dof.cross(vup_dof);

		this->_m0 = vup_dof[x];
		this->_m1 = vup_dof[y];
		this->_m2 = vup_dof[z];
		this->_m3 = 0.0f;

		this->_m4 = tmp[x];
		this->_m5 = tmp[y];
		this->_m6 = tmp[z];
		this->_m7 = 0.0f;

		this->_m8 = dof[x];
		this->_m9 = dof[y];
		this->_m10 = dof[z];
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetRotInvOrient(const Vec3& vect_dof, const Vec3& vect_vup)
	{
		//world to local
		Vec3 dof = vect_dof.getNorm();
		Vec3 vup = vect_vup.getNorm();

		Vec3 vup_dof = vup.cross(dof);
		Vec3 tmp = dof.cross(vup_dof);

		this->_m0 = vup_dof[x];
		this->_m1 = tmp[x];
		this->_m2 = dof[x];
		this->_m3 = 0.0f;

		this->_m4 = vup_dof[y];
		this->_m5 = tmp[y];
		this->_m6 = dof[y];
		this->_m7 = 0.0f;

		this->_m8 = vup_dof[z];
		this->_m9 = tmp[z];
		this->_m10 = dof[z];
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetAxisAngle(const Vec3& vAxis, const float angle_radians)
	{
		//angle & axis
		const float angle_a = 0.5f * angle_radians;
		float cos_a = Trig::cos(angle_a);
		float sin_a = Trig::sin(angle_a);

		Vec3 qV = vAxis.getNorm();
		qV *= sin_a;

		Vec4 Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		//function is transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Azul::Mat4::privSetRotXYZ(const float a, const float b, const float c)
	{
		Mat4 rx = Mat4(Mat4::Rot1::X, a);
		Mat4 ry = Mat4(Mat4::Rot1::Y, b);
		Mat4 rz = Mat4(Mat4::Rot1::Z, c);

		Mat4 mOut = rx * ry * rz;

		this->_m0 = mOut._m0;
		this->_m1 = mOut._m1;
		this->_m2 = mOut._m2;
		this->_m3 = mOut._m3;

		this->_m4 = mOut._m4;
		this->_m5 = mOut._m5;
		this->_m6 = mOut._m6;
		this->_m7 = mOut._m7;

		this->_m8 = mOut._m8;
		this->_m9 = mOut._m9;
		this->_m10 = mOut._m10;
		this->_m11 = mOut._m11;

		this->_m12 = mOut._m12;
		this->_m13 = mOut._m13;
		this->_m14 = mOut._m14;
		this->_m15 = mOut._m15;
	}

	void Azul::Mat4::privSetRotX(const float angle)
	{
		this->_m0 = 1.0f;
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = Trig::cos(angle);
		this->_m6 = Trig::sin(angle);
		this->_m7 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = -(Trig::sin(angle));
		this->_m10 = Trig::cos(angle);
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetRotY(const float angle)
	{
		this->_m0 = Trig::cos(angle);
		this->_m1 = 0.0f;
		this->_m2 = -(Trig::sin(angle));
		this->_m3 = 0.0f;

		this->_m4 = 0.0f;
		this->_m5 = 1.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		this->_m8 = Trig::sin(angle);
		this->_m9 = 0.0f;
		this->_m10 = Trig::cos(angle);
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}

	void Azul::Mat4::privSetRotZ(const float angle)
	{
		this->_m0 = Trig::cos(angle);
		this->_m1 = Trig::sin(angle);
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;

		this->_m4 = -(Trig::sin(angle));
		this->_m5 = Trig::cos(angle);
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;

		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m10 = 1.0f;
		this->_m11 = 0.0f;

		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;
		this->_m15 = 1.0f;
	}


	//-----------------------------------------------------------------------------
	//	HINT FUNCTIONS
	//-----------------------------------------------------------------------------

	void Azul::Mat4::privSetGeneralHint()
	{
		Trace::out("\nSet General Hint:\n");

		// generalized mat4: clear last 3 bits
		uint32_t* p = (uint32_t*)&this->_m15;
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n", Hint::Generalize, this->_m15, *p);

		*p &= (uint32_t)(0xFFFFFFF7);
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n\n", Hint::Generalize, this->_m15, *p);
	}

	void Azul::Mat4::privSetScaleHint()
	{
		Trace::out("\nSet Scale Hint:\n");

		// scale mat4: set 3rd bit
		uint32_t* p = (uint32_t*)&this->_m15;
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n", Hint::Scale, this->_m15, *p);

		//*p |= (uint32_t)(Hint::Scale);
		*p |= (uint32_t)(0x3f800004);
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n\n", Hint::Scale, this->_m15, *p);
	}

	void Azul::Mat4::privSetRotHint()
	{
		Trace::out("\nSet Rot Hint:\n");

		// rot mat4: set 1st bit
		uint32_t* p = (uint32_t*)&this->_m15;
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n", Hint::Rot, this->_m15, *p);

		//*p |= (uint32_t)(Hint::Rot);
		*p |= (uint32_t)(0x3f800001);
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n\n", Hint::Rot, this->_m15, *p);
	}

	void Azul::Mat4::privSetTransHint()
	{
		Trace::out("\nSet Trans Hint: \n");

		// trans mat4: set 2nd bit 
		uint32_t* p = (uint32_t*)&this->_m15;
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n", Hint::Trans, this->_m15, *p);

		//*p |= (uint32_t)(Hint::Trans);
		*p |= (uint32_t)(0x3f800002);
		Trace::out("Hint:%d\t_m15:%f\t0x%x\n\n", Hint::Trans, this->_m15, *p);
	}

	void Azul::Mat4::privSetNewHint(Hint A, Hint B)
	{
		//Trace::out("\nSet New Hint:\n");
		Hint hint;

		// determine what kind of mats we have
		if (A == Hint::Generalize || B == Hint::Affine)
		{
			hint = Hint::Generalize;
		}
		else
		{
			hint = (Hint)((uint32_t)A | (uint32_t)B);
		}

		// set hint bits
		uint32_t* p = (uint32_t*)&this->_m15;
		//Trace::out("A:%d \t B:%d \t_m15:%f\t0x%x\n", A, B, this->_m15, *p);

		*p &= (uint32_t)0xFFFFFFF0;
		//Trace::out("\t\t\t_m15:%f\t0x%x\n",this->_m15, *p);

		*p |= (uint32_t)hint;
		//Trace::out("Hint:%d\t\t_m15:%f\t0x%x\n\n", hint, this->_m15, *p);
	}

	void Azul::Mat4::privSetCopyHint() const
	{
		Trace::out("\nSet Copy Hint: \n");

	}

	Azul::Mat4::Hint Azul::Mat4::privGetHint() const
	{
		Hint h = Hint::Generalize;
		uint32_t* p = (uint32_t*)&this->_m15;

		if ((*p & (uint32_t)(0x3f800001)) == 0x3f800001)
		{
			h = Hint::Rot;
		}
		else if ((*p & (uint32_t)(0x3f800002)) == 0x3f800002)
		{
			h = Hint::Trans;
		}
		else if ((*p & (uint32_t)(0x3f800004)) == 0x3f800004)
		{
			h = Hint::Scale;
		}
		else if ((*p & (uint32_t)(0x3f800003)) == 0x3f800003)
		{
			h = Hint::RotTrans;
		}

		return h;
	}
}