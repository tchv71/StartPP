// PipeDescDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "PipeDescDialog.h"
#include "PipeDesc.h"
#include "Strings.h"

// диалоговое окно CPipeDescDialog

//IMPLEMENT_DYNAMIC(CPipeDescDialog, CPipeDescBaseDialog)

CPipeDescDialog::CPipeDescDialog(CPipeDesc& rPipeDesc, CWnd* pParent /*=nullptr*/)
	: CPipeDescBaseDialog(pParent), m_rPipeDesc(rPipeDesc)
{
	OnInitDialog();
}

CPipeDescDialog::~CPipeDescDialog()
{
}

//extern LPCTSTR LoadStr(UINT nID);

/*
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
		switch (m_cbIsp->GetSelection())
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
		m_cbStrings2.GetLBText(m_cbStrings2->GetSelection(), m_rPipeDesc.NormaSpring);
		if (m_cbStrings->GetSelection() == 0)
			m_rPipeDesc.NormaSpring = _T("");

		m_rPipeDesc.CalcStartComp = m_cbComp->GetSelection();
	}
}
*/
 
BEGIN_MESSAGE_MAP(CPipeDescDialog, CPipeDescBaseDialog)
	EVT_CHOICE(wxID_COMBO_ISP, CPipeDescDialog::OnLBIspChange)
	EVT_CHOICE(wxID_COMBO_STRINGS, CPipeDescDialog::OnCbnSelchangeComboStrings)
	EVT_CHOICE(wxID_COMBO_COMP, CPipeDescDialog::OnCbnSelchangeComboComp)
END_MESSAGE_MAP()


// обработчики сообщений CPipeDescDialog


BOOL CPipeDescDialog::OnInitDialog()
{
	//CDialog::OnInitDialog();
	//m_cbNormaDoc.AddString(LoadStr(IDS_PDD_RD_10_400_01_PDN));
	//m_cbNormaDoc.AddString(LoadStr(IDS_PDD_RD_10_400_01_PDK));
	//m_cbIsp.AddString(LoadStr(IDS_PDD_BY_WATER));
	//m_cbIsp.AddString(LoadStr(IDS_PDD_BY_AIR));
	//m_cbIsp.AddString(LoadStr(IDS_PDD_NO_PERFORM));
	wxDateTime date;
	wxString::const_iterator end;
	if (date.ParseFormat(m_rPipeDesc.Date,"%d.%m.%Y",&end))
		m_ctlDate->SetValue(date);
	m_textCtrlDesc->SetValue(m_rPipeDesc.Description);
	m_textCtrlTSet->SetValue(wxString::Format("%g",m_rPipeDesc.TSet));
	m_textCtrlTimeWork->SetValue(wxString::Format("%g",m_rPipeDesc.TimeWork));
	m_textCtrlTtest->SetValue(wxString::Format("%g",m_rPipeDesc.Ttest));
	m_textCtrlTz->SetValue(wxString::Format("%g",m_rPipeDesc.Tz));
	
	if (m_rPipeDesc.NormaDoc == LoadStr(IDS_PDD_RD_10_400_01_PDN))
		m_cbNormaDoc->SetSelection(1);
	else if(m_rPipeDesc.NormaDoc == LoadStr(IDS_PDD_RD_10_400_01_PDK))
		m_cbNormaDoc->SetSelection(0);
		
	if (m_rPipeDesc.Envir == LoadStr(IDS_PDD_WATER))
		m_cbIsp->SetSelection(0);
	else if (m_rPipeDesc.Envir == LoadStr(IDS_PDD_AIR))
		m_cbIsp->SetSelection(1);
	else
		m_cbIsp->SetSelection(2);
	wxCommandEvent event;
	OnLBIspChange(event);
	
	//m_cbStrings.AddString(LoadStr(IDS_PDD_NO_PERFORM));
	//m_cbStrings.AddString(LoadStr(IDS_PDD_PERFORM));
	m_cbStrings->SetSelection(m_rPipeDesc.NormaSpring.IsEmpty()? 0: 1);
	OnCbnSelchangeComboStrings(event);
	//m_cbComp.AddString(LoadStr(IDS_PDD_NO_PERFORM));
	//m_cbComp.AddString(LoadStr(IDS_PDD_PERFORM));
	m_cbComp->SetSelection(m_rPipeDesc.CalcStartComp);
	OnCbnSelchangeComboComp(event);
	//m_cbStrings2.AddString(LoadStr(IDS_NORMA_OST));
	//m_cbStrings2.AddString(LoadStr(IDS_NORMA_MVN));
	//m_cbStrings2.AddString(LoadStr(IDS_NORMA_MN));
	//m_cbStrings2.AddString(LoadStr(IDS_NORMA_OST24));
	//m_cbStrings2.AddString(LoadStr(IDS_NORMA_LISEGA));
	if (m_rPipeDesc.NormaSpring == LoadStr(IDS_NORMA_OST))
		m_cbStrings2->SetSelection(0);
	else if (m_rPipeDesc.NormaSpring == LoadStr(IDS_NORMA_MVN))
		m_cbStrings2->SetSelection(1);
	else if (m_rPipeDesc.NormaSpring == LoadStr(IDS_NORMA_MN))
		m_cbStrings2->SetSelection(2);
	else if (m_rPipeDesc.NormaSpring == LoadStr(IDS_NORMA_OST24))
		m_cbStrings2->SetSelection(3);
	else if (m_rPipeDesc.NormaSpring == LoadStr(IDS_NORMA_LISEGA))
		m_cbStrings2->SetSelection(4);
	else
		m_cbStrings2->SetSelection(0);


	//m_cbString3.AddString(LoadStr(IDS_WORK));
	//m_cbString3.AddString(LoadStr(IDS_COLD));
	m_cbStrings3->SetSelection(m_rPipeDesc.CondSelSpring);
	//COleDateTime tm;
	//if (tm.ParseDateTime(m_rPipeDesc.Date))
	//	m_ctlDate.SetTime(tm);
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CPipeDescDialog::OnLBIspChange(wxCommandEvent& event)
{
	if (m_cbIsp->GetSelection() == 2)
	{
		m_staticTextTest->Hide();//GetDlgItem(IDC_STATIC_T_ISP)->ShowWindow(SW_HIDE);
		m_textCtrlTtest->Hide();//GetDlgItem(IDC_EDIT_T_TEST)->ShowWindow(SW_HIDE);
		m_staticTextTtestGr->Hide();//GetDlgItem(IDC_STATIC13)->ShowWindow(SW_HIDE);
	}
	else
	{
		m_staticTextTest->Show();//GetDlgItem(IDC_STATIC_T_ISP)->ShowWindow(SW_NORMAL);
		m_textCtrlTtest->Show();//GetDlgItem(IDC_EDIT_T_TEST)->ShowWindow(SW_NORMAL);
		m_staticTextTtestGr->Show();//GetDlgItem(IDC_STATIC13)->ShowWindow(SW_NORMAL);
	}
	event.Skip();
}

void CPipeDescDialog::OnCbnSelchangeComboStrings(wxCommandEvent& event)
{
	if (m_cbStrings->GetSelection() == 0)
	{
		m_staticTextStrNorm->Hide();//GetDlgItem(IDC_STATIC18)->ShowWindow(SW_HIDE);
		m_cbStrings2->Hide();//GetDlgItem(IDC_COMBO_STRINGS2)->ShowWindow(SW_HIDE);
		m_staticTextStrCond->Hide();//GetDlgItem(IDC_STATIC19)->ShowWindow(SW_HIDE);
		m_cbStrings3->Hide();//GetDlgItem(IDC_COMBO_STRINGS3)->ShowWindow(SW_HIDE);
	}
	else
	{
		m_staticTextStrNorm->Show();//GetDlgItem(IDC_STATIC18)->ShowWindow(SW_NORMAL);
		m_cbStrings2->Show();//GetDlgItem(IDC_COMBO_STRINGS2)->ShowWindow(SW_NORMAL);
		m_staticTextStrCond->Show();//GetDlgItem(IDC_STATIC19)->ShowWindow(SW_NORMAL);
		m_cbStrings3->Show();//GetDlgItem(IDC_COMBO_STRINGS3)->ShowWindow(SW_NORMAL);
	}
	event.Skip();
}


void CPipeDescDialog::OnCbnSelchangeComboComp(wxCommandEvent& event)
{
	if (m_cbComp->GetSelection() == 0)
	{
		m_staticTextTz->Hide();//GetDlgItem(IDC_STATIC_T_Z)->ShowWindow(SW_HIDE);
		m_textCtrlTz->Hide();//GetDlgItem(IDC_EDIT_T_Z)->ShowWindow(SW_HIDE);
		m_staticTextTzGr->Hide();//GetDlgItem(IDC_STATIC14)->ShowWindow(SW_HIDE);
	}
	else
	{
		m_staticTextTz->Show();//GetDlgItem(IDC_STATIC_T_Z)->ShowWindow(SW_NORMAL);
		m_textCtrlTz->Show();//GetDlgItem(IDC_EDIT_T_Z)->ShowWindow(SW_NORMAL);
		m_staticTextTzGr->Show();//GetDlgItem(IDC_STATIC14)->ShowWindow(SW_NORMAL);
	}
	event.Skip();
}

bool CPipeDescDialog::OnOK() const
{
	m_rPipeDesc.Date = m_ctlDate->GetValue().Format("%d.%m.%Y");
	m_rPipeDesc.Description = m_textCtrlDesc->GetValue();
	double d;
	if (!m_textCtrlTSet->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(IDS_NUMBER_ERROR, wxOK | wxICON_ERROR);
		return false;
	}
	m_rPipeDesc.TSet = d;	
	if (!m_textCtrlTimeWork->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(IDS_NUMBER_ERROR, wxOK | wxICON_ERROR);
		return false;
	}
	m_rPipeDesc.TimeWork = d;
	if (!m_textCtrlTtest->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(IDS_NUMBER_ERROR, wxOK | wxICON_ERROR);
		return false;
	}
	m_rPipeDesc.Ttest = d;
	if (!m_textCtrlTz->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(IDS_NUMBER_ERROR, wxOK | wxICON_ERROR);
		return false;
	}
	m_rPipeDesc.Tz = d;
	m_rPipeDesc.NormaDoc = m_cbNormaDoc->GetString(m_cbNormaDoc->GetSelection());
	switch (m_cbIsp->GetSelection())
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
	default: ;
	}
	m_rPipeDesc.NormaSpring = m_cbStrings2->GetString(m_cbStrings2->GetSelection());
	m_rPipeDesc.CondSelSpring = m_cbStrings3->GetSelection();

	if (m_cbStrings->GetSelection() == 0)
		m_rPipeDesc.NormaSpring = _T("");

	m_rPipeDesc.CalcStartComp = m_cbComp->GetSelection();

	return true;
}


void CPipeDescDialog::EndModal(int retcode)
{
    if (retcode == wxID_OK)
	{
		if (!OnOK())
			return;
	}
	CPipeDescBaseDialog::EndModal(retcode);
}
