#include "stdafx.h"
#include "House.h"
#include <math.h>

//---------------------------------------------------------------------
// Method:  init
// Author:  Rick Sanders
// Function:  Draws a 3D house (Base plus Roof).
//			    .
//			     The house is oriented in the the xz plane.
//			     Compiles a display list to be used when drawing the house.
// Parameters: 
//				x - x coordinate of the middle of the house
//				y - y coordinate of the middle of the house
//				z - z coordinate of the middle of the house
//				houseWidth - the width of the house and base of the roof.
//				houseLength - the length of the side of the house.
//				baseHeight - the height of the base of the house.
//				roofHeight - the height of the roof of the house.
//				
// Returns: None
// Called By: 
// Calls: None
//---------------------------------------------------------------------

void House::init(float xPos, float yPos, float zPos, float houseWidth, 
					  float houseLength, float baseHeight, float roofHeight,
					  int siding1Tex, int shingleTex)
{
   x = xPos;
   y = yPos;
   z = zPos;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;
   damageCapacity = (houseWidth * houseLength * baseHeight) / 50.0f;
   pointValue = (int) damageCapacity;
	siding1Texture = siding1Tex;
	shingleTexture = shingleTex;

	GLfloat v[3]={0};
	GLfloat house_spec[] = {0.25, 0.25, 0.25, 1.0};
   float p[15][3];    // array to hold coords for the house faces.
	float offset = 0.01f;
	
	short color = 1;
	
	houseList = glGenLists(1);

	glNewList(houseList, GL_COMPILE);

	GLfloat halfWidth = houseWidth/2.0f;

	GLfloat halfBaseHeight = baseHeight/2.0f;

	GLfloat halfRoofHeight = roofHeight/2.0f;

	GLfloat halfLength = houseLength/2.0f;

    GLfloat radius = (GLfloat)(sqrt(houseWidth * houseWidth + houseLength * houseLength)/ 2.0f);

	// define the two colors
	GLfloat color1[3] = { 0.0f, 0.0f, 0.0f };
	GLfloat color2[3] = { 0.5f, 0.5f, 0.5f };
 	GLfloat color3[3] = { 1.0f, 1.0f, 1.0f };

	glNormal3f(0.0, 1.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, house_spec);

	glColor3fv(color2);
	glPointSize(2);

   // Back face.
   p[0][0]=x-halfWidth; // p[0] -+-
   p[0][1]=y+halfBaseHeight;
   p[0][2]=z-halfLength;

   p[1][0]=x+halfWidth; // p[1] ++-
   p[1][1]=y+halfBaseHeight;
   p[1][2]=z-halfLength;

   p[2][0]=x+halfWidth; // p[2] +--
   p[2][1]=y-halfBaseHeight;
   p[2][2]=z-halfLength;

   p[3][0]=x-halfWidth; // p[3] ---
   p[3][1]=y-halfBaseHeight;
   p[3][2]=z-halfLength;

   p[4][0]=x+halfWidth; // p[4] +++
   p[4][1]=y+halfBaseHeight;
   p[4][2]=z+halfLength;

   p[5][0]=x-halfWidth; // p[5] -++
   p[5][1]=y+halfBaseHeight;
   p[5][2]=z+halfLength;

   p[6][0]=x-halfWidth; // p[6] --+
   p[6][1]=y-halfBaseHeight;
   p[6][2]=z+halfLength;

   p[7][0]=x+halfWidth; // p[7] +-+
   p[7][1]=y-halfBaseHeight;
   p[7][2]=z+halfLength;

	p[8][0]=x; // p[8] back of the top of the roof
	p[8][1]=y+halfBaseHeight+roofHeight;
	p[8][2]=z-halfLength;

	p[9][0]=x; // p[9] front of the top of the roof
	p[9][1]=y+halfBaseHeight+roofHeight;
	p[9][2]=z+halfLength;

	p[10][0] = x - halfWidth/10.0f;// p[10] bottom left of door
	p[10][1] = y - halfBaseHeight;
	p[10][2] = z + halfLength + offset;

	p[11][0] = x + halfWidth/10.0f;// p[11] bottom right of door
	p[11][1] = y - halfBaseHeight;
	p[11][2] = z + halfLength + offset;

	p[12][0] = x + halfWidth/10.0f;// p[12] top right of door
	p[12][1] = y;
	p[12][2] = z + halfLength + offset;

	p[13][0] = x - halfWidth/10.0f;// p[13] top left of door
	p[13][1] = y;
	p[13][2] = z + halfLength + offset;

	p[14][0] = x - (halfWidth/20.0f);// p[14] door handle location
	p[14][1] = y - (halfBaseHeight/2.0f);
	p[14][2] = z + halfLength + (2.0f * offset);




	// enable texture mapping for the house
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, siding1Texture);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		glMaterialfv(GL_FRONT, GL_SPECULAR, house_spec);

		glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x-halfWidth, y-halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x+halfWidth, y-halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 3.0); 
			glVertex3f(x+halfWidth, y+halfBaseHeight, z+halfLength);
			glTexCoord2f(0.0, 3.0); 
			glVertex3f(x-halfWidth, y+halfBaseHeight, z+halfLength);
		glEnd();

/*		glBegin( GL_POLYGON );// front face of base
	//		glColor3f(0.5, 0.5, 0.5);  

			glVertex3fv(p[5]);
			glVertex3fv(p[6]);
			glVertex3fv(p[7]);
			glVertex3fv(p[4]);

		glEnd();*/

		glBegin(GL_QUADS);
			glNormal3f(1.0, 0.0, 0.0);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x+halfWidth, y-halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x+halfWidth, y-halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 3.0); 
			glVertex3f(x+halfWidth, y+halfBaseHeight, z-halfLength);
			glTexCoord2f(0.0, 3.0); 
			glVertex3f(x+halfWidth, y+halfBaseHeight, z+halfLength);
		glEnd();
		
/*		glBegin( GL_POLYGON );// right face of base
	//		glColor3f(1.0, 1.0, 0.0);  

			glVertex3fv(p[4]);
			glVertex3fv(p[7]);
			glVertex3fv(p[2]);		
			glVertex3fv(p[1]);
 		glEnd();	*/

		
		glBegin(GL_QUADS);
			glNormal3f(0.0, 0.0, -1.0);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x+halfWidth, y-halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x-halfWidth, y-halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 3.0); 
			glVertex3f(x-halfWidth, y+halfBaseHeight, z-halfLength);
			glTexCoord2f(0.0, 3.0); 
			glVertex3f(x+halfWidth, y+halfBaseHeight, z-halfLength);
		glEnd();
		
/*		glBegin( GL_POLYGON );// rear face of base
		
	//		glColor3f(0.0, 1.0, 1.0);  

			glVertex3fv(p[1]);
			glVertex3fv(p[2]);
			glVertex3fv(p[3]);
			glVertex3fv(p[0]);

		glEnd();

		glBegin(GL_POLYGON);// bottom face of base

	//		glColor3f(0.0, 0.5, 1.0);  
			glNormal3f(0.0, -1.0, 0.0);

			glVertex3fv(p[2]);
			glVertex3fv(p[7]);
			glVertex3fv(p[6]);      
			glVertex3fv(p[3]);
 
		glEnd();*/

		glBegin(GL_QUADS);
			glNormal3f(-1.0, 0.0, 0.0);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x-halfWidth, y-halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x-halfWidth, y-halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 3.0); 
			glVertex3f(x-halfWidth, y+halfBaseHeight, z+halfLength);
			glTexCoord2f(0.0, 3.0); 
			glVertex3f(x-halfWidth, y+halfBaseHeight, z-halfLength);
		glEnd();

/*		glBegin(GL_POLYGON);// left face of base

	//		glColor3f(0.0, 1.0, 0.0);  
			glVertex3fv(p[6]);      
			glVertex3fv(p[5]);
 			glVertex3fv(p[0]);
			glVertex3fv(p[3]);


		glEnd();  

		glBegin (GL_POLYGON);// top face
	//		glColor3f(1.0, 0.0, 1.0);  
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3fv(p[0]);
			glVertex3fv(p[5]);
			glVertex3fv(p[4]);
			glVertex3fv(p[1]);
 
		glEnd();*/

		// the base of the house is drawn.

		glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x-halfWidth, y+halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x+halfWidth, y+halfBaseHeight, z+halfLength);
			glTexCoord2f(0.5, 2.0); 
			glVertex3f(x, y+halfBaseHeight+roofHeight, z+halfLength);
		glEnd();

/*		glBegin (GL_POLYGON);// front face of roof
	//		glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3fv(p[5]);
			glVertex3fv(p[4]);
			glVertex3fv(p[9]);

		glEnd();*/

		glBegin(GL_TRIANGLES);
			glNormal3f(0.0f, 0.0f, -1.0f);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x+halfWidth, y+halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x-halfWidth, y+halfBaseHeight, z-halfLength);
			glTexCoord2f(0.5, 2.0); 
			glVertex3f(x, y+halfBaseHeight+roofHeight, z-halfLength);
		glEnd();

/*		glBegin (GL_POLYGON);// rear face of roof
	//		glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3fv(p[0]);
			glVertex3fv(p[8]);
			glVertex3fv(p[1]);

		glEnd();*/

		glBindTexture(GL_TEXTURE_2D, shingleTexture);

		glBegin(GL_QUADS);
			glNormal3f(-0.707f, 0.707f, 0.0f);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x-halfWidth, y+halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x-halfWidth, y+halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 3.0); 
			glVertex3f(x, y+halfBaseHeight+roofHeight, z+halfLength);
			glTexCoord2f(0.0, 3.0); 
			glVertex3f(x, y+halfBaseHeight+roofHeight, z-halfLength);
		glEnd();

/*		glBegin (GL_POLYGON);// left roof top
			glColor3fv(color1);
			glVertex3fv(p[0]);
			glVertex3fv(p[5]);
			glVertex3fv(p[9]);
			glVertex3fv(p[8]);

		glEnd();*/

		glBegin(GL_QUADS);
			glNormal3f(0.707f, 0.707f, 0.0f);
			glTexCoord2f(0.0, 0.0); 
			glVertex3f(x+halfWidth, y+halfBaseHeight, z+halfLength);
			glTexCoord2f(1.0, 0.0);
			glVertex3f(x+halfWidth, y+halfBaseHeight, z-halfLength);
			glTexCoord2f(1.0, 3.0); 
			glVertex3f(x, y+halfBaseHeight+roofHeight, z-halfLength);
			glTexCoord2f(0.0, 3.0); 
			glVertex3f(x, y+halfBaseHeight+roofHeight, z+halfLength);
		glEnd();

/*		glBegin (GL_POLYGON);// right roof top
	//		glColor3f(0.0f, 0.0f, 0.0f);
			glVertex3fv(p[4]);
			glVertex3fv(p[1]);
			glVertex3fv(p[8]);
			glVertex3fv(p[9]);

		glEnd();*/

		 glDisable(GL_TEXTURE_GEN_S);
		 glDisable(GL_TEXTURE_GEN_T);
		 glDisable(GL_TEXTURE_2D);


   // the roof of the house is drawn.


	glBegin (GL_POLYGON);// door
		glColor3fv(color3);
		glNormal3f(0.0f, 0.0, 1.0f);
		glVertex3fv(p[10]);
		glVertex3fv(p[11]);
		glVertex3fv(p[12]);
		glVertex3fv(p[13]);

	glEnd();


	glBegin (GL_POINTS);// door knob
		glColor3fv(color1);
		glNormal3f(0.0f, 0.0, 1.0f);
		glVertex3fv(p[14]);
		
	glEnd();
	
   // the door of the house is drawn.

	glEndList();

} // end initHouse

//---------------------------------------------------------------------
// Method:  draw
// Function:  Draws a house object with the size and location specified 
//			 by the class data members.
// Parameters:	 None
//				
// Returns:  Void
// Called By: 
// Calls:  None
//---------------------------------------------------------------------
void House::draw()
{
	glCallList(houseList);

} // end draw


GLfloat House::getRadius() {
   return radius;
} // end getRadius


GLfloat House::getX() {
   return x;
} // end getX


GLfloat House::getZ() {
   return z;
} // end getZ


bool House::isDestroyed() {
   return destroyed;
} // end isDestroyed


void House::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void House::destroy() {
   destroyed = true;
} // end destroy


Explosion* House::getExplosion() {
   return explosion;
} // end getExplosion


void House::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


void House::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void House::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void House::unForwardCollide() {
   forwardCollided = false;
} // end unForwardcollide


void House::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardcollide


bool House::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool House::isBackwardCollided() {
   return backwardCollided;
} // end isForwardCollided


int House::getPointValue() {
   return pointValue;
} // end getPointValue

// *********************** END HOUSE CLASS *****************************


