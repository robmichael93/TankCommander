#ifndef ___SILO_H__
#define ___SILO_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "Explosion.h"

class Silo {

	public:

   // Constructor   
	Silo(){};

   // Destructor
   ~Silo() {
      if (explosion != 0) {
         delete explosion;
      } // end if
   } // end Destructor

   // Sets up the display list for displaying a silo
	void init(float, float, float, float, float, int, int);

	// Calls the display list to render the silo
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

	private:

   GLfloat radius;
   GLfloat height;
   GLfloat x, y, z;

   //display list for silo
	GLuint siloList;

   bool destroyed;
   Explosion* explosion;

   bool forwardCollided;
   bool backwardCollided;
   int pointValue;

   GLfloat damageCapacity;

   //texture
	GLuint brickTexture;
	GLuint shingleTexture;

	//loads the brick texture
	void loadBrickTexture();

	//loads the shingle texture
	void loadShingleTexture();

};

#endif