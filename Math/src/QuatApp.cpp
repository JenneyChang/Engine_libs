#include "QuatApp.h"
#include "MathEngine.h"

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

namespace Azul
{
	void Azul::QuatApp::Slerp(Quat& result, const Quat& source, const Quat& target, const float slerpFactor)
	{
		Quat q_tar;

		const float EPSILON = 0.001f;	//math tolerance
		float tmp_cos = source.dot(target);	//cos_theta = q_src * q_tar

		if (tmp_cos >= 1.0f)
		{
			result = source;
		}
		else
		{
			if (tmp_cos < 0.0f)
			{
				//adjust negative
				tmp_cos = -tmp_cos;
				q_tar = -target;
			}
			else
			{
				q_tar = target;
			}

			//src & tar close-->lerp
			float tar_factor = slerpFactor;
			float src_factor = 1.0f - slerpFactor;

			if (tmp_cos < (1.0f - EPSILON))
			{
				//calc coefficients for slerp if quats too far apart for lerp
				const float omega = Trig::acos(tmp_cos);
				const float tmp_sin = 1.0f / Trig::sin(omega);

				src_factor = Trig::sin(src_factor * omega) * tmp_sin;
				tar_factor = Trig::sin(tar_factor * omega) * tmp_sin;
			}

			result = (source * src_factor) + (q_tar * tar_factor);
		}
	}

	void Azul::QuatApp::SlerpArray(Quat* result, const Quat* source, const Quat* target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; i++)
		{
			Slerp(result[i], source[i], target[i], slerpFactor);
		}
	}

}