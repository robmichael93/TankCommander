#if !defined(AFX_ROTATIONDIALOG_H__0BFF0474_8B7E_11D5_8639_00E01890ACE0__INCLUDED_)
#define AFX_ROTATIONDIALOG_H__0BFF0474_8B7E_11D5_8639_00E01890ACE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RotationDialog.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CRotationDialog dialog

class CRotationDialog : public CDialog
{
// Construction
public:
	CRotationDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRotationDialog)
	enum { IDD = IDD_ROTATION_DIALOG };
	float	m_angle1_increment;
	float	m_angle2_increment;
	float	m_angle3_increment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRotationDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTATIONDIALOG_H__0BFF0474_8B7E_11D5_8639_00E01890ACE0__INCLUDED_)
