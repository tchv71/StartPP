// StartPPStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "StartPPStatusBar.h"


// CStartPPStatusBar

IMPLEMENT_DYNAMIC(CStartPPStatusBar, CMFCStatusBar)

CStartPPStatusBar::CStartPPStatusBar()
{
}

CStartPPStatusBar::~CStartPPStatusBar()
{
}


BEGIN_MESSAGE_MAP(CStartPPStatusBar, CMFCStatusBar)
	ON_WM_SIZE()
	ON_WM_CREATE()
	END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR , // индикатор строки состояния
	ID_IND_FILE_COUNT,
	ID_IND_FILE_INFO,
	ID_INDICATOR_CAPS ,
	ID_INDICATOR_NUM ,
	ID_INDICATOR_SCRL ,
};


// CStartPPStatusBar message handlers


void CStartPPStatusBar::OnSize(UINT nType, int cx, int cy)
{
	CMFCStatusBar::OnSize(nType, cx, cy);

	int nPane0Width = cx / 3;
	int nPane1Width = cx / 8;
	SetPaneWidth(0, nPane0Width);
	SetPaneWidth(1, nPane1Width);
	SetPaneWidth(2, cx - nPane0Width - nPane1Width - 200);
}


int CStartPPStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	SetPaneWidth(0, 200);
	SetPaneWidth(1, 100);
	SetPaneWidth(2, 100);
	SetPaneText(1,_T("Text"));

	return 0;
}

