// MainFrm.h : интерфейс класса CMainFrame
//

#pragma once
#include "PropertiesWnd.h"
#include "PipeTableWnd.h"
#include "StartPPStatusBar.h"

class CProjButton : public CMFCToolBarMenuButton
{
	DECLARE_SERIAL(CProjButton)

public:
	CProjButton()
	{
	}

	CProjButton(UINT uiCmdID, HMENU h, LPCTSTR lpszText);


protected:
	CMFCPopupMenu* CreatePopupMenu() override;;

	BOOL IsEmptyMenuAllowed() const override;

	void OnChangeParentWnd(CWnd* pWndParent) override;

	BOOL IsExclusive() const override;
};


class CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

	// Атрибуты
public:

	// Операции
public:

	// Переопределение
public:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
	BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr) override;

	// Реализация
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

public: // встроенные члены панели элементов управления
	CMFCMenuBar m_wndMenuBar;
	CMFCToolBar m_wndToolBar;
	CMFCToolBar m_wndViewToolBar;
	CMFCToolBar m_wndFilterToolBar;
	CMFCToolBar m_wndOperationsToolBar;
	CMFCToolBar m_wndToolsToolBar;
	CMFCToolBar m_wndProjToolBar;

	CStartPPStatusBar m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	//CFileView         m_wndFileView;
	//CClassView        m_wndClassView;
	//COutputWnd        m_wndOutput;
	CPropertiesWnd m_wndProperties;
	CPipeTableWnd m_wndPipeTable;

	// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnToolbarReset(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:
	afx_msg void OnWindowTileVert();
	afx_msg void OnPropMert();
	afx_msg void OnUpdatePropMert(CCmdUI* pCmdUI);
	afx_msg void OnPropSk();
	afx_msg void OnUpdatePropSk(CCmdUI* pCmdUI);
	afx_msg void OnPropNapr();
	afx_msg void OnUpdatePropNapr(CCmdUI* pCmdUI);
	afx_msg void OnPropOtvIz();
	afx_msg void OnUpdatePropOtvIz(CCmdUI* pCmdUI);
	afx_msg void OnPropOtvSv();
	afx_msg void OnUpdatePropOtvSv(CCmdUI* pCmdUI);
	afx_msg void OnPropArm();
	afx_msg void OnUpdatePropArm(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndFileCount(CCmdUI* pCmdUI);
};

