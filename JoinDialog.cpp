// JoinDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "JoinDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJoinDialog dialog


CJoinDialog::CJoinDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CJoinDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJoinDialog)
	m_ipAdd = _T("");
	//}}AFX_DATA_INIT
}


void CJoinDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJoinDialog)
	DDX_Text(pDX, ID_IPADD, m_ipAdd);
	DDV_MaxChars(pDX, m_ipAdd, 64);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJoinDialog, CDialog)
	//{{AFX_MSG_MAP(CJoinDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJoinDialog message handlers

void CJoinDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
   UpdateData(TRUE);
}

void CJoinDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CJoinDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
   UpdateData(FALSE); 
	CEdit* pEditField = (CEdit *) (GetDlgItem(ID_IPADD));
	pEditField->SetFocus();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
