#pragma once
#include "Pipe.h"
#include "wxcrafter.h"

// диалоговое окно CNewNodeDialog

class CNewNodeDialog : public CNewNodeBaseDialog
{
public:
	CNewNodeDialog(CWnd* pParent, CPipes& pipes); // стандартный конструктор
	virtual ~CNewNodeDialog();
protected:
	//void DoDataExchange(CDataExchange* pDX) override; // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CPipes m_pipes;
	//CButton m_btnCheck;
	//CButton m_btnRadio;
	//CComboBox m_combo;
	int m_nNewNode;
	//	CEdit m_eDist;
	//	int m_nPipes;
	bool OnOK();
	int m_nPipes;
	//CEdit m_eDist;
	//CEdit m_ePipes;
	BOOL OnInitDialog();
	void EndModal(int retcode) wxOVERRIDE;

	afx_msg void OnCbnSelchangeCombo1(wxCommandEvent& event);
	afx_msg void OnBnClickedRadio1(wxCommandEvent& event);
	afx_msg void OnBnClickedRadio2(wxCommandEvent& event);
};

