
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "cubo.h"

GLfloat worldTranslate[] = { 0.0, 0.0, 0.0 };
GLfloat worldScale[] = { 1.0, 1.0, 1.0 };
GLfloat worldTheta[] = { 0.0, 0.0, 0.0 };

#define NUM_CUBES 100

Cubo cubes[NUM_CUBES];

void drawWorldAxis(void)
{
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(5.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 5.0);
	glEnd();
}

void drawFunc() {

	glPushMatrix();

	glTranslatef(worldTranslate[0], worldTranslate[1], worldTranslate[2]);
	glRotatef(worldTheta[0], 1.0, 0.0, 0.0);
	glRotatef(worldTheta[1], 0.0, 1.0, 0.0);
	glRotatef(worldTheta[2], 0.0, 0.0, 1.0);
	glScalef(worldScale[0], worldScale[1], worldScale[2]);

	drawWorldAxis();

	for (int i = 0; i < NUM_CUBES; i++) {
		drawCube(cubes[i]);
	}

	glPopMatrix();
}

void genCubes() {

	for (int i = 0; i < NUM_CUBES; i++) {
		if (cubes[i] != NULL) deleteCube(cubes[i]);
	}

	float minX = -50.0, maxX = 50.0;
	float minY = -50.0, maxY = 50.0;
	float minZ = -50.0, maxZ = 50.0;

	for (int i = 0; i < NUM_CUBES; i++) {
		float x = minX + ((float)rand() / RAND_MAX) * (maxX - minX);
		float y = minY + ((float)rand() / RAND_MAX) * (maxY - minY);
		float z = minZ + ((float)rand() / RAND_MAX) * (maxZ - minZ);

		cubes[i] = newCuboP(x, y, z, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

		setCubeColor(cubes[i], (float)i / NUM_CUBES, 1.0 - (float)i / NUM_CUBES, 0.5);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	drawFunc();
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{
	return;
}

void myKeyboardFunc(char key, int x, int y) {
	switch (key) {
	case '+': for (int i = 0; i < 3; i++) worldScale[i] += 0.05; break;
	case '-': for (int i = 0; i < 3; i++) worldScale[i] -= 0.05;	break;
	case 'a': case 'A': worldTranslate[0] -= 0.05; break;
	case 'w': case 'W': worldTranslate[1] += 0.05; break;
	case 's': case 'S': worldTranslate[1] -= 0.05; break;
	case 'd': case 'D': worldTranslate[0] += 0.05; break;
	case 'q': case 'Q': worldTranslate[2] -= 0.05; break;
	case 'e': case 'E': worldTranslate[2] += 0.05; break;
	case 'r': case 'R': for (int i = 0; i < 3; i++) { worldTranslate[i] = 0.0; worldScale[i] = 1.0; worldTheta[i] = 0.0; } break;
	case 'g': case 'G': genCubes();
	}
	glutPostRedisplay();
}

void mySpecialFunc(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_LEFT:		worldTheta[1] -= 10.0; break;
	case GLUT_KEY_RIGHT:	worldTheta[1] += 10.0; break;
	case GLUT_KEY_UP:		worldTheta[0] -= 10.0; break;
	case GLUT_KEY_DOWN:		worldTheta[0] += 10.0; break;
	}

	for (int i = 0; i < 3; i++) {
		if (worldTheta[i] > 360.0) worldTheta[i] -= 360.0;
		if (worldTheta[i] < 0) worldTheta[i] += 360.0;
	}

	glutPostRedisplay();
}

void myReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w,
			2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-2.0 * (GLfloat)w / (GLfloat)h,
			2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) 
{

	for (int i = 0; i < NUM_CUBES; i++) {
		cubes[i] = NULL;
	}
	genCubes();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialFunc);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}
