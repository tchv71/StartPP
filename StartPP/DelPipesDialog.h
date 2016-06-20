#pragma once
#include "afxwin.h"
#include "StartPPDoc.h"
#include "resource.h"

// диалоговое окно CDelPipesDialog

class CDelPipesDialog : public CDialog
{
	DECLARE_DYNAMIC(CDelPipesDialog)

public:
	CDelPipesDialog(CWnd* pParent, CStartPPDoc* pDoc); // стандартный конструктор
	virtual ~CDelPipesDialog();

	// Данные диалогового окна
	enum
	{
		IDD = IDD_DEL_PIPES
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override; // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CStartPPDoc* m_pDoc;
	CListBox m_listbox;
	BOOL OnInitDialog() override;
	afx_msg  void OnLbnSelchangeList1();
	void OnOK() override;
};

