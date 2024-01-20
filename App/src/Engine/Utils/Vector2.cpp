#include "stdafx.h"

#include "Vector2.h"

namespace MyEngine
{
	Vec2::Vec2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vec2::Vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vec2::Vec2(const Vec2& other)
	{
		x = other.x;
		y = other.y;
	}

	Vec2& Vec2::operator=(const Vec2& other)
	{
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	Vec2 Vec2::operator+(const Vec2& other) const 
	{
		return Vec2(x + other.x, y + other.y);
	}

	Vec2 Vec2::operator+(float scalar) const
	{
		return Vec2(x + scalar, y + scalar);
	}

	Vec2 Vec2::operator-(const Vec2& other) const 
	{
		return Vec2(x - other.x, y - other.y);
	}

	Vec2 Vec2::operator-(float scalar) const
	{
		return Vec2(x - scalar, y - scalar);
	}

	Vec2 Vec2::operator*(float scalar) const 
	{
		return Vec2(x * scalar, y * scalar);
	}

	Vec2 Vec2::operator/(float scalar) const
	{
		if (scalar != 0.0f) {
			return Vec2(x / scalar, y / scalar);
		}
		else {
			std::cerr << "Error: Division by zero!" << std::endl;
			return Vec2();
		}
	}

	Vec2 Vec2::operator-() const 
	{
		return Vec2(-x, -y);
	}

	float Vec2::Dot(const Vec2& other) const
	{
		return x * other.x + y * other.y;
	}

	float Vec2::Cross(const Vec2& other) const
	{
		return x * other.y - y * other.x;
	}
	
	float Vec2::Length() const
	{
		return std::sqrt(x * x + y * y);
	}

	Vec2 Vec2::Normalize() const
	{
		float length = Length();
		if (length != 0.0f) {
			return (*this) / length;
		}
		else {
			std::cerr << "Error: Normalizing the zero vector!" << std::endl;
			return Vec2();
		}
	}
}
