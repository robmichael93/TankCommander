; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyOpenGLView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OpenGL.h"
LastPage=0

ClassCount=12
Class1=COpenGLApp
Class2=COpenGLDoc
Class3=COpenGLView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMyOpenGLView
Resource2=IDD_ROTATION_DIALOG
Class7=CRotationDialog
Resource3=IDD_CONSOLE
Class8=CConsoleDialog
Class9=CMySocket
Class10=CMultiPlayerDialog
Class11=CSinglePlayerDialog
Resource4=IDR_MAINFRAME
Class12=CJoinDialog
Resource5=IDD_JOIN_DIALOG

[CLS:COpenGLApp]
Type=0
HeaderFile=OpenGL.h
ImplementationFile=OpenGL.cpp
Filter=N

[CLS:COpenGLDoc]
Type=0
HeaderFile=OpenGLDoc.h
ImplementationFile=OpenGLDoc.cpp
Filter=N

[CLS:COpenGLView]
Type=0
HeaderFile=OpenGLView.h
ImplementationFile=OpenGLView.cpp
Filter=C
LastObject=ID_TOGGLE_LIGHT1
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=OpenGL.cpp
ImplementationFile=OpenGL.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_SINGLE
Command2=ID_MULTI
Command3=ID_QUIT
Command4=ID_HOST
Command5=ID_JOIN
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[CLS:CMyOpenGLView]
Type=0
HeaderFile=MyOpenGLView.h
ImplementationFile=MyOpenGLView.cpp
BaseClass=COpenGLView
Filter=C
LastObject=ID_QUIT
VirtualFilter=VWC

[DLG:IDD_ROTATION_DIALOG]
Type=1
Class=CRotationDialog
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_ANGLE1,edit,1350631552
Control4=IDC_EDIT_ANGLE2,edit,1350631552
Control5=IDC_EDIT_ANGLE3,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CRotationDialog]
Type=0
HeaderFile=RotationDialog.h
ImplementationFile=RotationDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CRotationDialog
VirtualFilter=dWC

[DLG:IDD_CONSOLE]
Type=1
Class=CConsoleDialog
ControlCount=1
Control1=IDC_CONSOLE,edit,1352730820

[CLS:CConsoleDialog]
Type=0
HeaderFile=ConsoleDialog.h
ImplementationFile=ConsoleDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CConsoleDialog

[CLS:CMySocket]
Type=0
HeaderFile=mysocket.h
ImplementationFile=mysocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CMySocket

[CLS:CMultiPlayerDialog]
Type=0
HeaderFile=MultiPlayerDialog.h
ImplementationFile=MultiPlayerDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CMultiPlayerDialog

[CLS:CSinglePlayerDialog]
Type=0
HeaderFile=SinglePlayerDialog.h
ImplementationFile=SinglePlayerDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CSinglePlayerDialog
VirtualFilter=dWC

[DLG:IDD_JOIN_DIALOG]
Type=1
Class=CJoinDialog
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=ID_IPADD,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:CJoinDialog]
Type=0
HeaderFile=JoinDialog.h
ImplementationFile=JoinDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CJoinDialog

