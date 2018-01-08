// GlassFTPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GlassFTP.h"
#include "GlassFTPDlg.h"

#include "ForderName.h"
#include "ServerSetting.h"
#include "OptionDlg.h"
#include "MessageDlg.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlassFTPDlg dialog

CGlassFTPDlg::CGlassFTPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGlassFTPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGlassFTPDlg)
	m_nTransType = 2;
	m_bCurrentServer = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAIN_ICON);

	m_pFtp = NULL;
	m_bIDOKALL = FALSE;

	m_comboServerPath.SetParent(this);
	m_editClientPath.SetParent(this);

	m_Progress.SetRange32(0, 0);

	m_logFile.open("GlassFTP.log", std::ofstream::out | std::ofstream::app);
}

void CGlassFTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	

	//{{AFX_DATA_MAP(CGlassFTPDlg)
	DDX_Control(pDX, IDC_PROGRESS_FTP, m_Progress);
	DDX_Control(pDX, IDC_COMBO_SERVER_PATH, m_comboServerPath);
	DDX_Control(pDX, IDC_COMBO_SERVER, m_comboServer);
	DDX_Control(pDX, IDC_LIST_SERVER, m_listServer);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_listClient);
	DDX_Radio(pDX, IDC_RADIO_FILE_TRANS_ASC, m_nTransType);
	DDX_Check(pDX, IDC_CHECK_CURRENT_SERVER, m_bCurrentServer);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_CLIENT_PATH, m_editClientPath);
}

BEGIN_MESSAGE_MAP(CGlassFTPDlg, CDialog)
	//{{AFX_MSG_MAP(CGlassFTPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CLIENT, OnDblclkListClient)
	ON_BN_CLICKED(IDC_BTN_SHBF, OnBtnShbf)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SERVER, OnDblclkListServer)
	ON_BN_CLICKED(IDC_BTN_CLIENT_PARENT, OnBtnClientParent)
	ON_BN_CLICKED(IDC_BTN_SERVER_PARENT, OnBtnServerParent)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_PUT, OnBtnPut)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_SERVER, OnKeydownListServer)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_CLIENT, OnKeydownListClient)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER, OnSelchangeComboServer)
	ON_COMMAND(IDM_CLOSEALL, OnCloseall)
	ON_BN_CLICKED(IDC_BTN_SERVER_CLOSE, OnBtnServerClose)
	ON_BN_CLICKED(IDC_BTN_SERVER_NEWFORDER, OnBtnServerNewforder)
	ON_BN_CLICKED(IDC_BTN_CLIENT_NEWFORDER, OnBtnClientNewforder)
	ON_BN_CLICKED(IDC_BTN_SERVER_DELETE, OnBtnServerDelete)
	ON_BN_CLICKED(IDC_BTN_CLIENT_DELETE, OnBtnClientDelete)
	ON_COMMAND(IDOK, OnOk)
	ON_BN_CLICKED(IDC_BTN_SERVER_REFRESH, OnBtnServerRefresh)
	ON_BN_CLICKED(IDC_BTN_CLIENT_REFRESH, OnBtnClientRefresh)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CLIENT, OnRclickListClient)
	ON_COMMAND(IDM_EDITING, OnEditing)
	ON_COMMAND(IDM_OPTION, OnOption)
	ON_COMMAND(IDM_SET_DEFAULT_PATH, OnSetDefaultPath)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_SERVER_PATH, OnSelchangeComboServerPath)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_LOG_CLEAR, OnBtnLogClear)
	ON_BN_CLICKED(IDC_CHECK_CURRENT_SERVER, OnCheckCurrentServer)
	ON_COMMAND(IDM_EXECUTE, OnExecute)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_CLIENT, OnEndlabeleditListClient)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_CLIENT, OnBeginlabeleditListClient)
	ON_COMMAND(IDM_RENAME, OnRename)
	ON_COMMAND(IDM_CLOSE, OnClose)
	ON_WM_MENUSELECT()
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDC_BTN_CLIENT_PATH, &CGlassFTPDlg::OnBnClickedBtnClientPath)
//	ON_EN_CHANGE(IDC_EDIT_CLIENT_PATH, &CGlassFTPDlg::OnEnChangeEditClientPath)
ON_COMMAND(IDM_FILEVIEW_SERVER, &CGlassFTPDlg::OnFileviewServer)
ON_NOTIFY(NM_RCLICK, IDC_LIST_SERVER, &CGlassFTPDlg::OnNMRclickListServer)
ON_COMMAND(IDM_DIFF_SERVER, &CGlassFTPDlg::OnDiffServer)
ON_COMMAND(IDM_DIFF_CLIENT, &CGlassFTPDlg::OnDiffClient)
ON_COMMAND(IDM_EXECUTE_SERVER, &CGlassFTPDlg::OnExecuteServer)
//ON_NOTIFY(HDN_ITEMCHANGED, 0, &CGlassFTPDlg::OnHdnItemchangedListClient)
ON_NOTIFY(NM_CLICK, IDC_LIST_CLIENT, &CGlassFTPDlg::OnNMClickListClient)
ON_NOTIFY(NM_CLICK, IDC_LIST_SERVER, &CGlassFTPDlg::OnNMClickListServer)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlassFTPDlg message handlers


BOOL CGlassFTPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon



	//////////////////////////////////////////////////////////////////
	// Custom Code 
	m_pFtp = NULL;								// m_pFtp 초기화 
	
	m_listClient.InitFileList(TRUE);			// m_listClient 초기화 
	m_listServer.InitFileList(FALSE);			// m_listServer 초기화 

	SetClientFiles(GetClientDefaultPath());
	OnInitToolTip();

	m_nTransType = GetTransMode();
	m_AutoList.Reset(GetAutoTranListString());

	UpdateData(FALSE);

	SetStatus();

	SetTimer(ID_TIMER2, TIMER2_INTERVAL, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGlassFTPDlg::OnInitToolTip()
{
	m_ToolTip.Create(this);

	CImageList imgList;
	imgList.Create(16, 16, TRUE,  0, 0);

	imgList.Add(AfxGetApp()->LoadIcon(IDI_SHBF_ICON));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_PARENT_ICON));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_PUT_ICON));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_GET_ICON));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_NEWFORDER_ICON));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_DELETE_ICON));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_REFRESH));

	// Button Control Set Icon
	CButton *pButton = (CButton *)GetDlgItem(IDC_BTN_SHBF);
	pButton->SetIcon(imgList.ExtractIcon(0));
	m_ToolTip.AddTool(pButton, _T("파일 브라우저를 보여줍니다."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_PARENT);
	pButton->SetIcon(imgList.ExtractIcon(1));
	m_ToolTip.AddTool(pButton, _T("상위 디렉토리 이동"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_PARENT);
	pButton->SetIcon(imgList.ExtractIcon(1));
	m_ToolTip.AddTool(pButton, _T("상위 디렉토리 이동"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_PUT);
	pButton->SetIcon(imgList.ExtractIcon(2));
	m_ToolTip.AddTool(pButton, _T("파일 보내기"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_GET);
	pButton->SetIcon(imgList.ExtractIcon(3));
	m_ToolTip.AddTool(pButton, _T("파일 받기"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_NEWFORDER);
	pButton->SetIcon(imgList.ExtractIcon(4));
	m_ToolTip.AddTool(pButton, _T("새 폴더 만들기"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_NEWFORDER);
	pButton->SetIcon(imgList.ExtractIcon(4));
	m_ToolTip.AddTool(pButton, _T("새 폴더 만들기"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_DELETE);
	pButton->SetIcon(imgList.ExtractIcon(5));
	m_ToolTip.AddTool(pButton, _T("선택한 파일을 지웁니다."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_DELETE);
	pButton->SetIcon(imgList.ExtractIcon(5));
	m_ToolTip.AddTool(pButton, _T("선택한 파일을 지웁니다."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_CLOSE);
	pButton->SetIcon(imgList.ExtractIcon(5));
	m_ToolTip.AddTool(pButton, _T("연결을 끊습니다."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_REFRESH);
	pButton->SetIcon(imgList.ExtractIcon(6));
	m_ToolTip.AddTool(pButton, _T("현제 디렉토리를 새로고침"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_REFRESH);
	pButton->SetIcon(imgList.ExtractIcon(6));
	m_ToolTip.AddTool(pButton, _T("현제 디렉토리를 새로고침"));

	m_ToolTip.AddTool(GetDlgItem(IDC_RADIO_FILE_TRANS_ASC), _T("아스키 모드로 파일을 송수신 합니다."));
	m_ToolTip.AddTool(GetDlgItem(IDC_RADIO_FILE_TRANS_BIN), _T("바이너리 모드로 파일을 송수신 합니다."));
	m_ToolTip.AddTool(GetDlgItem(IDC_RADIO_FILE_TRANS_AUTO), _T("자동 모드로 파일을 송수신 합니다."));

	m_ToolTip.AddTool(&m_comboServerPath, _T("서버 디렉토리이동의 히스토리를 관리 합니다."));
	m_ToolTip.AddTool(&m_comboServer, _T("연결된 서버 목록"));

	m_ToolTip.AddTool(&m_listClient, _T("내컴퓨터 파일목록"));
	m_ToolTip.AddTool(&m_listServer, _T("연결한 서버의 파일목록"));

	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_LOG), _T("작업 로그"));
	
	m_ToolTip.Activate(TRUE);
}

void CGlassFTPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if (nID == SC_CLOSE) {
			EndDialog(IDOK);
		}

		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGlassFTPDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGlassFTPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGlassFTPDlg::OnCancel() 
{ 
}

void CGlassFTPDlg::OnOk() 
{ 
}


void CGlassFTPDlg::OnExit() 
{
	SendMessage(WM_SYSCOMMAND, SC_CLOSE, NULL);
	
}

//////////////////////////////////////////////////////////////////////
// 새로고침 시간 설정
UINT CGlassFTPDlg::GetInterval()
{
	using namespace NS_Config;

	return ::GetPrivateProfileInt (
				SECTION,
				_T("Interval"), 
				120, 
				INI_FILENAME
			) * 1000;
}

//////////////////////////////////////////////////////////////////////
// Editor 경로 가져오기 
CString CGlassFTPDlg::GetEditorPathName()
{
	using namespace NS_Config;

	TCHAR sz[SZ_SIZE + 1];

	::GetPrivateProfileString (
			SECTION,
			_T("Editor"), 
			_T("NotePad.exe"), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);

	return sz;
}

//////////////////////////////////////////////////////////////////////
// Diff 경로 가져오기 
CString CGlassFTPDlg::GetDiffPathName()
{
	using namespace NS_Config;

	TCHAR sz[SZ_SIZE + 1];

	::GetPrivateProfileString (
			SECTION,
			_T("Diff"), 
			_T(""), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);

	return sz;
}

//////////////////////////////////////////////////////////////////////
// 현제 디렉토리를 디폴트로 
void CGlassFTPDlg::OnSetDefaultPath() 
{
	using namespace NS_Config;

	::WritePrivateProfileString (
			SECTION,
			_T("DefaultPath"), 
			m_strClientPath, 
			INI_FILENAME
	);
}

//////////////////////////////////////////////////////////////////////
// 디폴트 클라이언트 디렉토리경로 가져오기  
CString CGlassFTPDlg::GetClientDefaultPath()
{
	using namespace NS_Config;

	TCHAR sz[SZ_SIZE + 1];

	::GetPrivateProfileString (
			SECTION,
			_T("DefaultPath"), 
			_T("c:"), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);

	return sz;
}


//////////////////////////////////////////////////////////////////////
// 디폴트 클라이언트 디렉토리경로 가져오기  
CString CGlassFTPDlg::GetBackupDirectory()
{
	using namespace NS_Config;

	TCHAR sz[SZ_SIZE + 1];

	::GetPrivateProfileString (
			SECTION,
			_T("Backup"), 
			_T(""), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);

	return sz;
}

//////////////////////////////////////////////////////////////////////
// 서버 파일 설정 개수 가져오기 
UINT CGlassFTPDlg::GetServerFileCount()
{
	using namespace NS_Config;

	return ::GetPrivateProfileInt(
				SECTION,
				_T("ServerFileCount"), 
				0, 
				INI_FILENAME
			);	
}

//////////////////////////////////////////////////////////////////////
// 전송모드 설정 가져오기 
UINT CGlassFTPDlg::GetTransMode()
{
	using namespace NS_Config;

	return ::GetPrivateProfileInt(
				SECTION,
				_T("TransMode"), 
				2, 
				INI_FILENAME
			);	
}

//////////////////////////////////////////////////////////////////////
// 전송모드 설정하기 
void CGlassFTPDlg::SetTransMode(UINT uMode)
{
	using namespace NS_Config;

	CString strMode;
	strMode.Format(_T("%u"), uMode);

	::WritePrivateProfileString (
				SECTION,
				_T("TransMode"), 
				(LPCTSTR)strMode,
				INI_FILENAME
			);	
}

//////////////////////////////////////////////////////////////////////
// 자동전송모드 파일 확장자 가져오기 
CString CGlassFTPDlg::GetAutoTranListString()
{
	using namespace NS_Config;

	TCHAR sz[SZ_SIZE + 1];

	::GetPrivateProfileString (
			SECTION,
			_T("Auto"), 
			_T(AUTOEXT_LIST), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);

	return sz;
}

//////////////////////////////////////////////////////////////////////
// 
CString CGlassFTPDlg::GetWriteLogFileMode()
{
	using namespace NS_Config;

	TCHAR sz[SZ_SIZE + 1];

	::GetPrivateProfileString(
		SECTION,
		_T("FileLog"),
		_T("0"),
		sz,
		SZ_SIZE,
		INI_FILENAME
	);

	return sz;
}




//////////////////////////////////////////////////////////////////////
// ListView Control에 Client파일 Setting
void CGlassFTPDlg::SetClientFiles(CString strPath)
{
	if (strPath.Right(1) == _T("\\")) {
		strPath += _T("*.*");
	}
	else {
		strPath += _T("\\*.*");	
	}

	TRACE(_T("%s\n"), strPath);

	BOOL bNotLast = TRUE;
	m_listClient.DeleteAllItems();			// Client ListView Control Reset

	CFileFind FFind;
	bNotLast = FFind.FindFile(strPath);

	int nCount = 0;
	while (bNotLast) {
		bNotLast = FFind.FindNextFile();

		m_strClientPath = FFind.GetRoot();
		SetDlgItemText(IDC_EDIT_CLIENT_PATH, m_strClientPath); 

		if (!FFind.IsDots()) {
			m_listClient.AddFile(FFind);
			++nCount;
		}
	}

	//CString s;
	//s.Format(_T("%d"), nCount);
	//SetDlgItemText(IDC_STATIC_STATUS_CLIENTS, s);

	m_listClient.Sort(0);
}

//////////////////////////////////////////////////////////////////////
// ListView Control에 Server파일 Setting
BOOL CGlassFTPDlg::SetServerFiles(CString strPath, BOOL bActiveServer)
{
	m_listServer.DeleteAllItems();				// Server ListView Control Reset 

	if (!m_pFtp) {
		return FALSE;
	}

	CString strServerPath = strPath;
	if (!strServerPath.IsEmpty()) {
		strServerPath += (strServerPath.Right(1) == _T("/") ? _T("*") : _T("/*"));
	}

	BOOL bNotLast = m_pFtp->m_pFFind->FindFile(strServerPath);
	
	// 활성화된 서버이면 해당 개수만큰 파일을 가져와 
	if (bActiveServer && bNotLast) {
		UINT uServerFileCount = GetServerFileCount();

		if (!uServerFileCount) {
			uServerFileCount = 0xFFFFFFFF;	
		}
		
		UINT uCnt = 0;
		while (bNotLast && uCnt < uServerFileCount) {
			bNotLast = m_pFtp->m_pFFind->FindNextFile();

			if (!m_pFtp->m_pFFind->IsDots()) {
				m_listServer.AddFile(*(m_pFtp->m_pFFind), FALSE);
				uCnt++;
			}
		}

		m_listServer.Sort(0);
	}

	if (!m_pFtp->m_pFtpCon->SetCurrentDirectory(strPath)) {
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// DblClick - Client 폴더이동 
void CGlassFTPDlg::OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DblclkListClient();
	*pResult = 0;
}


//////////////////////////////////////////////////////////////////////
// DblClick - Client 폴더이동 
void CGlassFTPDlg::DblclkListClient() 
{
	if (m_listClient.GetSelectedCount() <= 0)
		return ;

	int nIndex = m_listClient.GetSelectionMark(); 

	CString strDirName = m_listClient.GetItemText(nIndex, 0);		
	CString strFileSize = m_listClient.GetItemText(nIndex, 1);		

	if (strFileSize.IsEmpty()) {
		CString strClientPath = m_strClientPath + _T("\\");
		strClientPath += strDirName;

		SetClientFiles(strClientPath);
		SyncToServerDirectory(strDirName);
	}
	else {
		::ShellExecute (
			NULL,
			"open",
			strDirName, 
			NULL, 
			m_strClientPath, 
			SW_SHOWNORMAL
		);
	}
}

//////////////////////////////////////////////////////////////////////
// Server Path로 이동 
void CGlassFTPDlg::DirectMoveServerPath(const CString &strServerPath)
{
	if (!m_pFtp) {
		return ;
	}

	CString strOldServerPath;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strOldServerPath);
	
	if (!MultiServerMove(strServerPath)) {
		AfxMessageBox(_T("디렉토리 구조가 틀리거나 허가가 되어 있지 않아 이동할 수 없습니다. "));
		MultiServerMove(strOldServerPath);

		return ;
	}
}

//////////////////////////////////////////////////////////////////////
// Server Path Combo에서 경로를 선책한 경우 
void CGlassFTPDlg::OnSelchangeComboServerPath() 
{
	CString strServerPath;
	m_comboServerPath.GetLBText(m_comboServerPath.GetCurSel(), strServerPath);
	
	DirectMoveServerPath(strServerPath);
}

//////////////////////////////////////////////////////////////////////
// DblClick - Server 폴더이동 
void CGlassFTPDlg::OnDblclkListServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DblclkListServer();
	*pResult = 0;
}


//////////////////////////////////////////////////////////////////////
// DblClick - Server 폴더이동 
void CGlassFTPDlg::DblclkListServer()
{
	if (m_listServer.GetSelectedCount() <= 0) 
		return ;

	int nIndex = m_listServer.GetSelectionMark(); 

	CString strDirName = m_listServer.GetItemText(nIndex, 0);		
	CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

	if (strFileSize.IsEmpty()) {
		CString strServerPath;
		m_pFtp->m_pFtpCon->GetCurrentDirectory(strServerPath);
	
		CString strOldServerPath = strServerPath;

		strServerPath = (strServerPath.Right(1) == _T("/") ? strServerPath : strServerPath + _T("/"));
		strServerPath += strDirName;

		if (!MultiServerMove(strServerPath)) {
			AfxMessageBox(_T("디렉토리 구조가 틀리거나 허가가 되어 있지 않아 이동할 수 없습니다. "));
			MultiServerMove(strOldServerPath);

			return ;
		}

		SyncToClientDirectory(strDirName);
	}
	else {
		GetFileToTemp();
	}
}

//////////////////////////////////////////////////////////////////////
// 다중 Server 폴더이동 
BOOL CGlassFTPDlg::MultiServerMove(CString strServerPath)
{
	// 현제 활성화 서버 저장 
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	CString strMsg = _T(" 디렉토리 이동중 : ");
	strMsg += strServerPath;
	strMsg += _T("         ");		// 잔상을 없애기 위해 
	m_comboServerPath.SetWindowText(strMsg); 

	// m_comboServerPath 에 메세지를 표시하기 위해 
	m_comboServerPath.SetFocus();
	m_listServer.SetFocus();
	
	for (int i = 0; i < nLen; i++) {
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			if (!SetServerFiles(strServerPath, FALSE)) {
				return FALSE;
			}
		}
	}

	m_pFtp = pFtp;
	ServerRefresh();

	InsertServerPath();

	return TRUE;
}


//////////////////////////////////////////////////////////////////////
// Server Path Combo에 이동한 경로 추가 - HISTORY 추가 
void CGlassFTPDlg::InsertServerPath()
{
	CString strServerPath;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strServerPath);

	int nFindIndex = m_comboServerPath.FindStringExact(0, strServerPath);

	// 종전의 히스토리에서 문자열을 찾으면 지우기 
	if (CB_ERR != nFindIndex) {
		m_comboServerPath.DeleteString(nFindIndex);	
	}
	
	// 서버 경로를 맨앞에 삽입하고 커서를 맨앞노드에 위치 
	m_comboServerPath.InsertString(0, strServerPath); 
	m_comboServerPath.SetCurSel(0);	
}

//////////////////////////////////////////////////////////////////////
// SHBrowseForFolder
void CGlassFTPDlg::OnBtnShbf() 
{
	CString strPath;
	if (GetSHBF(strPath)) {
		SetClientFiles(strPath);
	}
}

//////////////////////////////////////////////////////////////////////
// SHBrowseForFolder 구현 
BOOL CGlassFTPDlg::GetSHBF(CString &strPath)
{
	TCHAR szDir[SZ_SIZE + 1];
	
	BROWSEINFO bi;
	ZeroMemory(reinterpret_cast<LPVOID>(&bi), sizeof(BROWSEINFO));

	bi.hwndOwner = m_hWnd;
	bi.lpszTitle  = "폴더를 이동합니다.  ";
	
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&bi);
	if (!pidl) {
		return FALSE;
	}

	::SHGetPathFromIDList(pidl, szDir); 

	strPath = szDir;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Client 상위 디렉토리로 ...
void CGlassFTPDlg::OnBtnClientParent() 
{
	SetClientFiles(m_strClientPath + _T("\\.."));
	SyncToServerDirectory(_T(".."));
}

//////////////////////////////////////////////////////////////////////
// Server 상위 디렉토리로 ...
void CGlassFTPDlg::OnBtnServerParent() 
{
	if (!m_pFtp) { 
		return;
	}

	CString strCurrServerPath;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strCurrServerPath);
	
	if (strCurrServerPath == _T("/") || strCurrServerPath == _T("")) {
		return;
	}

	MultiServerMove(_T(".."));
	SyncToClientDirectory(_T(".."));
}

//////////////////////////////////////////////////////////////////////
// Session Close : Button
void CGlassFTPDlg::OnBtnServerClose() 
{
	OnCloseall();
	
}

//////////////////////////////////////////////////////////////////////
// Ftp Session Open
void CGlassFTPDlg::OnOpen() 
{
	AfxBeginThread(CGlassFTPDlg::Open, reinterpret_cast<LPVOID>(this));
}

//////////////////////////////////////////////////////////////////////
// Ftp Session Open Impl
UINT CGlassFTPDlg::Open(LPVOID lpvParam) 
{
	CGlassFTPDlg *pThis = reinterpret_cast<CGlassFTPDlg *>(lpvParam);

	if (pThis->m_pFtp) {
		if (IDOK != AfxMessageBox(_T("이미 서버에 연결되어 있습니다. \n\n연결을 끊고 다시 연결 하시겠습니까?"), MB_OKCANCEL)) {
			return 0L;
		}
		pThis->CloseAll(FALSE);
	}

	CServerSetting dlg;
	if (dlg.DoModal() == IDCANCEL) {
		return 0L;
	}

	CString strConIP;
	CString strIP = dlg.m_strIP; 
	CString strID = dlg.m_strID; 
	CString strPassword = dlg.m_strPassword;
	CString strDefaultPath = dlg.m_strDefaultPath;
	CString strDefaultPathClient = dlg.m_strDefaultClientPath;
	WORD nPort = (WORD)dlg.m_uPort;
	int nPassive = dlg.m_nPassive;

	// 서버에서 설정한 클라이언트 기본 경로 설정 
	if (!strDefaultPathClient.IsEmpty()) {
		pThis->SetClientFiles(strDefaultPathClient);
	}

	CFtp *pFtp;
	int nIndex = 1;

	LPCTSTR p = static_cast<LPCTSTR>(strIP);
	int nServerCount = std::count(p, p + strIP.GetLength(), ';') + 1;
	pThis->SetProgRange(nServerCount);

	while (nIndex >= 0) {
		pThis->SetProgPosInc();
		nIndex = strIP.Find(TCHAR(';'));

		if (nIndex > 0) {
			strConIP = strIP.Left(nIndex);
			strIP = strIP.Mid(nIndex + 1);
		}
		else {
			strConIP = strIP;
		}

		strConIP.TrimLeft();
		strConIP.TrimRight();

		if (!strConIP.IsEmpty()) { 
			pFtp = new CFtp();
			pFtp->Open(strConIP, strID, strPassword, nPort, nPassive == 0 ? FALSE : TRUE); 

			if (!pFtp->IsOpen()) {
				int nResult = AfxMessageBox(strConIP + _T(" : 연결이 실패 했습니다. \n\n계속 진행 하시겠습니까? "), MB_YESNO);
				delete pFtp;
				pFtp = NULL;

				if (nResult != IDYES) {
					pThis->CloseAll(FALSE);
					return 0;
				}
			}

			pThis->m_FtpArray.Add((LPVOID)pFtp);

			if (pFtp) {
				pThis->m_pFtp = pFtp;

				if (!strDefaultPath.IsEmpty()) {
					pThis->SetServerFiles(strDefaultPath);
				}

				pThis->WriteLog(_T("[세션연결]  ") + pThis->GetActiveSessionName());
			}
			else {
				pThis->WriteLog(_T("[세션연결]  ") + strConIP + _T(" [실패]"));
			}
		}
	}
	
	if (pThis->m_FtpArray.GetSize() == 0) {
		AfxMessageBox(_T("연결된 서버가 없습니다."));
		return 0L;
	}

	// 디렉토리 이동 히스토리에 추가 
	pThis->InsertServerPath();
	
	pThis->UpdateServerList();		// List Control Update 
	pThis->SetTimer(ID_TIMER, pThis->GetInterval(), NULL);

	CMenu *pMenu = pThis->GetMenu();
	pMenu->EnableMenuItem(IDM_CLOSEALL, MF_ENABLED);	// Menu [Close] Enaable

	pThis->WriteLog(_T("[세션연결] 완료 되었습니다. !!"));
	pThis->WriteSeparator();
	
	pThis->SetProgPos();

	// 2003/07/03
	// 추가 : 드랍다운 리스트를 보여준다 
	pThis->m_comboServer.ShowDropDown();	

	return 0L;
}


//////////////////////////////////////////////////////////////////////
// CFtp Memory Free 
void CGlassFTPDlg::Release()
{
	ReleaseAll();
	/**
	int nSize = GetServerCount();

	for (int i = 0; i < nSize; i++) {
		if (m_pFtp == (CFtp *)m_FtpArray.GetAt(i)) {
			delete (CFtp *)m_FtpArray.GetAt(i);
			m_FtpArray.RemoveAt(i); 
			break;
		}
	}
	*/
}

//////////////////////////////////////////////////////////////////////
// CFtp Memory Free 
void CGlassFTPDlg::ReleaseAll()
{
	m_pFtp = NULL;

	m_comboServer.ResetContent();
	int nSize = GetServerCount();

	for (int i = 0; i < nSize; i++) {
		delete (CFtp *)m_FtpArray.GetAt(0);
		m_FtpArray.RemoveAt(0); 
	}

	KillTimer(ID_TIMER);
}


//////////////////////////////////////////////////////////////////////
// 파일 수신 
void CGlassFTPDlg::OnBtnGet() 
{
	AfxBeginThread(CGlassFTPDlg::GetFiles, reinterpret_cast<LPVOID>(this));
}


UINT CGlassFTPDlg::GetFiles(LPVOID lpvParam)
{
	CGlassFTPDlg *pThis = reinterpret_cast<CGlassFTPDlg *>(lpvParam);

	try {
		pThis->SetProgRange(pThis->m_listServer.GetSelectedCount());
		pThis->EnableSendRecv(FALSE);
		pThis->GetFilesImp(); 
/**
 * 20021217
		CString strTransMode;
		if (pThis->m_nTransType + 1 ==  FTP_TRANSFER_TYPE_ASCII) {
			strTransMode = _T("아스키 모드");
		}
		else {
			strTransMode = _T("바이너리 모드");
		}

		pThis->WriteLog(_T("[파일수신] ") + strTransMode + _T(" 수신완료 !!"));
*/
	}
	catch (...) {
		AfxMessageBox(_T("시스템 오류 !!"));
	}

	// 송수신 버튼을 Enable 시킨다 
	pThis->EnableSendRecv(TRUE);
	pThis->SetProgPos();

	return 0L;
}

void CGlassFTPDlg::GetFilesImp()
{
	UpdateData(TRUE);
	KillTimer(ID_TIMER);

	int nIndex = 0;
	POSITION pos;
	UINT uSelectedCount = m_listServer.GetSelectedCount();

	if (!uSelectedCount || !m_pFtp) {
		return ;
	}

	pos = m_listServer.GetFirstSelectedItemPosition();
	CString strGetFileName, strClientFileName;
	BOOL bFileExists = FALSE;
	m_bIDOKALL = FALSE;

	for (int i = 0; i < (int)uSelectedCount; i++) {
		SetProgPosInc();
		nIndex = m_listServer.GetNextSelectedItem(pos); 

		CString strFileName = m_listServer.GetItemText(nIndex, 0);		
		CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

		m_pFtp->m_pFtpCon->GetCurrentDirectory(strGetFileName);
		
		if (!strFileSize.IsEmpty()) {
			strGetFileName = (strGetFileName.Right(1) == _T("/") ? strGetFileName : strGetFileName + _T("/"));
			strGetFileName += strFileName;

			strClientFileName = m_strClientPath + _T("\\") + strFileName;

			bFileExists = ListViewFileExists(m_listClient, strFileName);			// 파일이 존재 하면 

			if (bFileExists && (!m_bIDOKALL)) {
				int nMessageBox = CMessageDlg::MessageBox(strFileName + _T(" 이 존재합니다. \n\n 덮어 쓰시겠습니까 ?")); 

				if (nMessageBox == IDCANCEL) {
					continue ;
				}
				else if (nMessageBox == CMessageDlg::IDOK_ALL) {
					m_bIDOKALL = TRUE;
				}
			}

			DWORD dwTransMode = GetAutoTransMode(strFileName);
			
			if (!m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, !bFileExists, FILE_ATTRIBUTE_NORMAL, dwTransMode)) {
				AfxMessageBox(strGetFileName + _T(" 의 수신이 실패했습니다. "));		
			}

			CString strBackup = GetBackupDirectory();
			// Backup Mode이면 Backup 수행 
			if (!strBackup.IsEmpty()) {
				CreateDirectory(m_strClientPath + _T("\\") + strBackup, NULL);
				strClientFileName = m_strClientPath + _T("\\") + strBackup + _T("\\") + strFileName;
				m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, !bFileExists, FILE_ATTRIBUTE_NORMAL, dwTransMode);
			}

			// Write log
			CString strServerName;
			strServerName.Format(_T("[파일수신: %s][%s] %s"), 
				GetActiveSessionName(),
				(dwTransMode == FTP_TRANSFER_TYPE_ASCII) ? _T("Asc") : _T("Bin"), 
				(LPCTSTR)strGetFileName
			);

			WriteLog(strServerName);
			WriteSeparator();

			ClientRefresh();
		}
	}

	SetTimer(ID_TIMER, GetInterval(), NULL);
}

//////////////////////////////////////////////////////////////////////
// 송수신 버튼을 제어한다 
void CGlassFTPDlg::EnableSendRecv(BOOL bEnable)
{
	GetDlgItem(IDC_BTN_PUT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_GET)->EnableWindow(bEnable);

	GetDlgItem(IDC_RADIO_FILE_TRANS_ASC)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_FILE_TRANS_BIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_RADIO_FILE_TRANS_AUTO)->EnableWindow(bEnable);

	GetDlgItem(IDC_BTN_CLIENT_PARENT)->EnableWindow(bEnable);
	GetDlgItem(IDC_BTN_SERVER_PARENT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_SERVER_PATH)->EnableWindow(bEnable);

	m_listClient.EnableEventMessage(bEnable);
	m_listServer.EnableEventMessage(bEnable);
}


//////////////////////////////////////////////////////////////////////
// 파일 송신
void CGlassFTPDlg::OnBtnPut() 
{
	AfxBeginThread(MultiServerPutFiles, reinterpret_cast<LPVOID>(this));
}

UINT CGlassFTPDlg::MultiServerPutFiles(LPVOID lpvParam)
{
	CGlassFTPDlg *pThis = reinterpret_cast<CGlassFTPDlg *>(lpvParam);

	try {
		// 송수신 버튼을 Disable 시킨다 
		pThis->EnableSendRecv(FALSE);
		
		// 활성화된 서버 인덱스 기억 
		const int nIndex = pThis->SearchFtp(pThis->m_pFtp);

		if (nIndex == -1) {
			pThis->EnableSendRecv(TRUE);
			return 0L;
		}

		int nServerCount = 0;

		// 현제 서버에만 적용이면 
		if (pThis->IsCurrentServerCheck()) {
			nServerCount = 1;
		}
		else {
			nServerCount = pThis->GetServerCount();
		}

		if (!nServerCount) {
			pThis->EnableSendRecv(TRUE);
			return 0L;
		}
		
		pThis->m_bIDOKALL = FALSE;
		pThis->SetProgRange(pThis->m_listClient.GetSelectedCount() * nServerCount);

		// 현제 서버에만 적용이면 
		if (pThis->IsCurrentServerCheck()) {
			pThis->SetActiveServer(nIndex);
			pThis->PutFiles();
		}
		else {
			for (int i = 0; i < nServerCount; i++) {
				pThis->SetActiveServer(i);
				pThis->PutFiles();
			}

			pThis->SetActiveServer(nIndex);
		}

		pThis->WriteLog(_T("[파일송신] 송신완료 !!"));
		pThis->WriteSeparator();

	}
	catch (...) {
		AfxMessageBox(_T("시스템 오류 !!"));
	}

	// 송수신 버튼을 Enable 시킨다 
	pThis->EnableSendRecv(TRUE);
	pThis->SetProgPos();

	return 0L;
}


//////////////////////////////////////////////////////////////////////
// 활성화된 서버에 선택한 파일을 올린다 
void CGlassFTPDlg::PutFiles()
{
	UpdateData(TRUE);
	KillTimer(ID_TIMER);

	int nIndex = 0;
	POSITION pos;
	CString strPutFileName;

	UINT uSelectedCount = m_listClient.GetSelectedCount();
	if (!uSelectedCount || !m_pFtp) {
		return ;
	}

	pos = m_listClient.GetFirstSelectedItemPosition();
	BOOL bFileExists = FALSE;

	for (int i = 0; i < (int)uSelectedCount; i++) {
		SetProgPosInc();
		nIndex = m_listClient.GetNextSelectedItem(pos); 

		CString strFileName = m_listClient.GetItemText(nIndex, 0);		
		CString strFileSize = m_listClient.GetItemText(nIndex, 1);		
		CString strFileTime = m_listClient.GetItemText(nIndex, 2);

		if (!strFileSize.IsEmpty()) {
			strPutFileName = m_strClientPath + _T("\\");
			strPutFileName += strFileName;

			bFileExists = ListViewFileExists(m_listServer, strFileName);			// 파일이 존재 하면 

			if (bFileExists && (!m_bIDOKALL)) {
				int nMessageBox = CMessageDlg::MessageBox(strFileName + _T(" 이 존재합니다. \n\n 덮어 쓰시겠습니까 ?")); 

				if (nMessageBox == IDCANCEL) {
					continue ;
				}
				else if (nMessageBox == CMessageDlg::IDOK_ALL) {
					m_bIDOKALL = TRUE;
				}
			}

			DWORD dwTransMode = GetAutoTransMode(strFileName);
			
			if (!ServerPutFile(strPutFileName, strFileName,  dwTransMode)) {
				AfxMessageBox(strPutFileName + _T(" 의 송신이 실패했습니다. "));	
			}

			// Write log
			CString strServerName;
			strServerName.Format(_T("[파일송신: %s][%s] %s"), 
				GetActiveSessionName(),
				(dwTransMode == FTP_TRANSFER_TYPE_ASCII) ? _T("Asc") : _T("Bin"), 
				(LPCTSTR)strPutFileName
			);

			m_listServer.AddFile(strFileName, strFileName, strFileSize, strFileTime, FALSE);
			WriteLog(strServerName);
		}
	}			

	SetTimer(ID_TIMER, GetInterval(), NULL);
}


//////////////////////////////////////////////////////////////////////
// 여려개의 서버에 파일 송신 
BOOL CGlassFTPDlg::ServerPutFile(CString strLocalFile, CString strRemoteFile, DWORD dwFlag)
{
	BOOL bRet = TRUE;;

	// 2006.09.06 by cdecl
	// 필요없는 로직 삭제 
	// 왜 파일을 지웠는지 몰겟다.
	//m_pFtp->m_pFtpCon->Remove(strRemoteFile);	// 파일이 있으면 먼저 지운다 

	if (!m_pFtp->m_pFtpCon->PutFile(strLocalFile, strRemoteFile, dwFlag)) {
		bRet = FALSE;
	}

	return bRet;
}


//////////////////////////////////////////////////////////////////////
// Server ListView Control 갱신 
void CGlassFTPDlg::ServerRefresh()
{
	CString strServerPath;

	if (m_pFtp) {
		m_pFtp->m_pFtpCon->GetCurrentDirectory(strServerPath);
	}

	SetServerFiles(strServerPath, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Client ListView Control 갱신 
void CGlassFTPDlg::ClientRefresh()
{
	SetClientFiles(m_strClientPath);
}

//////////////////////////////////////////////////////////////////////
// Server ListView Control 갱신 : Button
void CGlassFTPDlg::OnBtnServerRefresh() 
{
	ServerRefresh();
}

//////////////////////////////////////////////////////////////////////
// Client ListView Control 갱신 : Button
void CGlassFTPDlg::OnBtnClientRefresh() 
{
	ClientRefresh();
}

//////////////////////////////////////////////////////////////////////
// Written log 
void CGlassFTPDlg::WriteLog(CString strLog)
{
	CTime Time = CTime::GetCurrentTime();
	CString strTime;
	strTime.Format(_T("[%04d/%02d/%02d %02d:%02d:%02d] "), 
			Time.GetYear(), Time.GetMonth(), Time.GetDay(), 
			Time.GetHour(), Time.GetMinute(), Time.GetSecond());

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_LOG);

	int nLen = pEdit->GetWindowTextLength();

	if (pEdit->GetLimitText() <= (size_t)nLen) {
		pEdit->SetWindowText(_T(""));	
		nLen = 0;
	}
	
	pEdit->SetSel(nLen, nLen);
	pEdit->ReplaceSel(strTime + strLog + _T("\r\n")); 

	WriteLogFile(strTime + strLog);
}

//////////////////////////////////////////////////////////////////////
// Written log 
void CGlassFTPDlg::WriteSeparator()
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_LOG);

	int nLen = pEdit->GetWindowTextLength();

	if (pEdit->GetLimitText() <= nLen) {
		pEdit->SetWindowText(_T(""));	
		nLen = 0;
	}
	
	CString strLine = _T("──────────────────────────────────────────────────────────\r\n");
	pEdit->SetSel(nLen, nLen);
	pEdit->ReplaceSel((strLine + _T("\r\n"))); 

	WriteLogFile(strLine);
}

void CGlassFTPDlg::WriteLogFile(const CString &strLog)
{
	if (GetWriteLogFileMode() == _T("1")) {
		m_logFile << (LPCSTR)strLog << endl;
	}
}


//////////////////////////////////////////////////////////////////////
// 로그 지우기
void CGlassFTPDlg::OnBtnLogClear() 
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_LOG);
	int nLen = pEdit->GetWindowTextLength();
	pEdit->SetSel(0, nLen);
	pEdit->ReplaceSel(_T("")); 	
}


void CGlassFTPDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal(); 
}

//////////////////////////////////////////////////////////////////////
// Server ListView Contol KeyDown Message
// File Delete 
void CGlassFTPDlg::OnKeydownListServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	if (pLVKeyDow->wVKey == VK_DELETE) {
		AfxBeginThread(DeleteServerFile, reinterpret_cast<LPVOID>(this));
	}
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////
// Client ListView Contol KeyDown Message 
// File Delete 
void CGlassFTPDlg::OnKeydownListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	if (pLVKeyDow->wVKey == VK_F2) {
		ClientEditLabel();
	}

	if (pLVKeyDow->wVKey == VK_DELETE) {
		DeleteClientFile();
	}

	*pResult = 0;
}


UINT CGlassFTPDlg::DeleteServerFile(LPVOID lpvParam)
{
	CGlassFTPDlg *pThis = reinterpret_cast<CGlassFTPDlg *>(lpvParam);

	try {
		pThis->DeleteServerFileImp(); 
	}
	catch (...) {
		AfxMessageBox(_T("시스템 오류 !!"));
	}

	return 0L;
}


//////////////////////////////////////////////////////////////////////
// Server File Delete : Menu
void CGlassFTPDlg::DeleteServerFileImp()
{
	int nIndex = 0;
	POSITION pos;
	CString strMsgBox;

	UINT uSelectedCount = m_listServer.GetSelectedCount();
	if (uSelectedCount == 0 || !m_pFtp) {
		return ;
	}

	strMsgBox.Format(_T("%u 개의 항목을 삭제하시겠습니까 ?"), uSelectedCount);
	if (AfxMessageBox(strMsgBox, MB_OKCANCEL) == IDCANCEL) 
		return ;

	pos = m_listServer.GetFirstSelectedItemPosition();
	SetProgRange(uSelectedCount * GetServerCount());

	for (int i = 0; i < (int)uSelectedCount; i++) {
		nIndex = m_listServer.GetNextSelectedItem(pos); 

		CString strFileName = m_listServer.GetItemText(nIndex, 0);		
		CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

		if (!strFileSize.IsEmpty()) {		// 파일이면 
			if (!MultiServerRemove(strFileName)) {
				AfxMessageBox(strFileName + _T(" 파일 삭제 실패 !! - 한개 이상의 서버에서 문제가 발생하였습니다."));	
			}

			WriteLog(_T("[파일삭제]  파일삭제 완료 !!"));
		}
		else {								// 디렉토리면 
			if (!MultiServerRemoveDir(strFileName)) {
				AfxMessageBox(strFileName + _T(" 디렉토리 삭제 실패 !! - 한개 이상의 서버에서 문제가 발생하였습니다."));	
			}

			WriteLog(_T("[디렉토리삭제]  디렉토리삭제 완료 !!"));
		}

		WriteSeparator();
	}		

	ServerRefresh();
	SetProgPos();
}

//////////////////////////////////////////////////////////////////////
// 여려개의 서버 파일 삭제 
BOOL CGlassFTPDlg::MultiServerRemove(CString strFileName)
{
	BOOL bRet = TRUE;;
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	// 현제 서버에만 적용이면 
	BOOL bIsCurrentServerCheck = IsCurrentServerCheck();
		
	for (int i = 0; i < nLen; i++) {
		SetProgPosInc();
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	
			
			// 현제 서버에만 적용이면 
			if (bIsCurrentServerCheck) {
				if (m_pFtp == pFtp) {
					if (!m_pFtp->m_pFtpCon->Remove(strFileName)) {
						bRet = FALSE;
						WriteLog(_T("[파일삭제 실패:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					else {
						WriteLog(_T("[파일삭제:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					break;
				}
			}
			else {
				if (!m_pFtp->m_pFtpCon->Remove(strFileName)) {
					bRet = FALSE;
					WriteLog(_T("[파일삭제 실패:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
				else {
					WriteLog(_T("[파일삭제:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
			}
		}
	}

	m_pFtp = pFtp;
	return bRet;
}


//////////////////////////////////////////////////////////////////////
// 여려개의 서버 디렉토리 삭제 
BOOL CGlassFTPDlg::MultiServerRemoveDir(CString strFileName)
{
	BOOL bRet = TRUE;;
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	// 현제 서버에만 적용이면 
	BOOL bIsCurrentServerCheck = IsCurrentServerCheck();

	for (int i = 0; i < nLen; i++) {
		SetProgPosInc();
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			// 현제 서버에만 적용이면 
			if (bIsCurrentServerCheck) {
				if (m_pFtp == pFtp) {
					if (!m_pFtp->m_pFtpCon->RemoveDirectory(strFileName)) {
						bRet = FALSE;
						WriteLog(_T("[디렉토리삭제 실패:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					else {
						WriteLog(_T("[디렉토리삭제:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					break;
				}
			}
			else {	
				if (!m_pFtp->m_pFtpCon->RemoveDirectory(strFileName)) {
					bRet = FALSE;
					WriteLog(_T("[디렉토리삭제 실패:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
				else {
					WriteLog(_T("[디렉토리삭제:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
				
			}
		}
	}

	m_pFtp = pFtp;
	return bRet;
}


//////////////////////////////////////////////////////////////////////
// Server File Delete : Button
inline void CGlassFTPDlg::OnBtnServerDelete() 
{
	AfxBeginThread(DeleteServerFile, reinterpret_cast<LPVOID>(this));
}

//////////////////////////////////////////////////////////////////////
// Client File Delete : Menu
void CGlassFTPDlg::DeleteClientFile()
{
	int nIndex = 0;
	POSITION pos;
	CString strMsgBox;
	
	UINT uSelectedCount = m_listClient.GetSelectedCount();
	if (uSelectedCount == 0) {
		return ;
	}

	strMsgBox.Format(_T("%u 개의 항목을 삭제하시겠습니까 ?"), uSelectedCount);
	if (AfxMessageBox(strMsgBox, MB_OKCANCEL) == IDCANCEL) 
		return ;

	pos = m_listClient.GetFirstSelectedItemPosition();

	SetProgRange(uSelectedCount);
	for (int i = 0; i < (int)uSelectedCount; i++) {
		SetProgPosInc();
		nIndex = m_listClient.GetNextSelectedItem(pos); 

		CString strFileName = m_listClient.GetItemText(nIndex, 0);		
		CString strFileSize = m_listClient.GetItemText(nIndex, 1);		

		strFileName = m_strClientPath + _T("\\") + strFileName;

		if (!strFileSize.IsEmpty()) {		// 파일이면 
			if (!::DeleteFile(strFileName)) {
				AfxMessageBox(strFileName + _T(" 파일 삭제 실패 !! "));	
			}

			WriteLog(_T("[파일삭제:  Local] ") + strFileName);
		}
		else {								// 디렉토리면 
			if (!::RemoveDirectory(strFileName)) {
				AfxMessageBox(strFileName + _T(" 디렉토리 삭제 실패 !! "));	
			}

			WriteLog(_T("[디렉토리삭제:  Local] ") + strFileName);
		}

		WriteSeparator();
	}		

	ClientRefresh();
	SetProgPos();
}

//////////////////////////////////////////////////////////////////////
// Client File Delete : Button
void CGlassFTPDlg::OnBtnClientDelete() 
{
	DeleteClientFile();
}


//////////////////////////////////////////////////////////////////////
// Client ListView Control 에서 파일의 존재여부 검사 
BOOL CGlassFTPDlg::ListViewFileExists(CFileListCtrl &listView, CString strFileName)
{
	int nCount = listView.GetItemCount(); 

	for (int i = 0; i < nCount; i++) {
		if (listView.GetItemText(i, 0) == strFileName) {
			return TRUE;
		}
	}

	return FALSE;
}


//////////////////////////////////////////////////////////////////////
// Server를 보여주는 List Control 에서 파일의 존재여부 검사 
void CGlassFTPDlg::UpdateServerList()
{
	int nSize = GetServerCount();
	m_comboServer.ResetContent();

	CString strServerName;
	
	for (int i = 0; i < nSize; i++) {
		if (m_FtpArray.GetAt(i)) {
			strServerName.Format(_T("[%03d:] %s "), i + 1, ((CFtp *)m_FtpArray.GetAt(i))->m_pFtpCon->GetServerName());
		}
		else {
			strServerName.Format(_T("[%03d:] %s "), i + 1, _T("연결실패"));
		}
		m_comboServer.AddString(strServerName); 
	}
	
	SetActiveServer(0);
}

//////////////////////////////////////////////////////////////////////
// ListBox에서 선택한 서버가 Active된다 
void CGlassFTPDlg::SetActiveServer(int nListIndex)
{
	if (!GetServerCount() || !m_comboServer.GetCount()) {
		ServerRefresh();	
		return ;
	}
	
	m_pFtp = (CFtp *)m_FtpArray.GetAt(nListIndex);
	m_comboServer.SetCurSel(nListIndex); 

	ServerRefresh();
}

//////////////////////////////////////////////////////////////////////
// ListBox에서 선택하면 
inline void CGlassFTPDlg::OnSelchangeComboServer() 
{
	SetActiveServer(m_comboServer.GetCurSel()); 
}

//////////////////////////////////////////////////////////////////////
// 윈도우가	Destroy될때 메모리 헤제 
BOOL CGlassFTPDlg::DestroyWindow() 
{
	UpdateData(TRUE);
	SetTransMode(static_cast<UINT>(m_nTransType));

	ReleaseAll();

	return CDialog::DestroyWindow();
}

//////////////////////////////////////////////////////////////////////
// 모든 Session을 닫는다 
void CGlassFTPDlg::OnCloseall() 
{
	CloseAll();
}

//////////////////////////////////////////////////////////////////////
// 모든 Session을 닫는다 
void CGlassFTPDlg::CloseAll(BOOL bAskMsg)
{
	if (bAskMsg) {
		if (AfxMessageBox(_T("현제의 모든 세션을 종료 하시겠습니까 ?"), MB_OKCANCEL) == IDCANCEL) {
			return ;
		}
	}

	ReleaseAll();
	UpdateServerList();

	// 서버 이동 히스토리를 지운다 
	m_comboServerPath.ResetContent();

	CMenu *pMenu = GetMenu();
	pMenu->EnableMenuItem(IDM_CLOSEALL, MF_GRAYED);	// Menu [Close] Enaable

	WriteLog(_T("[세션끊기] 세션의 연결을 끊었습니다."));
	WriteSeparator();
}


//////////////////////////////////////////////////////////////////////
// CFtp 객체의 Index를 찾아 index를 return 한다 
int CGlassFTPDlg::SearchFtp(CFtp *pFtp)
{
	int nSize = GetServerCount();

	for (int i = 0; i < nSize; i++) {
		if (m_pFtp == (CFtp *)m_FtpArray.GetAt(i)) {
			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////
// Server에 새로운 폴더생성 
void CGlassFTPDlg::OnBtnServerNewforder() 
{
	CForderName FName;
	CString strForderName;

	if (!m_pFtp)							// 연결된 세션이 없으면 return 
		return ;

	if (FName.DoModal() != IDOK)			
		return ;

	if (FName.m_strForderName.IsEmpty())	// 생성할 폴더 이름이 없으면 return
		return ;

	m_pFtp->m_pFtpCon->GetCurrentDirectory(strForderName);
	strForderName += (_T("/") + FName.m_strForderName); 
	
	SetProgRange(GetServerCount());
	if (!MultiServerNewForder(strForderName)) {
		AfxMessageBox(strForderName + _T(" 디렉토리를 생성 할수 없습니다. - 한개 이상의 서버에서 문제가 발생하였습니다."));
	}

	WriteLog(_T("[디렉토리생성]  디렉토리생성 완료 !!"));
	WriteSeparator();

	ServerRefresh();
	SetProgPos();
}


//////////////////////////////////////////////////////////////////////
// 여려개의 Server에 새로운 폴더생성 
BOOL CGlassFTPDlg::MultiServerNewForder(CString strForderName)
{
	BOOL bRet = TRUE;;
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	// 현제 서버에만 적용이면 
	BOOL bIsCurrentServerCheck = IsCurrentServerCheck();

	for (int i = 0; i < nLen; i++) {
		SetProgPosInc();
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			// 현제 서버에만 적용이면 
			if (bIsCurrentServerCheck) {
				if (m_pFtp == pFtp) {
					if (!m_pFtp->m_pFtpCon->CreateDirectory(strForderName)) {
						bRet = FALSE;
						WriteLog(_T("[디렉토리생성 실패:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
					}
					else {
						WriteLog(_T("[디렉토리생성:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
					}
					break;
				}
			}
			else {
				if (!m_pFtp->m_pFtpCon->CreateDirectory(strForderName)) {
					bRet = FALSE;
					WriteLog(_T("[디렉토리생성 실패:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
				}
				else {
					WriteLog(_T("[디렉토리생성:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
				}
			}
		}
	}

	m_pFtp = pFtp;
	return bRet;
}


//////////////////////////////////////////////////////////////////////
// Client에 새로운 폴더생성 
void CGlassFTPDlg::OnBtnClientNewforder() 
{
	CForderName FName;
	CString strPath, strForderName;

	if (FName.DoModal() != IDOK)		
		return ;

	if (FName.m_strForderName.IsEmpty())		// 생성할 폴더 이름이 없으면 return
		return ;

	strForderName = m_strClientPath;
	strForderName += (_T("\\") + FName.m_strForderName); 

	TRACE(_T("New Forder : %s"), strForderName);
	if (!::CreateDirectory(strForderName, NULL)) {
		AfxMessageBox(strForderName + _T("을 생성 할수 없습니다. "));
	}

	WriteLog(_T("[디렉토리생성:  Local] ") + strForderName);
	WriteSeparator();

	ClientRefresh();
}


//////////////////////////////////////////////////////////////////////
// Client ListView Control의 Right Button Click : for TrackPopupMenu
void CGlassFTPDlg::OnRclickListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POINT point;

	POSITION pos = m_listClient.GetFirstSelectedItemPosition();
	int nItem = m_listClient.GetNextSelectedItem(pos);

	EditMenuUpdate();

	m_listClient.GetItemPosition(nItem, &point); 
	m_listClient.ClientToScreen(&point); 

	CMenu *pMenu = GetMenu();
	pMenu = pMenu->GetSubMenu(1);

	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y + 20, this);  
	
	*pResult = 0;
}

inline CString CGlassFTPDlg::GetActiveSessionName()
{
	return m_pFtp ? m_pFtp->m_pFtpCon->GetServerName() : _T("");
}

//////////////////////////////////////////////////////////////////////
// Client File Editing
void CGlassFTPDlg::OnEditing() 
{
	UINT uSelecetedCount = m_listClient.GetSelectedCount();
	POSITION pos = m_listClient.GetFirstSelectedItemPosition();

	CString strFileName;
	CString strEditor = GetEditorPathName();
	
	for (int i = 0; i < (int)uSelecetedCount; i++) {
		int nItem = m_listClient.GetNextSelectedItem(pos);

		if (m_listClient.GetItemText(nItem, 1).IsEmpty()) 
			continue;

		strFileName += _T("\"") + m_strClientPath + _T("\\") + m_listClient.GetItemText(nItem, 0) + _T("\" ");
	}	

	::ShellExecute (
		NULL, 
		"open", 
		strEditor, 
		strFileName,
		NULL, 
		SW_SHOW
	);
}

void CGlassFTPDlg::OnExecute() 
{
	UINT uSelecetedCount = m_listClient.GetSelectedCount();
	POSITION pos = m_listClient.GetFirstSelectedItemPosition();

	for (int i = 0; i < (int)uSelecetedCount; i++) {
		int nItem = m_listClient.GetNextSelectedItem(pos);

		if (m_listClient.GetItemText(nItem, 1).IsEmpty()) 
			continue;

		CString strFileName = m_strClientPath + _T("\\") + m_listClient.GetItemText(nItem, 0);

		::ShellExecute (
			NULL, 
			"open", 
			strFileName,  
			NULL,
			NULL, 
			SW_SHOW
		);
	}	
}

//////////////////////////////////////////////////////////////////////
// Option Dialog 
void CGlassFTPDlg::OnOption() 
{
	COptionDlg dlg;
	dlg.DoModal(); 

	SetStatus();	
}


void CGlassFTPDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu *pMenu = GetMenu();
	pMenu = pMenu->GetSubMenu(0);

	ClientToScreen(&point);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y, this);  
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CGlassFTPDlg::OnTimer(UINT_PTR nIDEvent) 
{
	if (ID_TIMER == nIDEvent) {
		// 주기적으로 Refrash
		int nLen = GetServerCount();

		for (int i = 0; i < nLen; i++) {
			CFtp *pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			if (pFtp) {
				BOOL bSuccess = pFtp->SendNOOP();
			}
		}
		WriteLog(_T("[연결유지]"));
	}
	else if (ID_TIMER2 == nIDEvent) {
		SetViewTimer();
	}

	CDialog::OnTimer(nIDEvent);
}

void CGlassFTPDlg::SetViewTimer()
{
	CTime timer = CTime::GetCurrentTime();

	CString szDW[] = {
		CString(_T("일")), CString(_T("월")), CString(_T("화")), CString(_T("수")), 
		CString(_T("목")), CString(_T("금")), CString(_T("토"))
	};

	CString str;
	str.Format(
		_T(" %04d-%02d-%02d %s %02d:%02d:%02d "), 
		timer.GetYear(), timer.GetMonth(), timer.GetDay(), 
		szDW[timer.GetDayOfWeek() - 1], 
		timer.GetHour(), timer.GetMinute(), timer.GetSecond()
	);
	
	SetDlgItemText(IDC_STATIC_TIMER, str);
}


HBRUSH CGlassFTPDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) {
		case CTLCOLOR_LISTBOX :
		case CTLCOLOR_EDIT : 
			pDC->SetTextColor(RGB(0x33,0x00,0x66));
			break;

		case CTLCOLOR_STATIC:
			pDC->SetTextColor(RGB(0x33,0x00,0x66));
			break;

	}

	return hbr;
}

//////////////////////////////////////////////////////////////////////
// 툴팁 메세지를 사용하기 위해 
BOOL CGlassFTPDlg::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTip.RelayEvent(pMsg); 

	CWnd *pFocusWnd = GetFocus(); 

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		if (pFocusWnd == GetDlgItem(IDC_LIST_CLIENT)) {
			DblclkListClient();
		}
		else if (pFocusWnd == GetDlgItem(IDC_LIST_SERVER)) {
			DblclkListServer();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

//////////////////////////////////////////////////////////////////////
// 윈도우 버전 알아내기 
BOOL CGlassFTPDlg::IsWindowsNTVersion()
{
	OSVERSIONINFO osver;

	ZeroMemory(&osver, sizeof(OSVERSIONINFO));
	osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	GetVersionEx(&osver);

	if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT) {
		return TRUE;
	}
	
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// 프로그레시브바 범위 생성 
inline void CGlassFTPDlg::SetProgRange(int nMax)
{
	m_Progress.SetRange32(0, nMax);
}

//////////////////////////////////////////////////////////////////////
// 프로그레시브바 값 세팅 
inline void CGlassFTPDlg::SetProgPos(int nPos /*= 0*/)
{
	m_Progress.SetPos(nPos);
}

inline void CGlassFTPDlg::SetProgPosInc()
{
	m_Progress.SetPos(m_Progress.GetPos() + 1);
}

//////////////////////////////////////////////////////////////////////
// 연결되어 있는 서버개수 
inline int CGlassFTPDlg::GetServerCount()
{
	return m_FtpArray.GetSize(); 
}

//////////////////////////////////////////////////////////////////////
// 선택된 서버에만 업로드, 삭제, 폴더생성 적용 버튼 상태 
BOOL CGlassFTPDlg::IsCurrentServerCheck()
{
	UpdateData();
	return m_bCurrentServer;
}

void CGlassFTPDlg::OnCheckCurrentServer() 
{
	if (IsCurrentServerCheck()) {
		AfxMessageBox(_T("지금부터 파일 업로드및 삭제, 폴더생성은 위의 선택된 한개의 서버에만 적용됩니다 !!"));
	}
	else {
		AfxMessageBox(_T("연결된 모든 서버 적용 !!"));
	}
	SetStatus();
}

void CGlassFTPDlg::SetStatus() 
{
	if (IsCurrentServerCheck()) {
		SetDlgItemText(IDC_STATIC_STATUS, _T("선택된서버적용"));
	}
	else {
		SetDlgItemText(IDC_STATIC_STATUS, _T("모든서버적용"));
	}

	if (GetBackupDirectory().IsEmpty()) {
		SetDlgItemText(IDC_STATIC_STATUS_BACKUP, _T("백업안함"));
	}
	else {
		SetDlgItemText(IDC_STATIC_STATUS_BACKUP, _T("백업모드"));
	}

	m_AutoList.Reset(GetAutoTranListString());
}

DWORD CGlassFTPDlg::GetAutoTransMode(const CString &strFileName)
{
	DWORD dwTrans = 0;
	int nPos = 0;

	switch (m_nTransType) {
		case 0:
			dwTrans = FTP_TRANSFER_TYPE_ASCII;
			break;
		
		case 1:
			dwTrans = FTP_TRANSFER_TYPE_BINARY;
			break;

		case 2:
			nPos = strFileName.ReverseFind(_T('.'));

			if (-1 == nPos) {
				dwTrans = FTP_TRANSFER_TYPE_BINARY;
			}
			else {
				if (m_AutoList.IsExistsAscFile(strFileName.Mid(nPos + 1))) {	// 찾으면 ASCII 모드로 
					dwTrans = FTP_TRANSFER_TYPE_ASCII;
				}
				else {		// 없으면 바이너리로
					dwTrans = FTP_TRANSFER_TYPE_BINARY;
				}
			}
			break;
	}

	return dwTrans; 
}


void CGlassFTPDlg::OnEndlabeleditListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;

	CString strNewName = pDispInfo->item.pszText;
	int nIndex = pDispInfo->item.iItem;
	CString strOldName = m_listClient.GetItemText(nIndex, 0);

	if (!strNewName.IsEmpty()) {
		ReName(strOldName, strNewName);
	}
	
	*pResult = 0;
}

void CGlassFTPDlg::OnBeginlabeleditListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// 하는일 없음 
	*pResult = 0;
}


void CGlassFTPDlg::ReName(const CString &strOldName, const CString &strNewName)
{
	CString strOldPath = m_strClientPath + _T("\\") + strOldName;
	CString strNewPath = m_strClientPath + _T("\\") + strNewName;

	
	if (!::MoveFile(strOldPath, strNewPath)) {
		AfxMessageBox(strOldPath + _T("의 이름을 바꿀수 없습니다. "));
	}

	WriteLog(_T("[이름변경:  Local] ") + strOldName + _T(" -> ") + strNewName);
	WriteSeparator();

	ClientRefresh();
}

void CGlassFTPDlg::ClientEditLabel()
{
	int nIndex = m_listClient.GetSelectionMark(); 
	if (nIndex >= 0) {
		m_listClient.EditLabel(nIndex);	
	}
}

void CGlassFTPDlg::OnRename() 
{
	ClientEditLabel();
}

void CGlassFTPDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
	EditMenuUpdate();
	CDialog::OnMenuSelect(nItemID, nFlags, hSysMenu);
}


void CGlassFTPDlg::EditMenuUpdate()
{
	CMenu *pMenu = GetMenu();
	int nIndex = m_listClient.GetSelectionMark(); 

	CString strFileName = m_listClient.GetItemText(nIndex, 0);	
	CString strFileSize = m_listClient.GetItemText(nIndex, 1);	

	pMenu->EnableMenuItem(IDM_RENAME, MF_GRAYED);
	pMenu->EnableMenuItem(IDM_EDITING, MF_GRAYED);
	pMenu->EnableMenuItem(IDM_EXECUTE, MF_GRAYED);
	pMenu->EnableMenuItem(IDM_DIFF_CLIENT, MF_GRAYED);

	if (nIndex >= 0) {
		pMenu->EnableMenuItem(IDM_RENAME, MF_ENABLED);

		if (!m_listClient.GetItemText(nIndex, 1).IsEmpty()) {
			pMenu->EnableMenuItem(IDM_EDITING, MF_ENABLED);
			pMenu->EnableMenuItem(IDM_EXECUTE, MF_ENABLED);

			if (ListViewFileExists(m_listServer, strFileName)) {
				pMenu->EnableMenuItem(IDM_DIFF_CLIENT, MF_ENABLED);
			}
		}
	}
}

void CGlassFTPDlg::EditMenuUpdateServer()
{
	CMenu *pMenu = GetMenu();
	int nIndex = m_listServer.GetSelectionMark(); 

	CString strFileName = m_listServer.GetItemText(nIndex, 0);		
	CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

	pMenu->EnableMenuItem(IDM_FILEVIEW_SERVER, MF_GRAYED);
	pMenu->EnableMenuItem(IDM_DIFF_SERVER, MF_GRAYED);
	pMenu->EnableMenuItem(IDM_EXECUTE_SERVER, MF_GRAYED);

	if (nIndex >= 0) {
		if (!m_listServer.GetItemText(nIndex, 1).IsEmpty()) {
			pMenu->EnableMenuItem(IDM_FILEVIEW_SERVER, MF_ENABLED);
			pMenu->EnableMenuItem(IDM_EXECUTE_SERVER, MF_ENABLED);

			if (ListViewFileExists(m_listClient, strFileName)) {
				pMenu->EnableMenuItem(IDM_DIFF_SERVER, MF_ENABLED);
			}
		}
	}
}

void CGlassFTPDlg::SetEditClientPath(CString strClientPath)
{

	DWORD dw = GetFileAttributes((LPCTSTR)strClientPath);
	if (INVALID_FILE_ATTRIBUTES == dw) {
		CString s;
		s.Format(_T("잘못된 경로입니다 : %s"), strClientPath);
		AfxMessageBox(s);
		
		return;
	}

	if (!(FILE_ATTRIBUTE_DIRECTORY & dw)) {
		CString s;
		s.Format(_T("디렉토리 경로가 아닙니다 : %s"), strClientPath);
		AfxMessageBox(s);
		
		return;
	}

	SetClientFiles(strClientPath);	
}


CString CGlassFTPDlg::GetFileToTemp()
{
	TCHAR szTempForder[MAX_PATH];
	SHGetSpecialFolderPath(GetSafeHwnd(), szTempForder, CSIDL_INTERNET_CACHE, 0);

	int nIndex = 0;
	POSITION pos;
	UINT uSelectedCount = m_listServer.GetSelectedCount();

	if (!uSelectedCount || !m_pFtp) {
		return _T("");
	}

	pos = m_listServer.GetFirstSelectedItemPosition();
	CString strGetFileName, strClientFileName, strFileList;

	for (int i = 0; i < (int)uSelectedCount; i++) {
		nIndex = m_listServer.GetNextSelectedItem(pos); 

		CString strFileName = m_listServer.GetItemText(nIndex, 0);		
		CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

		m_pFtp->m_pFtpCon->GetCurrentDirectory(strGetFileName);
		
		if (!strFileSize.IsEmpty()) {
			strGetFileName = (strGetFileName.Right(1) == _T("/") ? strGetFileName : strGetFileName + _T("/"));
			strGetFileName += strFileName;

			strClientFileName = szTempForder;
			strClientFileName += _T("\\") + strFileName;

			DWORD dwTransMode = GetAutoTransMode(strFileName);
			
			if (!m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, FALSE, FILE_ATTRIBUTE_NORMAL, dwTransMode)) {
				AfxMessageBox(strGetFileName + _T(" 의 수신이 실패했습니다. "));		
			}

			strFileList += _T("\"") + strClientFileName + _T("\" ");
		}
	}

	CString strEditor = GetEditorPathName();

	::ShellExecute (
		NULL, 
		"open", 
		strEditor, 
		strFileList,
		NULL, 
		SW_SHOW
	);

	return strFileList;
}

void CGlassFTPDlg::OnFileviewServer()
{
	GetFileToTemp();
}

void CGlassFTPDlg::OnNMRclickListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	POINT point;

	POSITION pos = m_listServer.GetFirstSelectedItemPosition();
	int nItem = m_listServer.GetNextSelectedItem(pos);

	EditMenuUpdateServer();

	m_listServer.GetItemPosition(nItem, &point); 
	m_listServer.ClientToScreen(&point); 

	CMenu *pMenu = GetMenu();
	pMenu = pMenu->GetSubMenu(2);

	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN, point.x, point.y + 20, this);  
	
	*pResult = 0;
}

void CGlassFTPDlg::OnDiffServer()
{
	int nIndex = m_listServer.GetSelectionMark();
	if (nIndex < 0) {
		return;
	}

	CString strFileName = m_listServer.GetItemText(nIndex, 0);		
	CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

	if (!strFileSize.IsEmpty()) {
		DiffFile(strFileName);
	}
}



void CGlassFTPDlg::OnExecuteServer()
{
	TCHAR szTempForder[MAX_PATH];
	SHGetSpecialFolderPath(GetSafeHwnd(), szTempForder, CSIDL_INTERNET_CACHE, 0);


	int nIndex = m_listServer.GetSelectionMark();
	if (nIndex < 0) {
		return;
	}

	CString strFileName = m_listServer.GetItemText(nIndex, 0);		

	CString strGetFileName, strClientFileName;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strGetFileName);
	
	strGetFileName = (strGetFileName.Right(1) == _T("/") ? strGetFileName : strGetFileName + _T("/"));
	strGetFileName += strFileName;

	strClientFileName = szTempForder;
	strClientFileName += _T("\\") + strFileName;

	DWORD dwTransMode = GetAutoTransMode(strFileName);
	
	if (!m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, FALSE, FILE_ATTRIBUTE_NORMAL, dwTransMode)) {
		AfxMessageBox(strGetFileName + _T(" 의 수신이 실패했습니다. "));		
	}

	::ShellExecute (
		NULL, 
		"open", 
		strClientFileName, 
		NULL,
		NULL, 
		SW_SHOW
	);
}


void CGlassFTPDlg::DiffFile(const CString &strFileName)
{
	CString strDiffPath = GetDiffPathName();
	if (strDiffPath.IsEmpty()) {
		AfxMessageBox(_T("옵션 메뉴에서 Diff툴 경로를 설정하세요!"));
		return;
	}

	TCHAR szTempForder[MAX_PATH];
	SHGetSpecialFolderPath(GetSafeHwnd(), szTempForder, CSIDL_INTERNET_CACHE, 0);

	CString strGetFileName, strClientFileName, strFileList;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strGetFileName);
	
	strGetFileName = (strGetFileName.Right(1) == _T("/") ? strGetFileName : strGetFileName + _T("/"));
	strGetFileName += strFileName;

	strClientFileName = szTempForder;
	strClientFileName += _T("\\") + strFileName;

	DWORD dwTransMode = GetAutoTransMode(strFileName);
	
	if (!m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, FALSE, FILE_ATTRIBUTE_NORMAL, dwTransMode)) {
		AfxMessageBox(strGetFileName + _T(" 의 수신이 실패했습니다. "));		
	}

	strFileList = _T("\"") + strClientFileName + _T("\" ");
	strFileList += _T("\"") + m_strClientPath + _T("\\") + strFileName + _T("\" ");

	::ShellExecute (
		NULL, 
		"open", 
		strDiffPath, 
		strFileList,
		NULL, 
		SW_SHOW
	);
}

void CGlassFTPDlg::OnDiffClient()
{
	int nIndex = m_listClient.GetSelectionMark();
	if (nIndex < 0) {
		return;
	}

	CString strFileName = m_listClient.GetItemText(nIndex, 0);		
	CString strFileSize = m_listClient.GetItemText(nIndex, 1);		

	if (!strFileSize.IsEmpty()) {
		DiffFile(strFileName);
	}
}


void CGlassFTPDlg::SyncToClientDirectory(const CString &strDirName) 
{
	CButton *pSync = static_cast<CButton *>(GetDlgItem(IDC_PATH_SYNC));

	if (pSync->GetCheck()) {
		if (ListViewFileExists(m_listClient, strDirName) || strDirName == _T("..")) {
			CString strClientPath = m_strClientPath + _T("\\");
			strClientPath += strDirName;

			SetClientFiles(strClientPath);
		}
		else {
			AfxMessageBox(_T("클라이언트 디렉토리 동기화 실패!"));
		}	
	}
}

void CGlassFTPDlg::SyncToServerDirectory(const CString &strDirName) 
{
	CButton *pSync = static_cast<CButton *>(GetDlgItem(IDC_PATH_SYNC));

	if (pSync->GetCheck()) {
		if (ListViewFileExists(m_listServer, strDirName) || strDirName == _T("..")) {
			CString strServerPath;
			m_pFtp->m_pFtpCon->GetCurrentDirectory(strServerPath);

			CString strOldServerPath = strServerPath;

			strServerPath = (strServerPath.Right(1) == _T("/") ? strServerPath : strServerPath + _T("/"));
			strServerPath += strDirName;

			if (!MultiServerMove(strServerPath)) {
				AfxMessageBox(_T("디렉토리 구조가 틀리거나 허가가 되어 있지 않아 이동할 수 없습니다. "));
				MultiServerMove(strOldServerPath);
				return ;
			}
		}
		else {
			AfxMessageBox(_T("서버 디렉토리 동기화 실패!"));
		}	
	}
}

//void CGlassFTPDlg::OnHdnItemchangedListClient(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	
//	static int nCount = 0;
//	++nCount;
//	CString s;
//	s.Format(_T("%d"), nCount);
//	SetDlgItemText(IDC_STATIC_STATUS_CLIENTS, s);
//
//
//	*pResult = 0;
//}

void CGlassFTPDlg::OnNMClickListClient(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int nCount = 0;
	int nIndex = 0;

	UINT uSelectedCount = m_listClient.GetSelectedCount();
	if (!uSelectedCount) {
		SetDlgItemText(IDC_STATIC_STATUS_CLIENTS, _T(""));
		return ;
	}

	POSITION pos = m_listClient.GetFirstSelectedItemPosition();
	
	for (int i = 0; i < (int)uSelectedCount; i++) {
		nIndex = m_listClient.GetNextSelectedItem(pos); 
		CString strFileSize = m_listClient.GetItemText(nIndex, 1);
		if (!strFileSize.IsEmpty()) {
			++nCount;
		}
	}		

	CString sLog;
	sLog.Format(_T("%d개 파일선택"), nCount);
	SetDlgItemText(IDC_STATIC_STATUS_CLIENTS, sLog);

	*pResult = 0;
}

void CGlassFTPDlg::OnNMClickListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nCount = 0;
	int nIndex = 0;

	UINT uSelectedCount = m_listServer.GetSelectedCount();
	if (!uSelectedCount) {
		SetDlgItemText(IDC_STATIC_STATUS_SERVERS, _T(""));
		return ;
	}

	POSITION pos = m_listServer.GetFirstSelectedItemPosition();
	
	for (int i = 0; i < (int)uSelectedCount; i++) {
		nIndex = m_listServer.GetNextSelectedItem(pos); 
		CString strFileSize = m_listServer.GetItemText(nIndex, 1);
		if (!strFileSize.IsEmpty()) {
			++nCount;
		}
	}		

	CString sLog;
	sLog.Format(_T("%d개 파일선택"), nCount);
	SetDlgItemText(IDC_STATIC_STATUS_SERVERS, sLog);

	*pResult = 0;
}
