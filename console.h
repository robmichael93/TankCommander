#if !defined(AFX_CONSOLECLASS_H__FF725165_46D5_11D4_904E_00104B2E2822__INCLUDED_)
#define AFX_CONSOLECLASS_H__FF725165_46D5_11D4_904E_00104B2E2822__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConsoleClass.h : header file
//

#include <wincon.h>
#include <string.h>
#include <stdlib.h>
#include <afx.h>

#include "resource.h"
#include "ConsoleDialog.h"

/////////////////////////////////////////////////////////////////////////////
// CConsoleClass

class console
{
public:

	console();

   ~console();

   static void showConsole();

   static void closeConsole();

   static void setView(CView* pView);

	static void output(char *);
	static void output(int);
	static void output(double);
	static void output(CString);

protected:

	static bool consoleEnabled;

   static bool consoleCreated;

   static CConsoleDialog * m_pConsoleDialog;
   
};



#endif // !defined(AFX_CONSOLECLASS_H__FF725165_46D5_11D4_904E_00104B2E2822__INCLUDED_)
