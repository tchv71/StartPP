#pragma once
#include "wx\object.h"

class CRecordset : public wxObject
{
public:
	int m_nFields;
	enum { dynaset } m_nDefaultType;

	virtual CString GetDefaultConnect();  // Строка подключения по умолчанию
	virtual CString GetDefaultSQL(); // код SQL по умолчанию для  набора записей
	virtual void DoFieldExchange(CFieldExchange* pFX); // поддержка RFX
	bool Open() { return true; }
	bool IsEOF() { return false; }
	void MoveNext() {}
	void Close() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};