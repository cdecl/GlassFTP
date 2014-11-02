#if !defined(AFX_MESSAGEDLG_H__53F4DC14_4A9A_4A69_98FB_C39CDA3C2427__INCLUDED_)
#define AFX_MESSAGEDLG_H__53F4DC14_4A9A_4A69_98FB_C39CDA3C2427__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageDlg dialog

class CMessageDlg : public CDialog
{
public:
	enum {
		IDOK_ALL		= 10
	};


// Construction
public:
	CMessageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageDlg)
	enum { IDD = IDD_MESSAGEBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMessageDlg)
	virtual void OnOK();
	afx_msg void OnOkall();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void SetMessage(const CString& strMessage);
	static int MessageBox(const CString& strMessage);

private:
	CString m_strMessage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEDLG_H__53F4DC14_4A9A_4A69_98FB_C39CDA3C2427__INCLUDED_)
