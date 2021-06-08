#ifndef ___HOUSE_H__
#define ___HOUSE_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include "Explosion.h"

class House {

	public:

   // Constructor   
	House(){};

   // Destructor
   ~House() {
      if (explosion != 0) {
         delete explosion;
      } // end if
   } // end Destructor

   // Sets up the display list for displaying a house
	void init(float, float, float, float, float, float, float,
				 int, int);

	// Calls the display list to render the house
   void draw();

   GLfloat getRadius();
   GLfloat getX();
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

	GLuint siding1Texture;
	GLuint shingleTexture;

   private:

   
	GLuint houseList;// display list house
//	GLuint doorList;// display list for door

   GLfloat radius;
   GLfloat x, y, z;

   bool destroyed;
   Explosion* explosion;

   bool forwardCollided;
   bool backwardCollided;
   int pointValue;

   GLfloat damageCapacity;
};


#endif