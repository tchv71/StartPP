#include "stdafx.h"
#include "Recordset.h"
#include <wx/filename.h>
#include "dbf_inl.h"
#include "dbf_wx.h"
#include "dbf_wx_inl.h"


void CRecordset::RFX_Single(CFieldExchange* pFX, LPCTSTR szName, float& value)
{
	if (pFX->m_nOperation == CFieldExchange::SQL_PARAM_INPUT)
	{
		wxString strName(szName);
		strName = strName.SubString(1, strName.Len() - 2);
		double dblVal;
		if (!m_dbf.Read(strName.ToAscii().data(), &dblVal))
		{
			long lVal = 0;
			/*bool bResult = */m_dbf.Read(strName.ToAscii().data(), &lVal);
			/*			if (!bResult)
							throw std::exception();*/
			dblVal = lVal;
		}
		value = dblVal;
	}
}

void CRecordset::RFX_Text(CFieldExchange* pFX, LPCTSTR szName, CStringA& value,
	// Default max length for char and varchar, default datasource type
	int nMaxLength, int nColumnType, short nScale)
{
	UNREFERENCED_PARAMETER(nScale);
	UNREFERENCED_PARAMETER(nColumnType);
	UNREFERENCED_PARAMETER(nMaxLength);
	if (pFX->m_nOperation == CFieldExchange::SQL_PARAM_INPUT)
	{
		wxString strName(szName);
		strName = strName.SubString(1, strName.Len() - 2);
		wxString buf;
		if (!m_dbf.Read(strName.ToAscii().data(), &value))
			assert(true);//throw std::exception();
	}
}

// boolean data
void CRecordset::RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, BOOL& value)
{
	if (pFX->m_nOperation == CFieldExchange::SQL_PARAM_INPUT)
	{
		wxString strName(szName);
		strName = strName.SubString(1, strName.Len() - 2);
		bool bVal = false;
		if (!m_dbf.Read(strName.ToAscii().data(), &bVal))
			throw std::exception();
		value = bVal;
	}

}

void CRecordset::RFX_Int(CFieldExchange* pFX, LPCTSTR szName, int& value)
{
	if (pFX->m_nOperation == CFieldExchange::SQL_PARAM_INPUT)
	{
		wxString strName(szName);
		strName = strName.SubString(1, strName.Len() - 2);
		long lVal;
		if (!m_dbf.Read(strName.ToAscii().data(), &lVal))
			throw std::exception();
		value = lVal;
	}

}

CRecordset::CRecordset(CDatabase* pdb) : m_bIsEOF(false), m_nFields(0), m_nDefaultType(dynaset)
{
	UNREFERENCED_PARAMETER(pdb);
}


CRecordset::~CRecordset()
{
}

bool CRecordset::Open()
{
	try
	{
		if (!m_dbf.Open(wxFileName(GetDefaultSQL()), dbf_editmode_readonly))
		{
			m_bIsEOF = true;
			return false;
		}
		m_bIsEOF = false;
		MoveNext();
	}
	catch (...)
	{
		Close();
		throw std::exception();
	}
	return true;
}

void CRecordset::Close()
{
	m_dbf.Close();
}

bool CRecordset::IsEOF() const
{
	return m_bIsEOF;
}

void CRecordset::MoveNext()
{
	while (!m_bIsEOF)
	{
		m_bIsEOF = !m_dbf.GetNextRecord();
		if (!m_bIsEOF && !m_dbf.IsRecordDeleted())
			break;
	}
	if (m_bIsEOF)
		return;
	m_fieldExchange.m_nOperation = CFieldExchange::SQL_PARAM_INPUT;
	DoFieldExchange(&m_fieldExchange);
}

