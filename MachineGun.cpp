#include "stdafx.h"
#include "MachineGun.h"
//---------------------------------------------------------------------

//---------------------------------------------------------------------

GLUquadricObj *qobjmg;

void MachineGun::init()
{
   qobjmg = gluNewQuadric();

   MachineGunList = glGenLists(2);

   glNewList(MachineGunList, GL_COMPILE);	
// .50 CAL

   glColor3f(0.0, 0.0, 0.0);

	glPushMatrix(); 
      glRotatef(180.0, 0.0, 1.0, 0.0);     
	   glTranslatef(0.0, 0.0, -0.5);
      gluCylinder(qobjmg, 0.08, 0.08, 2.5, 10.0, 10.0);
   glPopMatrix();

	glPushMatrix(); 
      glRotatef(180.0, 0.0, 1.0, 0.0);     
	   glTranslatef(0, 0.0, -0.5);
      gluCylinder(qobjmg, 0.15, 0.15, 1.0, 10.0, 10.0);
   glPopMatrix();

	glPushMatrix(); 
	   glTranslatef(0.0, 0.0, 0.5);
      gluDisk(qobjmg, 0.0, 0.15, 10.0, 10.0);
   glPopMatrix();

	glPushMatrix(); 
	   glRotatef(180, 0.0, 1.0, 0.0);  
	   glTranslatef(0.0, 0.0, 0.5);
      gluDisk(qobjmg, 0.0, 0.15, 10.0, 10.0);
   glPopMatrix();

	glPushMatrix(); 
	   glRotatef(180, 0.0, 1.0, 0.0);  
	   glTranslatef(0.0, 0.0, 2.0);
      gluDisk(qobjmg, 0.0, 0.08, 10.0, 10.0);
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
void MachineGun::draw(){ 
   glCallList(MachineGunList); 
} // end draw