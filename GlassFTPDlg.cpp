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
	m_pFtp = NULL;								// m_pFtp �ʱ�ȭ 
	
	m_listClient.InitFileList(TRUE);			// m_listClient �ʱ�ȭ 
	m_listServer.InitFileList(FALSE);			// m_listServer �ʱ�ȭ 

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
	m_ToolTip.AddTool(pButton, _T("���� �������� �����ݴϴ�."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_PARENT);
	pButton->SetIcon(imgList.ExtractIcon(1));
	m_ToolTip.AddTool(pButton, _T("���� ���丮 �̵�"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_PARENT);
	pButton->SetIcon(imgList.ExtractIcon(1));
	m_ToolTip.AddTool(pButton, _T("���� ���丮 �̵�"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_PUT);
	pButton->SetIcon(imgList.ExtractIcon(2));
	m_ToolTip.AddTool(pButton, _T("���� ������"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_GET);
	pButton->SetIcon(imgList.ExtractIcon(3));
	m_ToolTip.AddTool(pButton, _T("���� �ޱ�"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_NEWFORDER);
	pButton->SetIcon(imgList.ExtractIcon(4));
	m_ToolTip.AddTool(pButton, _T("�� ���� �����"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_NEWFORDER);
	pButton->SetIcon(imgList.ExtractIcon(4));
	m_ToolTip.AddTool(pButton, _T("�� ���� �����"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_DELETE);
	pButton->SetIcon(imgList.ExtractIcon(5));
	m_ToolTip.AddTool(pButton, _T("������ ������ ����ϴ�."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_DELETE);
	pButton->SetIcon(imgList.ExtractIcon(5));
	m_ToolTip.AddTool(pButton, _T("������ ������ ����ϴ�."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_CLOSE);
	pButton->SetIcon(imgList.ExtractIcon(5));
	m_ToolTip.AddTool(pButton, _T("������ �����ϴ�."));

	pButton = (CButton *)GetDlgItem(IDC_BTN_CLIENT_REFRESH);
	pButton->SetIcon(imgList.ExtractIcon(6));
	m_ToolTip.AddTool(pButton, _T("���� ���丮�� ���ΰ�ħ"));

	pButton = (CButton *)GetDlgItem(IDC_BTN_SERVER_REFRESH);
	pButton->SetIcon(imgList.ExtractIcon(6));
	m_ToolTip.AddTool(pButton, _T("���� ���丮�� ���ΰ�ħ"));

	m_ToolTip.AddTool(GetDlgItem(IDC_RADIO_FILE_TRANS_ASC), _T("�ƽ�Ű ���� ������ �ۼ��� �մϴ�."));
	m_ToolTip.AddTool(GetDlgItem(IDC_RADIO_FILE_TRANS_BIN), _T("���̳ʸ� ���� ������ �ۼ��� �մϴ�."));
	m_ToolTip.AddTool(GetDlgItem(IDC_RADIO_FILE_TRANS_AUTO), _T("�ڵ� ���� ������ �ۼ��� �մϴ�."));

	m_ToolTip.AddTool(&m_comboServerPath, _T("���� ���丮�̵��� �����丮�� ���� �մϴ�."));
	m_ToolTip.AddTool(&m_comboServer, _T("����� ���� ���"));

	m_ToolTip.AddTool(&m_listClient, _T("����ǻ�� ���ϸ��"));
	m_ToolTip.AddTool(&m_listServer, _T("������ ������ ���ϸ��"));

	m_ToolTip.AddTool(GetDlgItem(IDC_EDIT_LOG), _T("�۾� �α�"));
	
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
// ���ΰ�ħ �ð� ����
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
// Editor ��� �������� 
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
// Diff ��� �������� 
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
// ���� ���丮�� ����Ʈ�� 
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
// ����Ʈ Ŭ���̾�Ʈ ���丮��� ��������  
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
// ����Ʈ Ŭ���̾�Ʈ ���丮��� ��������  
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
// ���� ���� ���� ���� �������� 
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
// ���۸�� ���� �������� 
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
// ���۸�� �����ϱ� 
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
// �ڵ����۸�� ���� Ȯ���� �������� 
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
// ListView Control�� Client���� Setting
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
// ListView Control�� Server���� Setting
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
	
	// Ȱ��ȭ�� �����̸� �ش� ������ū ������ ������ 
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
// DblClick - Client �����̵� 
void CGlassFTPDlg::OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DblclkListClient();
	*pResult = 0;
}


//////////////////////////////////////////////////////////////////////
// DblClick - Client �����̵� 
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
// Server Path�� �̵� 
void CGlassFTPDlg::DirectMoveServerPath(const CString &strServerPath)
{
	if (!m_pFtp) {
		return ;
	}

	CString strOldServerPath;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strOldServerPath);
	
	if (!MultiServerMove(strServerPath)) {
		AfxMessageBox(_T("���丮 ������ Ʋ���ų� �㰡�� �Ǿ� ���� �ʾ� �̵��� �� �����ϴ�. "));
		MultiServerMove(strOldServerPath);

		return ;
	}
}

//////////////////////////////////////////////////////////////////////
// Server Path Combo���� ��θ� ��å�� ��� 
void CGlassFTPDlg::OnSelchangeComboServerPath() 
{
	CString strServerPath;
	m_comboServerPath.GetLBText(m_comboServerPath.GetCurSel(), strServerPath);
	
	DirectMoveServerPath(strServerPath);
}

//////////////////////////////////////////////////////////////////////
// DblClick - Server �����̵� 
void CGlassFTPDlg::OnDblclkListServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DblclkListServer();
	*pResult = 0;
}


//////////////////////////////////////////////////////////////////////
// DblClick - Server �����̵� 
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
			AfxMessageBox(_T("���丮 ������ Ʋ���ų� �㰡�� �Ǿ� ���� �ʾ� �̵��� �� �����ϴ�. "));
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
// ���� Server �����̵� 
BOOL CGlassFTPDlg::MultiServerMove(CString strServerPath)
{
	// ���� Ȱ��ȭ ���� ���� 
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	CString strMsg = _T(" ���丮 �̵��� : ");
	strMsg += strServerPath;
	strMsg += _T("         ");		// �ܻ��� ���ֱ� ���� 
	m_comboServerPath.SetWindowText(strMsg); 

	// m_comboServerPath �� �޼����� ǥ���ϱ� ���� 
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
// Server Path Combo�� �̵��� ��� �߰� - HISTORY �߰� 
void CGlassFTPDlg::InsertServerPath()
{
	CString strServerPath;
	m_pFtp->m_pFtpCon->GetCurrentDirectory(strServerPath);

	int nFindIndex = m_comboServerPath.FindStringExact(0, strServerPath);

	// ������ �����丮���� ���ڿ��� ã���� ����� 
	if (CB_ERR != nFindIndex) {
		m_comboServerPath.DeleteString(nFindIndex);	
	}
	
	// ���� ��θ� �Ǿտ� �����ϰ� Ŀ���� �Ǿճ�忡 ��ġ 
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
// SHBrowseForFolder ���� 
BOOL CGlassFTPDlg::GetSHBF(CString &strPath)
{
	TCHAR szDir[SZ_SIZE + 1];
	
	BROWSEINFO bi;
	ZeroMemory(reinterpret_cast<LPVOID>(&bi), sizeof(BROWSEINFO));

	bi.hwndOwner = m_hWnd;
	bi.lpszTitle  = "������ �̵��մϴ�.  ";
	
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&bi);
	if (!pidl) {
		return FALSE;
	}

	::SHGetPathFromIDList(pidl, szDir); 

	strPath = szDir;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Client ���� ���丮�� ...
void CGlassFTPDlg::OnBtnClientParent() 
{
	SetClientFiles(m_strClientPath + _T("\\.."));
	SyncToServerDirectory(_T(".."));
}

//////////////////////////////////////////////////////////////////////
// Server ���� ���丮�� ...
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
		if (IDOK != AfxMessageBox(_T("�̹� ������ ����Ǿ� �ֽ��ϴ�. \n\n������ ���� �ٽ� ���� �Ͻðڽ��ϱ�?"), MB_OKCANCEL)) {
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

	// �������� ������ Ŭ���̾�Ʈ �⺻ ��� ���� 
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
				int nResult = AfxMessageBox(strConIP + _T(" : ������ ���� �߽��ϴ�. \n\n��� ���� �Ͻðڽ��ϱ�? "), MB_YESNO);
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

				pThis->WriteLog(_T("[���ǿ���]  ") + pThis->GetActiveSessionName());
			}
			else {
				pThis->WriteLog(_T("[���ǿ���]  ") + strConIP + _T(" [����]"));
			}
		}
	}
	
	if (pThis->m_FtpArray.GetSize() == 0) {
		AfxMessageBox(_T("����� ������ �����ϴ�."));
		return 0L;
	}

	// ���丮 �̵� �����丮�� �߰� 
	pThis->InsertServerPath();
	
	pThis->UpdateServerList();		// List Control Update 
	pThis->SetTimer(ID_TIMER, pThis->GetInterval(), NULL);

	CMenu *pMenu = pThis->GetMenu();
	pMenu->EnableMenuItem(IDM_CLOSEALL, MF_ENABLED);	// Menu [Close] Enaable

	pThis->WriteLog(_T("[���ǿ���] �Ϸ� �Ǿ����ϴ�. !!"));
	pThis->WriteSeparator();
	
	pThis->SetProgPos();

	// 2003/07/03
	// �߰� : ����ٿ� ����Ʈ�� �����ش� 
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
// ���� ���� 
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
			strTransMode = _T("�ƽ�Ű ���");
		}
		else {
			strTransMode = _T("���̳ʸ� ���");
		}

		pThis->WriteLog(_T("[���ϼ���] ") + strTransMode + _T(" ���ſϷ� !!"));
*/
	}
	catch (...) {
		AfxMessageBox(_T("�ý��� ���� !!"));
	}

	// �ۼ��� ��ư�� Enable ��Ų�� 
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

			bFileExists = ListViewFileExists(m_listClient, strFileName);			// ������ ���� �ϸ� 

			if (bFileExists && (!m_bIDOKALL)) {
				int nMessageBox = CMessageDlg::MessageBox(strFileName + _T(" �� �����մϴ�. \n\n ���� ���ðڽ��ϱ� ?")); 

				if (nMessageBox == IDCANCEL) {
					continue ;
				}
				else if (nMessageBox == CMessageDlg::IDOK_ALL) {
					m_bIDOKALL = TRUE;
				}
			}

			DWORD dwTransMode = GetAutoTransMode(strFileName);
			
			if (!m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, !bFileExists, FILE_ATTRIBUTE_NORMAL, dwTransMode)) {
				AfxMessageBox(strGetFileName + _T(" �� ������ �����߽��ϴ�. "));		
			}

			CString strBackup = GetBackupDirectory();
			// Backup Mode�̸� Backup ���� 
			if (!strBackup.IsEmpty()) {
				CreateDirectory(m_strClientPath + _T("\\") + strBackup, NULL);
				strClientFileName = m_strClientPath + _T("\\") + strBackup + _T("\\") + strFileName;
				m_pFtp->m_pFtpCon->GetFile(strGetFileName, strClientFileName, !bFileExists, FILE_ATTRIBUTE_NORMAL, dwTransMode);
			}

			// Write log
			CString strServerName;
			strServerName.Format(_T("[���ϼ���: %s][%s] %s"), 
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
// �ۼ��� ��ư�� �����Ѵ� 
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
// ���� �۽�
void CGlassFTPDlg::OnBtnPut() 
{
	AfxBeginThread(MultiServerPutFiles, reinterpret_cast<LPVOID>(this));
}

UINT CGlassFTPDlg::MultiServerPutFiles(LPVOID lpvParam)
{
	CGlassFTPDlg *pThis = reinterpret_cast<CGlassFTPDlg *>(lpvParam);

	try {
		// �ۼ��� ��ư�� Disable ��Ų�� 
		pThis->EnableSendRecv(FALSE);
		
		// Ȱ��ȭ�� ���� �ε��� ��� 
		const int nIndex = pThis->SearchFtp(pThis->m_pFtp);

		if (nIndex == -1) {
			pThis->EnableSendRecv(TRUE);
			return 0L;
		}

		int nServerCount = 0;

		// ���� �������� �����̸� 
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

		// ���� �������� �����̸� 
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

		pThis->WriteLog(_T("[���ϼ۽�] �۽ſϷ� !!"));
		pThis->WriteSeparator();

	}
	catch (...) {
		AfxMessageBox(_T("�ý��� ���� !!"));
	}

	// �ۼ��� ��ư�� Enable ��Ų�� 
	pThis->EnableSendRecv(TRUE);
	pThis->SetProgPos();

	return 0L;
}


//////////////////////////////////////////////////////////////////////
// Ȱ��ȭ�� ������ ������ ������ �ø��� 
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

			bFileExists = ListViewFileExists(m_listServer, strFileName);			// ������ ���� �ϸ� 

			if (bFileExists && (!m_bIDOKALL)) {
				int nMessageBox = CMessageDlg::MessageBox(strFileName + _T(" �� �����մϴ�. \n\n ���� ���ðڽ��ϱ� ?")); 

				if (nMessageBox == IDCANCEL) {
					continue ;
				}
				else if (nMessageBox == CMessageDlg::IDOK_ALL) {
					m_bIDOKALL = TRUE;
				}
			}

			DWORD dwTransMode = GetAutoTransMode(strFileName);
			
			if (!ServerPutFile(strPutFileName, strFileName,  dwTransMode)) {
				AfxMessageBox(strPutFileName + _T(" �� �۽��� �����߽��ϴ�. "));	
			}

			// Write log
			CString strServerName;
			strServerName.Format(_T("[���ϼ۽�: %s][%s] %s"), 
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
// �������� ������ ���� �۽� 
BOOL CGlassFTPDlg::ServerPutFile(CString strLocalFile, CString strRemoteFile, DWORD dwFlag)
{
	BOOL bRet = TRUE;;

	// 2006.09.06 by cdecl
	// �ʿ���� ���� ���� 
	// �� ������ �������� ���ٴ�.
	//m_pFtp->m_pFtpCon->Remove(strRemoteFile);	// ������ ������ ���� ����� 

	if (!m_pFtp->m_pFtpCon->PutFile(strLocalFile, strRemoteFile, dwFlag)) {
		bRet = FALSE;
	}

	return bRet;
}


//////////////////////////////////////////////////////////////////////
// Server ListView Control ���� 
void CGlassFTPDlg::ServerRefresh()
{
	CString strServerPath;

	if (m_pFtp) {
		m_pFtp->m_pFtpCon->GetCurrentDirectory(strServerPath);
	}

	SetServerFiles(strServerPath, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Client ListView Control ���� 
void CGlassFTPDlg::ClientRefresh()
{
	SetClientFiles(m_strClientPath);
}

//////////////////////////////////////////////////////////////////////
// Server ListView Control ���� : Button
void CGlassFTPDlg::OnBtnServerRefresh() 
{
	ServerRefresh();
}

//////////////////////////////////////////////////////////////////////
// Client ListView Control ���� : Button
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
	
	CString strLine = _T("��������������������������������������������������������������������������������������������������������������������\r\n");
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
// �α� �����
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
		AfxMessageBox(_T("�ý��� ���� !!"));
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

	strMsgBox.Format(_T("%u ���� �׸��� �����Ͻðڽ��ϱ� ?"), uSelectedCount);
	if (AfxMessageBox(strMsgBox, MB_OKCANCEL) == IDCANCEL) 
		return ;

	pos = m_listServer.GetFirstSelectedItemPosition();
	SetProgRange(uSelectedCount * GetServerCount());

	for (int i = 0; i < (int)uSelectedCount; i++) {
		nIndex = m_listServer.GetNextSelectedItem(pos); 

		CString strFileName = m_listServer.GetItemText(nIndex, 0);		
		CString strFileSize = m_listServer.GetItemText(nIndex, 1);		

		if (!strFileSize.IsEmpty()) {		// �����̸� 
			if (!MultiServerRemove(strFileName)) {
				AfxMessageBox(strFileName + _T(" ���� ���� ���� !! - �Ѱ� �̻��� �������� ������ �߻��Ͽ����ϴ�."));	
			}

			WriteLog(_T("[���ϻ���]  ���ϻ��� �Ϸ� !!"));
		}
		else {								// ���丮�� 
			if (!MultiServerRemoveDir(strFileName)) {
				AfxMessageBox(strFileName + _T(" ���丮 ���� ���� !! - �Ѱ� �̻��� �������� ������ �߻��Ͽ����ϴ�."));	
			}

			WriteLog(_T("[���丮����]  ���丮���� �Ϸ� !!"));
		}

		WriteSeparator();
	}		

	ServerRefresh();
	SetProgPos();
}

//////////////////////////////////////////////////////////////////////
// �������� ���� ���� ���� 
BOOL CGlassFTPDlg::MultiServerRemove(CString strFileName)
{
	BOOL bRet = TRUE;;
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	// ���� �������� �����̸� 
	BOOL bIsCurrentServerCheck = IsCurrentServerCheck();
		
	for (int i = 0; i < nLen; i++) {
		SetProgPosInc();
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	
			
			// ���� �������� �����̸� 
			if (bIsCurrentServerCheck) {
				if (m_pFtp == pFtp) {
					if (!m_pFtp->m_pFtpCon->Remove(strFileName)) {
						bRet = FALSE;
						WriteLog(_T("[���ϻ��� ����:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					else {
						WriteLog(_T("[���ϻ���:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					break;
				}
			}
			else {
				if (!m_pFtp->m_pFtpCon->Remove(strFileName)) {
					bRet = FALSE;
					WriteLog(_T("[���ϻ��� ����:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
				else {
					WriteLog(_T("[���ϻ���:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
			}
		}
	}

	m_pFtp = pFtp;
	return bRet;
}


//////////////////////////////////////////////////////////////////////
// �������� ���� ���丮 ���� 
BOOL CGlassFTPDlg::MultiServerRemoveDir(CString strFileName)
{
	BOOL bRet = TRUE;;
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	// ���� �������� �����̸� 
	BOOL bIsCurrentServerCheck = IsCurrentServerCheck();

	for (int i = 0; i < nLen; i++) {
		SetProgPosInc();
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			// ���� �������� �����̸� 
			if (bIsCurrentServerCheck) {
				if (m_pFtp == pFtp) {
					if (!m_pFtp->m_pFtpCon->RemoveDirectory(strFileName)) {
						bRet = FALSE;
						WriteLog(_T("[���丮���� ����:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					else {
						WriteLog(_T("[���丮����:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
					}
					break;
				}
			}
			else {	
				if (!m_pFtp->m_pFtpCon->RemoveDirectory(strFileName)) {
					bRet = FALSE;
					WriteLog(_T("[���丮���� ����:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
				}
				else {
					WriteLog(_T("[���丮����:  ") + this->GetActiveSessionName() + _T("] ") + strFileName);
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

	strMsgBox.Format(_T("%u ���� �׸��� �����Ͻðڽ��ϱ� ?"), uSelectedCount);
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

		if (!strFileSize.IsEmpty()) {		// �����̸� 
			if (!::DeleteFile(strFileName)) {
				AfxMessageBox(strFileName + _T(" ���� ���� ���� !! "));	
			}

			WriteLog(_T("[���ϻ���:  Local] ") + strFileName);
		}
		else {								// ���丮�� 
			if (!::RemoveDirectory(strFileName)) {
				AfxMessageBox(strFileName + _T(" ���丮 ���� ���� !! "));	
			}

			WriteLog(_T("[���丮����:  Local] ") + strFileName);
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
// Client ListView Control ���� ������ ���翩�� �˻� 
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
// Server�� �����ִ� List Control ���� ������ ���翩�� �˻� 
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
			strServerName.Format(_T("[%03d:] %s "), i + 1, _T("�������"));
		}
		m_comboServer.AddString(strServerName); 
	}
	
	SetActiveServer(0);
}

//////////////////////////////////////////////////////////////////////
// ListBox���� ������ ������ Active�ȴ� 
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
// ListBox���� �����ϸ� 
inline void CGlassFTPDlg::OnSelchangeComboServer() 
{
	SetActiveServer(m_comboServer.GetCurSel()); 
}

//////////////////////////////////////////////////////////////////////
// �����찡	Destroy�ɶ� �޸� ���� 
BOOL CGlassFTPDlg::DestroyWindow() 
{
	UpdateData(TRUE);
	SetTransMode(static_cast<UINT>(m_nTransType));

	ReleaseAll();

	return CDialog::DestroyWindow();
}

//////////////////////////////////////////////////////////////////////
// ��� Session�� �ݴ´� 
void CGlassFTPDlg::OnCloseall() 
{
	CloseAll();
}

//////////////////////////////////////////////////////////////////////
// ��� Session�� �ݴ´� 
void CGlassFTPDlg::CloseAll(BOOL bAskMsg)
{
	if (bAskMsg) {
		if (AfxMessageBox(_T("������ ��� ������ ���� �Ͻðڽ��ϱ� ?"), MB_OKCANCEL) == IDCANCEL) {
			return ;
		}
	}

	ReleaseAll();
	UpdateServerList();

	// ���� �̵� �����丮�� ����� 
	m_comboServerPath.ResetContent();

	CMenu *pMenu = GetMenu();
	pMenu->EnableMenuItem(IDM_CLOSEALL, MF_GRAYED);	// Menu [Close] Enaable

	WriteLog(_T("[���ǲ���] ������ ������ �������ϴ�."));
	WriteSeparator();
}


//////////////////////////////////////////////////////////////////////
// CFtp ��ü�� Index�� ã�� index�� return �Ѵ� 
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
// Server�� ���ο� �������� 
void CGlassFTPDlg::OnBtnServerNewforder() 
{
	CForderName FName;
	CString strForderName;

	if (!m_pFtp)							// ����� ������ ������ return 
		return ;

	if (FName.DoModal() != IDOK)			
		return ;

	if (FName.m_strForderName.IsEmpty())	// ������ ���� �̸��� ������ return
		return ;

	m_pFtp->m_pFtpCon->GetCurrentDirectory(strForderName);
	strForderName += (_T("/") + FName.m_strForderName); 
	
	SetProgRange(GetServerCount());
	if (!MultiServerNewForder(strForderName)) {
		AfxMessageBox(strForderName + _T(" ���丮�� ���� �Ҽ� �����ϴ�. - �Ѱ� �̻��� �������� ������ �߻��Ͽ����ϴ�."));
	}

	WriteLog(_T("[���丮����]  ���丮���� �Ϸ� !!"));
	WriteSeparator();

	ServerRefresh();
	SetProgPos();
}


//////////////////////////////////////////////////////////////////////
// �������� Server�� ���ο� �������� 
BOOL CGlassFTPDlg::MultiServerNewForder(CString strForderName)
{
	BOOL bRet = TRUE;;
	CFtp *pFtp = m_pFtp;
	int nLen = GetServerCount();

	// ���� �������� �����̸� 
	BOOL bIsCurrentServerCheck = IsCurrentServerCheck();

	for (int i = 0; i < nLen; i++) {
		SetProgPosInc();
		if (m_FtpArray.GetAt(i)) {
			m_pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			// ���� �������� �����̸� 
			if (bIsCurrentServerCheck) {
				if (m_pFtp == pFtp) {
					if (!m_pFtp->m_pFtpCon->CreateDirectory(strForderName)) {
						bRet = FALSE;
						WriteLog(_T("[���丮���� ����:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
					}
					else {
						WriteLog(_T("[���丮����:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
					}
					break;
				}
			}
			else {
				if (!m_pFtp->m_pFtpCon->CreateDirectory(strForderName)) {
					bRet = FALSE;
					WriteLog(_T("[���丮���� ����:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
				}
				else {
					WriteLog(_T("[���丮����:  ") + this->GetActiveSessionName() + _T("] ") + strForderName);
				}
			}
		}
	}

	m_pFtp = pFtp;
	return bRet;
}


//////////////////////////////////////////////////////////////////////
// Client�� ���ο� �������� 
void CGlassFTPDlg::OnBtnClientNewforder() 
{
	CForderName FName;
	CString strPath, strForderName;

	if (FName.DoModal() != IDOK)		
		return ;

	if (FName.m_strForderName.IsEmpty())		// ������ ���� �̸��� ������ return
		return ;

	strForderName = m_strClientPath;
	strForderName += (_T("\\") + FName.m_strForderName); 

	TRACE(_T("New Forder : %s"), strForderName);
	if (!::CreateDirectory(strForderName, NULL)) {
		AfxMessageBox(strForderName + _T("�� ���� �Ҽ� �����ϴ�. "));
	}

	WriteLog(_T("[���丮����:  Local] ") + strForderName);
	WriteSeparator();

	ClientRefresh();
}


//////////////////////////////////////////////////////////////////////
// Client ListView Control�� Right Button Click : for TrackPopupMenu
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
		// �ֱ������� Refrash
		int nLen = GetServerCount();

		for (int i = 0; i < nLen; i++) {
			CFtp *pFtp = reinterpret_cast<CFtp *>(m_FtpArray.GetAt(i));	

			if (pFtp) {
				BOOL bSuccess = pFtp->SendNOOP();
			}
		}
		WriteLog(_T("[��������]"));
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
		CString(_T("��")), CString(_T("��")), CString(_T("ȭ")), CString(_T("��")), 
		CString(_T("��")), CString(_T("��")), CString(_T("��"))
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
// ���� �޼����� ����ϱ� ���� 
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
// ������ ���� �˾Ƴ��� 
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
// ���α׷��ú�� ���� ���� 
inline void CGlassFTPDlg::SetProgRange(int nMax)
{
	m_Progress.SetRange32(0, nMax);
}

//////////////////////////////////////////////////////////////////////
// ���α׷��ú�� �� ���� 
inline void CGlassFTPDlg::SetProgPos(int nPos /*= 0*/)
{
	m_Progress.SetPos(nPos);
}

inline void CGlassFTPDlg::SetProgPosInc()
{
	m_Progress.SetPos(m_Progress.GetPos() + 1);
}

//////////////////////////////////////////////////////////////////////
// ����Ǿ� �ִ� �������� 
inline int CGlassFTPDlg::GetServerCount()
{
	return m_FtpArray.GetSize(); 
}

//////////////////////////////////////////////////////////////////////
// ���õ� �������� ���ε�, ����, �������� ���� ��ư ���� 
BOOL CGlassFTPDlg::IsCurrentServerCheck()
{
	UpdateData();
	return m_bCurrentServer;
}

void CGlassFTPDlg::OnCheckCurrentServer() 
{
	if (IsCurrentServerCheck()) {
		AfxMessageBox(_T("���ݺ��� ���� ���ε�� ����, ���������� ���� ���õ� �Ѱ��� �������� ����˴ϴ� !!"));
	}
	else {
		AfxMessageBox(_T("����� ��� ���� ���� !!"));
	}
	SetStatus();
}

void CGlassFTPDlg::SetStatus() 
{
	if (IsCurrentServerCheck()) {
		SetDlgItemText(IDC_STATIC_STATUS, _T("���õȼ�������"));
	}
	else {
		SetDlgItemText(IDC_STATIC_STATUS, _T("��缭������"));
	}

	if (GetBackupDirectory().IsEmpty()) {
		SetDlgItemText(IDC_STATIC_STATUS_BACKUP, _T("�������"));
	}
	else {
		SetDlgItemText(IDC_STATIC_STATUS_BACKUP, _T("������"));
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
				if (m_AutoList.IsExistsAscFile(strFileName.Mid(nPos + 1))) {	// ã���� ASCII ���� 
					dwTrans = FTP_TRANSFER_TYPE_ASCII;
				}
				else {		// ������ ���̳ʸ���
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
	// �ϴ��� ���� 
	*pResult = 0;
}


void CGlassFTPDlg::ReName(const CString &strOldName, const CString &strNewName)
{
	CString strOldPath = m_strClientPath + _T("\\") + strOldName;
	CString strNewPath = m_strClientPath + _T("\\") + strNewName;

	
	if (!::MoveFile(strOldPath, strNewPath)) {
		AfxMessageBox(strOldPath + _T("�� �̸��� �ٲܼ� �����ϴ�. "));
	}

	WriteLog(_T("[�̸�����:  Local] ") + strOldName + _T(" -> ") + strNewName);
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
		s.Format(_T("�߸��� ����Դϴ� : %s"), strClientPath);
		AfxMessageBox(s);
		
		return;
	}

	if (!(FILE_ATTRIBUTE_DIRECTORY & dw)) {
		CString s;
		s.Format(_T("���丮 ��ΰ� �ƴմϴ� : %s"), strClientPath);
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
				AfxMessageBox(strGetFileName + _T(" �� ������ �����߽��ϴ�. "));		
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
		AfxMessageBox(strGetFileName + _T(" �� ������ �����߽��ϴ�. "));		
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
		AfxMessageBox(_T("�ɼ� �޴����� Diff�� ��θ� �����ϼ���!"));
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
		AfxMessageBox(strGetFileName + _T(" �� ������ �����߽��ϴ�. "));		
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
			AfxMessageBox(_T("Ŭ���̾�Ʈ ���丮 ����ȭ ����!"));
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
				AfxMessageBox(_T("���丮 ������ Ʋ���ų� �㰡�� �Ǿ� ���� �ʾ� �̵��� �� �����ϴ�. "));
				MultiServerMove(strOldServerPath);
				return ;
			}
		}
		else {
			AfxMessageBox(_T("���� ���丮 ����ȭ ����!"));
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
	sLog.Format(_T("%d�� ���ϼ���"), nCount);
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
	sLog.Format(_T("%d�� ���ϼ���"), nCount);
	SetDlgItemText(IDC_STATIC_STATUS_SERVERS, sLog);

	*pResult = 0;
}
