// stdafx.h: включите файл для добавления стандартных системных файлов
//или конкретных файлов проектов, часто используемых,
// но редко изменяемых
#ifndef _STDAFX_H
#define _STDAFX_H
// wxWidgets used
#include "wx/wx.h"
#include "wx/textfile.h"
#include "wx/dc.h"
#include "wx/dialog.h"
#include <wx/filename.h>
typedef wxString CStringA;
typedef wxString CString;
typedef wxFont CFont;
typedef int BOOL;
typedef unsigned UINT;
typedef const wchar_t* LPCTSTR;
typedef wchar_t TCHAR;
//typedef long LRESULT;
//typedef unsigned int WPARAM;
typedef unsigned short WORD;
typedef unsigned long DWORD;
//typedef long LPARAM;
#ifdef _WIN64
typedef unsigned long long DWORD_PTR;
#else
typedef unsigned long DWORD_PTR;
#endif
typedef wxFile CStdioFile;
typedef wxDC CDC;
typedef wxRect CRect;
typedef wxSize CSize;
typedef wxPen CPen;
typedef wxDialog CDialog;
typedef wxBrush CBrush;
typedef wxToolBar CMFCToolBar;
typedef wxFrame CFrameWnd;
typedef wxPanel CDockablePane;
typedef wxChoice CComboBox;
typedef wxListBox CListBox;
typedef wxClassInfo CRuntimeClass;
typedef wxObject CObject;
typedef wxScrollBar CScrollBar;

#define WriteString Write
//typedef wxFile CArchive;
typedef wxPoint CPoint;
#define afx_msg

#define DECLARE_DYNAMIC DECLARE_DYNAMIC_CLASS
#define IMPLEMENT_DYNAMIC IMPLEMENT_DYNAMIC_CLASS
#define IMPLEMENT_DYNCREATE IMPLEMENT_DYNAMIC_CLASS
#define DECLARE_MESSAGE_MAP DECLARE_EVENT_TABLE
#define DECLARE_DYNCREATE DECLARE_DYNAMIC_CLASS
#define BEGIN_MESSAGE_MAP BEGIN_EVENT_TABLE
#define END_MESSAGE_MAP END_EVENT_TABLE

enum
{
    ID_PropCombobox = wxID_HIGHEST+1,
    PGID,
	ID_RecalcXYZ
};

class COleControlSite;
typedef wxWindow CWnd;
#ifndef __WXMSW__
typedef void* HWND;
typedef wxRect RECT;
typedef RECT* LPRECT;
typedef wxPoint POINT;
typedef unsigned long COLORREF;
typedef long LONG;
#define UNREFERENCED_PARAMETER(x) wxUnusedVar(x) 
#endif
typedef unsigned char BYTE;
#define AfxMessageBox(x,y) wxMessageBox(x,wxTheApp->GetAppDisplayName(),y)
//#define AfxMessageBox(x) wxMessageBox(x)
//#define MB_YESNO wxYES_NO
//#define MB_ICONQUESTION wxICON_QUESTION
//#define IDYES wxYES
#ifdef __WXMAC__
inline wxString DataPath()
{
    wxFileName fn;
    fn.AssignHomeDir();
    wxString strPath = fn.GetPath();
    strPath.Append("/Library/StartPP/Data");
    return strPath;
}
#define DATA_PATH DataPath()
#else
#define DATA_PATH wxString("../Data")
#endif

// CDataExchange - for data exchange and validation
class CDataExchange
{
// Attributes
public:
	CDataExchange(CWnd *pWnd, bool bSaveAndValidate) : m_bSaveAndValidate(bSaveAndValidate), m_pDlgWnd(pWnd) {};
	BOOL m_bSaveAndValidate;   // TRUE => save and validate data
	CWnd* m_pDlgWnd;           // container usually a dialog

	CDataExchange(CWnd* pDlgWnd, BOOL bSaveAndValidate) : m_bSaveAndValidate(bSaveAndValidate), m_pDlgWnd(pDlgWnd) {};
};



//#define new WXDEBUG_NEW
#endif