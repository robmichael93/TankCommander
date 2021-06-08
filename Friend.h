#ifndef ___FRIEND_H__
#define ___FRIEND_H__

#include <gl\gl.h>
#include <gl\glu.h>
#include "Explosion.h"

class Friend {

	public:
	
   // Constructor
   Friend(){}

   // Destructor
   ~Friend() {
      if (explosion != 0) {
         delete explosion;
      } // end if
   } // end Destructor

   // Initializes the pyramid height and width
	void init(int);

   // Renders a pyramid center about the local origin
	void draw();

   GLfloat getSpeed();
   void setSpeed(GLfloat);
   GLfloat getRadius();
   void increaseSpeed();
   void decreaseSpeed();
   void stop();

   bool isDestroyed();
   void startExplosion();
   void destroy();
   Explosion* getExplosion();

   int getShells();
   int getBullets();
   void fireShell();
   void fireBullet();
   int getPointValue();
   GLfloat getDamageCapacity();
   void takeDamage(GLfloat);
   float takeCollisionDamage(int);
   float takeRammingDamage(float, float);
   void regen();

   void forwardCollide();
   void backwardCollide();
   void unForwardCollide();
   void unBackwardCollide();
   bool isForwardCollided();
   bool isBackwardCollided();

   GLfloat getX();
   GLfloat getY();
   GLfloat getZ();
   GLfloat getAzimuth();
   GLfloat getRotationX();
   GLfloat getRotationY();
   bool isMGLatched();
   void setX(GLfloat);
   void setY(GLfloat);
   void setZ(GLfloat);
   void setAzimuth(GLfloat);
   void setRotationX(GLfloat);
   void setRotationY(GLfloat);
   void setMGLatch(bool);

   bool isRespawning();
   void setRespawnFlag(bool);

	GLuint camoTexture;

   private:

	GLuint FriendList;// display list identifier
   GLfloat speed;

   static GLfloat maxFwdSpeed;
   static GLfloat maxRevSpeed;
   GLfloat radius;
   int shells;
   int bullets;
   int pointValue;
   GLfloat damageCapacity;
   GLfloat x;
   GLfloat y;
   GLfloat z;
   GLfloat azimuth;
   GLfloat rotationX;
   GLfloat rotationY;

   bool forwardCollided;
   bool backwardCollided;

   bool destroyed;
   Explosion* explosion;

   bool mgLatch;
   bool respawned;

};

#endif