#if !defined(AFX_MULTIPLAYERDIALOG_H__97D48904_AA63_4C9B_B238_884CA1E608D7__INCLUDED_)
#define AFX_MULTIPLAYERDIALOG_H__97D48904_AA63_4C9B_B238_884CA1E608D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MultiPlayerDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMultiPlayerDialog dialog

class CMultiPlayerDialog : public CDialog
{
// Construction
public:
	CMultiPlayerDialog(CWnd* pParent = NULL);   // standard constructor
	void SetParent(CView* pWnd);

// Dialog Data
	//{{AFX_DATA(CMultiPlayerDialog)
	enum { IDD = IDD_MULTI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiPlayerDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMultiPlayerDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CView* m_pWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTIPLAYERDIALOG_H__97D48904_AA63_4C9B_B238_884CA1E608D7__INCLUDED_)
