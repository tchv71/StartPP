// NewPipeDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "NewPipeDialog.h"


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
}


void CNewPipeDialog::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	//CDialog::OnOK();
	long l;
    m_textCtrlStartNode->GetValue().ToCLong(&l);
	m_nNAYZ = l;
    m_textCtrlEndNode->GetValue().ToCLong(&l);
	m_nKOYZ = l;
	m_pipes.InsertPipe(m_choice->GetSelection(), m_nNAYZ, m_nKOYZ);
}

void CNewPipeDialog::EndModal(int retcode)
{
    if (retcode == wxID_OK)
        OnOK();
    CNewPipeBaseDialog::EndModal(retcode);
}
