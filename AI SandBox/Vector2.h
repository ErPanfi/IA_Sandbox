#pragma once
#include <math.h>

/*
	Bidimensional Vector and some util methods.
*/

class Vector2
{
public:
	static const Vector2 ZERO;
	static const Vector2 X_VERSOR;
	static const Vector2 Y_VERSOR;

	Vector2() 
	{
		x = 0.f; y = 0.f;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float		x;
	float		y;

	inline Vector2&	operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		
		return *this;
	}

	inline Vector2 operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	inline Vector2 operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	inline Vector2 operator*=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	inline Vector2 operator/=(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	bool operator==(const Vector2& other)const
	{
		return ( x == other.x && y == other.y );
	}

	bool operator!=(const Vector2& other)const
	{
		return (x != other.x) || (y != other.y);
	}

	bool isZero()const{ return (x==0.f && y==0.f);}

	void Normalize()
	{
		float length = Length();
		if(length>0){
			x /= length;
			y /= length;
		}
	}
	Vector2 NormalizeCopy()
	{
		Vector2 temp(x, y);
		temp.Normalize();
		return temp;
	}

	float		DotProduct(const Vector2& other) const
	{
		return x * other.x + y * other.y;
	}
	
	float		Length() const
	{
		return sqrt(SquaredLength());
	}

	float		SquaredLength() const
	{
		return x * x + y * y;
	}

	void		Set(float x, float y) { this->x = x; this->y = y; }
	void		Zero(){ Set(0.f, 0.f); }

	inline void Truncate(float max)
	{
		if (this->Length() > max)
		{
			this->Normalize();

			*this *= max;
		} 
	}

	inline float Distance(const Vector2& v2)const
	{
		float ySeparation = v2.y - y;
		float xSeparation = v2.x - x;

		return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
	}

};

inline Vector2 operator*(const Vector2 &lhs, float rhs);
inline Vector2 operator*(float lhs, const Vector2 &rhs);
inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
inline Vector2 operator/(const Vector2 &lhs, float val);

inline Vector2 operator*(const Vector2 &lhs, float rhs)
{
	Vector2 result(lhs);
	result *= rhs;
	return result;
}

inline Vector2 operator*(float lhs, const Vector2 &rhs)
{
	Vector2 result(rhs);
	result *= lhs;
	return result;
}

inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
{
	Vector2 result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;

	return result;
}

inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
{
	Vector2 result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;

	return result;
}

inline Vector2 operator/(const Vector2 &lhs, float val)
{
	Vector2 result(lhs);
	result.x /= val;
	result.y /= val;

	return result;
}