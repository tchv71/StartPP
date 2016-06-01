#pragma once

class CFieldExchange;
class CDumpContext;

class CRecordset : public wxObject
{
public:
    int m_nFields;
	enum { dynaset } m_nDefaultType;

    virtual CString GetDefaultConnect();  // Строка подключения по умолчанию
    virtual CString GetDefaultSQL(); // код SQL по умолчанию для  набора записей
   	virtual void DoFieldExchange(CFieldExchange* pFX); // поддержка RFX
	bool Open() { return true;}
	bool IsEOF() {return false;} 
	void MoveNext() {}
	void Close() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
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

