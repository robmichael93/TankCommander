// OpenGLView.h : interface of the COpenGLView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPENGLVIEW_H__0BFF046C_8B7E_11D5_8639_00E01890ACE0__INCLUDED_)
#define AFX_OPENGLVIEW_H__0BFF046C_8B7E_11D5_8639_00E01890ACE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VIEWPOINT_Z -10
#define REFPOINT_Z -1000

#include "draw.h"
#include <mmsystem.h>
#include "RotationDialog.h"	// Added by ClassView
#include "fontClasses.h"
#include <math.h>

class COpenGLView : public CView
{
protected: // create from serialization only
	COpenGLView();
	DECLARE_DYNCREATE(COpenGLView)

// Attributes
public:
	COpenGLDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CRotationDialog dlg;
	//{{AFX_MSG(COpenGLView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRestoreView();
	afx_msg void OnSolid();
	afx_msg void OnWireframe();
	afx_msg void OnToggleLighting();
	afx_msg void OnToggleLight0();
	afx_msg void OnAnimationOn();
	afx_msg void OnAnimationOff();
	afx_msg void OnRotationDialog();
	afx_msg void OnPan();
	afx_msg void OnWalk();
	afx_msg void OnStudy();
	afx_msg void OnFly();
	virtual afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnToggleLight1();
	afx_msg void OnToggleLight2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// select the desired pixel format
	virtual BOOL setupPixelFormat( void ); 

	// initialize the OpenGL state machine
   virtual BOOL OpenGLInit(); 

   // Set the view point
   virtual void setViewPoint();
   
	// Draw scene objects
   virtual void drawScene();

   // Update scene objects
   virtual void updateScene();  

	// Timing and Frame rate calculation functions
	virtual DWORD	ElapsedTimeinMSSinceLastRender( void )
		{ return( m_ElapsedTime-m_previousElapsedTime);}
	virtual int	FramesPerSecond( void );
	virtual void displayFrameRate( void );	
   
   // Class Data Members

   // Viewing Parameters
	GLfloat  viewPointZ;
	GLfloat refPointZ;

  //Clear Color
   GLfloat clearColor[4];

	// Scene Paramters
 	GLfloat rotationAngles[3];  

	// Variables for elapsed timing calculations
	DWORD	m_ElapsedTime, m_previousElapsedTime;
	BOOL	m_bAnimationRunning; 	// boolean to drive animation
	CString	m_WindowTitle; // string variable for constructing the window title

	// Window information storage
	GLuint winSizeY, winSizeX;	  // window hieght and width in pixels

	HGLRC   m_hRC; //OpenGL Rendering Context
	CDC*     m_pDC; //Windows Device Context

   enum viewType {WALK, PAN, STUDY, FLY};

   // Viewing Methods

	virtual void computeFlyView();

	// Viewing Data Members

	GLint xCenter, yCenter;	  				// window center location in pixels

	GLint mouseX, mouseY;					// previous mouse position in pixels

	GLfloat viewPointX, viewPointY; 		//view point coordinates
	GLfloat refPointX, refPointY; 		// view reference coordinates

	GLfloat rotationX, rotationY;
	GLfloat heading, pitch;
	viewType viewPointMode;

	CBitMapFont flatFont;
	C3DFont strokeFont;

};

#ifndef _DEBUG  // debug version in OpenGLView.cpp
inline COpenGLDoc* COpenGLView::GetDocument()
   { return (COpenGLDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLVIEW_H__0BFF046C_8B7E_11D5_8639_00E01890ACE0__INCLUDED_)
