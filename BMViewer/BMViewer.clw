; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBMView
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "BMViewer.h"
LastPage=0

ClassCount=10
Class1=CBMApp
Class2=CBMDoc
Class3=CBMView
Class4=CMainFrame

ResourceCount=9
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_BMVIEWTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_HIST
Resource5=IDD_DENOISE
Resource6=IDD_BRIGHT_CONT
Class7=CHistDlg
Resource7=IDD_ABOUTBOX (English (U.S.))
Class8=CBrightContDlg
Resource8=IDR_BMVIEWTYPE (English (U.S.))
Class9=CDeNoiseDlg
Class10=CHistView
Resource9=IDR_MAINFRAME (English (U.S.))

[CLS:CBMApp]
Type=0
HeaderFile=BMViewer.h
ImplementationFile=BMViewer.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=ID_FILE_NEW

[CLS:CBMDoc]
Type=0
HeaderFile=BMDoc.h
ImplementationFile=BMDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=ID_EDIT_HISTOGRAM

[CLS:CBMView]
Type=0
HeaderFile=BMView.h
ImplementationFile=BMView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CBMView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=BMViewer.cpp
ImplementationFile=BMViewer.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
CommandCount=8
Command8=ID_APP_ABOUT

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_BMVIEWTYPE]
Type=1
Class=CBMView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
CommandCount=21
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT

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


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_EDIT_STOP
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_BMVIEWTYPE (English (U.S.))]
Type=1
Class=CBMView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_STOP
Command13=ID_EDIT_HALF
Command14=ID_EDIT_HISTOGRAM
Command15=ID_EDIT_BRIGHTNESSANDCONTRAST
Command16=ID_EDIT_INVERTCOLORS
Command17=ID_EDIT_EMBOSS
Command18=ID_EDIT_BLUR
Command19=ID_EDIT_CONTOUR
Command20=ID_EDIT_SHARP
Command21=ID_EDIT_DENOISE
Command22=ID_VIEW_TOOLBAR
Command23=ID_VIEW_STATUS_BAR
Command24=ID_VIEW_ZOOMIN
Command25=ID_VIEW_ZOOMOUT
Command26=ID_VIEW_STRETCHHALFTONE
Command27=ID_VIEW_STRETCHCOLORONCOLOR
Command28=ID_WINDOW_NEW
Command29=ID_WINDOW_CASCADE
Command30=ID_WINDOW_TILE_HORZ
Command31=ID_WINDOW_ARRANGE
Command32=ID_APP_ABOUT
CommandCount=32

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_EDIT_BRIGHTNESSANDCONTRAST
Command2=ID_EDIT_COPY
Command3=ID_VIEW_STRETCHCOLORONCOLOR
Command4=ID_EDIT_EMBOSS
Command5=ID_EDIT_HISTOGRAM
Command6=ID_VIEW_STRETCHHALFTONE
Command7=ID_EDIT_INVERTCOLORS
Command8=ID_FILE_NEW
Command9=ID_FILE_OPEN
Command10=ID_FILE_PRINT
Command11=ID_FILE_SAVE
Command12=ID_EDIT_PASTE
Command13=ID_VIEW_ZOOMIN
Command14=ID_EDIT_UNDO
Command15=ID_EDIT_CUT
Command16=ID_EDIT_STOP
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
Command19=ID_EDIT_COPY
Command20=ID_EDIT_PASTE
Command21=ID_VIEW_ZOOMOUT
Command22=ID_EDIT_CUT
Command23=ID_EDIT_UNDO
CommandCount=23

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_HIST]
Type=1
Class=CHistDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDC_HIST_VIEW,static,1342177287
Control3=IDCANCEL,button,1342242816
Control4=IDC_SLIDER_HIST_B,msctls_trackbar32,1342242820
Control5=IDC_SLIDER_HIST_T,msctls_trackbar32,1342242820
Control6=IDC_OFFSET_B_TXT,static,1342308352
Control7=IDC_OFFSET_T_TXT,static,1342308352

[CLS:CHistDlg]
Type=0
HeaderFile=HistDlg.h
ImplementationFile=HistDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CHistDlg
VirtualFilter=dWC

[DLG:IDD_BRIGHT_CONT]
Type=1
Class=CBrightContDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SLIDER_BRIGHTNESS,msctls_trackbar32,1342242820
Control4=IDC_STATIC_BRIGHTNESS,static,1342308352
Control5=IDC_SLIDER_CONTRAST,msctls_trackbar32,1342242820
Control6=IDC_STATIC_CONTRAST,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[CLS:CBrightContDlg]
Type=0
HeaderFile=BrightContDlg.h
ImplementationFile=BrightContDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CBrightContDlg

[DLG:IDD_DENOISE]
Type=1
Class=CDeNoiseDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NOISE_SMOOTH,button,1342308361
Control4=IDC_NOISE_SHOW,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDC_K,edit,1350631552
Control7=IDC_SPIN_K,msctls_updown32,1342177328
Control8=IDC_STATIC,static,1342308352

[CLS:CDeNoiseDlg]
Type=0
HeaderFile=DeNoiseDlg.h
ImplementationFile=DeNoiseDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDeNoiseDlg

[CLS:CHistView]
Type=0
HeaderFile=HistView.h
ImplementationFile=HistView.cpp
BaseClass=CStatic
Filter=W
LastObject=CHistView
VirtualFilter=WC

