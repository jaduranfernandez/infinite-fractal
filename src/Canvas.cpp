#include "Canvas.h"


int matrixIndex(int x, int y, int width) {
	return y * width + x;
}


void Canvas::preDisplay() {
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(testColor.r, testColor.g, testColor.b);
	glPointSize(pixelSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	Fractal::init(windowWidth, windowHeight);
}


void Canvas::postDisplay() {
	glEnd();
	glFlush();
	glutSwapBuffers();
}


void Canvas::init(int* argcp, char** argv) {
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	windowId = glutCreateWindow("Points");

	pixels = (color*)malloc(windowWidth * windowHeight * sizeof(color));


	preDisplay();

	//	Custom functions
	glutKeyboardFunc(keyInput);
	glutIdleFunc(idleFunc);
	glutDisplayFunc(displayCanvas);

}


void Canvas::idleFunc(void) {

	glutSetWindow(windowId);
	glutPostRedisplay();
}

void Canvas::mainLoop() {
	glutMainLoop();
}



void Canvas::displayCanvas(void){
	preDisplay();
	drawScreen();	
	postDisplay();
}


void Canvas::drawScreen() {
	for (int y = 0; y < windowHeight; y += pixelSize) {
		for (int x = 0; x < windowWidth; x += pixelSize) {
			float intensity = Fractal::calculateIntensity(x, y, windowWidth, windowHeight);
			//cout << intensity << "\n";

			drawPixel(x, y, color(intensity * testColor.r, intensity * testColor.g, intensity * testColor.b));
		}
	}


	
}

void Canvas::drawPixel(int x, int y) {
	color c = pixels[matrixIndex(x,y,windowWidth)];
	glColor3f(c.r, c.g, c.b);
	glVertex2f(x, y);
}


void Canvas::drawPixel(int x, int y, color c) {
	glColor3f(c.r, c.g, c.b);
	//glColor3f(0.7f, 1.0f, 1.0f);
	glVertex2f(x, y);
}


void Canvas::keyInput(unsigned char key, int x, int y){
	switch (key){
	case 'c':
		cout << "Change color \n";
		float aux;
		aux = testColor.r;
		testColor.r = testColor.b;
		testColor.b = aux;
		break;
	case 32:	//	Spacebar
		pixelSize -= 1;
		break;
	case 27:	//	Escape
		exit(0);
		break;

	}
}




int Canvas::windowId = 0;
float Canvas::pixelSize = 10.0f;
color* Canvas::pixels = nullptr;
int Canvas::windowWidth = 512;
int Canvas::windowHeight = 512;
color Canvas::backgroundColor = color(0,0,0);
color Canvas::testColor = color(0.7f, 1.0f, 1.0f);