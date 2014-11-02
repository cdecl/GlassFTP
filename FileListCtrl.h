#if !defined(AFX_FILELISTCTRL_H__533095DE_D974_4E5C_8346_E5B1FF4A4C0C__INCLUDED_)
#define AFX_FILELISTCTRL_H__533095DE_D974_4E5C_8346_E5B1FF4A4C0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FileListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl window

class CFileListCtrl : public CListCtrl
{
// Construction
public:
	CFileListCtrl();

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileListCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void EnableEventMessage(BOOL bEnable);
	int FindItemString(const CString &str);
	void Sort(int nSubItem, int nOrder = 1);
	static int __stdcall CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamInfo);
	void SetIconList();
	int GetIconIndex(const CString &strFilePath, BOOL bIsDirectory);
	CString EncodingFileName(CString strFileName);
	void AddFile(const CString &strFileName, const CString &strFilePath, const CString &strFileSize, const CString &strFileTime, BOOL bIsDirectory);
	void AddFile(CFileFind &FFind, BOOL bLongName = TRUE);
	void InitFileList(BOOL bClientSide = TRUE);
	virtual ~CFileListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFileListCtrl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CImageList m_imgList;

	BOOL m_bClientSide;
	int m_nSubItem;
	int m_nSortType;

private:
	volatile BOOL m_bRecvEventMessage;
};	

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILELISTCTRL_H__533095DE_D974_4E5C_8346_E5B1FF4A4C0C__INCLUDED_)
