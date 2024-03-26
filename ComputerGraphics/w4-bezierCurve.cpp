#include "gl/glut.h"
#include <cstdio>
#include "GCBezierCurve.h"


Vec2 mousePt = { 1, 0 };
float rotateAngle = 0.0;
std::vector<Vec2> ctrlPts;
std::vector<Vec2> boxPoints;

void displayGlutPrimitives() {

	glutWireSphere(1.0, 20, 20);
	//glutSolidSphere(1.0, 20, 20);

	//glutWireCube(0.5);
	//glutSolidCube(0.5);

	//glutWireCone(1.0, 1.5, 12, 12);
	//glutSolidCone(1.0, 1.5, 12, 12);

	//glutWireTorus(0.3, 0.7, 20, 20);
	//glutSolidTorus(0.3, 0.7, 20, 20);

	//glutWireTeapot(1.0);
	//glutSolidTeapot(1.0);
}

void display() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

	//----------------- 0. Display Glut Primitives -------------------
		//displayGlutPrimitives();
	// ----------------------------------------------------------------


	//--------------- 1. Simple transform ------------------------
		//glMatrixMode(GL_MODELVIEW);
		//glColor3f(0.0f, 0.0f, 0.0f);
		//glLoadIdentity();
		//glTranslatef(1.0, 0.0, 0.0);
		//displayGlutPrimitives();

		//glColor3f(1.0, 0.0, 0.0);
		//glLoadIdentity();
		//glTranslatef(0.0, 1.0, 0.0);
		//displayGlutPrimitives();

		//glColor3f(0.0, 0.0, 1.0);
		//glLoadIdentity();
		//glTranslatef(0.0, 0.0, 1.0);
		//displayGlutPrimitives();
	// ----------------------------------------------------------------


	// --------------- 2. Multiple transform --------------------------
		//glMatrixMode(GL_MODELVIEW);
		//// Rotate-Translate
		//glLoadIdentity();
		//glColor3f(1, 0, 0);
		//glRotatef(rotateAngle, 0.0, 0.0, 1.0);
		//glTranslatef(1.0, 0.0, 0.0);
		//displayGlutPrimitives();

		////Translate-Rotate
		//glColor3f(0, 0, 1);
		//glLoadIdentity();
		//glTranslatef(1.0, 0.0, 0.0);
		//glRotatef(rotateAngle, 0.0, 0.0, 1.0);
		//displayGlutPrimitives();
	// ----------------------------------------------------------------


	// --------------- 3. Bezier Curve --------------------------
	BezierCurve2D curve(ctrlPts);
	boxPoints.clear();
	boxPoints.push_back(ctrlPts.front());

	glPointSize(5.0);
	glLineWidth(1.0);
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	for (auto& pt : ctrlPts)
		glVertex2f(pt.x, pt.y);
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (auto& pt : ctrlPts)
		glVertex2f(pt.x, pt.y);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 100; i++) {
		auto pt = curve.Evaluate(i / 100.0);
		glVertex2f(pt.x, pt.y);
		if (1 < i) {
			Vec2 p1 = curve.Evaluate((i - 2) / 100.0);
			Vec2 p2 = curve.Evaluate((i - 1) / 100.0);
			float s1 = (p2.y - p1.y) * (p2.x - p1.x);
			float s2 = (pt.y - p2.y) * (pt.x - p2.x);
			if (s1 * s2 < 0) {
				boxPoints.push_back(p2);
			}
		}
	}
	glEnd();
	boxPoints.push_back(ctrlPts.back());

	// Draw AABB
	glColor3f(1.0f, 0, 1.0f);
	for (int i = 1; i < boxPoints.size(); ++i) {
		Vec2 p1 = boxPoints[i - 1], p2 = boxPoints[i];
		if (p1.x > p2.x) {
			std::swap(p1, p2);
		}

		glBegin(GL_LINE_LOOP);
		if (p1.y > p2.y) { // top-left & bottom-right 
			Vec2 size = { p2.x - p1.x, p1.y - p2.y };
			glVertex2f(p1.x, p1.y);
			glVertex2f(p1.x + size.x, p1.y);
			glVertex2f(p1.x + size.x, p1.y - size.y);
			glVertex2f(p1.x, p1.y - size.y);
		}
		else { // bottom-left & top-right
			Vec2 size = { p2.x - p1.x, p2.y - p1.y };
			glVertex2f(p1.x, p1.y);
			glVertex2f(p1.x + size.x, p1.y);
			glVertex2f(p1.x + size.x, p1.y + size.y);
			glVertex2f(p1.x, p1.y + size.y);
		}
		glEnd();
	}
	// ----------------------------------------------------------------

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 27: // ESC
		exit(0);
		break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotateAngle += 10;
		break;
	case GLUT_KEY_DOWN:
		rotateAngle -= 10;
		break;
	}
	glutPostRedisplay();
}

void mouseCoordinateTranslate(int winX, int winY)
{
	mousePt.x = winX / 50.0 - 5;
	mousePt.y = (winY / 50.0 - 5) * (-1.0);
}

void changeCtrlPts()
{
	for (auto& pt : ctrlPts) {
		if (sqrt(pow(pt.x - mousePt.x, 2) + pow(pt.y - mousePt.y, 2)) < 0.5) {
			pt = mousePt;
			break;
		}
	}
}

void mouse(int button, int state, int x, int y)
{
	printf("mouse: %d %d %d %d\n", button, state, x, y);
	if (state == GLUT_DOWN) {
		mouseCoordinateTranslate(x, y);
		changeCtrlPts();
	}
	glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
	printf("mouse motion: %d %d\n", x, y);
	mouseCoordinateTranslate(x, y);
	changeCtrlPts();

	glutPostRedisplay();
}

void mousePassiveMotion(int x, int y)
{
	printf("mouse passive motion: %d %d\n", x, y);
	mouseCoordinateTranslate(x, y);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	ctrlPts.push_back({ -2, 1 });
	ctrlPts.push_back({ 0, -2 });
	ctrlPts.push_back({ 2, 2 });
	ctrlPts.push_back({ 4, -1 });

	glutCreateWindow("OpenGL-BezierCurve");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	//glutPassiveMotionFunc(mousePassiveMotion);
	glutMainLoop();

	return 0;
}