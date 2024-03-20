#include "gl/glut.h"
#include <cstdio>
#include <vector>

struct Vec2 {
	Vec2() : x(.0), y(.0) { }
	Vec2(float x, float y) : x(x), y(y) { }

	float x, y;
};

constexpr int WIDTH = 500;
constexpr int HEIGHT = 500;
const float WEIGHTS[] = { 2.0, 4.0, 6.0, 8.0, 10.0 };

Vec2 mousePt = { 0, 0 };

std::vector<std::pair<std::vector<Vec2>, int>> lines(1);
int curWeight = 0;

void makeLineBuffer() {
	lines.emplace_back();
	lines.back().second = curWeight;
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10.0);

	glBegin(GL_POINTS);
	glVertex2f(mousePt.x, mousePt.y);
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	for (const auto& line : lines) { // Draw lines
		glLineWidth(WEIGHTS[line.second]);		// Set weight
		glBegin(GL_LINE_STRIP);
		for (const auto& point : line.first) {	// Draw line
			glVertex2f(point.x, point.y);
		}
		glEnd();
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC
		exit(0);
		break;
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
	case 0x35: // Change line width
		curWeight = lines.back().second = (key - 0x31);
		break;
	case 'r':
	case 'R': // Erase all
		lines.clear();
		makeLineBuffer();
	}
	glutPostRedisplay();
}

void mouseCoordinateTranslate(int winX, int winY) {
	mousePt.x = winX / (WIDTH / 2.0) - 1;
	mousePt.y = (winY / (HEIGHT / 2.0) - 1) * (-1.0);
}

void mouse(int button, int state, int x, int y) {
	printf("mouse: %d %d %d %d\n", button, state, x, y);
	if (state == GLUT_DOWN) {
		mouseCoordinateTranslate(x, y);
	} else if (state == GLUT_UP) {
		makeLineBuffer();
	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	printf("mouse motion: %d %d\n", x, y);
	mouseCoordinateTranslate(x, y);
	lines.back().first.push_back(mousePt); // Trace points
	glutPostRedisplay();
}

void mousePassiveMotion(int x, int y) {
	printf("mouse passive motion: %d %d\n", x, y);
	mouseCoordinateTranslate(x, y);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200, 200);


	glutCreateWindow("OpenGL-Drawing");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(mousePassiveMotion);
	glutMainLoop();

	return 0;
}