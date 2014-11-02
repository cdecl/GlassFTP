// OptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "glassftp.h"
#include "OptionDlg.h"

using namespace NS_Config;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog


COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	//{{AFX_MSG_MAP(COptionDlg)
	ON_BN_CLICKED(IDC_BTN_FILEDLG, OnBtnFiledlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_RADIO_SERVERFILECOUNT, OnRadioServerfilecount)
	ON_BN_CLICKED(IDC_RADIO_SERVERFILECOUNT2, OnRadioServerfilecount2)
	ON_BN_CLICKED(IDC_RADIO_BACKUP1, OnRadioBackup1)
	ON_BN_CLICKED(IDC_RADIO_BACKUP2, OnRadioBackup2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_FILEDLG_CONFIG, &COptionDlg::OnBnClickedBtnFiledlgConfig)
	ON_BN_CLICKED(IDC_BTN_FILEDLG_DIFF, &COptionDlg::OnBnClickedBtnFiledlgDiff)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDlg message handlers


BOOL COptionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetConfig();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void COptionDlg::OnBtnFiledlg() 
{
	CFileDialog dlgFile(TRUE);
	
	if (dlgFile.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_FILEPATH, dlgFile.GetPathName()); 
	}
}

void COptionDlg::OnBtnSave() 
{
	CString strValue;

	GetDlgItemText(IDC_EDIT_FILEPATH, strValue);
	if (strValue.IsEmpty()) 
		strValue = _T("NotePad.exe");
	
	::WritePrivateProfileString(
			SECTION,
			_T("Editor"), 
			strValue,
			INI_FILENAME
	);

	GetDlgItemText(IDC_EDIT_DIFFPATH, strValue);
	if (strValue.IsEmpty()) 
		strValue = _T("");
	
	::WritePrivateProfileString(
			SECTION,
			_T("Diff"), 
			strValue,
			INI_FILENAME
	);

	GetDlgItemText(IDC_EDIT_FILEPATH_CONFIG, strValue);
	if (strValue.IsEmpty()) 
		strValue = _T("GlassFTP.dat");
	
	::WritePrivateProfileString(
			SECTION,
			_T("ServerConfig"), 
			strValue,
			INI_FILENAME
	);
	
	GetDlgItemText(IDC_EDIT_INTERVAL, strValue);
	::WritePrivateProfileString (
			SECTION,
			_T("Interval"), 
			strValue,
			INI_FILENAME
	);

	///////////////////////////////////////////////
	if (static_cast<CButton *>(GetDlgItem(IDC_RADIO_SERVERFILECOUNT))->GetCheck()) {
		::WritePrivateProfileString (
			SECTION,
			_T("ServerFileCount"), 
			_T("0"),
			INI_FILENAME
		);
	}
	else {
		GetDlgItemText(IDC_EDIT_FILECOUNT, strValue);
		::WritePrivateProfileString (
			SECTION,
			_T("ServerFileCount"), 
			strValue,
			INI_FILENAME
		);
	}

	///////////////////////////////////////////////
	if (static_cast<CButton *>(GetDlgItem(IDC_RADIO_BACKUP1))->GetCheck()) {
		::WritePrivateProfileString (
			SECTION,
			_T("Backup"), 
			_T(""),
			INI_FILENAME
		);
	}
	else {
		GetDlgItemText(IDC_EDIT_BACKUP, strValue);
		::WritePrivateProfileString (
			SECTION,
			_T("Backup"), 
			strValue,
			INI_FILENAME
		);
	}

	// Auto모드시 파일 ASCII 파일 확장자 지정
	GetDlgItemText(IDC_EDIT_AUTOEXT, strValue);
	::WritePrivateProfileString (
			SECTION,
			_T("Auto"), 
			strValue,
			INI_FILENAME
	);

	EndDialog(IDOK);
}

void COptionDlg::GetConfig()
{
	TCHAR sz[SZ_SIZE + 1];

	///////////////////////////////////////////////
	::GetPrivateProfileString (
			SECTION,
			_T("Editor"), 
			_T("NotePad.exe"), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);
	SetDlgItemText(IDC_EDIT_FILEPATH, sz);

	///////////////////////////////////////////////
	::GetPrivateProfileString (
			SECTION,
			_T("Diff"), 
			_T(""), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);
	SetDlgItemText(IDC_EDIT_DIFFPATH, sz);


	///////////////////////////////////////////////
	::GetPrivateProfileString (
			SECTION,
			_T("ServerConfig"), 
			_T("GlassFTP.dat"), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);
	SetDlgItemText(IDC_EDIT_FILEPATH_CONFIG, sz);


	///////////////////////////////////////////////
	::GetPrivateProfileString (
			SECTION,
			_T("Auto"), 
			_T(AUTOEXT_LIST), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);
	SetDlgItemText(IDC_EDIT_AUTOEXT, sz);


	///////////////////////////////////////////////
	UINT uInterval = ::GetPrivateProfileInt(
							SECTION,
							_T("Interval"), 
							120, 
							INI_FILENAME
						);	
	SetDlgItemInt(IDC_EDIT_INTERVAL, uInterval);


	///////////////////////////////////////////////
	UINT uServerFileCount = ::GetPrivateProfileInt(
							SECTION,
							_T("ServerFileCount"), 
							0, 
							INI_FILENAME
						);	

	if (uServerFileCount) {
		static_cast<CButton *>(GetDlgItem(IDC_EDIT_FILECOUNT))->EnableWindow(TRUE);
		static_cast<CButton *>(GetDlgItem(IDC_RADIO_SERVERFILECOUNT2))->SetCheck(TRUE);
		SetDlgItemInt(IDC_EDIT_FILECOUNT, uServerFileCount);
	}
	else {
		static_cast<CButton *>(GetDlgItem(IDC_EDIT_FILECOUNT))->EnableWindow(FALSE);
		static_cast<CButton *>(GetDlgItem(IDC_RADIO_SERVERFILECOUNT))->SetCheck(TRUE);
		SetDlgItemInt(IDC_EDIT_FILECOUNT, uServerFileCount);
	}


	///////////////////////////////////////////////
	::GetPrivateProfileString (
			SECTION,
			_T("Backup"), 
			_T(""), 
			sz,
			SZ_SIZE,
			INI_FILENAME
	);

	CString strBackup = sz;
	if (strBackup.IsEmpty()) {
		static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->EnableWindow(FALSE);
		static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->SetWindowText(_T(""));
		static_cast<CButton *>(GetDlgItem(IDC_RADIO_BACKUP1))->SetCheck(TRUE);
	}
	else {
		static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->EnableWindow(TRUE);
		static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->SetWindowText(strBackup);
		static_cast<CButton *>(GetDlgItem(IDC_RADIO_BACKUP2))->SetCheck(TRUE);
	}
}


void COptionDlg::OnRadioServerfilecount() 
{
	static_cast<CButton *>(GetDlgItem(IDC_EDIT_FILECOUNT))->EnableWindow(FALSE);
}

void COptionDlg::OnRadioServerfilecount2() 
{
	static_cast<CButton *>(GetDlgItem(IDC_EDIT_FILECOUNT))->EnableWindow(TRUE);
}

void COptionDlg::OnRadioBackup1() 
{
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->EnableWindow(FALSE);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->SetWindowText(_T(""));
}

void COptionDlg::OnRadioBackup2() 
{
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->EnableWindow(TRUE);
	static_cast<CEdit *>(GetDlgItem(IDC_EDIT_BACKUP))->SetWindowText(_T("Backup"));
}

void COptionDlg::OnBnClickedBtnFiledlgConfig()
{
	CFileDialog dlgFile(TRUE);
	
	if (dlgFile.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_FILEPATH_CONFIG, dlgFile.GetPathName()); 
	}
}

void COptionDlg::OnBnClickedBtnFiledlgDiff()
{
	CFileDialog dlgFile(TRUE);
	
	if (dlgFile.DoModal() == IDOK) {
		SetDlgItemText(IDC_EDIT_DIFFPATH, dlgFile.GetPathName()); 
	}
}
