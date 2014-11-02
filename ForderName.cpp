// ForderName.cpp : implementation file
//

#include "stdafx.h"
#include "GlassFTP.h"
#include "ForderName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CForderName dialog


CForderName::CForderName(CWnd* pParent /*=NULL*/)
	: CDialog(CForderName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CForderName)
	m_strForderName = _T("");
	//}}AFX_DATA_INIT
}


void CForderName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CForderName)
	DDX_Text(pDX, IDC_EDIT_FORDERNAME, m_strForderName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CForderName, CDialog)
	//{{AFX_MSG_MAP(CForderName)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CForderName message handlers

HBRUSH CForderName::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr;

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC ) {
		pDC->SetBkColor(BACK_COLOR);
		return m_Brush;
	}
	else {
		hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CForderName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Brush.CreateSolidBrush(BACK_COLOR); 
	
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FORDERNAME);
	pEdit->SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
