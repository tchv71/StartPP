#pragma once
#include "PipesTableDlg.h"


// CArmatTableDlg dialog

class CArmatTableDlg : public CPipesTableDlg
{
	DECLARE_DYNAMIC(CArmatTableDlg)

public:
	CArmatTableDlg(CWnd* pParent = nullptr); // standard constructor
	virtual ~CArmatTableDlg();
	void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult) override;
	void OnTableDel() override;

	// Dialog Data
	enum
	{
		IDD = IDD_ARMATTABLEDLG
	};

protected:
	BOOL OnInitDialog() override;
	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnClose();
	afx_msg void OnDestroy();
};

