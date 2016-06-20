#pragma once
#include "StartPPDoc.h"
#include "wxcrafter.h"


// диалоговое окно CDelPipesDialog

class CDelPipesDialog : public CDelPipesBaseDialog
{
	//DECLARE_DYNAMIC(CDelPipesDialog)

public:
	CDelPipesDialog(CWnd* pParent, CStartPPDoc* pDoc); // стандартный конструктор
	virtual ~CDelPipesDialog();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CStartPPDoc* m_pDoc;
	//CListBox m_listbox;
	BOOL OnInitDialog();
	void OnOK();
    virtual void EndModal(int retcode) wxOVERRIDE;

};

