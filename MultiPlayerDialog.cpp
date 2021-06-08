// MultiPlayerDialog.cpp : implementation file
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "stdafx.h"
#include "OpenGL.h"
#include "MultiPlayerDialog.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiPlayerDialog dialog


CMultiPlayerDialog::CMultiPlayerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiPlayerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiPlayerDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMultiPlayerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiPlayerDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMultiPlayerDialog::SetParent(CView *pWnd)
{
	m_pWnd = pWnd;
}


BEGIN_MESSAGE_MAP(CMultiPlayerDialog, CDialog)
	//{{AFX_MSG_MAP(CMultiPlayerDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiPlayerDialog message handlers
