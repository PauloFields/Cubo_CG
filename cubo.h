#ifndef __CUBO_H__
#define __CUBO_H__

#define PI 3.141592653589

typedef struct cubo* Cubo;

Cubo newCubo();
/**
Translate / Scale / Theta / Color / Vel / Alpha / Beta
*/
Cubo newCuboP(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
Cubo newCuboC(Cubo);

GLfloat* getCubeTranslate(Cubo);
GLfloat* getCubeScale(Cubo);
GLfloat* getCubeTheta(Cubo);
GLfloat* getCubeColor(Cubo);
GLfloat getCubeAlpha(Cubo);
GLfloat getCubeBeta(Cubo);
GLfloat getCubeVel(Cubo);
GLfloat getCubeShow(Cubo);
GLfloat getCubeShowAxis(Cubo);

void setCubeTranslate(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeScale(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeTheta(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeColor(Cubo, GLfloat, GLfloat, GLfloat);
void setCubeAlpha(Cubo, GLfloat);
void setCubeBeta(Cubo, GLfloat);
void setCubeVel(Cubo, GLfloat);
void setCubeShow(Cubo, int);
void setCubeShowAxis(Cubo, int);

void deleteCube(Cubo);

void updateCubeTranslate(Cubo, float, float, float);
void updateCubeScale(Cubo, float, float, float);

int collisionCheck(Cubo a, Cubo b);

void printCube(Cubo);
void drawCube(Cubo);

#endif
