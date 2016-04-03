#pragma once
#include "afxwin.h"
#include "VecPnN.h"
#include "resource.h"


// CSpuskDialog dialog

class CSpuskDialog : public CDialog
{
	DECLARE_DYNAMIC(CSpuskDialog)

public:
	CSpuskDialog(CWnd* pParent, CVecPnN& PnN); // standard constructor
	virtual ~CSpuskDialog();

	// Dialog Data
	enum
	{
		IDD = IDD_SPUSK_DIALOG
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListDiam();
	CListBox m_lstDiam;
	CButton m_rSpusk;
	float m_h;
	float m_H1;
	float m_H2;
	CVecPnN& m_PnN;
	BOOL OnInitDialog() override;
	CStatic m_Image;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	void SetBitmap(int bmId);
	int m_Radio;
protected:
	void OnOK() override;
public:
	CButton m_btnOk;
};

