#pragma once
#include "common.h"

class Fractal {
private:
	static complex<double> getNextCoordinate(complex<double> z_n, complex<double> c);
	static complex<double> fromPixelToComplex(int x, int y, int windowWidth, int windowHeight);
	static float xRangeChanger, yRangeChanger;
	static float xSize, ySize;
	static float left, right, up, down;
public:
	static float centerX, centerY;
	static void init(int width, int height, float zoom);
	static int maxIterations;
	static float tolerance;
	static float calculateIntensity(int x, int y, int windowWidth, int windowHeight);
};

float linearInterpolation(float value_a, float left_a, float right_a, float left_b, float right_b);
