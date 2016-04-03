#pragma once

#include <vector>
#include "PipeAndNode.h" 

class CPipes
{
public:
	CPipes(size_t& n_Idx, std::vector<CPipeAndNode>& vecPipes);
	~CPipes(void);
	size_t& m_nIdx;
	unsigned m_SearchIdx;
	std::vector<CPipeAndNode>& m_vecPnN;
public:
	void FillCb(CComboBox* pCb, int& MaxNodeNum);
	void FillLb(CListBox* pLb, int& MaxNodeNum);
	void FillLb1(CListBox* pLb);
	bool InsertPipe(int nIdx, int NEW_NAYZ, int NEW_KOYZ);
	void SetINDX(int nIdx, int nPipes);
	void CopyValues(CPipeAndNode& p, const CPipeAndNode& p1);
	bool FindFirstNAYZ(int nNAYZ);
	bool FindNextNAYZ(int nNAYZ);
	bool FindFirstKOYZ(int nKOYZ);
	bool FindNextKOYZ(int nKOYZ);
};

