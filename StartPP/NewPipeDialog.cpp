// NewPipeDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "NewPipeDialog.h"
#include "Strings.h"

// диалоговое окно CNewPipeDialog

CNewPipeDialog::CNewPipeDialog(CWnd* pParent /*=nullptr*/, CPipes& pipes)
	: CNewPipeBaseDialog(pParent)
	  , m_nNAYZ(0)
	  , m_nKOYZ(0)
	  , m_pipes(pipes)
{
    OnInitDialog();
}

CNewPipeDialog::~CNewPipeDialog()
{
}


BEGIN_MESSAGE_MAP(CNewPipeDialog, CNewPipeBaseDialog)
	EVT_CHOICE(wxID_AFTER_NODE_CHOICE, CNewPipeDialog::OnLbChange)
END_MESSAGE_MAP()


// обработчики сообщений CNewPipeDialog


BOOL CNewPipeDialog::OnInitDialog()
{
	//CDialog::OnInitDialog();
	int MaxNodeNum;
	m_pipes.FillCb(m_choice, MaxNodeNum);
	m_nNAYZ = int(m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ);
	m_nKOYZ = MaxNodeNum + 1;
    m_textCtrlStartNode->SetValue(CString::Format(_T("%d"), m_nNAYZ));
    m_textCtrlEndNode->SetValue(CString::Format(_T("%d"), m_nKOYZ));
	//UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CNewPipeDialog::OnLbChange(wxCommandEvent& event)
{
	m_nNAYZ = int(m_pipes.m_vecPnN[m_choice->GetSelection()].m_KOYZ);
    m_textCtrlStartNode->SetValue(CString::Format(_T("%d"), m_nNAYZ));
	event.Skip();
}


bool CNewPipeDialog::OnOK()
{
	//CDialog::OnOK();
	long l;
    if (!m_textCtrlStartNode->GetValue().ToCLong(&l))
	{
		AfxMessageBox(IDS_NUMBER_ERROR, wxOK | wxICON_ERROR);
		return false;
	}

	m_nNAYZ = l;
    if (!m_textCtrlEndNode->GetValue().ToCLong(&l))
	{
		AfxMessageBox(IDS_NUMBER_ERROR, wxOK | wxICON_ERROR);
		return false;
	}
	m_nKOYZ = l;
	if (!m_pipes.FindFirstNAYZ(m_nNAYZ) && !m_pipes.FindFirstKOYZ(m_nNAYZ))
	{
		AfxMessageBox(wxString::Format(IDS_NODE_NOT_EXIST, m_nNAYZ), wxOK | wxICON_ERROR);
		return false;
	}
	if (m_pipes.FindFirstNAYZ(m_nKOYZ) || m_pipes.FindFirstKOYZ(m_nKOYZ))
	{
		AfxMessageBox(wxString::Format(IDS_NODE_EXISTS, m_nKOYZ), wxOK | wxICON_ERROR);
		return false;
	}
	m_pipes.InsertPipe(m_choice->GetSelection(), m_nNAYZ, m_nKOYZ);
	return true;
}

void CNewPipeDialog::EndModal(int retcode)
{
    if (retcode == wxID_OK)
	{
		if (!OnOK())
			return;
	}
	CNewPipeBaseDialog::EndModal(retcode);
}
