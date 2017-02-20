#include "stdafx.h"
#include "PipeTable.h"
#include "main.h"
#include "MainFrame.h"
#include "Material.h"

PipeTable::PipeTable()
{
}

PipeTable::~PipeTable()
{
}


wxString PipeTable::GetValue(int row, int col)
{
	CStartPPDoc *pDoc = GetCurDoc();
	if (!pDoc)
		return "";
	CPipeAndNode& p=pDoc->m_pipes.m_vecPnN[row];
	p.calc_angles();
	switch (col)
	{
		case 0: return wxString::Format(_T("%.3f"), p.m_OSIX);
		case 1: return wxString::Format(_T("%.3f"), p.m_OSIY);
		case 2: return wxString::Format(_T("%.3f"), p.m_OSIZ);
		case 3: return wxString::Format(_T("%.3f"), p.l_plan);
		case 4: return wxString::Format(_T("%.3f"), p.l_gen);
		case 5: return wxString::Format(_T("%.1f"), p.a_plan);
		case 6: p.GetRelAngle(pDoc, &p);
			return wxString::Format(_T("%.1f"), p.a_plan_rel);
		case 7: return wxString::Format(_T("%.1f"), p.a_prof);
		case 8: return wxString::Format(_T("%.0f"), p.uklon);
		case 9: return wxString::Format(_T("%.0f"), p.m_DIAM);
		case 10: return p.m_NAMA;
		case 11: return wxString::Format(_T("%.1f"), p.m_NTOS);
		case 12: return wxString::Format(_T("%.2f"), p.m_RTOS);
		case 13: return wxString::Format(_T("%.1f"), p.m_RADA);
		case 14: return wxString::Format(_T("%.1f"), p.m_DABI);
		case 15: return wxString::Format(_T("%.1f"), p.m_RATE);
	}
	return "1";
}

void PipeTable::SetValue(int row, int col, const wxString& value)
{
	CStartPPDoc *pDoc = GetCurDoc();
	if (!pDoc)
		return;
	CPipeAndNode& p=pDoc->m_pipes.m_vecPnN[row];
	switch (col)
	{
		case 10: p.m_NAMA = value;
			pDoc->UpdateData(false);
			return;
	}
}

void PipeTable::SetValueAsDouble(int row, int col, double value)
{
	CStartPPDoc *pDoc = GetCurDoc();
	if (!pDoc)
		return;
	CPipeAndNode& p=pDoc->m_pipes.m_vecPnN[row];
	p.calc_angles();
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
		case 6: // p.GetRelAngle(pDoc, &p);
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

	}
	if (col<10 || col>10)
		pDoc->UpdateData(false);
}

int PipeTable::GetNumberCols()
{
    return 20;
}

wxString PipeTable::GetTypeName(int row, int col)
{
	if (col<10)
		return wxGRID_VALUE_FLOAT;
	if (col==10)
		return wxGRID_VALUE_STRING;
	if (col<16)
		return wxGRID_VALUE_FLOAT;

	return wxGRID_VALUE_STRING;
}

bool PipeTable::CanSetValueAs(int row, int col, const wxString &typeName)
{
	if (col<10 && typeName==wxGRID_VALUE_FLOAT)
		return true;
	if (col>10 && col<16 && typeName==wxGRID_VALUE_FLOAT)
		return true;
	return wxGridTableBase::CanSetValueAs(row, col, typeName);
}

wxString PipeTable::GetRowLabelValue(int row)
{
	CStartPPDoc *pDoc = GetCurDoc();
	if (!pDoc)
		return "";
	return wxString::Format(_T("%g-%g"), pDoc->m_pipes.m_vecPnN[row].m_NAYZ, pDoc->m_pipes.m_vecPnN[row].m_KOYZ);
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
	if (col<stringList.size())
		return stringList[col];
	return wxGridTableBase::GetColLabelValue(col);
}

int PipeTable::GetNumberRows()
{
    CStartPPDoc *pDoc = GetCurDoc();
    return int(pDoc ? pDoc->m_pipes.m_vecPnN.size() : 0);
}

CStartPPDoc *PipeTable::GetCurDoc()
{
    MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
    return frame->m_doc;
}
