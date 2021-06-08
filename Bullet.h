#ifndef ___BULLET_H__
#define ___BULLET_H__

#include <gl\gl.h>
#include <gl\glu.h>

#define BULLET_FACTOR 10

class Bullet {

	public:
	
   // Constructor
   Bullet(){}

   // Initializes the pyramid height and width
	void init(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

   // Renders a pyramid center about the local origin
	void draw();

   int getID();
   GLfloat getX();
   GLfloat getY();
   GLfloat getZ();
   GLfloat getAzimuth();
   GLfloat getElevation();
   GLfloat getRotation();
   GLfloat getRange();
   void updateRealPosition();
   void increaseRange();
   GLfloat getRealX();
   GLfloat getRealY();
   GLfloat getRealZ();
   GLfloat getDamage();

	private:

   static int count;
   int id;
	GLuint BulletList;// display list identifier
   GLfloat x, y, z;
   GLfloat azimuth;
   GLfloat elevation;
   GLfloat rotation;
   GLfloat range;
   GLfloat realX, realY, realZ;

   GLfloat damage;

};

#endif