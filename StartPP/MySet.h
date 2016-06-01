#pragma once

class CFieldExchange;
class CDumpContext;

#include "Recordset.h"
class CDatabase;


class CMySet : public CRecordset
{
public:
	CMySet(CDatabase* pDatabase = nullptr);
	DECLARE_DYNAMIC(CMySet)

	CString m_strPath;
	CString m_strTable;
	CString GetDefaultConnect() override; // Строка подключения по умолчанию

	CString GetDefaultSQL() override; // код SQL по умолчанию для  набора записей
	// Реализация
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};

