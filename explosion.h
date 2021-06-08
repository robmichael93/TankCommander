#ifndef ___EXPLOSION_H_
#define ___EXPLOSION_H_

#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

class Explosion
{
	public:

		//constructor
		Explosion() {};
	
		// initializes the explosion
		void init(GLfloat);

		//renders the explosion
		void draw();

      bool isExplosionDone();
      bool isGrowing();

		//the radius of the explosion
		GLfloat radius;
      GLfloat maxRadius;


	private:

		// boolean used to determine if radius of explosion should increase or decrease
		bool getBigger;

		// boolean used to indicate that the explosion is complete
		bool explosionDone;

		// texture	
		GLuint fireTexture;   

		// loads the fire texture
		void loadFireTexture();
};

#endif