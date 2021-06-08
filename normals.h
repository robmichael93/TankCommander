#ifndef ___NORMALS_H__
#define ___NORMALS_H__


#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <math.h>

void normalize (GLfloat v[3]);

void normCrossProduct (GLfloat v1[3], GLfloat v2[3], GLfloat out[3]);

void findUnitNormal (GLfloat v0[3], GLfloat v1[3], GLfloat v2[3], GLfloat xProd[3]);

void makeShadowMatrix(GLfloat points[3][3], GLfloat LightPos[4], GLfloat destMat[4][4]);

#endif