// MultPipeDialog.cpp: ГґГ Г©Г« Г°ГҐГ Г«ГЁГ§Г Г¶ГЁГЁ
//

#include "stdafx.h"
#include "StartPP.h"
#include "MultPipeDialog.h"
#include "Strings.h"

// Г¤ГЁГ Г«Г®ГЈГ®ГўГ®ГҐ Г®ГЄГ­Г® CMultPipeDialog

CMultPipeDialog::CMultPipeDialog(CWnd* pParent, CPipes& pipes)
	: CMultPipeBaseDialog(pParent)
	  , m_NAYZ(0)
	  , m_KOYZ(0)
	  , m_nPipes(2)
	  , m_pipes(pipes)
      , m_bModifying(false)
{
	OnInitDialog();
}

CMultPipeDialog::~CMultPipeDialog()
{
}


BEGIN_MESSAGE_MAP(CMultPipeDialog, CMultPipeBaseDialog)
	//	ON_CBN_SELCHANGE(IDC_COMBO1,OnLbChange)
	EVT_TEXT(wxID_EDIT1, CMultPipeDialog::OnChangeEdit1)
	EVT_TEXT(wxID_EDIT2, CMultPipeDialog::OnChangeEdit2)
	EVT_SPINCTRL(wxID_EDIT3, CMultPipeDialog::OnChangeEdit3)
END_MESSAGE_MAP()



BOOL CMultPipeDialog::OnInitDialog()
{
	//CDialog::OnInitDialog();
	int nMaxNodeNum;
	m_pipes.FillCb(m_choice, nMaxNodeNum);
	m_NAYZ = nMaxNodeNum + 1;
	m_KOYZ = nMaxNodeNum + m_nPipes;

    m_bModifying = true;
	m_textCtrlStartNode->SetValue(CString::Format(_T("%d"), m_NAYZ));
	m_textCtrlEndNode->SetValue(CString::Format(_T("%d"), m_KOYZ));
	m_textCtrlNumPipes->SetValue(m_nPipes);
    m_bModifying = false;
	//UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
}


void CMultPipeDialog::OnOK()
{
	//UpdateData(TRUE);
	int nIdx = m_choice->GetSelection();
	for (int i = m_NAYZ; i <= m_KOYZ; i++)
		for (unsigned j = 0; j < m_pipes.m_vecPnN.size(); j++)
			if (m_pipes.m_vecPnN[j].m_NAYZ == i || m_pipes.m_vecPnN[j].m_KOYZ == i)
			{
				CString str;
				str.Format(LoadStr(IDS_NODE_EXISTS), i);
				AfxMessageBox(str, wxOK);
				return;
			}
	m_pipes.SetINDX(nIdx, m_KOYZ - m_NAYZ + 1);
	int nNewIdx = nIdx + 1;
	int IDX_F = int(m_pipes.m_vecPnN[nIdx].m_INDX) + 100;
	for (int i = m_NAYZ; i <= m_KOYZ; i++)
	{
		CPipeAndNode p = m_pipes.m_vecPnN[nIdx];
		m_pipes.m_vecPnN.insert(m_pipes.m_vecPnN.begin() + nNewIdx, p);
		m_pipes.m_vecPnN[nNewIdx].m_INDX = float(IDX_F);
		m_pipes.m_vecPnN[nNewIdx].m_NAYZ = float(i == m_NAYZ ? int(m_pipes.m_vecPnN[nIdx].m_KOYZ) : i - 1);
		m_pipes.m_vecPnN[nNewIdx].m_KOYZ = float(i);
		nNewIdx++;
		IDX_F += 100;
	}
	m_pipes.m_nIdx = nIdx + 1;

	//CDialog::OnOK();
}

//void CMultPipeDialog::OnLbChange(void)
//{
//	m_NAYZ = m_pipes.m_vecPnN[m_combo.GetCurSel()].m_KOYZ;
//	UpdateData(FALSE);
//}


void CMultPipeDialog::OnChangeEdit1(wxCommandEvent& event)
{
    if (m_bModifying)
        return;
	long l;
	m_textCtrlStartNode->GetValue().ToCLong(&l);
	m_NAYZ = l;
	m_KOYZ = m_NAYZ + m_nPipes - 1;
    m_bModifying = true;
	m_textCtrlEndNode->SetValue(CString::Format(_T("%d"), m_KOYZ));
    m_bModifying = false;
}


void CMultPipeDialog::OnChangeEdit2(wxCommandEvent& event)
{
    if (m_bModifying)
        return;
	long l;
	m_textCtrlEndNode->GetValue().ToCLong(&l);
	m_KOYZ = l;
	m_nPipes = m_KOYZ - m_NAYZ + 1;
    m_bModifying = true;
	m_textCtrlNumPipes->SetValue(m_nPipes);
    m_bModifying = false;
}


void CMultPipeDialog::OnChangeEdit3(wxSpinEvent& event)
{
    if (m_bModifying)
        return;
	m_nPipes = m_textCtrlNumPipes->GetValue();
	m_KOYZ = m_NAYZ + m_nPipes - 1;
    m_bModifying = true;
	m_textCtrlEndNode->SetValue(CString::Format(_T("%d"), m_KOYZ));
    m_bModifying = false;
}

void CMultPipeDialog::EndModal(int retcode)
{
	if (retcode == wxID_OK)
		OnOK();
	CMultPipeBaseDialog::EndModal(retcode);
}
