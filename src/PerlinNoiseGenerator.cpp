#include "PerlinNoiseGenerator.h"

#include <stdexcept>
#include <format>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <numbers>
#include <random>
#include "VecField2d2f.h"

inline static float smoothstep(float a, float b, float w)
{
	w = w * w * (3 - 2 * w);
	return (1 - w) * a + w * b;
}

PerlinNoiseGenerator::PerlinNoiseGenerator(int height, int width, int octaves, float scale)
	: height(height), width(width), octaves(octaves), scale(scale)
{
	if (height <= 0)
		throw std::invalid_argument("Generator height must be > 0!");

	if (width <= 0)
		throw std::invalid_argument("Generator width must be > 0!");

	if (octaves <= 0)
		throw std::invalid_argument("Generator octaves must be >= 1!");

	float intensity = 1 / std::powf(2, octaves - 1);
	float cellSize = scale * intensity;

	if (cellSize < 1)
		throw std::invalid_argument("Maximum detail level of noise is to high!");

	gradients = std::make_unique<VecField2d2f>(height, width);
}

PerlinNoiseGenerator::~PerlinNoiseGenerator()
{
}

void PerlinNoiseGenerator::generate(Image& target)
{
	if (target.getWidth() != width || target.getHeight() != height)
		throw std::invalid_argument("Target dimensions must match dimensions of generator.");

	static std::mt19937 rng;

	std::uniform_real_distribution<> dist(0, 2 * std::numbers::pi);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			target.at(y, x) = 0;
		}
	}

	float intensity = 1 / std::powf(2, octaves - 1);
	float cellSize = scale * intensity;
	int cellsX = std::ceil(width / cellSize + 1);
	int cellsY = std::ceil(height / cellSize + 1);

	if (cellSize < 1)
		throw std::invalid_argument("Maximum detail level of noise is to high!");

	VecField2d2f gradients(cellsX, cellsY);

	for (int octave = 0; octave < octaves; octave++)
	{
		for (int iy = 0; iy < cellsY; iy++)
		{
			for (int ix = 0; ix < cellsX; ix++)
			{
				float randomAngle = dist(rng);
				gradients.at(iy, ix).x = std::cosf(randomAngle);
				gradients.at(iy, ix).y = std::sinf(randomAngle);
			}
		}

		const float div = 1 / cellSize;

		for (int y = 0; y < height; y++)
		{
			const int iY = y * div;
			const float yDiff0 = (y - iY * cellSize) * div;
			const float yDiff1 = yDiff0 - 1;

			for (int x = 0; x < width; x++)
			{
				const int iX = x * div;
				const float xDiff0 = (x - iX * cellSize) * div;
				const float xDiff1 = xDiff0 - 1;

				float upperLeft = gradients.at(iY, iX).dot(Vec2f(xDiff0, yDiff0));
				float upperRight = gradients.at(iY, iX + 1).dot(Vec2f(xDiff1, yDiff0));
				float lowerLeft = gradients.at(iY + 1, iX).dot(Vec2f(xDiff0, yDiff1));
				float lowerRight = gradients.at(iY + 1, iX + 1).dot(Vec2f(xDiff1, yDiff1));

				float upper = smoothstep(upperLeft, upperRight, xDiff0);
				float lower = smoothstep(lowerLeft, lowerRight, xDiff0);

				float value = smoothstep(upper, lower, yDiff0);

				target.at(y, x) += value * intensity;
			}
		}

		cellSize *= 2;
		intensity *= 2;
		cellsX = std::ceil(width / cellSize);
		cellsY = std::ceil(height / cellSize);
	}
}

int PerlinNoiseGenerator::getHeight() const
{
	return height;
}

int PerlinNoiseGenerator::getWidth() const
{
	return width;
}

int PerlinNoiseGenerator::getOctaves() const
{
	return octaves;
}

float PerlinNoiseGenerator::getScale() const
{
	return octaves;
}