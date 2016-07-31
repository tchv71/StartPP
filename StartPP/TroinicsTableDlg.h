#pragma once
#include "CTableDlg.h"
// диалоговое окно CTroinicsTableDlg

class CTroinicsTableDlg : public CTableDlg
{
	//DECLARE_DYNAMIC(CTroinicsTableDlg)

public:
	CTroinicsTableDlg(CWnd* pParent = nullptr); // стандартный конструктор
	virtual ~CTroinicsTableDlg();


protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
};

