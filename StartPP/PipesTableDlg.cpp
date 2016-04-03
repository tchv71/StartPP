// PipesTableDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "PipesTableDlg.h"
#include "PipesSet.h"
#include "GridCtrl_src/GridCellCombo.h"
#include "Material.h"


// диалоговое окно CPipesTableDlg

IMPLEMENT_DYNAMIC(CPipesTableDlg, CDialog)

CPipesTableDlg::CPipesTableDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(CPipesTableDlg::IDD, pParent)
{
}

CPipesTableDlg::CPipesTableDlg(UINT nIDD, CWnd* pParent /*=nullptr*/)
	: CDialog(nIDD, pParent)
{
}

CPipesTableDlg::~CPipesTableDlg()
{
}

void CPipesTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST1, m_lbTable);
	//DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_GRID, m_Grid); // associate the grid window with a C++ object
}


BEGIN_MESSAGE_MAP(CPipesTableDlg, CDialog)
	//	ON_LBN_SELCHANGE(IDC_LIST1, &CPipesTableDlg::OnLbnSelchangeList1)
	//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CPipesTableDlg::OnTvnSelchangedTree1)
	ON_WM_SIZE()
	ON_NOTIFY(GVN_ENDLABELEDIT, IDC_GRID, OnGridEndEdit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TABLE_DEL, &CPipesTableDlg::OnTableDel)

	ON_WM_DESTROY()
	//	ON_WM_WINDOWPOSCHANGING()
	ON_WM_GETMINMAXINFO()
	END_MESSAGE_MAP()


// обработчики сообщений CPipesTableDlg


//void CPipesTableDlg::OnLbnSelchangeList1()
//{
//	// TODO: добавьте свой код обработчика уведомлений
//}

CPipesSet set;

extern LPCTSTR LoadStr(UINT nID);

BOOL CPipesTableDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Grid.SetFixedRowCount(1);
	m_Grid.SetFixedColumnCount(1);
	m_Grid.SetFixedColumnSelection(TRUE);
	m_Grid.SetListMode(TRUE);

	m_Grid.SetColumnCount(set.m_nFields + 1);
	m_Grid.EnableSelection(FALSE);
	//m_Grid.SetFixedColumnCount(1);
	SetHdr(LoadStr(IDS_AT_DIAM), 1);
	SetHdr(LoadStr(IDS_AT_S), 2);
	SetHdr(LoadStr(IDS_AT_C1), 3);
	SetHdr(LoadStr(IDS_PT_MAT), 4);
	SetHdr(LoadStr(IDS_PT_QTR), 5);
	SetHdr(LoadStr(IDS_PT_QI), 6);
	SetHdr(LoadStr(IDS_PT_QP), 7);
	SetHdr(LoadStr(IDS_PT_DIZ), 8);
	SetHdr(LoadStr(IDS_PT_ROTV), 9);
	SetHdr(LoadStr(IDS_PT_VESARM), 10);
	SetHdr(LoadStr(IDS_PT_MATOTV), 11);
	SetHdr(LoadStr(IDS_PT_SOTV), 12);
	SetHdr(LoadStr(IDS_PT_C1OTV), 13);
	SetHdr(LoadStr(IDS_PT_SEFF), 14);
	SetHdr(LoadStr(IDS_PT_KPOD), 15);
	SetHdr(LoadStr(IDS_PT_SHTR), 16);
	SetHdr(LoadStr(IDS_PT_PIPE_TYPE), 17);
	SetHdr(LoadStr(IDS_PT_SIZ), 18);
	set.m_strPath = _T(".");
	set.m_strTable = _T("[Pipes] order by PODZ, DIAM");
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
		SetFloat(set.m_NTOS, 2, row);
		SetFloat(set.m_RTOS, 3, row);
		m_Grid.SetCellType(row, 4, RUNTIME_CLASS(CGridCellCombo));
		str = set.m_NAMA;
		SetMaterial(str, 4, row);
		SetFloat(set.m_VETR, 5, row);
		SetFloat(set.m_VEIZ, 6, row);
		SetFloat(set.m_VEPR, 7, row);
		SetFloat(set.m_DIIZ, 8, row);
		SetFloat(set.m_RAOT, 9, row);
		SetFloat(set.m_VESA, 10, row);
		m_Grid.SetCellType(row, 11, RUNTIME_CLASS(CGridCellCombo));
		str = set.m_MARI;
		SetMaterial(str, 11, row);
		SetFloat(set.m_NOTO, 12, row);
		SetFloat(set.m_RATO, 13, row);
		SetFloat(set.m_SEFF, 14, row);
		SetFloat(set.m_KPOD, 15, row);
		SetFloat(set.m_SHTR, 16, row);
		m_Grid.SetCellType(row, 17, RUNTIME_CLASS(CGridCellCombo));
		CStringArray ar;
		ar.Add(LoadStr(IDS_PT_NADZ));
		ar.Add(LoadStr(IDS_PT_PODZ));
		CGridCellCombo* pCombo = dynamic_cast<CGridCellCombo*>(m_Grid.GetCell(row, 17));
		pCombo->SetOptions(ar);
		pCombo->SetStyle(CBS_DROPDOWNLIST);

		SetHdr(LoadStr(set.m_PODZ ? IDS_PT_PODZ : IDS_PT_NADZ), 17, row);
		if (set.m_PODZ)
			SetFloat(set.m_IZTO, 18, row);
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


BOOL CALLBACK EnumProc(HWND hwnd, LPARAM lParam)
{
	CWnd* pWnd = CWnd::FromHandle(hwnd);
	CSize* pTranslate = reinterpret_cast<CSize*>(lParam);

	CPipesTableDlg* pDlg = static_cast<CPipesTableDlg*>(pWnd->GetParent());
	if (!pDlg) return FALSE;

	CRect rect;
	pWnd->GetWindowRect(rect);
	//if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	//	TRACE(_T("Wnd rect: %d,%d - %d,%d\n"),rect.left,rect.top, rect.right, rect.bottom);

	pDlg->ScreenToClient(rect);
	//if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	//	TRACE(_T("Scr rect: %d,%d - %d,%d\n"),rect.left,rect.top, rect.right, rect.bottom);

	if (hwnd == pDlg->m_Grid.GetSafeHwnd())
	{
		if (((rect.top >= 7 && pTranslate->cy > 0) || rect.Height() > 20) &&
			((rect.left >= 7 && pTranslate->cx > 0) || rect.Width() > 20))
			pWnd->MoveWindow(rect.left, rect.top,
			                 rect.Width() + pTranslate->cx,
			                 rect.Height() + pTranslate->cy, FALSE);
		else
			pWnd->MoveWindow(rect.left + pTranslate->cx, rect.top + pTranslate->cy,
			                 rect.Width(), rect.Height(), FALSE);
	}
	else
	{
		//if (  ((rect.top >= 7 && pTranslate->cy > 0) || rect.Height() > 20) &&
		//	  ((rect.left >= 7 && pTranslate->cx > 0) || rect.Width() > 20)   )
		//	pWnd->MoveWindow(rect.left+pTranslate->cx, rect.top+pTranslate->cy, 
		//					 rect.Width(), 
		//					 rect.Height(), FALSE);
		//else
		pWnd->MoveWindow(rect.left + pTranslate->cx, rect.top + pTranslate->cy,
		                 rect.Width(), rect.Height(), FALSE);
	}
	pDlg->Invalidate();

	return TRUE;
}

void CPipesTableDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CSize Translate(cx - m_OldSize.cx, cy - m_OldSize.cy);
	::EnumChildWindows(GetSafeHwnd(), EnumProc, LPARAM(&Translate));
	m_OldSize = CSize(cx, cy);
}


void CPipesTableDlg::SetHdr(CString str, int pos, int row)
{
	GV_ITEM Item;

	Item.mask = GVIF_TEXT;
	Item.row = row;
	Item.col = pos;
	Item.strText = str;
	m_Grid.SetItem(&Item);
}

void CPipesTableDlg::SetMaterial(CString str, int pos, int row)
{
	CMaterial set;
	set.m_strPath = _T(".");
	set.m_strTable = _T("[MATUP]  order by NOM");
	set.Open();
	CStringArray ar;
	while (!set.IsEOF())
	{
		ar.Add(CString(set.m_MAT));
		set.MoveNext();
	}
	CGridCellCombo* pCombo = dynamic_cast<CGridCellCombo*>(m_Grid.GetCell(row, pos));
	pCombo->SetOptions(ar);
	pCombo->SetStyle(CBS_DROPDOWNLIST);
	set.Close();
	GV_ITEM Item;

	Item.mask = GVIF_TEXT;
	Item.row = row;
	Item.col = pos;
	Item.strText = str;
	m_Grid.SetItem(&Item);
}

void CPipesTableDlg::SetFloat(float val, int pos, int row)
{
	GV_ITEM Item;
	CString str;
	str.Format(_T("%g"), val);
	Item.mask = GVIF_TEXT;
	Item.row = row;
	Item.col = pos;
	Item.strText = str;
	m_Grid.SetItem(&Item);
}

void CPipesTableDlg::OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = reinterpret_cast<NM_GRIDVIEW*>(pNotifyStruct);
	CString str = m_Grid.GetCell(pItem->iRow, pItem->iColumn)->GetText();
	str.Replace(_T("."),_T(","));
	CString sPodzem = m_Grid.GetCell(pItem->iRow, 17)->GetText();
	BOOL bPodzem = sPodzem == LoadStr(IDS_PT_PODZ);
	//CPipesSet set;
	//set.m_strPath=_T(".");
	//set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %s and %d=PODZ order by DIAM, PODZ"),
	//		m_Grid.GetCell(pItem->iRow,1)->GetText(), int(bPodzem));
	//set.Open();
	if (pItem->iRow == m_Grid.GetRowCount() - 1)
	{
		set.AddNew();
		set.m_DIAM = 0.0;
		set.m_NTOS = 0.0;
		set.m_RTOS = 0.0;
		set.m_NAMA = "";
		set.m_VETR = 0.0;
		set.m_VEIZ = 0.0;
		set.m_VEPR = 0.0;
		set.m_DIIZ = 0.0;
		set.m_RAOT = 0.0;
		set.m_VESA = 0.0;
		set.m_MARI = "";
		set.m_NOTO = 0.0;
		set.m_RATO = 0.0;
		set.m_SEFF = 0.0;
		set.m_KPOD = 0.0;
		set.m_SHTR = 0.0;
		set.m_PODZ = FALSE;
		set.m_IZTO = 0.0;
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
		set.m_NTOS = float(_wtof(str));
		break;
	case 2:
		set.m_RTOS = float(_wtof(str));
		break;
	case 3:
		set.m_NAMA = str;
		break;
	case 4:
		set.m_VETR = float(_wtof(str));
		break;
	case 5:
		set.m_VEIZ = float(_wtof(str));
		break;
	case 6:
		set.m_VEPR = float(_wtof(str));
	case 7:
		set.m_DIIZ = float(_wtof(str));
		break;
	case 8:
		set.m_RAOT = float(_wtof(str));
		break;
	case 9:
		set.m_VESA = float(_wtof(str));
		break;
	case 10:
		set.m_MARI = str;
		break;
	case 11:
		set.m_NOTO = float(_wtof(str));
		break;
	case 12:
		set.m_RATO = float(_wtof(str));
		break;
	case 13:
		set.m_SEFF = float(_wtof(str));
		break;
	case 14:
		set.m_KPOD = float(_wtof(str));
		break;
	case 15:
		set.m_SHTR = float(_wtof(str));
		break;
	case 16:
		set.m_PODZ = bPodzem;
	case 17:
		set.m_IZTO = float(_wtof(str));
	}
	set.Update();
	//set.Close();
}

void CPipesTableDlg::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
	// Load the desired menu
	CMenu mnuPopup;
	mnuPopup.LoadMenu(IDR_POPUP_TABLE);


	// Get a pointer to the first item of the menu
	CMenu* mnuPopupMenu = mnuPopup.GetSubMenu(0);
	ASSERT(mnuPopupMenu);

	mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPipesTableDlg::OnTableDel()
{
	int nRow = m_Grid.GetFocusCell().row;
	if (AfxMessageBox(LoadStr(IDS_PT_DEL_LINE_Q), MB_YESNO) == IDYES)
	{
		CString sPodzem = m_Grid.GetCell(nRow, 16)->GetText();
		//BOOL bPodzem = sPodzem == _T("Подз.");
		//CPipesSet set;
		//set.m_strPath=_T(".");
		//set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %s and %d=PODZ order by DIAM, PODZ"),
		//	m_Grid.GetCell(nRow,1)->GetText(), int(bPodzem));
		//set.Open
		set.SetAbsolutePosition(nRow);
		m_Grid.DeleteRow(nRow);
		set.Delete();
		//set.Close();
	}
}

void CPipesTableDlg::OnDestroy()
{
	set.Close();
	CDialog::OnDestroy();
}


void CPipesTableDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize = CPoint(400, 250);

	CDialog::OnGetMinMaxInfo(lpMMI);
}

