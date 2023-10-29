#pragma once
#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include "Vec3.h"

namespace Azul
{
	//Utility: Generate Randomized numbers
	class Random
	{
	public:
		static void Init();

		static uint32_t UInt();
		static uint32_t UInt(uint32_t min, uint32_t max);

		/*static int32_t Int();
		static int32_t Int(int32_t min, int32_t max);*/

		static float Float();
		static float Float(float min, float max);

		static Vec3 Vector3();
		static Vec3 Vector3(float min, float max);

		//TODO: don't know if I want this to be here...
		static Vec3 InUnitSphere();


	private:
		//static std::mt19937 randomEngine;

		//if using MT...each core has its own state
		static thread_local std::mt19937 randomEngine;	
		static std::uniform_int_distribution<std::mt19937::result_type> distri;

	};
}
#endif // !RANDOM_H
