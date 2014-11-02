// FileListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "GlassFTP.h"
#include "FileListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl

CFileListCtrl::CFileListCtrl() : m_bRecvEventMessage(TRUE)
{
	m_nSortType = -1;
}

CFileListCtrl::~CFileListCtrl()
{
	m_imgList.Detach(); 
}


BEGIN_MESSAGE_MAP(CFileListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CFileListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileListCtrl message handlers


void CFileListCtrl::InitFileList(BOOL bClientSide)
{
	RECT rect;
	GetWindowRect(&rect);

	// Set Column Text
	InsertColumn(0, _T("이 름"), LVCFMT_LEFT, 150);
	InsertColumn(1, _T("크 기"), LVCFMT_RIGHT, 70);
	InsertColumn(2, _T("수정일"), LVCFMT_LEFT, 120);

	m_bClientSide = bClientSide;

	SetIconList();
}


int CFileListCtrl::FindItemString(const CString &str)
{
	LVFINDINFO finfo;
	finfo.flags = LVFI_STRING;
	finfo.psz = (LPCTSTR)str;

	return FindItem(&finfo); 
}


void CFileListCtrl::AddFile(
	const CString &strFileName, const CString &strFilePath, const CString &strFileSize, 
	const CString &strFileTime, BOOL bIsDirectory)
{
	// 파일이름이 존재하면 해당행을 Update
	int nRow = FindItemString(strFileName);
	bool bIsInsert = (nRow == -1) ? true : false;

	if (bIsInsert) {
		nRow = GetItemCount(); 
	}
	
	LVITEMA Item;

	Item.mask = LVIF_TEXT | LVIF_IMAGE;
	Item.iImage = GetIconIndex(strFilePath, bIsDirectory);
	Item.iItem = nRow;
	Item.iSubItem = 0;
	Item.pszText = (LPSTR)(LPCSTR)strFileName;  

	if (bIsInsert) {
		InsertItem(&Item);
	}
	else {
		SetItem(&Item);
	}

	Item.mask = LVIF_TEXT;
	Item.iItem = nRow;
	Item.iSubItem = 1;
	Item.pszText = (LPSTR)(LPCSTR)strFileSize;  
	SetItem(&Item);

	Item.mask = LVIF_TEXT;
	Item.iItem = nRow;
	Item.iSubItem = 2;
	Item.pszText = (LPSTR)(LPCSTR)strFileTime;  
	SetItem(&Item);
}


void CFileListCtrl::AddFile(CFileFind &FFind, BOOL bLongName)
{
	CString strFileName, strFilePath, strFileSize, strFileTime;

	strFilePath  = FFind.GetFilePath(); 
	strFileName  = FFind.GetFileName(); 

	if (strFileName == _T(".")) {
		return;
	}

	BOOL bIsDirectory = FFind.IsDirectory();
	
	if (!bIsDirectory) {
		strFileSize.Format(_T("%lu"), FFind.GetLength());
	}

	CTime Time;
	FILETIME filetime;

	FFind.GetLastWriteTime(&filetime);

	// 2004.03.10
	// 서버측 수정일 버그 수정 
	// 서버측 시간은 FileTimeToSystemTime로 변환해줘야 한다 
	if (m_bClientSide) {
		Time = CTime(filetime);
	}
	else {
		SYSTEMTIME systemtime;
		FileTimeToSystemTime(&filetime, &systemtime);
		Time = CTime(systemtime);
	}
	 

	strFileTime.Format(
		_T("%04d-%02d-%02d %02d:%02d"), 
		Time.GetYear(), Time.GetMonth(), Time.GetDay(), 
		Time.GetHour(), Time.GetMinute()
	);  

	int nRow = GetItemCount(); 

	if (!bLongName) {
		strFileName = EncodingFileName(strFileName);
	}	

	AddFile(strFileName, strFilePath, strFileSize, strFileTime, bIsDirectory);
}


CString CFileListCtrl::EncodingFileName(CString strFileName)
{
	int nLen = strFileName.GetLength();
	CString strBuff;

	if (nLen <= 0)
		return strFileName;
	
	/*
	for (int i = nLen - 1; i >= 0; i--) {
		if (strFileName.GetAt(i) == (TCHAR)' ') {
			break;
		}
		strBuff = strFileName.GetAt(i) + strBuff;
	}
	*/
	
	strBuff = strFileName;
	for (int i = nLen - 1; i >= 0; i--) {
		if (strFileName.GetAt(i) == (TCHAR)' ') {
		
			// 2003/05/12
			// 솔라리스 FTP SERVER측에는 이상하게 나옴 
			//strBuff = "\"" + strFileName + "\"";
			strBuff = strFileName.Mid(i + 1);
			break;
		}
	}

	return strBuff;
}


int CFileListCtrl::GetIconIndex(const CString &strFilePath, BOOL bIsDirectory)
{
	int nIcon;
	SHFILEINFO fi;
	ZeroMemory(&fi, sizeof(SHFILEINFO));

	if (m_bClientSide) {
		::SHGetFileInfo(
			strFilePath, 
			0, 
			&fi, 
			sizeof(SHFILEINFO), 
			SHGFI_SMALLICON | SHGFI_SYSICONINDEX
		);

		nIcon = fi.iIcon; 
	}
	else {
		::SHGetFileInfo(
			strFilePath, 
			bIsDirectory ? FILE_ATTRIBUTE_DIRECTORY : FILE_ATTRIBUTE_NORMAL, 
			&fi, 
			sizeof(SHFILEINFO), 
			SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES
		);

		nIcon = fi.iIcon; 
	}

	return nIcon;
}


void CFileListCtrl::SetIconList()
{
	const TCHAR szROOT[] = _T("C:\\");

	SHFILEINFO fi;
	ZeroMemory(&fi, sizeof(SHFILEINFO));

//	if (m_bClientSide) {
		HIMAGELIST hImageList = (HIMAGELIST)::SHGetFileInfo(szROOT, 0, &fi, sizeof(SHFILEINFO), SHGFI_SMALLICON | SHGFI_SYSICONINDEX);
		m_imgList.Attach(hImageList);
//	}
//	else {
//		m_imgList.Create(16, 16, TRUE,  4, 4);
//		m_imgList.Add((HICON)AfxGetApp()->LoadIcon(IDI_FORDER_ICON));
//		m_imgList.Add((HICON)AfxGetApp()->LoadIcon(IDI_FILE_ICON));
//	}

	SetImageList(&m_imgList, LVSIL_SMALL);
}

//////////////////////////////////////////////////////////////////////
// Column Click Event
void CFileListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	Sort(pNMListView->iSubItem, m_nSortType * -1);
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////
// static function 
int CFileListCtrl::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamInfo)
{
	CFileListCtrl *pThis = reinterpret_cast<CFileListCtrl *>(lParamInfo);
	int nSubItem = pThis->m_nSubItem;

	if (nSubItem == 1) {
		int n1 = _ttoi(pThis->GetItemText(lParam1, nSubItem)) * pThis->m_nSortType;
		int n2 = _ttoi(pThis->GetItemText(lParam2, nSubItem)) * pThis->m_nSortType;

		if (n1 > n2) 
			return -1; 
		else if (n1 < n2) 
			return 1; 
	}
	else {
		CString strItem1 = pThis->GetItemText(lParam1, nSubItem);
		CString strItem2 = pThis->GetItemText(lParam2, nSubItem);

		strItem1 = ((pThis->GetItemText(lParam1, 1)).IsEmpty() ? _T("1") : _T("2")) + strItem1; 	
		strItem2 = ((pThis->GetItemText(lParam2, 1)).IsEmpty() ? _T("1") : _T("2")) + strItem2; 	

		return strItem1.CompareNoCase(strItem2) * pThis->m_nSortType; 
	}

	return 0;
}

void CFileListCtrl::Sort(int nSubItem, int nOrder)
{
	m_nSubItem = nSubItem; 

	for (int i = 0; i < GetItemCount(); i++) {
		SetItemData(i, i); 	
	}

	m_nSortType = nOrder;
	SortItems(CompareFunc, reinterpret_cast<DWORD>(this));
}

BOOL CFileListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	if (m_bRecvEventMessage != TRUE &&
			(
				(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST) || 
				(pMsg->message >= WM_MOUSEFIRST && pMsg->message <= WM_MOUSELAST) 
			)) {
		
		return TRUE;
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

void CFileListCtrl::EnableEventMessage(BOOL bEnable)
{
	m_bRecvEventMessage = bEnable;
}
