#pragma once
#include <vector>
#include "PipeAndNode.h"

class CVecPnN
{
public:
	CVecPnN() : m_nIdx(0)
	{
	};

	size_t m_nIdx;
	int GetMaxNodeNum();
	void RenumPipes(int FirstNum);

	CPipeAndNode& CurPipe()
	{
		return m_vecPnN[m_nIdx];
	}

	std::vector<CPipeAndNode> m_vecPnN;
	void WriteIni(CStdioFile& file);
	void Serialize(CArchive& ar);
};

