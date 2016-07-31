#pragma once
#include "CTableDlg.h"
// диалоговое окно CArmatTableDlg

class CArmatTableDlg : public CTableDlg
{
	//DECLARE_DYNAMIC(CArmatTableDlg)

public:
	CArmatTableDlg(CWnd* pParent = nullptr); // стандартный конструктор
	virtual ~CArmatTableDlg();


protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	void OnGridCellChanged(wxGridEvent& event);
};

