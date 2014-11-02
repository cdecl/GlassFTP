// GlassFTPDlg.h : header file
//

#if !defined(AFX_GLASSFTPDLG_H__9F5041D1_08A7_4071_84EB_15AACC516DA8__INCLUDED_)
#define AFX_GLASSFTPDLG_H__9F5041D1_08A7_4071_84EB_15AACC516DA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "FileListCtrl.h"
#include "ComboServerPath.h"
#include "Ftp.h"

#include "AutoList.h"
#include "clientpath.h"

/////////////////////////////////////////////////////////////////////////////
// CGlassFTPDlg dialog

class CGlassFTPDlg : public CDialog
{
public:
	enum { 
		SZ_SIZE			= 1024,
		ID_TIMER		= 1,
		ID_TIMER2		= 2,
		TIMER2_INTERVAL = 1000,
		TIMER_ELAPSE	= 60000
	};
	
// Construction
public:
	CGlassFTPDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CGlassFTPDlg() {};

// Dialog Data
	//{{AFX_DATA(CGlassFTPDlg)
	enum { IDD = IDD_GLASSFTP_DIALOG };
	CProgressCtrl	m_Progress;
	CComboServerPath	m_comboServerPath;
	CComboBox		m_comboServer;
	CFileListCtrl	m_listServer;
	CFileListCtrl	m_listClient;
	int		m_nTransType;
	BOOL	m_bCurrentServer;
	CClientPath m_editClientPath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGlassFTPDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGlassFTPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnShbf();
	afx_msg void OnDblclkListServer(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnCancel();
	afx_msg void OnBtnClientParent();
	afx_msg void OnBtnServerParent();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnPut();
	afx_msg void OnAbout();
	afx_msg void OnOpen();
	afx_msg void OnKeydownListServer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboServer();
	afx_msg void OnCloseall();
	afx_msg void OnBtnServerClose();
	afx_msg void OnBtnServerNewforder();
	afx_msg void OnBtnClientNewforder();
	afx_msg void OnBtnServerDelete();
	afx_msg void OnBtnClientDelete();
	afx_msg void OnOk();
	afx_msg void OnBtnServerRefresh();
	afx_msg void OnBtnClientRefresh();
	afx_msg void OnRclickListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditing();
	afx_msg void OnOption();
	afx_msg void OnSetDefaultPath();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeComboServerPath();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnLogClear();
	afx_msg void OnCheckCurrentServer();
	afx_msg void OnExecute();
	afx_msg void OnEndlabeleditListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeleditListClient(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRename();
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


private:
	CString m_strClientPath;
	CFtp *m_pFtp;
	CPtrArray m_FtpArray;
	CToolTipCtrl m_ToolTip;

	CBrush m_Brush;
	BOOL m_bIDOKALL;

	CAutoList m_AutoList;

private:
	void ReName(const CString &strOldName, const CString &strNewName);
	void InsertServerPath();
	UINT GetServerFileCount();

public:
	void DblclkListClient();
	void DblclkListServer();
	CString GetBackupDirectory();
	void SetStatus();
	void OnInitToolTip();
	BOOL IsCurrentServerCheck();
	void GetFilesImp();
	void PutFiles();
	UINT GetInterval();
	CString GetClientDefaultPath();
	CString GetEditorPathName();
	CString GetDiffPathName();
	BOOL MultiServerNewForder(CString strForderName);
	BOOL MultiServerRemoveDir(CString strFileName);
	BOOL MultiServerRemove(CString strFileName);
	BOOL MultiServerMove(CString strServerPath);
	BOOL ServerPutFile(CString strLocalFile, CString strRemoteFile, DWORD dwFlag = FTP_TRANSFER_TYPE_BINARY);
	int SearchFtp(CFtp *pFtp);
	void SetActiveServer(int nListIndex);
	void UpdateServerList();
	void DeleteClientFile();
	BOOL ListViewFileExists(CFileListCtrl &listView, CString strFileName);
	void DeleteServerFileImp();
	void WriteLog(CString strLog);
	void WriteSeparator();
	void ServerRefresh();
	void ClientRefresh();
	void CloseAll(BOOL bAskMsg = TRUE);
	void Release();
	void ReleaseAll();
	BOOL GetSHBF(CString &);
	BOOL SetServerFiles(CString strPath = _T(""), BOOL bActiveServer = FALSE);
	void SetClientFiles(CString strPath = _T(""));
	void SetTransMode(UINT uMode);
	UINT GetTransMode();
	CString GetAutoTranListString();
	BOOL IsWindowsNTVersion();
	void DirectMoveServerPath(const CString& strServerPath);
	void EnableSendRecv(BOOL bEnable);
	CString GetActiveSessionName();
	void SetProgPos(int nPos = 0);
	void SetProgRange(int nMax);
	void SetProgPosInc();
	int GetServerCount();
	DWORD GetAutoTransMode(const CString &strFileName);
	void SetViewTimer();
	void SetEditClientPath(CString strClientPath);
	CString GetFileToTemp();
	void DiffFile(const CString &strFileName);
	void SyncToClientDirectory(const CString &strDirName);
	void SyncToServerDirectory(const CString &strDirName);

public:
	void EditMenuUpdate();
	void EditMenuUpdateServer();
	void ClientEditLabel();
	static UINT DeleteServerFile(LPVOID lpvParam);
	static UINT GetFiles(LPVOID lpvParam);
	static UINT Open(LPVOID lpvParam);
	static UINT MultiServerPutFiles(LPVOID lpvParam);

	
	afx_msg void OnFileviewServer();
	afx_msg void OnNMRclickListServer(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDiffServer();
	afx_msg void OnDiffClient();
	afx_msg void OnExecuteServer();
//	afx_msg void OnHdnItemchangedListClient(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListClient(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListServer(NMHDR *pNMHDR, LRESULT *pResult);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLASSFTPDLG_H__9F5041D1_08A7_4071_84EB_15AACC516DA8__INCLUDED_)





















