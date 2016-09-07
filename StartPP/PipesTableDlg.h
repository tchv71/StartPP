#pragma once
//#include "afxwin.h"
//#include "resource.h"
//#include "GridCtrl_src/GridCtrl.h"
#include "TableDlg.h"
// диалоговое окно CPipesTableDlg

class CPipesTableDlg : public CTableDlg
{
	//DECLARE_DYNAMIC(CPipesTableDlg)

public:
	CPipesTableDlg(CWnd* pParent = nullptr); // стандартный конструктор
	virtual ~CPipesTableDlg();


protected:
 	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLbnSelchangeList1();
	BOOL OnInitDialog();
	//CGridCtrl m_Grid;
	CSize m_OldSize;
	//CPipesSet set;
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetPodz(CString str, int pos, int row = 0) const;
	void OnGridCellChanged(wxGridEvent& event);
};
