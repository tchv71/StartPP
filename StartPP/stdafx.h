// stdafx.h: включите файл для добавления стандартных системных файлов
//или конкретных файлов проектов, часто используеCSмых,
// но редко изменяемых
#pragma once

#ifdef WX
// wxWidgets used
#include "wx/wx.h"
#include "wx/file.h"
typedef wxString CStringA;
typedef wxString CString;
typedef wxFont CFont;
typedef bool BOOL;
typedef unsigned UINT;
typedef const wchar_t* LPCTSTR;
typedef int LRESULT;
typedef short WPARAM;
typedef short WORD;
typedef int LPARAM;
typedef intptr_t DWORD_PTR;
typedef wxFile CStdioFile;
typedef wxFile CArchive;
typedef wxPoint CPoint;

#define nullptr NULL
#define DECLARE_DYNAMIC DECLARE_DYNAMIC_CLASS
#define DECLARE_MESSAGE_MAP DECLARE_EVENT_TABLE
#define DECLARE_DYNCREATE DECLARE_DYNAMIC_CLASS
#define BEGIN_MESSAGE_MAP BEGIN_EVENT_TABLE
#define END_MESSAGE_MAP END_EVENT_TABLE

#else
#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Исключите редко используемые компоненты из заголовков Windows
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // некоторые конструкторы CString будут явными

// отключает функцию скрытия некоторых общих и часто пропускаемых предупреждений MFC
#define _AFX_ALL_WARNINGS

#include <afxwin.h> // основные и стандартные компоненты MFC

#include <afxext.h> // расширения MFC



#include <afxdisp.h> // классы автоматизации MFC



// Выбрана поддержка базы данных с представлением.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h> // поддержка MFC для типовых элементов управления Internet Explorer 4

#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h> // поддержка MFC для типовых элементов управления Windows

#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxcontrolbars.h> // поддержка MFC для лент и панелей управления



#include <afxdb.h> // ODBC

#endif
