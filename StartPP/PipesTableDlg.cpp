// PipesTableDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "PipesTableDlg.h"
#include "PipesSet.h"
#include <wx/filefn.h>
#include "Material.h"
#include "Strings.h"
#include "dbf_wx_inl.h"
#include "dbf_inl.h"
#include "CTableDlg.h"


// диалоговое окно CPipesTableDlg

//IMPLEMENT_DYNAMIC(CPipesTableDlg, CDialog)

CPipesTableDlg::CPipesTableDlg(CWnd* pParent /*=nullptr*/)
	: CTableDlg(pParent, DATA_PATH _T("/") _T("PipesCopy.dbf"), DATA_PATH _T("/") _T("Pipes.dbf"))
{
	OnInitDialog();
	if (GetSizer()) {
		GetSizer()->Fit(this);
	}
}


CPipesTableDlg::~CPipesTableDlg()
{
}


//void CPipesTableDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//DDX_Control(pDX, IDC_LIST1, m_lbTable);
//	//DDX_Control(pDX, IDC_TREE1, m_tree);
//	DDX_Control(pDX, IDC_GRID, m_Grid); // associate the grid window with a C++ object
//}


BEGIN_MESSAGE_MAP(CPipesTableDlg, CTableDlg)
	EVT_GRID_CELL_CHANGED(CPipesTableDlg::OnGridCellChanged)
	EVT_GRID_CELL_RIGHT_CLICK(CPipesTableDlg::OnCellRightClick)
	EVT_MENU(wxID_DELETE, CPipesTableDlg::OnTableDel)
END_MESSAGE_MAP()


// обработчики сообщений CPipesTableDlg


CPipesSet set;

//extern LPCTSTR LoadStr(UINT nID);

BOOL CPipesTableDlg::OnInitDialog()
{
	CTableDlg::OnInitDialog();
	m_grid->AppendCols(set.m_nFields);
	//m_Grid.SetFixedRowCount(1);
	//m_Grid.SetFixedColumnCount(1);
	//m_Grid.SetFixedColumnSelection(TRUE);
	//m_Grid.SetListMode(TRUE);

	//m_Grid.SetColumnCount(set.m_nFields + 1);
	//m_Grid.EnableSelection(FALSE);
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
	set.m_strTable = m_strCopyDbfName;
	if (!set.Open())
		AfxMessageBox(_T("Can't open Pipes.mdb"),wxID_OK);
	int nRowCount = 0;
	while (!set.IsEOF())
	{
		nRowCount++;
		set.MoveNext();
	}
	//m_Grid.SetRowCount(nRowCount + 2);
	m_grid->AppendRows(nRowCount + 1);
	m_grid->SetRowLabelSize(20);
	//m_Grid.SetRowHeight(nRowCount + 1, 1);
	//m_Grid.SetEditable(false);
	set.Close();
	set.Open();

	std::vector<SPipe> table;
	while (!set.IsEOF())
	{
		set.m_pos = set.GetDatabase().GetPosition();
		table.push_back(set);
		set.MoveNext();
	}
	set.Close();
	std::sort(table.begin(), table.end());
	m_vecTableIdx.resize(table.size());
	for (int row = 1; row < nRowCount + 2 - 1; row++)
	{
		CString str;
		SPipe set1 = table[row - 1];
		m_vecTableIdx[row - 1] = set1.m_pos;
		m_grid->SetRowLabelValue(row-1,_T(""));
		SetFloat(set1.m_DIAM, 1, row, 0);
		SetFloat(set1.m_NTOS, 2, row, 1);
		SetFloat(set1.m_RTOS, 3, row, 2);
		//m_Grid.SetCellType(row, 4, RUNTIME_CLASS(CGridCellCombo));
		str = set1.m_NAMA;
		SetMaterial(str, 4, row);
		SetFloat(set1.m_VETR, 5, row,2);
		SetFloat(set1.m_VEIZ, 6, row,2);
		SetFloat(set1.m_VEPR, 7, row,2);
		SetFloat(set1.m_DIIZ, 8, row,0);
		SetFloat(set1.m_RAOT, 9, row,3);
		SetFloat(set1.m_VESA, 10, row,1);
		//m_Grid.SetCellType(row, 11, RUNTIME_CLASS(CGridCellCombo));
		str = set1.m_MARI;
		SetMaterial(str, 11, row);
		SetFloat(set1.m_NOTO, 12, row,0);
		SetFloat(set1.m_RATO, 13, row,1);
		SetFloat(set1.m_SEFF, 14, row,0);
		SetFloat(set1.m_KPOD, 15, row,5);
		SetFloat(set1.m_SHTR, 16, row,1);
#if 0
		m_Grid.SetCellType(row, 17, RUNTIME_CLASS(CGridCellCombo));
		CStringArray ar;
		ar.Add(LoadStr(IDS_PT_NADZ));
		ar.Add(LoadStr(IDS_PT_PODZ));
		CGridCellCombo* pCombo = dynamic_cast<CGridCellCombo*>(m_Grid.GetCell(row, 17));
		pCombo->SetOptions(ar);
		pCombo->SetStyle(CBS_DROPDOWNLIST);
#endif
		SetPodz(LoadStr(set1.m_PODZ ? IDS_PT_PODZ : IDS_PT_NADZ), 17, row);
		if (set1.m_PODZ)
			SetFloat(set1.m_IZTO, 18, row, 1);
	}
	//CRect rect;
	//GetClientRect(rect);
	//m_OldSize = CSize(rect.Width(), rect.Height());
	m_grid->SetRowLabelValue(nRowCount, _T("*"));


	//m_Grid.AutoSize();
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}



void CPipesTableDlg::SetHdr(CString str, int pos, int row)
{
	if (row == 0)
	{
		m_grid->SetColLabelValue(pos-1, str);
		return;
	}
	m_grid->SetCellValue(row-1, pos-1, str);
}

void CPipesTableDlg::SetPodz(CString str, int pos, int row)
{
	wxArrayString ar;
	ar.Add(IDS_PT_NADZ);
	ar.Add(IDS_PT_PODZ);
	m_grid->SetCellEditor(row - 1, pos - 1, new wxGridCellChoiceEditor(ar));
	m_grid->SetCellValue(row - 1, pos - 1, str);
}


void CPipesTableDlg::SetMaterial(CString str, int pos, int row)
{
	CMaterial setMaterial;
	setMaterial.m_strPath = DATA_PATH;
	setMaterial.m_strTable = _T("Matup.dbf");// _T("[MATUP]  order by NOM");
	setMaterial.Open();
	wxArrayString ar;
	while (!setMaterial.IsEOF())
	{
		ar.Add(CString(setMaterial.m_MAT));
		setMaterial.MoveNext();
	}
	m_grid->SetCellEditor(row - 1, pos - 1, new wxGridCellChoiceEditor(ar));
	m_grid->SetCellValue(row - 1, pos - 1, str);
}

void CPipesTableDlg::SetFloat(float val, int pos, int row, int prec)
{
	m_grid->SetColFormatFloat(pos-1, -1, prec);
	m_grid->SetCellValue(row-1, pos-1, CString::Format(_T("%g"), val));
}

void CPipesTableDlg::OnGridCellChanged(wxGridEvent& event)
{
	wxDBase& dbf = set.GetDatabase();
	dbf.Open(wxFileName(m_strCopyDbfName), dbf_editmode_editable);
	if (event.GetRow() == m_grid->GetNumberRows()-1)
	{
		dbf.AddNew();
		m_vecTableIdx.push_back(dbf.GetPosition());
		m_grid->SetRowLabelValue(event.GetRow(), _T(""));
		m_grid->AppendRows();
		m_grid->SetRowLabelValue(m_grid->GetNumberRows() - 1, _T("*"));
	}
	else
	{
		dbf.SetPosition(m_vecTableIdx[event.GetRow()]);
	}
	const char *arrFields[] = { "DIAM","NTOS","RTOS","NAMA","VETR","VEIZ","VEPR","DIIZ","RAOT","VESA","MARI","NOTO","RATO","SEFF","KPOD","SHTR","PODZ","IZTO" };
	int nCol = event.GetCol();
	wxString newValue = m_grid->GetCellValue(event.GetRow(), event.GetCol());
	bool bRes = false;
	if (nCol == 16)
	{
		BOOL bPodz = newValue == LoadStr(IDS_PT_PODZ);
		wxString val = bPodz ? _T("1") : _T("0");
		dbf.Write(arrFields[nCol], val);
	}
	else
	{
		bRes= dbf.Write(arrFields[nCol], newValue);
	}
	dbf.Update();
	dbf.Close();
	event.Skip();
}

void CPipesTableDlg::OnCellRightClick(wxGridEvent & event)
{
	//m_grid->SetGridCursor(m_grid->XYToCell(m_grid->ScreenToClient(ClientToScreen(event.GetPosition()))));
	m_grid->SetGridCursor(event.GetRow(), event.GetCol());
	if (!m_menu)
	{
		m_menu = new wxMenu();
		wxMenuItem* pItem = m_menu->Append(wxID_DELETE, wxT("&Удалить строку"));
		pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_MENU, wxDefaultSize));
	}
	PopupMenu(m_menu);
	event.Skip();
}


void CPipesTableDlg::OnTableDel(wxCommandEvent & event)
{
	int nRow = m_grid->GetGridCursorRow();
	if (AfxMessageBox(LoadStr(IDS_PT_DEL_LINE_Q), MB_YESNO) == IDYES)
	{
		wxDBase& dbf = set.GetDatabase();
		dbf.Open(wxFileName(m_strCopyDbfName), dbf_editmode_editable);
		dbf.SetPosition(m_vecTableIdx[nRow]);
		dbf.DeleteRecord();
		dbf.Update();
		dbf.Close();
		m_grid->DeleteRows(nRow);
		m_grid->SetRowLabelValue(m_grid->GetNumberRows() - 1, _T("*"));
		m_vecTableIdx.erase(m_vecTableIdx.cbegin() + nRow);
	}
	event.Skip();
}

