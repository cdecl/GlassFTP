// ComboServerPath.cpp : implementation file
//

#include "stdafx.h"
#include "glassftp.h"
#include "ComboServerPath.h"

#include "GlassFTPDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboServerPath

CComboServerPath::CComboServerPath()
{
	m_pParent = NULL;

	m_brushBack.CreateSolidBrush(RGB(0xEE, 0xEE, 0xEE)); 
}

CComboServerPath::~CComboServerPath()
{
}


BEGIN_MESSAGE_MAP(CComboServerPath, CComboBox)
	//{{AFX_MSG_MAP(CComboServerPath)
	ON_WM_KEYDOWN()
	ON_WM_CTLCOLOR()
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnEditupdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboServerPath message handlers

void CComboServerPath::SetParent(CGlassFTPDlg *pParent)
{
	m_pParent = pParent;	
}

void CComboServerPath::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == 13) && (m_pParent)) {
		CString strServerPath;
		GetWindowText(strServerPath);

		strServerPath.TrimLeft();
		if (strServerPath.IsEmpty()) {
			CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
			return ;
		}

		m_pParent->DirectMoveServerPath(strServerPath);
	}
	
	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

HBRUSH CComboServerPath::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkMode(TRANSPARENT);    
	hbr = (HBRUSH)m_brushBack;

	return hbr;
}

void CComboServerPath::OnEditupdate() 
{
	ShowDropDown(TRUE);
}
