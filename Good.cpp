#include "stdafx.h"
#include "Good.h"
#include "normals.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------
GLUquadricObj *gobj;

void Good::init(GLfloat xPos, GLfloat zPos, int camoTex)
{
   gobj = gluNewQuadric();

   x = xPos;
   y = 0.75;
   z = zPos;
   radius = 5.0f;
   damageCapacity = 25;
   explosion = 0;
   pointValue = -100;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;
	camoTexture = camoTex;

   float p[6][3]; // array of points for the front slope
   float norm[3];

   gluQuadricDrawStyle(gobj, GLU_FILL);
	gluQuadricOrientation(gobj, GLU_OUTSIDE);
	gluQuadricNormals(gobj, GLU_SMOOTH);	
   gluQuadricTexture(gobj, GL_TRUE);

   GoodList = glGenLists(2);

   glNewList(GoodList, GL_COMPILE);	

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
/*	glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
*/

	glPushMatrix(); 
	   glTranslatef(-1.9f, 3.3f, 1.0);
	   glRotatef(90, 0.0, 1.0, 0.0);
	   gluCylinder(gobj, 0.5, 0.5, 0.1, 10, 10);
	glPopMatrix();		

	glPushMatrix(); 
	   glTranslatef(-1.9f, 3.3f, 1.0);
	   glRotatef(90.0, 0.0, -1.0, 0.0); 
	   gluDisk(gobj, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	   glTranslatef(-1.8f, 3.3f, 1.0);
	   glRotatef(90.0, 0.0, 1.0, 0.0); 
	   gluDisk(gobj, 0.0, 0.5, 10, 10);
	glPopMatrix();

   glDisable(GL_TEXTURE_GEN_S);
   glDisable(GL_TEXTURE_GEN_T);
   glDisable(GL_TEXTURE_2D);

	// GUN TUBE

		 glColor3f(0.0, 0.0, 0.0);

		 glPushMatrix(); 
		 glTranslatef(2.0f, 2.5f, 0.0);
		  glRotatef(90.0, 0.0, 1.0, 0.0);     
		  gluCylinder(gobj, 0.25, 0.25, 4.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 2.6f, 0.0);
		  glRotatef(90.0, 0.0, 1.0, 0.0);     
		  gluCylinder(gobj, 0.35, 0.35, 1.0, 10, 10);
		  glPopMatrix(); 

		 glPushMatrix(); 
		 glTranslatef(3.0f, 2.6f, 0.0);
		 glRotatef(-90.0, 0.0, 1.0, 0.0);  
		  gluDisk(gobj, 0.0, 0.35, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(4.0f, 2.6f, 0.0);
		 glRotatef(90, 0.0, 1.0, 0.0);  
		  gluDisk(gobj, 0.0, 0.35, 10, 10);
		  glPopMatrix();
		 
		 glPushMatrix(); 
		 glTranslatef(6.0f, 2.5f, 0.0);
		 glRotatef(90.0, 0.0, 1.0, 0.0);  
		  gluDisk(gobj, 0.0, 0.25, 10, 10);
		  glPopMatrix();	 	 

	// ROADWHEELS

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, 1.8f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, 1.8f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, 1.8f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, 1.8f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, -2.6f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, -2.6f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, -2.6f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, -2.6f);
		  gluCylinder(gobj, 0.75, 0.75, 1.0, 10, 10);
		  glPopMatrix();

	// ROADWHEEL ENDS 

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, 2.8f);
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, 2.8f);
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, 2.8f);
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, 2.8f);
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, 1.8f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(3.0f, 0.0, -1.6f);
		 gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(1.0, 0.0, -1.6f);
		 gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-1.0, 0.0, -1.6f);
		 gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, -2.6f);
		 glRotatef(180.0, 0.0, 1.0, 0.0); 
		  gluDisk(gobj, 0.0, 0.75, 10, 10);
		  glPopMatrix();

		 glPushMatrix(); 
		 glTranslatef(-3.0f, 0.0, -1.6f);
		 gluDisk(gobj, 0.0, 0.75, 10, 10);
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

// .50 CAL

	glPushMatrix(); 
	 glTranslatef(-0.8f, 3.7f, 1.0);
     glRotatef(90.0, 0.0, 1.0, 0.0);     
     gluCylinder(gobj, 0.08, 0.08, 2.5, 10, 10);
     glPopMatrix();

	glPushMatrix(); 
	 glTranslatef(-0.8f, 3.7f, 1.0);
     glRotatef(90.0, 0.0, 1.0, 0.0);     
     gluCylinder(gobj, 0.15, 0.15, 1.0, 10, 10);
     glPopMatrix();

	 glPushMatrix(); 
	 glTranslatef(-0.8f, 3.7f, 1.0);
	 glRotatef(-90.0, 0.0, 1.0, 0.0);  
     gluDisk(gobj, 0.0, 0.15, 10, 10);
     glPopMatrix();

	 glPushMatrix(); 
	 glTranslatef(0.2f, 3.7f, 1.0);
	 glRotatef(90, 0.0, 1.0, 0.0);  
     gluDisk(gobj, 0.0, 0.15, 10, 10);
     glPopMatrix();

	 glPushMatrix(); 
	 glTranslatef(-0.3f, 3.7f, 1.0);
     glRotatef(90.0, 1.0, 0.0, 0.0);     
     gluCylinder(gobj, 0.05, 0.05, 1.0, 10, 10);
     glPopMatrix();

	 glPushMatrix(); 
	 glTranslatef(1.7f, 3.7f, 1.0);
	 glRotatef(90, 0.0, 1.0, 0.0);  
     gluDisk(gobj, 0.0, 0.08, 10, 10);
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
void Good::draw(){ 
   glCallList(GoodList); 
} // end draw

GLfloat Good::getRadius() {
   return radius;
} // end getRadius

bool Good::isDestroyed() {
   return destroyed;
} // end isDestroyed

void Good::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void Good::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


void Good::destroy() {
   destroyed = true;
} // end destroy


Explosion* Good::getExplosion() {
   return explosion;
} // end getExplosion

void Good::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void Good::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void Good::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void Good::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardCollide


bool Good::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool Good::isBackwardCollided() {
   return backwardCollided;
} // end isBackwardCollided


GLfloat Good::getX() {
   return x;
} // end getX


GLfloat Good::getY() {
   return y;
} // end getY


GLfloat Good::getZ() {
   return z;
} // end getZ


int Good::getPointValue() {
   return pointValue;
} // end getPointValue















