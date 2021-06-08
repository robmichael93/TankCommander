#include "stdafx.h"
#include "fontClasses.h"


void CBitMapFont::init(CDC* m_pDC, int size, char* fontname)
{
	// Generate font display list
	flatTextBase = glGenLists( 256 );

	CFont* oldfont; // Pointer to old font object

	if ( NULL != fontname ) {

		CFont newfont; // Create a temporary GDI font object

		LOGFONT logfont;
	
		logfont.lfHeight		= -size; // Specifies the height, in logical units, of the font

		logfont.lfWidth			= 0; // Average width, in logical units

		logfont.lfEscapement	= 0; // angle, in tenths of degrees, of each line of text

		logfont.lfOrientation	= logfont.lfEscapement; //Angle, in tenths of degrees, 
																		// of each character's base line 
		logfont.lfWeight		= FW_NORMAL; // Specifies the weight of the font

		logfont.lfItalic		= FALSE; // Specifies an italic font if set to TRUE

		logfont.lfUnderline		= FALSE; // Specifies an underlined font if set to TRUE.

		logfont.lfStrikeOut		= FALSE; // Specifies a strikeout font if set to TRUE.

		logfont.lfCharSet		= ANSI_CHARSET; // Specifies an ansi character set.

		logfont.lfOutPrecision	= OUT_DEFAULT_PRECIS; // Specifies the output precision

		logfont.lfClipPrecision	= CLIP_DEFAULT_PRECIS; // Specifies the clipping precision.

		logfont.lfQuality		= DEFAULT_QUALITY;	// Specifies the output quality

		logfont.lfPitchAndFamily = FF_DONTCARE|DEFAULT_PITCH; // Specifies the pitch and 
																			// family of the font. 
		lstrcpy ( logfont.lfFaceName, fontname ); // Specify the typeface name of the font

		newfont.CreateFontIndirect( &logfont ); // Create the requested font
		
		oldfont =	m_pDC->SelectObject( &newfont ); // Select the font into the DC

	}
	else {

		// make the system font the device context's selected font
		oldfont =	(CFont*)m_pDC->SelectStockObject( SYSTEM_FONT );

	}
	

	// Create a set of display lists based on the glyphs of the font 
   if (FALSE == wglUseFontBitmaps( m_pDC->m_hDC, 0, 256, flatTextBase )){

		glDeleteLists( flatTextBase, 256 );
		flatTextBase  = 0;
	}
   else {
		m_pDC->SelectObject( oldfont ); // Restore the old font to the DC
	}


} // end CBitMapFont::init



// Output bitmap text to a specified screen position
void CBitMapFont::screenTextOutput(int x, int y, int winX, int winY, const char * const textstring)
{
	GLint renderMode;

	glGetIntegerv(GL_RENDER_MODE, &renderMode);

	// Do not execute if in the selection mode
	if (renderMode != GL_SELECT) {

		GLboolean lightFlag = glIsEnabled(GL_LIGHTING); // Store lighting mode

		// Turn lighting off for bitmap text
		if (lightFlag == GL_TRUE) {
			glDisable(GL_LIGHTING); 
		}

		// Set up 2D orthographic projection
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, winX, 0.0, winY);
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();	

		// Set position for first letter of the text string
		glRasterPos2i(x, y);
		
		// Output the text
		renderText(textstring);
		
		// Restore the modelview and projection matices
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);

			// Restore the lighting mode
		if (lightFlag == GL_TRUE) {
			glEnable(GL_LIGHTING); // Turn Lighting on
		}
	}

} // end CBitMapFont::screenTextOutput


//Output text in the specified font at the current raster position
void CBitMapFont::renderText(const char * const textstring)
{
	// Check for valid font and string
	if (0 == textstring ) {
		return;
	}

	GLsizei size = strlen( textstring );

	glListBase( flatTextBase ); // Set display list base

	// Output the display lists for each character
	glCallLists( size, GL_UNSIGNED_BYTE, (const GLvoid*)textstring ); 

} // end CBitMapFont::renderText


void C3DFont::init(CDC* m_pDC, int size, char* fontname, float extrude)
{
	// Generate font display list	
	textBase = glGenLists(256);

	CFont newfont;  // Create a temporary GDI font object
	CFont* oldfont; // Pointer to old font object

	// structure defining the attributes of a font. 
	LOGFONT     logfont; 

	// lfHeight can't be used to change the font size
	logfont.lfHeight		= -size;	// Specifies the height, in logical units, of the font
											//	Use glScale to change size
	logfont.lfWidth			= 0;	// Average width, in logical units

	logfont.lfEscapement	= 0;		// angle, in tenths of degrees, of each line of text

	logfont.lfOrientation	= logfont.lfEscapement; //Angle, in tenths of degrees, 
																	// of each character's base line 
	logfont.lfWeight		= FW_NORMAL;	// Specifies the weight of the font, 
													// in the range 0 through 1000
	logfont.lfItalic		= FALSE;		// Specifies an italic font if set to TRUE

	logfont.lfUnderline		= FALSE;	// Specifies an underlined font if set to TRUE.

	logfont.lfStrikeOut		= FALSE;	// Specifies a strikeout font if set to TRUE.

	logfont.lfCharSet		= ANSI_CHARSET; // Specifies an ansi character set.

	logfont.lfOutPrecision	= OUT_TT_ONLY_PRECIS;	// Specifies the output precision

	logfont.lfClipPrecision	= CLIP_DEFAULT_PRECIS;	// Specifies the clipping precision. 

	logfont.lfQuality		= DEFAULT_QUALITY;			// Specifies the output quality

	logfont.lfPitchAndFamily = FF_DONTCARE|DEFAULT_PITCH; // Specifies the pitch and 
																			// family of the font. 
	lstrcpy ( logfont.lfFaceName, fontname ); // Specify the typeface name of the font

	newfont.CreateFontIndirect( &logfont ); // Create the requested font

	oldfont =	m_pDC->SelectObject( &newfont );	// Select the font into the DC


   // Create a set of display lists based on the glyphs of the TrueType font 
	// notice that we really waste the first 32 spaces....
	// if there's a problem delete the display lists
	// Note that this single call takes MOST of the initialization time
	// for the COpenGLView class (probably a couple of seconds!) 
	if ( FALSE == wglUseFontOutlines( m_pDC->m_hDC, 0, 256, textBase, 0.0f, 
									extrude, WGL_FONT_POLYGONS,  NULL) )	{	
		glDeleteLists( textBase, 256 ); 
		textBase  = 0;
	}
	else	{
		m_pDC->SelectObject( oldfont ); // Restore the old font to the DC
	}

} // end C3DFont::init


//Output 3D text in the specified font
void C3DFont::renderText(const char * const textstring)
{
	GLint frontFace;
	
	glGetIntegerv(GL_FRONT_FACE, &frontFace);	// save polygon front face mode

	// Check for valid font and string
	if (0 == textstring ) {
		return;
	}

	GLsizei size = strlen( textstring );

	glListBase( textBase ); // Set display list base

	// Output the display lists for each character
	glCallLists( size, GL_UNSIGNED_BYTE, (const GLvoid*)textstring );
	
		// Restore the polygon front face mode
	if (frontFace == GL_CCW) {
		glFrontFace(GL_CCW);
	}
	else {
		glFrontFace(GL_CW);
	}

} // end C3DFont::renderText
