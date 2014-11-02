#if !defined(AFX_OPENDLG_H__360CE702_5AE2_41B7_976E_10439B28B13D__INCLUDED_)
#define AFX_OPENDLG_H__360CE702_5AE2_41B7_976E_10439B28B13D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenDlg dialog

class COpenDlg : public CDialog
{
public:
	enum {
		BACK_COLOR = 0xDDDDDD
	};
// Construction
public:
	COpenDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COpenDlg)
	enum { IDD = IDD_OPEN };
	CString	m_strID;
	CString	m_strIP;
	CString	m_strPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_Brush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENDLG_H__360CE702_5AE2_41B7_976E_10439B28B13D__INCLUDED_)
