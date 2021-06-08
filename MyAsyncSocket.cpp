// MyAsyncSocket.cpp : implementation file
//
// Skip Morrow
// 04 May 2000

#include "stdafx.h"
#include "MFCAsyncPhoneServer.h"
#include "MFCAsyncPhoneServerDlg.h"
#include "MyAsyncSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyAsyncSocket

MyAsyncSocket::MyAsyncSocket()
{
}

MyAsyncSocket::~MyAsyncSocket()
{
}

void MyAsyncSocket::SetParent(CDialog *pWnd)
{
	m_pWnd = pWnd;
}

// because CMyAsyncSocket is derived from CAsyncSocket, these functions are called
// automatically when these events happen.  They simply call the related function
// located in the parent class.

// Once an accept happens, call the OnAccept() function of the dlg class
void MyAsyncSocket::OnAccept(int iErrorCode)
{
//	AfxMessageBox("MyAsyncSocket Accept() Called");
	if (iErrorCode == 0)
	{
//		AfxMessageBox("MyAsyncSocket Accept() Successful");
		((CMFCAsyncPhoneServerDlg*)m_pWnd)->OnAccept();
	}
	else
	{
		AfxMessageBox("Error Code: " + (CString)iErrorCode);
	}
}

// none of these functions should execute, but they are here because they help
// with debugging and they are required to be overridden due to the fact
// that they are pure virtual functions in CAsyncSocket
void MyAsyncSocket::OnConnect(int iErrorCode)
{
//	AfxMessageBox("void CMyAsyncSocket::OnConnect(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMFCAsyncPhoneServerDlg*)m_pWnd)->OnConnect();
	}

}

void MyAsyncSocket::OnClose(int iErrorCode)
{
//	AfxMessageBox("void CMyAsyncSocket::OnClose(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMFCAsyncPhoneServerDlg*)m_pWnd)->OnClose();
	}

}

void MyAsyncSocket::OnReceive(int iErrorCode)
{
//	AfxMessageBox("void CMyAsyncSocket::OnReceive(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMFCAsyncPhoneServerDlg*)m_pWnd)->OnReceive();
	}

}

void MyAsyncSocket::OnSend(int iErrorCode)
{
//	AfxMessageBox("void CMyAsyncSocket::OnSend(int iErrorCode)");
	if (iErrorCode == 0)
	{
		((CMFCAsyncPhoneServerDlg*)m_pWnd)->OnSend();
	}

}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(MyAsyncSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(MyAsyncSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// MyAsyncSocket member functions

// eof MyAsyncSocket