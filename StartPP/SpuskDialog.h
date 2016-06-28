#pragma once
#include "VecPnN.h"
#include "wxcrafter.h"


// CSpuskDialog dialog

class CSpuskDialog : public CSpuskBaseDialog
{
public:
	CSpuskDialog(CWnd* pParent, CVecPnN& PnN); // standard constructor
	virtual ~CSpuskDialog();

protected:
	//void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListDiam(wxCommandEvent& event);
	//CListBox m_lstDiam;
	//CButton m_rSpusk;
	float m_h;
	float m_H1;
	float m_H2;
	CVecPnN& m_PnN;
	BOOL OnInitDialog();
	//CStatic m_Image;
	//void SetBitmap(int bmId);
	int m_Radio;
protected:
	void OnOK();
	void EndModal(int retcode) wxOVERRIDE;

};

