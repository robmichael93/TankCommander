#if !defined(AFX_CONSOLEDIALOG_H__4A80B540_9D93_11D5_8639_00E01890ACE0__INCLUDED_)
#define AFX_CONSOLEDIALOG_H__4A80B540_9D93_11D5_8639_00E01890ACE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConsoleDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConsoleDialog dialog

class CConsoleDialog : public CDialog
{
// Construction
public:
	CConsoleDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConsoleDialog)
	enum { IDD = IDD_CONSOLE };
	CEdit	m_consoleText;
	CView*	m_pView;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsoleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConsoleDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOLEDIALOG_H__4A80B540_9D93_11D5_8639_00E01890ACE0__INCLUDED_)
