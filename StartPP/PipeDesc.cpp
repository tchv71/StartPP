#include "stdafx.h"
#include "PipeDesc.h"
#include "Strings.h"

static const int kCurrentVersion = 1;
extern CString _R(CString s);


CPipeDesc::CPipeDesc(void) : NormaDoc(IDS_PDD_RD_10_400_01_PDN), TSet(-26.0f), Tcold(0), CalcStartComp(0), Tz(0),
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
		ar << float(kCurrentVersion);
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

void CPipeDesc::WriteIni(CStdioFile& file) const
{
	file.WriteString(_T("[Заголовок]\n"));
	file.WriteString(_T("ИД=20080506\n"));
	file.WriteString(_T("Режим=0\n[Общие_данные]\n"));
	file.WriteString(CString::Format(_T("Дата=%s"),LPCTSTR(Date.c_str())));
	file.WriteString(CString::Format(_T("Трубопровод=%s\n"),LPCTSTR(Description.c_str())));
	file.WriteString(_R(CString::Format(_T("Т_монтажа=%g\n"), TSet)));
	file.WriteString(_R(CString::Format(_T("Т_охлаждения=%g\n"), Tcold)));
	file.WriteString(CString::Format(_T("Расчет_компенсаторов=%d\n"), CalcStartComp));
	file.WriteString(_R(CString::Format(_T("Т_компенсаторов=%g\n"), Tz)));
	file.WriteString(CString::Format(_T("Нормаль=%s\n"),NormaDoc));
	file.WriteString(_R(CString::Format(_T("Ресурс_трубопровода=%g\n"), TimeWork)));
	file.WriteString(CString::Format(_T("Среда_испытаний=%s"), LPCTSTR(Envir.c_str())));
	file.WriteString(CString::Format(_T("Т_испытания=%g\n"), Ttest));
}

