#if !defined(AFX_JOINDIALOG_H__AB40A560_4916_463E_9A05_B4A3A4BAF90C__INCLUDED_)
#define AFX_JOINDIALOG_H__AB40A560_4916_463E_9A05_B4A3A4BAF90C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JoinDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CJoinDialog dialog

class CJoinDialog : public CDialog
{
// Construction
public:
	CJoinDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CJoinDialog)
	enum { IDD = IDD_JOIN_DIALOG };
	CString	m_ipAdd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJoinDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJoinDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JOINDIALOG_H__AB40A560_4916_463E_9A05_B4A3A4BAF90C__INCLUDED_)
