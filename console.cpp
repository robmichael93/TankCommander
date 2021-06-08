// ConsoleClass.cpp : implementation file
//

#include "stdafx.h"
#include "console.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// console
bool console::consoleEnabled(false);

bool console::consoleCreated(false);

CConsoleDialog * console::m_pConsoleDialog;

console::console()
{

   if (consoleEnabled == false) {

      m_pConsoleDialog = new CConsoleDialog();
      ASSERT (m_pConsoleDialog != NULL);
      console::consoleEnabled = true;
   }

}



console::~console()
{
   closeConsole();
   delete m_pConsoleDialog;
   console::consoleEnabled = false;
}

void console::setView(CView* pView)
{
   m_pConsoleDialog->m_pView = pView;
}


void console::showConsole()
{
   if (consoleCreated == false) {
      m_pConsoleDialog->Create(IDD_CONSOLE);
      consoleCreated = true;
   }
}
void console::closeConsole()
{
   if (consoleCreated == true) {   
	   m_pConsoleDialog->DestroyWindow();
      consoleCreated = false;
   }
}
void console::output(char * string)
{

	if (console::consoleCreated == true) {
		   m_pConsoleDialog->m_consoleText.ReplaceSel(string);
   }

}

void console::output(int value)
{

   char string[64];
  
   _ltoa(value, string, 10 );

   output(string);

}

void console::output(double value)
{

   char string[64];
   
   sprintf(string,"%2.4f",value);
   output(string);

}

void console::output(CString string)
{
   if (console::consoleCreated == true) {
		   m_pConsoleDialog->m_consoleText.ReplaceSel(LPCTSTR(string));
   }

}

