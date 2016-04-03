#include "stdafx.h"
#include "VecPnN.h"
#include "PipesSet.h"
#include <math.h>
#include <map>


void CVecPnN::WriteIni(CStdioFile& file)
{
	CString str;
	file.WriteString(_T("[Участок]\n"));
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (int(p.m_NAYZ) == 0)
			continue;
		str.Format(_T("№узла_начало=%g\n"), p.m_NAYZ);
		file.WriteString(str);
		str.Format(_T("№узла_конец=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("X=%g\nY=%g\nZ=%g\n"), p.m_OSIX, p.m_OSIY, p.m_OSIZ);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Диаметр=%g\nМатериал="), p.m_DIAM);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str = p.m_NAMA;
		file.WriteString(str + _T("\n"));
		str.Format(_T("Толщина_ном=%g\nПрибавка=%g\n"), p.m_NTOS, p.m_RTOS);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Прибавка_кор=%g\nР=%g\n"), 0.0f, p.m_RADA);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Р_исп=%g\nТ=%g\n"), p.m_DABI, p.m_RATE);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Вес_трубы=%g\nВес_изоляции=%g\nВес_продукта=%g\n"), p.m_VETR, p.m_VEIZ, p.m_VEPR);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("К_изгиб=%g\nК_давление=%g\n"), p.m_KOPR, p.m_KOPE);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		bool bPodzem = fabs(p.m_NAGV + 1) < 1e-6;
		if (!bPodzem)
		{
			str.Format(_T("Дополнит_весов_нагр=%g\nМ_доп_X=%g\nМ_доп_Y=%g\nМ_доп_Z=%g\n"),
			                                                                             p.m_NAGV, p.m_NAGX, p.m_NAGY, p.m_NAGZ);
			str.Replace(_T(","),_T("."));
			file.WriteString(str);
		}
		else
		{
			str.Format(_T("Диам_изол=%g\nГлубина_заложения=%g\nГлубина_заложения2=%g\n"), p.m_NAGX, p.m_OS_TR1, p.m_OS_TR2);
			str.Replace(_T(","),_T("."));
			file.WriteString(str);
			CPipesSet set;
			set.m_strPath = _T(".");
			set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by DIAM, PODZ"), p.m_DIAM, 1);
			set.Open();

			str.Format(_T("Высота_воды=%g\nТолщина_кожуха=%g\nШирина_траншеи=%g\n"), 0.0f, set.m_IZTO, p.m_SHTR);
			set.Close();
			str.Replace(_T(","),_T("."));
			file.WriteString(str);
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
			str.Format(_T("Грунт_основание=0%d\nГрунт_верх=0%d\nГрунт_бок=0%d\n"), nDown, nUp, nSide);
			file.WriteString(str);
			str.Format(_T("Тип_изоляции=%d\nNm=%g\n"), 3, 0.67f);
			str.Replace(_T(","),_T("."));
			file.WriteString(str);
			str.Format(_T("Тип_подушек=%d\nПросадка=%g\n"), nPodush, 0.0f);
			str.Replace(_T(","),_T("."));
			file.WriteString(str);
		}
	}
	bool bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		int nType = 0;
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA == "ои")
			nType = 1;
		if (p.m_MNEA == "ос")
			nType = 3;
		if (p.m_MNEA == "оф")
			nType = 2;
		if (nType == 0)
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Отвод]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Тип=%d\nРадиус=%g\n"), nType, p.m_RAOT * 1000);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Вес=%g\nМатериал="), p.m_VESA);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str = p.m_MARI;
		file.WriteString(str + _T("\n"));
		str.Format(_T("Толщина_ном=%g\nПрибавка=%g\nПрибавка_кор=%g\n"), p.m_NOTO, p.m_RATO, 0.0f);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("К_овал=%g\nФланцы=%d\n"), 0.0f, 0);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("К_давление=%g\nСкосы=%d\n"), 1.0f, 3);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != "тр")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Тройник_сварной]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Вес=%g\n"), p.m_VESA);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		CString str1;
		str1 = p.m_MARI;
		str.Format(_T("Материал=%s\n"), LPCTSTR(str1));
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Толщина_маг_ном=%g\nПрибавка_маг=%g\n"), p.m_NOTO, p.m_RATO);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Толщина_штуц_ном=%g\nПрибавка_штуц=%g\n"), p.m_VEYS, p.m_DIGI);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Высота_штуц=%g\n"), p.m_SILX);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Толщина_накл=%g\nШирина_накл=%g\n"), p.m_DEFZ, p.m_RASG);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != "ap")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Арматура]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Длина=%g\nВес=%g\n"), p.m_RAOT, p.m_VESA);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_VREZKA != "св")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Врезка]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Толщина_накл=%g\nШирина_накл=%g\n"), p.m_DEFZ, p.m_RASG);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != "ку")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Компенсатор_угловой]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Податливость=%g\n"), p.m_KOTR);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEA != "ко")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Компенсатор_осевой]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		bool bPodzem = fabs(p.m_NAGV + 1) < 1e-6;
		//Тип компенсатора: 0 - Стартовый, 1 - Сильфонный, 2 - зарезервировано, 3 - Линзовый.
		str.Format(_T("Тип=%d\n"), bPodzem ? 0 : 1);
		file.WriteString(str);
		str.Format(_T("Площадь_эффект=%g\nПодатливость=%g\nОсевой_ход=%g\n"), p.m_RAOT, p.m_KOTR, p.m_DIGI);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != "мо")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Мертвая_опора]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != "ск")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Скользящая_опора]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("К_трения=%g\n"), p.m_KOTR);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != "нп")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Направляющая_опора2]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("К_трения=%g\n"), p.m_KOTR);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != "пр")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Пружинная_опора]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Число_тяг=%g\nИзменение_нагр=%g\n"), p.m_SEOP, p.m_NOTO);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("К_запаса_нагр=%g\nПоддержив_усилие=%g\nПодатливость=%g\n"),
		                                                                         p.m_RATO, p.m_VEYS, p.m_KOTR);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_MNEO != "пд")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Жесткая_подвеска]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Длина_тяги=%g\n"), p.m_DIGI);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	bFirst = true;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		if (p.m_TIDE != "рс" && p.m_TIDE != "сж")
			continue;
		if (bFirst)
		{
			file.WriteString(_T("[Деформации]\n"));
			bFirst = false;
		}
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		if (p.m_TIDE == "рс")
			str.Format(_T("Растяжение=%g\n"), p.m_RASG);
		else
			str.Format(_T("Сжатие=%g\n"), p.m_RASG);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
	file.WriteString(_T("[Узел]\n"));
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CPipeAndNode& p = m_vecPnN[i];
		str.Format(_T("№узла=%g\n"), p.m_KOYZ);
		file.WriteString(str);
		str.Format(_T("Лин=%d\n"), p.m_PELI == "л" ? 1 : 0);
		file.WriteString(str);
		str.Format(_T("Угл=%d\n"), p.m_PEYG == "у" ? 1 : 0);
		file.WriteString(str);
		str.Format(_T("Сила_X=%g\nСила_Y=%g\nСила_Z=%g\n"), p.m_MNEA == "тр" ? 0.0f : p.m_SILX, p.m_SILY, p.m_SILZ);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Момент_X=%g\nМомент_Y=%g\nМомент_Z=%g\n"), p.m_MOMX, p.m_MOMY, p.m_MOMZ);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
		str.Format(_T("Сила_весовая=%g\nМомент_вес_X=%g\nМомент_вес_Y=%g\n"),
		                                                                    p.m_VESZ, p.m_VESX, p.m_VESY);
		str.Replace(_T(","),_T("."));
		file.WriteString(str);
	}
}

void CVecPnN::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << unsigned int(m_vecPnN.size());
		ar << unsigned int(m_nIdx);
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

void CVecPnN::RenumPipes(int FirstNum, int MaxNodeNum)
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

