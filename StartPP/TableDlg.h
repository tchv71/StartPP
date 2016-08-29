#ifndef CTABLEDLG_H
#define CTABLEDLG_H
#include "stdafx.h"
#include "wxcrafter.h"


class CRecordset;

class CTableDlg : public CPipesTableBaseDlg
{
public:
	CTableDlg(CWnd* pParent, LPCTSTR pszDbfName, LPCTSTR pszCopyDbfName, CRecordset& rSet);
	virtual ~CTableDlg();
protected:
	DECLARE_MESSAGE_MAP()
	wxMenu* m_menu;
	//void OnContextMenu(wxContextMenuEvent& event);
	std::vector<unsigned> m_vecTableIdx;
	wxString m_strCopyDbfName;
	wxString m_strDbfName;
	CRecordset& m_set;
public:
	BOOL OnInitDialog() const;
	void SetHdr(CString str, int pos, int row = 0) const;
	void SetFloat(float val, int pos, int row = 0, int prec = -1) const;
	void SetMaterial(CString str, int pos, int row) const;
	void EndModal(int retcode) wxOVERRIDE;
	void OnCellRightClick(wxGridEvent& event);
	void OnTableDel(wxCommandEvent& event);
	void OnGridCellChanged(wxGridEvent& event);
};

#endif // CTABLEDLG_H
