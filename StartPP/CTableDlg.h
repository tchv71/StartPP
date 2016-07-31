#ifndef CTABLEDLG_H
#define CTABLEDLG_H
#include "stdafx.h"
#include "wxcrafter.h"


class CTableDlg : public CPipesTableBaseDlg
{
public:
	CTableDlg(CWnd* pParent, LPCTSTR pszDbfName, LPCTSTR pszCopyDbfName);
	virtual ~CTableDlg();
protected:
	wxMenu* m_menu;
	//void OnContextMenu(wxContextMenuEvent& event);
	std::vector<unsigned> m_vecTableIdx;
	wxString m_strCopyDbfName;
	wxString m_strDbfName;
public:
	BOOL OnInitDialog();
	void EndModal(int retcode) wxOVERRIDE;

};

#endif // CTABLEDLG_H
