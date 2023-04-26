#include "Canvas.h"


int matrixIndex(int x, int y, int width) {
	return y * width + x;
}

void Canvas::init(int* argcp, char** argv) {
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Points");

	pixels = (color*)malloc(windowWidth * windowHeight * sizeof(color));

	/*glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pixelSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);*/


	preDisplay();


	glutKeyboardFunc(keyInput);
	//glutIdleFunc(IdleFunc);
	glutDisplayFunc(displayCanvas);


	//	New Init




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
			//cout << "Ey\n";
			drawPixel(x, y, color(1, 1, 0));
		}
	}


	glColor3f(testColor.r, testColor.g, testColor.b);
	glVertex2f(pixelSize / 2, pixelSize / 2);

	glColor3f(testColor.r, testColor.g, testColor.b);
	glVertex2i(pixelSize / 2, windowHeight - pixelSize / 2);

	glColor3f(testColor.r, testColor.g, testColor.b);
	glVertex2i(windowWidth - pixelSize / 2, pixelSize / 2);


	glColor3f(testColor.r, testColor.g, testColor.b);
	glVertex2f(windowWidth - pixelSize / 2, windowHeight - pixelSize / 2);
	
}

void Canvas::drawPixel(int x, int y) {
	color c = pixels[matrixIndex(x,y,windowWidth)];
	glColor3f(c.r, c.g, c.b);
	glVertex2f(x, y);
}


void Canvas::drawPixel(int x, int y, color c) {
	glColor3f(c.r, c.g, c.b);
	glVertex2f(x, y);
}


void Canvas::keyInput(unsigned char key, int x, int y){
	switch (key){
	case 'c':
		cout << "Change color\n";
		if (testColor.b == 1.0f)
			testColor = color(1.0f, 0.0f, 0.0f);
		else
			testColor = color(0.0f, 0.0f, 1.0f);
		break;

	case 27:	//	Escape
		exit(0);
		break;

	}
}


void Canvas::preDisplay() {
	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pixelSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);


	//glViewport(0, 0, windowWidth, windowHeight);
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glPointSize(pixelSize);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);
	//glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
}


void Canvas::postDisplay() {
	glEnd();
	glFlush();
	glutSwapBuffers();
}



int Canvas::windowId = 0;
float Canvas::pixelSize = 50.0f;
color* Canvas::pixels = nullptr;
int Canvas::windowWidth = 512;
int Canvas::windowHeight = 512;
color Canvas::backgroundColor = color(0,0,0);
color Canvas::testColor = color(0, 0, 0);