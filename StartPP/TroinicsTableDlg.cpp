// TroinicsTableDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "TroinicsTableDlg.h"
#include "TroinicsSet.h"
#include "Strings.h"
#include "dbf_wx_inl.h"
#include "dbf_inl.h"


// диалоговое окно CTroinicsTableDlg

//IMPLEMENT_DYNAMIC(CTroinicsTableDlg, CDialog)
CTroinicsSet setTroinics;


CTroinicsTableDlg::CTroinicsTableDlg(CWnd* pParent /*=nullptr*/)
	: CTableDlg(pParent, _T("Troinics.dbf"), _T("TroinicsCopy.dbf"), setTroinics)
{
	SetTitle(_T("Таблица тройников"));
	OnInitDialog();
	if (GetSizer()) {
		GetSizer()->Fit(this);
	}
}


CTroinicsTableDlg::~CTroinicsTableDlg()
{
}


//void CTroinicsTableDlg::DoDataExchange(CDataExchange* pDX)
//{
//	CDialog::DoDataExchange(pDX);
//	//DDX_Control(pDX, IDC_LIST1, m_lbTable);
//	//DDX_Control(pDX, IDC_TREE1, m_tree);
//	DDX_Control(pDX, IDC_GRID, m_Grid); // associate the grid window with a C++ object
//}


BEGIN_MESSAGE_MAP(CTroinicsTableDlg, CTableDlg)
	EVT_GRID_CELL_CHANGED(CTableDlg::OnGridCellChanged)
END_MESSAGE_MAP()


// обработчики сообщений CTroinicsTableDlg

//extern LPCTSTR LoadStr(UINT nID);

BOOL CTroinicsTableDlg::OnInitDialog()
{
	CTableDlg::OnInitDialog();
	m_grid->AppendCols(setTroinics.m_nFields);
	//m_Grid.SetFixedRowCount(1);
	//m_Grid.SetFixedColumnCount(1);
	//m_Grid.SetFixedColumnSelection(TRUE);
	//m_Grid.SetListMode(TRUE);

	//m_Grid.SetColumnCount(setTroinics.m_nFields + 1);
	//m_Grid.EnableSelection(FALSE);
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
	setTroinics.m_strPath = DATA_PATH;
	setTroinics.m_strTable = m_strCopyDbfName;
	if (!setTroinics.Open())
		AfxMessageBox(_T("Can't open Troinics.dbf"),wxOK | wxICON_EXCLAMATION);
	int nRowCount = 0;
	while (!setTroinics.IsEOF())
	{
		nRowCount++;
		setTroinics.MoveNext();
	}
	//m_Grid.SetRowCount(nRowCount + 2);
	m_grid->AppendRows(nRowCount + 1);
	m_grid->SetRowLabelSize(20);
	//m_Grid.SetRowHeight(nRowCount + 1, 1);
	//m_Grid.SetEditable(false);
	setTroinics.Close();
	setTroinics.Open();

	std::vector<STroinics> table;
	while (!setTroinics.IsEOF())
	{
		setTroinics.m_pos = setTroinics.GetDatabase().GetPosition();
		table.push_back(setTroinics);
		setTroinics.MoveNext();
	}
	setTroinics.Close();
	std::sort(table.begin(), table.end());
	m_vecTableIdx.resize(table.size());
	for (int row = 1; row < nRowCount + 2 - 1; row++)
	{
		CString str;
		STroinics set1 = table[row - 1];
		m_vecTableIdx[row - 1] = set1.m_pos;
		m_grid->SetRowLabelValue(row-1,_T(""));
		SetFloat(set1.m_DIAM, 1, row, 0);
		SetFloat(set1.m_NTSTM, 2, row, 1);
		SetFloat(set1.m_RTSTM, 3, row, 2);
		SetFloat(set1.m_DIAMSH, 4, row, 0);
		SetFloat(set1.m_NTSTSH, 5, row, 1);
		SetFloat(set1.m_RTSTSH, 6, row, 2);
		SetFloat(float(set1.m_VIS_SHTU), 7, row,0);
		SetFloat(set1.m_WIDTHNAK, 8, row,0);
		SetFloat(set1.m_THINKNAK, 9, row,0);
		SetFloat(set1.m_VES, 10, row,2);
		SetFloat(float(set1.m_KORPUS), 11, row, 0);
	}
	m_grid->SetRowLabelValue(nRowCount, _T("*"));
	return TRUE; // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

