// MyAsyncSocket.h : header file
//
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MySocket.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// MyAsyncSocket command target

class MyAsyncSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	MyAsyncSocket();
	virtual ~MyAsyncSocket();

// Overrides
public:
	void OnSend(int iErrorCode);
	void OnReceive(int iErrorCode);
	void OnClose(int iErrorCode);
	void OnConnect(int iErrorCode);
	void OnAccept(int iErrorCode);
	void SetParent(CDialog* pWnd);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyAsyncSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(MyAsyncSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	CDialog* m_pWnd;
};