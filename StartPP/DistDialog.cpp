// DistDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "DistDialog.h"
#include <math.h>


// диалоговое окно CDistDialog

//IMPLEMENT_DYNAMIC(CDistDialog, CDialog)

CDistDialog::CDistDialog(CPipePresenter& pipes, CWnd* pParent /*=nullptr*/)
	: CDialog(CDistDialog::IDD, pParent), m_pipes(pipes)
	  , m_nFrom(0)
	  , m_nTo(0)
{
}

CDistDialog::~CDistDialog()
{
}

void CDistDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FROM, m_nFrom);
	DDX_Text(pDX, IDC_EDIT_TO, m_nTo);
}


BEGIN_MESSAGE_MAP(CDistDialog, CDialog)
	END_MESSAGE_MAP()


// обработчики сообщений CDistDialog

extern float Round(float x, int N);


BOOL CDistDialog::OnInitDialog()
{
	ASSERT(m_pipes.pvecSel->size()==2);
	auto it = m_pipes.pvecSel->begin();
	m_nFrom = it->SelNAYZ;
	++it;
	m_nTo = it->SelNAYZ;
	CPipePresenter::SPoint* p1 = &(m_pipes.Points.find(m_nFrom)->second);
	CPipePresenter::SPoint* p2 = &(m_pipes.Points.find(m_nTo)->second);
	float dx = p2->x - p1->x;
	float dy = p2->y - p1->y;
	float dz = p2->z - p1->z;
	float d = Round(sqrt(dx * dx + dy * dy + dz * dz), 3);
	CDataExchange DX(this, false);
	DDX_Text(&DX, IDC_EDIT_DIST_ALL, d);
	DDX_Text(&DX, IDC_EDIT_DIST_X, dx);
	DDX_Text(&DX, IDC_EDIT_DIST_Y, dy);
	DDX_Text(&DX, IDC_EDIT_DIST_Z, dz);

	CDialog::OnInitDialog();

	return TRUE; // return TRUE unless you set the focus to a control
}

