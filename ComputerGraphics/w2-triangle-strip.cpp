#include "gl/glut.h"
#include <cmath>

const double PI = std::atan(1) * 4;
double Angle2Raidn(double angle) { return angle * (PI / 180.0); }


void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	double length = 0.1f;

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(.0f, 1.0f, .0f);
	glVertex2f(.0f, .0f);
	for (int i = 1; i <= 4; ++i) {
		if (i % 2) {
			glVertex2f(.0f + length * i, .0f);
		}
		else {
			glVertex2f(.0f + length * (0.5 + i), .0f + length);
		}
	}
	glEnd();

	glColor3f(1.0f, .0f, .0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex2f(.0f, .0f);
	for (int i = 1; i <= 4; ++i) {
		if (i % 2) {
			glVertex2f(.0f + length * i, .0f);
		}
		else {
			glVertex2f(.0f + length * (0.5 + i), .0f + length);
		}
	}
	glEnd();

	glFinish();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(1200, 600);
	glutInitWindowPosition(200, 100);

	glutCreateWindow("OpenGL-Triangle(Strip)");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}