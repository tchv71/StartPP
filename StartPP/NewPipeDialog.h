#pragma once
#include "Pipe.h"
#include "wxcrafter.h"


// диалоговое окно CNewPipeDialog

class CNewPipeDialog : public CNewPipeBaseDialog
{
public:
	CNewPipeDialog(CWnd* pParent, CPipes& pipes); // стандартный конструктор
	virtual ~CNewPipeDialog();

protected:
	DECLARE_MESSAGE_MAP()
    virtual void EndModal(int retcode) wxOVERRIDE;

public:
	int m_nNAYZ;
	int m_nKOYZ;
	CPipes& m_pipes;
	BOOL OnInitDialog();
	void OnLbChange(wxCommandEvent& event);
	bool OnOK();
};

