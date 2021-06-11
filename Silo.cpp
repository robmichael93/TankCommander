#include "stdafx.h"
#include "Silo.h"

//---------------------------------------------------------------------
// Method:  init
// Author:  Rick Sanders
// Function:  Initializes a 3D Silo.
//			     The silo is oriented in the the xz plane.
//			     Compiles a display list to be used when drawing the silo.
// Parameters: 
//				x - x coordinate of the middle of the silo
//				y - y coordinate of the middle of the silo
//				z - z coordinate of the middle of the silo
//				siloRadius - radius of silo.
//				siloHeight - the height of the silo.
//				
// Returns: None
// Called By: 
// Calls: None
//---------------------------------------------------------------------


void Silo::init(float xPos, float yPos, float zPos, float siloRadius, 
					 float siloHeight, int brickTex, int shingleTex)
{
	radius = siloRadius;
	height = siloHeight;
	x = xPos;
	y = yPos;
	z = zPos;
   explosion = 0;
   destroyed = false;
   forwardCollided = false;
   backwardCollided = false;
   damageCapacity = (2.0f * 3.14159f * radius * height) / 100.0f;
   pointValue = (int) damageCapacity;
   brickTexture = brickTex;
   shingleTexture = shingleTex;

	//load the brick texture
//	loadBrickTexture();

	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
   gluQuadricTexture(qobj, GL_TRUE);
	siloList = glGenLists(1);

	glNewList(siloList, GL_COMPILE);

		glPushMatrix();

			//material property values
			GLfloat silo_spec[] = {0.5f, 0.5f, 0.5f, 1.0f};
			GLfloat silo_mat_dif[] = {0.7f, 0.4f, 0.1f, 1.0f};


		//   float p[3][3];    // array to hold coords for the silo.
			
			//create the list for generating a silo


			//define the color and material properties
			GLfloat color1[3] = { 0.5f, 0.5f, 0.5f };
			glMaterialfv(GL_FRONT, GL_SPECULAR, silo_spec);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, silo_mat_dif);

			
			// enable texture mapping of the silo
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, brickTexture);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPEAT);
/*				glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
*/
				// create the quadric

				glTranslatef(0.0f, siloHeight, 0.0f);
				glRotatef(90, 1.0f, 0.0f, 0.0f);
				gluCylinder(qobj, radius, radius, height,
								15, 5);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
			
//			loadShingleTexture();

			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, shingleTexture);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
				glEnable(GL_TEXTURE_GEN_S);
				glEnable(GL_TEXTURE_GEN_T);
				gluSphere(qobj, radius, 15, 5);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

	glEndList();

} // end initSilo

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
void Silo::draw()
{
	glCallList(siloList);

} // end draw

GLfloat Silo::getRadius() {
   return radius;
} // end getRadius


GLfloat Silo::getX() {
   return x;
} // end getX


GLfloat Silo::getZ() {
   return z;
} // end getZ


void Silo::loadBrickTexture()
{
	int numOfTextures = 1;
	
	glGenTextures(numOfTextures, &brickTexture);
	ASSERT(brickTexture != 0);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glBindTexture(GL_TEXTURE_2D, brickTexture);
	AUX_RGBImageRec* m_pRGBImage;
	m_pRGBImage = auxDIBImageLoadA("tiles.bmp");
	ASSERT (m_pRGBImage != 0);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_LINEAR_MIPMAP_LINEAR );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB,
						m_pRGBImage->sizeX,
						m_pRGBImage->sizeY,
						GL_RGB, GL_UNSIGNED_BYTE,
						m_pRGBImage->data );
	LocalFree( m_pRGBImage );

}

void Silo::loadShingleTexture()
{
	int numOfTextures = 1;
	
	glGenTextures(numOfTextures, &shingleTexture);
	ASSERT(shingleTexture != 0);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glBindTexture(GL_TEXTURE_2D, shingleTexture);
	AUX_RGBImageRec* m_pRGBImage;
	m_pRGBImage = auxDIBImageLoadA("shingle.bmp");
	ASSERT (m_pRGBImage != 0);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_LINEAR_MIPMAP_LINEAR );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB,
						m_pRGBImage->sizeX,
						m_pRGBImage->sizeY,
						GL_RGB, GL_UNSIGNED_BYTE,
						m_pRGBImage->data );
	LocalFree( m_pRGBImage );

}


bool Silo::isDestroyed() {
   return destroyed;
} // end isDestroyed


void Silo::startExplosion() {
   explosion = new Explosion();
   explosion->init(radius);
} // end startExplosion


void Silo::destroy() {
   destroyed = true;
} // end destroy


Explosion* Silo::getExplosion() {
   return explosion;
} // end getExplosion


void Silo::takeDamage(GLfloat damage) {
   damageCapacity -= damage;
   if (damageCapacity <= 0.0) {
      destroyed = true;
   } // end if
} // end takeDamage


void Silo::forwardCollide() {
   forwardCollided = true;
} // end forwardCollide


void Silo::backwardCollide() {
   backwardCollided = true;
} // end backwardCollide


void Silo::unForwardCollide() {
   forwardCollided = false;
} // end unForwardCollide


void Silo::unBackwardCollide() {
   backwardCollided = false;
} // end unBackwardCollide


bool Silo::isForwardCollided() {
   return forwardCollided;
} // end isForwardCollided


bool Silo::isBackwardCollided() {
   return backwardCollided;
} // end isBackwardCollided


int Silo::getPointValue() {
   return pointValue;
} // end getPointValue

// *********************** END SILO CLASS *****************************


