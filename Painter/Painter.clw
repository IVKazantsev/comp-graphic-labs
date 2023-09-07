; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPainterView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Painter.h"
LastPage=0

ClassCount=6
Class1=CPainterApp
Class2=CPainterDoc
Class3=CPainterView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME (English (U.S.))
Class5=CAboutDlg
Resource3=IDD_IMAGES
Class6=CPagePropertyDlg
Resource4=IDD_PAGE_PROPERTY
Resource5=IDR_MAINFRAME

[CLS:CPainterApp]
Type=0
HeaderFile=Painter.h
ImplementationFile=Painter.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CPainterApp

[CLS:CPainterDoc]
Type=0
HeaderFile=PainterDoc.h
ImplementationFile=PainterDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPainterDoc

[CLS:CPainterView]
Type=0
HeaderFile=PainterView.h
ImplementationFile=PainterView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CPainterView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDC_STATIC_PIC
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Painter.cpp
ImplementationFile=Painter.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC_ICON,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_SAVE_BMP
Command6=ID_FILE_PAGEPROPERTY
Command7=ID_FILE_PRINT
Command8=ID_FILE_PRINT_PREVIEW
Command9=ID_FILE_PRINT_SETUP
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_DELETE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_COPY
Command16=ID_EDIT_PASTE
Command17=ID_EDIT_ADDSHAPE_POINT
Command18=ID_EDIT_ADDSHAPE_CIRCLE
Command19=ID_EDIT_ADDSHAPE_SQUARE
Command20=ID_EDIT_ADDSHAPE_POLYLINE
Command21=ID_EDIT_ADDSHAPE_POLYGON
Command22=ID_EDIT_ADDSHAPE_SURFACE
Command23=ID_EDIT_CHANGEORDER_TOP
Command24=ID_EDIT_CHANGEORDER_BOTTOM
Command25=ID_EDIT_CHANGEORDER_STEPUP
Command26=ID_EDIT_CHANGEORDER_STEPDOWN
Command27=ID_EDIT_SELECT
Command28=ID_VIEW_TOOLBAR
Command29=ID_VIEW_STATUS_BAR
Command30=ID_APP_ABOUT
CommandCount=30

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_FILE_PAGEPROPERTY
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_DELETE
Command10=ID_EDIT_CUT
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_EDIT_SELECT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_EDIT_ADDSHAPE_CIRCLE
Command9=ID_EDIT_ADDSHAPE_SQUARE
Command10=ID_EDIT_ADDSHAPE_POLYGON
Command11=ID_EDIT_ADDSHAPE_SURFACE
Command12=ID_APP_ABOUT
CommandCount=12

[DLG:IDD_PAGE_PROPERTY]
Type=1
Class=CPagePropertyDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_WIDTH,edit,1350631552
Control4=IDC_SPIN_WIDTH,msctls_updown32,1342177330
Control5=IDC_EDIT_HEIGHT,edit,1350631552
Control6=IDC_SPIN_HEIGHT,msctls_updown32,1342177330
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CPagePropertyDlg]
Type=0
HeaderFile=PagePropertyDlg.h
ImplementationFile=PagePropertyDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPagePropertyDlg

[DLG:IDD_IMAGES]
Type=1
Class=?
ControlCount=1
Control1=IDC_IMAGE_LIST,SysListView32,1350666240

