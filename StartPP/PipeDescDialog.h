#pragma once
#include "wxcrafter.h"

class CPipeDesc;

// диалоговое окно CPipeDescDialog

class CPipeDescDialog : public CPipeDescBaseDialog
{
	//DECLARE_DYNAMIC(CPipeDescDialog)

public:
	CPipeDescDialog(CPipeDesc& rPipeDesc, CWnd* pParent = nullptr); // стандартный конструктор
	virtual ~CPipeDescDialog();

protected:
	CPipeDesc& m_rPipeDesc;
    virtual void EndModal(int retcode) wxOVERRIDE;
	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	//CComboBox m_cbNormaDoc;
	//CDateTimeCtrl m_ctlDate;
	//CComboBox m_cbStrings;
	//CComboBox m_cbIsp;
	//CComboBox m_cbComp;
	void OnLBIspChange(wxCommandEvent& event);
	void OnCbnSelchangeComboStrings(wxCommandEvent& event);
	//CComboBox m_cbStrings2;
	//CComboBox m_cbString3;
	void OnCbnSelchangeComboComp(wxCommandEvent& event);
	bool OnOK() const;
};

