#pragma once
#include <math.h>

const float PI = 3.14159f;
struct Vector2
{
	float x;
	float y;
	Vector2()
		:x(0.f)
		,y(0.f)
	{}
	Vector2(float _x,float _y)
		:x(_x)
		, y(_y)
	{}
	Vector2(const Vector2& v)
		:x(v.x)
		, y(v.y)
	{}
	// sqrtf : 루트
	float Angle(const Vector2& v) const
	{
		float width = v.x - x;
		float height = v.y - y;
		float hypotenuse = sqrtf(width * width + height * height);	//빗변
		float angle = width / hypotenuse;
		angle = acosf(angle) / PI * 180.f;
		if (v.y < y)
		{
			angle = 360.f - angle;
		}
		return angle;
	}

	float Distance(const Vector2& v)	const
	{
		float width = x - v.x;
		float height = y - v.y;
		return sqrtf(width * width + height * height);
	}

	void operator = (const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}

	void operator = (float f)
	{
		x = f;
		y = f;
	}

	bool operator == (const Vector2& v)	const
	{
		return x == v.x && y == v.y;
	}

	template<typename T>
	bool operator == (T type)	const
	{
		if (x == (float)type && y == (float)type)
		{
			return true;
		}
		return false;
	}

	bool operator != (const Vector2& v)	const
	{
		return x != v.x || y != v.y;
	}

	template<typename T>
	bool operator != (T type)	const
	{
		if(x !=(float)type||y !=(float)type)
		{
			return true;
		}
		return false;
	}

	//비교하기가 애매하다 
	//bool operator > (const Vector2& v)	const
	//{
	//	return x > v.x && y > v.y;
	//}

	//template<typename T>
	//bool operator > (T type)	const
	//{
	//	if (x > (float)type && y > (float)type)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	//bool operator < (const Vector2& v)	const
	//{
	//	return x < v.x && y < v.y;
	//}

	//template<typename T>
	//bool operator > (T type)	const
	//{
	//	if (x > (float)type && y > (float)type)
	//	{
	//		return true;
	//	}
	//	return false;
	//}

	Vector2 operator + (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x + v.x;
		result.y = y + v.y;

		return result;
	}

	template<typename T>
	Vector2 operator + (T type)	const
	{
		Vector2	result;

		result.x = x + (float)type;
		result.y = y + (float)type;

		return result;
	}

	void operator += (const Vector2& v)
	{
		x += v.x;
		y += v.y;
	}

	template<typename T>
	void operator += (T type)
	{
		x += (float)type;
		y += (float)type;
	}

	Vector2 operator - (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x - v.x;
		result.y = y - v.y;

		return result;
	}

	template<typename T>
	Vector2 operator - (T type)	const
	{
		Vector2	result;

		result.x = x - (float)type;
		result.y = y - (float)type;

		return result;
	}

	void operator -= (const Vector2& v) 
	{
		x -= v.x;
		y -= v.y;
	}

	template<typename T>
	void operator -= (T type)
	{
		x -= (float)type;
		y -= (float)type;
	}

	Vector2 operator * (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x * v.x;
		result.y = y * v.y;

		return result;
	}

	template<typename T>
	Vector2 operator * (T type)	const
	{
		Vector2	result;

		result.x = x * (float)type;
		result.y = y * (float)type;

		return result;
	}

	void operator *= (const Vector2& v)
	{
		x *= v.x;
		y *= v.y;
	}

	template<typename T>
	void operator *= (T type)
	{
		x *= (float)type;
		y *= (float)type;
	}

	Vector2 operator / (const Vector2& v)	const
	{
		Vector2	result;

		result.x = x / v.x;
		result.y = y / v.y;

		return result;
	}

	template<typename T>
	Vector2 operator / (T type)	const
	{
		Vector2	result;

		result.x = x / (float)type;
		result.y = y / (float)type;

		return result;
	}

	void operator /= (const Vector2& v)
	{
		x /= v.x;
		y /= v.y;
	}

	template<typename T>
	void operator /= (T type)
	{
		x /= (float)type;
		y /= (float)type;
	}
};