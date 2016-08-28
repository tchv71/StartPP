#pragma once
#include "PipePresenter.h"


// диалоговое окно CDistDialog

class CDistDialog : public CDialog
{
	//DECLARE_DYNAMIC(CDistDialog)

public:
	CDistDialog(CPipePresenter& pipes, CWnd* pParent = nullptr) : CDialog(pParent, wxID_ANY, _T("")), m_pipes(pipes) {}; // стандартный конструктор
	virtual ~CDistDialog() {};


protected:
	CPipePresenter& m_pipes;
	void DoDataExchange(CDataExchange* pDX); 

	//DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	int m_nFrom;
	int m_nTo;
};

