
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "cubo.h"

GLfloat worldTranslate[] = { 0.0, 0.0, 0.0 };
GLfloat worldScale[] = { 0.1, 0.1, 0.1 };
GLfloat worldTheta[] = { 0.0, 0.0, 0.0 };

#define NUM_CUBES 100

Cubo cubes[NUM_CUBES];

int tempo = 1000;

void drawGrid()
{
	glColor3f(0.3f, 0.3f, 0.3f);
	glBegin(GL_LINES);

	for (int i = -50; i <= 50; i++) {

		// Lines parallel to X (varying Z)
		glVertex3f(-50.0f, 0.0f, (float)i);
		glVertex3f(+50.0f, 0.0f, (float)i);

		// Lines parallel to Z (varying X)
		glVertex3f((float)i, 0.0f, -50.0f);
		glVertex3f((float)i, 0.0f, +50.0f);
	}

	glEnd();
}

void drawWorldAxis()
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

	drawGrid();
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

	float minX = -50.0f, maxX = 50.0f;
	float minY = -50.0f, maxY = 50.0f;
	float minZ = -50.0f, maxZ = 50.0f;

	for (int i = 0; i < NUM_CUBES; i++) {

		float x = minX + ((float)rand() / RAND_MAX) * (maxX - minX);
		float y = minY + ((float)rand() / RAND_MAX) * (maxY - minY);
		float z = minZ + ((float)rand() / RAND_MAX) * (maxZ - minZ);

		float vel = 0.02 + ((float)rand() / RAND_MAX) * 0.08;   // 0.02–0.10
		float alpha = ((float)rand() / RAND_MAX) * 360.0;       // 0–360°
		float beta = ((float)rand() / RAND_MAX) * 360.0;        // 0–360°

		cubes[i] = newCuboP(
			x, y, z,
			1.0f, 1.0f, 1.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			vel, alpha, beta
		);

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
	case 'a': case 'A': worldTranslate[0] -= 0.01; break;
	case 'w': case 'W': worldTranslate[1] += 0.01; break;
	case 's': case 'S': worldTranslate[1] -= 0.01; break;
	case 'd': case 'D': worldTranslate[0] += 0.01; break;
	case 'q': case 'Q': worldTranslate[2] -= 0.01; break;
	case 'e': case 'E': worldTranslate[2] += 0.01; break;
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

void myTimerFunc(int n) {
	int i = ++n;
	printf("CLOCK: %d\n", i);

	for (int i = 0; i < NUM_CUBES; i++) {

		Cubo c = cubes[i];
		if (c == NULL) continue;

		float vel = getCubeVel(c);
		float a = getCubeAlpha(c) * PI / 180.0;
		float b = getCubeBeta(c) * PI / 180.0;

		float dx = vel * cos(a);
		float dy = vel * sin(a);
		float dz = vel * sin(b);

		updateCubeTranslate(c, dx, dy, dz);

		GLfloat* cubeTranslate = getCubeTranslate(c);

		for (int k = 0; k < 3; k++) {

			if (cubeTranslate[k] > 50.0 || cubeTranslate[k] < -50.0) {
				setCubeVel(c, -vel);
			}
		}
	}


	glutPostRedisplay();
	glutTimerFunc(tempo, myTimerFunc, i);
	return;
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
	glutInitWindowSize(1880, 1040);
	glutCreateWindow("colorcube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(myKeyboardFunc);
	glutSpecialFunc(mySpecialFunc);
	glutTimerFunc(tempo, myTimerFunc, 0);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}
