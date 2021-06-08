#include "stdafx.h"
#include "Friend.h"
#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "normals.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------

GLfloat Friend::maxFwdSpeed = 2.0f;
GLfloat Friend::maxRevSpeed = -0.5f;

GLUquadricObj *qobj;

void Friend::init(int camoTex)
{
   speed = 0.0f;
   radius = 5.0f;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;
   damageCapacity = 30;
   pointValue = 500;
   shells = 20;
   bullets = 1000;
	camoTexture = camoTex;
   x = y = z = azimuth = rotationX = rotationY = 0.0f;
   mgLatch = false;
   respawned = false;

   float p[6][3]; // array of points for the front slope
   float norm[3];

   qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
   gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);	

   FriendList = glGenLists(2);

   glNewList(FriendList, GL_COMPILE);	

	// enable texture mapping for the friendly tank
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, camoTexture);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   // HULL

		glBegin(GL_POLYGON);
         glNormal3f(0.0, 0.0, 1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(-4.0, 2.0, 3.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(-4.0, 0.0, 3.0);
         glTexCoord2f(2.0, 0.0);
			glVertex3f(4.0, 0.0, 3.0);
         glTexCoord2f(2.0, 1.0);
			glVertex3f(4.0, 2.0, 3.0);
      glEnd();
		glBegin(GL_POLYGON);
         glNormal3f(-1.0, 0.0, 0.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(-4.0, 2.0, -3.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(-4.0, 0.0, -3.0);
         glTexCoord2f(2.0, 0.0);
			glVertex3f(-4.0, 0.0, 3.0);
         glTexCoord2f(2.0, 1.0);
			glVertex3f(-4.0, 2.0, 3.0);
      glEnd();
		glBegin(GL_POLYGON);
         glNormal3f(0.0, 0.0, -1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(4.0, 2.0, -3.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(4.0, 0.0, -3.0);
         glTexCoord2f(2.0, 0.0);
			glVertex3f(-4.0, 0.0, -3.0);
         glTexCoord2f(2.0, 1.0);
			glVertex3f(-4.0, 2.0, -3.0);
		glEnd();

	//DECK

		glBegin(GL_POLYGON);
         glNormal3f(0.0, 1.0, 0.0);
         glTexCoord2f(3.0, 0.0);
			glVertex3f(-4.0, 2.0, 3.0);
         glTexCoord2f(4.0, 3.0);
			glVertex3f(4.0, 2.0, 3.0);
         glTexCoord2f(0.0, 3.0);
			glVertex3f(4.0, 2.0, -3.0);
         glTexCoord2f(0.0, 3.0);
			glVertex3f(-4.0, 2.0, -3.0);
		glEnd();

		glBegin(GL_POLYGON);       
			glVertex3f(-4.0, 0.0, -3.0);
			glVertex3f(4.0, 0.0, -3.0);
			glVertex3f(4.0, 0.0, 3.0);
			glVertex3f(-4.0, 0.0, 3.0);
			
		glEnd();

	// TURRET

		glColor3f(1.0, 0.0, 0.0);

		glBegin(GL_QUADS);
         glNormal3f(0.0, 0.0, 1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(-3.0, 3.0, 2.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(-3.0, 2.0, 2.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(1.0, 2.0, 2.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(1.0, 3.0, 2.0);
      glEnd();
      glBegin(GL_QUADS);
         glNormal3f(0.707f, 0.0, 0.707f);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(1.0, 3.0, 2.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(1.0, 2.0, 2.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(2.0, 2.0, 1.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(2.0, 3.0, 1.0);
      glEnd();
      glBegin(GL_QUADS);
         glNormal3f(1.0, 0.0, 0.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(2.0, 3.0, 1.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(2.0, 2.0, 1.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(2.0, 2.0, -1.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(2.0, 3.0, -1.0);
      glEnd();
      glBegin(GL_QUADS);
         glNormal3f(0.707f, 0.0, -0.707f);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(2.0, 3.0, -1.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(2.0, 2.0, -1.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(1.0, 2.0, -2.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(1.0, 3.0, -2.0);
      glEnd();
      glBegin(GL_QUADS);
         glNormal3f(0.0, 0.0, -1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(1.0, 3.0, -2.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(1.0, 2.0, -2.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(-3.0, 2.0, -2.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(-3.0, 3.0, -2.0);
      glEnd();
      glBegin(GL_QUADS);
         glNormal3f(-1.0, 0.0, 0.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(-3.0, 3.0, -2.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(-3.0, 2.0, -2.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(-3.0, 2.0, 2.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(-3.0, 3.0, 2.0);
		glEnd();

	// TURRET TOP

		glColor3f(1.0, 1.0, 0.0);	

		glBegin(GL_QUADS);
         glNormal3f(0.0, 1.0, 0.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(-3.0, 3.0, 2.0);
         glTexCoord2f(1.0, 0.0);
			glVertex3f(1.0, 3.0, 2.0);
         glTexCoord2f(1.0, 1.0);
			glVertex3f(1.0, 3.0, -2.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(-3.0, 3.0, -2.0);
      glEnd();
      glBegin(GL_QUADS);
         glNormal3f(0.0, 1.0, 0.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(1.0, 3.0, 2.0);
         glTexCoord2f(0.25, 0.25);
			glVertex3f(2.0, 3.0, 1.0);
         glTexCoord2f(0.25, 0.75);
			glVertex3f(2.0, 3.0, -1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(1.0, 3.0, -2.0);
		glEnd();

	// FRONT SLOPE

      p[0][0] = 4.0;
      p[0][1] = 2.0;
      p[0][2] = -3.0;
      p[1][0] = 4.0;
      p[1][1] = 2.0;
      p[1][2] = 3.0;
      p[2][0] = 5.5;
      p[2][1] = 1.5;
      p[2][2] = 3.0;
      p[3][0] = 5.5;
      p[3][1] = 1.5;
      p[3][2] = -3.0;
      p[4][0] = 4.0;
      p[4][1] = 0.0;
      p[4][2] = 3.0;
      p[5][0] = 4.0;
      p[5][1] = 0.0;
      p[5][2] = -3.0;

		glColor3f(0.0, 0.0, 1.0);	
		glBegin(GL_QUADS);
         findUnitNormal(p[1], p[2], p[0], norm);
         glNormal3fv(norm);
         glTexCoord2f(2.0, 1.0);
			glVertex3fv(p[0]);
         glTexCoord2f(0.0, 1.0);
			glVertex3fv(p[1]);
         glTexCoord2f(0.0, 0.0);
			glVertex3fv(p[2]);
         glTexCoord2f(2.0, 0.0);
			glVertex3fv(p[3]);
      glEnd();
      glBegin(GL_QUADS);
         findUnitNormal(p[5], p[6], p[2], norm);
         glNormal3fv(norm);
         glTexCoord2f(2.0, 1.0);
			glVertex3fv(p[3]);
         glTexCoord2f(0.0, 1.0);
			glVertex3fv(p[2]);
         glTexCoord2f(0.0, 0.0);
			glVertex3fv(p[4]);
         glTexCoord2f(2.0, 0.0);
			glVertex3fv(p[5]);			
		glEnd();

		glBegin(GL_TRIANGLES);
         glNormal3f(0.0, 0.0, 1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(4.0, 2.0, 3.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(4.0, 0.0, 3.0);
         glTexCoord2f(0.75, 0.75);
			glVertex3f(5.5, 1.5, 3.0);
		glEnd();

		glBegin(GL_TRIANGLES);
         glNormal3f(0.0, 0.0, -1.0);
         glTexCoord2f(0.0, 1.0);
			glVertex3f(4.0, 2.0, -3.0);
         glTexCoord2f(0.75, 0.75);
			glVertex3f(5.5, 1.5, -3.0);
         glTexCoord2f(0.0, 0.0);
			glVertex3f(4.0, 0.0, -3.0);
		glEnd();

	//HATCH

/*      glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
*/
		glPushMatrix(); 
		 glTranslatef(-1.9f, 3.3f, 1.0);
		 glRotatef(90, 0.0, 1.0, 0.0);
		  gluCylinder(qobj, 0.5f, 0.5f, 0.1f, 10, 10);
		  glPopMatrix();		

		 glPushMatrix(); 
		 glTranslatef(-1.9f, 3.3f, 1.0);
		 glRotatef(90.0, 0.0, -1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.5, 10, 10);
		 glPopMatrix();

		glPushMatrix(); 
		 glTranslatef(-1.8f, 3.3f, 1.0);
		 glRotatef(90.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.5, 10, 10);
		 glPopMatrix();

		 glDisable(GL_TEXTURE_GEN_S);
		 glDisable(GL_TEXTURE_GEN_T);
		 glDisable(GL_TEXTURE_2D);

	// GUN TUBE

		 glColor3f(0.0, 0.0, 0.0);

		 glPushMatrix(); 
		 glTranslatef(2.0f, 2.5f, 0.0);
		  glRotatef(90.0, 0.0, 1.0, 0.0);     
		  gluCylinder(qobj, 0.25, 0.25, 4.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 2.6f, 0.0);
		  glRotatef(90.0, 0.0, 1.0, 0.0);     
		  gluCylinder(qobj, 0.35, 0.35, 1.0, 10, 10);
		  glPopMatrix(); 

		 glPushMatrix(); 
		 glTranslatef(3.0f, 2.6f, 0.0);
		 glRotatef(-90.0, 0.0, 1.0, 0.0);  
		  gluDisk(qobj, 0.0, 0.35, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(4.0f, 2.6f, 0.0);
		 glRotatef(90, 0.0, 1.0, 0.0);  
		  gluDisk(qobj, 0.0, 0.35, 10, 10);
		  glPopMatrix();
		 
		 glPushMatrix(); 
		 glTranslatef(6.0f, 2.5f, 0.0);
		 glRotatef(90.0, 0.0, 1.0, 0.0);  
		  gluDisk(qobj, 0.0, 0.25, 10, 10);
		  glPopMatrix();	 	 

	// ROADWHEELS

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, 1.8f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, 1.8f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, 1.8f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, 1.8f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, -2.6f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, -2.6f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, -2.6f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, -2.6f);
		  gluCylinder(qobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

	// ROADWHEEL ENDS 

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, 2.8f);
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, 2.8f);
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, 2.8f);
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, 2.8f);
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, -1.6f);
		 gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, -1.6f);
		 gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, -1.6f);
		 gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, -1.6f);
		 gluDisk(qobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

	//TRACK	

		 glBegin(GL_POLYGON);       
			glVertex3f(-3.0f, -0.75f, 2.8f);
			glVertex3f(3.0f, -0.75f, 2.8f);
			glVertex3f(3.0f, -0.75f, 1.8f);
			glVertex3f(-3.0f, -0.75f, 1.8f);
		glEnd();

		glBegin(GL_POLYGON);       
			glVertex3f(-3.0f, -0.75f, 1.8f);
			glVertex3f(3.0f, -0.75f, 1.8f);
			glVertex3f(3.0f, -0.75f, 2.8f);
			glVertex3f(-3.0f, -0.75f, 2.8f);		
			
		glEnd();

		glBegin(GL_POLYGON);       		
			glVertex3f(-3.0f, -0.75f, -1.6f);
			glVertex3f(3.0f, -0.75f, -1.6f);
			glVertex3f(3.0f, -0.75f, -2.6f);
			glVertex3f(-3.0f, -0.75f, -2.6f);
		glEnd();

		glBegin(GL_POLYGON);       		
			glVertex3f(-3.0f, -0.75f, -2.6f);
			glVertex3f(3.0f, -0.75f, -2.6f);
			glVertex3f(3.0f, -0.75f, -1.6f);
			glVertex3f(-3.0f, -0.75f, -1.6f);				
		glEnd();


	// GPS

		glBegin(GL_QUAD_STRIP);       
			glVertex3f(0.0f, 3.3f, 1.5f);
			glVertex3f(0.0f, 3.0f, 1.5f);
			glVertex3f(0.5f, 3.3f, 1.5f);
			glVertex3f(0.5f, 3.0f, 1.5f);
			glVertex3f(0.5f, 3.3f, 0.5f);
			glVertex3f(0.5f, 3.0f, 0.5f);
			glVertex3f(0.0f, 3.3f, 0.5f);
			glVertex3f(0.0f, 3.0f, 0.5f);
			glVertex3f(0.0f, 3.3f, 1.5f);
			glVertex3f(0.0f, 3.0f, 1.5f);
		glEnd();

		glBegin(GL_POLYGON);       
			glVertex3f(0.0f, 3.3f, 1.5f);
			glVertex3f(0.5f, 3.3f, 1.5f);
			glVertex3f(0.5f, 3.3f, 0.5f);
			glVertex3f(0.0f, 3.3f, 0.5f);
		glEnd();

	// .50 CAL post

   glPushMatrix(); 
		 glTranslatef(-0.0, 3.7f, 1.0);
		  glRotatef(90.0, 1.0, 0.0, 0.0);     
		  gluCylinder(qobj, 0.05, 0.05, 1.0, 10, 10);
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
void Friend::draw(){ 
   glCallList(FriendList); 
} // end draw


GLfloat Friend::getSpeed() {
   return speed;
} // end getSpeed


void Friend::setSpeed(GLfloat spd) {
   speed = spd;
} // end setSpeed


GLfloat Friend::getRadius() {
   return radius;
} // end getRadius


void Friend::increaseSpeed() {

   if (speed < maxFwdSpeed) {
      speed += 0.1f;
   } // end if
} // end increaseSpeed


void Friend::decreaseSpeed() {

   if (speed > maxRevSpeed) {
      speed -= 0.1f;
   } // end if
} // end decreaseSpeed


void Friend::stop() {
   speed = 0.0f;
} // end stop


void Friend::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


float Friend::takeRammingDamage(float oppHdg, float oppSpd) {

   float relativeHdg;
   float rammingSpeed;

   relativeHdg = oppHdg - azimuth;
   if (relativeHdg < 0) {
      relativeHdg += 360;
   } // end if

   if (relativeHdg >= 30 && relativeHdg < 150 || relativeHdg > 210 && relativeHdg <= 330) {
      rammingSpeed = oppSpd;
   } else if (relativeHdg < 30 || relativeHdg > 330) {
      rammingSpeed = oppSpd - speed;
   } else { // relativeHdg > 150 && relativeHdg < 210
      rammingSpeed = oppSpd + speed;
   } // end if-else
   if (rammingSpeed > 0.5) {
      damageCapacity -= ((GLfloat)25.0f) * rammingSpeed / 2.0f;
      return 25.0f * rammingSpeed / 2.0f;
   } // end if
   return 0.0f;
} // end takeRammingDamage


void Friend::regen() {
   speed = 0.0f;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;
   damageCapacity = 30;
   shells = 20;
   bullets = 1000;
   mgLatch = false;
}


GLfloat Friend::getDamageCapacity() {
   return damageCapacity;
} // end getDamageCapacity


bool Friend::isDestroyed() {
   return destroyed;
} // end isDestroyed


void Friend::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void Friend::destroy() {
   destroyed = true;
} // end destroy


Explosion* Friend::getExplosion() {
   return explosion;
} // end getExplosion


int Friend::getShells() {
   return shells;
} // end getShells


int Friend::getBullets() {
   return bullets;
} // end getBullets


void Friend::fireShell() {
   shells--;
} // end fireShell


void Friend::fireBullet() {
   bullets--;
} // end fireBullets


void Friend::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void Friend::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void Friend::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void Friend::unBackwardCollide() {
   backwardCollided = false;
} // end unbackwardCollide


bool Friend::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool Friend::isBackwardCollided() {
   return backwardCollided;
} // end isBackwardCollided


int Friend::getPointValue() {
   return pointValue;
} // end getPointValue


float Friend::takeCollisionDamage(int damage) {
   if (speed > 0.5) {
      damageCapacity -= ((GLfloat)damage) * speed / 2.0f;
      return ((float)damage) * speed / 2.0f;
   } // end if
   return 0.0f;
} // end takeCollisionDamage


GLfloat Friend::getX() {
   return x;
} // end getX


GLfloat Friend::getY() {
   return y;
} // end getY


GLfloat Friend::getZ() {
   return z;
} // end getZ


GLfloat Friend::getAzimuth() {
   return azimuth;
} // end getAzimuth


GLfloat Friend::getRotationX() {
   return rotationX;
} // end getRotationX


GLfloat Friend::getRotationY() {
   return rotationY;
} // end getRotationY


bool Friend::isMGLatched() {
   return mgLatch;
} // end isMGLatched


void Friend::setX(GLfloat pX) {
   x = pX;
} // end setX


void Friend::setY(GLfloat pY) {
   y = pY;
} // end setY


void Friend::setZ(GLfloat pZ) {
   z = pZ;
} // end setX


void Friend::setAzimuth(GLfloat pAz) {
   azimuth = pAz;
} // end setAzimuth


void Friend::setRotationX(GLfloat pRotX) {
   rotationX = pRotX;
} // end setRotationX


void Friend::setRotationY(GLfloat pRotY) {
   rotationY = pRotY;
} // end setRotationY


void Friend::setMGLatch(bool latch) {
   mgLatch = latch;
} // end setMGLatch


bool Friend::isRespawning() {
   return respawned;
} // end isRespawning


void Friend::setRespawnFlag(bool flag) {
   respawned = flag;
} // end setRespawnFlag