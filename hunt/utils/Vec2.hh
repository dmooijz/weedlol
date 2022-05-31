#pragma once

class c_vec {
public:
	int x, y;

	inline c_vec() {
		this->x = 0;
		this->y = 0;
	}

	inline c_vec(int x, int y) {
		this->x = x;
		this->y = y;
	}

	inline c_vec& operator=(const c_vec& vOther)
	{
		x = vOther.x;
		y = vOther.y;
		return *this;
	}

	inline int& operator[](int i)
	{
		return ((int*)this)[i];
	}

	inline int operator[](int i) const
	{
		return ((int*)this)[i];
	}

	inline bool operator==(const c_vec& src) const
	{
		return (src.x == x) && (src.y == y);
	}

	inline bool operator!=(const c_vec& src) const
	{
		return (src.x != x) || (src.y != y);
	}

	inline c_vec& operator+=(const c_vec& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	inline c_vec& operator-=(const c_vec& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	inline c_vec& operator*=(int fl)
	{
		x *= fl;
		y *= fl;
		return *this;
	}

	inline c_vec& operator*=(const c_vec& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	inline c_vec& operator+=(int fl)
	{
		x += fl;
		y += fl;
		return *this;
	}
	//===============================================
	inline c_vec& operator-=(int fl)
	{
		x -= fl;
		y -= fl;
		return *this;
	}
	//===============================================
	inline c_vec& operator/=(int fl)
	{
		const int oofl = 1 / fl;
		x *= oofl;
		y *= oofl;
		return *this;
	}

	inline c_vec& operator/=(const c_vec& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	inline c_vec operator+(const c_vec& v) const
	{
		c_vec res;
		res.x = x + v.x;
		res.y = y + v.y;
		return res;
	}


	inline c_vec operator-(const c_vec& v) const
	{
		c_vec res;
		res.x = x - v.x;
		res.y = y - v.y;
		return res;
	}

	inline c_vec operator*(int fl) const
	{
		c_vec res;
		res.x = x * fl;
		res.y = y * fl;
		return res;
	}

	inline c_vec operator*(const c_vec& v) const
	{
		c_vec res;
		res.x = x * v.x;
		res.y = y * v.y;
		return res;
	}

	inline c_vec operator/(int fl) const
	{
		c_vec res;
		res.x = x / fl;
		res.y = y / fl;
		return res;
	}

	inline c_vec operator/(const c_vec& v) const
	{
		c_vec res;
		res.x = x / v.x;
		res.y = y / v.y;
		return res;
	}
};