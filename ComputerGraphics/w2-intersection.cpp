#include "gl/glut.h"
#include <cstdio>
#include <iostream>

struct Vec2 {
    float x, y;
};
struct Vec3 {
    float x, y, z;
};

Vec2 linePt[4] = {
    {0.3f, 0.2f},
    {0.3f, -0.7f},
    {-0.7f, -0.5f},
    {0.5f, 0.0f}
};

bool isNearByZero(float value) { return value * value < 0.000001; }

void getEquationOfLine(const Vec2& p1, const Vec2& p2, Vec3* result) {
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    // ax + by = C
    result->x = dy;
    result->y = -dx;
    result->z = dy * p1.x - dx * p1.y;
}

bool getIntersection(const Vec3& f1, const Vec3& f2, Vec2* result) {
    float a = f1.x, b = f1.y, c = f2.x, d = f2.y, e = f1.z, f = f2.z;
    float k = a * d - b * c;
    if (!isNearByZero(k)) {
        result->x = (d * e - b * f) / k;
        result->y = (-c * e + a * f) / k;
        return true;
    }
    return false;
}

bool isOnLine(const Vec2& pA, const Vec2& pB, const Vec2& pC) {
    Vec2 ab, ac;
    ab.x = pB.x - pA.x; ab.y = pB.y - pA.y;
    ac.x = pC.x - pA.x; ac.y = pC.y - pA.y;

    float value = (ab.x * ac.x + ab.y * ac.y) / (ab.x * ab.x + ab.y * ab.y);
    return 0.0f <= value && value <= 1.0f;
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[0].x, linePt[0].y);
    glVertex2f(linePt[1].x, linePt[1].y);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(linePt[2].x, linePt[2].y);
    glVertex2f(linePt[3].x, linePt[3].y);
    glEnd();

    /* Calculate the interseciton point! */
    float x = .0f, y = .0f;
    Vec3 eq1, eq2;
    getEquationOfLine(linePt[0], linePt[1], &eq1);
    getEquationOfLine(linePt[2], linePt[3], &eq2);
    Vec2 inter;
    if (getIntersection(eq1, eq2, &inter)) {
        if (isOnLine(linePt[0], linePt[1], inter) && isOnLine(linePt[2], linePt[3], inter)) {
            glColor3f(0.0, 1.0, 0.0);
            glPointSize(10.0);
            glBegin(GL_POINTS);
            glVertex2f(inter.x, inter.y); /* Need to change the value. */
            glEnd();
        }
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) { 

    switch (key) {
	case 'w':
	    linePt[0].y += 0.1f;
	    linePt[1].y += 0.1f;
	    break;
	case 's':
	    linePt[0].y -= 0.1f;
	    linePt[1].y -= 0.1f;
	    break;
	case 'a':
	    linePt[0].x -= 0.1f;
	    linePt[1].x -= 0.1f;
	    break;
	case 'd':
	    linePt[0].x += 0.1f;
	    linePt[1].x += 0.1f;
	    break;
	case 27: // ESC
	    exit(0);
	    break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);


    glutCreateWindow("OpenGL-Intersection");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}