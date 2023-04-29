#pragma once
#include<SDL.h>
#include<map>


class InputManager{
private:
	SDL_Event event;
	bool finish = false;
	std::map<char, bool> keyState;
public:
	InputManager();
	bool isPressed(char key);
	void update();
	bool exit() { return this->finish; };
};

