#pragma once
//#include "afxwin.h"
//#include "resource.h"
//#include "GridCtrl_src/GridCtrl.h"
#include "wxcrafter.h"

// диалоговое окно CPipesTableDlg

class CPipesTableDlg : public CPipesTableBaseDlg
{
	//DECLARE_DYNAMIC(CPipesTableDlg)

public:
	CPipesTableDlg(CWnd* pParent = nullptr); // стандартный конструктор
	virtual ~CPipesTableDlg();


protected:
	wxMenu* m_menu;
	//void OnContextMenu(wxContextMenuEvent& event);
	std::vector<unsigned> m_vecTableIdx;
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLbnSelchangeList1();
	BOOL OnInitDialog();
	//CGridCtrl m_Grid;
	CSize m_OldSize;
	//CPipesSet set;
	virtual void OnTableDel(wxCommandEvent& event);
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetHdr(CString str, int pos, int row = 0);
	void SetPodz(CString str, int pos, int row = 0);
	void SetMaterial(CString str, int pos, int row);
	void SetFloat(float val, int pos, int row = 0, int prec = -1);
	void OnGridCellChanged(wxGridEvent& event);
	void OnCellRightClick(wxGridEvent& event);
	//virtual void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
	//afx_msg void OnDestroy();
	//afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};

