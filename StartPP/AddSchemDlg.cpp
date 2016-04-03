// AddSchemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddSchemDlg.h"
#include "VecPnN.h"
#include "Pipe.h"


// AddSchemDlg dialog

IMPLEMENT_DYNAMIC(CAddSchemDlg, CDialog)

CAddSchemDlg::CAddSchemDlg(CWnd* pParent, CVecPnN& p, CVecPnN& pNew)
	: CDialog(CAddSchemDlg::IDD, pParent), m_p(p), m_pNew(pNew)
{
}

CAddSchemDlg::~CAddSchemDlg()
{
}

void CAddSchemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
}


BEGIN_MESSAGE_MAP(CAddSchemDlg, CDialog)
	END_MESSAGE_MAP()


// AddSchemDlg message handlers

BOOL CAddSchemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CPipes pipes(m_p.m_nIdx, m_p.m_vecPnN);
	int nMaxNodeNum;
	pipes.FillCb(&m_combo, nMaxNodeNum);
	return TRUE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAddSchemDlg::OnOK()
{
	CDialog::OnOK();
	m_pNew.m_vecPnN[1].m_NAYZ = m_p.m_vecPnN[m_combo.GetCurSel()].m_KOYZ;
	for (unsigned i = 1; i < m_pNew.m_vecPnN.size(); i++)
		m_p.m_vecPnN.push_back(m_pNew.m_vecPnN[i]);
}

