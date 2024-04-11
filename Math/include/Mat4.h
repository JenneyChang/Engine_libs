#ifndef ENGINE_MATH_MATRIX_4x4_H
#define ENGINE_MATH_MATRIX_4x4_H

#include "Enum.h"
#include "Vec4.h"
#include "Vec3.h"
#include "Debug.h"

namespace Azul
{
	class Quat;

	class Mat4 final : public Align16
	{
	public:
		enum class Special
		{
			Zero,
			Identity
		};

		enum class Rot1
		{
			X,
			Y,
			Z
		};

		enum class Trans
		{
			XYZ
		};

		enum class Scale
		{
			XYZ
		};

		enum class Rot
		{
			AxisAngle
		};

		enum class Orient
		{
			LocalToWorld,
			WorldToLocal
		};

		enum class Row
		{
			i0,
			i1,
			i2,
			i3
		};

		enum class Rot3
		{
			XYZ
			// future combos... here
		};

		// TODO: Hint system
		enum class Hint : uint32_t
		{
			Generalize = 0x0,   // generalize 4x4 inverse  (no flags)
			Rot        = 0x1,   // matrix inverse is M.T()
			Trans      = 0x2,   // matrix inverse is M(-trans)
			RotTrans   = 0x3,   // rot and trans  A_inv is A.T() 
			Scale      = 0x4,   // matrix invers is M(1/scale)
			RotScale   = 0x5,   // Rot and Scale no translate
			TransScale = 0x6,   // Trans and Scale no Translate
			Affine     = 0x7    // generalize Affine
		};

		void privSetGeneralHint();
		void privSetScaleHint();
		void privSetRotHint();
		void privSetTransHint();
		void privSetNewHint(Hint A, Hint B);
		void privSetCopyHint() const;
		Hint privGetHint() const;


	public:
		// Big 4
		Mat4();
		~Mat4();
		Mat4(const Mat4& tM);
		Mat4& operator=(const Mat4 &A);
		
		// Constructors
		Mat4(const Vec4 &tV0, const Vec4 &tV1, const Vec4 &tV2, const Vec4 &tV3);

		Mat4(const Trans type, const float tx, const float ty, const float tz);
		Mat4(const Trans type, const Vec3 &vTrans);

		Mat4(const Scale, const float sx, const float sy, const float sz);
		Mat4(const Scale, const Vec3 &vScale);

		Mat4(const Rot, const Vec3 &vAxis, const float angle_radians);
		Mat4(const Rot1 type, const float angle);
		Mat4(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);

		Mat4(const Orient type, const Vec3 &dof, const Vec3 &up);

		explicit Mat4(const Special type);
		explicit Mat4(const Quat &q);

		// Set 
		void set(const Mat4 &mIn);
		void set(const Row type, const Vec4& V);
		void set(const Vec4 &V0, const Vec4 &V1, const Vec4 &V2, const Vec4 &V3);
		
		void set(const Rot1 type, const float angle);
		void set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);

		void set(const Rot r, const Vec3 &vAxis, const float angle_radians);
		void set(const Orient o, const Vec3 &dof, const Vec3 &up);

		void set(const Trans type, const float tx, const float ty, const float tz);
		void set(const Trans type, const Vec3 &vTrans);

		void set(const Scale type, const float sx, const float sy, const float sz);
		void set(const Scale type, const Vec3 &vScale);

		void set(const Special type);
		void set(const Quat &q);

		// Get
		Vec4 get(const Row type) const;

		// bracket operators	
		float& operator[] (const enum m0_enum) { return this->_m0; }
		float& operator[] (const enum m1_enum) { return this->_m1; }
		float& operator[] (const enum m2_enum) { return this->_m2; }
		float& operator[] (const enum m3_enum) { return this->_m3; }
		float& operator[] (const enum m4_enum) { return this->_m4; }
		float& operator[] (const enum m5_enum) { return this->_m5; }
		float& operator[] (const enum m6_enum) { return this->_m6; }
		float& operator[] (const enum m7_enum) { return this->_m7; }
		float& operator[] (const enum m8_enum) { return this->_m8; }
		float& operator[] (const enum m9_enum) { return this->_m9; }
		float& operator[] (const enum m10_enum) { return this->_m10; }
		float& operator[] (const enum m11_enum) { return this->_m11; }
		float& operator[] (const enum m12_enum) { return this->_m12; }
		float& operator[] (const enum m13_enum) { return this->_m13; }
		float& operator[] (const enum m14_enum) { return this->_m14; }
		float& operator[] (const enum m15_enum) { return this->_m15; }

		float operator[] (const enum m0_enum) const { return this->_m0; }
		float operator[] (const enum m1_enum) const { return this->_m1; }
		float operator[] (const enum m2_enum) const { return this->_m2; }
		float operator[] (const enum m3_enum) const { return this->_m3; }
		float operator[] (const enum m4_enum) const { return this->_m4; }
		float operator[] (const enum m5_enum) const { return this->_m5; }
		float operator[] (const enum m6_enum) const { return this->_m6; }
		float operator[] (const enum m7_enum) const { return this->_m7; }
		float operator[] (const enum m8_enum) const { return this->_m8; }
		float operator[] (const enum m9_enum) const { return this->_m9; }
		float operator[] (const enum m10_enum) const { return this->_m10; }
		float operator[] (const enum m11_enum) const { return this->_m11; }
		float operator[] (const enum m12_enum) const { return this->_m12; }
		float operator[] (const enum m13_enum) const { return this->_m13; }
		float operator[] (const enum m14_enum) const { return this->_m14; }
		float operator[] (const enum m15_enum) const { return this->_m15; }

		// Accessor	
		void m0(const float v) { this->_m0 = v; }
		void m1(const float v) { this->_m1 = v; }
		void m2(const float v) { this->_m2 = v; }
		void m3(const float v) { this->_m3 = v; }
		void m4(const float v) { this->_m4 = v; }
		void m5(const float v) { this->_m5 = v; }
		void m6(const float v) { this->_m6 = v; }
		void m7(const float v) { this->_m7 = v; }
		void m8(const float v) { this->_m8 = v; }
		void m9(const float v) { this->_m9 = v; }
		void m10(const float v) { this->_m10 = v; }
		void m11(const float v) { this->_m11 = v; }
		void m12(const float v) { this->_m12 = v; }
		void m13(const float v) { this->_m13 = v; }
		void m14(const float v) { this->_m14 = v; }
		void m15(const float v) { this->_m15 = v; }

		float m0() const { return this->_m0; }
		float m1() const { return this->_m1; }
		float m2() const { return this->_m2; }
		float m3() const { return this->_m3; }
		float m4() const { return this->_m4; }
		float m5() const { return this->_m5; }
		float m6() const { return this->_m6; }
		float m7() const { return this->_m7; }
		float m8() const { return this->_m8; }
		float m9() const { return this->_m9; }
		float m10() const { return this->_m10; }
		float m11() const { return this->_m11; }
		float m12() const { return this->_m12; }
		float m13() const { return this->_m13; }
		float m14() const { return this->_m14; }
		float m15() const { return this->_m15; }

		// Determinant
		float det() const;

		// Transpose
		Mat4 &T(void);
		const Mat4 getT(void)const;

		// Inverse
		const Mat4 getInv(void) const;
		Mat4 &inv(void);


		// Comparison
		bool isEqual(const Mat4 &A, const float epsilon = MATH_TOLERANCE) const;
		bool isIdentity(const float epsilon = MATH_TOLERANCE) const;
		bool isRotation(const float epsilon = MATH_TOLERANCE) const;

		// Add operators
		Mat4 operator+ (void) const;
		Mat4 operator+ (const Mat4 &A) const;
		void operator+= (const Mat4 &A);

		// Sub operators
		Mat4 operator- (void) const;
		Mat4 operator- (const Mat4 &A) const;
		void operator-= (const Mat4 &A);

		// Scale operators
		Mat4 operator* (const float s) const;
		friend Mat4 operator*(const float scale, const Mat4 &A);
		void operator*= (const float scale);

		// Multiply
		Mat4 operator* (const Mat4 &A) const;
		void operator*= (const Mat4 &A);
		Mat4 operator* (const Quat &q) const;
		Mat4 operator*= (const Quat &q);

		// For printing
		void Print(const char *pName) const;


	private:
		const Mat4 privGetAdj(void) const;

		void privSetIdentity();
		void privSetZero();
		void privSetQuat(const Quat& q);
		void privSetTransXYZ(const float tx, const float ty, const float tz);
		void privSetScaleXYZ(const float sx, const float sy, const float sz);

		void privSetRotOrient(const Vec3 &vect_dof, const Vec3 &vect_vup);
		void privSetRotInvOrient(const Vec3 &vect_dof, const Vec3 &vect_vup);
		void privSetAxisAngle(const Vec3& vAxis, const float angle_radians);
		void privSetRotXYZ(const float a, const float b, const float c);
		void privSetRotX(const float angle);
		void privSetRotY(const float angle);
		void privSetRotZ(const float angle);


	private:

		friend Mat3;
		friend Vec3;
		friend Vec4;

		union
		{
			/*     | m0  m1  m2   m3  | */
			/* m = | m4  m5  m6   m7  | */
			/*     | m8  m9  m10  m11 | */
			/*     | m12 m13 m14  m15 | */

			struct
			{
				Vec4 _rows[4];
			};

			struct
			{
				Vec4 _v0;
				Vec4 _v1;
				Vec4 _v2;
				Vec4 _v3;
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};
	};
}

#endif

//--- End of File ---
