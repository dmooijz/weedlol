#pragma once
#include "Vec3.hh"

namespace math
{
	struct quat_t
	{
		struct quat
		{
			vec3_t v;
			float w;

			void set_rotation(const vec3_t& vdir)
			{
				w = float(0.70710676908493042);
				v.x = float(vdir.z * 0.70710676908493042);
				v.y = float(0.0);
				v.z = float(0.0);
				float l = std::sqrt(vdir.x * vdir.x + vdir.y * vdir.y);
				if (l > float(0.00001))
				{
					//calculate LookAt quaternion
					vec3_t hv = vec3_t(vdir.x / l, vdir.y / l + 1.0f, l + 1.0f);
					float r = std::sqrt(hv.x * hv.x + hv.y * hv.y);
					float s = std::sqrt(hv.z * hv.z + vdir.z * vdir.z);
					//generate the half-angle sine&cosine
					float hacos0 = 0.0;
					float hasin0 = -1.0;
					if (r > float(0.00001)) { hacos0 = hv.y / r; hasin0 = -hv.x / r; }  //yaw
					float hacos1 = hv.z / s;
					float hasin1 = vdir.z / s;                        //pitch
					w = float(hacos0 * hacos1);
					v.x = float(hacos0 * hasin1);
					v.y = float(hasin0 * hasin1);
					v.z = float(hasin0 * hacos1);
				}

			}

			static quat create_rotation(const vec3_t& vdir)
			{
				quat q;
				q.set_rotation(vdir);
				return q;
			}

		} q;

		vec3_t t;
	};
}