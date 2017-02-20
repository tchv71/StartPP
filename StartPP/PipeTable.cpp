#include "stdafx.h"
#include "PipeTable.h"
#include "main.h"
#include "MainFrame.h"
#include "Material.h"
#include <PipesSet.h>
#include "Strings.h"

PipeTable::PipeTable()
{
}

PipeTable::~PipeTable()
{
}




wxString PipeTable::GetValue(int row, int col)
{
	CStartPPDoc *pDoc;
	CPipeAndNode *pPnN = getPipeAndNode(row, pDoc);
	if(!pPnN)
		return "";
	CPipeAndNode &p = *pPnN;
	switch (col)
	{
		case 10: return p.m_NAMA;
	}
	return "";
}

void PipeTable::SetValue(int row, int col, const wxString& value)
{
	CStartPPDoc *pDoc;
	CPipeAndNode *pPnN = getPipeAndNode(row, pDoc);
	if(!pPnN)
		return;
	CPipeAndNode &p = *pPnN;
	switch (col)
	{
		case 9:
		{
			double d;
			value.ToCDouble(&d);
			p.m_DIAM = d;
			CPipesSet pset;
			BOOL b_podzem = fabs(p.m_NAGV + 1) < 1e-6;
			pset.m_strPath = DATA_PATH;
			pset.m_strTable =
				_T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by
								 // DIAM, PODZ"),p.m_DIAM, int(b_podzem));
			pset.Open();
			// while (!set.IsEOF())
			for (; !pset.IsEOF(); pset.MoveNext())
				if (pset.m_PODZ == b_podzem && fabs(pset.m_DIAM - p.m_DIAM) < 0.1)
					break;
			{
				p.m_NAMA = pset.m_NAMA;
				p.m_NTOS = pset.m_NTOS;
				p.m_RTOS = pset.m_NTOS - pset.m_RTOS;
				p.m_VETR = pset.m_VETR;
				p.m_VEIZ = pset.m_VEIZ;
				p.m_VEPR = pset.m_VEPR;
				if (b_podzem)
				{
					p.m_NAGX = pset.m_DIIZ;
					p.m_SHTR = pset.m_SHTR;
				}
				p.m_RAOT = pset.m_RAOT;
				p.m_MARI = pset.m_MARI;
				p.m_NOTO = pset.m_NOTO;
				p.m_RATO = pset.m_NOTO - pset.m_RATO;
				if (p.m_MNEA == STR_KO)
				{
					p.m_RAOT = pset.m_SEFF;
					p.m_KOTR = pset.m_KPOD;
				}
			}
			pset.Close();
		}
		break;
		case 10: p.m_NAMA = value;
			break;
	default: return;
	}
	if (col >= 9 || col <= 10)
	{
		pDoc->m_pipes.m_vecPnN[row] = p;
		MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
		frame->m_bDontRefresh = true;
		pDoc->UpdateData(false);
		GetView()->ForceRefresh();
		frame->m_bDontRefresh = false;
	}
}

void PipeTable::SetValueAsDouble(int row, int col, double value)
{
	CStartPPDoc *pDoc;
	CPipeAndNode *pPnN = getPipeAndNode(row, pDoc);
	if(!pPnN)
		return;
	CPipeAndNode &p = *pPnN;
	switch (col)
	{
		case 0: p.m_OSIX = value;
			break;
		case 1: p.m_OSIY = value;
			break;
		case 2: p.m_OSIZ = value;
			break;
		case 3:
			p.setLPlan(value);
			break;
		case 4: p.setLGen(value);
			break;
		case 5:
			p.setAPlan(value);
			break;
		case 6:
			p.GetRelAngle(pDoc, &p);
			pDoc->RotateThisAndOthers(pPnN, DegToRad(value - p.a_plan_rel));
			break;
		case 7: p.setAProf(value);
			break;
		case 8: p.setUklon(value);
			break;
		case 9: p.m_DIAM = value;
			break;
		case 11: p.m_NTOS = value;
			break;
		case 12: p.m_RTOS = value;
			break;
		case 13: p.m_RADA = value;
			break;
		case 14: p.m_DABI = value;
			break;
		case 15: p.m_RATE = value;
			break;
		case 16: p.m_VETR = value;
			break;
		case 17: p.m_VEIZ = value;
			break;
		case 18: p.m_VEPR = value;
			break;
		case 19: p.m_KOPE = value;
			break;
		case 20: p.m_KOPR = value;
			break;


	}
	if (col < 10 || col>10)
	{
		MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
		frame->m_bDontRefresh = true;
		pDoc->UpdateData(false);
		GetView()->ForceRefresh();
		frame->m_bDontRefresh = false;
	}
}

int PipeTable::GetNumberCols()
{
    return 21;
}

wxString PipeTable::GetTypeName(int row, int col)
{
	wxUnusedVar(row);
	if (col<10 || col>10)
		return wxGRID_VALUE_FLOAT;
	return wxGRID_VALUE_STRING;
}

bool PipeTable::CanGetValueAs(int row, int col, const wxString& typeName)
{
	return CanSetValueAs(row, col, typeName);
}

CPipeAndNode * PipeTable::getPipeAndNode(int row, CStartPPDoc *&pDoc) const
{
	pDoc = GetCurDoc();
	if (!pDoc || row >= pDoc->m_pipes.m_vecPnN.size())
		return nullptr;
	CPipeAndNode* p = &pDoc->m_pipes.m_vecPnN[row];
	p->calc_angles();
	return p;
}

double PipeTable::GetValueAsDouble(int row, int col)
{
	CStartPPDoc *pDoc;
	CPipeAndNode *pPnN = getPipeAndNode(row, pDoc);
	if(!pPnN)
		return 0.0;
	CPipeAndNode &p = *pPnN;
	switch (col)
	{
	case 0: return p.m_OSIX;
	case 1: return p.m_OSIY;
	case 2: return p.m_OSIZ;
	case 3: return p.l_plan;
	case 4: return p.l_gen;
	case 5: return p.a_plan;
	case 6: p.GetRelAngle(pDoc, &p);
		return p.a_plan_rel;
	case 7: return p.a_prof;
	case 8: return p.uklon;
	case 9: return p.m_DIAM;
	case 11: return p.m_NTOS;
	case 12: return p.m_RTOS;
	case 13: return p.m_RADA;
	case 14: return p.m_DABI;
	case 15: return p.m_RATE;
	case 16: return p.m_VETR;
	case 17: return p.m_VEIZ;
	case 18: return p.m_VEPR;
	case 19: return p.m_KOPE;
	case 20: return p.m_KOPR;
	}
	return 0.0;
}

bool PipeTable::GetValueAsBool(int row, int col)
{
	return false;
}

void PipeTable::SetValueAsBool(int row, int col, bool value)
{
	CStartPPDoc *pDoc;
	CPipeAndNode *pPnN = getPipeAndNode(row, pDoc);
	if(!pPnN)
		return;
	CPipeAndNode &p = *pPnN;

}

bool PipeTable::CanSetValueAs(int row, int col, const wxString &typeName)
{
	if (col<10 && typeName==wxGRID_VALUE_FLOAT)
		return true;
	if (col>10 && typeName==wxGRID_VALUE_FLOAT)
		return true;
	return col == 10 && typeName == wxGRID_VALUE_STRING;
}

wxString PipeTable::GetRowLabelValue(int row)
{
	CStartPPDoc *pDoc;
	CPipeAndNode *pPnN =getPipeAndNode(row, pDoc);
	if (!pPnN)
		return "";
	return wxString::Format(_T("%g-%g"),pPnN->m_NAYZ, pPnN->m_KOYZ);
}

wxString PipeTable::GetColLabelValue(int col)
{
	wxStringList stringList;
	stringList.Add(_T("X"));
	stringList.Add(_T("Y"));
	stringList.Add(_T("Z"));
	stringList.Add(_T("Lплан"));
	stringList.Add(_T("Lобщ"));
	stringList.Add(_T("Aплан"));
	stringList.Add(_T("Aплан.отн."));
	stringList.Add(_T("Aпроф."));
	stringList.Add(_T("Уклон"));
	stringList.Add(_T("Диаметр"));
	stringList.Add(_T("Материал"));
	stringList.Add(_T("Толщ.стенки"));
	stringList.Add(_T("Тех.утон."));
	stringList.Add(_T("Pрасч"));
	stringList.Add(_T("Pисп"));
	stringList.Add(_T("Трасч"));
	stringList.Add(_T("ВесТр"));
	stringList.Add(_T("ВесИз"));
	stringList.Add(_T("ВесПр"));
	stringList.Add(_T("Kдавл."));
	stringList.Add(_T("Kизгиб"));
	if (col<stringList.size())
		return stringList[col];
	return wxGridTableBase::GetColLabelValue(col);
}

int PipeTable::GetNumberRows()
{
    CStartPPDoc *pDoc = GetCurDoc();
    return int(pDoc ? pDoc->m_pipes.m_vecPnN.size() : 0);
}

CStartPPDoc *PipeTable::GetCurDoc() const
{
    MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
    return frame->m_doc;
}
