#ifndef ___PYRAMID_H__
#define ___PYRAMID_H__

#include <gl\gl.h>
#include <gl\glu.h>

class Pyramid {

	public:
	
   // Constructor
   Pyramid(){}

   // Initializes the pyramid height and width
	void init(GLfloat, GLfloat, GLfloat, GLfloat);

   // Renders a pyramid center about the local origin
	void draw();

   GLfloat getHeight();
   GLfloat getWidth();

	GLfloat getRadius();
   GLfloat getX();
   GLfloat getZ();

   void forwardCollide();
   void backwardCollide();
   void unForwardCollide();
   void unBackwardCollide();
   bool isForwardCollided();
   bool isBackwardCollided();

   private:

	GLfloat height; // Height of the pyramid

	GLfloat width; // Width of the pyramid

   GLuint pyramidList;  // display list identifier

	bool forwardCollided;
   bool backwardCollided;

   GLfloat radius;
   GLfloat x, z;
};

#endif