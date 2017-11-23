#include "stdafx.h"
#include "VecPnN.h"
#include "PipesSet.h"
#include <map>
#include "Strings.h"
#include "Archive.h"

CString _R(CString s)
{
	s.Replace(_T(","), _T("."));
	return s;
}

void CVecPnN::WriteIni(CStdioFile& file)
{
	file.WriteString(_T("[Участок]\n"));
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (int(p.m_NAYZ) == 0)
			continue;
		file.WriteString(CString::Format(_T("№узла_начало=%g\n"), p.m_NAYZ));
		file.WriteString(CString::Format(_T("№узла_конец=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("X=%g\nY=%g\nZ=%g\n"), p.m_OSIX, p.m_OSIY, p.m_OSIZ)));
		file.WriteString(_R(CString::Format(_T("Диаметр=%g\nМатериал="), p.m_DIAM)));
		file.WriteString(p.m_NAMA + _T("\n"));
		file.WriteString(_R(CString::Format(_T("Толщина_ном=%g\nПрибавка=%g\n"), p.m_NTOS, p.m_RTOS)));
		file.WriteString(_R(CString::Format(_T("Прибавка_кор=%g\nР=%g\n"), 0.0f, p.m_RADA)));
		file.WriteString(_R(CString::Format(_T("Р_исп=%g\nТ=%g\n"), p.m_DABI, p.m_RATE)));
		file.WriteString(_R(CString::Format(_T("Вес_трубы=%g\nВес_изоляции=%g\nВес_продукта=%g\n"), p.m_VETR, p.m_VEIZ, p.m_VEPR)));
		file.WriteString(_R(CString::Format(_T("К_изгиб=%g\nК_давление=%g\n"), p.m_KOPR, p.m_KOPE)));
		bool bPodzem = p.isPodzem();
		if (!bPodzem)
		{
			file.WriteString(_R(CString::Format(_T("Дополнит_весов_нагр=%g\nМ_доп_X=%g\nМ_доп_Y=%g\nМ_доп_Z=%g\n"),
                              p.m_NAGV, p.m_NAGX, p.m_NAGY, p.m_NAGZ)));
		}
		else
		{
			file.WriteString(_R(CString::Format(_T("Диам_изол=%g\nГлубина_заложения=%g\nГлубина_заложения2=%g\n"), p.m_NAGX, p.m_OS_TR1, p.m_OS_TR2)));
			CPipesSet set;
			set.m_strPath = DATA_PATH;
			set.m_strTable = _T("Pipes.dbf");
			//set.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by DIAM, PODZ"), p.m_DIAM, 1);
			set.Open();
			for (; !set.IsEOF(); set.MoveNext())
				if (set.m_PODZ == 1 && fabs(set.m_DIAM - p.m_DIAM) < 0.1)
					break;

			file.WriteString(_R(CString::Format(_T("Высота_воды=%g\nТолщина_кожуха=%g\nШирина_траншеи=%g\n"), 0.0f, set.m_IZTO, p.m_SHTR)));
			set.Close();
			int n = int(p.m_NAGZ * 10 + 0.5f);
			int nSide = n % 10;
			n /= 100;
			int nUp = n % 10;
			n /= 100;
			int nDown = n;
			int nPodush = 0;
			if (nSide == 6 || nSide == 7)
			{
				nSide = nUp;
				nPodush = 1;
			}
			file.WriteString(CString::Format(_T("Грунт_основание=0%d\nГрунт_верх=0%d\nГрунт_бок=0%d\n"), nDown, nUp, nSide));
			file.WriteString(_R(CString::Format(_T("Тип_изоляции=%d\nNm=%g\n"), 3, 0.67f)));
			file.WriteString(_R(CString::Format(_T("Тип_подушек=%d\nПросадка=%g\n"), nPodush, 0.0f)));
		}
	}
	bool bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		int nType = 0;
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA == STR_OI)
			nType = 1;
		if (p.m_MNEA == STR_OS)
			nType = 3;
		if (p.m_MNEA == STR_OF)
			nType = 2;
		if (nType == 0)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Отвод]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Тип=%d\nРадиус=%g\n"), nType, p.m_RAOT * 1000)));
		file.WriteString(_R(CString::Format(_T("Вес=%g\nМатериал="), p.m_VESA)));
		file.WriteString(p.m_MARI + _T("\n"));
		file.WriteString(_R(CString::Format(_T("Толщина_ном=%g\nПрибавка=%g\nПрибавка_кор=%g\n"), p.m_NOTO, p.m_RATO, 0.0f)));
		file.WriteString(_R(CString::Format(_T("К_овал=%g\nФланцы=%d\n"), 0.0f, 0)));
		file.WriteString(_R(CString::Format(_T("К_давление=%g\nСкосы=%d\n"), 1.0f, 3)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != STR_TR)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Тройник_сварной]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Вес=%g\n"), p.m_VESA)));
		file.WriteString(_R(CString::Format(_T("Материал=%s\n"), LPCTSTR(p.m_MARI.c_str()))));
		file.WriteString(_R(CString::Format(_T("Толщина_маг_ном=%g\nПрибавка_маг=%g\n"), p.m_NOTO, p.m_RATO)));
		file.WriteString(_R(CString::Format(_T("Толщина_штуц_ном=%g\nПрибавка_штуц=%g\n"), p.m_VEYS, p.m_DIGI)));
		file.WriteString(_R(CString::Format(_T("Высота_штуц=%g\n"), p.m_SILX)));
		file.WriteString(_R(CString::Format(_T("Толщина_накл=%g\nШирина_накл=%g\n"), p.m_DEFZ, p.m_RASG)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != STR_AR)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Арматура]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Длина=%g\nВес=%g\n"), p.m_RAOT, p.m_VESA)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_VREZKA != STR_SV)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Врезка]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Толщина_накл=%g\nШирина_накл=%g\n"), p.m_DEFZ, p.m_RASG)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != STR_KU)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Компенсатор_угловой]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Податливость=%g\n"), p.m_KOTR)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != STR_KO)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Компенсатор_осевой]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		bool bPodzem = p.isPodzem();
		file.WriteString(CString::Format(_T("Тип=%d\n"), bPodzem ? 0 : 1));
		file.WriteString(_R(CString::Format(_T("Площадь_эффект=%g\nПодатливость=%g\nОсевой_ход=%g\n"), p.m_RAOT, p.m_KOTR, p.m_DIGI)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != STR_MO)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Мертвая_опора]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != STR_SK)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Скользящая_опора]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("К_трения=%g\n"), p.m_KOTR)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != STR_NP)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Направляющая_опора2]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("К_трения=%g\n"), p.m_KOTR)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != STR_PR)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Пружинная_опора]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Число_тяг=%g\nИзменение_нагр=%g\n"), p.m_SEOP, p.m_NOTO)));
		file.WriteString(_R(CString::Format(_T("К_запаса_нагр=%g\nПоддержив_усилие=%g\nПодатливость=%g\n"),
		                                                                                                  p.m_RATO, p.m_VEYS, p.m_KOTR)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != STR_PD)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Жесткая_подвеска]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R(CString::Format(_T("Длина_тяги=%g\n"), p.m_DIGI)));
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_TIDE != STR_RS && p.m_TIDE != STR_SG)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Деформации]\n"));
			bFirst = false;
		}
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(_R( CString::Format(p.m_TIDE == "рс" ? _T("Растяжение=%g\n") : _T("Сжатие=%g\n"), p.m_RASG)));
	}
	file.WriteString(_T("[Узел]\n"));
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		file.WriteString(CString::Format(_T("№узла=%g\n"), p.m_KOYZ));
		file.WriteString(CString::Format(_T("Лин=%d\n"), p.m_PELI == "л" ? 1 : 0));
		file.WriteString(CString::Format(_T("Угл=%d\n"), p.m_PEYG == "у" ? 1 : 0));
		file.WriteString(_R(CString::Format(_T("Сила_X=%g\nСила_Y=%g\nСила_Z=%g\n"), p.m_MNEA == "тр" ? 0.0f : p.m_SILX, p.m_SILY, p.m_SILZ)));
		file.WriteString(_R(CString::Format(_T("Момент_X=%g\nМомент_Y=%g\nМомент_Z=%g\n"), p.m_MOMX, p.m_MOMY, p.m_MOMZ)));
		file.WriteString(_R(CString::Format(_T("Сила_весовая=%g\nМомент_вес_X=%g\nМомент_вес_Y=%g\n"), p.m_VESZ, p.m_VESX, p.m_VESY)));
	}
}

void CVecPnN::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << unsigned(m_vecPnN.size());
		ar << unsigned(m_nIdx);
		for (auto it = m_vecPnN.begin(); it != m_vecPnN.end(); ++it)
			it->Serialize(ar);
	}
	else
	{
		std::vector<CPipeAndNode>::size_type sz;
		unsigned int szi;
		ar >> szi;
		sz = szi;
		ar >> szi;
		m_nIdx = szi;
		for (unsigned i = 0; i < sz; i++)
		{
			CPipeAndNode pn;
			pn.Serialize(ar);
			m_vecPnN.push_back(pn);
		}
	}
}

int CVecPnN::GetMaxNodeNum()
{
	int MaxNodeNum = 0;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		if (m_vecPnN[i].m_NAYZ > MaxNodeNum)
			MaxNodeNum = int(m_vecPnN[i].m_NAYZ);
		if (m_vecPnN[i].m_KOYZ > MaxNodeNum)
			MaxNodeNum = int(m_vecPnN[i].m_KOYZ);
	}
	return MaxNodeNum;
}

void CVecPnN::RenumPipes(int FirstNum)
{
	std::map<int, int> vecRenum;
	//vecRenum.resize(MaxNodeNum+1);
	//for (unsigned i=0;i<vecRenum.size();i++) vecRenum[i]=0;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		int NAYZ = int(m_vecPnN[i].m_NAYZ);
		if (NAYZ != 0)
		{
			if (vecRenum[NAYZ] == 0) vecRenum[NAYZ] = FirstNum++;
			m_vecPnN[i].m_NAYZ = float(vecRenum[NAYZ]);
		}
		int KOYZ = int(m_vecPnN[i].m_KOYZ);
		if (KOYZ != 0)
		{
			if (vecRenum[KOYZ] == 0) vecRenum[KOYZ] = FirstNum++;
			m_vecPnN[i].m_KOYZ = float(vecRenum[KOYZ]);
		}
	}
}

