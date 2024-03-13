#include "gl/glut.h"
#include <cmath>

const double PI = std::atan(1) * 4;
double Angle2Raidn(double angle) { return angle * (PI / 180.0); }


void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	int gap = 1, limit = 360;
	double radius = 0.5f;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(.0f, .0f);
	for (int angle = 0; angle <= limit; angle += gap) {
		glColor3f(.0f, .0f, 1.0f * angle / limit);
		float x = radius * std::cosf(Angle2Raidn(angle));
		float y = radius * std::sinf(Angle2Raidn(angle));
		glVertex2f(x, y);
	}
	glEnd();

	glFinish();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 100);

	glutCreateWindow("OpenGL-Triangle(Loop)");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}