// SinglePlayerDialog.cpp : implementation file
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "stdafx.h"
#include "OpenGL.h"
#include "SinglePlayerDialog.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CSinglePlayerDialog dialog


CSinglePlayerDialog::CSinglePlayerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSinglePlayerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSinglePlayerDialog)
	//}}AFX_DATA_INIT
}


void CSinglePlayerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSinglePlayerDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSinglePlayerDialog, CDialog)
	//{{AFX_MSG_MAP(CSinglePlayerDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinglePlayerDialog message handlers

void CSinglePlayerDialog::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	CButton* pOKButton = (CButton *) (GetDlgItem(IDOK));
   if (!pOKButton->IsWindowEnabled()) {
      pOKButton->EnableWindow(true);
   } // end if
	
}

void CSinglePlayerDialog::OnRadio10() 
{
	// TODO: Add your control notification handler code here
	CButton* pOKButton = (CButton *) (GetDlgItem(IDOK));
   if (!pOKButton->IsWindowEnabled()) {
      pOKButton->EnableWindow(true);
   } // end if
	
}

void CSinglePlayerDialog::OnRadio15() 
{
	// TODO: Add your control notification handler code here
	CButton* pOKButton = (CButton *) (GetDlgItem(IDOK));
   if (!pOKButton->IsWindowEnabled()) {
      pOKButton->EnableWindow(true);
   } // end if
	
}
