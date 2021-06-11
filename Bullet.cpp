#include "stdafx.h"
#include "Bullet.h"
//#include "OpenGLDoc.h"
//#include "OpenGLView.h"
//#include <GL/glut.h>
#include <math.h>

#define PI 3.14159
//---------------------------------------------------------------------

//---------------------------------------------------------------------
GLUquadricObj *bullet;
int Bullet::count = 0;

void Bullet::init(GLfloat xLoc, GLfloat yLoc, GLfloat zLoc,
                  GLfloat heading, GLfloat elev, GLfloat rot) {

   id = count++;

   x = xLoc;
   y = yLoc;
   z = zLoc;
   azimuth = heading;
   elevation = elev;
   rotation = rot;
   realX = (GLfloat) (x + 1.5 * sin(azimuth * PI/180.0) + 
           2 * cos (elevation * PI/180.0) * sin((azimuth + rotation) * PI/180.0));
   realY = (GLfloat) (y - 0.55 + 2 * sin(elevation * PI/180.0));
   realZ = (GLfloat) (z - 1.5 * cos(azimuth * PI/180.0) - 
           2 * cos(elevation * PI/180.0) * cos((azimuth + rotation) * PI/180.0));
   range = 0;
   damage = 1;

   bullet = gluNewQuadric();

   BulletList = glGenLists(1);

   glNewList(BulletList, GL_COMPILE);
      glColor3f(0.25, 0.25, 0.25);
      gluSphere(bullet, 0.05, 6, 6);
   glEndList();
} // end init

void Bullet::draw() {
   glCallList(BulletList);
} // end draw


int Bullet::getID() {
   return id;
} // end getID


GLfloat Bullet::getX() {
   return x;
} // end getX


GLfloat Bullet::getY() {
   return y;
} // end getY


GLfloat Bullet::getZ() {
   return z;
} // end getZ


GLfloat Bullet::getAzimuth() {
   return azimuth;
} // end getAzimuth


GLfloat Bullet::getElevation() {
   return elevation;
} // end getElevation


GLfloat Bullet::getRotation() {
   return rotation;
} // end getRotation


GLfloat Bullet::getRange() {
   return range;
} // end getRange


void Bullet::updateRealPosition() {
   realX += (GLfloat) (BULLET_FACTOR * cos (elevation * PI/180.0) * 
                            sin((azimuth + rotation) * PI/180.0));
   realY += (GLfloat) (BULLET_FACTOR * sin(elevation * PI/180.0));
   realZ -= (GLfloat) (BULLET_FACTOR * cos(elevation * PI/180.0) * 
                            cos((azimuth + rotation) * PI/180.0));
} // end updateRealPosition

void Bullet::increaseRange() {
   range += BULLET_FACTOR;
} // end increaseRange


GLfloat Bullet::getRealX() {
   return realX;
} // end getRealX


GLfloat Bullet::getRealY() {
   return realY;
} // end getRealY


GLfloat Bullet::getRealZ() {
   return realZ;
} // end getRealZ


GLfloat Bullet::getDamage() {
   return damage;
} // end getDamage