#if !defined(AFX_FORDERNAME_H__BA0662F2_A31B_4608_826B_5BEEF2DB9E60__INCLUDED_)
#define AFX_FORDERNAME_H__BA0662F2_A31B_4608_826B_5BEEF2DB9E60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ForderName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CForderName dialog

class CForderName : public CDialog
{
public:
	enum {
		BACK_COLOR = 0xDDDDDD
	};
// Construction
public:
	CForderName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CForderName)
	enum { IDD = IDD_FORDERNAME };
	CString	m_strForderName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CForderName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CForderName)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_Brush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORDERNAME_H__BA0662F2_A31B_4608_826B_5BEEF2DB9E60__INCLUDED_)
