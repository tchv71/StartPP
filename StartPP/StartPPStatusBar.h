#pragma once


// CStartPPStatusBar

class CStartPPStatusBar : public CMFCStatusBar
{
	DECLARE_DYNAMIC(CStartPPStatusBar)

public:
	CStartPPStatusBar();
	virtual ~CStartPPStatusBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

