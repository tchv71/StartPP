// stdafx.h: включите файл для добавления стандартных системных файлов
//или конкретных файлов проектов, часто используеCSмых,
// но редко изменяемых
#pragma once

// wxWidgets used
#include "wx/wx.h"
#include "wx/textfile.h"
#include "wx/dc.h"
#include "wx/dialog.h"
typedef wxString CStringA;
typedef wxString CString;
typedef wxFont CFont;
typedef int BOOL;
typedef unsigned UINT;
typedef const wchar_t* LPCTSTR;
typedef wchar_t TCHAR;
typedef long LRESULT;
typedef unsigned int WPARAM;
typedef unsigned short WORD;
typedef long LPARAM;
typedef unsigned long DWORD_PTR;
typedef wxTextFile CStdioFile;
typedef wxDC CDC;
typedef wxRect CRect;
typedef wxSize CSize;
typedef wxPen CPen;
typedef wxDialog CDialog;
typedef wxBrush CBrush;
#define WriteString AddLine
//typedef wxFile CArchive;
typedef wxPoint CPoint;
#define afx_msg

#define DECLARE_DYNAMIC DECLARE_DYNAMIC_CLASS
#define IMPLEMENT_DYNAMIC IMPLEMENT_DYNAMIC_CLASS
#define DECLARE_MESSAGE_MAP DECLARE_EVENT_TABLE
#define DECLARE_DYNCREATE DECLARE_DYNAMIC_CLASS
#define BEGIN_MESSAGE_MAP BEGIN_EVENT_TABLE
#define END_MESSAGE_MAP END_EVENT_TABLE
#define DEBUG_NEW new
enum
{
    ID_PropCombobox = wxID_HIGHEST+1,
    PGID,
	ID_PropToolMo,
	ID_PropToolSk,
	ID_PropToolNapr,
	ID_PropToolOtvSv,
	ID_PropToolOtvIz,
	ID_PropToolArm
};

class COleControlSite;
typedef wxWindow CWnd;
#ifndef __WXMSW__
typedef void* HWND;
#define UNREFERENCED_PARAMETER(x) wxUnusedVar(x) 
#endif
typedef unsigned char BYTE;
#define AfxMessageBox wxMessageBox

// CDataExchange - for data exchange and validation
class CDataExchange
{
// Attributes
public:
	CDataExchange(CWnd *pWnd, bool bSaveAndValidate) : m_pDlgWnd(pWnd), m_bSaveAndValidate(bSaveAndValidate) {};
	BOOL m_bSaveAndValidate;   // TRUE => save and validate data
	CWnd* m_pDlgWnd;           // container usually a dialog

	void Fail() {};                    // will throw exception

	CDataExchange(CWnd* pDlgWnd, BOOL bSaveAndValidate) : m_pDlgWnd(pDlgWnd), m_bSaveAndValidate(bSaveAndValidate) {};

// Implementation
    UINT m_idLastControl;      // last control used (for validation)
	BOOL m_bEditLastControl;   // last control was an edit item
};


