#include "common.h"
#include "Canvas.h"




void main(int argc, char** argv) {
	
	Canvas window;
	window.windowWidth = 512;
	window.windowHeight = 512;
	window.init(&argc, argv);
	window.mainLoop();

}