#include "stdafx.h"
#include "Recordset.h"
#include <wx/filename.h>
#include "dbf.inl"
#include "dbf_wx.h"
#include "dbf_wx_inl.h"


class m_dbf;
class m_dbf;
void CRecordset::RFX_Single(CFieldExchange* pFX, LPCTSTR szName, float& value)
{
    if (pFX->m_nOperation ==  CFieldExchange::SQL_PARAM_INPUT)
    {
        wxString strName(szName);
        strName = strName.SubString(1, strName.Len()-2);
        double dblVal;
        m_dbf.Read(strName.ToAscii().data(), &dblVal);
        value = dblVal;
    }
}

void CRecordset::RFX_Text(CFieldExchange* pFX, LPCTSTR szName, CStringA &value,
	// Default max length for char and varchar, default datasource type
	int nMaxLength, int nColumnType, short nScale)
{
    if (pFX->m_nOperation ==  CFieldExchange::SQL_PARAM_INPUT)
    {
        wxString strName(szName);
        strName = strName.SubString(1, strName.Len()-2);
        wxString buf;
        m_dbf.Read(strName.ToAscii().data(), &value);
     }
}

// boolean data
void CRecordset::RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, BOOL& value)
{
    if (pFX->m_nOperation ==  CFieldExchange::SQL_PARAM_INPUT)
    {
        wxString strName(szName);
        strName = strName.SubString(1, strName.Len()-2);
        bool bVal;
        m_dbf.Read(strName.ToAscii().data(), &bVal);
        value = bVal;
    }

}

void CRecordset::RFX_Int(CFieldExchange* pFX, LPCTSTR szName, int& value)
{
    if (pFX->m_nOperation ==  CFieldExchange::SQL_PARAM_INPUT)
    {
        wxString strName(szName);
        strName = strName.SubString(1, strName.Len()-2);
        long lVal;
        m_dbf.Read(strName.ToAscii().data(), &lVal);
        value = lVal;
    }

}

CRecordset::CRecordset(CDatabase* pdb) : m_bIsEOF(false), m_fieldExchange(0,this)
{
 
}


CRecordset::~CRecordset()
{
}

bool CRecordset::Open()
{
    if (!m_dbf.Open(wxFileName(GetDefaultSQL()),dbf_editmode_readonly))
        return false;
	m_bIsEOF  = !m_dbf.GetNextRecord();
    m_fieldExchange.m_nOperation = CFieldExchange::SQL_PARAM_INPUT;
    DoFieldExchange(&m_fieldExchange);
    return true;
}

void CRecordset::Close()
{
    m_dbf.Close();
}

bool CRecordset::IsEOF()
{
    return m_bIsEOF;
}

void CRecordset::MoveNext()
{
    m_bIsEOF = !m_dbf.GetNextRecord();
    m_fieldExchange.m_nOperation = CFieldExchange::SQL_PARAM_INPUT;
    DoFieldExchange(&m_fieldExchange);
}

void CRecordset::DoFieldExchange(CFieldExchange* pFX)
{
}