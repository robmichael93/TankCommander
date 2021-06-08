#include "stdafx.h"
#include "Foe.h"
#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "normals.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------


GLUquadricObj *qobjf;

void Foe::init(GLfloat xPos, GLfloat zPos, int dcamoTex)
{
   x = xPos;
   y = 0.75;
   z = zPos;
   radius = 3.61f;
	dcamoTexture = dcamoTex;
   pointValue = 20;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;
   damageCapacity = 20;

   qobjf = gluNewQuadric();
	gluQuadricDrawStyle(qobjf, GLU_FILL);
	gluQuadricOrientation(qobjf, GLU_OUTSIDE);
	gluQuadricNormals(qobjf, GLU_SMOOTH);	
   gluQuadricTexture(qobjf, GL_TRUE);

   float p[6][3]; // array of points for the front slope
   float t[6][3]; // array of points for side of the front slope
   float norm[3];

   FoeList = glGenLists(2);

   glNewList(FoeList, GL_COMPILE);	
   
	// enable texture mapping for the enemy tank
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, dcamoTexture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// HULL


	glBegin(GL_QUADS);
      glNormal3f(0.0, 0.0, 1.0);
      glTexCoord2f(0.0, 1.0);
	   glVertex3f(-3.0, 1.5, 2.0);
      glTexCoord2f(0.0, 0.0);
	   glVertex3f(-3.0, 0.0, 2.0);
      glTexCoord2f(1.0, 0.0);
	   glVertex3f(3.0, 0.0, 2.0);
      glTexCoord2f(1.0, 1.0);
	   glVertex3f(3.0, 1.5, 2.0);
   glEnd();
   glBegin(GL_QUADS);
      glNormal3f(1.0, 0.0, 0.0);
      glTexCoord2f(0.0, 1.0);
	   glVertex3f(-3.0, 1.5, -2.0);
      glTexCoord2f(0.0, 0.0);
	   glVertex3f(-3.0, 0.0, -2.0);
      glTexCoord2f(1.0, 0.0);
	   glVertex3f(-3.0, 0.0, 2.0);
      glTexCoord2f(1.0, 1.0);
	   glVertex3f(-3.0, 1.5, 2.0);
   glEnd();
   glBegin(GL_QUADS);
      glNormal3f(-1.0, 0.0, 0.0);
      glTexCoord2f(0.0, 1.0);
	   glVertex3f(3.0, 1.5, -2.0);
      glTexCoord2f(0.0, 0.0);
	   glVertex3f(3.0, 0.0, -2.0);
      glTexCoord2f(1.0, 0.0);
	   glVertex3f(-3.0, 0.0, -2.0);
      glTexCoord2f(1.0, 1.0);
	   glVertex3f(-3.0, 1.5, -2.0);
	glEnd();

	//DECK

	glBegin(GL_POLYGON);
      glNormal3f(0.0, 1.0, 0.0);
      glTexCoord2f(0.0, 0.0);
	   glVertex3f(-3.0, 1.5, 2.0);
      glTexCoord2f(0.0, 1.0);
	   glVertex3f(3.0, 1.5, 2.0);
      glTexCoord2f(1.0, 1.0);
	   glVertex3f(3.0, 1.5, -2.0);
      glTexCoord2f(1.0, 0.0);
	   glVertex3f(-3.0, 1.5, -2.0);
	glEnd();

	glBegin(GL_POLYGON);       
	   glVertex3f(-3.0, 0.0, -2.0);
	   glVertex3f(3.0, 0.0, -2.0);
	   glVertex3f(3.0, 0.0, 2.0);
	   glVertex3f(-3.0, 0.0, 2.0);	
	glEnd();


	// FRONT SLOPE

   p[0][0] = 3.0;
   p[0][1] = 1.5;
   p[0][2] = -2.0;
   p[1][0] = 3.0;
   p[1][1] = 1.5;
   p[1][2] = 2.0;
   p[2][0] = 4.5;
   p[2][1] = 1.5;
   p[2][2] = 1.5;
   p[3][0] = 4.5;
   p[3][1] = 1.5;
   p[3][2] = -1.5;
   p[4][0] = 3.0;
   p[4][1] = 0.0;
   p[4][2] = 2.0;
   p[5][0] = 3.0;
   p[5][1] = 0.0;
   p[5][2] = -2.0;

	glBegin(GL_QUADS);
      findUnitNormal(p[1], p[2], p[0], norm);
      glNormal3fv(norm);
      glTexCoord2f(1.0, 1.0);
		glVertex3fv(p[0]);
      glTexCoord2f(0.0, 1.0);
		glVertex3fv(p[1]);
      glTexCoord2f(0.125, 0.0);
		glVertex3fv(p[2]);
      glTexCoord2f(0.875, 0.0);
		glVertex3fv(p[3]);
   glEnd();
   glBegin(GL_QUADS);
      findUnitNormal(p[5], p[6], p[2], norm);
      glNormal3fv(norm);
      glTexCoord2f(0.875, 1.0);
		glVertex3fv(p[3]);
      glTexCoord2f(0.125, 1.0);
		glVertex3fv(p[2]);
      glTexCoord2f(0.0, 0.0);
		glVertex3fv(p[4]);
      glTexCoord2f(1.0, 0.0);
		glVertex3fv(p[5]);			
	glEnd();
	
   t[0][0] = 3.0;
   t[0][1] = 1.5;
   t[0][2] = 2.0;
   t[1][0] = 3.0;
   t[1][1] = 0.0;
   t[1][2] = 2.0;
   t[2][0] = 4.5;
   t[2][1] = 1.5;
   t[2][2] = 1.5;

	glBegin(GL_TRIANGLES);
      findUnitNormal(t[0], t[2], t[1], norm);
      glNormal3fv(norm);
      glTexCoord2f(0.0, 0.75);
		glVertex3fv(t[0]);
      glTexCoord2f(0.0, 0.0);
		glVertex3fv(t[1]);
      glTexCoord2f(0.75, 0.75);
		glVertex3fv(t[2]);
	glEnd();

   t[3][0] = 3.0;
   t[3][1] = 1.5;
   t[3][2] = -2.0;
   t[4][0] = 4.5;
   t[4][1] = 1.5;
   t[4][2] = -1.5;
   t[5][0] = 3.0;
   t[5][1] = 0.0;
   t[5][2] = -2.0;

	glBegin(GL_TRIANGLES);
      findUnitNormal(t[3], t[4], t[5], norm);
      glNormal3fv(norm);
      glTexCoord2f(0.0, 0.75);
		glVertex3fv(t[3]);
      glTexCoord2f(0.75, 0.75);
		glVertex3fv(t[4]);
      glTexCoord2f(0.0, 0.0);
		glVertex3fv(t[5]);
	glEnd();

/*	glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
*/
	// TURRET

	glPushMatrix(); 
	 glTranslatef(0.0, 2.25f, 0.0);
	 glRotatef(90.0, 1.0, 0.0, 0.0);     
	 gluCylinder(qobjf, 0.75, 2.0, 1.0, 20, 20);
	 glPopMatrix();

	 glPushMatrix(); 
	 glTranslatef(0.0, 2.25f, 0.0);
	 glRotatef(90.0, -1.0, 0.0, 0.0);    
	  gluDisk(qobjf, 0.0, 0.77, 20, 20);
	  glPopMatrix();

	//SEARCHLIGHT

	glPushMatrix(); 
	 glTranslatef(0.9f, 2.15f, -0.5f);
	 glRotatef(90.0, 0.0, 1.0, 0.0);     
	 gluCylinder(qobjf, 0.05, 0.30, 0.3, 20, 20);
	 glPopMatrix();

	glPushMatrix(); 
	glTranslatef(1.2f, 2.15f, -0.5f);
	glRotatef(90.0, 0.0, 1.0, 0.0);    
	 gluDisk(qobjf, 0.0, 0.30, 20, 20);
	 glPopMatrix();

    //HATCH

	glPushMatrix(); 
		glTranslatef(-0.4f, 2.4f, 0.3f);
		glRotatef(90, 0.0, 1.0, 0.0);
		gluCylinder(qobjf, 0.25, 0.25, 0.1, 10, 10);
		glPopMatrix();		

	 glPushMatrix(); 
	 glTranslatef(-0.4f, 2.4f, 0.3f);
	 glRotatef(90.0, 0.0, -1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.25, 10, 10);
	 glPopMatrix();

	glPushMatrix(); 
	 glTranslatef(-0.3f, 2.4f, 0.3f);
	 glRotatef(90.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.25, 10, 10);
	 glPopMatrix();	

	 glDisable(GL_TEXTURE_GEN_S);
	 glDisable(GL_TEXTURE_GEN_T);
	 glDisable(GL_TEXTURE_2D);


	//GUNTUBE 

	glColor3f(0.0, 0.0, 0.0);

	glPushMatrix(); 
		glTranslatef(1.0, 2.0, 0.0);
		glRotatef(90.0, 0.0, 1.0, 0.0);
		glRotatef(5.0, -1.0, 0.0, 0.0);  
		gluCylinder(qobjf, 0.10, 0.10, 3.0, 10, 10);
		glTranslatef(0.0, 0.0, 3.0);
		gluDisk(qobjf, 0.0, 0.1, 10, 10);
	glPopMatrix();
		 
//ROADWHEELS

	glPushMatrix(); 
	  glTranslatef(2.5, 0.0, 2.0);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(1.5, 0.0, 2.0);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
   glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(0.5, 0.0, 2.0);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-0.5, 0.0, 2.0);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-1.5, 0.0, 2.0);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-2.5, 0.0, 2.0);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(2.5, 0.0, 2.75);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();
	 
	glPushMatrix(); 
	  glTranslatef(2.5, 0.0, 2.0);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(1.5, 0.0, 2.75);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(1.5, 0.0, 2.0);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(0.5, 0.0, 2.75);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(0.5, 0.0, 2.0);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-0.5, 0.0, 2.75);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-0.5, 0.0, 2.0);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-1.5, 0.0, 2.75);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-1.5, 0.0, 2.0);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-2.5, 0.0, 2.75);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-2.5, 0.0, 2.0);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(2.5, 0.0, -2.75);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(2.5, 0.0, -2.0);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(1.5, 0.0, -2.75);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(1.5, 0.0, -2.0);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(0.5, 0.0, -2.75);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(0.5, 0.0, -2.0);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-0.5, 0.0, -2.75);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-0.5, 0.0, -2.0);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-1.5, 0.0, -2.75);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-1.5, 0.0, -2.0);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-2.5, 0.0, -2.75);
	  gluCylinder(qobjf, 0.5, 0.5, 0.75, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(-2.5, 0.0, -2.0);
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	  glTranslatef(2.5, 0.0, -2.75);
	  glRotatef(180.0, 0.0, 1.0, 0.0); 
	  gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix();
	   glTranslatef(1.5, 0.0, -2.75);
	   glRotatef(180.0, 0.0, 1.0, 0.0); 
	   gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	   glTranslatef(0.5, 0.0, -2.75);
	   glRotatef(180.0, 0.0, 1.0, 0.0); 
	   gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	   glTranslatef(-0.5, 0.0, -2.75);
	   glRotatef(180.0, 0.0, 1.0, 0.0); 
	   gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	   glTranslatef(-1.5, 0.0, -2.75);
	   glRotatef(180.0, 0.0, 1.0, 0.0); 
	   gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	glPushMatrix(); 
	   glTranslatef(-2.5, 0.0, -2.75);
	   glRotatef(180.0, 0.0, 1.0, 0.0); 
	   gluDisk(qobjf, 0.0, 0.5, 10, 10);
	glPopMatrix();

	//TRACK

	glBegin(GL_POLYGON);       
		glVertex3f(-2.5, -0.5, 2.0);
		glVertex3f(-2.5, -0.5, 2.75);
		glVertex3f(2.5, -0.5, 2.75);
		glVertex3f(2.5, -0.5, 2.0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(2.5, -0.5, 2.0);
		glVertex3f(2.5, -0.5, 2.75);
		glVertex3f(-2.5, -0.5, 2.75);
		glVertex3f(-2.5, -0.5, 2.0);		
	glEnd();

	glBegin(GL_POLYGON);       
		glVertex3f(-2.5, 0.5, 2.0);
		glVertex3f(-2.5, 0.5, 2.75);
		glVertex3f(2.5, 0.5, 2.75);
		glVertex3f(2.5, 0.5, 2.0);
	glEnd();

	glBegin(GL_POLYGON);       
		glVertex3f(2.5, 0.5, 2.0);
		glVertex3f(2.5, 0.5, 2.75);
		glVertex3f(-2.5, 0.5, 2.75);
		glVertex3f(-2.5, 0.5, 2.0);		
	glEnd();

	glBegin(GL_POLYGON);       
		glVertex3f(-2.5, -0.5, -2.0);
		glVertex3f(-2.5, -0.5, -2.75);
		glVertex3f(2.5, -0.5, -2.75);
		glVertex3f(2.5, -0.5, -2.0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(2.5, -0.5, -2.0);
		glVertex3f(2.5, -0.5, -2.75);
		glVertex3f(-2.5, -0.5, -2.75);
		glVertex3f(-2.5, -0.5, -2.0);		
		
	glEnd();

	glBegin(GL_POLYGON);       
		glVertex3f(-2.5, 0.5, -2.0);
		glVertex3f(-2.5, 0.5, -2.75);
		glVertex3f(2.5, 0.5, -2.75);
		glVertex3f(2.5, 0.5, -2.0);
	glEnd();

	glBegin(GL_POLYGON);       
		glVertex3f(2.5, 0.5, -2.0);
		glVertex3f(2.5, 0.5, -2.75);
		glVertex3f(-2.5, 0.5, -2.75);
		glVertex3f(-2.5, 0.5, -2.0);		
	glEnd();

	// AT ROCKET

	glPushMatrix(); 
	   glTranslatef(-0.5f, 2.7f, -0.2f);
	   glRotatef(115.0, 0.0, 1.0, 0.0);
	   glRotatef(20.0, -1.0, 0.0, 0.0);  
	   gluCylinder(qobjf, 0.10, 0.10, 1.25, 10, 10);
	   gluDisk(qobjf, 0.0, 0.10, 10, 10);
	   glTranslatef(0.0, 0.0, 1.25f);
	   gluCylinder(qobjf, 0.2, 0.0, 0.3, 10, 10);
	   glRotatef(180.0, 0.0, 1.0, 0.0);  
	   gluDisk(qobjf, 0.0, 0.2, 10, 10);
	glPopMatrix();	 

	//ROCKET FINS

	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix(); 
		glTranslatef(-0.5f, 2.7f, -0.2f);
		glRotatef(20.0, 0.0, 0.0, 1.0);
		glRotatef(25.0, 0.0, 1.0, 0.0); 	 
		gluPartialDisk(qobjf, 0.0, 0.35, 10, 10, 0.0, 90.0);
	glPopMatrix();

	glPushMatrix(); 
		glTranslatef(-0.5f, 2.7f, -0.2f);	
		glRotatef(20.0, 0.0, 0.0, 1.0);
		glRotatef(25.0, 0.0, 1.0, 0.0); 
		glRotatef(120.0, 1.0, 0.0, 0.0);
		gluPartialDisk(qobjf, 0.0, 0.35, 10, 10, 0.0, 90.0);
	glPopMatrix();

	glPushMatrix(); 
		glTranslatef(-0.5f, 2.7f, -0.2f);	
		glRotatef(20.0, 0.0, 0.0, 1.0);
		glRotatef(25.0, 0.0, 1.0, 0.0); 
		glRotatef(240.0, 1.0, 0.0, 0.0);
		gluPartialDisk(qobjf, 0.0, 0.35, 10, 10, 0.0, 90.0);
	glPopMatrix();

	glPushMatrix(); 
		glTranslatef(-0.5f, 2.7f, -0.2f);
		glRotatef(20.0, 0.0, 0.0, 1.0);
		glRotatef(25.0, 0.0, 1.0, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0); 
		gluPartialDisk(qobjf, 0.0, 0.35, 10, 10, 270.0, 90.0);
	glPopMatrix();

	glPushMatrix(); 
		glTranslatef(-0.5f, 2.7f, -0.2f);
		glRotatef(20.0, 0.0, 0.0, 1.0);
		glRotatef(25.0, 0.0, 1.0, 0.0);
		glRotatef(120.0, 1.0, 0.0, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0); 
		gluPartialDisk(qobjf, 0.0, 0.35, 10, 10, 270.0, 90.0);
	glPopMatrix();

	glPushMatrix(); 
		glTranslatef(-0.5f, 2.7f, -0.2f);
		glRotatef(20.0, 0.0, 0.0, 1.0);
		glRotatef(25.0, 0.0, 1.0, 0.0); 
		glRotatef(240.0, 1.0, 0.0, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0); 
		gluPartialDisk(qobjf, 0.0, 0.35, 10, 10, 270.0, 90.0);
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);

	glPushMatrix(); 
		glTranslatef(0.0, 1.9f, -0.45f);
		glRotatef(-90.0, 1.0, 0.0, 0.0);     
		gluCylinder(qobjf, 0.05, 0.05, 1.0, 10, 10);
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
void Foe::draw(){ 
   glCallList(FoeList); 
} // end draw


GLfloat Foe::getRadius() {
   return radius;
} // end getRadius


GLfloat Foe::getX() {
   return x;
} // end getX


GLfloat Foe::getY() {
   return y;
} // end getY


GLfloat Foe::getZ() {
   return z;
} // end getZ


bool Foe::isDestroyed() {
   return destroyed;
} // end isDestroyed


void Foe::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void Foe::destroy() {
   destroyed = true;
} // end destroy


Explosion* Foe::getExplosion() {
   return explosion;
} // end getExplosion


void Foe::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


void Foe::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void Foe::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void Foe::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void Foe::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardCollide


bool Foe::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool Foe::isBackwardCollided() {
   return backwardCollided;
} // end isBackwardCollided


int Foe::getPointValue() {
   return pointValue;
} // end getPointValue

