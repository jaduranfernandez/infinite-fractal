#pragma once

#include "Color.h"
#include "Fractal.h"
#include<SDL.h>

#include <iostream>
void parallelFractal(Fractal fractal, Color* h_Colors, int width, int height);

enum class RenderMethod { CPU = 1, GPU = 2 };

class Canvas{
private:
	int windowWidth, windowHeight;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	Uint32* pixels;
public:
	Color* colors;
	float zoom;
	RenderMethod renderMethod;
	Canvas(int, int);
	Canvas(int, int, RenderMethod);
	~Canvas();
	void update();
	void render(Fractal &fractal);
	void exit();
	void drawPixel(int x, int y, Color);
};

