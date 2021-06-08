// RotationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL.h"
#include "RotationDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRotationDialog dialog


CRotationDialog::CRotationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRotationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRotationDialog)
	m_angle1_increment = 0.0f;
	m_angle2_increment = 0.0f;
	m_angle3_increment = 0.0f;
	//}}AFX_DATA_INIT
}


void CRotationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRotationDialog)
	DDX_Text(pDX, IDC_EDIT_ANGLE1, m_angle1_increment);
	DDV_MinMaxFloat(pDX, m_angle1_increment, -25.f, 25.f);
	DDX_Text(pDX, IDC_EDIT_ANGLE2, m_angle2_increment);
	DDV_MinMaxFloat(pDX, m_angle2_increment, -25.f, 25.f);
	DDX_Text(pDX, IDC_EDIT_ANGLE3, m_angle3_increment);
	DDV_MinMaxFloat(pDX, m_angle3_increment, -25.f, 25.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRotationDialog, CDialog)
	//{{AFX_MSG_MAP(CRotationDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotationDialog message handlers

void CRotationDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
   // Read from the controls
   UpdateData(TRUE);

}

BOOL CRotationDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
   // Write to the controls
   UpdateData(FALSE); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

