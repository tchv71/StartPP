#include "stdafx.h"
#include "PipeDesc.h"


CPipeDesc::CPipeDesc(void) : NormaDoc(_T("РД 10-400-01(режим ПДН)")), TSet(-26.0f), Tcold(0), CalcStartComp(0), Tz(0),
                             TimeWork(30.0f), Ttest(0), CondSelSpring(0)
{
}


CPipeDesc::~CPipeDesc(void)
{
}

void CPipeDesc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << TSet;
		ar << Tcold;
		ar << CalcStartComp;
		ar << Tz;
		ar << TimeWork;
		ar << Ttest;
		ar << CondSelSpring;
		ar << NormaDoc;
	}
	else
	{
		ar >> TSet;
		ar >> Tcold;
		ar >> CalcStartComp;
		ar >> Tz;
		ar >> TimeWork;
		ar >> Ttest;
		ar >> CondSelSpring;
		ar >> NormaDoc;
	}
}

void CPipeDesc::WriteIni(CStdioFile& file)
{
	file.WriteString(_T("[Заголовок]\n"));
	file.WriteString(_T("ИД=20080506\n"));

	file.WriteString(_T("Режим=0\n[Общие_данные]\n"));
	file.WriteString(_T("Дата="));
	file.WriteString(Date);
	file.WriteString(_T("\n"));
	file.WriteString(_T("Трубопровод="));
	file.WriteString(Description);
	file.WriteString(_T("\n"));
	CString str;
	str.Format(_T("%g"), TSet);
	file.WriteString(_T("Т_монтажа="));
	file.WriteString(str);
	file.WriteString(_T("\n"));
	str.Format(_T("%g"), Tcold);
	file.WriteString(_T("Т_охлаждения="));
	file.WriteString(str);
	file.WriteString(_T("\n"));
	str.Format(_T("%d"), CalcStartComp);
	file.WriteString(_T("Расчет_компенсаторов="));
	file.WriteString(str);
	file.WriteString(_T("\n"));
	str.Format(_T("%g"), Tz);
	file.WriteString(_T("Т_компенсаторов="));
	file.WriteString(str);
	file.WriteString(_T("\n"));
	file.WriteString(_T("Нормаль="));
	file.WriteString(NormaDoc);
	file.WriteString(_T("\n"));
	str.Format(_T("%g"), TimeWork);
	file.WriteString(_T("Ресурс_трубопровода="));
	file.WriteString(str);
	file.WriteString(_T("\n"));
	file.WriteString(_T("Среда_испытаний="));
	file.WriteString(Envir);
	file.WriteString(_T("\n"));
	str.Format(_T("%g"), Ttest);
	file.WriteString(_T("Т_испытания="));
	file.WriteString(str);
	file.WriteString(_T("\n"));
}

