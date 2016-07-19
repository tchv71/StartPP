// PipesSet.h: интерфейс класса CPipesSet
//
#include "MySet.h"

#pragma once

// создаваемый код 31 января 2013 г., 22:33

struct SPipe
{
	float m_DIAM;
	float m_NTOS;
	float m_RTOS;
	CStringA m_NAMA;
	float m_VETR;
	float m_VEIZ;
	float m_VEPR;
	float m_DIIZ;
	float m_RAOT;
	float m_VESA;
	CStringA m_MARI;
	float m_NOTO;
	float m_RATO;
	float m_SEFF;
	float m_KPOD;
	float m_SHTR;
	BOOL m_PODZ;
	float m_IZTO;
	bool operator <(const SPipe& other)
	{
		if (m_PODZ == other.m_PODZ)
			return m_DIAM < other.m_DIAM;
		return m_PODZ < other.m_PODZ;
	}
};

class CPipesSet : public CMySet, public SPipe
{
public:
	CPipesSet(CDatabase* pDatabase = nullptr);
	DECLARE_DYNAMIC(CPipesSet)

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
	void DoFieldExchange(CFieldExchange* pFX) override; // поддержка RFX

	// Реализация
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif
};

