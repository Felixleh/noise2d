#include "Vec2f.h"


Vec2f::Vec2f()
{
}

Vec2f::Vec2f(float x, float y)
	: x(x), y(y)
{
}

Vec2f Vec2f::operator+(const Vec2f& other) const
{
	return Vec2f(x + other.x, y + other.y);
}

Vec2f Vec2f::operator-(const Vec2f& other) const
{
	return Vec2f(x - other.x, y - other.y);
}

Vec2f Vec2f::operator*(const float scalar) const
{
	return Vec2f(x * scalar, y * scalar);
}

float Vec2f::dot(const Vec2f& other) const
{
	return x * other.x + y * other.y;
}
