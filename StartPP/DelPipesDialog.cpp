// DelPipesDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "DelPipesDialog.h"


// диалоговое окно CDelPipesDialog

IMPLEMENT_DYNAMIC(CDelPipesDialog, CDialog)

CDelPipesDialog::CDelPipesDialog(CWnd* pParent /*=nullptr*/, CStartPPDoc* pDoc)
	: CDialog(CDelPipesDialog::IDD, pParent), m_pDoc(pDoc)
{
}

CDelPipesDialog::~CDelPipesDialog()
{
}

void CDelPipesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}


BEGIN_MESSAGE_MAP(CDelPipesDialog, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CDelPipesDialog::OnLbnSelchangeList1)
	END_MESSAGE_MAP()


// обработчики сообщений CDelPipesDialog

extern LPCTSTR LoadStr(UINT nID);

BOOL CDelPipesDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	std::vector<CPipeAndNode>& m_vecPnN = m_pDoc->m_pipes.m_vecPnN;
	for (unsigned i = 0; i < m_vecPnN.size(); i++)
	{
		CString str;
		str.Format(_T("%g - %g"), m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ);
		m_listbox.AddString(str);
		m_listbox.SetItemData(i, MAKELPARAM(int(m_vecPnN[i].m_NAYZ),int(m_vecPnN[i].m_KOYZ)));
		if (m_pDoc->vecSel.Contains(m_vecPnN[i].m_NAYZ, m_vecPnN[i].m_KOYZ))
			m_listbox.SetSel(i);
	}
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}


void CDelPipesDialog::OnLbnSelchangeList1()
{
	// TODO: добавьте свой код обработчика уведомлений
}

extern LPCTSTR LoadString(UINT nID);

void CDelPipesDialog::OnOK()
{
	// TODO: добавьте специализированный код или вызов базового класса

	CDialog::OnOK();
	CString str;
	str.Format(LoadStr(IDS_DEL_PIPES_Q), m_listbox.GetSelCount());
	if (AfxMessageBox(str, MB_YESNO) == IDYES)
	{
		m_pDoc->vecSel.clear();
		for (int i = 0; i < m_listbox.GetCount(); i++)
			if (m_listbox.GetSel(i))
			{
				DWORD_PTR dw = m_listbox.GetItemData(i);
				int NAYZ = LOWORD(dw), KOYZ = HIWORD(dw);
				m_pDoc->vecSel.insert(SelStr(NAYZ, KOYZ));
			}
		if (!m_pDoc->IsSelConnected())
		{
			AfxMessageBox(IDS_PARTS_NOT_CONNECTED, MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		m_pDoc->DeleteSelected();
	}
}

