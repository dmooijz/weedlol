#pragma once
#include "Vec3.hh"

namespace math
{
	struct matrix3x4_t
	{
		float* operator[](int i)
		{
			return m_matrix[i];
		}

		const float* operator[](int i) const
		{
			return m_matrix[i];
		}

		inline vec3_t operator*(const vec3_t& p) const
		{
			vec3_t tp;
			tp.x = m_matrix[0][0] * p.x + m_matrix[0][1] * p.y + m_matrix[0][2] * p.z + m_matrix[0][3];
			tp.y = m_matrix[1][0] * p.x + m_matrix[1][1] * p.y + m_matrix[1][2] * p.z + m_matrix[1][3];
			tp.z = m_matrix[2][0] * p.x + m_matrix[2][1] * p.y + m_matrix[2][2] * p.z + m_matrix[2][3];
			return tp;
		}

		float m_matrix[3][4];
	};
}