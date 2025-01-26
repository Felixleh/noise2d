#pragma once

#include <memory>
#include <span>

#include "Image.h"

class VecField2d2f;

class PerlinNoiseGenerator
{
public:
	PerlinNoiseGenerator(int height, int width, int octaves, float scale);
	virtual ~PerlinNoiseGenerator();

	void generate(Image& target);

	int getHeight() const;
	int getWidth() const;
	int getOctaves() const;
	float getScale() const;

private:
	const int height;
	const int width;
	const int octaves;
	const float scale;

	std::unique_ptr<VecField2d2f> gradients;
};