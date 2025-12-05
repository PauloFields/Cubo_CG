#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "cubo.h"

GLfloat vertices[][3] = {
    { -1.0, -1.0, -1.0},
    {  1.0, -1.0, -1.0},
    {  1.0,  1.0, -1.0},
    { -1.0,  1.0, -1.0},
    { -1.0, -1.0,  1.0},
    {  1.0, -1.0,  1.0},
    {  1.0,  1.0,  1.0},
    { -1.0,  1.0,  1.0}};
GLfloat normals[][3] = {
    { -1.0, -1.0, -1.0},
    {  1.0, -1.0, -1.0},
    {  1.0,  1.0, -1.0},
    { -1.0,  1.0, -1.0},
    { -1.0, -1.0,  1.0},
    {  1.0, -1.0,  1.0},
    {  1.0,  1.0,  1.0},
    { -1.0,  1.0,  1.0}};

struct cubo {
    GLfloat cubeTranslate[3];
    GLfloat cubeScale[3];
    GLfloat cubeTheta[3];
    GLfloat color[3];
    GLfloat alpha; // angulo xy
    GLfloat beta;  // angulo xz
    GLfloat vel;
    int show, showAxis;
};

Cubo newCubo() {
    Cubo c = malloc(sizeof(struct cubo));
    for (int i = 0; i < 3; i++) {
        c->cubeTranslate[i] = 0.0;
        c->cubeScale[i] = 1.0;
        c->cubeTheta[i] = 0.0;
        c->color[i] = 1.0;
    }
    c->alpha = 0.0;
    c->beta = 0.0;
    c->vel = 0.0;
    c->show = 1;
    c->showAxis = 0;
    return c;
}

Cubo newCuboP(GLfloat tx, GLfloat ty, GLfloat tz,
    GLfloat sx, GLfloat sy, GLfloat sz,
    GLfloat rx, GLfloat ry, GLfloat rz,
    GLfloat r, GLfloat g, GLfloat b,
    GLfloat vel, GLfloat alpha, GLfloat beta) {

    Cubo c = malloc(sizeof(struct cubo));
    c->cubeTranslate[0] = tx;
    c->cubeTranslate[1] = ty;
    c->cubeTranslate[2] = tz;
    c->cubeScale[0] = sx;
    c->cubeScale[1] = sy;
    c->cubeScale[2] = sz;
    c->cubeTheta[0] = rx;
    c->cubeTheta[1] = ry;
    c->cubeTheta[2] = rz;
    c->color[0] = r;
    c->color[1] = g;
    c->color[2] = b;
    c->alpha = alpha;
    c->beta = beta;
    c->vel = vel;
    c->show = 1;
    c->showAxis = 0;
    return c;
}

Cubo newCuboC(Cubo src) {
    Cubo c = malloc(sizeof(struct cubo));
    for (int i = 0; i < 3; i++) {
        c->cubeTranslate[i] = src->cubeTranslate[i];
        c->cubeScale[i] = src->cubeScale[i];
        c->cubeTheta[i] = src->cubeTheta[i];
        c->color[i] = src->color[i];
    }
    c->alpha = src->alpha;
    c->beta = src->beta;
    c->vel = src->vel;
    c->show = src->show;
    c->showAxis = src->showAxis;
    return c;
}

GLfloat* getCubeTranslate(Cubo c) { return c->cubeTranslate; }
GLfloat* getCubeScale(Cubo c) { return c->cubeScale; }
GLfloat* getCubeTheta(Cubo c) { return c->cubeTheta; }
GLfloat* getCubeColor(Cubo c) { return c->color; }
GLfloat getCubeAlpha(Cubo c) { return c->alpha; }
GLfloat getCubeBeta(Cubo c) { return c->beta; }
GLfloat getCubeVel(Cubo c) { return c->vel; }
GLfloat getCubeShow(Cubo c) { return c->show; }
GLfloat getCubeShowAxis(Cubo c) { return c->showAxis; }

void setCubeTranslate(Cubo c, GLfloat tx, GLfloat ty, GLfloat tz) { c->cubeTranslate[0] = tx; c->cubeTranslate[1] = ty; c->cubeTranslate[2] = tz; }
void setCubeScale(Cubo c, GLfloat sx, GLfloat sy, GLfloat sz) { c->cubeScale[0] = sx; c->cubeScale[1] = sy; c->cubeScale[2] = sz; }
void setCubeTheta(Cubo c, GLfloat rx, GLfloat ry, GLfloat rz) { c->cubeTheta[0] = rx; c->cubeTheta[1] = ry; c->cubeTheta[2] = rz; }
void setCubeColor(Cubo c, GLfloat r, GLfloat g, GLfloat b) { c->color[0] = r; c->color[1] = g; c->color[2] = b; }
void setCubeAlpha(Cubo c, GLfloat alpha) { c->alpha = alpha; }
void setCubeBeta(Cubo c, GLfloat beta) { c->beta = beta; }
void setCubeVel(Cubo c, GLfloat vel) { c->vel = vel; }
void setCubeShow(Cubo c, int show) { c->show = show; }
void setCubeShowAxis(Cubo c, int showAxis) { c->showAxis = showAxis; }

void deleteCube(Cubo c) {
    free(c);
}

void updateCubeTranslate(Cubo c, float dx, float dy, float dz) {
    c->cubeTranslate[0] += dx;
    c->cubeTranslate[1] += dy;
    c->cubeTranslate[2] += dz;
}

void updateCubeScale(Cubo c, float sx, float sy, float sz) {
    c->cubeScale[0] = sx;
    c->cubeScale[1] = sy;
    c->cubeScale[2] = sz;
}

int collisionCheck(Cubo a, Cubo b) {
    for (int i = 0; i < 3; i++) {
        float da = a->cubeTranslate[i] - b->cubeTranslate[i];
        float sa = a->cubeScale[i];
        float sb = b->cubeScale[i];
        if (abs(da) > sa + sb) return 0;
    }
    return 1;
}

void printCube(Cubo c) {
    printf("position\t[%.2f, %.2f, %.2f]\n", c->cubeTranslate[0], c->cubeTranslate[1], c->cubeTranslate[2]);
    printf("scale\t[%.2f, %.2f, %.2f]\n", c->cubeScale[0], c->cubeScale[1], c->cubeScale[2]);
    printf("rotation\t[%.2f, %.2f, %.2f]\n", c->cubeTheta[0], c->cubeTheta[1], c->cubeTheta[2]);
    
    if(c->show) printf("Hidden: No\n");
    else printf("Hidden: Yes\n");

    if (c->showAxis) printf("Axis: On\n");
    else printf("Axis: Off\n");
}

void polygon(int v0, int v1, int v2, int v3, Cubo cube)
{
    glColor3fv(cube->color);

    glBegin(GL_POLYGON);

    glNormal3fv(normals[v0]);
    glVertex3fv(vertices[v0]);

    glNormal3fv(normals[v1]);
    glVertex3fv(vertices[v1]);

    glNormal3fv(normals[v2]);
    glVertex3fv(vertices[v2]);

    glNormal3fv(normals[v3]);
    glVertex3fv(vertices[v3]);

    glEnd();
}

void drawCube(Cubo c) {

    if (!c->show) return;

    glPushMatrix();

    glTranslatef(c->cubeTranslate[0], c->cubeTranslate[1], c->cubeTranslate[2]);
    glRotatef(c->cubeTheta[0], 1, 0, 0);
    glRotatef(c->cubeTheta[1], 0, 1, 0);
    glRotatef(c->cubeTheta[2], 0, 0, 1);
    glScalef(c->cubeScale[0], c->cubeScale[1], c->cubeScale[2]);
    glColor3fv(c->color);

    polygon(0, 3, 2, 1, c);
    polygon(2, 3, 7, 6, c);
    polygon(0, 4, 7, 3, c);
    polygon(1, 2, 6, 5, c);
    polygon(4, 5, 6, 7, c);
    polygon(0, 1, 5, 4, c);

    glPopMatrix();
}
