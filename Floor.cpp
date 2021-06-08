#include "stdafx.h"
#include "Floor.h"

//---------------------------------------------------------------------
// Method: init
// Author: Eric Bachmann
// Function: Initializes the "checker board" floor xyz location.
//			    Initializes the "checker board" floor size.
//			    The floor is oriented in the the xz plane.
//			    Compiles a display list to be used when drawing the floor.
// Parameters: 
//				x - x coordinate of the middle of the floor
//				y - y coordinate of the middle of the floor
//				z - z coordinate of the middle of the floor
//				sideLength - the length of the sides of the square board.
//				
// Returns: None
// Called By: 
// Calls: None
//---------------------------------------------------------------------

void Floor::init(float x, float y, float z, float sideLength)
{
	GLfloat v[3]={0};
	GLfloat board_spec[] = {0.25, 0.25, 0.25, 1.0};
	short color = 1;
	
	floorList = glGenLists(1);

	glNewList(floorList, GL_COMPILE);

	GLfloat tileWidth = sideLength / 8.0f;

	GLfloat tileX = x  - (4.0f * tileWidth);

	GLfloat tileZ = z + (4.0f * tileWidth);

	// define the two colors
	GLfloat color1[3] = { 0.9f, 0.9f, 0.9f };
 	GLfloat color2[3] = { 0.05f, 0.05f, 0.05f };

	glNormal3f(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, board_spec);

	for ( int j = 0 ; j < 8; j++ ) {

		glColor3fv( (color++)%2 ? color1 : color2 );

		for ( int i = 0 ; i < 8 ; i++ ) {

			glBegin (GL_POLYGON );

			glColor3fv( (color++)%2 ? color1 : color2 );

			v[0] = tileX;
			v[1] = y;
			v[2] = tileZ-tileWidth;
			glVertex3fv(v);

			v[0] = tileX;
			v[1] = y;
			v[2] = tileZ;
			glVertex3fv(v);
			tileX++;

			v[0] = tileX;
			v[1] = y;
			v[2] = tileZ;
			glVertex3fv(v);

			v[0] = tileX;
			v[1] = y;
			v[2] = tileZ-tileWidth;
			glVertex3fv(v);

			glEnd();
		} // end for


		tileX = x  - (4.0f * tileWidth);
		tileZ -= tileWidth;
	}

	glEndList();

} // end initFloor

//---------------------------------------------------------------------
// Method: draw
// Function: Draws a floor object with the size and location specified 
//			 by the class data members.
// Parameters: 
//			None
//				
// Returns: Void
// Called By: 
// Calls: None
//---------------------------------------------------------------------
void Floor::draw()
{
	glCallList(floorList);


} // end draw


// *********************** END FLOOR CLASS *****************************


