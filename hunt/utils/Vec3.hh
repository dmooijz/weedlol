#pragma once
#include <limits>
#include <cmath>

namespace math
{
	struct vec3_t
	{
		constexpr vec3_t(float x = 0.f, float y = 0.f, float z = 0.f) : x(x), y(y), z(z) {}
		constexpr vec3_t(const float* array_vector) : x(array_vector[0]), y(array_vector[1]), z(array_vector[2]) {}
		constexpr vec3_t(const vec3_t& base) : x(base.x), y(base.y), z(base.z) {}

		[[nodiscard]] bool is_valid() const
		{
			return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
		}

		constexpr void invalidate()
		{
			x = y = z = std::numeric_limits<float>::infinity();
		}

		bool operator==(const vec3_t& base) const
		{
			return is_equal(base);
		}

		bool operator!=(const vec3_t& base) const
		{
			return !is_equal(base);
		}

		vec3_t operator+(const vec3_t& add) const
		{
			return vec3_t(x + add.x, y + add.y, z + add.z);
		}

		vec3_t operator-(const vec3_t& sub) const
		{
			return vec3_t(x - sub.x, y - sub.y, z - sub.z);
		}

		vec3_t operator*(const vec3_t& mul) const
		{
			return vec3_t(x * mul.x, y * mul.y, z * mul.z);
		}

		vec3_t operator/(const vec3_t& div) const
		{
			return vec3_t(x / div.x, y / div.y, z / div.z);
		}

		vec3_t operator+(const float add) const
		{
			return vec3_t(x + add, y + add, z + add);
		}

		vec3_t operator-(const float sub) const
		{
			return vec3_t(x - sub, y - sub, z - sub);
		}

		vec3_t operator*(const float mul) const
		{
			return vec3_t(x * mul, y * mul, z * mul);
		}

		vec3_t operator/(const float div) const
		{
			return vec3_t(x / div, y / div, z / div);
		}

		vec3_t normalize()
		{
			const auto length = this->length();
			const auto radius = 1.0f / (length + std::numeric_limits<float>::epsilon());

			this->x *= radius;
			this->y *= radius;
			this->z *= radius;

			return *this;
		}

		[[nodiscard]] bool is_equal(const vec3_t& equal) const
		{
			return (std::fabsf(x - equal.x) < std::numeric_limits<float>::epsilon() &&
				std::fabsf(y - equal.y) < std::numeric_limits<float>::epsilon() &&
				std::fabsf(z - equal.z) < std::numeric_limits<float>::epsilon());
		}

		[[nodiscard]] bool is_zero() const
		{
			return (std::fpclassify(x) == FP_ZERO && std::fpclassify(y) == FP_ZERO && std::fpclassify(z) == FP_ZERO);
		}

		[[nodiscard]] float length() const
		{
			return std::sqrtf(x * x + y * y + z * z);
		}

		[[nodiscard]] float length_sqr() const
		{
			return dot_product(*this);
		}

		[[nodiscard]] float length_2d() const
		{
			return std::sqrtf(x * x + y * y);
		}

		[[nodiscard]] float length_2d_sqr() const
		{
			return x * x + y * y;
		}

		[[nodiscard]] float dist_to(const vec3_t& end) const
		{
			return (*this - end).length();
		}

		[[nodiscard]] float dist_to_sqr(const vec3_t& end) const
		{
			return (*this - end).length_sqr();
		}

		[[nodiscard]] constexpr float dot_product(const vec3_t& dot) const
		{
			return x * dot.x + y * dot.y + z * dot.z;
		}

		[[nodiscard]] constexpr vec3_t cross_product(const vec3_t& cross) const
		{
			return vec3_t(y * cross.z - z * cross.y, z * cross.x - x * cross.z, x * cross.y - y * cross.x);
		}

		float x, y, z;
	};
}