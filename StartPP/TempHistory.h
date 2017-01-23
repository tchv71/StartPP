#pragma once
#include <vector>

struct STempHistRec
{
	float Temp; // Температурный коэффициент 
	int Sequency; // Частота цикла за период
	int Period; // Период цикла 0-день, 1-неделя, 2-месяц, 3-год 
};

class CTempHistory
{
public:
	CTempHistory(void);
	~CTempHistory(void);
	float Tmax; // Наибольшая температура в трубопроводе
	std::vector<STempHistRec> m_vecRec;
	void Add(float Temp, int Sequency, int Period);

	void WriteIni(CStdioFile& file);
};

