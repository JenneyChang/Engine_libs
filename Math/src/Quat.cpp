#include "Quat.h"
#include "MathEngine.h"

namespace Azul
{
	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//-----------------------------------------------------------------------------

	Azul::Quat::Quat(void)
		: _qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
	{ }

	Azul::Quat::~Quat(void)
	{ }

	Azul::Quat::Quat(const Quat& qIn)
		: _qx(qIn._qx), _qy(qIn._qy), _qz(qIn._qz), _qw(qIn._qw)
	{ }

	const Quat& Azul::Quat::operator=(const Quat& q)
	{
		if (this != &q)
		{
			this->_qx = q._qx;
			this->_qy = q._qy;
			this->_qz = q._qz;
			this->_qw = q._qw;
		}

		return *this;
	}

	const Quat& Azul::Quat::operator=(const Mat4& m)
	{
		//convert mat to quat
		Quat tmp;
		tmp.privSetMatrix(m);

		if (this != &tmp)
		{
			this->_qx = tmp._qx;
			this->_qy = tmp._qy;
			this->_qz = tmp._qz;
			this->_qw = tmp._qw;
		}

		return *this;
	}

	Azul::Quat::Quat(const Vec3& vect, const float real)
		: _qx(vect._vx), _qy(vect._vy), _qz(vect._vz), _qw(real)
	{ }

	Azul::Quat::Quat(const float vx, const float vy, const float vz, const float real)
		: _qx(vx), _qy(vy), _qz(vz), _qw(real)
	{ }

	Azul::Quat::Quat(const Mat4& mIn)
	{
		this->privSetMatrix(mIn);
	}

	Azul::Quat::Quat(const Special value)
	{
		switch (value)
		{
		case Quat::Special::Identity:
			this->privSetIdentity();
			break;

		case Quat::Special::Zero:
			this->privSetZero();
			break;
		}
	}

	Azul::Quat::Quat(const Rot type, const Vec3& vAxis, const float angle_radians)
	{
		if (type == Rot::AxisAngle)
		{
			this->privSetRotAxisAngle(vAxis, angle_radians);
		}
	}

	Azul::Quat::Quat(const Rot1 type, const float angle)
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
	}

	Azul::Quat::Quat(const Rot3 type, const float angle_0, const float angle_1, const float angle_2)
	{
		if (type == Rot3::XYZ)
		{
			this->privSetRotXYZ(angle_0, angle_1, angle_2);
		}
	}

	Azul::Quat::Quat(const Orient o, const Vec3& dof, const Vec3& up)
	{
		Mat4 m;
		switch (o)
		{
		case Orient::LocalToWorld:
			m = Mat4(Mat4::Orient::LocalToWorld, dof, up);
			this->privSetMatrix(m);
			break;

		case Orient::WorldToLocal:
			m = Mat4(Mat4::Orient::WorldToLocal, dof, up);
			this->privSetMatrix(m);
			break;
		}
	}


	//-----------------------------------------------------------------------------
	//	ACCESSORS 
	//-----------------------------------------------------------------------------

	void Azul::Quat::setVec3(const Vec3& vect)
	{
		this->_qx = vect._vx;
		this->_qy = vect._vy;
		this->_qz = vect._vz;
		this->_qw = 0.0f;
	}

	void Azul::Quat::set(const float vx, const float vy, const float vz, const float real)
	{
		this->_qx = vx;
		this->_qy = vy;
		this->_qz = vz;
		this->_qw = real;
	}

	void Azul::Quat::set(const Vec3& vect, const float real)
	{
		this->_qx = vect._vx;
		this->_qy = vect._vy;
		this->_qz = vect._vz;
		this->_qw = real;
	}

	void Azul::Quat::set(const Special type)
	{
		switch (type)
		{
		case Quat::Special::Identity:
			this->privSetIdentity();
			break;

		case Quat::Special::Zero:
			this->privSetZero();
			break;
		}
	}

	void Azul::Quat::set(const Mat4& m)
	{
		this->privSetMatrix(m);
	}

	void Azul::Quat::set(const Rot type, const Vec3& vAxis, const float angle_radians)
	{
		if (type == Rot::AxisAngle)
		{
			this->privSetRotAxisAngle(vAxis, angle_radians);
		}
	}

	void Azul::Quat::set(const Rot1 type, const float angle)
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
	}

	void Azul::Quat::set(const Rot3 type, const float angle_0, const float angle_1, const float angle_2)
	{
		if (type == Rot3::XYZ)
		{
			this->privSetRotXYZ(angle_0, angle_1, angle_2);
		}
	}

	void Azul::Quat::set(const Orient o, const Vec3& dof, const Vec3& up)
	{
		Mat4 m;
		switch (o)
		{
		case Orient::LocalToWorld:
			m = Mat4(Mat4::Orient::LocalToWorld, dof, up);
			this->privSetMatrix(m);
			break;

		case Orient::WorldToLocal:
			m = Mat4(Mat4::Orient::WorldToLocal, dof, up);
			this->privSetMatrix(m);
			break;
		}
	}

	/*const*/ float Azul::Quat::getAngle(void) const
	{
		return (2.0f * Trig::acos(_qw));
	}

	void Azul::Quat::getAxis(Vec3& vOut) const
	{
		vOut._vx = _qx;
		vOut._vy = _qy;
		vOut._vz = _qz;

		vOut.norm();
	}

	void Azul::Quat::getVec3(Vec3& vOut) const
	{
		vOut._vx = _qx;
		vOut._vy = _qy;
		vOut._vz = _qz;
	}



	//-----------------------------------------------------------------------------
	//	OPERATORS: ADD
	//----------------------------------------------------------------------------- 

	const Quat Azul::Quat::operator+(void) const
	{
		return Quat(+_qx, +_qy, +_qz, +_qw);
	}

	const Quat Azul::Quat::operator+(const Quat& q) const
	{
		return Quat(_qx + q._qx, _qy + q._qy, _qz + q._qz, _qw + q._qw);
	}

	Quat Azul::Quat::operator+(const float a) const
	{
		return Quat(_qx + a, _qy + a, _qz + a, _qw + a);
	}

	Quat Azul::operator+(const float a, const Quat& q)
	{
		return Quat(a + q._qx, a + q._qy, a + q._qz, a + q._qw);
	}

	const Quat& Azul::Quat::operator+=(const Quat& q)
	{
		_qx += q._qx;
		_qy += q._qy;
		_qz += q._qz;
		_qw += q._qw;

		return *this;
	}

	const Quat& Azul::Quat::operator+=(const float a)
	{
		_qx += a;
		_qy += a;
		_qz += a;
		_qw += a;

		return *this;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: SUB
	//----------------------------------------------------------------------------- 

	const Quat Azul::Quat::operator-(void) const
	{
		return Quat(-_qx, -_qy, -_qz, -_qw);
	}

	Quat Azul::Quat::operator-(const Quat& q) const
	{
		return Quat(_qx - q._qx, _qy - q._qy, _qz - q._qz, _qw - q._qw);
	}

	Quat Azul::Quat::operator-(const float a) const
	{
		return Quat(_qx - a, _qy - a, _qz - a, _qw - a);
	}

	Quat Azul::operator-(const float a, const Quat& q)
	{
		return Quat(a - q._qx, a - q._qy, a - q._qz, a - q._qw);
	}

	const Quat& Azul::Quat::operator-=(const Quat& q)
	{
		_qx -= q._qx;
		_qy -= q._qy;
		_qz -= q._qz;
		_qw -= q._qw;

		return *this;
	}

	const Quat& Azul::Quat::operator-=(const float a)
	{
		_qx -= a;
		_qy -= a;
		_qz -= a;
		_qw -= a;

		return *this;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: MULTIPLY
	//----------------------------------------------------------------------------- 

	Quat Azul::Quat::operator*(const Quat& q) const
	{
		float w = (_qw * q._qw) - ((_qx * q._qx) + (_qy * q._qy) + (_qz * q._qz));

		Vec3 q1(_qx, _qy, _qz);
		Vec3 q2(q._qx, q._qy, q._qz);
		Vec3 result(q2.cross(q1) + (_qw * q2) + (q._qw * q1));

		return Quat(result[x], result[y], result[z], w);
	}

	Quat Azul::Quat::operator*(const float a) const
	{
		return Quat(_qx * a, _qy * a, _qz * a, _qw * a);
	}

	Quat Azul::operator*(const float a, const Quat& q)
	{
		return Quat(q._qx * a, q._qy * a, q._qz * a, q._qw * a);
	}

	Mat4 Azul::Quat::operator*(const Mat4& m) const
	{
		//convert quat to mat4
		Mat4 mOut(*this);

		return mOut * m;
	}

	const Quat& Azul::Quat::operator*=(const Quat& q)
	{
		float w = (_qw * q._qw) - ((_qx * q._qx) + (_qy * q._qy) + (_qz * q._qz));

		Vec3 q1(_qx, _qy, _qz);
		Vec3 q2(q._qx, q._qy, q._qz);
		Vec3 result(q2.cross(q1) + (_qw * q2) + (q._qw * q1));

		this->_qx = result[x];
		this->_qy = result[y];
		this->_qz = result[z];
		this->_qw = w;

		return *this;
	}

	const Quat& Azul::Quat::operator*=(const float a)
	{
		_qx *= a;
		_qy *= a;
		_qz *= a;
		_qw *= a;

		return *this;
	}

	const Quat& Azul::Quat::operator*=(const Mat4& m)
	{
		Quat q(m);
		return *this *= q;
	}


	//-----------------------------------------------------------------------------
	//	OPERATORS: QUOTIENT
	//----------------------------------------------------------------------------- 

	Quat Azul::Quat::operator/(const Quat& q) const
	{
		return Quat((_qx / q._qx), (_qy / q._qy), (_qz / q._qz), (_qw / q._qw));
	}

	Quat Azul::Quat::operator/(const float a) const
	{
		return Quat((_qx / a), (_qy / a), (_qz / a), (_qw / a));
	}

	Quat Azul::operator/(const float a, const Quat& q)
	{
		return Quat((a / q._qx), (a / q._qy), (a / q._qz), (a / q._qw));
	}

	const Quat& Azul::Quat::operator/=(const Quat& q)
	{
		_qx /= q._qx;
		_qy /= q._qy;
		_qz /= q._qz;
		_qw /= q._qw;

		return *this;
	}

	const Quat& Azul::Quat::operator/=(const float a)
	{
		_qx /= a;
		_qy /= a;
		_qz /= a;
		_qw /= a;

		return *this;
	}


	//-----------------------------------------------------------------------------
	//	QUAT FUNCTIONS 
	//-----------------------------------------------------------------------------

	float Azul::Quat::dot(const Quat& qin) const
	{
		return ((_qx * qin._qx) + (_qy * qin._qy) + (_qz * qin._qz) + (_qw * qin._qw));
	}

	float Quat::mag(void) const
	{
		return Trig::sqrt((_qx * _qx) + (_qy * _qy) + (_qz * _qz) + (_qw * _qw));
	}

	float Azul::Quat::magSquared(void) const
	{
		float mag = this->mag();
		return (mag * mag);
	}

	float Azul::Quat::invMag(void) const
	{
		return (1.0f / this->mag());
	}

	Quat& Azul::Quat::conj(void)
	{
		this->_qx = -_qx;
		this->_qy = -_qy;
		this->_qz = -_qz;

		return *this;
	}

	Quat Azul::Quat::getConj(void) const
	{
		return Quat(-_qx, -_qy, -_qz, _qw);
	}

	Quat& Azul::Quat::T(void)
	{
		this->_qx = -_qx;
		this->_qy = -_qy;
		this->_qz = -_qz;

		return *this;
	}

	Quat Azul::Quat::getT(void) const
	{
		return Quat(-_qx, -_qy, -_qz, _qw);
	}

	Quat& Azul::Quat::inv(void)
	{
		Quat m(this->getConj() / this->magSquared());

		this->_qx = m._qx;
		this->_qy = m._qy;
		this->_qz = m._qz;
		this->_qw = m._qw;

		return *this;
	}

	Quat Azul::Quat::getInv(void) const
	{
		return Quat(this->getConj() / this->magSquared());
	}

	Quat& Azul::Quat::norm(void)
	{
		float mag = this->mag();

		_qx /= mag;
		_qy /= mag;
		_qz /= mag;
		_qw /= mag;

		return *this;
	}

	Quat Azul::Quat::getNorm(void) const
	{
		float mag = this->mag();
		Quat q(*this);

		return Quat(q._qx /= mag, q._qy /= mag, q._qz /= mag, q._qw /= mag);
	}

	void Azul::Quat::Lqvqc(const Vec3& vIn, Vec3& vOut) const
	{
		//vout = Quat * Vector * Quat(conjugate)
		Quat qIn(vIn._vx, vIn._vy, vIn._vz, 0.0f);
		Quat result = (*this * qIn * this->getConj());

		vOut._vx = result._qx;
		vOut._vy = result._qy;
		vOut._vz = result._qz;
	}

	void Azul::Quat::Lqcvq(const Vec3& vIn, Vec3& vOut) const
	{
		//vOut = Quat(conjugate) * Vector * Quat
		Quat qIn(vIn._vx, vIn._vy, vIn._vz, 0.0f);
		Quat result = (this->getConj() * qIn * *this);

		vOut._vx = result._qx;
		vOut._vy = result._qy;
		vOut._vz = result._qz;
	}

	bool Azul::Quat::isEqual(const Quat& qin, const float epsilon) const
	{
		return (Util::isEqual(_qx, qin._qx, epsilon) && 
				Util::isEqual(_qy, qin._qy, epsilon) &&
				Util::isEqual(_qz, qin._qz, epsilon) && 
				Util::isEqual(_qw, qin._qw, epsilon));
	}

	bool Azul::Quat::isEquivalent(const Quat& qin, const float epsilon) const
	{
		//if qin is negative
		if (qin._qx < 0 && qin._qy < 0 && qin._qz < 0)
		{
			return isNegEqual(qin, epsilon);
		}
		//else qin is positive
		else
		{
			return isEqual(qin, epsilon);
		}
	}

	bool Azul::Quat::isNegEqual(const Quat& qin, const float epsilon) const
	{
		return (Util::isEqual(_qx, fabsf(qin._qx), epsilon) &&
				Util::isEqual(_qy, fabsf(qin._qy), epsilon) &&
				Util::isEqual(_qz, fabsf(qin._qz), epsilon) &&
				Util::isEqual(_qw, fabsf(qin._qw), epsilon));
	}
	
	 bool Azul::Quat::isConjugateEqual(const Quat& qin, const float epsilon) const
	{
		return (Util::isEqual(_qx, fabsf(qin._qx), epsilon) &&
				Util::isEqual(_qy, fabsf(qin._qy), epsilon) &&
				Util::isEqual(_qz, fabsf(qin._qz), epsilon) &&
				Util::isEqual(_qw, qin._qw, epsilon));
	}

	bool Azul::Quat::isIdentity(const float epsilon) const
	{
		return (Util::isZero(_qx, epsilon) &&
				Util::isZero(_qy, epsilon) &&
				Util::isZero(_qz, epsilon) &&
				Util::isOne(_qw, epsilon));
	}

	bool Azul::Quat::isNormalized(const float epsilon) const
	{
		return (Util::isOne(this->mag(), epsilon));
	}

	bool Azul::Quat::isZero(const float epsilon) const
	{
		return (Util::isZero(_qx, epsilon) &&
				Util::isZero(_qy, epsilon) &&
				Util::isZero(_qz, epsilon) &&
				Util::isZero(_qw, epsilon));
	}

	void Azul::Quat::Print(const char* pName) const
	{
		Debug::Print(pName, *this);
	}


	//-----------------------------------------------------------------------------
	//	PRIVATE FUNCTIONS
	//-----------------------------------------------------------------------------

	void Azul::Quat::privSetZero()
	{
		this->_qx = 0.0f;
		this->_qy = 0.0f;
		this->_qz = 0.0f;
		this->_qw = 0.0f;
	}

	void Azul::Quat::privSetIdentity()
	{
		this->_qx = 0.0f;
		this->_qy = 0.0f;
		this->_qz = 0.0f;
		this->_qw = 1.0f;
	}

	void Azul::Quat::privSetMatrix(const Mat4& mIn)
	{
		float tr = mIn[m0] + mIn[m5] + mIn[m10];
		float S = 0.0f;

		if (tr > 0.0f)
		{
			S = 2 * Trig::sqrt(tr + 1.0f);

			this->_qw = 0.25f * S;
			this->_qx = -(mIn[m9] - mIn[m6]) / S;
			this->_qy = -(mIn[m2] - mIn[m8]) / S;
			this->_qz = -(mIn[m4] - mIn[m1]) / S;
		}
		else if ((mIn[m0] > mIn[m5]) && (mIn[m0] > mIn[m10]))
		{
			S = 2 * Trig::sqrt(1.0f + mIn[m0] - mIn[m5] - mIn[m10]);

			this->_qw = -(mIn[m9] - mIn[m6]) / S;
			this->_qx = 0.25f * S;
			this->_qy = (mIn[m1] + mIn[m4]) / S;
			this->_qz = (mIn[m2] + mIn[m8]) / S;
		}
		else if (mIn[m5] > mIn[m10])
		{
			S = 2 * Trig::sqrt(1.0f + mIn[m5] - mIn[m0] - mIn[m10]);

			this->_qw = -(mIn[m2] - mIn[m8]) / S;
			this->_qx = (mIn[m1] + mIn[m4]) / S;
			this->_qy = 0.25f * S;
			this->_qz = (mIn[m6] + mIn[m9]) / S;
		}
		else
		{
			S = 2 * Trig::sqrt(1.0f + mIn[m10] - mIn[m0] - mIn[m5]);

			this->_qw = -(mIn[m4] - mIn[m1]) / S;
			this->_qx = (mIn[m2] + mIn[m8]) / S;
			this->_qy = (mIn[m6] + mIn[m9]) / S;
			this->_qz = 0.25f * S;
		}
	}

	void Azul::Quat::privSetRotX(const float a)
	{
		Mat4 m(Mat4::Rot1::X, a);
		this->privSetMatrix(m);
	}

	void Azul::Quat::privSetRotY(const float a)
	{
		Mat4 m(Mat4::Rot1::Y, a);
		this->privSetMatrix(m);
	}

	void Azul::Quat::privSetRotZ(const float a)
	{
		Mat4 m(Mat4::Rot1::Z, a);
		this->privSetMatrix(m);
	}

	void Azul::Quat::privSetRotAxisAngle(const Vec3& axis, const float angle)
	{
		Vec3 temp = axis.getNorm() * (Trig::sin(angle * 0.5f));

		this->_qx = temp[x];
		this->_qy = temp[y];
		this->_qz = temp[z];
		this->_qw = Trig::cos(angle * 0.5f);	
	}

	void Azul::Quat::privSetRotXYZ(const float a, const float b, const float c)
	{
		Mat4 m(Mat4::Rot3::XYZ, a, b, c);
		this->privSetMatrix(m);
	}

}
