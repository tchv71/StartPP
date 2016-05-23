#pragma once
#include "afxwin.h"
#include "resource.h"
#include "GridCtrl_src/GridCtrl.h"

// ���������� ���� CPipesTableDlg

class CPipesTableDlg : public CDialog
{
	DECLARE_DYNAMIC(CPipesTableDlg)

public:
	CPipesTableDlg(CWnd* pParent = nullptr); // ����������� �����������
	CPipesTableDlg(UINT nIDD, CWnd* pParent = nullptr); // ����������� �����������
	virtual ~CPipesTableDlg();

	// ������ ����������� ����
	enum
	{
		IDD = IDD_PIPES_DIALOG
	};

protected:
	void DoDataExchange(CDataExchange* pDX) override; // ��������� DDX/DDV
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnLbnSelchangeList1();
	BOOL OnInitDialog() override;
	CGridCtrl m_Grid;
	CSize m_OldSize;
	//CPipesSet set;
	virtual void OnTableDel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetHdr(CString str, int pos, int row = 0);
	void SetMaterial(CString str, int pos, int row);
	void SetFloat(float val, int pos, int row = 0);
	virtual void OnGridEndEdit(NMHDR* pNotifyStruct, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
