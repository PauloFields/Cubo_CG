#ifndef __CUBO_H__
#define __CUBO_H__

#define PI 3.141592653589

typedef struct cubo* Cubo;

Cubo newCubo();
Cubo newCuboP(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
Cubo newCuboC(Cubo);

GLfloat* getCubeTranslate(Cubo);
GLfloat* getCubeScale(Cubo);
GLfloat* getCubeTheta(Cubo);
GLfloat* getCubeDir(Cubo);
GLfloat* getCubeVel(Cubo);
GLfloat* getCubeColor(Cubo);

void setCubeTranslate(Cubo c, GLfloat tx, GLfloat ty, GLfloat tz);
void setCubeScale(Cubo c, GLfloat sx, GLfloat sy, GLfloat sz);
void setCubeTheta(Cubo c, GLfloat rx, GLfloat ry, GLfloat rz);
void setCubeDir(Cubo c, GLfloat dx, GLfloat dy, GLfloat dz);
void setCubeVel(Cubo c, GLfloat vx, GLfloat vy, GLfloat vz);
void setCubeColor(Cubo c, GLfloat r, GLfloat g, GLfloat b);
void setCubeShow(Cubo c, int show);
void setCubeShowAxis(Cubo c, int showAxis);

void deleteCube(Cubo);

void updateCubeTranslate(Cubo, float, float, float);
void updateCubeScale(Cubo, float, float, float);

int collisionCheck(Cubo a, Cubo b);

void printCube(Cubo);
void drawCube(Cubo);

#endif
