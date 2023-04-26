#pragma once
#include "common.h"


struct color {
	float r, g, b;
	color() { this->r = 0; this->g = 0; this->b = 0; };
	color(float r, float g, float b) :r(r), g(g), b(b) {};
};


class Canvas {
private:
	static int windowId;
	static float pixelSize;
	static color* pixels;

	static void preDisplay();
	static void postDisplay();
	static void keyInput(unsigned char key, int x, int y);
	static void displayCanvas(void);
	static void drawScreen();
	static color backgroundColor;

public:
	Canvas(){};
	static color testColor;
	static int windowWidth;
	static int windowHeight;
	string windowName = "Fractal";
	static void init(int* argcp, char** argv);
	static void drawPixel(int x, int y);
	static void drawPixel(int x, int y, color);
	static void mainLoop();
};