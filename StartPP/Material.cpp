// Material.h : Implementation of the CMaterial class


// CMaterial implementation

// code generated on 4 апреля 2015 г., 12:16

#include "stdafx.h"
#include "Material.h"
IMPLEMENT_DYNAMIC(CMaterial, CMySet)

CMaterial::CMaterial(CDatabase* pdb)
	: CMySet(pdb)
{
	m_MAT = L"";
	m_CLAS = L"";
	m_NOM = L"";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}

void CMaterial::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Macros such as RFX_Text() and RFX_Int() are dependent on the
	// type of the member variable, not the type of the field in the database.
	// ODBC will try to automatically convert the column value to the requested type
	RFX_Text(pFX, _T("[MAT]"), m_MAT);
	RFX_Text(pFX, _T("[CLAS]"), m_CLAS);
	RFX_Text(pFX, _T("[NOM]"), m_NOM);
}

/////////////////////////////////////////////////////////////////////////////
// CMaterial diagnostics

#ifdef _DEBUG
void CMaterial::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMaterial::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


