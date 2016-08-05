#include "stdafx.h"
#include "AddSchemDialog.h"
#include "Pipe.h"
#include "VecPnN.h"


CAddSchemDlg::CAddSchemDlg(wxWindow* parent, CVecPnN& p, CVecPnN& pNew) : CAddSchemDialogBase(parent),
	m_p(p), m_pNew(pNew)
{
	OnInitDialog();
}

CAddSchemDlg::~CAddSchemDlg()
{
}

BOOL CAddSchemDlg::OnInitDialog()
{
	CPipes pipes(m_p.m_nIdx, m_p.m_vecPnN);
	int nMaxNodeNum;
	pipes.FillCb(m_choice, nMaxNodeNum);
	return TRUE; // return TRUE unless you set the focus to a control
				 // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddSchemDlg::EndModal(int retcode)
{
	if (retcode == wxID_OK)
	{
		m_pNew.m_vecPnN[1].m_NAYZ = m_p.m_vecPnN[m_choice->GetSelection()].m_KOYZ;
		for (unsigned i = 1; i < m_pNew.m_vecPnN.size(); i++)
			m_p.m_vecPnN.push_back(m_pNew.m_vecPnN[i]);
	}
	CAddSchemDialogBase::EndModal(retcode);
}


