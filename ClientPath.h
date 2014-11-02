#pragma once


// CClientPath

class CGlassFTPDlg;

class CClientPath : public CEdit
{
	DECLARE_DYNAMIC(CClientPath)

public:
	CClientPath();
	virtual ~CClientPath();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);


private:
	CGlassFTPDlg *m_pParent;

public:
	void SetParent(CGlassFTPDlg *pParent);
};


