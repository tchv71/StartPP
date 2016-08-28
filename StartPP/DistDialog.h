#pragma once
#include "PipePresenter.h"


// ?????????? ???? CDistDialog

class CDistDialog : public CDialog
{
	//DECLARE_DYNAMIC(CDistDialog)

public:
	CDistDialog(CPipePresenter& pipes, CWnd* pParent = nullptr) : CDialog(pParent, wxID_ANY, _T("")), m_pipes(pipes) {}; // ??????????? ???????????
	virtual ~CDistDialog() {};


protected:
	CPipePresenter& m_pipes;
	void DoDataExchange(CDataExchange* pDX); // ????????? DDX/DDV

	//DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	int m_nFrom;
	int m_nTo;
};

