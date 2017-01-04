// ArmatSet.h: интерфейс класса CArmatSet
//
#include "MySet.h"

#pragma once

// создаваемый код 7 февраля 2013 г., 20:42

class CArmatSet : public CMySet
{
public:
	CArmatSet(CDatabase* pDatabase = nullptr);
	DECLARE_DYNAMIC(CArmatSet)

	// Данные полей и параметров

	// Следующие типы строк (если присутствуют) отражают фактические типы данных 
	// поля базы данных - CStringA для типов данных ANSI и CStringW для типов 
	// данных Юникода. Это должно предотвратить выполнение драйвером ODBC 
	// потенциально ненужных преобразований. При желании можно заменить эти члены на 
	// типы CString, и драйвер ODBC выполнит все необходимые преобразования.
	// (Примечание. Необходимо использовать драйвер ODBC версии 3.5 или более поздней 
	// для поддержки как Юникода, так и этих преобразований).

	float m_DIAM;
	float m_NOTO;
	float m_RATO;
	float m_RAOT;
	float m_VESA;
	float m_RAOT1;
	float m_VESA1;
	float m_NAG1;
	float m_NAG2;

	// Переопределение
	// Мастер создал переопределения виртуальных функций
public:
	void DoFieldExchange(CFieldExchange* pFX) override; // поддержка RFX

	// Реализация
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};

