// ClientPath.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GlassFTP.h"
#include "ClientPath.h"

#include "GlassFTPDlg.h"


// CClientPath

IMPLEMENT_DYNAMIC(CClientPath, CEdit)

CClientPath::CClientPath()
{

}

CClientPath::~CClientPath()
{
}


BEGIN_MESSAGE_MAP(CClientPath, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CClientPath 메시지 처리기입니다.


void CClientPath::SetParent(CGlassFTPDlg *pParent)
{
	m_pParent = pParent;	
}



void CClientPath::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if ((nChar == 13) && (m_pParent)) {
		CString strPath;
		GetWindowText(strPath);

		strPath.TrimLeft();
		if (strPath.IsEmpty()) {
			CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
			return ;
		}

		m_pParent->SetEditClientPath(strPath);
	}
	
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
