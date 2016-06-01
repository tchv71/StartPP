#include "stdafx.h"
#include "Recordset.h"



void RFX_Single(CFieldExchange* pFX, LPCTSTR szName, float& value)
{
}

void RFX_Text(CFieldExchange* pFX, LPCTSTR szName, CStringA &value,
	// Default max length for char and varchar, default datasource type
	int nMaxLength, int nColumnType, short nScale)
{
}

// boolean data
void RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, BOOL& value)
{

}

void RFX_Int(CFieldExchange* pFX, LPCTSTR szName, int& value)
{

}

CRecordset::CRecordset(CDatabase* pdb)
{
}


CRecordset::~CRecordset()
{
}

void CRecordset::DoFieldExchange(CFieldExchange* pFX)
{
}