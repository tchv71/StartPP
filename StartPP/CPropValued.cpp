//
// Created by Дмитрий Цветков on 18.02.17.
//

#include "wxcrafter.h"
#include <wx/xrc/xmlres.h>
#include "PropertiesWnd.h"
#include "stdafx.h"
#include "CPropValued.h"
#include "Strings.h"
#include "PipeArray.h"
#include "TroinicsSet.h"
#include "StartPPDoc.h"

extern void AfxLoadString(wxString id, TCHAR* str);

template <typename T1, typename T2> size_t OffsetOf(T1* val, T2* base)
{
	return reinterpret_cast<BYTE*>(val) - reinterpret_cast<BYTE*>(base);
}

template <typename T1, typename T2> CPipeAndNode* GetPnN(float* ptr, T1* val, T2* base)
{
	return reinterpret_cast<CPipeAndNode*>(reinterpret_cast<BYTE*>(ptr) - OffsetOf(val, base));
}

void CPropValued::OnValueChanged(DWORD_PTR dwData, wxVariant &val, wxVariant &valNew, bool bButtons)
{
	switch(dwData)
	{
		case E_PIPE_TYPE:
		{
			CString strVal = valNew.GetString();
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				TCHAR strPodzem[256];
				AfxLoadString(IDS_PODZEM, strPodzem);
				BOOL bPodzem1 = strVal == strPodzem;
				set.m_strPath = DATA_PATH;
				set.m_strTable = _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and
				// %d=PODZ  order by
				// DIAM, PODZ"),pPnN->m_DIAM, int(bPodzem1));
				set.Open();
				for(; !set.IsEOF(); set.MoveNext())
					if(set.m_PODZ == bPodzem1 && fabs(set.m_DIAM - pPnN->m_DIAM) < 0.1)
						break;
				if(bPodzem1)
				{
					if(pPnN->m_NAGV != -1)
					{
						pPnN->m_NAGV = -1.0f;
						pPnN->m_NAGY = 0.0f;
						pPnN->m_NAGZ = 1010.1f;
						pPnN->m_NAGX = set.m_DIIZ;
						pPnN->m_SHTR = set.m_SHTR;
						pPnN->m_VIZA = pPnN->m_VIZA2 = 0;
						pPnN->m_OS_TR1 = pPnN->m_OS_TR2 = set.m_DIIZ / 2000;
					}
				}
				else
				{
					pPnN->m_NAGV = pPnN->m_NAGX = pPnN->m_NAGY = pPnN->m_NAGZ = 0.0f;
				}
				set.Close();
			}
			RecalcXYZ();
			break;
		}

		case E_OSIX: // Проекция участка на ось X
		case E_OSIY: // Проекция участка на ось Y
		case E_OSIZ: // Проекция участка на ось Z
			ToFloat(valNew, dwData);
			RecalcXYZ();
			break;
		case E_LEN_PLAN: // Длина участка в плане
		case E_LEN_TOTAL: // Длина участка
		case E_ANG_PLAN_ABS: // Угол в плане абсолютный
		case E_UKLON: // Уклон
		{
			ToFloat(valNew);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				switch (dwData)
				{
					case E_LEN_PLAN:
						pPnN->setLPlan(valNew.GetDouble());
						break;
					case E_LEN_TOTAL: // Длина участка
						pPnN->setLGen(valNew.GetDouble());
						break;
					case E_ANG_PLAN_ABS: // Угол в плане абсолютный
						pPnN->setAPlan(valNew.GetDouble());
						break;
					case E_UKLON: // Уклон
						pPnN->setUklon(valNew.GetDouble());
						break;
				}
			}
			RecalcXYZ();
		}
		break;

		case E_ANG_PLAN_REL: // Угол в плане относительно предыдущего участка
		{
			float ang;
			ToFloat(valNew, ang);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				CAngles a1;
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.GetRelAngle(m_pDoc, pPnN);
				m_pDoc->RotateThisAndOthers(pPnN, DegToRad(ang - a1.a_plan_rel));
			}
			RecalcXYZ();
		}
		break;

		case E_ANG_PROF: // Угол в профиле (азимутальный)
		{
			float ang;
			ToFloat(valNew, ang);
			//pProp->SetValue(_variant_t(S_Round(ang, 1)));
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				if(bButtons)
					pPnN->setAProfFix(ang);
				else
					pPnN->setAProf(ang);
			}
			RecalcXYZ();
		}
		break;
		case E_DIAM:
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				CPipesSet pset;
				ToFloat(valNew, pPnN->m_DIAM);
				BOOL b_podzem = fabs(pPnN->m_NAGV + 1) < 1e-6;
				pset.m_strPath = DATA_PATH;
				pset.m_strTable =
				    _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by
				// DIAM, PODZ"),pPnN->m_DIAM, int(b_podzem));
				pset.Open();
				// while (!set.IsEOF())
				for(; !pset.IsEOF(); pset.MoveNext())
					if(pset.m_PODZ == b_podzem && fabs(pset.m_DIAM - pPnN->m_DIAM) < 0.1)
						break;
				{
					pPnN->m_NAMA = pset.m_NAMA;
					pPnN->m_NTOS = pset.m_NTOS;
					pPnN->m_RTOS = pset.m_NTOS - pset.m_RTOS;
					pPnN->m_VETR = pset.m_VETR;
					pPnN->m_VEIZ = pset.m_VEIZ;
					pPnN->m_VEPR = pset.m_VEPR;
					if(b_podzem)
					{
						pPnN->m_NAGX = pset.m_DIIZ;
						pPnN->m_SHTR = pset.m_SHTR;
					}
					pPnN->m_RAOT = pset.m_RAOT;
					pPnN->m_MARI = pset.m_MARI;
					pPnN->m_NOTO = pset.m_NOTO;
					pPnN->m_RATO = pset.m_NOTO - pset.m_RATO;
					if(pPnN->m_MNEA == STR_KO)
					{
						m_pPnN->m_RAOT = pset.m_SEFF;
						m_pPnN->m_KOTR = pset.m_KPOD;
					}
				}
				pset.Close();
			}
			RecalcXYZ();
			break;
		case E_MATERIAL:
			ToStr(valNew, dwData);
			break;
		case E_OS_TR_BEG:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_OS_TR1, m_pPnN);
				pPnN->m_OS_TR1 = valNew.GetDouble();
				pPnN->m_VIZA = pPnN->m_OS_TR1 - pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(auto p = &(arr.InFirst(int(pPnN->m_NAYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR2 = pPnN->m_OS_TR1;
						p->m_pPnN->m_VIZA2 = p->m_pPnN->m_OS_TR2 - p->m_pPnN->m_NAGX / 2000;
					}
				for(auto p = &arr.OutFirst(int(pPnN->m_NAYZ), cnt); arr.HasOut(cnt); p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR1 = pPnN->m_OS_TR1;
						p->m_pPnN->m_VIZA = p->m_pPnN->m_OS_TR1 - p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_OS_TR_END:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_OS_TR2, m_pPnN);
				pPnN->m_OS_TR2 = valNew.GetDouble();
				pPnN->m_VIZA2 = pPnN->m_OS_TR2 - pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(Pipe * p = &(arr.InFirst(int(pPnN->m_KOYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR2 = pPnN->m_OS_TR2;
						p->m_pPnN->m_VIZA2 = p->m_pPnN->m_OS_TR2 - p->m_pPnN->m_NAGX / 2000;
					}
				for(Pipe * p = &(arr.OutFirst(int(pPnN->m_KOYZ), cnt)); arr.HasOut(cnt);
				        p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR1 = pPnN->m_OS_TR2;
						p->m_pPnN->m_VIZA = p->m_pPnN->m_OS_TR1 - p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_VIZA_BEG:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_VIZA, m_pPnN);
				pPnN->m_VIZA = valNew.GetDouble();
				pPnN->m_OS_TR1 = pPnN->m_VIZA + pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(Pipe * p = &(arr.InFirst(int(pPnN->m_NAYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA2 = pPnN->m_VIZA;
						p->m_pPnN->m_OS_TR2 = p->m_pPnN->m_VIZA2 + p->m_pPnN->m_NAGX / 2000;
					}
				for(Pipe * p = &(arr.OutFirst(int(pPnN->m_NAYZ), cnt)); arr.HasOut(cnt);
				        p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA = pPnN->m_VIZA;
						p->m_pPnN->m_OS_TR1 = p->m_pPnN->m_VIZA + p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_VIZA_END:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_VIZA2, m_pPnN);
				pPnN->m_VIZA2 = valNew.GetDouble();
				pPnN->m_OS_TR2 = pPnN->m_VIZA2 + pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(Pipe * p = &(arr.InFirst(int(pPnN->m_KOYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA2 = pPnN->m_VIZA2;
						p->m_pPnN->m_OS_TR2 = p->m_pPnN->m_VIZA2 + p->m_pPnN->m_NAGX / 2000;
					}
				for(Pipe * p = &(arr.OutFirst(int(pPnN->m_KOYZ), cnt)); arr.HasOut(cnt);
				        p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA = pPnN->m_VIZA2;
						p->m_pPnN->m_OS_TR1 = p->m_pPnN->m_VIZA + p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_GRTYPE_UP:
		case E_GRTYPE_OSN:
		case E_GRTYPE_SIDE:
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				int n = int((*(it->second)) * 10 + 0.5f);
				int nSide = n % 10;
				n /= 100;
				int nUp = n % 10;
				n /= 100;
				int nDown = n;
				switch(dwData)
				{
				case E_GRTYPE_UP:
					nUp = valNew.GetLong();
					break;
				case E_GRTYPE_OSN:
					nDown = valNew.GetLong();
					break;
				case E_GRTYPE_SIDE:
					nSide = valNew.GetLong();
					break;
				default:
					wxASSERT_MSG(false,"Unknown type");
				}
				*it->second = Round(float(nSide) / 10 + nUp * 10 + nDown * 1000, 1);
			}
			break;
		case E_IZD_TYPE:
		{
			CString strVal = valNew.GetString();
			seta.m_strPath = DATA_PATH;
			seta.m_strTable =
			    _T("Armat.dbf"); // Format(_T("[Armat] WHERE DIAM = %g order by DIAM"), m_pPnN->m_DIAM);
			if(!seta.Open())
				AfxMessageBox(_T("Can't open Armat.dbf"), wxOK | wxICON_EXCLAMATION);
			for(; !seta.IsEOF(); seta.MoveNext())
				if(fabs(seta.m_DIAM - m_pPnN->m_DIAM) < 0.1)
					break;
			TCHAR strNone[256];
			AfxLoadString(IDS_NONE, strNone);
			if(strVal == strNone)
			{
				m_pPnN->m_MNEA = _T("");
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_ARMAT))
			{
				m_pPnN->m_MNEA = STR_AR;
				m_pPnN->m_RAOT = seta.m_RAOT1;
				m_pPnN->m_VESA = seta.m_VESA1;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_OTVIZ))
			{
				m_pPnN->m_MNEA = STR_OI;
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_OTVSV))
			{
				m_pPnN->m_MNEA = STR_OS;
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_OTVFL))
			{
				m_pPnN->m_MNEA = STR_OF;
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_KO))
			{
				set.m_strPath = DATA_PATH;
				set.m_strTable =
				    _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g order by
				// DIAM"), m_pPnN->m_DIAM);
				set.Open();
				for(; !set.IsEOF(); set.MoveNext())
					if(fabs(set.m_DIAM - m_pPnN->m_DIAM) < 0.1)
						break;
				m_pPnN->m_MNEA = STR_KO;
				m_pPnN->m_RAOT = set.m_SEFF;
				m_pPnN->m_KOTR = set.m_KPOD;
				m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = _T("");
				set.Close();
			}
			else if(strVal == LoadStr(IDS_KU))
			{
				m_pPnN->m_MNEA = STR_KU;
				m_pPnN->m_KOTR = m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_TR))
			{
				m_pPnN->m_MNEA = STR_TR;
				m_pPnN->m_KOTR = m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = _T("");
			}

			else if(strVal == LoadStr(IDS_VREZKA))
			{
				m_pPnN->m_VREZKA = STR_SV;
				m_pPnN->m_MNEA = _T("");
			}
			seta.Close();
			CDataExchange dx(nullptr, FALSE);
			DoDataExchange(&dx, m_pPnN, m_pDoc);
		}
		break;

		case E_OPOR_TYPE:
		{
			CString strVal = valNew.GetString();
			if (strVal == LoadStr(IDS_NONE))
				ToStr(_variant_t(_T("")), m_pPnN->m_MNEO);
			else if(strVal == LoadStr(IDS_MERT))
			{
				ToStr(_variant_t(STR_MO), m_pPnN->m_MNEO);
			}
			else if(strVal == LoadStr(IDS_SK))
			{
				ToStr(_variant_t(STR_SK), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.3f), m_pPnN->m_KOTR);
			}
			else if(strVal == LoadStr(IDS_NAPR))
			{
				ToStr(_variant_t(STR_NP), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.3f), m_pPnN->m_KOTR);
			}
			else if(strVal == LoadStr(IDS_UPR))
			{
				ToStr(_variant_t(STR_PR), m_pPnN->m_MNEO);
				ToFloat(_variant_t(1.0f), m_pPnN->m_SEOP);
				ToFloat(_variant_t(35.0f), m_pPnN->m_NOTO);
				ToFloat(_variant_t(1.0f), m_pPnN->m_RATO);
				ToFloat(_variant_t(0.0f), m_pPnN->m_VEYS);
				ToFloat(_variant_t(0.0f), m_pPnN->m_KOTR);
			}
			else if(strVal == LoadStr(IDS_ZHESTK_PODV))
			{
				ToStr(_variant_t(STR_PD), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.0f), m_pPnN->m_DIGI);
			}
			OnLBChanged();
			break;
		}
		case E_DEF_TYPE:
		{
			CString strVal = valNew.GetString();
			if(strVal == LoadStr(IDS_NONE))
				m_pPnN->m_TIDE = _T("");
			else if(strVal == LoadStr(IDS_RAST))
			{
				m_pPnN->m_TIDE = STR_RS;
				// m_pPnN->m_RASG=0.0f;
			}
			else if(strVal == LoadStr(IDS_SG))
			{
				m_pPnN->m_TIDE = STR_SG;
				// m_pPnN->m_RASG=0.0f;
			}
			OnLBChanged();
		}
		break;
		case E_MATOTV:
		case E_TR_MAT:
		case E_MATOTV_SV:
		case E_MATOTV_OF:
			ToStr(valNew, dwData);
			break;
		case E_TR_DIAM_OTV:
		{
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				ToFloat(valNew, pPnN->m_NONE);
				CTroinicsSet set1;
				set1.m_strPath = DATA_PATH;
				set1.m_strTable = _T("Troinics.dbf"); // set1.m_strTable.Format(_T("[Troinics] WHERE DIAM =
				// %g and DIAMSH =
				// %g"), pPnN->m_DIAM, pPnN->m_NONE);
				if(!set1.Open())
					AfxMessageBox(_T("Can't open Troinics.dbf"), wxOK | wxICON_EXCLAMATION);
				for(; !set1.IsEOF(); set1.MoveNext())
					if(fabs(set1.m_DIAM - m_pPnN->m_DIAM) < 0.1 &&
					   fabs(set1.m_DIAMSH - m_pPnN->m_NONE) < 0.1)
						break;

				pPnN->m_NOTO = set1.m_NTSTM;
				pPnN->m_RATO = set1.m_NTSTM - set1.m_RTSTM;
				pPnN->m_VEYS = set1.m_NTSTSH;
				pPnN->m_DIGI = set1.m_NTSTSH - set1.m_RTSTSH;
				pPnN->m_SILX = float(set1.m_VIS_SHTU);
				pPnN->m_RASG = set1.m_WIDTHNAK;
				pPnN->m_DEFZ = set1.m_THINKNAK;
				pPnN->m_VESA = set1.m_VES;
				pPnN->m_KORPUS = float(set1.m_KORPUS);
				pPnN->m_MARI = pPnN->m_NAMA;
				set1.Close();
			}
			RecalcXYZ();
			break;
		}
		default:
			ToFloat(valNew, dwData);
			break;
	}
	m_pDoc->PnNIsUpdated();
}

void CPropValued::ToFloat(COleVariant& val)
{
	double d;
	CString str = val.GetString();
	str.ToCDouble(&d);
	val = d;
}

void CPropValued::ToStr(const COleVariant& val, CStringA& x)
{
	x = val.GetString();
}

void CPropValued::ToFloat(const COleVariant& val, DWORD_PTR dwData)
{
	float x;
	if(val.GetType() == _T("double"))
		x = val.GetDouble();
	else if(val.GetType() == _T("long"))
		x = float(val.GetLong());
	else
	{
		CString strVal = val.GetString();
		strVal.Replace(_T("."), _T(","));
		double d;
		strVal.ToCDouble(&d);
		x = d;
	}
	for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		*it->second = x;
}

void CPropValued::ToStr(const COleVariant& val, DWORD_PTR dwData)
{
	for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		*reinterpret_cast<CStringA*>(it->second) = val.GetString();
}

void CPropValued::RecalcXYZ()
{

}

void CPropValued::OnLBChanged()
{

}

void CPropValued::ToFloat(const COleVariant& val, float& x)
{
	if(val.GetType() == _T("double"))
	{
		x = val.GetDouble();
		return;
	}
	if(val.GetType() == _T("long"))
	{
		x = float(val.GetLong());
		return;
	}

	CString strVal = val.GetString();
	strVal.Replace(_T("."), _T(","));
	double d;
	strVal.ToCDouble(&d);
	x = d;
}

CPropValued::CPropValued() : bUpdatedByParent(false), m_pDoc(nullptr), m_pPnN(nullptr)
{}

void CPropValued::DoDataExchange(CDataExchange *pExchange, CPipeAndNode *pNode, CStartPPDoc *pDoc)
{

}
