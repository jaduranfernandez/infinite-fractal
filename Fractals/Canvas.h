#pragma once

#include "Color.h"
#include<SDL.h>

class Canvas{
private:
	int windowWidth, windowHeight;
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;
	Uint32* pixels;
public:
	Color* colors;
	Canvas(int, int);
	~Canvas();
	void update();
	void exit();
	void drawPixel(int x, int y, Color);
};

