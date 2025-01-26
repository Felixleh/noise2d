#pragma once

#include "Vec2f.h"

class VecField2d2f
{
public:
	VecField2d2f(int height, int width);
	virtual ~VecField2d2f();

	void set(const Vec2f& value);
	Vec2f& at(int y, int x);
	const Vec2f& get(int y, int x) const;

	int getHeight() const;
	int getWidth() const;

private:
	const int width;
	const int height;
	Vec2f* data;
};
