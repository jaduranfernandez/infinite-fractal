#include <iostream>
#include "Canvas.h"
#include "InputManager.h"
#include "Fractal.h"

using namespace std;


void parallelFractalTest(Color* colors, int width, int height);


int main(int argc, char** argv) {
    int width = 500;
    int height = 500;
    Canvas screen(width, height, RenderMethod::GPU);  
    InputManager input;
    Fractal fractal;
    fractal.maxIterations = 100;
    
    fractal.init(width, height, 0);
    clock_t begin_time;
    begin_time = clock();
    cout << "(CPU) Tiempo de calculo: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;

    while (!input.isPressed(SDLK_ESCAPE)) {
        input.update();



        if (input.isPressed(SDLK_w)) fractal.centerY -= 0.01;
        if (input.isPressed(SDLK_s)) fractal.centerY += 0.01;
        if (input.isPressed(SDLK_a)) fractal.centerX -= 0.01;
        if (input.isPressed(SDLK_d)) fractal.centerX += 0.01;
        if (input.isPressed(SDLK_UP)) screen.zoom += 0.01;
        if (input.isPressed(SDLK_DOWN)) screen.zoom -= 0.01;
        

        screen.render(fractal);
        screen.update();
    }


    screen.exit();

    return 0;
}

