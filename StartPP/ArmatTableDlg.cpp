// ArmatTableDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ArmatTableDlg.h"
#include "ArmatSet.h"


// CArmatTableDlg dialog

IMPLEMENT_DYNAMIC(CArmatTableDlg, CPipesTableDlg)

CArmatTableDlg::CArmatTableDlg(CWnd* pParent /*=nullptr*/)
	: CPipesTableDlg(CArmatTableDlg::IDD, pParent)
{
}

CArmatTableDlg::~CArmatTableDlg()
{
}

void CArmatTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CPipesTableDlg::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CArmatTableDlg, CPipesTableDlg)
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	//	ON_WM_CLOSE()
	ON_WM_DESTROY()
	END_MESSAGE_MAP()

CArmatSet set;
extern LPCTSTR LoadStr(UINT nID);

// CArmatTableDlg message handlers
BOOL CArmatTableDlg::OnInitDialog()
{
	SetWindowText(LoadStr(IDS_ARMAT_TABLE));
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
	SetHdr(LoadStr(IDS_AT_C1), 3);
	SetHdr(LoadStr(IDS_AT_ROTV), 4);
	SetHdr(LoadStr(IDS_AT_VESOTV), 5);
	SetHdr(LoadStr(IDS_AT_LZADV), 6);
	SetHdr(LoadStr(IDS_AT_VESZADV), 7);
	SetHdr(LoadStr(IDS_AT_NAGRMERT), 8);
	SetHdr(LoadStr(IDS_AT_NAGRSK), 9);
	set.m_strPath = _T(".");
	set.m_strTable = _T("[Armat] order by DIAM");
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
		SetFloat(set.m_NOTO, 2, row);
		SetFloat(set.m_RATO, 3, row);
		SetFloat(set.m_RAOT, 4, row);
		SetFloat(set.m_VESA, 5, row);
		SetFloat(set.m_RAOT1, 6, row);
		SetFloat(set.m_VESA1, 7, row);
		SetFloat(set.m_NAG1, 8, row);
		SetFloat(set.m_NAG2, 9, row);
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

void CArmatTableDlg::OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = reinterpret_cast<NM_GRIDVIEW*>(pNotifyStruct);
	CString str = m_Grid.GetCell(pItem->iRow, pItem->iColumn)->GetText();
	str.Replace(_T("."),_T(","));
	//CArmatSet set;
	//set.m_strPath=_T(".");
	//set.m_strTable.Format(_T("[Armat] order by DIAM"),
	//		m_Grid.GetCell(pItem->iRow, 1)->GetText());
	//set.Open();
	if (pItem->iRow == m_Grid.GetRowCount() - 1)
	{
		set.AddNew();
		set.m_DIAM = 0.0;
		set.m_NOTO = 0.0;
		set.m_RATO = 0.0;
		set.m_RAOT = 0.0;
		set.m_VESA = 0.0;
		set.m_RAOT1 = 0.0;
		set.m_VESA1 = 0.0;
		set.m_NAG1 = 0.0;
		set.m_NAG2 = 0.0;
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
		set.m_NOTO = float(_wtof(str));
		break;
	case 2:
		set.m_RATO = float(_wtof(str));
		break;
	case 3:
		set.m_RAOT = float(_wtof(str));
		break;
	case 4:
		set.m_VESA = float(_wtof(str));
		break;
	case 5:
		set.m_RAOT1 = float(_wtof(str));
		break;
	case 6:
		set.m_VESA1 = float(_wtof(str));
	case 7:
		set.m_NAG1 = float(_wtof(str));
		break;
	case 8:
		set.m_NAG2 = float(_wtof(str));
		break;
	}
	set.Update();
	//set.Close();
}

void CArmatTableDlg::OnTableDel()
{
	int nRow = m_Grid.GetFocusCell().row;
	if (AfxMessageBox(LoadStr(IDS_PT_DEL_LINE_Q), MB_YESNO) == IDYES)
	{
		//CArmatSet set;
		//set.m_strPath=_T(".");
		//set.m_strTable =_T("[Armat] order by DIAM");
		//set.Open();
		set.SetAbsolutePosition(nRow);
		m_Grid.DeleteRow(nRow);
		m_Grid.RedrawWindow();
		set.Delete();
		//set.Close();
	}
}

//void CArmatTableDlg::OnClose()
//{
//
//	CPipesTableDlg::OnClose();
//}


void CArmatTableDlg::OnDestroy()
{
	set.Close();
	CDialog::OnDestroy();
}

