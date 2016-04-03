#pragma once
#include "GridCtrl_src/GridCtrl.h"


// CPipeTableWnd
class CStartPPDoc;

class CPipeTableWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CPipeTableWnd)

public:
	CPipeTableWnd();
	virtual ~CPipeTableWnd();

protected:
	DECLARE_MESSAGE_MAP()
	CGridCtrl m_wndGrid;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void DoDataExchange(CDataExchange* pDX, CStartPPDoc* pDoc);
};


