; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImageProcessingView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ImageProcessing.h"
LastPage=0

ClassCount=10
Class1=CImageProcessingApp
Class2=CImageProcessingDoc
Class3=CImageProcessingView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_DIALOG_XZ
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CImageCYDlg
Resource3=IDD_DIALOG_PY
Class7=CImageZFTDlg
Resource4=IDR_MAINFRAME
Class8=CImagePYDlg
Resource5=IDD_DIALOG_CY
Class9=CImageXZDlg
Resource6=IDD_DIALOG_ZFT
Class10=CImageSFDlg
Resource7=IDD_DIALOG_SF

[CLS:CImageProcessingApp]
Type=0
HeaderFile=ImageProcessing.h
ImplementationFile=ImageProcessing.cpp
Filter=N

[CLS:CImageProcessingDoc]
Type=0
HeaderFile=ImageProcessingDoc.h
ImplementationFile=ImageProcessingDoc.cpp
Filter=N

[CLS:CImageProcessingView]
Type=0
HeaderFile=ImageProcessingView.h
ImplementationFile=ImageProcessingView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_RH_GTMB


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ImageProcessing.cpp
ImplementationFile=ImageProcessing.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_APP_EXIT
Command5=ID_SHOW_TWO
Command6=ID_SHOW_HD
Command7=ID_LH_2
Command8=ID_LH_4
Command9=ID_LH_8
Command10=ID_LH_16
Command11=ID_LH_32
Command12=ID_LH_64
Command13=ID_CY
Command14=ID_ZFT_YT
Command15=ID_DYS_XXYD
Command16=ID_DYS_XXZQ
Command17=ID_DYS_XXJX
Command18=ID_DYS_XXQB
Command19=ID_DYS_FXXPF
Command20=ID_DYS_FXXHS
Command21=ID_DYS_YZBH
Command22=ID_DYS_JHH
Command23=ID_JHBH_PY
Command24=ID_JHBH_FZ
Command25=ID_JHBH_DZ
Command26=ID_JHBH_TXXZ
Command27=ID_JHBH_ZXXZ
Command28=ID_JHBH_SF
Command29=ID_TXZQ_PTPH1
Command30=ID_TXZQ_PTPH2
Command31=ID_TXZQ_GSPH
Command32=ID_TXZQ_ZZLB
Command33=ID_RH_Laplacian
Command34=ID_RH_Sobel
Command35=ID_RH_Prewitt
Command36=ID_RH_Isotropic
Command37=ID_RH_GTMB
CommandCount=37

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
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

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
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG_CY]
Type=1
Class=CImageCYDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_CYX,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_CYY,edit,1350631552

[CLS:CImageCYDlg]
Type=0
HeaderFile=ImageCYDlg.h
ImplementationFile=ImageCYDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CImageCYDlg

[DLG:IDD_DIALOG_ZFT]
Type=1
Class=CImageZFTDlg
ControlCount=45
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_RGB,button,1342177287
Control3=IDC_STATIC,static,1342177296
Control4=IDC_STATIC,static,1342177296
Control5=IDC_STATIC,static,1342177296
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC_XS_RED,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC_PJHD_RED,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC_ZZHD_RED,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC_BZC_RED,static,1342308352
Control17=IDC_STATIC,static,1342177296
Control18=IDC_STATIC,static,1342177296
Control19=IDC_STATIC,static,1342177296
Control20=IDC_STATIC,static,1342177297
Control21=IDC_STATIC,static,1342177297
Control22=IDC_STATIC,static,1342177297
Control23=IDC_STATIC,static,1342177297
Control24=IDC_STATIC,static,1342177297
Control25=IDC_STATIC,static,1342177297
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC_XS_GREEN,static,1342308352
Control29=IDC_STATIC_PJHD_GREEN,static,1342308352
Control30=IDC_STATIC_ZZHD_GREEN,static,1342308352
Control31=IDC_STATIC_BZC_GREEN,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC_XS_BLUE,static,1342308352
Control35=IDC_STATIC_PJHD_BLUE,static,1342308352
Control36=IDC_STATIC_ZZHD_BLUE,static,1342308352
Control37=IDC_STATIC_BZC_BLUE,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC_KJ,static,1342177298
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352

[CLS:CImageZFTDlg]
Type=0
HeaderFile=ImageZFTDlg.h
ImplementationFile=ImageZFTDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CImageZFTDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_PY]
Type=1
Class=CImagePYDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_PYX,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_PYY,edit,1350631552

[CLS:CImagePYDlg]
Type=0
HeaderFile=ImagePYDlg.h
ImplementationFile=ImagePYDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_EDIT_PASTE
VirtualFilter=dWC

[DLG:IDD_DIALOG_XZ]
Type=1
Class=CImageXZDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_XZ,edit,1350631552
Control3=IDC_STATIC,static,1342308352

[CLS:CImageXZDlg]
Type=0
HeaderFile=ImageXZDlg.h
ImplementationFile=ImageXZDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_XZ

[DLG:IDD_DIALOG_SF]
Type=1
Class=CImageSFDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_SF,edit,1350631552
Control3=IDC_STATIC,static,1342308352

[CLS:CImageSFDlg]
Type=0
HeaderFile=ImageSFDlg.h
ImplementationFile=ImageSFDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_SF

