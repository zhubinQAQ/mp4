; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVrDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "vr.h"
LastPage=0

ClassCount=7
Class1=CAbout
Class2=Begain
Class3=CVrApp
Class4=CVrDlg

ResourceCount=7
Resource1=IDD_ABOUT
Resource2=IDR_MENU
Resource3=IDD_DATA
Resource4=IDD_DIALOG1
Class5=CSettdcs
Resource5=IDD_VR_DIALOG
Class6=CData
Resource6=IDD_SETDA
Class7=CHelp
Resource7=IDR_TOOLBAR (English (U.S.))

[CLS:CAbout]
Type=0
BaseClass=CDialog
HeaderFile=About.h
ImplementationFile=About.cpp

[CLS:Begain]
Type=0
BaseClass=CDialog
HeaderFile=Begain.h
ImplementationFile=Begain.cpp
LastObject=Begain

[CLS:CVrApp]
Type=0
BaseClass=CWinApp
HeaderFile=vr.h
ImplementationFile=vr.cpp

[CLS:CVrDlg]
Type=0
BaseClass=CDialog
HeaderFile=vrDlg.h
ImplementationFile=vrDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_SLIDER

[DLG:IDD_ABOUT]
Type=1
Class=CAbout
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BMP,static,1342177294

[DLG:IDD_BEGAIN]
Type=1
Class=Begain

[DLG:IDD_VR_DIALOG]
Type=1
Class=CVrDlg
ControlCount=80
Control1=IDC_RADIO0,button,1342242825
Control2=IDC_RADIO1,button,1342242825
Control3=IDC_RADIO2,button,1342242825
Control4=IDC_RADIO3,button,1342242825
Control5=IDC_COMBO,combobox,1344342019
Control6=IDC_BX,static,1476395015
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_CHECK0,button,1342373891
Control10=IDC_CHECK1,button,1342373891
Control11=IDC_CHECK2,button,1342373891
Control12=IDC_CHECK3,button,1342373891
Control13=IDC_CHECK4,button,1342373891
Control14=IDC_CHECK5,button,1342373891
Control15=IDC_CHECK6,button,1342373891
Control16=IDC_CHECK7,button,1342373891
Control17=IDC_CHECK8,button,1342373891
Control18=IDC_CHECK9,button,1342373891
Control19=IDC_CHECK10,button,1342373891
Control20=IDC_CHECK11,button,1342373891
Control21=IDC_CHECK12,button,1342373891
Control22=IDC_CHECK13,button,1342373891
Control23=IDC_CHECK14,button,1342373891
Control24=IDC_CHECK15,button,1342373891
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,button,1342308359
Control27=IDC_BX2,static,1476395015
Control28=IDC_STATIC,button,1342177287
Control29=IDC_STATIC,button,1342177287
Control30=IDC_STATIC0,static,1342177287
Control31=IDC_STATIC,static,1342308866
Control32=IDC_STATIC1,static,1342177287
Control33=IDC_STATIC,static,1342308866
Control34=IDC_STATIC2,static,1342177287
Control35=IDC_STATIC,static,1342308866
Control36=IDC_STATIC3,static,1342177287
Control37=IDC_STATIC,static,1342308866
Control38=IDC_STATIC4,static,1342177287
Control39=IDC_STATIC,static,1342308866
Control40=IDC_STATIC5,static,1342177287
Control41=IDC_STATIC,static,1342308866
Control42=IDC_STATIC6,static,1342177287
Control43=IDC_STATIC,static,1342308866
Control44=IDC_STATIC7,static,1342177287
Control45=IDC_STATIC,static,1342308866
Control46=IDC_STATIC8,static,1342177287
Control47=IDC_STATIC,static,1342308866
Control48=IDC_STATIC9,static,1342177287
Control49=IDC_STATIC,static,1342308866
Control50=IDC_STATIC10,static,1342177287
Control51=IDC_STATIC,static,1342308866
Control52=IDC_STATIC11,static,1342177287
Control53=IDC_STATIC,static,1342308866
Control54=IDC_STATIC12,static,1342177287
Control55=IDC_STATIC,static,1342308866
Control56=IDC_STATIC13,static,1342177287
Control57=IDC_STATIC,static,1342308866
Control58=IDC_STATIC14,static,1342177287
Control59=IDC_STATIC,static,1342308866
Control60=IDC_STATIC15,static,1342177287
Control61=IDC_STATIC,static,1342308866
Control62=IDC_STATIC,static,1342308354
Control63=IDC_SLIDER,msctls_trackbar32,1342177304
Control64=IDC_STATIC,static,1342308354
Control65=IDC_ABC,static,1342308352
Control66=IDC_STATIC,static,1342308354
Control67=IDC_TIMES,edit,1350639744
Control68=IDC_STATIC,static,1342308352
Control69=IDC_STATIC,static,1342308352
Control70=IDC_MIN,edit,1350639744
Control71=IDC_STATIC,static,1342308352
Control72=IDC_MAX,edit,1350639744
Control73=IDC_EDIT1,edit,1350633600
Control74=IDC_STATIC,static,1342308354
Control75=IDC_STATIC,static,1342308354
Control76=IDC_STATIC,static,1342308352
Control77=IDC_FACTTIMES,static,1342308352
Control78=IDC_RATFORHARDWARE,edit,1350633600
Control79=IDC_STATIC,static,1342308354
Control80=IDC_SCROLLBAR1,scrollbar,1342177280

[MNU:IDR_MENU]
Type=1
Class=CVrDlg
Command1=ID_OPENDATA
Command2=ID_SAVEDATA
Command3=ID_EXIT
Command4=ID_USE
Command5=IDM_AUOUT
CommandCount=5

[TB:IDR_TOOLBAR (English (U.S.))]
Type=1
Class=CVrDlg
Command1=ID_OPENDATA
Command2=ID_SAVEDATA
Command3=ID_ANALYSEFILE
Command4=ID_SETDAMOUDL
Command5=ID_RUN
Command6=ID_BEGAINFFT
Command7=ID_RATEFORHARDWARE
Command8=ID_DATA
Command9=ID_SAVEBMP
CommandCount=9

[CLS:CSettdcs]
Type=0
HeaderFile=Settdcs.h
ImplementationFile=Settdcs.cpp
BaseClass=CDialog
Filter=D
LastObject=CSettdcs
VirtualFilter=dWC

[DLG:IDD_SETDA]
Type=1
Class=CSettdcs
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO1,button,1342177289
Control3=IDC_RADIO3,button,1342177289
Control4=IDC_RADIO4,button,1342177289
Control5=IDOK,button,1342242817
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308875
Control8=IDC_PINLV,edit,1350631552
Control9=IDC_STATIC,static,1342308875
Control10=IDC_ZHANKONGBI,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308354
Control13=IDC_MAX,edit,1350631552
Control14=IDC_STATIC,static,1342308354
Control15=IDC_MIN,edit,1350631552

[DLG:IDD_DATA]
Type=1
Class=CData
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:CData]
Type=0
HeaderFile=Data.h
ImplementationFile=Data.cpp
BaseClass=CDialog
Filter=D
LastObject=CData
VirtualFilter=dWC

[DLG:IDD_DIALOG1]
Type=1
Class=CHelp
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_STATIC1,static,1342308352

[CLS:CHelp]
Type=0
HeaderFile=Help.h
ImplementationFile=Help.cpp
BaseClass=CDialog
Filter=D
LastObject=CHelp
VirtualFilter=dWC

