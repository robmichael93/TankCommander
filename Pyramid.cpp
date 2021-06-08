#include "stdafx.h"
#include "Pyramid.h"
#include "normals.h"
#include <math.h>

//---------------------------------------------------------------------
// Method: init
// Function: Initializes the class data members height and width
// Parameters: 
//			h - desired height for the pyramid object
//			w - desired width for the pyramid object
//				
// Returns: Void
// Called By: 
// Calls: None
//---------------------------------------------------------------------



void Pyramid::init(GLfloat h, GLfloat w, GLfloat xPos, GLfloat zPos)
{
   x = xPos;
   z = zPos;
   height = h;
   width = w;
   radius = (float) sqrt(2 * width * width) / 2.0f;

   forwardCollided = false;
   backwardCollided = false;

   float p[5][3]; // storage array for the points on the pyramid
   float norm[3]; // array for unit normal

   p[0][0] = -width/2.0f; // p[0] -0+
   p[0][1] = 0.0f;
   p[0][2] = width/2.0f;

   p[1][0] = -width/2.0f; // p[1] -0-
   p[1][1] = 0.0f;
   p[1][2] = -width/2.0f;

   p[2][0] = width/2.0f;  // p[2] +0-
   p[2][1] = 0.0f;
   p[2][2] = -width/2.0f;

   p[3][0] = width/2.0f;  // p[3] +0+
   p[3][1] = 0.0f;
   p[3][2] = width/2.0f;

   p[4][0] = 0.0f;        // p[4] 0h0
   p[4][1] = height;
   p[4][2] = 0.0f;

   pyramidList = glGenLists(1);

   glNewList(pyramidList, GL_COMPILE);
      glBegin(GL_QUADS);
         glNormal3f(0.0, -1.0, 0.0);
         glVertex3fv(p[0]);
         glVertex3fv(p[1]);
         glVertex3fv(p[2]);
         glVertex3fv(p[3]);
      glEnd();
      glBegin(GL_TRIANGLE_FAN);
         findUnitNormal(p[4], p[0], p[3], norm);
         glNormal3fv(norm);
         glVertex3fv(p[4]);
         glVertex3fv(p[0]);
         glVertex3fv(p[3]);
         findUnitNormal(p[4], p[3], p[2], norm);
         glNormal3fv(norm);
         glVertex3fv(p[4]);
         glVertex3fv(p[3]);
         glVertex3fv(p[2]);
         findUnitNormal(p[4], p[2], p[1], norm);
         glNormal3fv(norm);
         glVertex3fv(p[4]);
         glVertex3fv(p[2]);
         glVertex3fv(p[1]);
         findUnitNormal(p[4], p[1], p[0], norm);
         glNormal3fv(norm);
         glVertex3fv(p[4]);
         glVertex3fv(p[1]);
         glVertex3fv(p[0]);
      glEnd();
   glEndList();
} // end init


//---------------------------------------------------------------------
// Method: draw
// Function: Draws a pyramid centered at the origin with the height and 
//			    width given by the class data members. The pyramid is 
//			    oriented in the xz plane pointing along the positive y axis.
// Parameters: 
//			None
//				
// Returns: Void
// Called By: 
// Calls: None
//---------------------------------------------------------------------
void Pyramid::draw()
{
   glCallList(pyramidList);
} // end draw

GLfloat Pyramid::getHeight() {
   return height;
} // end getHeight

GLfloat Pyramid::getWidth() {
   return width;
} // edn getWidth


GLfloat Pyramid::getRadius() {
   return radius;
} // end getRadius


GLfloat Pyramid::getX() {
   return x;
} // end getX


GLfloat Pyramid::getZ() {
   return z;
} // end getZ


void Pyramid::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void Pyramid::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void Pyramid::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void Pyramid::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardCollide


bool Pyramid::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool Pyramid::isBackwardCollided() {
   return backwardCollided;
} // end isBackwardCollided


