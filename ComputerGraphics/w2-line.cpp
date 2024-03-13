#include "gl/glut.h"
#include <cmath>

const double PI = std::atan(1) * 4;
double Angle2Raidn(double angle) { return angle * (PI / 180.0); }

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	double innerRadius = 0.2, outterRadius = 0.5;
	int limit = 360, gap = 45;

	// 점 그리기
	glColor3f(.0f, .0f, 1.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	for (int angle = 0; angle < limit; angle += gap) {
		float x = outterRadius * std::cosf(Angle2Raidn(angle));
		float y = outterRadius * std::sinf(Angle2Raidn(angle));
		glVertex2f(x, y);
	}
	glEnd();

	// 선 그리기
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	for (int angle = 0; angle < limit; angle += gap) {
		float x1 = innerRadius * std::cosf(Angle2Raidn(angle));
		float y1 = innerRadius * std::sinf(Angle2Raidn(angle));
		float x2 = outterRadius * std::cosf(Angle2Raidn(angle));
		float y2 = outterRadius * std::sinf(Angle2Raidn(angle));

		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	}
	glEnd();


	// 선 그리기 (스트립)
	glColor3f(.0f, 1.0f, .0f);
	glBegin(GL_LINE_STRIP);
	for (int angle = 0; angle < limit; angle += gap) {
		float x = innerRadius * std::cosf(Angle2Raidn(angle));
		float y = innerRadius * std::sinf(Angle2Raidn(angle));
		glVertex2f(x, y);
	}
	glEnd();
	// 선 그리기 (루프)
	glColor3f(1.0f, .0f, .0f);
	glBegin(GL_LINE_LOOP);
	for (int angle = 0; angle < limit; angle += gap) {
		float x = outterRadius * std::cosf(Angle2Raidn(angle));
		float y = outterRadius * std::sinf(Angle2Raidn(angle));
		glVertex2f(x, y);
	}
	glEnd();

	glFinish();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(500, 100);

	glutCreateWindow("OpenGL-Line");

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}