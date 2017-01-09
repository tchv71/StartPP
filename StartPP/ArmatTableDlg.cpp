// ArmatTableDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "ArmatTableDlg.h"
#include "ArmatSet.h"
#include "Strings.h"
#include "dbf_wx_inl.h"
#include "dbf_inl.h"


// диалоговое окно CArmatTableDlg

//IMPLEMENT_DYNAMIC(CArmatTableDlg, CDialog)
CArmatSet setArmat;


CArmatTableDlg::CArmatTableDlg(CWnd* pParent /*=nullptr*/)
	: CTableDlg(pParent, DATA_PATH _T("/") _T("Armat.dbf"), DATA_PATH _T("/") _T("ArmatCopy.dbf"), setArmat)
{
	SetTitle(_T("Таблица арматуры"));
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
	EVT_GRID_CELL_CHANGED(CTableDlg::OnGridCellChanged)
END_MESSAGE_MAP()


// обработчики сообщений CArmatTableDlg

//extern LPCTSTR LoadStr(UINT nID);

BOOL CArmatTableDlg::OnInitDialog()
{
	CTableDlg::OnInitDialog();
	m_grid->AppendCols(setArmat.m_nFields);
	//m_Grid.SetFixedRowCount(1);
	//m_Grid.SetFixedColumnCount(1);
	//m_Grid.SetFixedColumnSelection(TRUE);
	//m_Grid.SetListMode(TRUE);

	//m_Grid.SetColumnCount(setArmat.m_nFields + 1);
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
	setArmat.m_strPath = _T(".");
	setArmat.m_strTable = m_strCopyDbfName;
	if (!setArmat.Open())
		AfxMessageBox(_T("Can't open Armat.dbf"),wxOK | wxICON_EXCLAMATION);
	int nRowCount = 0;
	while (!setArmat.IsEOF())
	{
		nRowCount++;
		setArmat.MoveNext();
	}
	//m_Grid.SetRowCount(nRowCount + 2);
	m_grid->AppendRows(nRowCount + 1);
	m_grid->SetRowLabelSize(20);
	//m_Grid.SetRowHeight(nRowCount + 1, 1);
	//m_Grid.SetEditable(false);
	setArmat.Close();
	setArmat.Open();

	std::vector<SArmat> table;
	while (!setArmat.IsEOF())
	{
		setArmat.m_pos = setArmat.GetDatabase().GetPosition();
		table.push_back(setArmat);
		setArmat.MoveNext();
	}
	setArmat.Close();
	std::sort(table.begin(), table.end());
	m_vecTableIdx.resize(table.size());
	for (int row = 1; row < nRowCount + 2 - 1; row++)
	{
		CString str;
		SArmat set1 = table[row - 1];
		m_vecTableIdx[row - 1] = set1.m_pos;
		m_grid->SetRowLabelValue(row-1,_T(""));
		SetFloat(set1.m_DIAM, 1, row,0);
		SetFloat(set1.m_NOTO, 2, row,0);
		SetFloat(set1.m_RATO, 3, row,1);
		SetFloat(set1.m_RAOT, 4, row,2);
		SetFloat(set1.m_VESA, 5, row,1);
		SetFloat(set1.m_RAOT1, 6, row,1);
		SetFloat(set1.m_VESA1, 7, row,0);
		SetFloat(set1.m_NAG1, 8, row,1);
		SetFloat(set1.m_NAG2, 9, row,1);
	}
	m_grid->SetRowLabelValue(nRowCount, _T("*"));
	return TRUE; // return TRUE unless you setArmat the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

