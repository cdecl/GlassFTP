// MessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "glassftp.h"
#include "MessageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog


CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMessageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMessageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialog)
	//{{AFX_MSG_MAP(CMessageDlg)
	ON_BN_CLICKED(IDOKALL, OnOkall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg message handlers

void CMessageDlg::OnOK() 
{
	CDialog::OnOK();
}

void CMessageDlg::OnOkall() 
{
	EndDialog(IDOK_ALL);
}

void CMessageDlg::SetMessage(const CString &strMessage)
{
	m_strMessage = strMessage;
}


BOOL CMessageDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_STATIC_MSG, (LPCTSTR)m_strMessage);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CMessageDlg::MessageBox(const CString& strMessage)
{
	CMessageDlg dlg;
	
	dlg.SetMessage(strMessage);
	return dlg.DoModal();
}

