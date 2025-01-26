#pragma once

#include <span>

class Image
{
public:
	Image(std::span<float> memory, int height, int width);

	float& at(int y, int x);
	const float& at(int y, int x) const;

	int getWidth() const;
	int getHeight() const;

private:
	int index(int y, int x) const;

	std::span<float> memory;
	int height;
	int width;
};