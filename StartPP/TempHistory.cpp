#include "stdafx.h"
#include "TempHistory.h"

extern CString _R(CString s);

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
	file.WriteString(_R(CString::Format(_T("Т_макс=%g\n"), Tmax)));
	for (unsigned i = 0; i < m_vecRec.size(); i++)
	{
		file.WriteString(_R(CString::Format(_T("№цикла=%d\n"), i + 1)));
		file.WriteString(_R(CString::Format(_T("Т_коэф=%g\n"), m_vecRec[i].Temp)));
		file.WriteString(CString::Format(_T("Частота=%d\n"), m_vecRec[i].Sequency));
		file.WriteString(CString::Format(_T("Период=%d\n"), m_vecRec[i].Period));
	}
}

