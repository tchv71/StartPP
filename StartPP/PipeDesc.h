#pragma once
class CPipeDesc
{
public:
	CPipeDesc(void);
	~CPipeDesc(void);
	CString Date; //Дата расчета в формате (ДД.ММ.ГГГГ)
	CString Description; //№ объекта по терминологии ПС СТАРТ (строка)
	CString NormaDoc; // Параметр нормативного документа
	float TSet; // Температура монтажа (гр. С)
	float Tcold; // Температура после охлаждения (гр. С) 
	int CalcStartComp; // Признак расчета стартовых компенсаторов
	//0 – расчет стартовых компенсаторов не проводить, 1 - проводить
	float Tz; // Температура заварки стартовых компенсаторов (гр. С) 
	float TimeWork; // Расчетный срок службы трубопровода (годы) 
	CString Envir; // Среда испытаний трубопровода 
	float Ttest; // Температура испытания (гр.С)  
	CString NormaSpring; // Нормаль для подбора пружин 
	int CondSelSpring; //  Состояние трубопровода при подборе пружин (холодное\рабочее)
	//0 – рабочее 1 - холодное  
	void Serialize(CArchive& ar);
	void WriteIni(CStdioFile& file);
};

