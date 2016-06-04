// ArmatSet.cpp : реализация класса CArmatSet
//

#include "stdafx.h"
#include "ArmatSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// реализация CArmatSet

// создаваемый код 7 февраля 2013 г., 20:42

IMPLEMENT_DYNAMIC(CArmatSet, CRecordset)

CArmatSet::CArmatSet(CDatabase* pdb)
	: CMySet(pdb)
{
	m_DIAM = 0.0;
	m_NOTO = 0.0;
	m_RATO = 0.0;
	m_RAOT = 0.0;
	m_VESA = 0.0;
	m_RAOT1 = 0.0;
	m_VESA1 = 0.0;
	m_NAG1 = 0.0;
	m_NAG2 = 0.0;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}

void CArmatSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Такие макросы, как RFX_Text() и RFX_Int(), зависят от типа 
	// переменной члена, а не от типа поля в базе данных.
	// ODBC выполняет попытку автоматически преобразовать значение столбца к нужному типу
	RFX_Single(pFX, _T("[DIAM]"), m_DIAM);
	RFX_Single(pFX, _T("[NOTO]"), m_NOTO);
	RFX_Single(pFX, _T("[RATO]"), m_RATO);
	RFX_Single(pFX, _T("[RAOT]"), m_RAOT);
	RFX_Single(pFX, _T("[VESA]"), m_VESA);
	RFX_Single(pFX, _T("[RAOT1]"), m_RAOT1);
	RFX_Single(pFX, _T("[VESA1]"), m_VESA1);
	RFX_Single(pFX, _T("[NAG1]"), m_NAG1);
	RFX_Single(pFX, _T("[NAG2]"), m_NAG2);
}

/////////////////////////////////////////////////////////////////////////////
// CArmatSet диагностика

#ifdef _DEBUG
void CArmatSet::AssertValid() const
{
	CMySet::AssertValid();
}

void CArmatSet::Dump(CDumpContext& dc) const
{
	CMySet::Dump(dc);
}
#endif //_DEBUG


