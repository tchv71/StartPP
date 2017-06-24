#include "stdafx.h"
#include "TableDlg.h"
#include "Strings.h"
#include "dbf.hpp"
#include "dbf_inl.h"
#include "dbf_wx.h"
#include "dbf_wx_inl.h"
#include "Material.h"
#include <wx/dynarray.h>
enum
{
	wxID_DEL_LINE = ID_RecalcXYZ+1
};

BEGIN_MESSAGE_MAP(CTableDlg, CPipesTableBaseDlg)
	//EVT_GRID_CELL_RIGHT_CLICK(CTableDlg::OnCellRightClick)
	EVT_MENU(wxID_DEL_LINE, CTableDlg::OnTableDel)
	EVT_UPDATE_UI(wxID_DEL_LINE, CTableDlg::OnUpdateDelLine)
END_MESSAGE_MAP()

CTableDlg::CTableDlg(CWnd* pParent, LPCTSTR pszDbfName, LPCTSTR pszCopyDbfName, CRecordset& rSet) :
	CPipesTableBaseDlg(pParent),
	m_menu(nullptr),
	m_strCopyDbfName(pszCopyDbfName),
	m_strDbfName(pszDbfName),
	m_set(rSet)
{
}

CTableDlg::~CTableDlg()
{
}

BOOL CTableDlg::OnInitDialog() const
{
	wxCopyFile(DATA_PATH+"/"+m_strDbfName, DATA_PATH+"/"+m_strCopyDbfName);
	return TRUE;
}

void CTableDlg::SetHdr(CString str, int pos, int row) const
{
	if (row == 0)
	{
		m_grid->SetColLabelValue(pos - 1, str);
		return;
	}
	m_grid->SetCellValue(row - 1, pos - 1, str);
}

void CTableDlg::SetFloat(float val, int pos, int row, int prec) const
{
	m_grid->SetColFormatFloat(pos - 1, -1, prec);
	m_grid->SetCellValue(row - 1, pos - 1, CString::Format(_T("%g"), val));
}

void CTableDlg::SetMaterial(CString str, int pos, int row) const
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


void CTableDlg::EndModal(int retcode)
{
	if (retcode == wxID_OK)
	{
		wxCopyFile(DATA_PATH+"/"+m_strCopyDbfName, DATA_PATH+"/"+m_strDbfName);
	}
	wxRemoveFile(DATA_PATH+"/"+m_strCopyDbfName);
	CPipesTableBaseDlg::EndModal(retcode);
}

void CTableDlg::OnCellRightClick(wxGridEvent & event)
{
	//m_grid->SetGridCursor(m_grid->XYToCell(m_grid->ScreenToClient(ClientToScreen(event.GetPosition()))));
	m_grid->SetGridCursor(event.GetRow(), event.GetCol());
	if (!m_menu)
	{
		m_menu = new wxMenu();
		wxMenuItem* pItem = m_menu->Append(wxID_DEL_LINE, wxT("&Удалить строку"));
		pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_DELETE, wxART_MENU, wxDefaultSize));
		pItem->Enable(true);
	}
	PopupMenu(m_menu);
	event.Skip();
}


void CTableDlg::OnTableDel(wxCommandEvent & event)
{
	int nRow = m_grid->GetGridCursorRow();
	DeleteLine(nRow);
	event.Skip();
}

void CTableDlg::DeleteLine(int nRow)
{
	wxDBase& dbf = m_set.GetDatabase();
	dbf.Open(wxFileName(DATA_PATH+"/"+m_strCopyDbfName), dbf_editmode_editable);
	dbf.SetPosition(m_vecTableIdx[nRow]);
	dbf.DeleteRecord();
	dbf.Update();
	dbf.Close();
	m_grid->DeleteRows(nRow);
	m_grid->SetRowLabelValue(m_grid->GetNumberRows() - 1, _T("*"));
	m_vecTableIdx.erase(m_vecTableIdx.cbegin() + nRow);
}


void CTableDlg::OnGridCellChanged(wxGridEvent& event)
{
	wxDBase& dbf = m_set.GetDatabase();
	dbf.Open(wxFileName(DATA_PATH+"/"+m_strCopyDbfName), dbf_editmode_editable);
	if (event.GetRow() == m_grid->GetNumberRows() - 1)
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

void CTableDlg::OnUpdateDelLine(wxUpdateUIEvent& event)
{
	event.Enable(true);
}

void CTableDlg::OnTableDelLine(wxCommandEvent& event)
{
	event.Skip();
	if (AfxMessageBox(LoadStr(IDS_PT_DEL_LINE_Q), wxYES_NO | wxICON_QUESTION) != wxYES)
		return;
	while (true)
	{
		wxArrayInt selRows = m_grid->GetSelectedRows();
		if (selRows.Count() == 0)
			return;
		DeleteLine(selRows[0]);
	}
}

void CTableDlg::OnUpdateTableDelLine(wxUpdateUIEvent& event)
{
	wxArrayInt selRows = m_grid->GetSelectedRows();
	event.Enable(selRows.Count()>0);
}
