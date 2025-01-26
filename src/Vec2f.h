#pragma once

struct Vec2f
{
	float x = 0;
	float y = 0;

	Vec2f();
	Vec2f(float x, float y);
	
	Vec2f operator+(const Vec2f& other) const;
	Vec2f operator-(const Vec2f& other) const;
	Vec2f operator*(const float scalar) const;

	float dot(const Vec2f& other) const;
};
