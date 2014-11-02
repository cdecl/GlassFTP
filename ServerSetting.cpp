// ServerSetting.cpp : implementation file
//

#include "stdafx.h"
#include "glassftp.h"
#include "ServerSetting.h"

#include "OptionDlg.h"

static const TCHAR F_DELIMITER		= (TCHAR)27;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSetting dialog


CServerSetting::CServerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CServerSetting::IDD, pParent)

	, m_nPassive(0)
{
	//{{AFX_DATA_INIT(CServerSetting)
	m_strDefaultPath = _T("");
	m_strID = _T("");
	m_strIP = _T("");
	m_strName = _T("");
	m_strPassword = _T("");
	m_uPort = 21;
	m_strDefaultClientPath = _T("");
	//}}AFX_DATA_INIT


	strFileHeader = _T("Ver3");
	m_nSelectIndex = -1;


	TCHAR sz[COptionDlg::SZ_SIZE + 1];

	::GetPrivateProfileString (
			NS_Config::SECTION,
			_T("ServerConfig"), 
			_T("GlassFTP.dat"), 
			sz,
			COptionDlg::SZ_SIZE,
			NS_Config::INI_FILENAME
	);
	SetDlgItemText(IDC_EDIT_FILEPATH_CONFIG, sz);

	strSettingFile = sz;
	
}


void CServerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerSetting)
	DDX_Control(pDX, IDC_LIST_SERVER, m_listServer);
	DDX_Text(pDX, IDC_EDIT_DEFAULT_PATH, m_strDefaultPath);
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uPort);
	DDX_Text(pDX, IDC_EDIT_DEFAULT_PATH_CLIENT, m_strDefaultClientPath);
	//}}AFX_DATA_MAP
	DDX_Radio(pDX, IDC_RADIO_MODE_ACTIVE, m_nPassive);
}


BEGIN_MESSAGE_MAP(CServerSetting, CDialog)
	//{{AFX_MSG_MAP(CServerSetting)
	ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
	ON_BN_CLICKED(IDC_BTN_OPEN, OnBtnOpen)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_LIST_SERVER, OnSelchangeListServer)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_LBN_DBLCLK(IDC_LIST_SERVER, OnDblclkListServer)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_CHECK_SELECT_CLIENTPATH, OnCheckSelectClientpath)
	ON_BN_CLICKED(IDC_BTN_SELECT_CLIENT_PATH, OnBtnSelectClientPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerSetting message handlers

BOOL CServerSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetSettingData();
	OnCheckSelectClientpath();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//////////////////////////////////////////////////////////////////////
// Data ���Ͽ��� ������ ������ �����´� 
void CServerSetting::GetSettingData()
{
	CStdioFile File;
	TServer2 TS2;
	TServer3 TS3;
	char sz[10];

	m_listServer.ResetContent();
	Release();

	if (File.Open(strSettingFile, CFile::modeRead | CFile::typeBinary)) {
		int nSize = strFileHeader.GetLength();

		File.Read(sz, nSize);
		sz[nSize] = NULL;


		// ������ ���� Ver 3 �̸� 
		if (CString(sz) == strFileHeader) {
			while (File.Read(&TS3, sizeof(TServer3))) {
				SetDecoding(&TS3);

				TServer3 *pTS = new TServer3;
				CopyData(pTS, &TS3);

				m_listServer.AddString(pTS->szName);
				m_arrServer.Add(reinterpret_cast<LPVOID>(pTS));
			}				
		}
		// ������ ���� Ver 2 �̸� 
		else if (CString(sz) == _T("Ver2")) {
			while (File.Read(&TS2, sizeof(TServer2))) {
				SetDecoding(&TS2);

				TServer3 *pTS = new TServer3;
				CopyData(pTS, &TS2);

				m_listServer.AddString(pTS->szName);
				m_arrServer.Add(reinterpret_cast<LPVOID>(pTS));
			}				
		}

		File.Close();
	}
}

//////////////////////////////////////////////////////////////////////
// ���ο� �׸� 
void CServerSetting::OnBtnNew() 
{
	m_nSelectIndex = -1;
	Clear();
}

//////////////////////////////////////////////////////////////////////
// ���� �ϱ� 
void CServerSetting::OnBtnOpen() 
{
	UpdateData(TRUE);
	EndDialog(IDOK);
}

//////////////////////////////////////////////////////////////////////
// �ݱ� 
void CServerSetting::OnBtnExit() 
{
	EndDialog(IDCANCEL);
}

//////////////////////////////////////////////////////////////////////
// �����ϱ� 
void CServerSetting::OnBtnSave() 
{
	TServer3 TS;
	ZeroMemory(&TS, sizeof(TServer3));

	CStdioFile File;
	File.Open(strSettingFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	int nCount = m_arrServer.GetSize(); 

	File.Write((LPCSTR)strFileHeader, strFileHeader.GetLength());

	for (int i = 0; i < nCount; i++) {
		if (i == m_nSelectIndex) {
			GetView(&TS);
			SetEncoding(&TS);
			File.Write(&TS, sizeof(TServer3));
		}
		else {
			SetEncoding((TServer3 *)m_arrServer[i]);
			File.Write(((TServer3 *)m_arrServer[i]), sizeof(TServer3));
		}
	}

	if (m_nSelectIndex < 0) {			// ���� �׸� ����� 
		GetView(&TS);
		SetEncoding(&TS);
		File.Write(&TS, sizeof(TServer3));
	}

	File.Close();

	if (m_nSelectIndex == -1) {
		m_nSelectIndex = m_arrServer.GetSize();
	}

	GetSettingData();
}

//////////////////////////////////////////////////////////////////////
// �����׸��� �����ش� 
void CServerSetting::SetView(TServer3 *pServer)
{
	m_strName = pServer->szName; 
	m_strIP = pServer->szIP; 
	m_strID = pServer->szID;
	m_uPort = pServer->wPort;
	m_strPassword = pServer->szPassword;
	m_nPassive = pServer->nPassive;

	CString strPath = pServer->szDefaultPath; 
	const int nPos = strPath.Find(F_DELIMITER);

	SetClientPathCheck(nPos == -1 ? FALSE : TRUE);

	if (nPos == -1) {
		m_strDefaultPath = strPath; 
	}
	else {
		m_strDefaultPath = strPath.Left(nPos);
		m_strDefaultClientPath = strPath.Mid(nPos + 1);
	}

	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////
// ���̴� �����׸��� �����´� 
void CServerSetting::GetView(TServer3 *pServer)
{
	UpdateData(TRUE);

	lstrcpy(pServer->szName, m_strName); 
	lstrcpy(pServer->szIP, m_strIP);
	pServer->wPort = m_uPort;
	lstrcpy(pServer->szID, m_strID);
	lstrcpy(pServer->szPassword, m_strPassword);
	pServer->nPassive = m_nPassive;

	//////////////////////////////////////////////////////////////////
	// modify - 2003/01/25
	// ���� �⺻ ��� ������ ���� 
	// ���� �⺻ ��ο� �߰��ϸ� ���� �⺻ ��ο� F_DELIMITER(Ascii:27)�� ������ �����δ�
	CString strPath = m_strDefaultPath;
	if (IsGetCheckedClientPath() && !m_strDefaultClientPath.IsEmpty()) {
		strPath += F_DELIMITER;
		strPath += m_strDefaultClientPath;
	}

	lstrcpy(pServer->szDefaultPath, strPath); 
}

//////////////////////////////////////////////////////////////////////
// Control Clear
void CServerSetting::Clear()
{
	TServer3 TS;
	ZeroMemory(&TS, sizeof(TServer3));
	TS.wPort = 21;

	SetView(&TS);
}

//////////////////////////////////////////////////////////////////////
// �����찡 ���϶� Free Memory
void CServerSetting::OnDestroy() 
{
	Release();

	CDialog::OnDestroy();	
}

//////////////////////////////////////////////////////////////////////
// Free Memory
void CServerSetting::Release()
{
	int nCount = m_arrServer.GetSize(); 

	for (int i = 0; i < nCount; i++) {
		delete (TServer3 *)m_arrServer.GetAt(0);
		m_arrServer.RemoveAt(0); 	
	}
}


//////////////////////////////////////////////////////////////////////
// ����ü �����͸� ī���Ѵ� 
void CServerSetting::CopyData(TServer3 *pCopy, TServer3 *pOrg)
{
	lstrcpy(pCopy->szName, pOrg->szName); 
	lstrcpy(pCopy->szIP, pOrg->szIP);
	pCopy->wPort = pOrg->wPort;
	pCopy->nPassive = pOrg->nPassive;
	lstrcpy(pCopy->szID, pOrg->szID);
	lstrcpy(pCopy->szPassword, pOrg->szPassword);
	lstrcpy(pCopy->szDefaultPath, pOrg->szDefaultPath); 
}

//////////////////////////////////////////////////////////////////////
// ����ü �����͸� ī���Ѵ� 
void CServerSetting::CopyData(TServer3 *pCopy, TServer2 *pOrg)
{
	lstrcpy(pCopy->szName, pOrg->szName); 
	lstrcpy(pCopy->szIP, pOrg->szIP);
	pCopy->wPort = pOrg->wPort;
	pCopy->nPassive = 0;
	lstrcpy(pCopy->szID, pOrg->szID);
	lstrcpy(pCopy->szPassword, pOrg->szPassword);
	lstrcpy(pCopy->szDefaultPath, pOrg->szDefaultPath); 
}

//////////////////////////////////////////////////////////////////////
// List�� ���� �ϸ� ...
void CServerSetting::OnSelchangeListServer() 
{
	m_nSelectIndex = m_listServer.GetCurSel(); 

	if (m_nSelectIndex >= 0) {
		SetView(reinterpret_cast<TServer3 *>(m_arrServer.GetAt(m_nSelectIndex)));	
	}
}

//////////////////////////////////////////////////////////////////////
// �����׸��� ���� 
void CServerSetting::OnBtnDelete() 
{
	TServer3 TS;
	ZeroMemory(&TS, sizeof(TServer3));
	Clear();

	CStdioFile File;
	File.Open(strSettingFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	File.Write((LPCSTR)strFileHeader, strFileHeader.GetLength());
	int nCount = m_arrServer.GetSize(); 

	for (int i = 0; i < nCount; i++) {
		if (i != m_nSelectIndex) {
			SetEncoding((TServer3 *)m_arrServer[i]);
			File.Write(((TServer3 *)m_arrServer[i]), sizeof(TServer3));
		}
	}

	File.Close();
	GetSettingData();		
}

//////////////////////////////////////////////////////////////////////
// �����׸��� DblClick : ���� �Ѵ� 
void CServerSetting::OnDblclkListServer() 
{
	OnBtnOpen();
}

//////////////////////////////////////////////////////////////////////
// ��ȣȭ 
void CServerSetting::SetEncoding(TCHAR *psz)
{
	int nLen = lstrlen(psz);

	for (int i = 0; i < nLen; i++) {
		psz[i] = ~psz[i];
	}
}

//////////////////////////////////////////////////////////////////////
// ��ȣȭ 
void CServerSetting::SetDecoding(TCHAR *psz)
{
	int nLen = lstrlen(psz);

	for (int i = 0; i < nLen; i++) {
		psz[i] = ~psz[i];
	}
}

//////////////////////////////////////////////////////////////////////
// �������� ��ȣȭ 
void CServerSetting::SetEncoding(TServer2 *pServer)
{
	SetEncoding(pServer->szIP);
	SetEncoding(pServer->szName);
	SetEncoding(pServer->szID);
	SetEncoding(pServer->szPassword);
	SetEncoding(pServer->szDefaultPath);
}

//////////////////////////////////////////////////////////////////////
// �������� ��ȣȭ 
void CServerSetting::SetDecoding(TServer2 *pServer)
{
	SetDecoding(pServer->szIP);
	SetDecoding(pServer->szName);
	SetDecoding(pServer->szID);
	SetDecoding(pServer->szPassword);
	SetDecoding(pServer->szDefaultPath);
}

//////////////////////////////////////////////////////////////////////
// �������� ��ȣȭ 
void CServerSetting::SetEncoding(TServer3 *pServer)
{
	SetEncoding(pServer->szIP);
	SetEncoding(pServer->szName);
	SetEncoding(pServer->szID);
	SetEncoding(pServer->szPassword);
	SetEncoding(pServer->szDefaultPath);
}

//////////////////////////////////////////////////////////////////////
// �������� ��ȣȭ 
void CServerSetting::SetDecoding(TServer3 *pServer)
{
	SetDecoding(pServer->szIP);
	SetDecoding(pServer->szName);
	SetDecoding(pServer->szID);
	SetDecoding(pServer->szPassword);
	SetDecoding(pServer->szDefaultPath);
}

void CServerSetting::OnCheckSelectClientpath() 
{
	BOOL b = IsGetCheckedClientPath();
	
	if (!b) {
		m_strDefaultClientPath = "";
		SetDlgItemText(IDC_EDIT_DEFAULT_PATH_CLIENT, m_strDefaultClientPath);
		//UpdateData(FALSE);
	}

	GetDlgItem(IDC_EDIT_DEFAULT_PATH_CLIENT)->EnableWindow(b);
	GetDlgItem(IDC_BTN_SELECT_CLIENT_PATH)->EnableWindow(b);
}

BOOL CServerSetting::IsGetCheckedClientPath()
{
	return static_cast<CButton *>(GetDlgItem(IDC_CHECK_SELECT_CLIENTPATH))->GetCheck() ? TRUE : FALSE;
}

void CServerSetting::OnBtnSelectClientPath() 
{
	// ���� 2003/04/03
	SetDlgItemText(IDC_EDIT_DEFAULT_PATH_CLIENT, GetBrowsePath());
}

CString CServerSetting::GetBrowsePath()
{
	TCHAR szDir[SZ_SIZE + 1];
	
	BROWSEINFO bi;
	ZeroMemory(reinterpret_cast<LPVOID>(&bi), sizeof(BROWSEINFO));
	bi.hwndOwner = m_hWnd;
	
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&bi);
	::SHGetPathFromIDList(pidl, szDir); 

	return szDir;
}

void CServerSetting::SetClientPathCheck(BOOL bCheck)
{
	static_cast<CButton *>(GetDlgItem(IDC_CHECK_SELECT_CLIENTPATH))->SetCheck(bCheck ? 1 : 0);
	OnCheckSelectClientpath();
}
