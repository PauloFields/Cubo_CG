
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "cubo.h"

GLfloat worldTranslate[] = { 0.0, 0.0, 0.0 };
GLfloat worldScale[] = { 1.0, 1.0, 1.0 };
GLfloat worldTheta[] = { 0.0, 0.0, 0.0 };

#define NUM_CUBES 1
#define WINDOWWIDTH 1000
#define WINDOWHEIGHT 1000

#define WORLDCUBESIZE 2

Cubo cubes[NUM_CUBES];
Cubo worldCube;

#define FPS 60;
GLint tempo = 1000 / FPS; // tempo por divisão


void drawWorldCube()
{
	glColor3f(1.0, 1.0, 1.0);
	drawCube(worldCube);
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

	drawWorldCube();
	drawWorldAxis();

	for (int i = 0; i < NUM_CUBES; i++) {
		draw(cubes[i]);
	}

	glPopMatrix();
}

void genCubes() {


	for (int i = 0; i < NUM_CUBES; i++) {
		if (cubes[i] != NULL) deleteCube(cubes[i]);
	}

	float minX = -WORLDCUBESIZE / 2, maxX = WORLDCUBESIZE / 2;
	float minY = -WORLDCUBESIZE / 2, maxY = WORLDCUBESIZE / 2;
	float minZ = -WORLDCUBESIZE / 2, maxZ = WORLDCUBESIZE / 2;

	for (int i = 0; i < NUM_CUBES; i++) {

		float x = minX + ((float)rand() / RAND_MAX) * (maxX - minX);
		float y = minY + ((float)rand() / RAND_MAX) * (maxY - minY);
		float z = minZ + ((float)rand() / RAND_MAX) * (maxZ - minZ);

		float vel = 0 *( 0.01 + ((float)rand() / RAND_MAX) * 0.05);   // 0.01–0.6
		float alpha = ((float)rand() / RAND_MAX) * 360.0;       // 0–360°
		float beta = ((float)rand() / RAND_MAX) * 360.0;        // 0–360°

		cubes[i] = newCubeP(
			x, y, z,
			0.1, 0.1, 0.1,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
			vel, alpha, beta,
			CUBO
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
		if (cubes[i] != NULL) updateCube(cubes[i], WORLDCUBESIZE, tempo);
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

	worldCube = newCubeP(
		0, 0, 0,
		1, 1, 1,
		0, 0, 0,
		1, 1, 1,
		0, 0, 0, CUBO
	);

	setCubeWireframe(worldCube, 1);

	for (int i = 0; i < NUM_CUBES; i++) {
		cubes[i] = NULL;
	}

	genCubes();

	deleteCube(cubes[0]);

	cubes[0] = newCubeP(
		0, 0, 0,
		1.0, 1.0, 1.0,
		0.0, 0.0, 0.0,
		1.0, 1.0, 1.0,
		0.0, 0.0, 0,
		BONECO
	);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
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
