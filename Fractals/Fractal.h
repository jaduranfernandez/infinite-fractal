#pragma once
#include <complex>
#include "Color.h"

using namespace std;

class Fractal {
private:
	complex<double> getNextCoordinate(complex<double> z_n, complex<double> c);
	complex<double> fromPixelToComplex(int x, int y, int windowWidth, int windowHeight);
	float xRangeChanger, yRangeChanger;
	float xSize, ySize;
public:
	Color color;
	Color altColor;
	float left, right, up, down;
	float centerX, centerY;
	Fractal();
	void init(int width, int height, float zoom);
	int maxIterations;
	float tolerance;
	float calculateIntensity(int x, int y, int windowWidth, int windowHeight);
	void calculateColors(Color* color, int width, int height);	
};

float linearInterpolation(float value_a, float left_a, float right_a, float left_b, float right_b);
