#if !defined(AFX_MYOPENGLVIEW_H__0BFF0473_8B7E_11D5_8639_00E01890ACE0__INCLUDED_)
#define AFX_MYOPENGLVIEW_H__0BFF0473_8B7E_11D5_8639_00E01890ACE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyOpenGLView.h : header file
//

#include "OpenGLView.h"
#include "floor.h"
#include "pyramid.h"
#include "friend.h"
#include "good.h"
#include "MachineGun.h"
#include "foe.h"
#include "house.h"
#include "silo.h"
#include "pine.h"
#include "smallpine.h"
#include "Explosion.h"
#include "shell.h"
#include "bullet.h"
#include "MySocket.h"
#include "JoinDialog.h"
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include <vector>

using namespace std;


#define NUMBER_OF_ENEMIES 20
#define NUMBER_OF_HOUSES 58
#define NUMBER_OF_PYRAMIDS 20
#define NUMBER_OF_FRIENDLIES 5
#define NUMBER_OF_PINES 44
#define NUMBER_OF_SMALL_PINES 75
#define NUMBER_OF_SILOS 5

/////////////////////////////////////////////////////////////////////////////
// CMyOpenGLView view

struct Packet {
   // packet type:
   // 0 Friend (opponent)
   // 1 Shell
   // 2 Bullet
   // 3 Damage to our tank
   // 4 Damage to friendly tanks
   // 5 Damage to enemy tanks
   // 6 Damage to houses
   // 7 Damage to pine trees
   // 8 Damage to small pine trees
   // 9 Damage to silos
   // 10 Spawn site notification
   // 11 Damage to opponent
   int packetType;
   int id;
   GLfloat x;
   GLfloat y;
   GLfloat z;
   GLfloat azimuth;
   GLfloat elevation;
   GLfloat rotation;
   GLfloat rotationX;
   GLfloat rotationY;
   GLfloat speed;
   GLfloat damage;
//   bool isDestroyed;
   bool mgLatch;
   bool spawnSiteActive;
};

class CMyOpenGLView : public COpenGLView
{
protected:
	CMyOpenGLView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyOpenGLView)

// Attributes
public:

// Operations
public:
   virtual void OnDraw(CDC* pDC);
   void setUpLighting();
   double ElapsedTimeInMSSinceLastShot() {
      return timeGetTime() - previousShotTime;
   } //
   bool setUpTextures();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyOpenGLView)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyOpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyOpenGLView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCollisionOn();
	afx_msg void OnCollisionOff();
	afx_msg void OnHost();
	afx_msg void OnJoin();
	afx_msg void OnDisconnect();
	afx_msg void OnSingle();
	afx_msg void OnMulti();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
   // Draw scene objects
   virtual void drawScene();

   // Set the view point
   virtual void setViewPoint();

   virtual void updateScene();
   virtual BOOL OpenGLInit();

   GLfloat translationVector[3];

   Friend ourTank;
   MachineGun mg;

   vector<Pyramid*> pyramid;
   vector<Good*> friendly;
   vector<Foe*> enemy;
   vector<House*> house;
   vector<Silo*> silo;
   vector<Pine*> pine;
   vector<SmallPine*> smallPine;
   vector<Shell*> shells;
   vector<Bullet*> bullets;

   Friend opponent;
   MachineGun oppMG;
   vector<Shell*> oppShells;
   vector<Bullet*> oppBullets;

   	//texture
	GLuint brickImage;
	GLuint siding1Image;
	GLuint marbleImage;
	GLuint skyImage;
	GLuint tilesImage;
	GLuint shingleImage;
	GLuint camoImage;
	GLuint dcamoImage;


   GLfloat xDist, yDist, zDist, dist, minDist;
   GLfloat azimuth, elevation, rotation;

   float calculateRelativeBearing(GLfloat, GLfloat);
   void respawn();

   double previousShotTime;
   double elapsedShotTime;
   double gameStartTime;
   bool shotFired;

   bool mgLatch;

   bool collisionDetection;
   bool bulletCollision;
   bool shellCollision;

   bool startGame;
   bool gameOver;
   bool playedFinalSound;
   int spawnSites[4][3];
   bool spawnSiteActive[4];
   int spawnSite;

   int score;

   CString m_ip;
	int m_iPort;
	CMySocket m_clientSocket;
	CMySocket m_serverSocket;
   CMySocket m_receiveSocket;

   CJoinDialog joinDialog;

   bool multiPlayer;
   bool server;
   void CheckError(int);

public:
	void OnConnect();
	void OnClose();
	void OnSend();
	void OnReceive();
	void OnAccept();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYOPENGLVIEW_H__0BFF0473_8B7E_11D5_8639_00E01890ACE0__INCLUDED_)
