// CopyParamsDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "Strings.h"
#include "CopyParamsDialog.h"
#include <math.h>

const struct Param
{
	const TCHAR * Name;
	//UINT idName;
	const char* Field;
	bool Podzem;
} Params[] = {
	{IDS_F_DIAM,"DIAM",0},
	{IDS_F_NAMA,"NAMA",0},
	{IDS_F_NTOS,"NTOS",0},
	{IDS_F_RTOS,"RTOS",0},
	{IDS_F_VETR,"VETR",0},
	{IDS_F_VEIZ,"VEIZ",0},
	{IDS_F_VEPR,"VEPR",0},
	{IDS_F_RADA,"RADA",0},
	{IDS_F_DABI,"DABI",0},
	{IDS_F_DIAM_KOZH,"NAGX",1},
	{IDS_F_VIZA,"VIZA",1},
	{IDS_F_VIZA2,"VIZA2",1},
	{IDS_F_SHTR,"SHTR",1},
	{IDS_F_PELI,"PELI",0},
	{IDS_F_PEUG,"PEYG",0},
	{IDS_F_LEN,"LEN",0},
	{IDS_F_APROF,"APROF",0},
	{0,nullptr,0}};

// диалоговое окно CCopyParamsDialog

//extern LPCTSTR LoadStr(UINT nID);

CCopyParamsDialog::CCopyParamsDialog(CWnd* pParent, CPipes& pipes)
	: CCopyParamsBaseDialog(pParent), m_pipes(pipes)
{
	OnInitDialog();
}

CCopyParamsDialog::~CCopyParamsDialog()
{
}

/*
void CCopyParamsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PARAMS, m_lbParams);
	DDX_Control(pDX, IDC_PIPES, m_lbPipes);
	DDX_Control(pDX, IDC_PIPE_NAME, m_sPipeName);
}
*/




// обработчики сообщений CCopyParamsDialog


BOOL CCopyParamsDialog::OnInitDialog()
{
	//CDialog::OnInitDialog();
	m_pipes.FillLb1(m_lbPipes);
	for (int i = 0; Params[i].Name != 0; i++)
		m_lbParams->Append(LoadStr(Params[i].Name));
	CString str = CString::Format(_T("%g - %g"), m_pipes.m_vecPnN[m_pipes.m_nIdx].m_NAYZ, m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ);
	m_sPipeName->SetLabelText(str);
	return TRUE; // return TRUE unless you set the focus to a control
}


void CCopyParamsDialog::OnOK()
{
	//CDialog::OnOK();
	for (size_t i = 0; i < m_lbPipes->GetCount(); i++)
		if (m_lbPipes->IsSelected(i))
		{
			float n = m_pipes.m_vecPnN[i].m_NAGV,
				n1 = m_pipes.m_vecPnN[m_pipes.m_nIdx].m_NAGV;
			for (size_t j = 0; j < m_lbParams->GetCount(); j++)
				if (m_lbParams->IsSelected(j) &&
					((!Params[j].Podzem) || (n < 0 && n1 < 0)))
				{
					const char* v = Params[j].Field;
					CPipeAndNode& Dest = m_pipes.m_vecPnN[i];
					CPipeAndNode& Src = m_pipes.m_vecPnN[m_pipes.m_nIdx];
					if (strcmp(v, "PELI") == 0 || strcmp(v, "PEYG") == 0)
					{
						wxString v1 = Dest.m_MNEA;
						if (!(v1==STR_OS || v1 == STR_OI || v1 == STR_OF))
						{
							if (strcmp(v, "PELI") == 0)
								Dest.m_PELI = Src.m_PELI;
							else
								Dest.m_PEYG = Src.m_PEYG;
						}
					}
					else if (strcmp(v, "NAMA") == 0)
					{
						wxString v1 = Dest.m_MNEA;
						Dest.m_NAMA = Src.m_NAMA;
						if (v1==STR_OS || v1 == STR_OI || v1 == STR_OF)
							Dest.m_MARI = Src.m_NAMA;
					}
					else if (strcmp(v, "LEN") == 0)
					{
						float dx = Src.m_OSIX,
							dy = Src.m_OSIY,
							dz = Src.m_OSIZ,
							Len = sqrt(dx * dx + dy * dy + dz * dz),
							dx1 = Dest.m_OSIX,
							dy1 = Dest.m_OSIY,
							dz1 = Dest.m_OSIZ,
							DestLen = sqrt(dx1 * dx1 + dy1 * dy1 + dz1 * dz1);
						if (fabs(DestLen) >= 0.001)
						{
							Dest.m_OSIX = dx1 * Len / DestLen;
							Dest.m_OSIY = dy1 * Len / DestLen;
							Dest.m_OSIZ = dz1 * Len / DestLen;
						}
					}
					else if (strcmp(v, "APROF") == 0)
					{
						float dx = Src.m_OSIX;
						float dy = Src.m_OSIY;
						float dz = Src.m_OSIZ;
						float LenPlan = sqrt(dx * dx + dy * dy);
						float dx1 = Dest.m_OSIX;
						float dy1 = Dest.m_OSIY;
						float DestLenPlan = sqrt(dx1 * dx1 + dy1 * dy1);
						if (fabs(LenPlan) >= 0.001)
						{
							Dest.m_OSIZ = dz * DestLenPlan / LenPlan;
						}
					}
					else if (strcmp(v, "DIAM") == 0)
						Dest.m_DIAM = Src.m_DIAM;
					else if (strcmp(v, "NTOS") == 0)
						Dest.m_NTOS = Src.m_NTOS;
					else if (strcmp(v, "RTOS") == 0)
						Dest.m_RTOS = Src.m_RTOS;
					else if (strcmp(v, "VETR") == 0)
						Dest.m_VETR = Src.m_VETR;
					else if (strcmp(v, "VEIZ") == 0)
						Dest.m_VEIZ = Src.m_VEIZ;
					else if (strcmp(v, "VEPR") == 0)
						Dest.m_VEPR = Src.m_VEPR;
					else if (strcmp(v, "RADA") == 0)
						Dest.m_RADA = Src.m_RADA;
					else if (strcmp(v, "DABI") == 0)
						Dest.m_DABI = Src.m_DABI;
					else if (strcmp(v, "RATE") == 0)
						Dest.m_RATE = Src.m_RATE;
					else if (strcmp(v, "NAGX") == 0)
						Dest.m_NAGX = Src.m_NAGX;
					else if (strcmp(v, "VIZA") == 0)
					{
						Dest.m_VIZA = Src.m_VIZA;
						Dest.m_VIZA2 = Src.m_VIZA2;
						Dest.m_OS_TR1 = Src.m_OS_TR1;
						Dest.m_OS_TR2 = Src.m_OS_TR2;
					}
					else if (strcmp(v, "SHTR") == 0)
						Dest.m_SHTR = Src.m_SHTR;
				};
		};
}


void CCopyParamsDialog::EndModal(int retcode)
{
    if (retcode == wxID_OK)
        OnOK();
    CCopyParamsBaseDialog::EndModal(retcode);
}
