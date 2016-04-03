// MultPipeDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "StartPP.h"
#include "MultPipeDialog.h"


// диалоговое окно CMultPipeDialog

IMPLEMENT_DYNAMIC(CMultPipeDialog, CDialog)

CMultPipeDialog::CMultPipeDialog(CWnd* pParent, CPipes& pipes)
	: CDialog(CMultPipeDialog::IDD, pParent)
	  , m_NAYZ(0)
	  , m_KOYZ(0)
	  , m_nPipes(2)
	  , m_pipes(pipes)
{
}

CMultPipeDialog::~CMultPipeDialog()
{
}

void CMultPipeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_NAYZ);
	DDX_Text(pDX, IDC_EDIT2, m_KOYZ);
	DDX_Text(pDX, IDC_EDIT3, m_nPipes);
}


BEGIN_MESSAGE_MAP(CMultPipeDialog, CDialog)
	//	ON_CBN_SELCHANGE(IDC_COMBO1,OnLbChange)
	ON_EN_CHANGE(IDC_EDIT1, &CMultPipeDialog::OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMultPipeDialog::OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMultPipeDialog::OnChangeEdit3)
	END_MESSAGE_MAP()


// обработчики сообщений CMultPipeDialog


BOOL CMultPipeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	int nMaxNodeNum;
	m_pipes.FillCb(&m_combo, nMaxNodeNum);
	m_NAYZ = nMaxNodeNum + 1;
	m_KOYZ = nMaxNodeNum + m_nPipes;
	UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
}

extern LPCTSTR LoadStr(UINT nID);

void CMultPipeDialog::OnOK()
{
	UpdateData(TRUE);
	int nIdx = m_combo.GetCurSel();
	for (int i = m_NAYZ; i <= m_KOYZ; i++)
		for (unsigned j = 0; j < m_pipes.m_vecPnN.size(); j++)
			if (m_pipes.m_vecPnN[j].m_NAYZ == i || m_pipes.m_vecPnN[j].m_KOYZ == i)
			{
				CString str;
				str.Format(LoadStr(IDS_NODE_EXISTS), i);
				AfxMessageBox(str, MB_OK);
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

	CDialog::OnOK();
}

//void CMultPipeDialog::OnLbChange(void)
//{
//	m_NAYZ = m_pipes.m_vecPnN[m_combo.GetCurSel()].m_KOYZ;
//	UpdateData(FALSE);
//}


void CMultPipeDialog::OnChangeEdit1()
{
	UpdateData(TRUE);
	m_KOYZ = m_NAYZ + m_nPipes - 1;
	UpdateData(FALSE);
}


void CMultPipeDialog::OnChangeEdit2()
{
	UpdateData(TRUE);
	m_nPipes = m_KOYZ - m_NAYZ + 1;
	UpdateData(FALSE);
}


void CMultPipeDialog::OnChangeEdit3()
{
	UpdateData(TRUE);
	m_KOYZ = m_NAYZ + m_nPipes - 1;
	UpdateData(FALSE);
}

