#include "common.h"
#include "Canvas.h"

int width, height;

int pixelSize = 2;
float leftBorder = -1.5f;
float rightBorder = 0.5f;
float topBorder = 1.0f;
float bottomBorder = -1.0f;

int maxIterations = 30;
float tolerance = 0.01f;



//struct color {
//	float r, g, b;
//	color() { this->r = 0; this->g = 0; this->b = 0; };
//	color(float r, float g, float b) :r(r), g(g), b(b) {};
//};

color c(1.0f, 0.0f, 0.0f);



/*
----------------------------------------------------------------------
Fractals operations
----------------------------------------------------------------------
*/

complex<double> getNextCoordinate(complex<double> z_n, complex<double> c) {
	return z_n * z_n + c; // Next coordinate
}


float growsToInfinity(complex<double> point, int maxIterations, float tolerance) {
	int currentIteration = 0;
	complex<double> previousCoordinate = point;
	complex<double> nextCoordinate = getNextCoordinate(point, point);
	float magDifference = tolerance + 1;
	while (currentIteration < maxIterations && magDifference > tolerance) {
		//while(currentIteration < maxIterations){
		previousCoordinate = nextCoordinate;
		nextCoordinate = getNextCoordinate(nextCoordinate, point);
		nextCoordinate = getNextCoordinate(nextCoordinate, point);
		magDifference = abs(nextCoordinate - previousCoordinate);
		currentIteration++;
	}
	return currentIteration / (float)maxIterations;
}


int matrixIndex(int x, int y) {
	return y * width + x;
}



/*
----------------------------------------------------------------------
OpenGL specific drawing routines
----------------------------------------------------------------------
*/

static void PreDisplay(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pixelSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
}

static void PostDisplay(void){
	glutSwapBuffers();
}

void calculateCanvas() {

}

static void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	
	glBegin(GL_POINTS);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(pixelSize / 2, pixelSize / 2);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(pixelSize/2, height-pixelSize/2);

	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(width - pixelSize / 2, pixelSize / 2);


	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(width - pixelSize/2, height - pixelSize / 2);


	/*float stepHor = pixelSize * (rightBorder - leftBorder) / (width - 1);
	float stepVer = pixelSize * (topBorder - bottomBorder) / (height - 1);


	float yCoordinate = bottomBorder;
	for (int y = 0; y < height; y+=pixelSize) {
		float xCoordinate = leftBorder;
		for (int x = 0; x < width; x+=pixelSize) {
			complex<double> point(xCoordinate, yCoordinate);
			float intensity = growsToInfinity(point, maxIterations, tolerance);
			glColor3f(c.r * intensity, c.g * intensity, c.b * intensity);
			glVertex2f(x + pixelSize / 2, y + pixelSize / 2);

			xCoordinate += stepHor;
		}
		yCoordinate += stepVer;
	}*/


	glEnd();
	glFlush();
	glutSwapBuffers();

}




static void KeyFunc(unsigned char key, int x, int y){
	switch (key){
	case 'c':
		cout << "Skere\n";
		c.g -= 0.1;
		c.b += 0.1;
		break;
	}
}


void myinit() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(pixelSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
}



//void main(int argc, char** argv) {
//	glutInit(&argc, argv);
//	width = height = 500;
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowSize(width, height);
//	glutInitWindowPosition(0, 0);
//	glutCreateWindow("Points");
//	glutDisplayFunc(display);
//	
//
//	myinit();
//	glutMainLoop();
//}


void main(int argc, char** argv) {
	
	Canvas window;	
	window.init(&argc, argv);
	window.testColor = color(0.0f, 0.0f, 1.0f);
	window.mainLoop();

}