#if !defined(AFX_CMYSOCKET1_H__94114506_2057_4D8A_AD10_CD7CF6DF94CB__INCLUDED_)
#define AFX_CMYSOCKET1_H__94114506_2057_4D8A_AD10_CD7CF6DF94CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// MySocket command target

class CMySocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMySocket();
	virtual ~CMySocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMySocket)
	//}}AFX_VIRTUAL
	// all of the On* functions are pure virtual in CAsyncSocket, and are required to
	// be overridden
	void OnSend(int iErrorCode);
	void OnReceive(int iErrorCode);
	void OnClose(int iErrorCode);
	void OnConnect(int iErrorCode);
	void OnAccept(int iErrorCode);
	void SetParent(CView* pWnd);

	// Generated message map functions
	//{{AFX_MSG(CMySocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	CView* m_pWnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYSOCKET1_H__94114506_2057_4D8A_AD10_CD7CF6DF94CB__INCLUDED_)
