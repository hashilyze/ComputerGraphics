#include "gl/glut.h"
#include <cmath>


void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(.0f, .0f, 1.0f);
	glBegin(GL_LINE_LOOP);

	glEnd();

	glFinish();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 100);

	glutCreateWindow("OpenGL");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}