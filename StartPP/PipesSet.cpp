// PipesSet.cpp : реализация класса CPipesSet
//

#include "stdafx.h"
//#include "Pipes.h"
#include "PipesSet.h"

// реализация CPipesSet

// создаваемый код 31 января 2013 г., 22:33

IMPLEMENT_DYNAMIC(CPipesSet, CMySet)

CPipesSet::CPipesSet(CDatabase* pdb)
	: CMySet(pdb)
{
	m_DIAM = 0.0;
	m_NTOS = 0.0;
	m_RTOS = 0.0;
	m_NAMA = "";
	m_VETR = 0.0;
	m_VEIZ = 0.0;
	m_VEPR = 0.0;
	m_DIIZ = 0.0;
	m_RAOT = 0.0;
	m_VESA = 0.0;
	m_MARI = "";
	m_NOTO = 0.0;
	m_RATO = 0.0;
	m_SEFF = 0.0;
	m_KPOD = 0.0;
	m_SHTR = 0.0;
	m_PODZ = FALSE;
	m_IZTO = 0.0;
	m_nFields = 18;
	m_nDefaultType = dynaset;
}

void CPipesSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Такие макросы, как RFX_Text() и RFX_Int(), зависят от типа 
	// переменной члена, а не от типа поля в базе данных.
	// ODBC выполняет попытку автоматически преобразовать значение столбца к нужному типу
	RFX_Single(pFX, _T("[DIAM]"), m_DIAM);
	RFX_Single(pFX, _T("[NTOS]"), m_NTOS);
	RFX_Single(pFX, _T("[RTOS]"), m_RTOS);
	RFX_Text(pFX, _T("[NAMA]"), m_NAMA);
	RFX_Single(pFX, _T("[VETR]"), m_VETR);
	RFX_Single(pFX, _T("[VEIZ]"), m_VEIZ);
	RFX_Single(pFX, _T("[VEPR]"), m_VEPR);
	RFX_Single(pFX, _T("[DIIZ]"), m_DIIZ);
	RFX_Single(pFX, _T("[RAOT]"), m_RAOT);
	RFX_Single(pFX, _T("[VESA]"), m_VESA);
	RFX_Text(pFX, _T("[MARI]"), m_MARI);
	RFX_Single(pFX, _T("[NOTO]"), m_NOTO);
	RFX_Single(pFX, _T("[RATO]"), m_RATO);
	RFX_Single(pFX, _T("[SEFF]"), m_SEFF);
	RFX_Single(pFX, _T("[KPOD]"), m_KPOD);
	RFX_Single(pFX, _T("[SHTR]"), m_SHTR);
	RFX_Bool(pFX, _T("[PODZ]"), m_PODZ);
	RFX_Single(pFX, _T("[IZTO]"), m_IZTO);
}

/////////////////////////////////////////////////////////////////////////////
// CPipesSet диагностика

#ifdef _DEBUG
void CPipesSet::AssertValid() const
{
	CMySet::AssertValid();
}

void CPipesSet::Dump(CDumpContext& dc) const
{
	CMySet::Dump(dc);
}
#endif //_DEBUG


