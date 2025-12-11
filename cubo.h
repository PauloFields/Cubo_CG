#ifndef __CUBO_H__
#define __CUBO_H__

#define PI 3.141592653589

typedef struct cubo* Cubo;

Cubo newCube();
Cubo newCubeP(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
Cubo newCubeC(Cubo);

GLfloat* getCubeTranslate(Cubo);
GLfloat* getCubeScale(Cubo);
GLfloat* getCubeTheta(Cubo);
GLfloat* getCubeColor(Cubo);
GLfloat getCubeAlpha(Cubo);
GLfloat getCubeBeta(Cubo);
GLfloat getCubeVel(Cubo);
GLfloat getCubeShow(Cubo);
GLfloat getCubeShowAxis(Cubo);
GLfloat getCubeWireframe(Cubo);

void setCubeTranslate(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeScale(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeTheta(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeColor(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeAlpha(Cubo, GLfloat);
void setCubeBeta(Cubo, GLfloat);
void setCubeVel(Cubo, GLfloat);
void setCubeShow(Cubo, GLint);
void setCubeShowAxis(Cubo, GLint);
void setCubeWireframe(Cubo, GLint);

void deleteCube(Cubo);

void updateCubeTranslate(Cubo, GLfloat, GLfloat, GLfloat);
void updateCubeScale(Cubo, GLfloat, GLfloat, GLfloat);
void updateCube(Cubo, GLfloat);

int collisionCheck(Cubo a, Cubo b);

void printCube(Cubo);
void drawCube(Cubo);

#endif
