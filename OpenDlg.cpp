// OpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GlassFTP.h"
#include "OpenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenDlg dialog


COpenDlg::COpenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenDlg)
	m_strID = _T("administrator");
	m_strIP = _T("cdecl");
	m_strPassword = _T("road2you");
	//}}AFX_DATA_INIT
}


void COpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenDlg)
	DDX_Text(pDX, IDC_EDIT_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_IP, m_strIP);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenDlg, CDialog)
	//{{AFX_MSG_MAP(COpenDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenDlg message handlers

BOOL COpenDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Brush.CreateSolidBrush(BACK_COLOR); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH COpenDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC ) {
		pDC->SetBkColor(BACK_COLOR);
		return m_Brush;
	}
	else {
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	
	return hbr;
}
