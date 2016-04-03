#pragma once
#include "resource.h"

class CVecPnN;

// AddSchemDlg dialog

class CAddSchemDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddSchemDlg)

public:
	CAddSchemDlg(CWnd* pParent, CVecPnN& p, CVecPnN& pNew); // standard constructor
	virtual ~CAddSchemDlg();
	CComboBox m_combo;
	CVecPnN& m_p;
	CVecPnN& m_pNew;

	// Dialog Data
	enum
	{
		IDD = IDD_ADD_SCHEM
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog() override;
protected:
	void OnOK() override;
};

