// ArmatTableDlg.cpp: файл реализации
//
-----------
#include "stdafx.h"
#include "ArmatTableDlg.h"
#include "ArmatSet.h"
#include "Strings.h"
#include "dbf_wx_inl.h"
#include "dbf_inl.h"


// диалоговое окно CArmatTableDlg

//IMPLEMENT_DYNAMIC(CArmatTableDlg, CDialog)
CArmatSet set;


CArmatTableDlg::CArmatTableDlg(CWnd* pParent /*=nullptr*/)
	: CTableDlg(pParent, DATA_PATH _T("/") _T("ArmatCopy.dbf"), DATA_PATH _T("/") _T("Armat.dbf"), set)
{
	OnInitDialog();
	if (GetSizer()) {
		GetSizer()->Fit(this);
	}
}


CArmatTableDlg::~CArmatTableDlg()
{
}


//void CArmatTableDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//DDX_Control(pDX, IDC_LIST1, m_lbTable);
//	//DDX_Control(pDX, IDC_TREE1, m_tree);
//	DDX_Control(pDX, IDC_GRID, m_Grid); // associate the grid window with a C++ object
//}


BEGIN_MESSAGE_MAP(CArmatTableDlg, CTableDlg)
	EVT_GRID_CELL_CHANGED(CArmatTableDlg::OnGridCellChanged)
END_MESSAGE_MAP()


// обработчики сообщений CArmatTableDlg

//extern LPCTSTR LoadStr(UINT nID);

BOOL CArmatTableDlg::OnInitDialog()
{
	CTableDlg::OnInitDialog();
	m_grid->AppendCols(set.m_nFields);
	//m_Grid.SetFixedRowCount(1);
	//m_Grid.SetFixedColumnCount(1);
	//m_Grid.SetFixedColumnSelection(TRUE);
	//m_Grid.SetListMode(TRUE);

	//m_Grid.SetColumnCount(set.m_nFields + 1);
	//m_Grid.EnableSelection(FALSE);
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
	set.m_strTable = m_strCopyDbfName;
	if (!set.Open())
		AfxMessageBox(_T("Can't open Armat.mdb"),wxID_OK);
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

	std::vector<SArmat> table;
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
		SArmat set1 = table[row - 1];
		m_vecTableIdx[row - 1] = set1.m_pos;
		m_grid->SetRowLabelValue(row-1,_T(""));
		SetFloat(set1.m_DIAM, 1, row);
		SetFloat(set1.m_NOTO, 2, row);
		SetFloat(set1.m_RATO, 3, row);
		SetFloat(set1.m_RAOT, 4, row);
		SetFloat(set1.m_VESA, 5, row);
		SetFloat(set1.m_RAOT1, 6, row);
		SetFloat(set1.m_VESA1, 7, row);
		SetFloat(set1.m_NAG1, 8, row);
		SetFloat(set1.m_NAG2, 9, row);
	}
	m_grid->SetRowLabelValue(nRowCount, _T("*"));
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CArmatTableDlg::OnGridCellChanged(wxGridEvent& event)
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
	int nCol = event.GetCol();
	wxString newValue = m_grid->GetCellValue(event.GetRow(), event.GetCol());
	dbf.Write(dbf_uint(nCol), newValue);

	dbf.Update();
	dbf.Close();
	event.Skip();
}

