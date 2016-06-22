#pragma once
#include "Pipe.h"
#include "wxcrafter.h"
//#include "resource.h"

// диалоговое окно CMultPipeDialog

class CMultPipeDialog : public CMultPipeBaseDialog
{

public:
	CMultPipeDialog(CWnd* pParent, CPipes& pipes); // стандартный конструктор
	virtual ~CMultPipeDialog();


protected:
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo;
	int m_NAYZ;
	int m_KOYZ;
	int m_nPipes;
	CPipes& m_pipes;
	BOOL OnInitDialog();
	void OnOK();
	void EndModal(int retcode) wxOVERRIDE;
	//	void OnLbChange(void);
	afx_msg void OnChangeEdit1(wxCommandEvent& event);
	afx_msg void OnChangeEdit2(wxCommandEvent& event);
	afx_msg void OnChangeEdit3(wxCommandEvent& event);
};

