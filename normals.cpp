#include <math.h>
#include "stdafx.h"
#include "normals.h"

void normalize (GLfloat v[3]) 
{
	GLfloat length = float(sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));

	if (length > 0.0) {
		v[0] /= length;
		v[1] /= length;
		v[2] /= length;
	}
}

void normCrossProduct (GLfloat v1[3], GLfloat v2[3], GLfloat out[3]) 
{
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];

	normalize(out);
}


void findUnitNormal (GLfloat v0[3], GLfloat v1[3], GLfloat v2[3], GLfloat xProd[3]) 
{
	GLfloat vector1[3] = {v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2]};
   // changed to v2 - v0 vice v2 - v1
	GLfloat vector2[3] = {v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]};

	normCrossProduct(vector1, vector2, xProd);
}

void makeShadowMatrix(GLfloat points[3][3], GLfloat LightPos[4], GLfloat destMat[4][4])
{
	GLfloat planeCoeff[4];
	GLfloat dot;

	// Flind the plane equation coefficients
	// Find the first three coefficients the same way
	// a normal is found
	findUnitNormal(&points[0][0], &points[1][0], &points[2][0], planeCoeff);

	// Find the last coefficient by back substitutions
	planeCoeff[3] = - ((planeCoeff[0]*points[2][0]) +
						(planeCoeff[1]*points[2][1]) +
						(planeCoeff[2]*points[2][2]));

	// Dot product of plane and Light position
	dot = planeCoeff[0] * LightPos[0] + 
		planeCoeff[1] * LightPos[1] +
		planeCoeff[2] * LightPos[2] +
		planeCoeff[3] * LightPos[3];

	// Now do the projection
	// First column
	destMat[0][0] =  dot -  LightPos[0] * planeCoeff[0];
	destMat[1][0] =  0.0f - LightPos[0] * planeCoeff[1];
	destMat[2][0] =  0.0f - LightPos[0] * planeCoeff[2];
	destMat[3][0] =  0.0f - LightPos[0] * planeCoeff[3];

	// Second column
	destMat[0][1] =  0.0f - LightPos[1] * planeCoeff[0];
	destMat[1][1] =  dot -  LightPos[1] * planeCoeff[1];
	destMat[2][1] =  0.0f - LightPos[1] * planeCoeff[2];
	destMat[3][1] =  0.0f - LightPos[1] * planeCoeff[3];

	// Third column
	destMat[0][2] =  0.0f - LightPos[2] * planeCoeff[0];
	destMat[1][2] =  0.0f - LightPos[2] * planeCoeff[1];
	destMat[2][2] =  dot -  LightPos[2] * planeCoeff[2];
	destMat[3][2] =  0.0f - LightPos[2] * planeCoeff[3];

	// Fourth column
	destMat[0][3] =  0.0f - LightPos[3] * planeCoeff[0];
	destMat[1][3] =  0.0f - LightPos[3] * planeCoeff[1];
	destMat[2][3] =  0.0f - LightPos[3] * planeCoeff[2];
	destMat[3][3] =  dot -  LightPos[3] * planeCoeff[3];

} // end makeShadowMatrix