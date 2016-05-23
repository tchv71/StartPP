// MFCApplication1Set.h: интерфейс класса CStartPPSet
//

#include "PipeAndNode.h"

#pragma once

// создаваемый код 1 декабря 2012 г., 18:46


class CStartPPSet : public CRecordset, public CPipeAndNode
{
public:
	CStartPPSet(CDatabase* pDatabase = nullptr);
	DECLARE_DYNAMIC(CStartPPSet)

	// Данные полей и параметров

	// Следующие типы строк (если присутствуют) отражают фактические типы данных 
	// поля базы данных - CStringA для типов данных ANSI и CStringW для типов 
	// данных Юникода. Это должно предотвратить выполнение драйвером ODBC 
	// потенциально ненужных преобразований. При желании можно заменить эти члены на 
	// типы CString, и драйвер ODBC выполнит все необходимые преобразования.
	// (Примечание. Необходимо использовать драйвер ODBC версии 3.5 или более поздней 
	// для поддержки как Юникода, так и этих преобразований).

	// Переопределение
	// Мастер создал переопределения виртуальных функций
public:
	CString m_strPath;
	CString m_strTable;
	CString GetDefaultConnect() override; // Строка подключения по умолчанию

	CString GetDefaultSQL() override; // код SQL по умолчанию для  набора записей
	void DoFieldExchange(CFieldExchange* pFX) override; // поддержка RFX

	// Реализация
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
	void SetOldSet(bool bOldSet)
	{
		m_bOldSet = bOldSet;
		m_nFields = m_bOldSet ? 58 : 67;
	}

protected:
	bool m_bOldSet;
};

