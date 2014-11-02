#if !defined(AFX_COMBOSERVERPATH_H__B74F98E9_F6A5_418C_B6B2_300372DFEE7B__INCLUDED_)
#define AFX_COMBOSERVERPATH_H__B74F98E9_F6A5_418C_B6B2_300372DFEE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboServerPath.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CComboServerPath window

class CGlassFTPDlg;


class CComboServerPath : public CComboBox
{
// Construction
public:
	CComboServerPath();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboServerPath)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboServerPath();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboServerPath)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnEditupdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CGlassFTPDlg *m_pParent;
	CBrush m_brushBack;

public:
	void SetParent(CGlassFTPDlg *pParent);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOSERVERPATH_H__B74F98E9_F6A5_418C_B6B2_300372DFEE7B__INCLUDED_)
