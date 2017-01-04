#include "stdafx.h"
#include "PipeDesc.h"

static const int kCurrentVersion = 1;


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
		ar << (float(kCurrentVersion));
		ar << TSet;
		ar << Tcold;
		ar << CalcStartComp;
		ar << Tz;
		ar << TimeWork;
		ar << Ttest;
		ar << CondSelSpring;
		ar << NormaDoc;
		ar << Date;
		ar << Description;
		ar << Envir;
		ar << NormaSpring;
	}
	else
	{
		float fVersion;
		ar >> fVersion;
		int nVersion = 0;
		if (fVersion!=-26.0f)
			nVersion = int(fVersion);
		if (nVersion != 0)
			ar >> TSet;
		ar >> Tcold;
		ar >> CalcStartComp;
		ar >> Tz;
		ar >> TimeWork;
		ar >> Ttest;
		ar >> CondSelSpring;
		ar >> NormaDoc;
		if (nVersion>0)
		{
			ar >> Date;
			ar >> Description;
			ar >> Envir;
			ar >> NormaSpring;
		}
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
	file.WriteString(_T("Т_монтажа="));
	file.WriteString(CString::Format(_T("%g"), TSet));
	file.WriteString(_T("\n"));
	file.WriteString(_T("Т_охлаждения="));
	file.WriteString(CString::Format(_T("%g"), Tcold));
	file.WriteString(_T("\n"));
	file.WriteString(_T("Расчет_компенсаторов="));
	file.WriteString(CString::Format(_T("%d"), CalcStartComp));
	file.WriteString(_T("\n"));
	file.WriteString(_T("Т_компенсаторов="));
	file.WriteString(CString::Format(_T("%g"), Tz));
	file.WriteString(_T("\n"));
	file.WriteString(_T("Нормаль="));
	file.WriteString(NormaDoc);
	file.WriteString(_T("\n"));
	file.WriteString(_T("Ресурс_трубопровода="));
	file.WriteString(CString::Format(_T("%g"), TimeWork));
	file.WriteString(_T("\n"));
	file.WriteString(_T("Среда_испытаний="));
	file.WriteString(Envir);
	file.WriteString(_T("\n"));
	file.WriteString(_T("Т_испытания="));
	file.WriteString(CString::Format(_T("%g"), Ttest));
	file.WriteString(_T("\n"));
}

