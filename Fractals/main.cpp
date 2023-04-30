#include <iostream>
#include "Canvas.h"
#include "InputManager.h"
#include "Fractal.h"

using namespace std;


void parallelFractalTest(Color* colors, int width, int height);
void parallelFractal(Fractal fractal, Color* h_Colors, int width, int height);


int main(int argc, char** argv) {
    int width = 500;
    int height = 500;
    Canvas screen(width, height);  
    InputManager input;
    Fractal fractal;
    fractal.maxIterations = 150;
    
    fractal.init(width, height, 0);
    clock_t begin_time;
    while (!input.isPressed(SDLK_ESCAPE)) {
        input.update();
        if (input.isPressed(SDLK_SPACE)) {
            begin_time = clock();
            fractal.calculateColors(screen.colors, width, height);
            cout << "(CPU) Tiempo de calculo: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
        }
        if (input.isPressed(SDLK_c)) {
            begin_time = clock();
            parallelFractal(fractal, screen.colors, width, height);
            cout << "(GPU) Tiempo de calculo: " << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
        }
        screen.update();
    }


    screen.exit();

    return 0;
}

