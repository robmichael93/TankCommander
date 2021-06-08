#ifndef ___SHELL_H__
#define ___SHELL_H__

#include <gl\gl.h>
#include <gl\glu.h>

#define FACTOR 10

class Shell {

	public:
	
   // Constructor
   Shell(){}

   // Initializes the pyramid height and width
	void init(GLfloat, GLfloat, GLfloat, GLfloat);

   // Renders a pyramid center about the local origin
	void draw();

   int getID();
   GLfloat getX();
   GLfloat getY();
   GLfloat getZ();
   GLfloat getAzimuth();
   GLfloat getRange();
   void updateRealPosition();
   void increaseRange();
   GLfloat getRealX();
   GLfloat getRealZ();
   GLfloat getDamage();

	private:

   static int count;
   int id;
	GLuint ShellList;// display list identifier
   GLfloat x, y, z;
   GLfloat azimuth;
   GLfloat range;
   GLfloat realX, realY, realZ;

   GLfloat damage;

};

#endif