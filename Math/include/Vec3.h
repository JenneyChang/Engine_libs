#ifndef ENGINE_MATH_VECT3_H
#define ENGINE_MATH_VECT3_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Enum.h"
#include "Constants.h"
#include "Vec3Proxy.h"

// This file assumes Framework.h is included in executable for Align16

namespace Azul
{
	// forward declare
	class Mat3;
	class Vec4;
	class Quat;

	// -----------------------------------------------------------
	// 
	// Vec3 
	//   True 3 element vector... 
	//     its stored in a SIMD friendly struct for cache reasons
	//     the "w" component is ignored and not set
	//                         
	//   v3  = | x  y  z  - | 
	//     
	// -----------------------------------------------------------

	class Vec3 final : public Align16
	{
	public:

		// Do your magic here

		// Big 4
		Vec3();
		~Vec3();
		Vec3(const Vec3 &inV);
		Vec3 &operator=(const Vec3 &v);
		
		// Constructors
		Vec3(const float in_x, const float in_y, const float in_z);

		// Forces User to explicitly do the cast or constructor call with explicit
		explicit Vec3(const Vec4 &v);
		Vec3 &operator=(const Vec4 &v);

		// Bracket
		float& operator[] (const enum x_enum) { return this->_vx; }
		float& operator[] (const enum y_enum) { return this->_vy; }
		float& operator[] (const enum z_enum) { return this->_vz; }

		float operator[] (const enum x_enum) const { return this->_vx; }
		float operator[] (const enum y_enum) const { return this->_vy; }
		float operator[] (const enum z_enum) const { return this->_vz; }

		// Accessors - Robin's suggestion
		void x(const float v) { this->_vx = v; }
		void y(const float v) { this->_vy = v; }
		void z(const float v) { this->_vz = v; }

		float x() const { return this->_vx; }
		float y() const { return this->_vy; }
		float z() const { return this->_vz; }

		// add operators
		Vec3 operator+ (void) const;
		Vec3 operator+ (const Vec3 &inV) const;
		void operator+= (const Vec3 &inV);

		// sub operators
		Vec3 operator- (void) const;
		Vec3 operator- (const Vec3 &inV) const;
		void operator-= (const Vec3 &inV);

		// scale operators
		Vec3 operator* (const float scale) const;
		friend Vec3 operator*(const float scale, const Vec3 &inV);
		void operator*= (const float scale);

		// Vec3 * Mat3
		Vec3 operator* (const Mat3 &m) const;
		Vec3 operator*= (const Mat3 &m);

		// Vect * Quat
		Vec3 operator* (const Quat &q) const;
		Vec3 operator*= (const Quat &q);

		// Vector functions
		Vec3 &norm(void);
		Vec3 getNorm(void) const;
		float dot(const Vec3 &vIn) const;
		const Vec3 cross(const Vec3 &vIn) const;
		//const Vec3Proxy len(void) const;
		float len(void) const;
		float getAngle(const Vec3 &vIn) const;

		// set
		void set(const float inX, const float inY, const float inZ);
		void set(const Vec3 &A);
		void set(const Vec4 &A);

		// comparison
		bool isEqual(const Vec3 &v, const float epsilon = MATH_TOLERANCE) const;
		bool isZero(const float epsilon = MATH_TOLERANCE) const;

		// for printing
		void Print(const char *pName) const;


	private:

		friend Mat3;
		friend Vec4;
		friend Quat;
		
		union
		{
			/*                          */
			/*   v3  = | x  y  z  - |   */
			/*                          */

			__m128	_mv;

			// anonymous struct
			struct
			{
				float _vx;
				float _vy;
				float _vz;
				
			};
		};
	};
}

#endif

//--- End of File ---
