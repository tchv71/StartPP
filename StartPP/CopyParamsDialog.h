#pragma once
#include "Pipe.h"
#include "wxcrafter.h"

// диалоговое окно CCopyParamsDialog

class CCopyParamsDialog : public CCopyParamsBaseDialog
{
public:
	CCopyParamsDialog(CWnd* pParent, CPipes& pipes); // стандартный конструктор
	virtual ~CCopyParamsDialog();

protected:
	//void DoDataExchange(CDataExchange* pDX) override; // поддержка DDX/DDV

	//DECLARE_MESSAGE_MAP()
public:
	CPipes m_pipes;
	BOOL OnInitDialog();
	void OnOK();
    virtual void EndModal(int retcode) wxOVERRIDE;
	//CListBox m_lbParams;
	//CListBox m_lbPipes;
	afx_msg void OnStnClickedPipeName();
	//CStatic m_sPipeName;
};

