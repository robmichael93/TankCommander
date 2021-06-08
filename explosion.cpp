#include "stdafx.h"
#include "Explosion.h"

//---------------------------------------------------------------------
// Method: init
// Author: Ernesto Salles
// Function: Initializes explosion. at radius .1 units, and indicates 
//              that it should increase in size
//			   
// Parameters: none
//				
// Returns: None
// Called By: 
// Calls: None
//---------------------------------------------------------------------

void Explosion::init(GLfloat maxRad)
{
	
	radius = 0.1;
   maxRadius = 2 * maxRad;
	getBigger = true;
	explosionDone = false;

	// load the sky texture
	loadFireTexture();

} // end initExplosion

//---------------------------------------------------------------------
// Method: draw
// Function: Draws the explosion.  uses a global variable to keep track 
//				of the explosion's size.  
// Parameters: 
//			None
//				
// Returns: Void
// Called By: 
// Calls: None
//---------------------------------------------------------------------
void Explosion::draw()
{
	// the material property values
	GLfloat explosion_spec[] = { 0.2, 0.1, 0.0, 1.0};
	GLfloat explosion_mat_dif[] = {0.7, 0.4, 0.1, 1.0};

	// if the explosion is underway, draw it
	if(!explosionDone)
	{

	//	define the color and material properties
		glColor3f( 0.94f, 0.59f, 0.12f);
		glMaterialfv(GL_FRONT, GL_SPECULAR, explosion_spec);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, explosion_mat_dif);
		
		// if explosion should get bigger, increase the radius, otherwise decrease it
		if (getBigger)
			radius = radius + 1.0f;
		else
			radius = radius - 1.0f;

		//if the radius is 0, the explosion is done
		if (radius <= 0.0)
			explosionDone = true;

		// if the radius is 5, the explosion is maxed, and should start decreasing
		if (radius >= maxRadius)
			getBigger = false;
		
	// enable texture mapping of the sky
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fireTexture);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexGend(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGend(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

		// create a quadric for the explosion
		GLUquadricObj *qobj;
		qobj = gluNewQuadric();
		gluQuadricDrawStyle(qobj, GLU_FILL);
		gluQuadricOrientation(qobj, GLU_OUTSIDE);
		gluQuadricNormals(qobj, GLU_SMOOTH);	

		// draw the explosion and delete the quadric object
      glPolygonMode(GL_BACK, GL_FILL);
		gluSphere(qobj, radius, 10, 10);
		gluDeleteQuadric(qobj);
      glPolygonMode(GL_BACK, GL_LINE);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);

	}

} // end draw

void Explosion::loadFireTexture()
{
	int numOfTextures = 1;
	
	glGenTextures(numOfTextures, &fireTexture);
	ASSERT(fireTexture != 0);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glBindTexture(GL_TEXTURE_2D, fireTexture);
	AUX_RGBImageRec* m_pRGBImage2;
	m_pRGBImage2 = auxDIBImageLoadA("flames.bmp" );
	ASSERT (m_pRGBImage2 != 0);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					 GL_LINEAR_MIPMAP_LINEAR );
	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB,
						m_pRGBImage2->sizeX,
						m_pRGBImage2->sizeY,
						GL_RGB, GL_UNSIGNED_BYTE,
						m_pRGBImage2->data );
	LocalFree( m_pRGBImage2 );

}


bool Explosion::isExplosionDone() {
   return explosionDone;
} // end isExplosionDone


bool Explosion::isGrowing() {
   return getBigger;
} // end getBigger