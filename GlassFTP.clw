; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGlassFTPDlg
LastTemplate=CComboBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "glassftp.h"
LastPage=0

ClassCount=10
Class1=CFileListCtrl
Class2=CForderName
Class3=CGlassFTPApp
Class4=CAboutDlg
Class5=CGlassFTPDlg
Class6=COpenDlg
Class7=COptionDlg
Class8=CServerSetting

ResourceCount=7
Resource1=IDD_MESSAGEBOX
Resource2=IDD_FORDERNAME
Resource3=IDD_GLASSFTP_DIALOG
Resource4=IDD_ABOUTBOX
Resource5=IDD_SERVER
Resource6=IDD_OPTION
Class9=CMessageDlg
Class10=CComboServerPath
Resource7=IDR_MAINMENU

[CLS:CFileListCtrl]
Type=0
BaseClass=CListCtrl
HeaderFile=FileListCtrl.h
ImplementationFile=FileListCtrl.cpp
Filter=W
VirtualFilter=FWC
LastObject=CFileListCtrl

[CLS:CForderName]
Type=0
BaseClass=CDialog
HeaderFile=ForderName.h
ImplementationFile=ForderName.cpp
LastObject=CForderName

[CLS:CGlassFTPApp]
Type=0
BaseClass=CWinApp
HeaderFile=GlassFTP.h
ImplementationFile=GlassFTP.cpp
LastObject=CGlassFTPApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=GlassFTPDlg.cpp
ImplementationFile=GlassFTPDlg.cpp
LastObject=IDM_EDITING

[CLS:CGlassFTPDlg]
Type=0
BaseClass=CDialog
HeaderFile=GlassFTPDlg.h
ImplementationFile=GlassFTPDlg.cpp
LastObject=IDM_RENAME
Filter=W
VirtualFilter=dWC

[CLS:COpenDlg]
Type=0
BaseClass=CDialog
HeaderFile=OpenDlg.h
ImplementationFile=OpenDlg.cpp
LastObject=COpenDlg

[CLS:COptionDlg]
Type=0
BaseClass=CDialog
HeaderFile=OptionDlg.h
ImplementationFile=OptionDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=COptionDlg

[CLS:CServerSetting]
Type=0
BaseClass=CDialog
HeaderFile=ServerSetting.h
ImplementationFile=ServerSetting.cpp
LastObject=CServerSetting
Filter=D
VirtualFilter=dWC

[DLG:IDD_FORDERNAME]
Type=1
Class=CForderName
ControlCount=3
Control1=IDC_EDIT_FORDERNAME,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353

[DLG:IDD_GLASSFTP_DIALOG]
Type=1
Class=CGlassFTPDlg
ControlCount=30
Control1=IDC_RADIO_FILE_TRANS_ASC,button,1342312457
Control2=IDC_RADIO_FILE_TRANS_BIN,button,1342181385
Control3=IDC_BTN_PUT,button,1342242880
Control4=IDC_RADIO_FILE_TRANS_AUTO,button,1342181385
Control5=IDC_BTN_GET,button,1342242880
Control6=IDC_BTN_CLIENT_NEWFORDER,button,1342242880
Control7=IDC_BTN_CLIENT_DELETE,button,1342242880
Control8=IDC_BTN_CLIENT_REFRESH,button,1342242880
Control9=IDC_BTN_SERVER_NEWFORDER,button,1342242880
Control10=IDC_BTN_SERVER_DELETE,button,1342242880
Control11=IDC_BTN_SERVER_REFRESH,button,1342242880
Control12=IDC_COMBO_SERVER,combobox,1344340226
Control13=IDC_BTN_SERVER_CLOSE,button,1342242880
Control14=IDC_COMBO_SERVER_PATH,combobox,1344340034
Control15=IDC_BTN_SERVER_PARENT,button,1342242880
Control16=IDC_CHECK_CURRENT_SERVER,button,1342242819
Control17=IDC_BTN_LOG_CLEAR,button,1342275584
Control18=IDC_EDIT_LOG,edit,1344344260
Control19=IDC_STATIC,button,1342177287
Control20=IDC_LIST_CLIENT,SysListView32,1350631937
Control21=IDC_EDIT_CLIENT_PATH,edit,1342247044
Control22=IDC_BTN_SHBF,button,1342275648
Control23=IDC_LIST_SERVER,SysListView32,1350631425
Control24=IDC_BTN_CLIENT_PARENT,button,1342242880
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,static,1342308352
Control27=IDC_PROGRESS_FTP,msctls_progress32,1350565888
Control28=IDC_STATIC_STATUS,static,1342312449
Control29=IDC_STATIC_STATUS_BACKUP,static,1342312449
Control30=IDC_STATIC_TIMER,static,1342312448

[DLG:IDD_OPEN]
Type=1
Class=COpenDlg

[DLG:IDD_OPTION]
Type=1
Class=COptionDlg
ControlCount=22
Control1=IDOK,button,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_FILEPATH,edit,1350631552
Control4=IDC_BTN_FILEDLG,button,1342242816
Control5=IDC_BTN_SAVE,button,1342242816
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_INTERVAL,edit,1350639744
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_RADIO_SERVERFILECOUNT,button,1342308361
Control12=IDC_RADIO_SERVERFILECOUNT2,button,1342177289
Control13=IDC_EDIT_FILECOUNT,edit,1350639744
Control14=IDC_RADIO_BACKUP1,button,1342308361
Control15=IDC_RADIO_BACKUP2,button,1342177289
Control16=IDC_EDIT_BACKUP,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_AUTOEXT,edit,1352732676
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_FILEPATH_CONFIG,edit,1350631552
Control22=IDC_BTN_FILEDLG_CONFIG,button,1342242816

[DLG:IDD_SERVER]
Type=1
Class=CServerSetting
ControlCount=24
Control1=IDC_LIST_SERVER,listbox,1353777409
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_NAME,edit,1350631552
Control9=IDC_EDIT_IP,edit,1350631552
Control10=IDC_EDIT_ID,edit,1350631552
Control11=IDC_EDIT_PASSWORD,edit,1350631584
Control12=IDC_EDIT_DEFAULT_PATH,edit,1350631552
Control13=IDC_BTN_OPEN,button,1342242817
Control14=IDC_BTN_EXIT,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_BTN_SAVE,button,1342242816
Control17=IDC_BTN_NEW,button,1342242816
Control18=IDC_BTN_DELETE,button,1342242816
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_PORT,edit,1350631552
Control22=IDC_CHECK_SELECT_CLIENTPATH,button,1342242819
Control23=IDC_EDIT_DEFAULT_PATH_CLIENT,edit,1350631552
Control24=IDC_BTN_SELECT_CLIENT_PATH,button,1342242816

[MNU:IDR_MAINMENU]
Type=1
Class=CGlassFTPDlg
Command1=IDM_OPEN
Command2=IDM_CLOSEALL
Command3=IDM_EXIT
Command4=IDM_RENAME
Command5=IDM_EDITING
Command6=IDM_EXECUTE
Command7=IDM_OPTION
Command8=IDM_SET_DEFAULT_PATH
Command9=IDM_ABOUT
CommandCount=9

[DLG:IDD_MESSAGEBOX]
Type=1
Class=CMessageDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_MSG,static,1342308353
Control4=IDOKALL,button,1342242816

[CLS:CMessageDlg]
Type=0
HeaderFile=MessageDlg.h
ImplementationFile=MessageDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CMessageDlg
VirtualFilter=dWC

[CLS:CComboServerPath]
Type=0
HeaderFile=ComboServerPath.h
ImplementationFile=ComboServerPath.cpp
BaseClass=CComboBox
Filter=D
LastObject=CComboServerPath
VirtualFilter=cWC

