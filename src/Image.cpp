#include "Image.h"

#include <stdexcept>

Image::Image(std::span<float> memory, int height, int width)
	: memory(memory), height(height), width(width)
{
	if (height <= 0)
		throw std::invalid_argument("Image height must be > 0!");

	if (width <= 0)
		throw std::invalid_argument("Image width must be > 0!");

	if (memory.size() != static_cast<size_t>(height * width))
		throw std::invalid_argument("The size of memory does not match the image size!");
}

float& Image::at(int y, int x)
{
	return memory[index(y, x)];
}

const float& Image::at(int y, int x) const
{
	return memory[index(y, x)];
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

int Image::index(int y, int x) const
{
	return y * width + x;
}
