#include "stdafx.h"
#include "PropertiesWnd.h"
#include "StartPPDoc.h"
#include "MainFrame.h"

CStartPPDoc::CStartPPDoc()
{
}

CStartPPDoc::~CStartPPDoc()
{

}

BOOL CStartPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPipeAndNode p;
	p.m_KOYZ = 1;
	p.m_MNEO = "мо";
	m_pipes.m_vecPnN.push_back(p);
	p.m_MNEO = "";
	p.m_RADA = 16.0f;
	p.m_RATE = 150.0f;
	p.m_KOPE = 0.8f;
	p.m_KOPR = 1.0f;
	p.m_OSIX = 1.0f;
	p.m_KOYZ = 2;
	p.m_NAYZ = 1;
	m_pipes.m_vecPnN.push_back(p);
	m_pipes.m_nIdx = 1;
	vecSel.insert(SelStr(1, 2));
	m_pFrame->GetPropWnd()->m_PropMode = E_PIPE;

	UpdateAllViews(nullptr);
	UpdateData(FALSE);
	return TRUE;
}


void CStartPPDoc::SetUndo(void)
{
	if (!m_vecUndo.size() == 0 && m_pipes.m_vecPnN.size() == m_vecUndo[m_vecUndo.size() - 1].vec.m_vecPnN.size())
	{
		std::vector<CPipeAndNode>& vecTop = m_vecUndo[m_vecUndo.size() - 1].vec.m_vecPnN;
		unsigned i;
		for (i = 0; i < vecTop.size(); i++)
		{
			if (memcmp(&vecTop[i], &m_pipes.m_vecPnN[i], sizeof(CPipeAndNode)) != 0)
				break;
		}
		if (i == vecTop.size())
			return;
	}
	m_vecUndo.push_back(SUndo(m_pipes, vecSel));
	m_nUndoPos = m_vecUndo.size() - 1;
}



void CStartPPDoc::UpdateData(bool bSaveAndValidate)
{
	CDataExchange dx(m_pFrame, bSaveAndValidate);
	m_pFrame->GetPropWnd()->DoDataExchange(&dx, &m_pipes.CurPipe(), this);
	//m_pFrame->m_wndPipeTable.DoDataExchange(&dx, this);
	if (!bSaveAndValidate)
	{
		SetUndo();
		UpdateAllViews(nullptr); // Selection is changed
	}
}

void CStartPPDoc::PnNIsUpdated(void)
{
	m_bModified = true;
	SetUndo();
	UpdateAllViews(nullptr);
}


CPipeAndNode* CStartPPDoc::GetPrevPnN(int NAYZ)
{
	for (unsigned i = 0; i < m_pipes.m_vecPnN.size(); i++)
		if (fabs(m_pipes.m_vecPnN[i].m_KOYZ - NAYZ) < 1e-3f)
			return &m_pipes.m_vecPnN[i];
	return nullptr;
}


void CStartPPDoc::RotateThisAndOthers(float fAngle)
{
	m_bvecRotated.resize(m_pipes.m_vecPnN.size());
	for (unsigned i = 0; i < m_bvecRotated.size(); i++)
		m_bvecRotated[i] = false;
	RotateOne(m_pipes.m_nIdx, fAngle);
	RotateAll(int(m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ), fAngle);
}

void CStartPPDoc::RotateThisAndOthers(CPipeAndNode* pPnN, float fAngle)
{
	m_bvecRotated.resize(m_pipes.m_vecPnN.size());
	int nIdx = 0;
	for (unsigned i = 0; i < m_bvecRotated.size(); i++)
	{
		m_bvecRotated[i] = false;
		if (pPnN->m_NAYZ == m_pipes.m_vecPnN[i].m_NAYZ && pPnN->m_KOYZ == m_pipes.m_vecPnN[i].m_KOYZ)
			nIdx = i;
	}
	RotateOne(nIdx, fAngle);
	RotateAll(int(m_pipes.m_vecPnN[nIdx].m_KOYZ), fAngle);
}


extern float Round(float x, int N);


void CStartPPDoc::RotateOne(size_t recNo, float fAngle)
{
	float x, y, x1, y1;
	x = m_pipes.m_vecPnN[recNo].m_OSIX;
	y = m_pipes.m_vecPnN[recNo].m_OSIY;
	m_bvecRotated[recNo] = true;
	x1 = Round(x * cos(fAngle) - y * sin(fAngle), 3);
	y1 = Round(x * sin(fAngle) + y * cos(fAngle), 3);
	m_pipes.m_vecPnN[recNo].m_OSIX = x1;
	m_pipes.m_vecPnN[recNo].m_OSIY = y1;
}


void CStartPPDoc::RotateAll(int NAYZ, float fAngle)
{
	unsigned i = 0;
	bool bFound = false;
	for (; i < m_pipes.m_vecPnN.size(); i++)
		if (fabs(m_pipes.m_vecPnN[i].m_NAYZ - NAYZ) < 1e-3f)
		{
			bFound = true;
			break;
		}
	while (bFound)
	{
		if (!m_bvecRotated[i])
		{
			RotateOne(i, fAngle);
			RotateAll(int(m_pipes.m_vecPnN[i].m_KOYZ), fAngle);
		}
		i++;
		bFound = false;
		for (; i < m_pipes.m_vecPnN.size(); i++)
			if (fabs(m_pipes.m_vecPnN[i].m_NAYZ - NAYZ) < 1e-3f)
			{
				bFound = true;
				break;
			}
	}
}


void CStartPPDoc::Select(int NAYZ, int KOYZ)
{
	vecSel.SelNAYZ = NAYZ;
	vecSel.SelKOYZ = KOYZ;
	if (NAYZ < 0 || KOYZ < 0)
	{
		vecSel.clear();
		return;
	}
	if (vecSel.size() == 0)
	{
		vecSel.insert(SelStr(NAYZ, KOYZ));
	}
	else if (vecSel.size() == 1)
	{
		vecSel.clear();
		vecSel.insert(SelStr(NAYZ, KOYZ));
	}
	if (NAYZ == KOYZ)
	{
		for (unsigned i = 0; i < m_pipes.m_vecPnN.size(); i++)
			if (fabs(m_pipes.m_vecPnN[i].m_KOYZ - NAYZ) < 1e-3f)
			{
				UpdateData(TRUE);
				m_pipes.m_nIdx = i;
				m_pFrame->GetPropWnd()->m_PropMode = E_NODE;
				UpdateData(FALSE);
				break;
			}
		return;
	}

	for (unsigned i = 0; i < m_pipes.m_vecPnN.size(); i++)
		if (fabs(m_pipes.m_vecPnN[i].m_NAYZ - NAYZ) < 1e-3f && fabs(m_pipes.m_vecPnN[i].m_KOYZ - KOYZ) < 1e-3f)
		{
			UpdateData(TRUE);
			m_pipes.m_nIdx = i;
			m_pFrame->GetPropWnd()->m_PropMode = E_PIPE;
			UpdateData(FALSE);
			break;
		}
}

#ifdef _DEBUG
void CStartPPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStartPPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
