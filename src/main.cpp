#include "common.h"
#include "Canvas.h"




void main(int argc, char** argv) {
	
	Canvas window;	
	window.init(&argc, argv);
	window.mainLoop();

}