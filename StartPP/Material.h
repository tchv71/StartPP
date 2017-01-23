// Material.h : Declaration of the CMaterial

#pragma once
#include "MySet.h"

// code generated on 4 апреля 2015 г., 12:16

class CMaterial : public CMySet
{
public:
	CMaterial(CDatabase* pDatabase = nullptr);
	DECLARE_DYNAMIC(CMaterial)

	// Field/Param Data

	// The string types below (if present) reflect the actual data type of the
	// database field - CStringA for ANSI datatypes and CStringW for Unicode
	// datatypes. This is to prevent the ODBC driver from performing potentially
	// unnecessary conversions.  If you wish, you may change these members to
	// CString types and the ODBC driver will perform all necessary conversions.
	// (Note: You must use an ODBC driver version that is version 3.5 or greater
	// to support both Unicode and these conversions).

	CStringA m_MAT;
	CStringA m_CLAS;
	CStringA m_NOM;

	// Overrides
	// Wizard generated virtual function overrides
public:
	void DoFieldExchange(CFieldExchange* pFX) override; // RFX support

	// Implementation
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};

