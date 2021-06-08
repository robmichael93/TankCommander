// MySocket.cpp : implementation file
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "stdafx.h"
#include "OpenGL.h"
#include "MySocket.h"
#include "MyOpenGLView.cpp"



/////////////////////////////////////////////////////////////////////////////
// MySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMySocket, CSocket)
	//{{AFX_MSG_MAP(CMySocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// MySocket member functions
void CMySocket::SetParent(CView *pWnd)
{
	m_pWnd = pWnd;
}

// because CMySocket is derived from CAsyncSocket, these functions are called
// automatically when these events happen.  They simply call the related function
// located in the parent class.

// Once an accept happens, call the OnAccept() function of the dlg class
void CMySocket::OnAccept(int iErrorCode)
{
	if (iErrorCode == 0)
	{
		((CMyOpenGLView*)m_pWnd)->OnAccept();
	}
	else
	{
		AfxMessageBox("Error Code: " + (CString)iErrorCode);
	}
}

// none of these functions should execute, but they are here because they help
// with debugging and they are required to be overridden due to the fact
// that they are pure virtual functions in CAsyncSocket
void CMySocket::OnConnect(int iErrorCode)
{
//	AfxMessageBox("void CMySocket::OnConnect(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMyOpenGLView*)m_pWnd)->OnConnect();
	}

}

void CMySocket::OnClose(int iErrorCode)
{
//	AfxMessageBox("void CMySocket::OnClose(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMyOpenGLView*)m_pWnd)->OnClose();
	}

}

void CMySocket::OnReceive(int iErrorCode)
{
//	AfxMessageBox("void CMySocket::OnReceive(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMyOpenGLView*)m_pWnd)->OnReceive();
	}

}

void CMySocket::OnSend(int iErrorCode)
{
//	AfxMessageBox("void CMySocket::OnSend(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMyOpenGLView*)m_pWnd)->OnSend();
	}

}

// eof MySocket.cpp
