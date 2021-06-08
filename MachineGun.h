#ifndef ___MACHINEGUN_H__
#define ___MACHINEGUN_H__

#include <gl\gl.h>
#include <gl\glu.h>

class MachineGun {

	public:
	
   // Constructor
   MachineGun(){}

   // Initializes the pyramid height and width
	void init();

   // Renders a pyramid center about the local origin
	void draw();

	private:

	GLuint MachineGunList;// display list identifier

};

#endif