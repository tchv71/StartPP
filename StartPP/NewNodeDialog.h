#pragma once
#include "Pipe.h"
#include "afxwin.h"

// диалоговое окно CNewNodeDialog

class CNewNodeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CNewNodeDialog)

public:
	CNewNodeDialog(CWnd* pParent, CPipes& pipes); // стандартный конструктор
	virtual ~CNewNodeDialog();

	// Данные диалогового окна
	enum
	{
		IDD = IDD_NEW_NODE
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override; // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CPipes m_pipes;
	CButton m_btnCheck;
	CButton m_btnRadio;
	CComboBox m_combo;
	int m_nNewNode;
	//	CEdit m_eDist;
	//	int m_nPipes;
	INT_PTR DoModal() override;
	void OnOK() override;
	int m_nPipes;
	CEdit m_eDist;
	CEdit m_ePipes;
	BOOL OnInitDialog() override;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	BOOL PreTranslateMessage(MSG* pMsg) override;
};

