#ifndef ___FOE_H__
#define ___FOE_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include "Explosion.h"

class Foe {

	public:
	
   // Constructor
   Foe(){}

   // Destructor
   ~Foe() {
      if (explosion != 0) {
         delete explosion;
      } // end if
   } // end Destructor

   // Initializes the foe tank location and texture
	void init(GLfloat, GLfloat, int);

   // Renders a pyramid center about the local origin
	void draw();

   GLfloat getRadius();
   GLfloat getX();
   GLfloat getY();
   GLfloat getZ();

   void takeDamage(GLfloat);
   bool isDestroyed();
   void startExplosion();
   void destroy();
   Explosion* getExplosion();
   int getPointValue();

   void forwardCollide();
   void backwardCollide();
   void unForwardCollide();
   void unBackwardCollide();
   bool isForwardCollided();
   bool isBackwardCollided();

	GLuint dcamoTexture;
   private:

	GLuint FoeList;// display list identifier

   GLfloat radius;
   GLfloat x, y, z;
   GLfloat damageCapacity;
   int pointValue;

   bool forwardCollided;
   bool backwardCollided;

   bool destroyed;
   Explosion* explosion;

};

#endif