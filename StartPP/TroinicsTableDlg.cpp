// TroinicsTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StartPP.h"
#include "TroinicsTableDlg.h"
#include "TroinicsSet.h"

extern LPCTSTR LoadStr(UINT nID);

// CTroinicsTableDlg dialog

IMPLEMENT_DYNAMIC(CTroinicsTableDlg, CPipesTableDlg)

CTroinicsTableDlg::CTroinicsTableDlg(CWnd* pParent /*=nullptr*/)
	: CPipesTableDlg(pParent)
{
}

CTroinicsTableDlg::~CTroinicsTableDlg()
{
}

void CTroinicsTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CPipesTableDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTroinicsTableDlg, CPipesTableDlg)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_WM_DESTROY()
	END_MESSAGE_MAP()

CTroinicsSet set;

// CTroinicsTableDlg message handlers
BOOL CTroinicsTableDlg::OnInitDialog()
{
	SetWindowText(LoadStr(IDS_TR_TABLE));
	CDialog::OnInitDialog();
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetColumnCount(set.m_nFields + 1);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetFixedColumnSelection(TRUE);
	m_Grid.SetListMode(TRUE);
	m_Grid.EnableSelection(FALSE);
	//m_Grid.SetFixedColumnCount(1);
	SetHdr(LoadStr(IDS_AT_DIAM), 1);
	SetHdr(LoadStr(IDS_AT_S), 2);
	SetHdr(LoadStr(IDS_C), 3);
	SetHdr(LoadStr(IDS_DIAM_SHT), 4);
	SetHdr(LoadStr(IDS_S_SHT), 5);
	SetHdr(LoadStr(IDS_C_SHT), 6);
	SetHdr(LoadStr(IDS_VYS_SHT), 7);
	SetHdr(LoadStr(IDS_SHIR_NAKL), 8);
	SetHdr(LoadStr(IDS_TOLSCH_NAKL), 9);
	SetHdr(LoadStr(IDS_VES_TR), 10);
	SetHdr(LoadStr(IDS_KORPUS), 11);
	set.m_strPath = _T(".");
	set.m_strTable = _T("[Troinics] order by DIAM,DIAMSH");
	if (!set.Open())
		AfxMessageBox(_T("Can't open Pipes.mdb"));
	int nRowCount = 0;
	while (!set.IsEOF())
	{
		nRowCount++;
		set.MoveNext();
	}
	m_Grid.SetRowCount(nRowCount + 2);
	m_Grid.SetRowHeight(nRowCount + 1, 1);
	//m_Grid.SetEditable(false);
	set.Close();
	set.Open();
	for (int row = 1; row < m_Grid.GetRowCount() - 1; row++)
	{
		CString str;
		SetFloat(set.m_DIAM, 1, row);
		SetFloat(set.m_NTSTM, 2, row);
		SetFloat(set.m_RTSTM, 3, row);
		SetFloat(set.m_DIAMSH, 4, row);
		SetFloat(set.m_NTSTSH, 5, row);
		SetFloat(set.m_RTSTSH, 6, row);
		SetFloat(float(set.m_VIS_SHTU), 7, row);
		SetFloat(set.m_WIDTHNAK, 8, row);
		SetFloat(set.m_THINKNAK, 9, row);
		SetFloat(set.m_VES, 10, row);
		SetFloat(float(set.m_KORPUS), 11, row);
		set.MoveNext();
	}
	//set.Close();
	CRect rect;
	GetClientRect(rect);
	m_OldSize = CSize(rect.Width(), rect.Height());
	SetHdr(CString(_T("*")), 0, nRowCount + 1);


	m_Grid.AutoSize();
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CTroinicsTableDlg::OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = reinterpret_cast<NM_GRIDVIEW*>(pNotifyStruct);
	CString str = m_Grid.GetCell(pItem->iRow, pItem->iColumn)->GetText();
	str.Replace(_T("."),_T(","));
	//CTroinicsSet set;
	//set.m_strPath=_T(".");
	//set.m_strTable.Format(_T("[Troinics] WHERE DIAM = %s AND DIAMSH = %s order by DIAMSH,DIAM"),
	//		m_Grid.GetItemText(pItem->iRow,1),m_Grid.GetItemText(pItem->iRow,4));
	//set.Open();
	if (pItem->iRow == m_Grid.GetRowCount() - 1)
	{
		set.AddNew();
		set.m_DIAM = 0.0;
		set.m_DIAMSH = 0.0;
		set.m_NTSTM = 0.0;
		set.m_RTSTM = 0.0;
		set.m_NTSTSH = 0.0;
		set.m_RTSTSH = 0.0;
		set.m_WIDTHNAK = 0.0;
		set.m_THINKNAK = 0.0;
		set.m_VES = 0.0;
		set.m_VIS_SHTU = 0;
		set.m_KORPUS = 0;
		SetHdr(CString(_T("")), 0, m_Grid.GetRowCount() - 1);
		m_Grid.SetRowCount(m_Grid.GetRowCount() + 1);
		SetHdr(CString(_T("*")), 0, m_Grid.GetRowCount() - 1);
	}
	else
	{
		set.SetAbsolutePosition(pItem->iRow);
		set.Edit();
	}
	switch (pItem->iColumn - 1)
	{
	case 0:
		set.m_DIAM = float(_wtof(str));
		break;
	case 1:
		set.m_NTSTM = float(_wtof(str));
		break;
	case 2:
		set.m_RTSTM = float(_wtof(str));
		break;
	case 3:
		set.m_DIAMSH = float(_wtof(str));
		break;
	case 4:
		set.m_NTSTSH = float(_wtof(str));
		break;
	case 5:
		set.m_RTSTSH = float(_wtof(str));
		break;
	case 6:
		set.m_VIS_SHTU = _wtoi(str);
	case 7:
		set.m_WIDTHNAK = float(_wtof(str));
		break;
	case 8:
		set.m_THINKNAK = float(_wtof(str));
		break;
	case 9:
		set.m_VES = float(_wtof(str));
		break;
	case 10:
		set.m_KORPUS = _wtoi(str);
		break;
	}
	set.Update();
	//set.Close();
}

void CTroinicsTableDlg::OnTableDel()
{
	int nRow = m_Grid.GetFocusCell().row;
	if (AfxMessageBox(LoadStr(IDS_PT_DEL_LINE_Q), MB_YESNO) == IDYES)
	{
		//CTroinicsSet set;
		//set.m_strPath=_T(".");
		//set.m_strTable.Format(_T("[Troinics] WHERE DIAM = %s AND DIAMSH = %s") ,
		//	m_Grid.GetCell(nRow,1)->GetText(),m_Grid.GetCell(nRow,4)->GetText());
		//set.Open();
		set.SetAbsolutePosition(nRow);
		m_Grid.DeleteRow(nRow);
		set.Delete();
		//set.Close();
	}
}


void CTroinicsTableDlg::OnDestroy()
{
	set.Close();
	CDialog::OnDestroy();
}

