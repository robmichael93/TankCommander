// OpenGLView.cpp : implementation of the COpenGLView class
//

#include "stdafx.h"
#include "OpenGL.h"
#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "console.h"
#include <math.h>

#define PI 3.14159

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	//{{AFX_MSG_MAP(COpenGLView)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_RESTORE_VIEW, OnRestoreView)
	ON_COMMAND(ID_SOLID, OnSolid)
	ON_COMMAND(ID_WIREFRAME, OnWireframe)
	ON_COMMAND(ID_TOGGLE_LIGHTING, OnToggleLighting)
	ON_COMMAND(ID_TOGGLE_LIGHT0, OnToggleLight0)
	ON_COMMAND(ID_ANIMATION_ON, OnAnimationOn)
	ON_COMMAND(ID_ANIMATION_OFF, OnAnimationOff)
	ON_COMMAND(ID_ROTATION_DIALOG, OnRotationDialog)
	ON_COMMAND(ID_PAN, OnPan)
	ON_COMMAND(ID_WALK, OnWalk)
	ON_COMMAND(ID_STUDY, OnStudy)
	ON_COMMAND(ID_FLY, OnFly)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TOGGLE_LIGHT1, OnToggleLight1)
	ON_COMMAND(ID_TOGGLE_LIGHT2, OnToggleLight2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView construction/destruction

COpenGLView::COpenGLView(): m_hRC(0), m_pDC(0), 
   	viewPointX(0.0), viewPointY(0.0), viewPointZ(0.0),
		rotationX(0.0), rotationY(0.0), viewPointMode(STUDY),
		refPointX(0.0), refPointY(0.0), refPointZ(-VIEWPOINT_Z),
		pitch(0.0), heading(0.0), 
	   m_bAnimationRunning(TRUE)

{
   // Set the initial rotation angles
	rotationAngles[0] = 0.0;
   rotationAngles[1] = 45.0;
   rotationAngles[2] = 180.0;

   // Set the initial clear color
/*	clearColor[0] = 0.0f;
   clearColor[1] = 0.65f;
   clearColor[2] = 1.0f;
   clearColor[3] = 1.0f;*/
	clearColor[0] = 0.0f;
   clearColor[1] = 0.0f;
   clearColor[2] = 0.0f;
   clearColor[3] = 1.0f;

//   console::setView(this);
//   console::showConsole();
}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
   cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
	// TODO: add draw code for native data here
   m_ElapsedTime = timeGetTime();

	// Keep the paint messages coming
	if ( m_bAnimationRunning ) {
	
		InvalidateRect( 0, FALSE );
		GetParent()->PostMessage(WM_PAINT);
	}	

	// Limit frame rate to 25 frames per second
	if ( ElapsedTimeinMSSinceLastRender() >= 35  || (!m_bAnimationRunning) ) {

       glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	    glMatrixMode( GL_MODELVIEW );
	    glLoadIdentity();

	    // Execute Viewing transformations
	    setViewPoint();

       // Draw the scene objects
       drawScene();

	   glFlush();

	   SwapBuffers( m_pDC->GetSafeHdc() );

      if ( m_bAnimationRunning ) {
         
         updateScene();

      }
		   displayFrameRate();

	   // save the elapsed time, this is used with the  next elapsed time to calculate the
		// elapsed time since a render and control the frame rate
		m_previousElapsedTime = m_ElapsedTime;

   }
}

/////////////////////////////////////////////////////////////////////////////

BOOL COpenGLView::setupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,               // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		16,                             // 16-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	
	SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);

	return TRUE;

} // end SetupPixelFormat

BOOL COpenGLView::OpenGLInit()
{
	m_pDC = new CClientDC(this);

	setupPixelFormat();
	m_hRC = wglCreateContext( m_pDC->GetSafeHdc() );
	wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC );

	GLfloat global_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat lit0_amb[] = {0.05f, 0.05f, 0.05f, 1.0f};
	GLfloat lit0_diffuse[] = {0.75f, 0.75f, 0.75f, 1.0f};
	GLfloat lit0_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};

	glEnable(GL_LIGHTING);

	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient);

	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit0_spec);   
	glEnable( GL_LIGHT0 );

	// Explicitly set shade model to default
	glShadeModel (GL_SMOOTH);               

	// Cull the back faces of polygons
	glPolygonMode( GL_BACK, GL_LINE );

	// specify the clear color
	glClearColor( clearColor[0], clearColor[1], clearColor[2], clearColor[3] );

	// specify the back of the buffer as clear depth
	glClearDepth( 1.0f );

	// enable depth testing
	glEnable( GL_DEPTH_TEST );

	flatFont.init(m_pDC );
	strokeFont.init(m_pDC);



	return TRUE;

} // end OpenGLInit

void COpenGLView::setViewPoint()
{

	// Execute Viewing transformations
	if (viewPointMode == FLY) {
		computeFlyView();		
	}

	gluLookAt(viewPointX, viewPointY, viewPointZ, 
		       refPointX, refPointY, refPointZ,
			    0.0, 1.0, 0.0);

} // end SetViewPoint

// Draw scene objects
void COpenGLView::drawScene()
{
	static GLfloat lit0_posit[] = {10.0f, 10.0f, 10.0f, 0.0f};
   
   //******** Draw Your Objects Here *********

	//Execute drawing commands
	drawFloor(0.0, -3.0, 0.0, 8.0);

	glPushMatrix();
	glRotatef(rotationAngles[0], 1.0f, 0.0f, 0.0f);
	drawcube(0.0, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0f, 0.0f, 0.0f);
	glRotatef(rotationAngles[1], 0.0f, 1.0f, 0.0f);
	drawcube(0.0, 0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0f, 0.0f, 0.0f);
	glRotatef(rotationAngles[2], 0.0f, 0.0f, 1.0f);
	drawRedBall(0.0, 0.0, 0.0, 1.0);
	glPopMatrix();

	glLightfv(GL_LIGHT0, GL_POSITION, lit0_posit);

} // end drawScene

// Update scene objects
void COpenGLView::updateScene()
{
	// Update rotation angles for next display of the scene
	rotationAngles[0] += 5.0;
	rotationAngles[1] += 10.0;
	rotationAngles[2] += 15.0;

   rotationAngles[0] = (rotationAngles[0] < 360.0) ? rotationAngles[0] : 
								  rotationAngles[0] - 360.0f;
	rotationAngles[1] = (rotationAngles[1] < 360.0) ? rotationAngles[1] : 
								  rotationAngles[1] - 360.0f;
	rotationAngles[2] = (rotationAngles[2] < 360.0) ? rotationAngles[2] : 
								  rotationAngles[2] - 360.0f;


} // end updateScene



void COpenGLView::displayFrameRate( void )
{
	// Only update the title every 15 redraws (this is about
	// every 1/2 second)
	static int updateFrame = 15;

	if ( !m_bAnimationRunning || 16 > ++updateFrame )
		return;

	updateFrame = 0;

	char string[256];
	_snprintf( string, 200, "%s ( %d Frames/sec )",
		(const char*)m_WindowTitle, FramesPerSecond() );

	GetParentFrame()->SetWindowText( string );

} // end displayFrameRate


// FramesPerSecond
// fetch frame rate calculations
int COpenGLView::FramesPerSecond( void )
{
	double eTime = ElapsedTimeinMSSinceLastRender();

	if ( 0 == (int)eTime )
		return 0;

	return (int)(1000/(int)eTime);

} // end FramesPerSecond

void COpenGLView::computeFlyView()
{
	static GLfloat hasvector[4][4] = {1.0, 0.0, 0.0, 0.0,
							                0.0, 1.0, 0.0, 0.0,
							                0.0, 0.0,-1.0, 0.0,
							                1.0, 1.0, 1.0, 1.0};
	
   GLfloat *hasvectorPtr = &hasvector[0][0];

	static GLfloat direction[4][4];
	GLfloat *directionPtr = &direction[0][0];

	static float delta_angle = 0.005f;
	static float speed = 0.1f;
	static float deadZoneSize = 25.0f;

	float horzMag = float(xCenter) - mouseX;
	float vertMag = float(yCenter) - mouseY;

	if (fabs(horzMag) > deadZoneSize) {
		heading -= (horzMag * delta_angle);
	}
	
	if (fabs(vertMag) > deadZoneSize) {
		
		pitch -= (vertMag * delta_angle);
	}

	glPushMatrix();
 
      glRotatef(-pitch, 1.0, 0.0, 0.0);
      glRotatef(-heading, 0.0f, 1.0f, 0.0f);

	   glMultMatrixf(hasvectorPtr);
	   glGetFloatv(GL_MODELVIEW_MATRIX, directionPtr);

   glPopMatrix();

	// Compute the new view points
	viewPointX += (speed * direction[2][0]);
	viewPointY += (speed * direction[2][1]);
	viewPointZ += (speed * direction[2][2]);

	// Compute the new referenc points
	refPointX += (speed * direction[2][0]);
	refPointY += (speed * direction[2][1]);
	refPointZ += (speed * direction[2][2]);

	glRotatef(pitch, 1.0, 0.0, 0.0);
   glRotatef(heading, 0.0f, 1.0f, 0.0f);

} // end computeFlyView

// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

void COpenGLView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
   wglMakeCurrent( 0, 0);

   wglDeleteContext( m_hRC );	

	if ( m_pDC ) {
	     delete m_pDC;
	}
   	
}

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	OpenGLInit();
	return 0;
}

void COpenGLView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	winSizeY = (cy == 0) ? 1 : cy;
	winSizeX = (cx == 0) ? 1 : cx;
   mouseX = xCenter = winSizeX / 2;
	mouseY = yCenter = winSizeY / 2;

	// Set viewport to entire client area
	glViewport(0, 0, winSizeX, winSizeY);

	glMatrixMode (GL_PROJECTION);           // Projection matrix stack
	glLoadIdentity();                       // Reset the projection marix stack

	// Set up a perspective projection matrix
	gluPerspective(45.0f, (GLfloat)winSizeX/(GLfloat)winSizeY, 0.25f, 2000.0f);

	glMatrixMode (GL_MODELVIEW);            // Modelview matrix stack

}

void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	// TODO: Add your message handler code here and/or call default
   // handle keyboard inputs
		switch (nChar) {

		// up arrow key
		case VK_UP: 
			break;

		// down arrow key
		case VK_DOWN:
			break;

      case VK_LEFT:
         break;

      case VK_RIGHT:
         break;

      // "Space bar": fire
      case 0x33:
      // "r" reverse key
		case 0x52:
		if (refPointZ < 0.0) {
			refPointZ = -REFPOINT_Z;
		}
		else {
			refPointZ = REFPOINT_Z;
		}

		} // end switch
	
//      refPointX = viewPointX;
//		refPointY = viewPointY;
//	   refPointZ = viewPointZ-VIEWPOINT_Z;

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COpenGLView::OnRestoreView() 
{
	// TODO: Add your command handler code here
	viewPointX = 0.0; refPointX = 0.0;
	viewPointY = 0.0; refPointY = 0.0;
	viewPointZ = VIEWPOINT_Z;  refPointZ = 0.0;

	rotationX = 0.0; 		rotationY = 0.0;
	
	heading = 0.0;  		pitch = 0.0;	

	mouseX = xCenter;	mouseY = yCenter;

}

void COpenGLView::OnSolid() 
{
	// TODO: Add your command handler code here
   // OnSolid

	// Render polygon fronts and fill them
	glPolygonMode(GL_FRONT, GL_FILL);

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);

}

void COpenGLView::OnWireframe() 
{
	// TODO: Add your command handler code here
   // OnWireframe

	// Render polygon fronts in wire frame
	glPolygonMode(GL_FRONT, GL_LINE);	

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);
	
}

void COpenGLView::OnToggleLighting() 
{
	// TODO: Add your command handler code here
   // OnToggleLighting

	if (glIsEnabled(GL_LIGHTING) ) {
		glDisable(GL_LIGHTING); // Turn Lighting off
	}
	else {
		glEnable(GL_LIGHTING); // Turn Lighting on
	}	

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);

}

void COpenGLView::OnToggleLight0() 
{
	// TODO: Add your command handler code here
   // OnToggleLight0

	if (glIsEnabled(GL_LIGHT0) ) {
		glDisable(GL_LIGHT0); // Turn Light 0 off
	}
	else {
		glEnable(GL_LIGHT0); // Turn Light 0 on
	}	

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);

}

void COpenGLView::OnAnimationOn() 
{
	// TODO: Add your command handler code here
   // OnAnimationOn

	m_bAnimationRunning = TRUE;

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);

}

void COpenGLView::OnAnimationOff() 
{
	// TODO: Add your command handler code here
   // OnAnimationOff
	
   m_bAnimationRunning = FALSE;
	GetParentFrame()->SetWindowText( (const char*)m_WindowTitle );

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);

}

void COpenGLView::OnRotationDialog() 
{
	// TODO: Add your command handler code here
	dlg.DoModal();
	
}

void COpenGLView::OnPan() 
{
	// TODO: Add your command handler code here
	viewPointMode = PAN;	
}

void COpenGLView::OnWalk() 
{
	// TODO: Add your command handler code here
	viewPointMode = WALK;	
}

void COpenGLView::OnStudy() 
{
	// TODO: Add your command handler code here
	viewPointMode = STUDY;
}

void COpenGLView::OnFly() 
{
	// TODO: Add your command handler code here
	viewPointMode = FLY;
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int x = point.x;
	int y = point.y;

	if (nFlags == MK_LBUTTON) {
		
		switch(viewPointMode) {

		case (WALK):
			if(y-mouseY > 0) {	
				viewPointZ+=0.5f;
			}
			else if(y-mouseY < 0){
				viewPointZ-=0.5f;
			}
			if(x-mouseX > 0) {
				viewPointX-=0.5f;
			}
			else if(x-mouseX < 0){
				viewPointX+=0.5f;
			}
			break;
		case (PAN):
			if(y-mouseY > 0) {
				viewPointY-=0.5f;
			}
			else if(y-mouseY < 0){ 		
				viewPointY+=0.5f;
			}
			if(x-mouseX > 0) {
				viewPointX+=0.5f;
			}
			else if(x-mouseX < 0){
			viewPointX-=0.5f;
			}
			break;
	
		case (STUDY):
			if(y-mouseY > 0) {	
				rotationX+=5;
			}
			else if(y-mouseY < 0){ 		
				rotationX-=5;
			}
			if(x-mouseX > 0) {
				rotationY+=5;
			}
			else if(x-mouseX < 0){
				rotationY-=5;
			}
			break;
		
		default:
		
			break;
		} // end switch

		if ( viewPointMode != FLY ) {
			refPointX = viewPointX;
			refPointY = viewPointY;
			refPointZ = viewPointZ-VIEWPOINT_Z;
		} // end if
	
		mouseX = x; 
		mouseY = y;

	} // end if

	CView::OnMouseMove(nFlags, point);
}

void COpenGLView::OnToggleLight1() 
{
   // OnToggleLight1

	if (glIsEnabled(GL_LIGHT1) ) {
		glDisable(GL_LIGHT1); // Turn Light 1 off
	}
	else {
		glEnable(GL_LIGHT1); // Turn Light 1 on
	}	

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);
	
}

void COpenGLView::OnToggleLight2() 
{
   // OnToggleLight2

	if (glIsEnabled(GL_LIGHT2) ) {
		glDisable(GL_LIGHT2); // Turn Light 2 off
	}
	else {
		glEnable(GL_LIGHT2); // Turn Light 2 on
	}	

	//Repaint the window
	InvalidateRect( 0, FALSE );
	GetParent()->PostMessage(WM_PAINT);
	
}
