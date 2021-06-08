#include "stdafx.h"
#include "draw.h"

//---------------------------------------------------------------------
// Method: drawFloor
// Author: Eric Bachmann
// Function: Draws a "checker board" floor at a specified xyz location.
//			The floor is oriented in the the xz plane.
// Parameters: 
//				x - x coordinate of the middle of the floor
//				y - y coordinate of the middle of the floor
//				z - z coordinate of the middle of the floor
//				sideLength - the length of the sides of the square board.
//				
// Returns: None
// Called By: display
// Calls: None
//---------------------------------------------------------------------
void drawFloor(float x, float y, float z, float sideLength)
{
	GLfloat v[3]={0};
	GLfloat board_spec[] = {0.25, 0.25, 0.25, 1.0};
	short color = 1;

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

}
//---------------------------------------------------------------------
// Method: drawCube
// Author: Eric Bachmann
// Function: Draws a multi-colored cube centered at a specified xyz location.
// Parameters: 
//				x - x coordinate of the middle of the cube
//				y - y coordinate of the middle of the cube
//				z - z coordinate of the middle of the cube
//				sideLength - the length of the sides of the cube.
// Returns: void
// Called By: display
// Calls: None
//---------------------------------------------------------------------
void drawcube(float x, float y, float z, float sidelength)
{
	GLfloat cube_spec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	
   float halfside;   // length of half the side of the cube.

   float p[8][3];    // array to hold coords for the cube faces.

   // Compute the halfside.
   halfside=sidelength/2.0f;

   // Back face.
   p[0][0]=x-halfside; // p[0] -+-
   p[0][1]=y+halfside;
   p[0][2]=z-halfside;

   p[1][0]=x+halfside; // p[1] ++-
   p[1][1]=y+halfside;
   p[1][2]=z-halfside;

   p[2][0]=x+halfside; // p[2] +--
   p[2][1]=y-halfside;
   p[2][2]=z-halfside;

   p[3][0]=x-halfside; // p[3] ---
   p[3][1]=y-halfside;
   p[3][2]=z-halfside;

   p[4][0]=x+halfside; // p[4] +++
   p[4][1]=y+halfside;
   p[4][2]=z+halfside;

   p[5][0]=x-halfside; // p[5] -++
   p[5][1]=y+halfside;
   p[5][2]=z+halfside;

   p[6][0]=x-halfside; // p[6] --+
   p[6][1]=y-halfside;
   p[6][2]=z+halfside;

   p[7][0]=x+halfside; // p[7] +-+
   p[7][1]=y-halfside;
   p[7][2]=z+halfside;

	glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);

	glBegin( GL_POLYGON );
		glColor3f(1.0, 0.0, 0.0);  
		glNormal3f(0.0, 0.0, 1.0);

      glVertex3fv(p[5]);
      glVertex3fv(p[6]);
      glVertex3fv(p[7]);
      glVertex3fv(p[4]);

	glEnd();
	
	glBegin( GL_POLYGON );
		glColor3f(1.0, 1.0, 0.0);  
		glNormal3f(1.0, 0.0, 0.0);

      glVertex3fv(p[4]);
      glVertex3fv(p[7]);
		glVertex3fv(p[2]);		
		glVertex3fv(p[1]);
 	glEnd();	

	
	glBegin( GL_POLYGON );	
	
		glColor3f(0.0, 1.0, 1.0);  
		glNormal3f(0.0, 0.0, -1.0);

      glVertex3fv(p[1]);
      glVertex3fv(p[2]);
      glVertex3fv(p[3]);
		glVertex3fv(p[0]);

	glEnd();

   glBegin(GL_POLYGON);

		glColor3f(0.0, 0.5, 1.0);  
		glNormal3f(0.0, -1.0, 0.0);

      glVertex3fv(p[2]);
      glVertex3fv(p[7]);
		glVertex3fv(p[6]);      
		glVertex3fv(p[3]);
 
	glEnd();

   glBegin(GL_POLYGON);

		glColor3f(0.0, 1.0, 0.0);  
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3fv(p[6]);      
		glVertex3fv(p[5]);
 		glVertex3fv(p[0]);
		glVertex3fv(p[3]);


	glEnd();  

	glBegin (GL_POLYGON);
		glColor3f(1.0, 0.0, 1.0);  
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3fv(p[0]);
		glVertex3fv(p[5]);
		glVertex3fv(p[4]);
		glVertex3fv(p[1]);
 
	glEnd();
	
   // the cube is drawn.
}
//---------------------------------------------------------------------
// Method: drawRedBall
// Author: Eric Bachmann
// Function: Draws a red ball centered at a specified xyz location.
// Parameters: 
//				x - x coordinate of the middle of the ball
//				y - y coordinate of the middle of the ball
//				z - z coordinate of the middle of the ball
//				radius - radius of the ball.
// Returns: void
// Called By: display
// Calls: None
//---------------------------------------------------------------------
void drawRedBall(float x, float y, float z, float diameter)
{
	GLfloat ball_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat ball_shine(128.0);

	glPushMatrix();

	glTranslatef(x, y, z);

	glColor3f(1.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ball_spec);
	glMaterialf(GL_FRONT, GL_SHININESS, ball_shine);

	auxSolidSphere(diameter);

	glPopMatrix();

} // end drawRedBall