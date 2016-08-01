#pragma once
#include "PipePresenter.h"
#include "Resource.h"


// äèàëîãîâîå îêíî CDistDialog

class CDistDialog : public CDialog
{
	//DECLARE_DYNAMIC(CDistDialog)

public:
	CDistDialog(CPipePresenter& pipes, CWnd* pParent = nullptr) : CDialog(pParent, wxID_ANY, _T("")), m_pipes(pipes) {}; // ñòàíäàðòíûé êîíñòðóêòîð
	virtual ~CDistDialog() {};

	// Äàííûå äèàëîãîâîãî îêíà
	enum
	{
		IDD = IDD_DIST
	};

protected:
	CPipePresenter& m_pipes;
	void DoDataExchange(CDataExchange* pDX); // ïîääåðæêà DDX/DDV

	//DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	int m_nFrom;
	int m_nTo;
};

