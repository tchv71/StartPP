// DelPipesDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "Strings.h"
#include "DelPipesDialog.h"


// диалоговое окно CDelPipesDialog

//IMPLEMENT_DYNAMIC(CDelPipesDialog, CDialog)

CDelPipesDialog::CDelPipesDialog(CWnd* pParent /*=nullptr*/, CStartPPDoc* pDoc)
	: CDelPipesBaseDialog(pParent), m_pDoc(pDoc)
{
    OnInitDialog();
}

CDelPipesDialog::~CDelPipesDialog()
{
}


BEGIN_MESSAGE_MAP(CDelPipesDialog, CDelPipesBaseDialog)
END_MESSAGE_MAP()


// обработчики сообщений CDelPipesDialog

//xtern LPCTSTR LoadStr(UINT nID);

BOOL CDelPipesDialog::OnInitDialog()
{
	//CDialog::OnInitDialog();
	int nFirstSelection = -1;
	std::vector<CPipeAndNode>& m_vecPnN = m_pDoc->m_pipes.m_vecPnN;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CString str = CString::Format(_T("%g - %g"), m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ);
		m_listBox->Append(str);
		m_listBox->SetClientData(i, (void*)((size_t(m_vecPnN[i].m_NAYZ) << 16 )| size_t(m_vecPnN[i].m_KOYZ)));
		if (m_pDoc->vecSel.Contains(m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ))
		{
			if (nFirstSelection<0)
				nFirstSelection = i;
			m_listBox->Select(i);
		}
	}
	if (nFirstSelection>=0)
		m_listBox->EnsureVisible(nFirstSelection);
	
	return TRUE; 
}

//extern LPCTSTR LoadString(UINT nID);

void CDelPipesDialog::OnOK()
{
	//CDialog::OnOK();
    wxArrayInt arr;
    m_listBox->GetSelections(arr);
	CString str =  CString::Format(LoadStr(IDS_DEL_PIPES_Q), (int)arr.GetCount());
	if (AfxMessageBox(str, wxYES_NO | wxICON_QUESTION) == wxYES)
	{
		m_pDoc->vecSel.clear();
		for (size_t i = 0; i < m_listBox->GetCount(); i++)
			if (m_listBox->IsSelected(i))
			{
				DWORD_PTR dw =  (DWORD_PTR)m_listBox->GetClientData(i);
				int NAYZ = dw >> 16, KOYZ = dw & 0xFFFF;
				m_pDoc->vecSel.insert(SelStr(NAYZ, KOYZ));
			}
		if (!m_pDoc->IsSelConnected())
		{
			AfxMessageBox(IDS_PARTS_NOT_CONNECTED, wxOK | wxICON_EXCLAMATION);
			return;
		}
		m_pDoc->DeleteSelected();
	}
}

void CDelPipesDialog::EndModal(int retcode)
{
    if (retcode == wxID_OK)
        OnOK();
    CDelPipesBaseDialog::EndModal(retcode);
}
