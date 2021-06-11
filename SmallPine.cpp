#include "stdafx.h"
#include "SmallPine.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------


GLUquadricObj *SmallPineObj;

void SmallPine::init(GLfloat xPos, GLfloat zPos)
{
   x = xPos;
   z = zPos;
   radius = 4.0f;
   damageCapacity = 5;
   pointValue = 5;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;

   SmallPineObj = gluNewQuadric();

   SmallPineList = glGenLists(2);

   glNewList(SmallPineList, GL_COMPILE);	

// HULL

   	glColor3f(0.42, 0.64, 0.38);    

	glBegin(GL_TRIANGLES);       
		glVertex3f(-3.0, 5.0, 0.0);
		glVertex3f(3.0, 5.0, 0.0);
		glVertex3f(0.0, 8.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);  
		glVertex3f(0.0, 8.0, 0.0);
		glVertex3f(3.0, 5.0, 0.0);
		glVertex3f(-3.0, 5.0, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
		glVertex3f(-3.5, 3.5, 0.0);
		glVertex3f(3.5, 3.5, 0.0);
		glVertex3f(0.0, 6.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);    
		glVertex3f(0.0, 6.0, 0.0);
		glVertex3f(3.5, 3.5, 0.0);
		glVertex3f(-3.5, 3.5, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
	glVertex3f(-4.0, 1.5, 0.0);
		glVertex3f(4.0, 1.5, 0.0);
		glVertex3f(0.0, 4.5, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);   
		glVertex3f(0.0, 4.5, 0.0);
		glVertex3f(4.0, 1.5, 0.0);
		glVertex3f(-4.0, 1.5, 0.0);	
	glEnd();

	glPushMatrix();
		glRotatef(90, 0.0, 1.0, 0.0);

	glBegin(GL_TRIANGLES);       
		glVertex3f(-3.0, 5.0, 0.0);
		glVertex3f(3.0, 5.0, 0.0);
		glVertex3f(0.0, 8.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);  
		glVertex3f(0.0, 8.0, 0.0);
		glVertex3f(3.0, 5.0, 0.0);
		glVertex3f(-3.0, 5.0, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
		glVertex3f(-3.5, 3.5, 0.0);
		glVertex3f(3.5, 3.5, 0.0);
		glVertex3f(0.0, 6.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);    
		glVertex3f(0.0, 6.0, 0.0);
		glVertex3f(3.5, 3.5, 0.0);
		glVertex3f(-3.5, 3.5, 0.0);		
	glEnd();

	glBegin(GL_TRIANGLES);       
	glVertex3f(-4.0, 1.5, 0.0);
		glVertex3f(4.0, 1.5, 0.0);
		glVertex3f(0.0, 4.5, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);   
		glVertex3f(0.0, 4.5, 0.0);
		glVertex3f(4.0, 1.5, 0.0);
		glVertex3f(-4.0, 1.5, 0.0);	
	glEnd();
	glPopMatrix();

		glColor3f(0.65, 0.41, 0.36);

	glPushMatrix(); 
     glRotatef(90.0, -1.0, 0.0, 0.0);     
     gluCylinder(SmallPineObj, 0.25, 0.25, 1.5, 10.0, 10.0);
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
void SmallPine::draw(){ 
   glCallList(SmallPineList); 
} // end draw


GLfloat SmallPine::getRadius() {
   return radius;
} // end getRadius


GLfloat SmallPine::getX() {
   return x;
} // end getX


GLfloat SmallPine::getZ() {
   return z;
} // end getZ


bool SmallPine::isDestroyed() {
   return destroyed;
} // end isDestroyed


void SmallPine::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void SmallPine::destroy() {
   destroyed = true;
} // end destroy


Explosion* SmallPine::getExplosion() {
   return explosion;
} // end getExplosion


void SmallPine::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


void SmallPine::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void SmallPine::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void SmallPine::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void SmallPine::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardCollide


bool SmallPine::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool SmallPine::isBackwardCollided() {
   return backwardCollided;
} // end isForwardCollided


int SmallPine::getPointValue() {
   return pointValue;
} // end getPointValue








