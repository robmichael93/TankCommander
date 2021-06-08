#ifndef ___PINE_H__
#define ___PINE_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include "Explosion.h"

class Pine {

	public:
	
   // Constructor
   Pine(){}

   // Destructor
   ~Pine() {
      if (explosion != 0) {
         delete explosion;
      } // end if
   } // end Destructor

   // Initializes the pyramid height and width
	void init(GLfloat, GLfloat);

   // Renders a pyramid center about the local origin
	void draw();

   GLfloat getRadius();
   GLfloat getX();
   GLfloat getZ();

   void forwardCollide();
   void backwardCollide();
   void unForwardCollide();
   void unBackwardCollide();
   bool isForwardCollided();
   bool isBackwardCollided();

   void takeDamage(GLfloat);
   bool isDestroyed();
   void startExplosion();
   void destroy();
   Explosion* getExplosion();
   int getPointValue();

   private:

	GLuint PineList;// display list identifier

   bool forwardCollided;
   bool backwardCollided;

   GLfloat radius;
   GLfloat x, z;

   GLfloat damageCapacity;
   bool destroyed;
   Explosion* explosion;
   int pointValue;

};

#endif