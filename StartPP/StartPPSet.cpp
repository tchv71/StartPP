// MFCApplication1Set.cpp : реализация класса CStartPPSet
//

#include "stdafx.h"
#include "StartPPSet.h"
#include "ODBCINST.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// реализация CStartPPSet

// создаваемый код 1 декабря 2012 г., 18:46

IMPLEMENT_DYNAMIC(CStartPPSet, CRecordset)

CStartPPSet::CStartPPSet(CDatabase* pdb)
	: CRecordset(pdb)
	  , m_bOldSet(false)
{
	m_nFields = 67;
	m_nDefaultType = dynaset;
	::SQLConfigDataSource(nullptr,ODBC_ADD_DSN, _T("Microsoft dBase Driver (*.dbf)"),
	                      _T("DSN=dBASE Files\0")
	                      _T("MaxScanRows=20\0"));
}

//#error Проблема безопасности: строка подключения может содержать пароль 
// Следующая строка подключения может содержать незашифрованные пароли или 
// другую конфиденциальную информацию. Удалите #error после просмотра строки подключения 
// в целях безопасности. Возможно, 
// потребуется сохранить пароль в другом виде или использовать другую проверку подлинности.
CString CStartPPSet::GetDefaultConnect()
{
	CString str;
	str.Format(_T("DSN=dBASE Files;DBQ=%s;DefaultDir=%s;DriverId=533;Extended Properties=dBASE IV;MaxBufferSize=2048;PageTimeout=5;"), m_strPath, m_strPath);
	return str;
}

CString CStartPPSet::GetDefaultSQL()
{
	CString str;
	str.Format(_T("[%s] order by INDX"), m_strTable);
	return str;
}

void CStartPPSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	// Такие макросы, как RFX_Text() и RFX_Int(), зависят от типа 
	// переменной члена, а не от типа поля в базе данных.
	// ODBC выполняет попытку автоматически преобразовать значение столбца к нужному типу
	RFX_Single(pFX, _T("[NAYZ]"), m_NAYZ);
	RFX_Single(pFX, _T("[KOYZ]"), m_KOYZ);
	RFX_Single(pFX, _T("[OSIX]"), m_OSIX);
	RFX_Single(pFX, _T("[OSIY]"), m_OSIY);
	RFX_Single(pFX, _T("[OSIZ]"), m_OSIZ);
	RFX_Text(pFX, _T("[NAMA]"), m_NAMA);
	RFX_Single(pFX, _T("[DIAM]"), m_DIAM);
	RFX_Single(pFX, _T("[NTOS]"), m_NTOS);
	RFX_Single(pFX, _T("[RTOS]"), m_RTOS);
	RFX_Single(pFX, _T("[RATE]"), m_RATE);
	RFX_Single(pFX, _T("[RADA]"), m_RADA);
	RFX_Single(pFX, _T("[VETR]"), m_VETR);
	RFX_Single(pFX, _T("[VEIZ]"), m_VEIZ);
	RFX_Single(pFX, _T("[VEPR]"), m_VEPR);
	RFX_Single(pFX, _T("[KOPE]"), m_KOPE);
	RFX_Single(pFX, _T("[KOPR]"), m_KOPR);
	RFX_Single(pFX, _T("[KOYS]"), m_KOYS);
	RFX_Single(pFX, _T("[KORA]"), m_KORA);
	RFX_Text(pFX, _T("[MNEA]"), m_MNEA);
	RFX_Text(pFX, _T("[MNEO]"), m_MNEO);
	RFX_Single(pFX, _T("[DABI]"), m_DABI);
	RFX_Single(pFX, _T("[RAOT]"), m_RAOT);
	RFX_Single(pFX, _T("[DIGI]"), m_DIGI);
	RFX_Text(pFX, _T("[MARI]"), m_MARI);
	RFX_Single(pFX, _T("[NOTO]"), m_NOTO);
	RFX_Single(pFX, _T("[RATO]"), m_RATO);
	RFX_Single(pFX, _T("[KOTR]"), m_KOTR);
	RFX_Single(pFX, _T("[VESA]"), m_VESA);
	RFX_Single(pFX, _T("[SEOP]"), m_SEOP);
	RFX_Single(pFX, _T("[VEYS]"), m_VEYS);
	RFX_Text(pFX, _T("[PELI]"), m_PELI);
	RFX_Text(pFX, _T("[PEYG]"), m_PEYG);
	RFX_Text(pFX, _T("[TIDE]"), m_TIDE);
	RFX_Single(pFX, _T("[RASG]"), m_RASG);
	RFX_Single(pFX, _T("[DEFX]"), m_DEFX);
	RFX_Single(pFX, _T("[DEFY]"), m_DEFY);
	RFX_Single(pFX, _T("[DEFZ]"), m_DEFZ);
	RFX_Single(pFX, _T("[DEME]"), m_DEME);
	RFX_Single(pFX, _T("[NAGV]"), m_NAGV);
	RFX_Single(pFX, _T("[NAGX]"), m_NAGX);
	RFX_Single(pFX, _T("[NAGY]"), m_NAGY);
	RFX_Single(pFX, _T("[NAGZ]"), m_NAGZ);
	RFX_Single(pFX, _T("[VESX]"), m_VESX);
	RFX_Single(pFX, _T("[VESY]"), m_VESY);
	RFX_Single(pFX, _T("[VESZ]"), m_VESZ);
	RFX_Single(pFX, _T("[SILX]"), m_SILX);
	RFX_Single(pFX, _T("[SILY]"), m_SILY);
	RFX_Single(pFX, _T("[SILZ]"), m_SILZ);
	RFX_Single(pFX, _T("[MOMX]"), m_MOMX);
	RFX_Single(pFX, _T("[MOMY]"), m_MOMY);
	RFX_Single(pFX, _T("[MOMZ]"), m_MOMZ);
	RFX_Single(pFX, _T("[NAAN]"), m_NAAN);
	RFX_Single(pFX, _T("[NABA]"), m_NABA);
	RFX_Single(pFX, _T("[VIZA]"), m_VIZA);
	RFX_Single(pFX, _T("[SHTR]"), m_SHTR);
	RFX_Single(pFX, _T("[VIVO]"), m_VIVO);
	RFX_Single(pFX, _T("[INDX]"), m_INDX);
	RFX_Single(pFX, _T("[NONE]"), m_NONE);
	if (!m_bOldSet)
	{
		RFX_Text(pFX, _T("[VREZKA]"), m_VREZKA);
		RFX_Text(pFX, _T("[TEXT]"), m_TEXT);
		RFX_Single(pFX, _T("[KOR]"), m_KOR);
		RFX_Single(pFX, _T("[VIZA2]"), m_VIZA2);
		RFX_Single(pFX, _T("[OS_TR1]"), m_OS_TR1);
		RFX_Single(pFX, _T("[OS_TR2]"), m_OS_TR2);
		RFX_Single(pFX, _T("[KORPUS]"), m_KORPUS);
		RFX_Bool(pFX, _T("[TYPE_KOMP]"), m_TYPE_KOMP);
		RFX_Single(pFX, _T("[L_KOMP]"), m_L_KOMP);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CStartPPSet диагностика

#ifdef _DEBUG
void CStartPPSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStartPPSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


