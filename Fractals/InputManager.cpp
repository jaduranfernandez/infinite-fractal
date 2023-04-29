#include "InputManager.h"


InputManager::InputManager() {
    for (int charValue = 97; charValue < 122; charValue++) {
        keyState[charValue] = false;
    }
    keyState[32] = false;   //  Space
    keyState[SDLK_ESCAPE] = false;   //  Escape
}


void InputManager::update() {
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {            
            case SDL_KEYDOWN:
                keyState[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keyState[event.key.keysym.sym] = false;
                break;      
        }
    }
}



bool InputManager::isPressed(char key) {
	return keyState[key];
}
