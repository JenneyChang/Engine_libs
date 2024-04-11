#ifndef ENGINE_MATH_Vect4D_H
#define ENGINE_MATH_Vect4D_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Enum.h"
#include "Constants.h"
#include "Vec4Proxy.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Mat4;
	class Mat3;
	class Vec3;
	class Quat;

	// -----------------------------------------------------------
	// 
	// Vec4 
	//   True 4 element vector... 
	//     its stored in a SIMD friendly struct for cache reasons
	//                         
	//   v4  = | x  y  z  w | 
	//     
	// -----------------------------------------------------------

	class Vec4 final : public Align16
	{
	public:

	    // Do your magic here
		// Big 4
		Vec4();
		~Vec4();
		Vec4(const Vec4 &inV);
		Vec4(Vec4 &&v) = default;

		Vec4 &operator=(const Vec4 &v);
		Vec4 &operator=(Vec4 &&v) = default;		

		// Constructors
		Vec4(const float in_x, const float in_y, const float in_z, const float in_w);

		// Forces User to explicitly do the cast or constructor call with explicit
		Vec4(const Vec3 &v, const float w = 1.0f);

		// Bracket
		float& operator[] (const enum x_enum) { return this->_vx; }
		float& operator[] (const enum y_enum) { return this->_vy; }
		float& operator[] (const enum z_enum) { return this->_vz; }
		float& operator[] (const enum w_enum) { return this->_vw; }

		float operator[] (const enum x_enum) const { return this->_vx; }
		float operator[] (const enum y_enum) const { return this->_vy; }
		float operator[] (const enum z_enum) const { return this->_vz; }
		float operator[] (const enum w_enum) const { return this->_vw; }

		// Accessors - Robin's suggestion
		void x(const float v) { this->_vx = v; }
		void y(const float v) { this->_vy = v; }
		void z(const float v) { this->_vz = v; }
		void w(const float v) { this->_vw = v; }

		float x()const { return this->_vx; }
		float y()const { return this->_vy; }
		float z()const { return this->_vz; }
		float w()const { return this->_vw; }

		// add operators
		Vec4 operator+ (void) const;
		Vec4 operator+ (const Vec4 &inV) const;
		void operator+= (const Vec4 &inV);

		// sub operators
		Vec4 operator- (void) const;
		Vec4 operator- (const Vec4& inV) const;
		void operator-= (const Vec4& inV);

		// scale operators
		Vec4 operator* (const float scale) const;
		friend Vec4 operator*(const float scale, const Vec4 &inV);
		void operator*= (const float scale);

		// Vec4 * Mat4
		Vec4 operator* (const Mat4 &m) const;
		Vec4 operator*= (const Mat4 &m);

		//(Vec3,1) * Mat4
        	friend Vec4 operator*(const Vec3 &v, const Mat4 &m);
        	friend Vec4 operator*= (const Vec3 &v, const Mat4 &m);

		// Vec4 functions
		Vec4 &norm(void);
		Vec4 getNorm(void) const;
		float dot(const Vec4 &vIn) const;
		//const Vec4Proxy len() const;
		float len() const;

		// set
		void set(const float inX, const float inY, const float inZ, const float inW);
		void set(const Vec4 &A);
		void set(const Vec3 &v, const float w = 1.0f);

		// comparison
		bool isEqual(const Vec4 &v, const float epsilon = MATH_TOLERANCE) const;
		bool isZero(const float epsilon = MATH_TOLERANCE) const;

		// for printing
		void Print(const char *pName) const;

	private:

		friend Mat4;
		friend Mat3;
		friend Vec3;
		friend Quat;

		union
		{
			/*                          */
			/*   v4  = | x  y  z  w |   */
			/*                          */

			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				float _vw;
			};
		};
	};

	Vec4 operator* (const Vec3 &v, const Mat4 &m);
	Vec4 operator*= (const Vec3 &v, const Mat4 &m);
}

#endif

//--- End of File ---
