#if !defined(AFX_OPTIONDLG_H__D4721998_0618_4652_AF57_0926CC0613F5__INCLUDED_)
#define AFX_OPTIONDLG_H__D4721998_0618_4652_AF57_0926CC0613F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDlg.h : header file
//


namespace NS_Config {
	static const TCHAR SECTION[]		= _T("Config");
	static const TCHAR INI_FILENAME[]	= _T("GlassFtp.ini");
	static const TCHAR AUTOEXT_LIST[]	= 
		_T("txt;h;hpp;cpp;c;java;jsp;asp;html;htm;css;vbs;js;")
		_T("py;pl;php;php3;xml;properties");

};

/////////////////////////////////////////////////////////////////////////////
// COptionDlg dialog

class COptionDlg : public CDialog
{
public:
	enum {
		SZ_SIZE = 1024
	};
// Construction
public:
	void GetConfig();
	COptionDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionDlg)
	enum { IDD = IDD_OPTION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionDlg)
	afx_msg void OnBtnFiledlg();
	afx_msg void OnBtnSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioServerfilecount();
	afx_msg void OnRadioServerfilecount2();
	afx_msg void OnRadioBackup1();
	afx_msg void OnRadioBackup2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnFiledlgConfig();
	afx_msg void OnBnClickedBtnFiledlgDiff();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONDLG_H__D4721998_0618_4652_AF57_0926CC0613F5__INCLUDED_)
