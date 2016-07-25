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
typedef unsigned long DWORD;
typedef long LPARAM;
typedef unsigned long DWORD_PTR;
typedef wxTextFile CStdioFile;
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

#define WriteString AddLine
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
typedef wxRect RECT;
typedef RECT* LPRECT;
typedef wxPoint POINT;
typedef unsigned long COLORREF;
typedef long LONG;
#define UNREFERENCED_PARAMETER(x) wxUnusedVar(x) 
#endif
typedef unsigned char BYTE;
#define AfxMessageBox(x,y) wxMessageBox(x,wxMessageBoxCaptionStr,y)
//#define AfxMessageBox(x) wxMessageBox(x)
#define MB_YESNO wxYES_NO
#define MB_ICONQUESTION wxICON_QUESTION
#define IDYES wxYES
#define DATA_PATH _T("../Data")

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

class CMenu;
class CCmdTarget;

class CCmdUI // simple helper class
{
public:
	// Attributes
	UINT m_nID;
	UINT m_nIndex; // menu item or other index

				   // if a menu item
	CMenu* m_pMenu;    // NULL if not a menu
	CMenu* m_pSubMenu; // sub containing menu item
					   // if a popup sub menu - ID is for first in popup

					   // if from some other window
	CWnd* m_pOther; // NULL if a menu or not a CWnd

					// Operations to do in ON_UPDATE_COMMAND_UI
	virtual void Enable(BOOL bOn = TRUE);
	virtual void SetCheck(int nCheck = 1); // 0, 1 or 2 (indeterminate)
	virtual void SetRadio(BOOL bOn = TRUE);
	virtual void SetText(LPCTSTR lpszText);

	// Advanced operation
	void ContinueRouting();

	// Implementation
	CCmdUI();
	BOOL m_bEnableChanged;
	BOOL m_bContinueRouting;
	UINT m_nIndexMax; // last + 1 for iterating m_nIndex

	CMenu* m_pParentMenu; // NULL if parent menu not easily determined
						  //  (probably a secondary popup menu)

	BOOL DoUpdate(CCmdTarget* pTarget, BOOL bDisableIfNoHndler);
};