#include <iostream>
#include "Canvas.h"
#include "InputManager.h"
#include "Fractal.h"

using namespace std;


void parallelFractalTest(Color* colors, int width, int height);


int main(int argc, char** argv) {
    
    /*----------------------------------------------------------------------
                Canvas
    ----------------------------------------------------------------------*/    
    int width = 500;
    int height = 500;
    Canvas screen(width, height, RenderMethod::GPU);    //  Usign Cuda
    

    /*----------------------------------------------------------------------
            Fractal
    ----------------------------------------------------------------------*/
    Fractal fractal;
    fractal.maxIterations = 100;   
    fractal.tolerance = 0.001f;
    fractal.color = Color(200, 0, 206);
    fractal.altColor = Color(102, 255, 255);



    InputManager input;
    while (!input.isPressed(SDLK_ESCAPE)) {
        input.update();
        
        //  Input handler
        if (input.isPressed(SDLK_w)) fractal.centerY -= 0.01;
        if (input.isPressed(SDLK_s)) fractal.centerY += 0.01;
        if (input.isPressed(SDLK_a)) fractal.centerX -= 0.01;
        if (input.isPressed(SDLK_d)) fractal.centerX += 0.01;
        if (input.isPressed(SDLK_e)) screen.zoom += 0.01;
        if (input.isPressed(SDLK_q)) screen.zoom -= 0.01;
        
            
        //  Render screen
        screen.render(fractal);
        screen.update();
    }


    screen.exit();

    return 0;
}

