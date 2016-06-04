#include "stdafx.h"
#include "TempHistory.h"


CTempHistory::CTempHistory(void) : Tmax(100.0f)
{
	Add(1.0f, 1, 3);
	Add(0.5f, 2, 2);
	Add(0.25f, 4, 1);
	Add(0.125f, 8, 0);
}


CTempHistory::~CTempHistory(void)
{
}

void CTempHistory::Add(float Temp, int Sequency, int Period)
{
	STempHistRec r;
	r.Temp = Temp;
	r.Sequency = Sequency;
	r.Period = Period;
	m_vecRec.push_back(r);
}


void CTempHistory::WriteIni(CStdioFile& file)
{
	file.WriteString(_T("[Температурная_история]\n"));
	CString str;
	str.Format(_T("%g"), Tmax);
	file.WriteString(_T("Т_макс="));
	str.Replace(_T(","),_T("."));
	file.WriteString(str + _T("\n"));
	for (unsigned i = 0; i < m_vecRec.size(); i++)
	{
		str.Format(_T("%d"), i + 1);
		file.WriteString(_T("№цикла="));
		str.Replace(_T(","),_T("."));
		file.WriteString(str + _T("\n"));
		str.Format(_T("%g"), m_vecRec[i].Temp);
		str.Replace(_T(","),_T("."));
		file.WriteString(_T("Т_коэф="));
		file.WriteString(str + _T("\n"));
		str.Format(_T("%d"), m_vecRec[i].Sequency);
		file.WriteString(_T("Частота="));
		file.WriteString(str + _T("\n"));
		str.Format(_T("%d"), m_vecRec[i].Period);
		file.WriteString(_T("Период="));
		file.WriteString(str + _T("\n"));
	}
}

