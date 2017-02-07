// DistDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "DistDialog.h"


// диалоговое окно CDistDialog

//IMPLEMENT_DYNAMIC(CDistDialog, CDialog)



CDistDialog::CDistDialog(CPipePresenter& pipes, CWnd* pParent): CDistBaseDialog(pParent)
, m_pipes(pipes)
, m_nFrom(0)
, m_nTo(0)
{
	OnInitDialog();
}

CDistDialog::~CDistDialog()
{
}


// обработчики сообщений CDistDialog

extern float Round(float x, int N);


BOOL CDistDialog::OnInitDialog()
{
	wxASSERT(m_pipes.m_pvecSel->size()==2);
	auto it = m_pipes.m_pvecSel->begin();
	m_nFrom = it->SelNAYZ;
	++it;
	m_nTo = it->SelNAYZ;
	m_textCtrlStart->SetValue(CString::Format(_T("%d"), m_nFrom));
	m_textCtrlEnd->SetValue(CString::Format(_T("%d"), m_nTo));
	CPipePresenter::SPoint* p1 = &(m_pipes.m_Points.find(m_nFrom)->second);
	CPipePresenter::SPoint* p2 = &(m_pipes.m_Points.find(m_nTo)->second);
	float dx = p2->x - p1->x;
	float dy = p2->y - p1->y;
	float dz = p2->z - p1->z;
	float d = Round(sqrt(dx * dx + dy * dy + dz * dz), 3);
	CDataExchange DX(this, false);
	m_textCtrlDistAll->SetValue(CString::Format(_T("%g"), d));
	m_textCtrlDistX->SetValue(CString::Format(_T("%g"), dx));
	m_textCtrlDistY->SetValue(CString::Format(_T("%g"), dy));
	m_textCtrlDistZ->SetValue(CString::Format(_T("%g"), dz));
	return TRUE; // return TRUE unless you set the focus to a control
}

