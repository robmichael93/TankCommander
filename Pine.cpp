#include "stdafx.h"
#include "Pine.h"
#include "OpenGLDoc.h"
#include "OpenGLView.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------


GLUquadricObj *PineObj;

void Pine::init(GLfloat xPos, GLfloat zPos)
{
   x = xPos;
   z = zPos;
   radius = 5.0f;
   damageCapacity = 10;
   pointValue = 10;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;

   PineObj = gluNewQuadric();

   PineList = glGenLists(2);

   glNewList(PineList, GL_COMPILE);	

// HULL

   	glColor3f(0.42, 0.64, 0.38);    

	glBegin(GL_TRIANGLES);       
		glVertex3f(-4.0, 8.0, 0.0);
		glVertex3f(4.0, 8.0, 0.0);
		glVertex3f(0.0, 12.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);  
		glVertex3f(0.0, 12.0, 0.0);
		glVertex3f(4.0, 8.0, 0.0);
		glVertex3f(-4.0, 8.0, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
		glVertex3f(-4.5, 6.0, 0.0);
		glVertex3f(4.5, 6.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);    
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(4.5, 6.0, 0.0);
		glVertex3f(-4.5, 6.0, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
	glVertex3f(-5.0, 3.5, 0.0);
		glVertex3f(5.0, 3.5, 0.0);
		glVertex3f(0.0, 8.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);   
		glVertex3f(0.0, 8.0, 0.0);
		glVertex3f(5.0, 3.5, 0.0);
		glVertex3f(-5.0, 3.5, 0.0);	
	glEnd();

	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);       
		glVertex3f(-4.0, 8.0, 0.0);
		glVertex3f(4.0, 8.0, 0.0);
		glVertex3f(0.0, 12.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);  
		glVertex3f(0.0, 12.0, 0.0);
		glVertex3f(4.0, 8.0, 0.0);
		glVertex3f(-4.0, 8.0, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
		glVertex3f(-4.5, 6.0, 0.0);
		glVertex3f(4.5, 6.0, 0.0);
		glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);    
		glVertex3f(0.0, 10.0, 0.0);
		glVertex3f(4.5, 6.0, 0.0);
		glVertex3f(-4.5, 6.0, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
	glVertex3f(-5.0, 3.5, 0.0);
		glVertex3f(5.0, 3.5, 0.0);
		glVertex3f(0.0, 8.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);   
		glVertex3f(0.0, 8.0, 0.0);
		glVertex3f(5.0, 3.5, 0.0);
		glVertex3f(-5.0, 3.5, 0.0);	
	glEnd();

	glPopMatrix();

		glColor3f(0.65, 0.41, 0.36);

	glPushMatrix(); 
     glRotatef(90.0, -1.0, 0.0, 0.0);     
     gluCylinder(PineObj, 0.5, 0.5, 3.5, 10.0, 10.0);
    glPopMatrix();


	glEndList();

} // end init


//---------------------------------------------------------------------
// Method: 
// Function: 
// Parameters: 			
// Returns: 
// Called By: 
// Calls: 
//---------------------------------------------------------------------
void Pine::draw(){ 
   glCallList(PineList); 
} // end draw


GLfloat Pine::getRadius() {
   return radius;
} // end getRadius


GLfloat Pine::getX() {
   return x;
} // end getX


GLfloat Pine::getZ() {
   return z;
} // end getZ


bool Pine::isDestroyed() {
   return destroyed;
} // end isDestroyed


void Pine::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void Pine::destroy() {
   destroyed = true;
} // end destroy


Explosion* Pine::getExplosion() {
   return explosion;
} // end getExplosion


void Pine::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


void Pine::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void Pine::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void Pine::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void Pine::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardCollide


bool Pine::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool Pine::isBackwardCollided() {
   return backwardCollided;
} // end isBackwardCollided


int Pine::getPointValue() {
   return pointValue;
} // end getPointValue








