#pragma once


// CTroinicsTableDlg
#include "PipesTableDlg.h"

class CTroinicsTableDlg : public CPipesTableDlg
{
	DECLARE_DYNAMIC(CTroinicsTableDlg)

public:
	CTroinicsTableDlg(CWnd* pParent = nullptr); // standard constructor
	virtual ~CTroinicsTableDlg();
	void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult) override;
	void OnTableDel() override;

	// Dialog Data
	enum
	{
		IDD = IDD_PIPES_DIALOG
	};

protected:
	BOOL OnInitDialog() override;
	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};

