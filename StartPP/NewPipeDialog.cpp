// NewPipeDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "NewPipeDialog.h"


// диалоговое окно CNewPipeDialog

IMPLEMENT_DYNAMIC(CNewPipeDialog, CDialog)

CNewPipeDialog::CNewPipeDialog(CWnd* pParent /*=nullptr*/, CPipes& pipes)
	: CDialog(CNewPipeDialog::IDD, pParent)
	  , m_nNAYZ(0)
	  , m_nKOYZ(0)
	  , m_pipes(pipes)
{
}

CNewPipeDialog::~CNewPipeDialog()
{
}

void CNewPipeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_nNAYZ);
	DDX_Text(pDX, IDC_EDIT2, m_nKOYZ);
}


BEGIN_MESSAGE_MAP(CNewPipeDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO1,OnLbChange)
	END_MESSAGE_MAP()


// обработчики сообщений CNewPipeDialog


BOOL CNewPipeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	int MaxNodeNum;
	m_pipes.FillCb(&m_combo, MaxNodeNum);
	m_nNAYZ = int(m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ);
	m_nKOYZ = MaxNodeNum + 1;
	UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CNewPipeDialog::OnLbChange(void)
{
	m_nNAYZ = int(m_pipes.m_vecPnN[m_combo.GetCurSel()].m_KOYZ);
	UpdateData(FALSE);
}


void CNewPipeDialog::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnOK();
	m_pipes.InsertPipe(m_combo.GetCurSel(), m_nNAYZ, m_nKOYZ);
}

