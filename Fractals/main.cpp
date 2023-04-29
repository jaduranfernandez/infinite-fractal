#include <iostream>
#include "Canvas.h"
#include "InputManager.h"
#include "Fractal.h"

using namespace std;


int mainAlt();


int main(int argc, char** argv) {
    int width = 500;
    int height = 500;
    Canvas screen(width, height);  
    InputManager input;
    Fractal fractal;
    fractal.init(width, height, 0);
    while (!input.isPressed(SDLK_ESCAPE)) {
        input.update();
        if (input.isPressed(SDLK_SPACE)) {
            fractal.calculateColors(screen.colors,width, height);
        }        
        screen.update();
    }


    screen.exit();

    return 0;
}


int main3(int argc, char** argv) {
    int width = 640;
    Canvas screen(width, 480);
    bool quit = false;
    bool changed = false;
    int x = 300;
    int y = 150;
    int pos;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    cout << "Ey\n";


                    for (int y = 0; y < 480; y++) {
                        for (int x = 0; x < width; x++) {
                            if (changed)
                                screen.drawPixel(x, y, Color(255, 0, 0));
                            else
                                screen.drawPixel(x, y, Color(0, 0, 255));
                        }
                    }
                    changed = !changed;
                    break;

                case SDLK_q:
                    quit = true;
                    break;
                }
                break;
            }
        }
        screen.update();
    }


    screen.exit();

    return 0;
}




int main2(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    mainAlt();
    // Creamos una ventana
    SDL_Window* window = SDL_CreateWindow("Ejemplo de dibujo de pixeles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    // Creamos una superficie en la que dibujar
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    // Creamos un puntero al primer píxel de la superficie
    Uint32* pixels = (Uint32*)surface->pixels;

    // Dibujamos píxeles en la superficie
    for (int y = 0; y < 480; y++) {
        for (int x = 0; x < 640; x++) {
            // Calculamos el índice del píxel
            int index = y * surface->w + x;

            // Coloreamos el píxel de rojo
            pixels[index] = SDL_MapRGB(surface->format, 255, 0, 0);
        }
    }

    // Actualizamos la ventana
    SDL_UpdateWindowSurface(window);

    // Esperamos a que el usuario cierre la ventana
    bool quit = false;
    bool changed = false;
    int x = 300;
    int y = 150;
    int pos;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    cout << "Ey\n";


                    for (int y = 0; y < 480; y++) {
                        for (int x = 0; x < 640; x++) {
                            // Calculamos el índice del píxel
                            int index = y * surface->w + x;

                            // Coloreamos el píxel de rojo
                            if (changed)
                                pixels[index] = SDL_MapRGB(surface->format, 0, 0, 255);
                            else
                                pixels[index] = SDL_MapRGB(surface->format, 255, 0, 0);
                        }
                    }
                    SDL_UpdateWindowSurface(window);



                    changed = !changed;
                    break;

                case SDLK_q:
                    quit = true;
                    break;
                }
                break;
            }
        }

    }

    // Liberamos la memoria utilizada por SDL
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}