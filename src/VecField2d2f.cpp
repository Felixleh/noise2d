#include "VecField2d2f.h"

#include <stdexcept>
#include <format>

VecField2d2f::VecField2d2f(int height, int width)
	: height(height), width(width)
{
	data = new Vec2f[height * width];
}

VecField2d2f::~VecField2d2f()
{
	delete[] data;
}

void VecField2d2f::set(const Vec2f& value)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			data[y * width + x].x = value.x;
			data[y * width + x].y = value.y;
		}
	}
}

Vec2f& VecField2d2f::at(int y, int x)
{
	if (y >= height || y < 0)
		throw std::out_of_range(std::format("{} is out of range for VecField with height {}!", y, height));

	if (x >= width || x < 0)
		throw std::out_of_range(std::format("{} is out of range for VecField with height {}!", x, width));

	return data[y * width + x];
}

const Vec2f& VecField2d2f::get(int y, int x) const
{
	if (y >= height || y < 0)
		throw std::out_of_range(std::format("{} is out of range for VecField with height {}!", y, height));

	if (x >= width || x < 0)
		throw std::out_of_range(std::format("{} is out of range for VecField with height {}!", x, width));

	return data[y * width + x];
}

int VecField2d2f::getHeight() const
{
	return height;
}

int VecField2d2f::getWidth() const
{
	return width;
}
