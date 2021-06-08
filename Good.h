#ifndef ___GOOD_H__
#define ___GOOD_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include "Explosion.h"

class Good {

	public:
	
   // Constructor
   Good(){}

   // Destructor
   ~Good() {
      if (explosion != 0) {
         delete explosion;
      } // end if
   } // end Destructor

   // Initializes the pyramid height and width
	void init(GLfloat, GLfloat, int);

   // Renders a pyramid center about the local origin
	void draw();


   GLfloat getRadius();
   GLfloat getX();
   GLfloat getY();
   GLfloat getZ();
  

   bool isDestroyed();
   void startExplosion();
   void destroy();
   Explosion* getExplosion();
   int getPointValue();
   void takeDamage(GLfloat);

 
   void forwardCollide();
   void backwardCollide();
   void unForwardCollide();
   void unBackwardCollide();
   bool isForwardCollided();
   bool isBackwardCollided();

	GLuint camoTexture;

   private:

	GLuint GoodList;// display list identifier
   GLfloat speed;   
   GLfloat x, y, z;
   GLfloat damageCapacity;
   int pointValue;
  
   GLfloat radius;

   bool forwardCollided;
   bool backwardCollided;

   bool destroyed;
   Explosion* explosion;

};

#endif

