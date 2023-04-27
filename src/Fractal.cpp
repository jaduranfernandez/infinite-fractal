#include "Fractal.h"



//	Turns value in range [a,b] to value in range [c,d]
float linearInterpolation(float value, float a, float b, float c, float d) {
	return c + (((d - c) / (b - a)) * (value - a));
}
//	Turns value in range [a,b] to value in range [c,d] with previously calculated value
float linearInterpolation(float value, float a, float c, float conversionValue) {
	return c + (conversionValue * (value - a));
}


complex<double> Fractal::getNextCoordinate(complex<double> z_n, complex<double> c) {
	return z_n * z_n + c; // Next coordinate
}

complex<double> Fractal::fromPixelToComplex(int x, int y, int windowWidth, int windowHeight) {
	/*float realValue = linearInterpolation(x, 0, windowWidth, left, right);
	float imaValue = linearInterpolation(y, 0, windowHeight, up, down);*/
	float realValue = linearInterpolation(x, 0, left, xRangeChanger);
	float imaValue = linearInterpolation(y, 0, up, yRangeChanger);
	return complex<double>(realValue, imaValue);
}

void Fractal::init(int width, int height, float zoom) {
	left = (centerX - xSize / 2) + zoom;
	right = (centerX + xSize / 2) - zoom;
	up = (centerY - ySize / 2) + zoom;
	down = (centerY + ySize / 2) - zoom;
	xRangeChanger = ((right - left) / (width - 0));
	yRangeChanger = ((down - up) / (height - 0));
}

float Fractal::calculateIntensity(int x, int y, int windowWidth, int windowHeight) {
	int currentIteration = 0;
	complex<double> point = fromPixelToComplex(x, y, windowWidth, windowHeight);
	complex<double> previousCoordinate = point;
	complex<double> nextCoordinate = getNextCoordinate(point, point);
	float magDifference = tolerance + 1;
	while (currentIteration < maxIterations && magDifference > tolerance) {
		previousCoordinate = nextCoordinate;
		nextCoordinate = getNextCoordinate(nextCoordinate, point);
		nextCoordinate = getNextCoordinate(nextCoordinate, point);
		magDifference = abs(nextCoordinate - previousCoordinate);
		currentIteration++;
	}
	return currentIteration / (float)maxIterations;
}

int Fractal::maxIterations = 20;
float Fractal::tolerance = 0.01f;
float Fractal::centerX = -0.5f;
float Fractal::centerY = 0.0f;
float Fractal::xSize = 2.0f;
float Fractal::ySize = 2.0f;
float Fractal::left = -1.5f;
float Fractal::right = 0.5f;
float Fractal::up = 1.0f;
float Fractal::down = -1.0f;
float Fractal::xRangeChanger = 0.0f;
float Fractal::yRangeChanger = 0.0f;
