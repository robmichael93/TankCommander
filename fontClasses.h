#ifndef ___FONTCLASSES_H__
#define ___FONTCLASSES_H__

#include <gl\gl.h>
#include <gl\glu.h>


class CBitMapFont {

	public:
		
	CBitMapFont(){};

	void init(CDC* m_pDC, int size = 24, char* fontname = "MS Sans Serif");

	// Output bitmap text to a specified screen position
	void screenTextOutput(int x, int y, int winX, int winY, 
											 const char * const textstring);

	//Output text in the specified font at the current raster position
	void renderText(const char * const textstring);

	private:

	GLuint flatTextBase;

};

class C3DFont {

	public:
		
	C3DFont(){};

	void init(CDC* m_pDC, int size = 12, char* fontname = "Arial", float extrude = 0.1f);

	//Output 3D text in the specified font
	void renderText(const char * const textstring);

	private:

	GLuint textBase;

};
#endif