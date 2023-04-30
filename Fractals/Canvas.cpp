#include "Canvas.h"


Canvas::Canvas(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Infinite fractals", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    pixels = (Uint32*)surface->pixels;
    colors = (Color*)malloc(windowWidth * windowHeight * sizeof(Color));
    zoom = 0.0f;
    renderMethod = RenderMethod::CPU;
}

Canvas::Canvas(int width, int height, RenderMethod renderMethod):Canvas(width,height) {
    this->renderMethod = renderMethod;
}


Canvas::~Canvas() {
    window = nullptr;
    surface = nullptr;
    pixels = nullptr;
    colors = nullptr;
}


void Canvas::drawPixel(int x, int y, Color color) {
    colors[y * windowWidth + x] = color;
}


void Canvas::update() {
    int index;
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            index = y * windowWidth + x;
            Color color = colors[index];
            pixels[index] = SDL_MapRGB(surface->format, color.r, color.g, color.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}


void Canvas::render(Fractal &fractal) {
    fractal.init(this->windowWidth, this->windowHeight, this->zoom);
    switch (renderMethod){
    case RenderMethod::CPU:
        fractal.calculateColors(this->colors, this->windowWidth, this->windowHeight);
        break;
    case RenderMethod::GPU:
        parallelFractal(fractal, this->colors, this->windowWidth, this->windowHeight);
        break;
    default:
        break;
    }
}



void Canvas::exit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}