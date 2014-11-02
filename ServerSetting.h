#if !defined(AFX_SERVERSETTING_H__084F1575_E563_4E50_BE86_D051C9F71CFE__INCLUDED_)
#define AFX_SERVERSETTING_H__084F1575_E563_4E50_BE86_D051C9F71CFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CServerSetting dialog

class CServerSetting : public CDialog
{
private:
	enum { SZ_SIZE = 1024 };
/*
	struct TServer {
		TCHAR	szName[30];
		TCHAR	szIP[256];
		TCHAR	szID[20];
		TCHAR	szPassword[20];
		TCHAR	szDefaultPath[100];
	};
*/
	struct TServer2 {
		TCHAR	szName[100];
		TCHAR	szIP[1024];
		short	wPort;
		TCHAR	szID[30];
		TCHAR	szPassword[30];
		TCHAR	szDefaultPath[1024];
	};

	struct TServer3 {
		TCHAR	szName[100];
		TCHAR	szIP[1024];
		short	wPort;
		int		nPassive;
		TCHAR	szID[30];
		TCHAR	szPassword[30];
		TCHAR	szDefaultPath[1024];
	};


// Construction
public:
	void SetClientPathCheck(BOOL bCheck);
	CString GetBrowsePath();
	BOOL IsGetCheckedClientPath();
	void Clear();
	CServerSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CServerSetting)
	enum { IDD = IDD_SERVER };
	CListBox	m_listServer;
	CString	m_strDefaultPath;
	CString	m_strID;
	CString	m_strIP;
	CString	m_strName;
	CString	m_strPassword;
	UINT	m_uPort;
	CString	m_strDefaultClientPath;
	//}}AFX_DATA
	int m_nPassive;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNew();
	afx_msg void OnBtnOpen();
	afx_msg void OnBtnSave();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeListServer();
	afx_msg void OnBtnDelete();
	afx_msg void OnDblclkListServer();
	afx_msg void OnBtnExit();
	afx_msg void OnCheckSelectClientpath();
	afx_msg void OnBtnSelectClientPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetDecoding(TServer2 *pServer);
	void SetEncoding(TServer2 *pServer);

	void SetDecoding(TServer3 *pServer);
	void SetEncoding(TServer3 *pServer);

	void SetDecoding(TCHAR *psz);
	void SetEncoding(TCHAR *psz);

	void CopyData(TServer3 *pCopy, TServer3 *pOrg);
	void CopyData(TServer3 *pCopy, TServer2 *pOrg);

	void Release();
	void GetSettingData();
	void GetView(TServer3 *pServer);
	void SetView(TServer3 *pServer);

	CString strSettingFile;
	CString strFileHeader;
	CPtrArray m_arrServer;
	int m_nSelectIndex;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSETTING_H__084F1575_E563_4E50_BE86_D051C9F71CFE__INCLUDED_)
