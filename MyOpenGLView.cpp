// MyOpenGLView.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGLDoc.h"
#include "MyOpenGLView.h"
#include <math.h>

#define PI 3.14159

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUFFER_LENGTH 64

/////////////////////////////////////////////////////////////////////////////
// CMyOpenGLView

IMPLEMENT_DYNCREATE(CMyOpenGLView, COpenGLView)

CMyOpenGLView::CMyOpenGLView(): azimuth(0.0), elevation(0.0), rotation(0.0)
{
   COpenGLView::COpenGLView( );
}

CMyOpenGLView::~CMyOpenGLView()
{
   for(int py = 0; py < pyramid.size(); py++){
      delete pyramid[py];
   }
   for(int f = 0; f < friendly.size(); f++){
      delete friendly[f];
   }
   for(int e = 0; e < enemy.size(); e++){
      delete enemy[e];
   }
   for(int h = 0; h < house.size(); h++){
      delete house[h];
   }
   for(int s = 0; s < silo.size(); s++){
      delete silo[s];
   }   
   for(int i = 0; i < pine.size(); i++){
	   delete pine[i];
   }
   for(int j = 0; j < smallPine.size(); j++){
	   delete smallPine[j];
   }
   for (i = 0; i < shells.size(); i++) {
      delete shells[i];
   }
   for (i = 0; i < bullets.size(); i++) {
      delete bullets[i];
   }
   for (i = 0; i < oppShells.size(); i++) {
      delete oppShells[i];
   }
   for (i = 0; i < oppBullets.size(); i++) {
      delete oppBullets[i];
   }
}

GLuint textNames[8] = {0};

BOOL CMyOpenGLView::OpenGLInit() {

   COpenGLView::OpenGLInit();

   m_iPort = 12345;
   multiPlayer = false;
   server = false;
	m_serverSocket.SetParent(this);
   m_receiveSocket.SetParent(this);
	m_clientSocket.SetParent(this);

   xDist = yDist = zDist = minDist = 0.0f;
   collisionDetection = true;
   bulletCollision = false;
   shellCollision = false;
   previousShotTime = 0.0;
   elapsedShotTime = 0.0;
   shotFired = false;
   mgLatch = false;
   score = 0;
   startGame = false;
   gameOver = false;
   playedFinalSound = false;

   setUpLighting();
   setUpTextures();

   ourTank.init(textNames[6]);
   mg.init();

   opponent.init(textNames[6]);
   oppMG.init();

   spawnSites[0][0] = -290;
   spawnSites[0][1] = -360;
   spawnSites[0][2] = 315;
   spawnSites[1][0] = 200;
   spawnSites[1][1] = -450;
   spawnSites[1][2] = 25;
   spawnSites[2][0] = 200;
   spawnSites[2][1] = 350;
   spawnSites[2][2] = 145;
   spawnSites[3][0] = -350;
   spawnSites[3][1] = 150;
   spawnSites[3][2] = 260;
   spawnSiteActive[0] = spawnSiteActive[1] = spawnSiteActive[2] = spawnSiteActive[3] = false;

   srand(timeGetTime());

   for(int py = 0; py < NUMBER_OF_PYRAMIDS; py++){
      pyramid.push_back(new Pyramid());
   }
   pyramid[0]->init(50, 100, 0, 900);
   pyramid[1]->init(50, 100, -200, 900);
   pyramid[2]->init(50, 100, -500, 900);
   pyramid[3]->init(50, 100, -600, 900);
   pyramid[4]->init(80, 120, -800, 900);
   pyramid[5]->init(50, 100, -900, 700);
   pyramid[6]->init(80, 120, -900, 500);
   pyramid[7]->init(80, 120, -900, 200);
   pyramid[8]->init(80, 120, -900, 0);
   pyramid[9]->init(80, 120, -900, -350);
   pyramid[10]->init(80, 120, -900, -500);
   pyramid[11]->init(80, 120, 300, 900);
   pyramid[12]->init(50, 100, 500, 900);
   pyramid[13]->init(80, 120, 900, 900);
   pyramid[14]->init(50, 100, 900, 700);
   pyramid[15]->init(50, 120, 900, 500);
   pyramid[16]->init(80, 120, 800, 100);
   pyramid[17]->init(80, 120, 800, 0);
   pyramid[18]->init(50, 120, 900, -300);
   pyramid[19]->init(80, 120, 900, -500);

   for(int f = 0; f < NUMBER_OF_FRIENDLIES; f++){
      friendly.push_back(new Good());
   }
   friendly[0]->init(-530, 620, textNames[6]);
   friendly[1]->init(160, 710, textNames[6]);
   friendly[2]->init(230, 280, textNames[6]);
   friendly[3]->init(-175, -30, textNames[6]);
   friendly[4]->init(25, -115, textNames[6]);



   for(int e = 0; e < NUMBER_OF_ENEMIES; e++){
      enemy.push_back(new Foe());
   }
   enemy[0]->init(0, -30, textNames[7]);
   enemy[0]->init(-220, -100, textNames[7]);
	enemy[1]->init(-490, 575, textNames[7]);
	enemy[2]->init(-180, -130, textNames[7]);
	enemy[3]->init(-120, -40, textNames[7]);
	enemy[4]->init(-30, -90, textNames[7]);
	enemy[5]->init(25, -200, textNames[7]);
	enemy[6]->init(80, -40, textNames[7]);
	enemy[7]->init(120, -85, textNames[7]);
	enemy[8]->init(170, -30, textNames[7]);
	enemy[9]->init(185, -200, textNames[7]);
	enemy[10]->init(160, 350, textNames[7]);
	enemy[11]->init(200, 380, textNames[7]);
	enemy[12]->init(270, 310, textNames[7]);
	enemy[13]->init(90, 600, textNames[7]);
	enemy[14]->init(130, 700, textNames[7]);
	enemy[15]->init(200, 650, textNames[7]);
	enemy[16]->init(-400, 200, textNames[7]);
	enemy[17]->init(-300, 10, textNames[7]);
	enemy[18]->init(-50, 100, textNames[7]);
	enemy[19]->init(100, 225, textNames[7]);

   for(int h = 0; h < NUMBER_OF_HOUSES; h++){
      house.push_back(new House());
   }
   for(int street1 = 0; street1 < 10; street1++){
      int x1 = street1 * 50;
      house[street1]->init(-250 + x1, 3.75, -15, 12, 10, 7.5, 5,
			                  textNames[1], textNames[5]);
   }
   for(int street2 = 10; street2 < 20; street2++){
      int x2 = (street2 - 10) * 50;
      house[street2]->init(-250 + x2, 3.75, -65, 12, 10, 7.5, 5,
									textNames[1], textNames[5]);
   }
   for(int street3 = 20; street3 < 30; street3++){
      int x3 = (street3 - 20) * 50;
      house[street3]->init(-250 + x3, 3.75, -115, 12, 10, 7.5, 5,
									textNames[1], textNames[5]);
   }
   for(int street4 = 30; street4 < 40; street4++){
      int x4 = (street4 - 30) * 50;
      house[street4]->init(-250 + x4, 3.75, -165, 12, 10, 7.5, 5,
									textNames[1], textNames[5]);
   }
   for(int street5 = 40; street5 < 50; street5++){
      int x5 = (street5 - 40) * 50;
      house[street5]->init(-250 + x5, 3.75, -215, 12, 10, 7.5, 5,
									textNames[1], textNames[5]);
   }
   //BARN
   house[50]->init(200 , 5, 355, 20, 30, 10, 10,
						 textNames[1], textNames[5]); 
   //FARMHOUSES
   house[51]->init(250 , 3.75, 300, 12, 10, 7.5, 5,
						 textNames[1], textNames[5]);
   house[52]->init(260 , 3.75, 320, 12, 10, 7.5, 5,
						 textNames[1], textNames[5]);  
   //SHED
   house[53]->init(180 , 1.5, 360, 5, 4, 3, 2,
						 textNames[1], textNames[5]);  

   //Second Farm

   //BARN
   house[54]->init(-500 , 5, 600, 20, 30, 10, 10,
						 textNames[1], textNames[5]); 
   //FARMHOUSES
   house[55]->init(-520 , 3.75, 650, 12, 10, 7.5, 5,
						 textNames[1], textNames[5]);
   house[56]->init(-480 , 3.75, 650, 12, 10, 7.5, 5,
						 textNames[1], textNames[5]);  
   //SHED
   house[57]->init(-520 , 1.5, 600, 5, 4, 3, 2,
						 textNames[1], textNames[5]);  


   for(int s = 0; s < NUMBER_OF_SILOS; s++){
      silo.push_back(new Silo());
   }   
	silo[0]->init(180.0, 10.0, 375.0, 2.0, 20.0, textNames[0], textNames[5]); 
	silo[1]->init(220.0, 10.0, 380.0, 2.0, 20.0, textNames[0], textNames[5]); 

	//Second Farm

	silo[2]->init(-480.0, 10.0, 600.0, 2.0, 20.0, textNames[0], textNames[5]); 
	silo[3]->init(-480.0, 10.0, 590.0, 2.0, 20.0, textNames[0], textNames[5]); 
	silo[4]->init(-480.0, 10.0, 580.0, 2.0, 20.0, textNames[0], textNames[5]); 

  //888888888888888888888888888888888888888888888888888888888888888
   for(int i = 0; i < NUMBER_OF_PINES; i++){
	  pine.push_back(new Pine());
   }
	  pine[0]->init(-250, 110);
	  pine[1]->init(-200, -8);
	  pine[2]->init(-175, 65);
	  pine[3]->init(-155, 26);
	  pine[4]->init(-134, 10);
	  pine[5]->init(-122, 80);
	  pine[6]->init(-100, -5);
	  pine[7]->init(-85, 80);
	  pine[8]->init(-75, -3);
	  pine[9]->init(-40, 55);
	  pine[10]->init(-20, 20);
	  pine[11]->init(10, 65);
	  pine[12]->init(55, 14);
	  pine[13]->init(75, 0);
	  pine[14]->init(100, 126);
	  pine[15]->init(125, 70);
	  pine[16]->init(150, 130);
	  pine[17]->init(175, -4);
	  pine[18]->init(200, 50);
	  pine[19]->init(250, 65);
	  pine[20]->init(-230, -40);
	  pine[21]->init(-175, -185);
	  pine[22]->init(-130, -80);
	  pine[23]->init(-70, -140);
	  pine[24]->init(-30, -145);
	  pine[25]->init(20, -80);
	  pine[26]->init(75, -180);
	  pine[27]->init(130, -40);
	  pine[28]->init(120, -130);
//FARM TREES
	  pine[29]->init(320, 290);
	  pine[30]->init(325, 325);
	  pine[31]->init(320, 350);
	  pine[32]->init(325, 375);
	  pine[33]->init(320, 400);

	  pine[34]->init(290, 420);
	  pine[35]->init(255, 425);
	  pine[36]->init(230, 420);
	  pine[37]->init(190, 425);
	  pine[38]->init(150, 420);

	  pine[39]->init(135, 390);
	  pine[40]->init(140, 370);
	  pine[41]->init(135, 350);
	  pine[42]->init(140, 320);
	  pine[43]->init(135, 300);
	 
   
   
   for(int j = 0; j < NUMBER_OF_SMALL_PINES; j++){
	  smallPine.push_back(new SmallPine());
   }
	  smallPine[0]->init(-250, 10);
	  smallPine[1]->init(-200, 38);
	  smallPine[2]->init(-165, 55);
	  smallPine[3]->init(-125, 86);
	  smallPine[4]->init(-104, 25);
	  smallPine[5]->init(-82, 65);
	  smallPine[6]->init(-70, -5);
	  smallPine[7]->init(-55, 38);
	  smallPine[8]->init(-35, 15);
	  smallPine[9]->init(-15, 58);
	  smallPine[10]->init(-35, 0);
	  smallPine[11]->init(18, 80);
	  smallPine[12]->init(43, 110);
	  smallPine[13]->init(75, 48);
	  smallPine[14]->init(80, 75);
	  smallPine[15]->init(112, 40);
	  smallPine[16]->init(130, 98);
	  smallPine[17]->init(145, 34);
	  smallPine[18]->init(185, -3);
	  smallPine[19]->init(210, 50);
	  smallPine[20]->init(-225, -145);
	  smallPine[21]->init(-75, -185);
	  smallPine[22]->init(-30, -35);
	  smallPine[23]->init(115, -130);
	  smallPine[24]->init(130, -180);

//TREE GROVE
	  smallPine[25]->init(100, 500);
	  smallPine[26]->init(100, 520);
	  smallPine[27]->init(100, 540);
	  smallPine[28]->init(100, 560);
	  smallPine[29]->init(100, 580);
	  smallPine[30]->init(100, 600);
	  smallPine[31]->init(100, 620);
	  smallPine[32]->init(100, 640);
	  smallPine[33]->init(100, 660);
	  smallPine[34]->init(100, 680);
	  
	  smallPine[35]->init(120, 500);
	  smallPine[36]->init(120, 520);
	  smallPine[37]->init(120, 540);
	  smallPine[38]->init(120, 560);
	  smallPine[39]->init(120, 580);
	  smallPine[40]->init(120, 600);
	  smallPine[41]->init(120, 620);
	  smallPine[42]->init(120, 640);
	  smallPine[43]->init(120, 660);
	  smallPine[44]->init(120, 680);
	  
     smallPine[45]->init(140, 500);
	  smallPine[46]->init(140, 520);
	  smallPine[47]->init(140, 540);
	  smallPine[48]->init(140, 560);
	  smallPine[49]->init(140, 580);
	  smallPine[50]->init(140, 600);
	  smallPine[51]->init(140, 620);
	  smallPine[52]->init(140, 640);
	  smallPine[53]->init(140, 660);
	  smallPine[54]->init(140, 680);

	  smallPine[55]->init(160, 500);
	  smallPine[56]->init(160, 520);
	  smallPine[57]->init(160, 540);
	  smallPine[58]->init(160, 560);
	  smallPine[59]->init(160, 580);
	  smallPine[60]->init(160, 600);
	  smallPine[61]->init(160, 620);
	  smallPine[62]->init(160, 640);
	  smallPine[63]->init(160, 660);
	  smallPine[64]->init(160, 680);

	  smallPine[65]->init(180, 500);
	  smallPine[66]->init(180, 520);
	  smallPine[67]->init(180, 540);
	  smallPine[68]->init(180, 560);
	  smallPine[69]->init(180, 580);
	  smallPine[70]->init(180, 600);
	  smallPine[71]->init(180, 620);
	  smallPine[72]->init(180, 640);
	  smallPine[73]->init(180, 660);
	  smallPine[74]->init(180, 680);



   return TRUE;
}

BEGIN_MESSAGE_MAP(CMyOpenGLView, COpenGLView)
	//{{AFX_MSG_MAP(CMyOpenGLView)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_COLLISION_ON, OnCollisionOn)
	ON_COMMAND(ID_COLLISION_OFF, OnCollisionOff)
	ON_COMMAND(ID_HOST, OnHost)
	ON_COMMAND(ID_JOIN, OnJoin)
	ON_COMMAND(ID_DISCONNECT, OnDisconnect)
	ON_COMMAND(ID_SINGLE, OnSingle)
	ON_COMMAND(ID_MULTI, OnMulti)
	ON_COMMAND(ID_QUIT, OnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView drawing

void CMyOpenGLView::OnDraw(CDC* pDC)
{
   
   static GLfloat light0_pos[] = {100.0, 100.0, 100.0, 0.0};
   static GLfloat light1_pos[] = {95.0, 95.0, 95.0, 1.0};
   static GLfloat light2_pos[] = {0.0, 0.0, 0.0, 1.0};
   static GLfloat spot_direction[] = {0.0, 0.0, -1.0};

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

	   glMatrixMode (GL_MODELVIEW);            // Modelview matrix stack
	   glLoadIdentity();

      // Positon Light 2
      glLightfv(GL_LIGHT2, GL_POSITION, light2_pos);
      glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
      glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);

      // Execute Viewing transformations
	   setViewPoint();

      // Draw the scene objects
      drawScene();

      // Position Light 0
      glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);

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


void CMyOpenGLView::setViewPoint()
{
   if (startGame && !gameOver) {
      GLUquadricObj *sun;
      sun = gluNewQuadric();

	   // Execute Viewing transformations
	   if (viewPointMode == FLY) {
		   computeFlyView();		
	   }
      glRotatef( rotationX, 1, 0, 0 );
	   glRotatef( rotationY, 0, 1, 0 );
      glRotatef(azimuth, 0, 1, 0);
      glPushMatrix();
         glRotatef(-azimuth, 0, 1, 0);
         glTranslatef(-1.0f, -4.25f, -1.5f);
         glRotatef(90.0f, 0, 1, 0);
         ourTank.draw();
      glPopMatrix();

      GLfloat sun_emissive[3] = {1.0, 1.0, 0.0};
      GLfloat no_emissive[3] = {0.0, 0.0, 0.0};
      glColor4f(1.0, 1.0, 0.65f, 0.0);
      glPushMatrix();
         glTranslatef(120, 120, 120);
         glMaterialfv(GL_FRONT, GL_EMISSION, sun_emissive);
         gluSphere(sun, 5, 20, 20);
   //      glutSolidSphere(5, 20, 20);
      glPopMatrix();
      glMaterialfv(GL_FRONT, GL_EMISSION, no_emissive);
      glTranslatef(viewPointX - 1, viewPointY - 5, viewPointZ - 1);
   } else if (!startGame && !gameOver) {
	   gluLookAt(0.0, 0.0, 0.0, 
		          0.0, 0.0, -1.0,
			       0.0, 1.0, 0.0);
   } else if (startGame && gameOver) {
      gluLookAt(350.0, 150.0, -400.0, -75.0, 0.0, 100.0, 0.0, 1.0, 0.0);
   } // end if-else
} // end SetViewPoint


// Draw scene objects
void CMyOpenGLView::drawScene()
{
   //******** Draw Your Objects Here *********
if (startGame) {
   if (multiPlayer) {
      // do network stuff here
      Packet *packet = new Packet;
      packet->packetType = 0;
      packet->x = viewPointX - 1;
      packet->y = viewPointY - 5;
      packet->z = viewPointZ - 1;
      packet->azimuth = azimuth;
      packet->rotationX = rotationX;
      packet->rotationY = rotationY;
      packet->speed = ourTank.getSpeed();
//      packet->isDestroyed = ourTank.isDestroyed();
      packet->mgLatch = mgLatch;
	   int len = sizeof(*packet);
      if (server) {
         if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	      {
		   CheckError(m_receiveSocket.GetLastError());
		   m_receiveSocket.Close();
         multiPlayer = false;
	      }
         delete packet;
      } else {
	      if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	      {
		   CheckError(m_clientSocket.GetLastError());
		   m_clientSocket.Close();
         multiPlayer = false;
	      }
         delete packet;
      } // end if-else
   } // end if
   if (multiPlayer) {
      // Draw opponent
      glPushMatrix();  
         glTranslatef(-opponent.getX(), -opponent.getY(), -opponent.getZ());
         glRotatef(90 - opponent.getAzimuth(), 0, 1, 0);
         glTranslatef(1.5, -4.25, -1.0);
         if (!opponent.isDestroyed() || 
            (opponent.isDestroyed() && opponent.getExplosion()->isGrowing())) {
            opponent.draw();
         } // end if
         if (opponent.isDestroyed()) {
            opponent.getExplosion()->draw();
            if (opponent.getExplosion()->isExplosionDone()) {
               opponent.regen();
            } // end if
         } // end if
	   glPopMatrix();
      // Draw opponent's machine gun
      glPushMatrix();
         glTranslatef(-opponent.getX(), -opponent.getY(), -opponent.getZ());
         glRotatef(-opponent.getAzimuth(), 0, 1, 0);
         glTranslatef(0.0f, -0.55f, -1.5f);
         if (opponent.isMGLatched()) {
            glRotatef(-opponent.getRotationX(), 1, 0, 0);
            glRotatef(-opponent.getRotationY(), 0, 1, 0);
         } // end if
         if (!opponent.isDestroyed() || 
            (opponent.isDestroyed() && opponent.getExplosion()->isGrowing())) {
            oppMG.draw();
         } // end if
      glPopMatrix();

      if (ourTank.isRespawning()) {
         float xDist = abs(spawnSites[spawnSite][0] - ourTank.getX());
         float zDist = abs(spawnSites[spawnSite][1] - ourTank.getZ());
         float dist = sqrt(xDist * xDist + zDist * zDist);
         if (dist > 50) {
            spawnSiteActive[spawnSite] = false;
            ourTank.setRespawnFlag(false);
            Packet *packet = new Packet;
            packet->packetType = 10;
            packet->id = spawnSite;
            packet->spawnSiteActive = false;
            int len = sizeof(*packet);
            if (server) {
               if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	            {
		         CheckError(m_receiveSocket.GetLastError());
		         m_receiveSocket.Close();
               multiPlayer = false;
	            }
               delete packet;
            } else {
	            if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	            {
		         CheckError(m_clientSocket.GetLastError());
		         m_clientSocket.Close();
               multiPlayer = false;
	            }
               delete packet;
            } // end if-else
         } // end if
      } // end if
   } // end if

   //88888888888888888888888888888888888888888888888888888888
   char* explode = "explobig.wav";


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textNames[3]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

   // create a quadric for the explosion
	GLUquadricObj *sobj;
	sobj = gluNewQuadric();
	gluQuadricOrientation(sobj, GLU_INSIDE);
	gluQuadricDrawStyle(sobj, GLU_FILL);
	gluQuadricNormals(sobj, GLU_SMOOTH);
   gluQuadricTexture(sobj, GL_TRUE);

		// draw the explosion and delete the quadric object
//      glPolygonMode(GL_BACK, GL_FILL);
   glColor3f(0.0, 0.65f, 1.0);
	gluSphere(sobj, 1100, 100, 100);
	gluDeleteQuadric(sobj);
//      glPolygonMode(GL_BACK, GL_LINE);

   // Draw ground
	glBindTexture(GL_TEXTURE_2D, textNames[2]);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
   glColor3f(0.0, 0.5, 0.0);
   for (int x = -1000; x < 1000; x += 100) {
      for (int z = -1000; z < 1000; z += 100) {
         glBegin(GL_QUADS);
            glNormal3f(0.0, 1.0, 0.0);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(x, 0.0, z);
            glTexCoord2f(10.0, 0.0);
            glVertex3f(x, 0.0, z + 100);
            glTexCoord2f(10.0, 10.0);
            glVertex3f(x + 100, 0.0, z + 100);
            glTexCoord2f(0.0, 10.0);
            glVertex3f(x + 100, 0.0, z);
         glEnd();
      } // end for
   } // end for

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
    
   // Draw machine gun
   glPushMatrix();
      glTranslatef(-viewPointX + 1, viewPointY + 5, -viewPointZ + 1);
      glRotatef(-azimuth, 0, 1, 0);
      glTranslatef(0, -0.55f, -1.5f);
      if (mgLatch) {
         glRotatef(-rotationX, 1, 0, 0);
         glRotatef(-rotationY, 0, 1, 0);
      } // end if
      mg.draw();
   glPopMatrix();

   // Display tank info on screen
   char buffer[50];
   int i;
   i =  sprintf(buffer, "Speed: ");
   if (ourTank.getSpeed() < 0.05 && ourTank.getSpeed() > -0.05) {
      i += sprintf(buffer + i, "0");
   } else {
      i += sprintf(buffer + i, "%.0f", ourTank.getSpeed() * 10);
   } // end if-else
   if (ourTank.getSpeed() >= -0.05) {
      glColor3f(0.0, 1.0, 0.0);
   } else {
      glColor3f(1.0, 0.0, 0.0);
   } // end if-else
   flatFont.screenTextOutput(10, 10, winSizeX, winSizeY, buffer);
   if (azimuth < 0.5 && azimuth > -0.5) {
      i =  sprintf(buffer, "000");
   } else if (azimuth < 10) {
      i =  sprintf(buffer, "00");
      i += sprintf(buffer + i, "%.0f", azimuth);
   } else if (azimuth < 100) {
      i =  sprintf(buffer, "0");
      i += sprintf(buffer + i, "%.0f", azimuth);
   } else {
      i = sprintf(buffer, "%.0f", azimuth);
   } // end if-else
   glColor3f(1.0, 0.0, 0.0);
   flatFont.screenTextOutput(winSizeX/2.0 - 25, winSizeY - 20, winSizeX, winSizeY, buffer);
   i =  sprintf(buffer, "Shells: ");
   i += sprintf(buffer + i, "%i", ourTank.getShells());
   flatFont.screenTextOutput(winSizeX - 200, 30, winSizeX, winSizeY, buffer);
   if (ElapsedTimeInMSSinceLastShot() > 250 && ElapsedTimeInMSSinceLastShot() < 10000) {
      i = sprintf(buffer, " Reloading");
      flatFont.screenTextOutput(winSizeX - 170, 50, winSizeX, winSizeY, buffer);
   } // end if
   i =  sprintf(buffer, ".50 Rounds: ");
   i += sprintf(buffer + i, "%i", ourTank.getBullets());
   flatFont.screenTextOutput(winSizeX - 200, 10, winSizeX, winSizeY, buffer);
   i =  sprintf(buffer, "Score: ");
   i += sprintf(buffer + i, "%i", score);
   glColor3f(0.0, 0.0, 1.0);
   flatFont.screenTextOutput(10, winSizeY - 20, winSizeX, winSizeY, buffer);
   i =  sprintf(buffer, "Hull: ");
   i += sprintf(buffer + i, "%.0f", ourTank.getDamageCapacity());
   if (ourTank.getDamageCapacity() > 20) {
      glColor3f(0.0, 1.0, 0.0);
   } else if (ourTank.getDamageCapacity() > 10) {
      glColor3f(1.0, 1.0, 0.0);
   } else {
      glColor3f(1.0, 0.0, 0.0);
   } // end if-else
   flatFont.screenTextOutput(winSizeX - 100, winSizeY - 20, winSizeX, winSizeY, buffer);
   glColor3f(0.0, 0.0, 1.0);
   i = sprintf(buffer, "Time Remaining");
   flatFont.screenTextOutput(winSizeX/2.0 - 100, 30, winSizeX, winSizeY, buffer);
   double elapsedTime = timeGetTime() - gameStartTime;
   double timeRemainingInSec = (600000 - elapsedTime) / 1000;
   int timeRemainingMin = (int) (timeRemainingInSec / 60.0);
   int timeRemainingSec = timeRemainingInSec - timeRemainingMin * 60;
   if (!gameOver) {
      i =  sprintf(buffer, "%d:", timeRemainingMin);
      if (timeRemainingSec < 10) {
         i += sprintf(buffer + i, "0%d", timeRemainingSec);
      } else {
         i += sprintf(buffer + i, "%d", timeRemainingSec);
      } // end if
      flatFont.screenTextOutput(winSizeX/2.0 - 35, 10, winSizeX, winSizeY, buffer);
   } // end if
   if (multiPlayer && ourTank.getDamageCapacity() <= 0) {
      i = sprintf(buffer, "You've been fragged!");
      ourTank.stop();
      glColor3f(1.0, 0.0, 0.0);
      flatFont.screenTextOutput(winSizeX/2.0 - 100, winSizeY/2.0, winSizeX, winSizeY, buffer);
      respawn();
   } else if (multiPlayer && timeRemainingInSec <= 0) {
      i = sprintf(buffer, "Game Over");
      ourTank.stop();
      glColor3f(1.0, 0.0, 0.0);
      flatFont.screenTextOutput(winSizeX/2.0 - 50, winSizeY/2.0, winSizeX, winSizeY, buffer);
      gameOver = true;
      if (!playedFinalSound) {
         sndPlaySound("gameover.wav", SND_ASYNC | SND_FILENAME);
         playedFinalSound = true;
      } // end if
   } // end if-else
   if (!multiPlayer && (ourTank.getDamageCapacity() <= 0 || timeRemainingInSec <= 0 ||
      (ourTank.getBullets() == 0 && ourTank.getShells() == 0)  ||
      (enemy.size() == 0))) {
      i = sprintf(buffer, "Game Over");
      ourTank.stop();
      glColor3f(1.0, 0.0, 0.0);
      flatFont.screenTextOutput(winSizeX/2.0 - 50, winSizeY/2.0, winSizeX, winSizeY, buffer);
      gameOver = true;
      if (!playedFinalSound) {
         sndPlaySound("gameover.wav", SND_ASYNC | SND_FILENAME);
         playedFinalSound = true;
      } // end if
} // end if


   for(int p = 0; p < pyramid.size(); p++){
      glPushMatrix();  
      glTranslatef(pyramid[p]->getX(), 0.0, pyramid[p]->getZ());
      pyramid[p]->draw();
	  glPopMatrix();
   }

   for(int t = 0; t < friendly.size(); t++){
      glPushMatrix();  
      glTranslatef(friendly[t]->getX(), 0.9f, friendly[t]->getZ());
         if (!friendly[t]->isDestroyed()) {
            friendly[t]->draw();
         } else if (friendly[t]->isDestroyed() && friendly[t]->getExplosion()->isGrowing()) {
            friendly[t]->draw();
         } // end if-else
         if (friendly[t]->isDestroyed()) {
            friendly[t]->getExplosion()->draw();
            if (friendly[t]->getExplosion()->isExplosionDone()) {
               delete friendly[t];
               friendly.erase(&friendly[t]);
            } // end if
         } // end if
	  glPopMatrix();
   }

   // Draw enemy tanks
   for (i = 0; i < enemy.size(); i++) {
      glPushMatrix();
         glTranslatef(enemy[i]->getX(), 0.5, enemy[i]->getZ());
         if (!enemy[i]->isDestroyed()) {
            enemy[i]->draw();
         } else if (enemy[i]->isDestroyed() && enemy[i]->getExplosion()->isGrowing()) {
            enemy[i]->draw();
         } // end if-else
         if (enemy[i]->isDestroyed()) {
            enemy[i]->getExplosion()->draw();
            if (enemy[i]->getExplosion()->isExplosionDone()) {
               delete enemy[i];
               enemy.erase(&enemy[i]);
            } // end if
         } // end if
      glPopMatrix();
   } // end for

   // Draw houses
   for (i = 0; i < house.size(); i++) {
      if (!house[i]->isDestroyed()) {
         house[i]->draw();
      } else if (house[i]->isDestroyed() && house[i]->getExplosion()->isGrowing()) {
         house[i]->draw();
      } // end if-else
      if (house[i]->isDestroyed()) {
         glPushMatrix();
            glTranslatef(house[i]->getX(), 0, house[i]->getZ());
            house[i]->getExplosion()->draw();
         glPopMatrix();
         if (house[i]->getExplosion()->isExplosionDone()) {
            delete house[i];
            house.erase(&house[i]);
         } // end if
      } // end if
   } // end for

   // Draw pine trees
   for(int a = 0; a < pine.size(); a++){
      glPushMatrix();  
         glTranslatef(pine[a]->getX(), 0, pine[a]->getZ());
         if (!pine[a]->isDestroyed()) {
            pine[a]->draw();
         } else if (pine[a]->isDestroyed() && pine[a]->getExplosion()->isGrowing()) {
            pine[a]->draw();
         } // end if-else
         if (pine[a]->isDestroyed()) {
            pine[a]->getExplosion()->draw();
            if (pine[a]->getExplosion()->isExplosionDone()) {
               delete pine[a];
               pine.erase(&pine[a]);
            } // end if
         } // end if
	   glPopMatrix();
   } // end for

   // Draw small pine trees   
   for(int b = 0; b < smallPine.size(); b++){
      glPushMatrix();  
         glTranslatef(smallPine[b]->getX(), 0, smallPine[b]->getZ());
         if (!smallPine[b]->isDestroyed()) {
            smallPine[b]->draw();
         } else if (smallPine[b]->isDestroyed() && 
                    smallPine[b]->getExplosion()->isGrowing()) {
            smallPine[b]->draw();
         } // end if-else
         if (smallPine[b]->isDestroyed()) {
            smallPine[b]->getExplosion()->draw();
            if (smallPine[b]->getExplosion()->isExplosionDone()) {
               delete smallPine[b];
               smallPine.erase(&smallPine[b]);
            } // end if
         } // end if
      glPopMatrix();
   } // end for

   // Draw silos
   for(int sh = 0; sh < silo.size(); sh++){
      glPushMatrix();  
         glTranslatef(silo[sh]->getX(), 0, silo[sh]->getZ());
         if (!silo[sh]->isDestroyed()) {
            silo[sh]->draw();
         } else if (silo[sh]->isDestroyed() && silo[sh]->getExplosion()->isGrowing()) {
            silo[sh]->draw();
         } // end if-else
         if (silo[sh]->isDestroyed()) {
            silo[sh]->getExplosion()->draw();
            if (silo[sh]->getExplosion()->isExplosionDone()) {
               delete silo[sh];
               silo.erase(&silo[sh]);
            } // end if
         } // end if
	   glPopMatrix();
   } // end for

   // Draw the shells from the main gun
   for (i = 0; i < shells.size(); i++) {
      shellCollision = false;
      glPushMatrix();
         glTranslatef(shells[i]->getX(), shells[i]->getY(), shells[i]->getZ());
         glRotatef(-(shells[i]->getAzimuth()), 0, 1, 0);
         glTranslatef(-1, -1.75, -7.5 - shells[i]->getRange());
         shells[i]->draw();
      glPopMatrix();
      // Check for shell collisions with the opponent
      if (multiPlayer && !shellCollision) {
         xDist = abs(shells[i]->getRealX() + opponent.getX());
         zDist = abs(shells[i]->getRealZ() + opponent.getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         if (dist < opponent.getRadius()) {
            shellCollision = true;
            if (opponent.getDamageCapacity() > 0) {
               opponent.takeDamage(shells[i]->getDamage());
            } // end if
            if (multiPlayer && opponent.getDamageCapacity() > 0) {
               Packet *packet = new Packet;
               packet->packetType = 3;
               packet->damage = shells[i]->getDamage();
               int len = sizeof(*packet);
               if (server) {
                  if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	               {
		            CheckError(m_receiveSocket.GetLastError());
		            m_receiveSocket.Close();
                  multiPlayer = false;
	               }
                  delete packet;
               } else {
	               if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	               {
		            CheckError(m_clientSocket.GetLastError());
		            m_clientSocket.Close();
                  multiPlayer = false;
	               }
                  delete packet;
               } // end if-else
            } // end if
            if (opponent.isDestroyed() && opponent.getExplosion() == 0) {
               score += opponent.getPointValue();
               opponent.startExplosion();
               sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
            } // end if
            delete shells[i];
            shells.erase(&shells[i]);
         } // end if
      } // end if

      if (!shellCollision) {
         int j = 0;
         do {
            xDist = abs(shells[i]->getRealX() - enemy[j]->getX());
            zDist = abs(shells[i]->getRealZ() - enemy[j]->getZ());
            dist = sqrt(xDist * xDist + zDist * zDist);
            if (dist < enemy[j]->getRadius()) {
               shellCollision = true;
               enemy[j]->takeDamage(shells[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 5;
                  packet->id = j;
                  packet->damage = shells[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete shells[i];
               shells.erase(&shells[i]);
               if (enemy[j]->isDestroyed() && enemy[j]->getExplosion() == 0) {
                  score += enemy[j]->getPointValue();
                  enemy[j]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
         } while (!shellCollision && j < enemy.size());
      } // end if
      // Check for shell collisions with houses
      if (!shellCollision) {
         int j = 0;
         do {
            xDist = abs(shells[i]->getRealX() - house[j]->getX());
            zDist = abs(shells[i]->getRealZ() - house[j]->getZ());
            dist = sqrt(xDist * xDist + zDist * zDist);
            if (dist < house[j]->getRadius()) {
               shellCollision = true;
               house[j]->takeDamage(shells[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 6;
                  packet->id = j;
                  packet->damage = shells[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete shells[i];
               shells.erase(&shells[i]);
               if (house[j]->isDestroyed() && house[j]->getExplosion() == 0) {
                     score += house[j]->getPointValue();
                     house[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
         } while (!shellCollision && j < house.size());
      } // end if
      // Check for shell collisions with pine trees
      if (!shellCollision) {
         int j = 0;
         do {
            xDist = abs(shells[i]->getRealX() - pine[j]->getX());
            zDist = abs(shells[i]->getRealZ() - pine[j]->getZ());
            dist = sqrt(xDist * xDist + zDist * zDist);
            if (dist < pine[j]->getRadius()) {
               shellCollision = true;
               pine[j]->takeDamage(shells[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 7;
                  packet->id = j;
                  packet->damage = shells[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete shells[i];
               shells.erase(&shells[i]);
               if (pine[j]->isDestroyed() && pine[j]->getExplosion() == 0) {
                  score += pine[j]->getPointValue();
                  pine[j]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
         } while (!shellCollision && j < pine.size());
      } // end if
      // Check for shell collisions with small pine trees
      if (!shellCollision) {
         int j = 0;
         do {
            xDist = abs(shells[i]->getRealX() - smallPine[j]->getX());
            zDist = abs(shells[i]->getRealZ() - smallPine[j]->getZ());
            dist = sqrt(xDist * xDist + zDist * zDist);
            if (dist < smallPine[j]->getRadius()) {
               shellCollision = true;
               smallPine[j]->takeDamage(shells[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 8;
                  packet->id = j;
                  packet->damage = shells[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete shells[i];
               shells.erase(&shells[i]);
               if (smallPine[j]->isDestroyed() && smallPine[j]->getExplosion() == 0) {
                  score += smallPine[j]->getPointValue();
                  smallPine[j]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
         } while (!shellCollision && j < smallPine.size());
      } // end if
      // Check for shell collisions with silos
      if (!shellCollision) {
         int j = 0;
         do {
            xDist = abs(shells[i]->getRealX() - silo[j]->getX());
            zDist = abs(shells[i]->getRealZ() - silo[j]->getZ());
            dist = sqrt(xDist * xDist + zDist * zDist);
            if (dist < silo[j]->getRadius()) {
               shellCollision = true;
               silo[j]->takeDamage(shells[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 9;
                  packet->id = j;
                  packet->damage = shells[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete shells[i];
               shells.erase(&shells[i]);
               if (silo[j]->isDestroyed() && silo[j]->getExplosion() == 0) {
                  score += silo[j]->getPointValue();
                  silo[j]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
         } while (!shellCollision && j < silo.size());
      } // end if
      // Check for shell collisions with friendly tanks
      if (!shellCollision) {
         int j = 0;
         do {
            xDist = abs(shells[i]->getRealX() - friendly[j]->getX());
            zDist = abs(shells[i]->getRealZ() - friendly[j]->getZ());
            dist = sqrt(xDist * xDist + zDist * zDist);
            if (dist < friendly[j]->getRadius()) {
               shellCollision = true;
               friendly[j]->takeDamage(shells[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 4;
                  packet->id = j;
                  packet->damage = shells[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete shells[i];
               shells.erase(&shells[i]);
               if (friendly[j]->isDestroyed() && friendly[j]->getExplosion() == 0) {
                  score += friendly[j]->getPointValue();
                  friendly[j]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
         } while (!shellCollision && j < friendly.size());
      } // end if 
   } // end for

   if (multiPlayer) {
      // Draw the shells from the opponent's main gun
      for (i = 0; i < oppShells.size(); i++) {
         shellCollision = false;
         glPushMatrix();
            glTranslatef(oppShells[i]->getX(), oppShells[i]->getY(), oppShells[i]->getZ());
            glRotatef(-oppShells[i]->getAzimuth(), 0, 1, 0);
            glTranslatef(-1.0f, -1.75f, -7.5f - oppShells[i]->getRange());
            oppShells[i]->draw();
         glPopMatrix();
      // Check for shell collisions with us
/*      if (!shellCollision) {
         xDist = abs(-oppShells[i]->getRealX() - ourTank.getX());
         zDist = abs(-oppShells[i]->getRealZ() - ourTank.getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         if (dist < ourTank.getRadius()) {
            shellCollision = true;
            ourTank.takeDamage(oppShells[i]->getDamage());
            delete oppShells[i];
            oppShells.erase(&oppShells[i]);
            if (ourTank.isDestroyed() && ourTank.getExplosion() == 0) {
               ourTank.startExplosion();
               sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
            } // end if
         } // end if
      } // end if
         // Check for shell collisions with enemy tanks
   /*      if (!shellCollision) {
            int j = 0;
            do {
               xDist = abs(oppShells[i]->getRealX() - enemy[j]->getX());
               zDist = abs(oppShells[i]->getRealZ() - enemy[j]->getZ());
               dist = sqrt(xDist * xDist + zDist * zDist);
               if (dist < enemy[j]->getRadius()) {
                  shellCollision = true;
                  enemy[j]->takeDamage(oppShells[i]->getDamage());
                  delete oppShells[i];
                  oppShells.erase(&oppShells[i]);
                  if (enemy[j]->isDestroyed() && enemy[j]->getExplosion() == 0) {
                     enemy[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
            } while (!shellCollision && j < enemy.size());
         } // end if
         // Check for shell collisions with houses
         if (!shellCollision) {
            int j = 0;
            do {
               xDist = abs(oppShells[i]->getRealX() - house[j]->getX());
               zDist = abs(oppShells[i]->getRealZ() - house[j]->getZ());
               dist = sqrt(xDist * xDist + zDist * zDist);
               if (dist < house[j]->getRadius()) {
                  shellCollision = true;
                  house[j]->takeDamage(oppShells[i]->getDamage());
                  delete oppShells[i];
                  oppShells.erase(&oppShells[i]);
                  if (house[j]->isDestroyed() && house[j]->getExplosion() == 0) {
                        house[j]->startExplosion();
                        sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
            } while (!shellCollision && j < house.size());
         } // end if
         // Check for shell collisions with pine trees
         if (!shellCollision) {
            int j = 0;
            do {
               xDist = abs(oppShells[i]->getRealX() - pine[j]->getX());
               zDist = abs(oppShells[i]->getRealZ() - pine[j]->getZ());
               dist = sqrt(xDist * xDist + zDist * zDist);
               if (dist < pine[j]->getRadius()) {
                  shellCollision = true;
                  pine[j]->takeDamage(oppShells[i]->getDamage());
                  delete oppShells[i];
                  oppShells.erase(&oppShells[i]);
                  if (pine[j]->isDestroyed() && pine[j]->getExplosion() == 0) {
                     pine[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
            } while (!shellCollision && j < pine.size());
         } // end if
         // Check for shell collisions with small pine trees
         if (!shellCollision) {
            int j = 0;
            do {
               xDist = abs(oppShells[i]->getRealX() - smallPine[j]->getX());
               zDist = abs(oppShells[i]->getRealZ() - smallPine[j]->getZ());
               dist = sqrt(xDist * xDist + zDist * zDist);
               if (dist < smallPine[j]->getRadius()) {
                  shellCollision = true;
                  smallPine[j]->takeDamage(oppShells[i]->getDamage());
                  delete oppShells[i];
                  oppShells.erase(&oppShells[i]);
                  if (smallPine[j]->isDestroyed() && smallPine[j]->getExplosion() == 0) {
                     smallPine[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
            } while (!shellCollision && j < smallPine.size());
         } // end if
         // Check for shell collisions with silos
         if (!shellCollision) {
            int j = 0;
            do {
               xDist = abs(oppShells[i]->getRealX() - silo[j]->getX());
               zDist = abs(oppShells[i]->getRealZ() - silo[j]->getZ());
               dist = sqrt(xDist * xDist + zDist * zDist);
               if (dist < silo[j]->getRadius()) {
                  shellCollision = true;
                  silo[j]->takeDamage(oppShells[i]->getDamage());
                  delete oppShells[i];
                  oppShells.erase(&shells[i]);
                  if (silo[j]->isDestroyed() && silo[j]->getExplosion() == 0) {
                     silo[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
            } while (!shellCollision && j < silo.size());
         } // end if
         // Check for shell collisions with friendly tanks
         if (!shellCollision) {
            int j = 0;
            do {
               xDist = abs(oppShells[i]->getRealX() - friendly[j]->getX());
               zDist = abs(oppShells[i]->getRealZ() - friendly[j]->getZ());
               dist = sqrt(xDist * xDist + zDist * zDist);
               if (dist < friendly[j]->getRadius()) {
                  shellCollision = true;
                  friendly[j]->takeDamage(oppShells[i]->getDamage());
                  delete oppShells[i];
                  oppShells.erase(&oppShells[i]);
                  if (friendly[j]->isDestroyed() && friendly[j]->getExplosion() == 0) {
                     friendly[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
            } while (!shellCollision && j < friendly.size());
         } // end if */
      } // end for
   } // end if

   // Draw the bullets from the .50 machine gun
   for (i = 0; i < bullets.size(); i++) {
      bulletCollision = false;
      glPushMatrix();
         glTranslatef(bullets[i]->getX(), bullets[i]->getY(), bullets[i]->getZ());
         glRotatef(-(bullets[i]->getAzimuth()), 0, 1, 0);
         glTranslatef(0, -0.55f, -1.5f);
         glRotatef(bullets[i]->getElevation(), 1, 0, 0);
         glRotatef(-bullets[i]->getRotation(), 0, 1, 0);
         glTranslatef(0, 0, -2 - bullets[i]->getRange());
         bullets[i]->draw();
      glPopMatrix();
      // Check for bullet collisions with the opponent
      if (multiPlayer && !bulletCollision) {
         xDist = abs(bullets[i]->getRealX() + opponent.getX());
         yDist = abs(bullets[i]->getRealY() - 0.75f);
         zDist = abs(bullets[i]->getRealZ() + opponent.getZ());
         dist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
         if (dist < opponent.getRadius()) {
            bulletCollision = true;
            if (opponent.getDamageCapacity() > 0) {
               opponent.takeDamage(bullets[i]->getDamage());
            } // end if
            if (multiPlayer && opponent.getDamageCapacity() > 0) {
               Packet *packet = new Packet;
               packet->packetType = 3;
               packet->damage = bullets[i]->getDamage();
               int len = sizeof(*packet);
               if (server) {
                  if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	               {
		            CheckError(m_receiveSocket.GetLastError());
		            m_receiveSocket.Close();
                  multiPlayer = false;
	               }
                  delete packet;
               } else {
	               if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	               {
		            CheckError(m_clientSocket.GetLastError());
		            m_clientSocket.Close();
                  multiPlayer = false;
	               }
                  delete packet;
               } // end if-else
            } // end if
            delete bullets[i];
            bullets.erase(&bullets[i]);
            if (opponent.isDestroyed() && opponent.getExplosion() == 0) {
               score += opponent.getPointValue();
               opponent.startExplosion();
               sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
            } // end if
         } // end if
      } // end if
      // Check for bullet collisions with enemy tanks
      int j = 0;
      do {
            xDist = abs(bullets[i]->getRealX() - enemy[j]->getX());
            yDist = abs(bullets[i]->getRealY() - enemy[j]->getY());
            zDist = abs(bullets[i]->getRealZ() - enemy[j]->getZ());
            dist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
            if (dist < enemy[j]->getRadius()) {
               bulletCollision = true;
               enemy[j]->takeDamage(bullets[i]->getDamage());
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 4;
                  packet->id = j;
                  packet->damage = bullets[i]->getDamage();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               delete bullets[i];
               bullets.erase(&bullets[i]);
               if (enemy[j]->isDestroyed() && enemy[j]->getExplosion() == 0) {
                  score += enemy[j]->getPointValue();
                  enemy[j]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
            } // end if
            j++;
      } while (!bulletCollision && j < enemy.size());
      // Check for bullet collisions with friendly tanks
      if (!bulletCollision) {
         int j = 0;
         do {
               xDist = abs(bullets[i]->getRealX() - friendly[j]->getX());
               yDist = abs(bullets[i]->getRealY() - friendly[j]->getY());
               zDist = abs(bullets[i]->getRealZ() - friendly[j]->getZ());
               dist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
               if (dist < friendly[j]->getRadius()) {
                  bulletCollision = true;
                  friendly[j]->takeDamage(bullets[i]->getDamage());
                  if (multiPlayer) {
                     Packet *packet = new Packet;
                     packet->packetType = 5;
                     packet->id = j;
                     packet->damage = bullets[i]->getDamage();
                     int len = sizeof(*packet);
                     if (server) {
                        if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                     {
		                  CheckError(m_receiveSocket.GetLastError());
		                  m_receiveSocket.Close();
                        multiPlayer = false;
	                     }
                        delete packet;
                     } else {
	                     if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                     {
		                  CheckError(m_clientSocket.GetLastError());
		                  m_clientSocket.Close();
                        multiPlayer = false;
	                     }
                        delete packet;
                     } // end if-else
                  } // end if
                  delete bullets[i];
                  bullets.erase(&bullets[i]);
                  if (friendly[j]->isDestroyed() && friendly[j]->getExplosion() == 0) {
                     score += friendly[j]->getPointValue();
                     friendly[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
         } while (!bulletCollision && j < friendly.size());
      } // end if 
   } // end for

   // Draw the bullets from the opponent's .50 machine gun
   if (multiPlayer) {
      for (i = 0; i < oppBullets.size(); i++) {
         bulletCollision = false;
         glPushMatrix();
            glTranslatef(oppBullets[i]->getX(), oppBullets[i]->getY(), oppBullets[i]->getZ());
            glRotatef(-(oppBullets[i]->getAzimuth()), 0, 1, 0);
            glTranslatef(0, -0.55f, -1.5f);
            glRotatef(oppBullets[i]->getElevation(), 1, 0, 0);
            glRotatef(-oppBullets[i]->getRotation(), 0, 1, 0);
            glTranslatef(0, 0, -2 - oppBullets[i]->getRange());
            oppBullets[i]->draw();
         glPopMatrix();
      // Check for bullet collisions with us
/*      if (!bulletCollision) {
         xDist = abs(oppBullets[i]->getRealX() - ourTank.getX());
         yDist = abs(oppBullets[i]->getRealY() - 0.75f);
         zDist = abs(-oppBullets[i]->getRealZ() + ourTank.getZ());
         dist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
         i = sprintf(buffer, "xDist: %.1f\tyDist: %.1f\tzDist: %.1f\r\n", xDist, yDist, zDist);
         console::output(buffer);
         if (dist < ourTank.getRadius()) {
            bulletCollision = true;
            ourTank.takeDamage(oppBullets[i]->getDamage());
            delete oppBullets[i];
            oppBullets.erase(&oppBullets[i]);
            if (ourTank.isDestroyed() && ourTank.getExplosion() == 0) {
               ourTank.startExplosion();
               sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
            } // end if
         } // end if
      } // end if
         // Check for bullet collisions with enemy tanks
   /*      int j = 0;
         do {
               xDist = abs(oppBullets[i]->getRealX() - enemy[j]->getX());
               yDist = abs(oppBullets[i]->getRealY() - enemy[j]->getY());
               zDist = abs(oppBullets[i]->getRealZ() - enemy[j]->getZ());
               dist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
               if (dist < enemy[j]->getRadius()) {
                  bulletCollision = true;
                  enemy[j]->takeDamage(oppBullets[i]->getDamage());
                  delete oppBullets[i];
                  oppBullets.erase(&oppBullets[i]);
                  if (enemy[j]->isDestroyed() && enemy[j]->getExplosion() == 0) {
                     enemy[j]->startExplosion();
                     sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                  } // end if
               } // end if
               j++;
         } while (!bulletCollision && j < enemy.size());
         // Check for bullet collisions with friendly tanks
         if (!bulletCollision) {
            int j = 0;
            do {
                  xDist = abs(oppBullets[i]->getRealX() - friendly[j]->getX());
                  yDist = abs(oppBullets[i]->getRealY() - friendly[j]->getY());
                  zDist = abs(oppBullets[i]->getRealZ() - friendly[j]->getZ());
                  dist = sqrt(xDist * xDist + yDist * yDist + zDist * zDist);
                  if (dist < friendly[j]->getRadius()) {
                     bulletCollision = true;
                     friendly[j]->takeDamage(oppBullets[i]->getDamage());
                     delete oppBullets[i];
                     oppBullets.erase(&oppBullets[i]);
                     if (friendly[j]->isDestroyed() && friendly[j]->getExplosion() == 0) {
                        friendly[j]->startExplosion();
                        sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
                     } // end if
                  } // end if
                  j++;
            } while (!bulletCollision && j < friendly.size());
         } // end if */
      } // end for
   } // end if

   // Only do movement collision detection if it is enabled and the tank is moving
   if (collisionDetection && !gameOver && 
       (ourTank.getSpeed() > 0.05 || ourTank.getSpeed() < -0.05)) {
      if (multiPlayer) {
      // Check for collisions with the opponent
         xDist = abs(-viewPointX + opponent.getX());
         zDist = abs(-viewPointZ + opponent.getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + opponent.getRadius();
         float relBrg = calculateRelativeBearing(-opponent.getX(), -opponent.getZ());
         float relHdg = opponent.getAzimuth() - azimuth;
         if (relHdg < 0) {
            relHdg += 360;
         } // end if
         if (dist <= minDist) {
            if (opponent.isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (opponent.isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!opponent.isForwardCollided() && !opponent.isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeRammingDamage(opponent.getAzimuth(), opponent.getSpeed());
//               ourTank.takeCollisionDamage(opponent.getPointValue());
//               opponent.takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (opponent.isDestroyed() && opponent.getExplosion() == 0) {
                  score += opponent.getPointValue();
                  opponent.startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               if (relBrg < 30 || relBrg > 330) {
                  if (relHdg > 45 && relHdg < 315) {
                     ourTank.stop();
                     opponent.forwardCollide();
                  } else if (relHdg <= 45 || relHdg >= 315) {
                     if (ourTank.getSpeed() > opponent.getSpeed()) {
                        ourTank.setSpeed(opponent.getSpeed());
                        opponent.forwardCollide();
                     } // end if
                  } // end if-else
               } // end if
            } else if (opponent.isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (opponent.isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!opponent.isBackwardCollided() && !opponent.isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               ourTank.takeRammingDamage(opponent.getAzimuth(), opponent.getSpeed());
//               ourTank.takeCollisionDamage(opponent.getPointValue());
//               opponent.takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (opponent.isDestroyed() && opponent.getExplosion() == 0) {
                  score += opponent.getPointValue();
                  opponent.startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               if (relBrg > 150 && relBrg < 210) {
                  if (relHdg > 45 && relHdg < 315) {
                     ourTank.stop();
                     opponent.backwardCollide();
                  } else if (relHdg <= 45 || relHdg >= 315) {
                     if (ourTank.getSpeed() > opponent.getSpeed()) {
                        ourTank.setSpeed(opponent.getSpeed());
                        opponent.backwardCollide();
                     } // end if
                  } // end if-else
               } // end if
            } // end if-else
         } else {
            if (opponent.isForwardCollided()) {
               opponent.unForwardCollide();
            } // end if
            if (opponent.isBackwardCollided()) {
               opponent.unBackwardCollide();
            } // end if
         } // end if-else
      } // end if
      // Check for collisions with enemy tanks
      for (i = 0; i < enemy.size(); i++) {
         xDist = abs(-viewPointX - enemy[i]->getX());
         zDist = abs(-viewPointZ - enemy[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + enemy[i]->getRadius();
         if (dist <= minDist) {
            if (enemy[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (enemy[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!enemy[i]->isForwardCollided() && !enemy[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeCollisionDamage(enemy[i]->getPointValue());
               enemy[i]->takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 5;
                  packet->id = i;
                  packet->damage = ourTank.getSpeed()/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (enemy[i]->isDestroyed() && enemy[i]->getExplosion() == 0) {
                  score += enemy[i]->getPointValue();
                  enemy[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               enemy[i]->forwardCollide();
            } else if (enemy[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (enemy[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!enemy[i]->isBackwardCollided() && !enemy[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               float damage = ourTank.takeCollisionDamage(enemy[i]->getPointValue());
               enemy[i]->takeDamage(abs(ourTank.getSpeed())/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 5;
                  packet->id = i;
                  packet->damage = abs(ourTank.getSpeed())/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (enemy[i]->isDestroyed() && enemy[i]->getExplosion() == 0) {
                  score += enemy[i]->getPointValue();
                  enemy[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               enemy[i]->backwardCollide();
            } // end if-else
         } else {
            if (enemy[i]->isForwardCollided()) {
               enemy[i]->unForwardCollide();
            } // end if
            if (enemy[i]->isBackwardCollided()) {
               enemy[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
      // Check for collisions with houses
      for (i = 0; i < house.size(); i++) {
         xDist = abs(-viewPointX - house[i]->getX());
         zDist = abs(-viewPointZ - house[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + house[i]->getRadius();
         if (dist <= minDist) {
            if (house[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (house[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!house[i]->isForwardCollided() && !house[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeCollisionDamage(house[i]->getPointValue());
               house[i]->takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 6;
                  packet->id = i;
                  packet->damage = ourTank.getSpeed()/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (house[i]->isDestroyed() && house[i]->getExplosion() == 0) {
                  score += house[i]->getPointValue();
                  house[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               house[i]->forwardCollide();
            } else if (house[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (house[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!house[i]->isBackwardCollided() && !house[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               float damage = ourTank.takeCollisionDamage(house[i]->getPointValue());
               house[i]->takeDamage(abs(ourTank.getSpeed())/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 5;
                  packet->id = i;
                  packet->damage = abs(ourTank.getSpeed())/2.0 * 20;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (house[i]->isDestroyed() && house[i]->getExplosion() == 0) {
                  score += house[i]->getPointValue();
                  house[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               house[i]->backwardCollide();
            } // end if-else
         } else {
            if (house[i]->isForwardCollided()) {
               house[i]->unForwardCollide();
            } // end if
            if (house[i]->isBackwardCollided()) {
               house[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
      // Check for collisions with pine trees
      for (i = 0; i < pine.size(); i++) {
         xDist = abs(-viewPointX - pine[i]->getX());
         zDist = abs(-viewPointZ - pine[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + pine[i]->getRadius();
         if (dist <= minDist) {
            if (pine[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (pine[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!pine[i]->isForwardCollided() && !pine[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeCollisionDamage(pine[i]->getPointValue());
               pine[i]->takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 7;
                  packet->id = i;
                  packet->damage = ourTank.getSpeed()/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (pine[i]->isDestroyed() && pine[i]->getExplosion() == 0) {
                  score += pine[i]->getPointValue();
                  pine[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               pine[i]->forwardCollide();
            } else if (pine[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (pine[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!pine[i]->isBackwardCollided() && !pine[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               float damage = ourTank.takeCollisionDamage(pine[i]->getPointValue());
               pine[i]->takeDamage(abs(ourTank.getSpeed())/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 5;
                  packet->id = i;
                  packet->damage = abs(ourTank.getSpeed())/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (pine[i]->isDestroyed() && pine[i]->getExplosion() == 0) {
                  score += pine[i]->getPointValue();
                  pine[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               pine[i]->backwardCollide();
            } // end if-else
         } else {
            if (pine[i]->isForwardCollided()) {
               pine[i]->unForwardCollide();
            } // end if
            if (pine[i]->isBackwardCollided()) {
               pine[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
      // Check for collisions with small pine trees
      for (i = 0; i < smallPine.size(); i++) {
         xDist = abs(-viewPointX - smallPine[i]->getX());
         zDist = abs(-viewPointZ - smallPine[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + smallPine[i]->getRadius();
         if (dist <= minDist) {
            if (smallPine[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (smallPine[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!smallPine[i]->isForwardCollided() && !smallPine[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeCollisionDamage(smallPine[i]->getPointValue());
               smallPine[i]->takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 8;
                  packet->id = i;
                  packet->damage = ourTank.getSpeed()/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (smallPine[i]->isDestroyed() && smallPine[i]->getExplosion() == 0) {
                  score += smallPine[i]->getPointValue();
                  smallPine[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               smallPine[i]->forwardCollide();
            } else if (smallPine[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (smallPine[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!smallPine[i]->isBackwardCollided() && !smallPine[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               float damage = ourTank.takeCollisionDamage(smallPine[i]->getPointValue());
               smallPine[i]->takeDamage(abs(ourTank.getSpeed())/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 8;
                  packet->id = i;
                  packet->damage = abs(ourTank.getSpeed())/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (smallPine[i]->isDestroyed() && smallPine[i]->getExplosion() == 0) {
                  score += smallPine[i]->getPointValue();
                  smallPine[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               smallPine[i]->backwardCollide();
            } // end if-else
         } else {
            if (smallPine[i]->isForwardCollided()) {
               smallPine[i]->unForwardCollide();
            } // end if
            if (smallPine[i]->isBackwardCollided()) {
               smallPine[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
      // Check for collisions with silos
      for (i = 0; i < silo.size(); i++) {
         xDist = abs(-viewPointX - silo[i]->getX());
         zDist = abs(-viewPointZ - silo[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + silo[i]->getRadius();
         if (dist <= minDist) {
            if (silo[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (silo[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!silo[i]->isForwardCollided() && !silo[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeCollisionDamage(silo[i]->getPointValue());
               silo[i]->takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 9;
                  packet->id = i;
                  packet->damage = ourTank.getSpeed()/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (silo[i]->isDestroyed() && silo[i]->getExplosion() == 0) {
                  score += silo[i]->getPointValue();
                  silo[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               silo[i]->forwardCollide();
            } else if (silo[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (silo[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!silo[i]->isBackwardCollided() && !silo[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               float damage = ourTank.takeCollisionDamage(silo[i]->getPointValue());
               silo[i]->takeDamage(abs(ourTank.getSpeed())/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 9;
                  packet->id = i;
                  packet->damage = abs(ourTank.getSpeed())/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (silo[i]->isDestroyed() && silo[i]->getExplosion() == 0) {
                  score += silo[i]->getPointValue();
                  silo[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               silo[i]->backwardCollide();
            } // end if-else
         } else {
            if (silo[i]->isForwardCollided()) {
               silo[i]->unForwardCollide();
            } // end if
            if (silo[i]->isBackwardCollided()) {
               silo[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
      // Check for collisions with friendly tanks
      for (i = 0; i < friendly.size(); i++) {
         xDist = abs(-viewPointX - friendly[i]->getX());
         zDist = abs(-viewPointZ - friendly[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + friendly[i]->getRadius();
         if (dist <= minDist) {
            if (friendly[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (friendly[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!friendly[i]->isForwardCollided() && !friendly[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               float damage = ourTank.takeCollisionDamage(friendly[i]->getPointValue());
               friendly[i]->takeDamage(ourTank.getSpeed()/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 4;
                  packet->id = i;
                  packet->damage = ourTank.getSpeed()/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (friendly[i]->isDestroyed() && friendly[i]->getExplosion() == 0) {
                  score += friendly[i]->getPointValue();
                  friendly[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               friendly[i]->forwardCollide();
            } else if (friendly[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (friendly[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!friendly[i]->isBackwardCollided() && !friendly[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               float damage = ourTank.takeCollisionDamage(friendly[i]->getPointValue());
               friendly[i]->takeDamage(abs(ourTank.getSpeed())/2.0 * 20.0);
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 11;
                  packet->damage = damage;
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
                  packet = new Packet;
                  packet->packetType = 4;
                  packet->id = i;
                  packet->damage = abs(ourTank.getSpeed())/2.0 * 20.0;
                  len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
               if (friendly[i]->isDestroyed() && friendly[i]->getExplosion() == 0) {
                  score += friendly[i]->getPointValue();
                  friendly[i]->startExplosion();
                  sndPlaySound(explode, SND_ASYNC | SND_FILENAME );
               } // end if
               ourTank.stop();
               friendly[i]->backwardCollide();
            } // end if-else
         } else {
            if (friendly[i]->isForwardCollided()) {
               friendly[i]->unForwardCollide();
            } // end if
            if (friendly[i]->isBackwardCollided()) {
               friendly[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
      // Check for collisions with mountains
      for (i = 0; i < pyramid.size(); i++) {
         xDist = abs(-viewPointX - pyramid[i]->getX());
         zDist = abs(-viewPointZ - pyramid[i]->getZ());
         dist = sqrt(xDist * xDist + zDist * zDist);
         minDist = ourTank.getRadius() + pyramid[i]->getRadius();
         if (dist <= minDist) {
            if (pyramid[i]->isForwardCollided() && ourTank.getSpeed() > 0.0) {
               ourTank.stop();
            } else if (pyramid[i]->isForwardCollided() && ourTank.getSpeed() < 0.0) {
               // do nothing
            } else if (!pyramid[i]->isForwardCollided() && !pyramid[i]->isBackwardCollided()
                       && ourTank.getSpeed() > 0) {
               ourTank.stop();
               pyramid[i]->forwardCollide();
            } else if (pyramid[i]->isBackwardCollided() && ourTank.getSpeed() < 0.0) {
               ourTank.stop();
            } else if (pyramid[i]->isBackwardCollided() && ourTank.getSpeed() > 0.0) {
               // do nothing
            } else if (!pyramid[i]->isBackwardCollided() && !pyramid[i]->isForwardCollided()
                       && ourTank.getSpeed() < 0) {
               ourTank.stop();
               pyramid[i]->backwardCollide();
            } // end if-else
         } else {
            if (pyramid[i]->isForwardCollided()) {
               pyramid[i]->unForwardCollide();
            } // end if
            if (pyramid[i]->isBackwardCollided()) {
               pyramid[i]->unBackwardCollide();
            } // end if
         } // end if-else
      } // end for
   } // end if
} else {
	// Draw title screen
   glPushMatrix();
      glScalef(2.0f, 1.0f, 1.0f);
      glColor3f(1.0, 0.0, 0.0);
      glTranslatef(-1.0f, 0.0f, -10.0f);
      strokeFont.renderText("Tank");
   glPopMatrix();
   glPushMatrix();
      glScalef(2.0f, 1.0f, 1.0f);
      glColor3f(1.0, 0.0, 0.0);
      glTranslatef(-2.5f, -1.5f, -10.0f);
      strokeFont.renderText("Commander");
   glPopMatrix();
} // end if-else
} // end drawScene

void CMyOpenGLView::updateScene() {

   if (startGame && !gameOver) {
      viewPointZ += (GLfloat) ourTank.getSpeed() * cos(azimuth * PI/180.0);
      viewPointX -= (GLfloat) ourTank.getSpeed() * sin(azimuth * PI/180.0);

      for (int i = 0; i < shells.size(); i++) {
         shells[i]->increaseRange();
         shells[i]->updateRealPosition();
             if (abs(shells[i]->getRealX()) > 1000.0 || abs(shells[i]->getRealZ()) > 1000.0) {
               delete shells[i];
               shells.erase(&shells[i]);
            } // end if
      } // end for
      for (i = 0; i < bullets.size(); i++) {
         bullets[i]->increaseRange();
         bullets[i]->updateRealPosition();
             if (abs(bullets[i]->getRealX()) > 1000.0 || 
                 bullets[i]->getRealY() <= 0.0 ||
                 abs(bullets[i]->getRealZ()) > 1000.0 ||
                 bullets[i]->getRange() > 100.0) {
               delete bullets[i];
               bullets.erase(&bullets[i]);
            } // end if
      } // end for

      if (multiPlayer) {
         for (int i = 0; i < oppShells.size(); i++) {
            oppShells[i]->increaseRange();
            oppShells[i]->updateRealPosition();
                if (abs(oppShells[i]->getRealX()) > 1000.0 || abs(oppShells[i]->getRealZ()) > 1000.0) {
                  delete oppShells[i];
                  oppShells.erase(&oppShells[i]);
               } // end if
         } // end for
         for (i = 0; i < oppBullets.size(); i++) {
            oppBullets[i]->increaseRange();
            oppBullets[i]->updateRealPosition();
                if (abs(oppBullets[i]->getRealX()) > 1000.0 || 
                    oppBullets[i]->getRealY() <= 0.0 ||
                    abs(oppBullets[i]->getRealZ()) > 1000.0 ||
                    oppBullets[i]->getRange() > 100.0) {
                  delete oppBullets[i];
                  oppBullets.erase(&oppBullets[i]);
               } // end if
         } // end for
      } // end if
   } // end if

}

/////////////////////////////////////////////////////////////////////////////
// CMyOpenGLView diagnostics

#ifdef _DEBUG
void CMyOpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void CMyOpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyOpenGLView message handlers

void CMyOpenGLView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int x = point.x;
	int y = point.y;

   // Space for selection buffer
   GLuint selectBuff[BUFFER_LENGTH];
   // Hit counter and viewport storage
   GLint viewport[4];

   // Setup selection buffer
   glSelectBuffer(BUFFER_LENGTH, selectBuff);

   // Get the viewport
   glGetIntegerv(GL_VIEWPORT, viewport);

   // Switch to projection and save the matrix
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();

   // Change render mode
   glRenderMode(GL_SELECT);
   
   // Establish new clipping volume around mouse cursor point, extending
   // two pixels in the vertical and horizontal directions.
   glLoadIdentity();
   gluPickMatrix(x, (viewport[3] - y), 2, 2, viewport);

   // Apply perspective matrix
	gluPerspective(45.0f, (GLfloat)winSizeX/(GLfloat)winSizeY, 1.0f, 50.0f);

   // Draw the scene
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   setViewPoint();

   drawScene();

   // Restore the projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();

   // Go back to modelview for normal rendering
   glMatrixMode(GL_MODELVIEW);

	COpenGLView::OnRButtonDown(nFlags, point);
}


void CMyOpenGLView::setUpLighting() {

	GLfloat lit0_amb[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat lit0_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lit0_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lit1_amb[] = {0.2f, 0.2f, 0.2f, 1.0f};
   GLfloat lit1_diffuse[] = {0.5f, 0.5f, 0.5f, 1.0f};
	GLfloat lit1_spec[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat lit2_amb[] = {0.05f, 0.05f, 0.05f, 1.0f};
	GLfloat lit2_diffuse[] = {0.0f, 1.0f, 0.0f, 1.0f};
	GLfloat lit2_spec[] = {0.0f, 1.0f, 0.0f, 1.0f};

	glEnable(GL_LIGHTING);

	// Explicitly set shade model to default
	glShadeModel (GL_SMOOTH);
   
	glEnable( GL_COLOR_MATERIAL );
	glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat global_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient);
   glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
   glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	// Light0
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit0_spec);   
	glEnable( GL_LIGHT0 );

	// Light1
	glLightfv(GL_LIGHT1, GL_AMBIENT, lit1_amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lit1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lit1_spec);   
	glEnable( GL_LIGHT1 );

	// Light2
	glLightfv(GL_LIGHT2, GL_AMBIENT, lit2_amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lit2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lit2_spec);
   glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0);
//	glEnable( GL_LIGHT2 );

   GLfloat fogColor[3] = {0.5, 0.5, 0.5};
   glEnable(GL_FOG);
   glFogi(GL_FOG_MODE, GL_EXP2);
   glFogfv(GL_FOG_COLOR, fogColor);
   glFogf(GL_FOG_DENSITY, 0.0009f);
   glHint(GL_FOG_HINT, GL_DONT_CARE);
   glFogf(GL_FOG_START, 300.0);
   glFogf(GL_FOG_END, 500.0);
}


void CMyOpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//   char buffer[50];
//   int i;
   char* mainGun = "105_mm.wav";
   char* machineGun = "50clmgs1.wav";

	// TODO: Add your message handler code here and/or call default
   // handle keyboard inputs
   if (startGame && !gameOver) {
      switch (nChar) {

		   // up arrow key
		   case VK_UP:
            ourTank.increaseSpeed();
   /*   i =  sprintf(buffer, "X: ");
      i += sprintf(buffer + i, "%.1f  ", viewPointX);
      i += sprintf(buffer + i, "Y: ");
      i += sprintf(buffer + i, "%.1f  ", viewPointY);
      i += sprintf(buffer + i, "Z: ");
      i += sprintf(buffer + i, "%.1f  ", viewPointZ);
      i += sprintf(buffer + i, "Az: ");
      i += sprintf(buffer + i, "%.1f\r\n", azimuth);
            console::output(buffer);*/
			   break;

		   // down arrow key
		   case VK_DOWN:
            ourTank.decreaseSpeed();
			   break;

         case VK_LEFT:
            azimuth--;
            if (azimuth < 0) {
               azimuth += 360;
            } // end if
            break;

         case VK_RIGHT:
            azimuth++;
            if (azimuth > 360) {
               azimuth -= 360;
            } // end if
            break;

         // f: fire main gun
         case 0x46:
            if (ourTank.getShells() > 0) {
               if (!shotFired) {
                  shells.push_back(new Shell());
                  shells.back()->init(-viewPointX + 1, viewPointY + 5, -viewPointZ + 1, azimuth);
                  previousShotTime = timeGetTime();
                  shotFired = true;
                  ourTank.fireShell();
                  sndPlaySound(mainGun, SND_ASYNC | SND_FILENAME );
                  if (multiPlayer) {
                     Packet *packet = new Packet;
                     packet->packetType = 1;
                     packet->id = shells.back()->getID();
                     packet->x = -viewPointX + 1;
                     packet->y = viewPointY + 5;
                     packet->z = -viewPointZ + 1;
                     packet->azimuth = azimuth;
                     int len = sizeof(*packet);
                     if (server) {
                        if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                     {
		                  CheckError(m_receiveSocket.GetLastError());
		                  m_receiveSocket.Close();
                        multiPlayer = false;
	                     }
                        delete packet;
                     } else {
	                     if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                     {
		                  CheckError(m_clientSocket.GetLastError());
		                  m_clientSocket.Close();
                        multiPlayer = false;
	                     }
                        delete packet;
                     } // end if-else
                  } // end if
               } else if (shotFired && ElapsedTimeInMSSinceLastShot() >= 10000 
                          && ourTank.getShells() > 0) {
                  shells.push_back(new Shell());
                  shells.back()->init(-viewPointX + 1, viewPointY + 5, -viewPointZ + 1, azimuth);
                  previousShotTime = timeGetTime();
                  ourTank.fireShell();
                  sndPlaySound(mainGun, SND_ASYNC | SND_FILENAME );
                  if (multiPlayer) {
                     Packet *packet = new Packet;
                     packet->packetType = 1;
                     packet->id = shells.back()->getID();
                     packet->x = -viewPointX + 1;
                     packet->y = viewPointY + 5;
                     packet->z = -viewPointZ + 1;
                     packet->azimuth = azimuth;
                     int len = sizeof(*packet);
                     if (server) {
                        if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                     {
		                  CheckError(m_receiveSocket.GetLastError());
		                  m_receiveSocket.Close();
                        multiPlayer = false;
	                     }
                        delete packet;
                     } else {
	                     if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                     {
		                  CheckError(m_clientSocket.GetLastError());
		                  m_clientSocket.Close();
                        multiPlayer = false;
	                     }
                        delete packet;
                     } // end if-else
                  } // end if-else
               } // end if
            } // end if
            break;

         // m: move the machine gun around with the view
         case 0x4D:
            if (mgLatch) {
               mgLatch = false;
               elevation = 0.0;
               rotation = 0.0;
            } else {
               mgLatch = true;
            } // end if
            break;

         // Space Bar: fire machine gun
         case ' ':
//   i = sprintf(buffer, "x: %.0f  z: %.0f  Az: %.0f\r\n", viewPointX, viewPointZ, azimuth);
//   console::output(buffer);
            if (ourTank.getBullets() > 0) {
               bullets.push_back(new Bullet());
               bullets.back()->init(-viewPointX + 1, viewPointY + 5, -viewPointZ + 1, 
                                    azimuth, elevation, rotation);
               ourTank.fireBullet();
               sndPlaySound(machineGun, SND_ASYNC | SND_FILENAME );
               if (multiPlayer) {
                  Packet *packet = new Packet;
                  packet->packetType = 2;
                  packet->id = bullets.back()->getID();
                  packet->x = -(-viewPointX + 1);
                  packet->y = viewPointY + 5;
                  packet->z = -(-viewPointZ + 1);
                  packet->azimuth = bullets.back()->getAzimuth();
                  packet->elevation = bullets.back()->getElevation();
                  packet->rotation = bullets.back()->getRotation();
                  int len = sizeof(*packet);
                  if (server) {
                     if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_receiveSocket.GetLastError());
		               m_receiveSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } else {
	                  if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	                  {
		               CheckError(m_clientSocket.GetLastError());
		               m_clientSocket.Close();
                     multiPlayer = false;
	                  }
                     delete packet;
                  } // end if-else
               } // end if
            } // end if
            break;

      } // end switch
   } // end if
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMyOpenGLView::OnMouseMove(UINT nFlags, CPoint point) 
{
   char* machineGun = "50clmgs1.wav";

	// TODO: Add your message handler code here and/or call default
   if (startGame && !gameOver) {
      int x = point.x;
	   int y = point.y;

	   if (nFlags == MK_LBUTTON && mgLatch) {
         if (ourTank.getBullets() > 0) {
            bullets.push_back(new Bullet());
            bullets.back()->init(-viewPointX + 1, viewPointY + 5, -viewPointZ + 1, 
                                 azimuth, elevation, rotation);
            ourTank.fireBullet();
            sndPlaySound(machineGun, SND_ASYNC | SND_FILENAME );
            if (multiPlayer) {
               Packet *packet = new Packet;
               packet->packetType = 2;
               packet->id = bullets.back()->getID();
               packet->x = -viewPointX + 1;
               packet->y = viewPointY + 5;
               packet->z = -viewPointZ + 1;
               packet->azimuth = bullets.back()->getAzimuth();
               packet->elevation = bullets.back()->getElevation();
               packet->rotation = bullets.back()->getRotation();
               int len = sizeof(*packet);
               if (server) {
                  if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	               {
		            CheckError(m_receiveSocket.GetLastError());
		            m_receiveSocket.Close();
                  multiPlayer = false;
	               }
                  delete packet;
               } else {
	               if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	               {
		            CheckError(m_clientSocket.GetLastError());
		            m_clientSocket.Close();
                  multiPlayer = false;
	               }
                  delete packet;
               } // end if-else
            } // end if
         } // end if
	   } // end if

      if(y-mouseY > 0) {	
	      rotationX+=2;
         if (mgLatch) {
            if (rotationX > 10) {
               rotationX = 10;
            } // end if
            elevation = -rotationX;
         } else {
            elevation = 0.0;
         } // end if-else
	   }
	   else if(y-mouseY < 0){ 		
	      rotationX-=2;
         if (mgLatch) {
            if (rotationX < -20) {
               rotationX = -20;
            } // end if
            elevation = -rotationX;
         } else {
            elevation = 0.0;
         } // end if-else
      }
      if(x-mouseX > 0) {
	      rotationY+=2;
         if (mgLatch) {
            if (rotationY > 50) {
               rotationY = 50;
            } // end if
            rotation = rotationY;
         } else {
            rotation = 0.0;
         } // end if-else
      }
      else if(x-mouseX < 0){
         rotationY-=2;
         if (mgLatch) {
            if (rotationY < -50) {
               rotationY = -50;
            } // end if
            rotation = rotationY;
         } else {
            rotation = 0.0;
         } // end if-else
	   }
	   
	   if (nFlags == MK_LBUTTON && !mgLatch) {
         if(y-mouseY > 0) {	
	         rotationX+=2;
	      }
	      else if(y-mouseY < 0){ 		
	         rotationX-=2;
         }
         if(x-mouseX > 0) {
	         rotationY+=2;
         }
         else if(x-mouseX < 0){
            rotationY-=2;
	      }
	   } // end if

      mouseX = x; 
	   mouseY = y;


	   CView::OnMouseMove(nFlags, point);
   } // end if
}


bool CMyOpenGLView::setUpTextures() {

	AUX_RGBImageRec* brickImage;
	AUX_RGBImageRec* siding1Image;
	AUX_RGBImageRec* marbleImage;
	AUX_RGBImageRec* skyImage;
	AUX_RGBImageRec* tilesImage;
	AUX_RGBImageRec* shingleImage;	
	AUX_RGBImageRec* camoImage;
	AUX_RGBImageRec* dcamoImage;

	brickImage = auxDIBImageLoadA("brick.bmp");
	siding1Image = auxDIBImageLoadA("siding1.bmp");
	marbleImage = auxDIBImageLoadA("marble.bmp");
	skyImage = auxDIBImageLoadA("clouds.bmp");
	tilesImage = auxDIBImageLoadA("tiles.bmp");
	shingleImage = auxDIBImageLoadA("shingle.bmp");
	camoImage = auxDIBImageLoadA("camo.bmp");
	dcamoImage = auxDIBImageLoadA("desertcamo.bmp");
	
	ASSERT (brickImage != 0);
	ASSERT (siding1Image != 0);
	ASSERT (marbleImage != 0);
	ASSERT (skyImage != 0);
	ASSERT (tilesImage != 0);
	ASSERT (shingleImage != 0);
	ASSERT (camoImage != 0);
	ASSERT (dcamoImage != 0);

	glGenTextures(8, textNames);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	glBindTexture(GL_TEXTURE_2D, textNames[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, brickImage->sizeX,
		          brickImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 brickImage->data);

	glBindTexture(GL_TEXTURE_2D, textNames[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, siding1Image->sizeX,
		          siding1Image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 siding1Image->data);
	
	glBindTexture(GL_TEXTURE_2D, textNames[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, marbleImage->sizeX,
		          marbleImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 marbleImage->data);

	glBindTexture(GL_TEXTURE_2D, textNames[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyImage->sizeX,
		          skyImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 skyImage->data);

	glBindTexture(GL_TEXTURE_2D, textNames[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tilesImage->sizeX,
		          tilesImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 tilesImage->data);

	glBindTexture(GL_TEXTURE_2D, textNames[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, shingleImage->sizeX,
		          shingleImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 shingleImage->data);

	glBindTexture(GL_TEXTURE_2D, textNames[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, camoImage->sizeX,
		          camoImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 camoImage->data);

	glBindTexture(GL_TEXTURE_2D, textNames[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dcamoImage->sizeX,
		          dcamoImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,
					 dcamoImage->data);

	return true;
}


float CMyOpenGLView::calculateRelativeBearing(float oppX, float oppZ) {

   float deltaX, deltaZ;
   float heading;
   float relativeBearing;

   deltaX = oppX + viewPointX;
   deltaZ = oppZ + viewPointZ;

   if (deltaX == 0) {
      if (deltaZ >= 0) {
         heading = 180;
      } else {
         heading = 0;
      } // end if-else
   } else if (deltaZ == 0) {
      if (deltaX >= 0) {
         heading = 90;
      } else {
         heading = 270;
      } // end if-else
   } else if (oppX > (-viewPointX) && oppZ < (-viewPointZ)) {
      heading = atan(deltaX / (-deltaZ)) * 180.0f / PI;
   } else if (oppX > (-viewPointX) && oppZ > (-viewPointZ)) {
      heading = 90 + atan(deltaZ / deltaX) * 180.0f / PI;
   } else if (oppX < (-viewPointX) && oppZ > (-viewPointZ)) {
      heading =  180 - atan(deltaX / deltaZ) * 180.0f / PI;
   } else { // (pilotX < enemyX && pilotY < enemyY)
      heading = 360 - atan(deltaX / deltaZ) * 180.0f / PI;
   } // end if-else

   relativeBearing = heading - azimuth;
   if (relativeBearing < 0) {
      relativeBearing += 360;
   } // end if

   return relativeBearing;
} // end calculateRelativeBearing


void CMyOpenGLView::respawn() {
   int previousSpawn = spawnSite;
   do {
      spawnSite = rand() % 4;
      viewPointX = spawnSites[spawnSite][0];
      viewPointZ = spawnSites[spawnSite][1];
      azimuth = spawnSites[spawnSite][2];
   } while (spawnSiteActive[spawnSite] == true);
   ourTank.setX(spawnSites[spawnSite][0]);
   ourTank.setZ(spawnSites[spawnSite][1]);
   rotationX = rotationY = 0;
   spawnSiteActive[spawnSite] = true;
   if (ourTank.isRespawning()) {
      spawnSiteActive[previousSpawn] = false;
   } // end if
   ourTank.setRespawnFlag(true);
   ourTank.regen();
   Packet *packet = new Packet;
   packet->packetType = 10;
   packet->id = spawnSite;
   packet->spawnSiteActive = true;
   int len = sizeof(*packet);
   if (server) {
      if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	   {
		CheckError(m_receiveSocket.GetLastError());
		m_receiveSocket.Close();
      multiPlayer = false;
	   }
      delete packet;
   } else {
	   if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	   {
		CheckError(m_clientSocket.GetLastError());
		m_clientSocket.Close();
      multiPlayer = false;
	   }
      delete packet;
   } // end if-else
}


void CMyOpenGLView::OnCollisionOn() 
{
	// TODO: Add your command handler code here
   collisionDetection = true;
	
}

void CMyOpenGLView::OnCollisionOff() 
{
	// TODO: Add your command handler code here
   collisionDetection = false;
	
}

void CMyOpenGLView::OnHost() 
{
//   char buffer[50];
   CString peerName;
   UINT* port = (UINT*) &m_iPort;
	// TODO: Add your command handler code here
	m_serverSocket.Create(m_iPort);
	if (!m_serverSocket.Listen())
	{
		AfxMessageBox("Listen() Failed!");
		m_serverSocket.Close();
	}
   server = true;
   m_serverSocket.GetSockName(peerName, *port);
/*   int i = 0;
      i =  sprintf(buffer, "Socket address: ");
      console::output(buffer);
     i += sprintf(buffer + i, "%s  ", peerName);
   console::output(peerName);
      i = sprintf(buffer , " Port: ");
      i += sprintf(buffer + i, "%d\n", m_iPort);
           console::output(buffer);
*/
	// Locate the network submenu
	CMenu* pNetworkMenu = NULL;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
		CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_HOST)
		{
			pNetworkMenu = pMenu;
			break;
		}
	}

   pNetworkMenu->DeleteMenu(ID_HOST, MF_BYCOMMAND);
   pNetworkMenu->DeleteMenu(ID_JOIN, MF_BYCOMMAND);
   pNetworkMenu->AppendMenu(MF_STRING, ID_DISCONNECT, "Disconnect");
}

void CMyOpenGLView::OnJoin() 
{
	// TODO: Add your command handler code here
	if (!m_clientSocket.Create())
	{
		AfxMessageBox("Failed to create Socket");
	}

   if (joinDialog.DoModal() == IDOK) {
      CString hostAddress = joinDialog.m_ipAdd;
	   if (m_clientSocket.Connect(hostAddress, 12345))
	   {
         multiPlayer = true;
         startGame = true;
         do {
            gameStartTime = timeGetTime();
            spawnSite = rand() % 2 + 2;
            viewPointX = spawnSites[spawnSite][0];
            viewPointZ = spawnSites[spawnSite][1];
            azimuth = spawnSites[spawnSite][2];
         } while (spawnSiteActive[spawnSite] == true);
         ourTank.setX(spawnSites[spawnSite][0]);
         ourTank.setZ(spawnSites[spawnSite][1]);
         spawnSiteActive[spawnSite] = true;
         ourTank.setRespawnFlag(true);
//         sndPlaySound("1492.wav", SND_LOOP | SND_ASYNC | SND_FILENAME);
         Packet *packet = new Packet;
         packet->packetType = 10;
         packet->id = spawnSite;
         packet->spawnSiteActive = true;
         int len = sizeof(*packet);
         if (server) {
            if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	         {
		      CheckError(m_receiveSocket.GetLastError());
		      m_receiveSocket.Close();
            multiPlayer = false;
	         }
            delete packet;
         } else {
	         if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	         {
		      CheckError(m_clientSocket.GetLastError());
		      m_clientSocket.Close();
            multiPlayer = false;
	         }
            delete packet;
         } // end if-else
	      CMenu* pNetworkMenu = NULL;
	      CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	      int iPos;
	      for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	      {
		      CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		      if (pMenu && pMenu->GetMenuItemID(0) == ID_HOST)
		      {
			      pNetworkMenu = pMenu;
			      break;
		      }
	      }

         pNetworkMenu->DeleteMenu(ID_HOST, MF_BYCOMMAND);
         pNetworkMenu->DeleteMenu(ID_JOIN, MF_BYCOMMAND);
         pNetworkMenu->AppendMenu(MF_STRING, ID_DISCONNECT, "Disconnect");
	   }
	   else
	   {
		   CheckError(m_clientSocket.GetLastError());
		   m_clientSocket.Close();
	   }
   } // end if
	
}


void CMyOpenGLView::OnDisconnect() 
{
	// TODO: Add your command handler code here
	m_serverSocket.Close();
   m_receiveSocket.Close();
	m_clientSocket.Close();
   multiPlayer = false;
   if (server) {
      server = false;
   } // end if
	CMenu* pNetworkMenu = NULL;
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
	int iPos;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
		CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && (pMenu->GetMenuItemID(0) == ID_DISCONNECT))
		{
			pNetworkMenu = pMenu;
			break;
		}
	}

   pNetworkMenu->DeleteMenu(ID_DISCONNECT, MF_BYCOMMAND);
   pNetworkMenu->InsertMenu(0, MF_BYPOSITION, ID_JOIN, "Join");
   pNetworkMenu->InsertMenu(0, MF_BYPOSITION, ID_HOST, "Host");
	
}


// all of this happens once a connection is made
void CMyOpenGLView::OnAccept()
{
//	if(!m_serverSocket.Accept(m_sConnectSocket))
	if(!m_serverSocket.Accept(m_receiveSocket))
	{
		AfxMessageBox("Accept() failed");
		return;
	}
   multiPlayer = true;
   startGame = true;
   do {
      gameStartTime = timeGetTime();
      spawnSite = rand() % 2;
      viewPointX = spawnSites[spawnSite][0];
      viewPointZ = spawnSites[spawnSite][1];
      azimuth = spawnSites[spawnSite][2];
   } while (spawnSiteActive[spawnSite] == true);
   ourTank.setX(spawnSites[spawnSite][0]);
   ourTank.setZ(spawnSites[spawnSite][1]);
   spawnSiteActive[spawnSite] = true;
   ourTank.setRespawnFlag(true);
//   sndPlaySound("1492.wav", SND_LOOP | SND_ASYNC | SND_FILENAME);
   Packet *packet = new Packet;
   packet->packetType = 10;
   packet->id = spawnSite;
   packet->spawnSiteActive = true;
   int len = sizeof(*packet);
   if (server) {
      if (m_receiveSocket.Send((void*)packet, len) == SOCKET_ERROR)
	   {
		CheckError(m_receiveSocket.GetLastError());
		m_receiveSocket.Close();
      multiPlayer = false;
	   }
      delete packet;
   } else {
	   if (m_clientSocket.Send((void*)packet, len) == SOCKET_ERROR)
	   {
		CheckError(m_clientSocket.GetLastError());
		m_clientSocket.Close();
      multiPlayer = false;
	   }
      delete packet;
   } // end if-else
}


// functions required because CAsyncSocket is a template, and all
// pure virtual functions must be overridden
void CMyOpenGLView::OnReceive()
{
//   char buffer[64];
//   int i;

   Packet *packet = new Packet;
   int packetType;
   if (server) {
      if (m_receiveSocket.Receive(packet, sizeof(*packet)) == SOCKET_ERROR) {
		CheckError(m_receiveSocket.GetLastError());
		m_receiveSocket.Close();
      multiPlayer = false;
      } else {
         packetType = packet->packetType;
      } // end if-else
   } else {
      if (m_clientSocket.Receive(packet, sizeof(*packet)) == SOCKET_ERROR) {
		CheckError(m_clientSocket.GetLastError());
		m_clientSocket.Close();
      multiPlayer = false;
      } else {
         packetType = packet->packetType;
      } // end if-else
   } // end if-else
/*      i =  sprintf(buffer, "Rcvd packet type: %d\r\n", packetType);
      i += sprintf(buffer + i, "X: %.1f", packet->x);
      i += sprintf(buffer + i, " Y: %.1f", packet->y);
      i += sprintf(buffer + i, " Z: %.1f\r\n", packet->z);
      i += sprintf(buffer + i, "Az: %.1f", packet->azimuth);
      i += sprintf(buffer + i, " RotX: %.1f", packet->rotationX);
      i += sprintf(buffer + i, " RotY: %.1f\r\n", packet->rotationY);
      console::output(buffer);*/

   switch (packetType) {

   case 0:
      opponent.setX(packet->x);
      opponent.setY(packet->y);
      opponent.setZ(packet->z);
      opponent.setAzimuth(packet->azimuth);
      opponent.setRotationX(packet->rotationX);
      opponent.setRotationY(packet->rotationY);
      opponent.setSpeed(packet->speed);
//      opponent.setDestroyed(packet->isDestroyed);
      opponent.setMGLatch(packet->mgLatch);
      break;
   case 1:
      oppShells.push_back(new Shell());
      oppShells.back()->init(packet->x, packet->y, packet->z, packet->azimuth);
      break;
   case 2:
      oppBullets.push_back(new Bullet());
      oppBullets.back()->init(packet->x, packet->y, packet->z,
                              packet->azimuth, packet->elevation, packet->rotation);
      break;
   case 3:
      ourTank.takeDamage(packet->damage);
      break;
   case 4:
      friendly[packet->id]->takeDamage(packet->damage);
      if (friendly[packet->id]->isDestroyed() && friendly[packet->id]->getExplosion() == 0) {
         friendly[packet->id]->startExplosion();
         sndPlaySound("explobig.wav", SND_ASYNC | SND_FILENAME );
      } // end if
      break;
   case 5:
      enemy[packet->id]->takeDamage(packet->damage);
      if (enemy[packet->id]->isDestroyed() && enemy[packet->id]->getExplosion() == 0) {
         enemy[packet->id]->startExplosion();
         sndPlaySound("explobig.wav", SND_ASYNC | SND_FILENAME );
      } // end if
      break;
   case 6:
      house[packet->id]->takeDamage(packet->damage);
      if (house[packet->id]->isDestroyed() && house[packet->id]->getExplosion() == 0) {
         house[packet->id]->startExplosion();
         sndPlaySound("explobig.wav", SND_ASYNC | SND_FILENAME );
      } // end if
      break;
   case 7:
      pine[packet->id]->takeDamage(packet->damage);
      if (pine[packet->id]->isDestroyed() && pine[packet->id]->getExplosion() == 0) {
         pine[packet->id]->startExplosion();
         sndPlaySound("explobig.wav", SND_ASYNC | SND_FILENAME );
      } // end if
      break;
   case 8:
      smallPine[packet->id]->takeDamage(packet->damage);
      if (smallPine[packet->id]->isDestroyed() && smallPine[packet->id]->getExplosion() == 0) {
         smallPine[packet->id]->startExplosion();
         sndPlaySound("explobig.wav", SND_ASYNC | SND_FILENAME );
      } // end if
      break;
   case 9:
      silo[packet->id]->takeDamage(packet->damage);
      if (silo[packet->id]->isDestroyed() && silo[packet->id]->getExplosion() == 0) {
         silo[packet->id]->startExplosion();
         sndPlaySound("explobig.wav", SND_ASYNC | SND_FILENAME );
      } // end if
      break;
   case 10:
      spawnSiteActive[packet->id] = packet->spawnSiteActive;
      break;
   case 11:
      opponent.takeDamage(packet->damage);
      break;
   } // end switch

}

void CMyOpenGLView::OnSend()
{
}


// executes when a client closes a connection
void CMyOpenGLView::OnClose()
{
	m_serverSocket.Close();
   m_receiveSocket.Close();
   m_clientSocket.Close();
   multiPlayer = false;
   if (server) {
      server = false;
   } // end if
}

void CMyOpenGLView::OnConnect()
{
}


// Check for the last error message.
void CMyOpenGLView::CheckError(int errorCode)
{
	switch (errorCode)
	{
	case WSANOTINITIALISED:
		AfxMessageBox ("WSANOTINITIALISED");
		break;
	case WSAENETDOWN:
		AfxMessageBox ("WSAENETDOWN");
		break;
	case WSAEADDRINUSE:
		AfxMessageBox ("WSAEADDRINUSE");
		break;
	case WSAEINPROGRESS:
		AfxMessageBox ("WSAEINPROGRESS");
		break;
	case WSAEINVAL:
		AfxMessageBox ("WSAEINVAL");
		break;
	case WSAEISCONN:
		AfxMessageBox ("WSAEISCONN");
		break;
	case WSAEMFILE:
		AfxMessageBox ("WSAEMFILE");
		break;
	case WSAENOBUFS:
		AfxMessageBox ("WSAENOBUFS");
		break;
	case WSAENOTSOCK:
		AfxMessageBox ("WSAENOTSOCK");
		break;
	case WSAEOPNOTSUPP:
		AfxMessageBox ("WSAEOPNOTSUPP");
		break;
	case WSAEFAULT:
		AfxMessageBox ("WSAEFAULT");
		break;
	case WSAEWOULDBLOCK:
		AfxMessageBox ("WSAEWOULDBLOCK");
		break;
	case WSAEAFNOSUPPORT:
		AfxMessageBox ("WSAEAFNOSUPPORT");
		break;
	case WSAEADDRNOTAVAIL:
		AfxMessageBox ("WSAEADDRNOTAVAIL");
		break;
	case WSAECONNREFUSED:
		AfxMessageBox ("WSAECONNREFUSED");
		break;
	case WSAEDESTADDRREQ:
		AfxMessageBox ("WSAEDESTADDRREQ");
		break;
	case WSAENETUNREACH:
		AfxMessageBox ("WSAENETUNREACH");
		break;
	case WSAETIMEDOUT:
		AfxMessageBox ("WSAETIMEDOUT");
		break;
	case WSAEMSGSIZE:
		AfxMessageBox ("WSAEMSGSIZE");
		break;
	case WSAECONNABORTED:
		AfxMessageBox ("WSAECONNABORTED");
		break;
	case WSAECONNRESET:
		AfxMessageBox ("WSAECONNRESET");
		break;
	default:
		AfxMessageBox ("Wow. I didn't think this would happen.");
		break;
	}// end of big switch-case
} // end CheckError()

void CMyOpenGLView::OnSingle() 
{
	// TODO: Add your command handler code here
   startGame = true;
   gameStartTime = timeGetTime();
   spawnSite = rand() % 4;
   viewPointX = spawnSites[spawnSite][0];
   viewPointZ = spawnSites[spawnSite][1];
   azimuth = spawnSites[spawnSite][2];
//   sndPlaySound("1492.wav", SND_LOOP | SND_ASYNC | SND_FILENAME);
}

void CMyOpenGLView::OnMulti() 
{
	// TODO: Add your command handler code here
	CMenu* pTopMenu = AfxGetMainWnd()->GetMenu();
   CMenu* pNetworkMenu = NULL;
	int iPos;
	for (iPos = pTopMenu->GetMenuItemCount()-1; iPos >= 0; iPos--)
	{
		CMenu* pMenu = pTopMenu->GetSubMenu(iPos);
		if (pMenu && pMenu->GetMenuItemID(0) == ID_HOST)
		{
			pNetworkMenu = pMenu;
			break;
		}
	}
   pTopMenu->EnableMenuItem(1, MF_BYPOSITION | MF_ENABLED);
   pNetworkMenu->EnableMenuItem(ID_HOST, MF_BYCOMMAND | MF_ENABLED);
   pNetworkMenu->EnableMenuItem(ID_JOIN, MF_BYCOMMAND | MF_ENABLED);
}

void CMyOpenGLView::OnQuit() 
{
	// TODO: Add your command handler code here
   if (multiPlayer) {
	   m_serverSocket.Close();
      m_receiveSocket.Close();
      m_clientSocket.Close();
   } // end if
   exit(0);
//   SendMessage(WM_CLOSE);
}

