// PipeDescDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "PipeDescDialog.h"
#include "PipeDesc.h"


// диалоговое окно CPipeDescDialog

IMPLEMENT_DYNAMIC(CPipeDescDialog, CDialog)

CPipeDescDialog::CPipeDescDialog(CPipeDesc& rPipeDesc, CWnd* pParent /*=nullptr*/)
	: CDialog(CPipeDescDialog::IDD, pParent), m_rPipeDesc(rPipeDesc)
{
}

CPipeDescDialog::~CPipeDescDialog()
{
}

extern LPCTSTR LoadStr(UINT nID);


void CPipeDescDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATETIMEPICKER1, m_rPipeDesc.Date);
	DDX_Text(pDX, IDC_EDIT_DESC, m_rPipeDesc.Description);
	DDX_Text(pDX, IDC_EDIT_T_SET, m_rPipeDesc.TSet);
	DDX_Text(pDX, IDC_EDIT_TIME_WORK, m_rPipeDesc.TimeWork);
	DDX_Text(pDX, IDC_EDIT_T_TEST, m_rPipeDesc.Ttest);
	DDX_Text(pDX, IDC_EDIT_T_Z, m_rPipeDesc.Tz);
	DDX_Control(pDX, IDC_COMBO_NORMA_DOC, m_cbNormaDoc);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctlDate);
	DDX_Control(pDX, IDC_COMBO_STRINGS, m_cbStrings);
	DDX_Control(pDX, IDC_COMBO_ISP, m_cbIsp);
	DDX_Control(pDX, IDC_COMBO_COMP, m_cbComp);
	DDX_Control(pDX, IDC_COMBO_STRINGS2, m_cbStrings2);
	DDX_Control(pDX, IDC_COMBO_STRINGS3, m_cbString3);
	if (pDX->m_bSaveAndValidate)
	{
		switch (m_cbIsp.GetCurSel())
		{
		case 0:
			m_rPipeDesc.Envir = LoadStr(IDS_PDD_WATER);
			break;
		case 1:
			m_rPipeDesc.Envir = LoadStr(IDS_PDD_AIR);
			break;
		case 2:
			m_rPipeDesc.Envir = LoadStr(IDS_PDD_NO_PERFORM);
			break;
		}
		m_cbStrings2.GetLBText(m_cbStrings2.GetCurSel(), m_rPipeDesc.NormaSpring);
		if (m_cbStrings.GetCurSel() == 0)
			m_rPipeDesc.NormaSpring = _T("");

		m_rPipeDesc.CalcStartComp = m_cbComp.GetCurSel();
	}
}

BEGIN_MESSAGE_MAP(CPipeDescDialog, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_ISP,OnLBIspChange)
	ON_CBN_SELCHANGE(IDC_COMBO_STRINGS, &CPipeDescDialog::OnCbnSelchangeComboStrings)
	ON_CBN_SELCHANGE(IDC_COMBO_COMP, &CPipeDescDialog::OnCbnSelchangeComboComp)
	END_MESSAGE_MAP()


// обработчики сообщений CPipeDescDialog


BOOL CPipeDescDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_cbNormaDoc.AddString(LoadStr(IDS_PDD_RD_10_400_01_PDN));
	m_cbNormaDoc.AddString(LoadStr(IDS_PDD_RD_10_400_01_PDK));
	m_cbIsp.AddString(LoadStr(IDS_PDD_BY_WATER));
	m_cbIsp.AddString(LoadStr(IDS_PDD_BY_AIR));
	m_cbIsp.AddString(LoadStr(IDS_PDD_NO_PERFORM));
	m_cbNormaDoc.SetCurSel(0);
	if (m_rPipeDesc.Envir == LoadStr(IDS_PDD_WATER))
		m_cbIsp.SetCurSel(0);
	else if (m_rPipeDesc.Envir == LoadStr(IDS_PDD_AIR))
		m_cbIsp.SetCurSel(1);
	else
		m_cbIsp.SetCurSel(2);
	OnLBIspChange();
	m_cbStrings.AddString(LoadStr(IDS_PDD_NO_PERFORM));
	m_cbStrings.AddString(LoadStr(IDS_PDD_PERFORM));
	m_cbStrings.SetCurSel(!m_rPipeDesc.NormaSpring.IsEmpty());
	OnCbnSelchangeComboStrings();
	m_cbComp.AddString(LoadStr(IDS_PDD_NO_PERFORM));
	m_cbComp.AddString(LoadStr(IDS_PDD_PERFORM));
	m_cbComp.SetCurSel(m_rPipeDesc.CalcStartComp);
	OnCbnSelchangeComboComp();
	m_cbStrings2.AddString(LoadStr(IDS_NORMA_OST));
	m_cbStrings2.AddString(LoadStr(IDS_NORMA_MVN));
	m_cbStrings2.AddString(LoadStr(IDS_NORMA_MN));
	m_cbStrings2.AddString(LoadStr(IDS_NORMA_OST24));
	m_cbStrings2.AddString(LoadStr(IDS_NORMA_LISEGA));
	m_cbStrings2.SetCurSel(0);

	m_cbString3.AddString(LoadStr(IDS_WORK));
	m_cbString3.AddString(LoadStr(IDS_COLD));
	m_cbString3.SetCurSel(m_rPipeDesc.CondSelSpring);
	COleDateTime tm;
	if (tm.ParseDateTime(m_rPipeDesc.Date))
		m_ctlDate.SetTime(tm);
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CPipeDescDialog::OnLBIspChange(void)
{
	if (m_cbIsp.GetCurSel() == 2)
	{
		GetDlgItem(IDC_STATIC_T_ISP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_T_TEST)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC13)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_T_ISP)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_EDIT_T_TEST)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STATIC13)->ShowWindow(SW_NORMAL);
	}
}

void CPipeDescDialog::OnCbnSelchangeComboStrings()
{
	if (m_cbStrings.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STATIC18)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_STRINGS2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC19)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO_STRINGS3)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC18)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_COMBO_STRINGS2)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STATIC19)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_COMBO_STRINGS3)->ShowWindow(SW_NORMAL);
	}
}


void CPipeDescDialog::OnCbnSelchangeComboComp()
{
	if (m_cbComp.GetCurSel() == 0)
	{
		GetDlgItem(IDC_STATIC_T_Z)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_T_Z)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC14)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_T_Z)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_EDIT_T_Z)->ShowWindow(SW_NORMAL);
		GetDlgItem(IDC_STATIC14)->ShowWindow(SW_NORMAL);
	}
}

