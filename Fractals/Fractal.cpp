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
	float realValue = linearInterpolation(x, 0, left, xRangeChanger);
	float imaValue = linearInterpolation(y, 0, up, yRangeChanger);
	return complex<double>(realValue, imaValue);
}


Fractal::Fractal() {
	maxIterations = 20;
	tolerance = 0.01f;
	centerX = -0.5f;
	centerY = 0.0f;
	xSize = 2.0f;
	ySize = 2.0f;
	left = -1.5f;
	right = 0.5f;
	up = 1.0f;
	down = -1.0f;
	xRangeChanger = 0.0f;
	yRangeChanger = 0.0f;
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


void Fractal::calculateColors(Color* colors, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float intensity = calculateIntensity(x, y, width, height);
			colors[y * width + x] = Color(102 * intensity, 255 * intensity, 255 * intensity);
		}
	}
}
