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
	void FillCb(CComboBox* pCb, int& MaxNodeNum) const;
	void FillLb(CListBox* pLb, int& MaxNodeNum) const;
	void FillLb1(CListBox* pLb) const;
	bool InsertPipe(int nIdx, int NEW_NAYZ, int NEW_KOYZ) const;
	void SetINDX(int nIdx, int nPipes) const;
	static void CopyValues(CPipeAndNode& p, const CPipeAndNode& p1);
	bool FindFirstNAYZ(int nNAYZ);
	bool FindNextNAYZ(int nNAYZ);
	bool FindFirstKOYZ(int nKOYZ);
	bool FindNextKOYZ(int nKOYZ);
};

