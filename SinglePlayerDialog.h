#if !defined(AFX_SINGLEPLAYERDIALOG_H__5E148F9C_A08E_4838_9A30_C5C03D812622__INCLUDED_)
#define AFX_SINGLEPLAYERDIALOG_H__5E148F9C_A08E_4838_9A30_C5C03D812622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SinglePlayerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSinglePlayerDialog dialog

class CSinglePlayerDialog : public CDialog
{
// Construction
public:
	CSinglePlayerDialog(CWnd* pParent = NULL);   // standard constructor
	void SetParent(CView* pWnd);

// Dialog Data
	//{{AFX_DATA(CSinglePlayerDialog)
	enum { IDD = IDD_SINGLE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSinglePlayerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSinglePlayerDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CView* m_pWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLEPLAYERDIALOG_H__5E148F9C_A08E_4838_9A30_C5C03D812622__INCLUDED_)
