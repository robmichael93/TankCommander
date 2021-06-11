#include "stdafx.h"
#include "Shell.h"
//#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
//---------------------------------------------------------------------

//---------------------------------------------------------------------
GLUquadricObj *shell;
int Shell::count = 0;

void Shell::init(GLfloat xLoc, GLfloat yLoc, GLfloat zLoc, GLfloat heading) {

   id = count++;
   x = xLoc;
   y = yLoc;
   z = zLoc;
   azimuth = heading;
   realX = (GLfloat) (x - cos(azimuth * PI/180.0f) + 7.5f * sin(azimuth * PI/180.0f));
   realZ = (GLfloat) (z - sin(azimuth * PI/180.0f) - 7.5f * cos(azimuth * PI/180.0f));
   range = 0;
   damage = 25;

   shell = gluNewQuadric();

   ShellList = glGenLists(1);

   glNewList(ShellList, GL_COMPILE);
      glColor3f(0.0, 0.0, 0.0);
      gluSphere(shell, 0.25, 6, 6);
   glEndList();
} // end init

void Shell::draw() {
   glCallList(ShellList);
} // end draw


int Shell::getID() {
   return id;
} // end getID


GLfloat Shell::getX() {
   return x;
} // end getX


GLfloat Shell::getY() {
   return y;
} // end getX


GLfloat Shell::getZ() {
   return z;
} // end getX


GLfloat Shell::getAzimuth() {
   return azimuth;
} // end getX


GLfloat Shell::getRange() {
   return range;
} // end getRange


void Shell::updateRealPosition() {
   realX += (GLfloat) (FACTOR * sin(azimuth * PI/180.0f));
   realZ -= (GLfloat) (FACTOR * cos(azimuth * PI/180.0f));
} // end updateRealPosition

void Shell::increaseRange() {
   range += FACTOR;
} // end increaseRange


GLfloat Shell::getRealX() {
   return realX;
} // end getRealX


GLfloat Shell::getRealZ() {
   return realZ;
} // end getRealZ


GLfloat Shell::getDamage() {
   return damage;
} // end getDamage