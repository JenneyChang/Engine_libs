#include "Random.h"

namespace Azul
{
	thread_local std::mt19937 Random::randomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::distri;

	//-----------------------------------------------------------------------------
	//	CONSTRUCTION
	//----------------------------------------------------------------------------- 

	void Azul::Random::Init()
	{
		randomEngine.seed(std::random_device()());
	}


	//-----------------------------------------------------------------------------
	//	RAND UNSIGNED INT & INT
	//----------------------------------------------------------------------------- 

	uint32_t Azul::Random::UInt()
	{
		return distri(randomEngine);
	}

	uint32_t Azul::Random::UInt(uint32_t min, uint32_t max)
	{
		return min + (distri(randomEngine) % (max - min + 1));
	}


	//-----------------------------------------------------------------------------
	//	RAND FLOAT
	//----------------------------------------------------------------------------- 

	float Azul::Random::Float()
	{
		return (float)(distri(randomEngine)) / (float)std::numeric_limits<uint32_t>::max();
	}

	float Azul::Random::Float(float min, float max)
	{
		return Float() * (max - min) + min;
	}


	//-----------------------------------------------------------------------------
	//	RAND VEC3
	//----------------------------------------------------------------------------- 

	Vec3 Azul::Random::Vector3()
	{
		return Vec3(Float(), Float(), Float());
	}

	Vec3 Azul::Random::Vector3(float min, float max)
	{
		return Vec3(Float(min,max), Float(min,max), Float(min,max));
	}


	//-----------------------------------------------------------------------------
	//	OTHER
	//----------------------------------------------------------------------------- 

	Vec3 Azul::Random::InUnitSphere()
	{
		//normalized point in unit sphere
		return Random::Vector3(-1.0f, 1.0f).norm();
	}


}