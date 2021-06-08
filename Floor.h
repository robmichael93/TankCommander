#ifndef ___FLOOR_H__
#define ___FLOOR_H__

#include <gl\gl.h>
#include <gl\glu.h>

class Floor {

	public:

   // Constructor   
	Floor(){};

   // Sets up the display list for displaying the floor
	void init(float x, float y, float z, float sideLength);

	// Calls the display list to render the floor
   void draw();

	private:

   
	GLuint floorList;// display list identifier

};


#endif