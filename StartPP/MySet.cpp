#include "stdafx.h"
#include "MySet.h"


//#include "Pipes.h"

// реализация CMySet


IMPLEMENT_DYNAMIC(CMySet, CRecordset)

CMySet::CMySet(CDatabase* pdb)
	: CRecordset(pdb)
{
}

CString CMySet::GetDefaultConnect()
{
	CString str;
	//str.Format(_T("DSN=dBASE Files;DBQ=%s;DefaultDir=%s;DriverId=533;MaxBufferSize=2048;PageTimeout=5;"), m_strPath, m_strPath);
	/*
	CString strPath = AfxGetApp()->m_pszHelpFilePath;
	PathRemoveFileSpec(strPath.GetBuffer());
	strPath.ReleaseBuffer();
	m_strPath = strPath;
	*/
	//str.Format(_T("DSN=DBF;DBQ=%s\\Pipes.mdb;DefaultDir=%s;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;)"), m_strPath, m_strPath);
	//str.Format(_T("DSN=DBF;DBQ=%s\\Pipes.mdb"), ""/*m_strPath*/);
	return str;
}

CString CMySet::GetDefaultSQL()
{
	return m_strPath+_T("/")+m_strTable;
}

/////////////////////////////////////////////////////////////////////////////
// CPipesSet диагностика

#ifdef _DEBUG
void CMySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


