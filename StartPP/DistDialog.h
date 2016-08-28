#pragma once
#include "PipePresenter.h"
#include "wxcrafter.h"


// диалоговое окно CDistDialog

class CDistDialog : public CDistBaseDialog
{
	//DECLARE_DYNAMIC(CDistDialog)

public:
	CDistDialog(CPipePresenter& pipes, CWnd* pParent = nullptr);; // стандартный конструктор
	virtual ~CDistDialog();


protected:
	CPipePresenter& m_pipes;
	//void DoDataExchange(CDataExchange* pDX); 

	//DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	int m_nFrom;
	int m_nTo;
};

