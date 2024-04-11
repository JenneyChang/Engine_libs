#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

#include "Enum.h"
#include "Mat4.h"
#include "Debug.h"

//------------------------------------------------------------------------
// 
//  This class contains functions and data structure for a 4-dimensional
//  Quaternions.  The quaternions are internally stored interms of the
//  imaginary components (x,y,z) and the real components (real).
// 
//  In the Math library, quaternions can be thought of as "rotational"
//  matrices, everything that you can represent with rotational matrices
//  you can use with quaternions.  Such as quaternion concatenation,
//  inverses, transpose, normalize, multiplying with matrices, and with
//  vectors.
// 
//------------------------------------------------------------------------
namespace Azul
{
	class Quat final : public Align16
	{
	public:
		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot
		{
			AxisAngle,
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

	public:

		// Constructors
		explicit Quat(void);			// default Constructor 
		~Quat(void);				// default Destructor
		Quat(const Quat &qIn);			// copy constructor
		const Quat& operator=(const Quat& q);	// Assignment operator
		const Quat& operator=(const Mat4& m);	// Assignment operator

		// set real, vector	component
		Quat(const Vec3 &vect, const float real);

		// set every component	
		Quat(const float vx, const float vy, const float vz, const float real);

		// by matrix ( essentially Quat to Matrix conversion )
		explicit Quat(const Mat4 &mIn);

		//	Initialize to Identity Rotation
		explicit Quat(const Special  value);

		// Rotations by 1 angle:
		Quat(const Rot1 type, const float angle);

		// Rotations by 3 angle:
		Quat(const Rot3 type, const float angle_0, const float angle_1, const float angle_2);

		// Axis and Angle:
		Quat(const Rot type, const Vec3 &vAxis, const float angle_radians);

		// Orientation:
		Quat(const Orient, const Vec3 &dof, const Vec3 &up);

	 
		// Set
		// set by component, does not set the real component
		void setVec3(const Vec3& vect);

		// set every component	
		void set(const float vx, const float vy, const float vz, const float real);

		// set real, vector	
		void set(const Vec3& vect, const float real);

		// set by matrix ( essentially Quat to Matrix conversion )
		void set(const Mat4& m);
		void set(const Special type);
		
		// Axis and Angle:
		void set(const Rot type, const Vec3 &vAxis, const float angle_radians);
		void set(const Rot1 type, const float angle);
		void set(const Rot3 type, const float angle_0, const float angle_1, const float angle_2);

		// Orientation:
		void set(const Orient, const Vec3 &dof, const Vec3 &up);


		// Set values
		float& operator[](const x_enum value) { return this->_qx; }
		float& operator[](const y_enum value) { return this->_qy; }
		float& operator[](const z_enum value) { return this->_qz; }
		float& operator[](const w_enum value) { return this->_qw; }

		void qx(const float x) { this->_qx = x; }
		void qy(const float y) { this->_qy = y; }
		void qz(const float z) { this->_qz = z; }
		void real(const float w) { this->_qw = w; }

		// Get values
		float operator[](const x_enum value) const { return this->_qx; }
		float operator[](const y_enum value) const { return this->_qy; }
		float operator[](const z_enum value) const { return this->_qz; }
		float operator[](const w_enum value) const { return this->_qw; }

		float qx()const { return this->_qx; }
		float qy()const { return this->_qy; }
		float qz()const { return this->_qz; }
		float real()const { return this->_qw; }

		// Get Angle of rotation about the axis of rotation
		float getAngle(void) const;

		// Get Axis of rotation
		void getAxis(Vec3& vOut) const;

		// Get Vector component
		void getVec3(Vec3 &vOut) const;


		// General member functions
		float dot(const Quat &qin) const;	// dot product of two quaternions (4D)

		float mag(void) const;		// magnitude 
		float magSquared(void) const;	// magnitude Squared (Remember for Unit Quats, magSquared == 1.0f );
		float invMag(void) const;		// inverse magnitude

		Quat &conj(void);			// Conjugate Quat in place
		Quat getConj(void) const;	// Return conjuate Quat

		Quat &T(void);				// Transpose Quat in place
		Quat getT(void) const;		// Return Transpose Quat	

		Quat &inv(void);			// Inverse Quat in place
		Quat getInv(void) const;	// Return inverse Quat

		Quat &norm(void);			// Normalize Quat in place
		Quat getNorm(void) const;	// Return Normalize Quat


		// Linear Operator
		// Linear Operator vout = Quat * Vector * Quat(conjugate)
		// vOut = Quat * vIn * Quat.conj()
		void Lqvqc(const Vec3 &vIn, Vec3 &vOut) const;

		// Linear Operator  vOut = Quat(conjugate) * Vector * Quat
		// vOut = Quat.conj() * vIn * Quat		
		void Lqcvq(const Vec3 &vIn, Vec3 &vOut) const;

		
		// Test functions

		// Return true if the two Quats are equal within epsilon of each other
		bool isEqual(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the two Quats are equivalent within epsilon of each other
		bool isEquivalent(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the two Quats are equal but negative in direction within epsilon of each other
		bool isNegEqual(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the two Quats are equal but conjugate within epsilon of each other
		bool isConjugateEqual(const Quat &qin, const float epsilon = MATH_TOLERANCE) const;

		// Return true if the Quat represents Identity Rotation
		bool isIdentity(const float epsilon = MATH_TOLERANCE) const;

		// Return true if the Quat is normalized
		bool isNormalized(const float epsilon = MATH_TOLERANCE) const;

		// Return true if the Quat is a ZERO quat
		bool isZero(const float epsilon = MATH_TOLERANCE) const;


		// Overload the + operator
		const Quat operator+(void) const;			// +Quat (unary op)
		const Quat operator+(const Quat &q) const;	// Quat + Quat 
		Quat operator+(const float a) const;		// Quat + Constant
		const Quat& operator+=(const Quat &q);		// Quat += Quat
		const Quat& operator+=(const float a);		// Quat += Constant
		friend Quat operator+(const float a, const Quat& q);	// Constant + Quat


		// Overload the - operator
		const Quat operator-(void) const;		// -Quat
		Quat operator-(const Quat &q) const;	// Quat - Quat 
		Quat operator-(const float a) const;	// Quat - Constant
		const Quat& operator-=(const Quat &q);	// Quat -= Quat
		const Quat& operator-=(const float a);	// Quat -= Constant
		friend Quat operator-(const float a, const Quat &q);	// Constant - Quat


		// Overload the * operator
		Quat operator*(const Quat &q) const;	// Quat * Quat
		Quat operator*(const float a) const;	// Quat * Constant
		Mat4 operator*(const Mat4& m) const;	// Quat * Matrix

		const Quat& operator*=(const Quat &q);	// Quat *= Quat
		const Quat& operator*=(const float a);	// Quat *= Constant
		const Quat& operator*=(const Mat4& m);	// Quat *= Matrix
		
		friend Quat operator*(const float a, const Quat &q);	// Constant * Quat

	
		// Overload the / operator
		Quat operator/(const Quat &q) const;	// Quat / Quat
		Quat operator/(const float a) const;	// Quat / Constant
		const Quat& operator/=(const Quat &q);	// Quat /= Quat
		const Quat& operator/=(const float a);	// Quat /= Constant
		friend Quat operator/(const float a, const Quat &q);	// Constant / Quat

		// For printing
		void Print(const char *pName) const;


	private:
		void privSetZero();
		void privSetIdentity();
		void privSetMatrix(const Mat4& m);
		
		void privSetRotX(const float a);
		void privSetRotY(const float a);
		void privSetRotZ(const float a);

		void privSetRotXYZ(const float a, const float b, const float c);
		void privSetRotAxisAngle(const Vec3 &axis, const float angle);


	private:
		friend Vec4;
		friend Mat4;

		// anonymous union
		union
		{
			__m128	_mq;

			// anonymous struct
			struct
			{
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};

			struct
			{
				Vec3  _qV3;
			};

			struct
			{
				Vec4 _qV4;
			};
		};

	};
}

#endif 

//--- End of File ---
