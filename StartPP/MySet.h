#pragma once

#ifdef WX
class CFieldExchange;

class CRecordset
{
public:
    int m_nFields;
    virtual CString GetDefaultConnect();  // Строка подключения по умолчанию
    virtual CString GetDefaultSQL(); // код SQL по умолчанию для  набора записей
   	virtual void DoFieldExchange(CFieldExchange* pFX); // поддержка RFX
};
class CDatabase;

#endif

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

