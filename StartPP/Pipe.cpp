#include "stdafx.h"
#include "Pipe.h"
#include "Strings.h"

CPipes::CPipes(size_t& n_Idx, std::vector<CPipeAndNode>& vecPipes) :
	m_nIdx(n_Idx), m_SearchIdx(0), m_vecPnN(vecPipes)
{
}


CPipes::~CPipes()
{
}


void CPipes::FillCb(CComboBox* pCb, int& MaxNodeNum) const
{
	MaxNodeNum = 0;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CString str = CString::Format(_T("%g - %g"), m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ);
		pCb->Append(str);
		if (m_vecPnN[i].m_NAYZ > MaxNodeNum)
			MaxNodeNum = int(m_vecPnN[i].m_NAYZ);
		if (m_vecPnN[i].m_KOYZ > MaxNodeNum)
			MaxNodeNum = int(m_vecPnN[i].m_KOYZ);
	}
	pCb->SetSelection(int(m_nIdx));
}

void CPipes::FillLb(CListBox* pLb, int& MaxNodeNum) const
{
	MaxNodeNum = 0;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CString str = CString::Format(_T("%g - %g"), m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ);
		pLb->Append(str);
		if (m_vecPnN[i].m_NAYZ > MaxNodeNum)
			MaxNodeNum = int(m_vecPnN[i].m_NAYZ);
		if (m_vecPnN[i].m_KOYZ > MaxNodeNum)
			MaxNodeNum = int(m_vecPnN[i].m_KOYZ);
		pLb->SetClientData(i, reinterpret_cast<void*>(size_t(m_vecPnN[i].m_NAYZ) << 16 | size_t(m_vecPnN[i].m_KOYZ)));
	}
	pLb->SetSelection(int(m_nIdx));
}

void CPipes::FillLb1(CListBox* pLb) const
{
	for (size_t i = 0; i < m_vecPnN.size(); i++)
	{
		CString str = CString::Format(_T("%g - %g"), m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ);
		pLb->Append(str);
		pLb->SetClientData(int(i), reinterpret_cast<void*>(i));
	}
}

//extern LPCTSTR LoadStr(UINT nID);

bool CPipes::InsertPipe(int nIdx, int NEW_NAYZ, int NEW_KOYZ) const
{
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
		if (m_vecPnN[i].m_NAYZ == NEW_NAYZ && m_vecPnN[i].m_KOYZ == NEW_KOYZ)
		{
			CString str = CString::Format(LoadStr(IDS_FORMAT_PIPE_EXISTS), NEW_NAYZ, NEW_KOYZ);
			AfxMessageBox(str, wxOK | wxICON_EXCLAMATION);
			return false;
		}
	SetINDX(nIdx, 1);
	CPipeAndNode p;
	CopyValues(p, m_vecPnN[nIdx]);
	p.m_NAYZ = float(NEW_NAYZ);
	p.m_KOYZ = float(NEW_KOYZ);
	p.m_INDX = m_vecPnN[nIdx].m_INDX + 100;
	m_vecPnN.insert(m_vecPnN.begin() + nIdx + 1, p);
	m_nIdx = nIdx + 1;
	return true;
}


void CPipes::SetINDX(int nIdx, int nPipes) const
{
	int nINDX = int(m_vecPnN[nIdx].m_INDX) + 100;
	int nNewIdx = nINDX + nPipes * 100;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
		if (m_vecPnN[i].m_INDX >= nINDX)
		{
			m_vecPnN[i].m_INDX = float(nNewIdx);
			nNewIdx += 100;
		}
}


void CPipes::CopyValues(CPipeAndNode& p, const CPipeAndNode& p1)
{
	p.m_OSIX = p1.m_OSIX;
	p.m_OSIY = p1.m_OSIY;
	p.m_OSIZ = p1.m_OSIZ;
	p.m_NAMA = p1.m_NAMA;
	p.m_DIAM = p1.m_DIAM;
	p.m_NTOS = p1.m_NTOS;
	p.m_RTOS = p1.m_RTOS;
	p.m_RATE = p1.m_RATE;
	p.m_RADA = p1.m_RADA;
	p.m_VETR = p1.m_VETR;
	p.m_VEIZ = p1.m_VEIZ;
	p.m_VEPR = p1.m_VEPR;
	p.m_KOPE = p1.m_KOPE;
	p.m_KOPR = p1.m_KOPR;
	p.m_KOYS = p1.m_KOYS;
	p.m_KORA = p1.m_KORA;
	p.m_DABI = p1.m_DABI;
	p.m_PELI = "л";
	p.m_PEYG = "у";
	if (p1.m_NAGV < 0)
	{
		p.m_NAGV = -1;
		p.m_NAGX = p1.m_NAGX;
		p.m_NAGY = 0;
		p.m_NAGZ = p1.m_NAGZ;
	}
	else
	{
		p.m_NAGV = 0;
		p.m_NAGX = 0;
		p.m_NAGY = 0;
		p.m_NAGZ = 0;
	}
	p.m_NAAN = p1.m_NAAN;
	p.m_NABA = p1.m_NABA;
	p.m_VIZA = p1.m_VIZA2;
	p.m_VIZA2 = p1.m_VIZA2;
	p.m_OS_TR1 = p1.m_OS_TR2;
	p.m_OS_TR2 = p1.m_OS_TR2;
	p.m_SHTR = p1.m_SHTR;
	p.m_VIVO = p1.m_VIVO;
}


bool CPipes::FindFirstNAYZ(int nNAYZ)
{
	for (m_SearchIdx = 0; m_SearchIdx < m_vecPnN.size(); m_SearchIdx++)
		if (m_vecPnN[m_SearchIdx].m_NAYZ == nNAYZ)
			return true;
	return false;
}

bool CPipes::FindNextNAYZ(int nNAYZ)
{
	m_SearchIdx++;
	for (; m_SearchIdx < m_vecPnN.size(); m_SearchIdx++)
		if (m_vecPnN[m_SearchIdx].m_NAYZ == nNAYZ)
			return true;
	return false;
}

bool CPipes::FindFirstKOYZ(int nKOYZ)
{
	for (m_SearchIdx = 0; m_SearchIdx < m_vecPnN.size(); m_SearchIdx++)
		if (m_vecPnN[m_SearchIdx].m_KOYZ == nKOYZ)
			return true;
	return false;
}

bool CPipes::FindNextKOYZ(int nKOYZ)
{
	m_SearchIdx++;
	for (; m_SearchIdx < m_vecPnN.size(); m_SearchIdx++)
		if (m_vecPnN[m_SearchIdx].m_KOYZ == nKOYZ)
			return true;
	return false;
}

