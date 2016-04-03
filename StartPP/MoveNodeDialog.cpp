// MoveNodeDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "MoveNodeDialog.h"
#include <math.h>


// диалоговое окно CMoveNodeDialog

IMPLEMENT_DYNAMIC(CMoveNodeDialog, CDialog)

CMoveNodeDialog::CMoveNodeDialog(CWnd* pParent, CPipes& pipes)
	: CDialog(CMoveNodeDialog::IDD, pParent), m_pipes(pipes)
	  , m_nDist(0)
{
}

CMoveNodeDialog::~CMoveNodeDialog()
{
}

void CMoveNodeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_sNode);
	DDX_Text(pDX, IDC_EDIT1, m_nDist);
}


BEGIN_MESSAGE_MAP(CMoveNodeDialog, CDialog)
	END_MESSAGE_MAP()


// обработчики сообщений CMoveNodeDialog

extern LPCTSTR LoadStr(UINT nID);

BOOL CMoveNodeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString str;
	str.Format(_T("%g"), m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ);
	m_sNode.SetWindowText(str);
	return TRUE; // return TRUE unless you set the focus to a control
}


void CMoveNodeDialog::OnOK()
{
	UpdateData(TRUE);
	CString str;
	int nKOYZ = int(m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ);
	if (!m_pipes.FindFirstKOYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_NO_PIPES_UZ), nKOYZ);
		AfxMessageBox(str);
		return;
	}
	if (m_pipes.FindNextKOYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_2PIPES_IN), nKOYZ);
		AfxMessageBox(str);
		return;
	}

	if (!m_pipes.FindFirstNAYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_NO_PIPES_OUT), nKOYZ);
		AfxMessageBox(str);
		return;
	}
	if (m_pipes.FindNextNAYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_2_PIPES_OUT), nKOYZ);
		AfxMessageBox(str);
		return;
	}
	CPipeAndNode& p = m_pipes.m_vecPnN[m_pipes.m_nIdx];
	float dx1 = p.m_OSIX,
		dy1 = p.m_OSIY,
		dz1 = p.m_OSIZ,
		Len1 = sqrt(dx1 * dx1 + dy1 * dy1 + dz1 * dz1);
	m_pipes.FindFirstNAYZ(nKOYZ);
	CPipeAndNode& p1 = m_pipes.m_vecPnN[m_pipes.m_SearchIdx];
	//int NewEndNode= int(p1.m_KOYZ);
	float dx2 = p1.m_OSIX,
		dy2 = p1.m_OSIY,
		dz2 = p1.m_OSIZ,
		Len2 = sqrt(dx2 * dx2 + dy2 * dy2 + dz2 * dz2);

	if (fabs(Len1) < 0.001 || fabs(Len2) < 0.001)
	{
		AfxMessageBox(LoadStr(IDS_MN_NULL_LEN));
		return;
	}
	if (fabs(dx1 / Len1 - dx2 / Len2) > 0.001 || fabs(dy1 / Len1 - dy2 / Len2) > 0.001 ||
		fabs(dz1 / Len1 - dz2 / Len2) > 0.001)
	{
		str.Format(LoadStr(IDS_MN_IZLOM), p.m_KOYZ);
		AfxMessageBox(str);
		return;
	}
	if (((m_nDist > 0) && (m_nDist >= Len2)) || ((m_nDist < 0) && (fabs(m_nDist) >= Len1)))
	{
		AfxMessageBox(LoadStr(IDS_MN_TOO_MUCH_LEN));
		return;
	}

	p1.m_OSIX = dx2 * (1 - m_nDist / Len2);
	p1.m_OSIY = dy2 * (1 - m_nDist / Len2);
	p1.m_OSIZ = dz2 * (1 - m_nDist / Len2);

	p.m_OSIX = dx1 * (1 + m_nDist / Len1);
	p.m_OSIY = dy1 * (1 + m_nDist / Len1);
	p.m_OSIZ = dz1 * (1 + m_nDist / Len1);

	CDialog::OnOK();
}

