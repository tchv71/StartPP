// TroinicsSet.h: интерфейс класса CTroinicsSet
//
#include "MySet.h"

#pragma once

// создаваемый код 9 февраля 2013 г., 19:49
struct STroinics
{
	// Данные полей и параметров

	// Следующие типы строк (если присутствуют) отражают фактические типы данных 
	// поля базы данных - CStringA для типов данных ANSI и CStringW для типов 
	// данных Юникода. Это должно предотвратить выполнение драйвером ODBC 
	// потенциально ненужных преобразований. При желании можно заменить эти члены на 
	// типы CString, и драйвер ODBC выполнит все необходимые преобразования.
	// (Примечание. Необходимо использовать драйвер ODBC версии 3.5 или более поздней 
	// для поддержки как Юникода, так и этих преобразований).

	float m_DIAM;
	float m_DIAMSH;
	float m_NTSTM;
	float m_RTSTM;
	float m_NTSTSH;
	float m_RTSTSH;
	float m_WIDTHNAK;
	float m_THINKNAK;
	float m_VES;
	float m_VIS_SHTU;
	float m_KORPUS;
	bool operator <(const STroinics& other) const
	{
		if (fabs(m_DIAM - other.m_DIAM)<0.1)
			return m_DIAMSH < other.m_DIAMSH;
		return m_DIAM < other.m_DIAM;
	}
	unsigned m_pos;

};


class CTroinicsSet : public CMySet, public STroinics
{
public:
	CTroinicsSet(CDatabase* pDatabase = nullptr);
	DECLARE_DYNAMIC(CTroinicsSet)

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

