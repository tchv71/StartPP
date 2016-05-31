#pragma once

#include "PipeAndNode.h"
#include "PipesSet.h"
#include "ArmatSet.h"
#include <map>
#include <set>

#ifdef WX
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/manager.h>
typedef wxToolBar CMFCToolBar;
typedef wxFrame CFrameWnd;
typedef wxPanel CDockablePane;
typedef wxComboBox CComboBox;
typedef wxPropertyGridManager CMFCPropertyGridCtrl;
typedef wxPGProperty CMFCPropertyGridProperty;
typedef wxWindow CWnd;
class CCmdUI;
class CDataExchange;
typedef wxVariant _variant_t;
typedef wxVariant COleVariant;
#define afx_msg
#endif

class CPropertiesToolBar : public CMFCToolBar
{
public:
#ifndef WX
	void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler) //override
	{
		CMFCToolBar::OnUpdateCmdUI(static_cast<CFrameWnd*>(GetOwner()), bDisableIfNoHndler);
	}

	BOOL AllowShowOnList() const //overridea
	{
		return FALSE;
	}
#endif
};

class CStartPPDoc;

enum EPropMode
{
	E_NONE,
	E_PIPE,
	E_NODE
};

class CPropertiesWnd : public CDockablePane
{
	// Создание
public:
	CPropertiesWnd();

	void AdjustLayout() ;//override;

	// Атрибуты
public:
#ifndef WX
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
#endif

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;
	CPipesSet set;
	CArmatSet seta;

	// Реализация
public:
	virtual ~CPropertiesWnd();

protected:
#ifdef WX
    int OnCreate();
    void OnSize(wxSizeEvent& evt);
    void OnSetFocus(wxFocusEvent& evt);
#else
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
#endif
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnLBChange(void);

	DECLARE_MESSAGE_MAP()
	void FillPipeProps();
	void FillNodeProps();

	void InitPropList();
	void SetPropListFont();

	class CAngles
	{
	public:
		float a_plan, a_prof, a_plan_rel, a_plan_prev, l_plan, l_gen, uklon;
		void GetRelAngle(CStartPPDoc* m_pDoc, CPipeAndNode* pPnN);
		void calc_angles(float x, float y, float z);
	} a1, a2;


	CMFCPropertyGridProperty* m_propX;
	CMFCPropertyGridProperty* m_propY;
	CMFCPropertyGridProperty* m_propZ;
	CMFCPropertyGridProperty* m_propLen;
	CMFCPropertyGridProperty* m_propLPlan;
	CMFCPropertyGridProperty* m_propAPlan;
	CMFCPropertyGridProperty* m_propAPlanRel;
	CMFCPropertyGridProperty* m_propAProf;
	CMFCPropertyGridProperty* m_propUklon;

	CMFCPropertyGridProperty* m_propNagr;
	CMFCPropertyGridProperty* m_pIzdProp;

	CStartPPDoc* m_pDoc;
	void RecalcXYZ();

	int m_nComboHeight;
public:
	EPropMode m_PropMode;
	EPropMode m_oPropMode;
	void DoDataExchange(CDataExchange* pDx, CPipeAndNode* pPnN, CStartPPDoc* pDoc);
#ifdef WX
    void OnPropertyGridChange(wxPropertyGridEvent &event);
#else
	LRESULT OnPropChange(WPARAM wParam, LPARAM lParam);
#endif
	CPipeAndNode* m_pPnN;
	CPipeAndNode m_PnN;
	//	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnPropMert();
	afx_msg void OnUpdatePropMert(CCmdUI* pCmdUI);
	afx_msg void OnPropSk();
	afx_msg void OnUpdatePropSk(CCmdUI* pCmdUI);
	afx_msg void OnPropNapr();
	afx_msg void OnUpdatePropNapr(CCmdUI* pCmdUI);
	afx_msg void OnPropOtvSv();
	afx_msg void OnUpdatePropOtvSv(CCmdUI* pCmdUI);
	afx_msg void OnPropOtvIz();
	afx_msg void OnUpdatePropOtvIz(CCmdUI* pCmdUI);
	afx_msg void OnPropArm();
	afx_msg void OnUpdatePropArm(CCmdUI* pCmdUI);
protected:
	CMFCPropertyGridProperty* AddPGroup(UINT idName, DWORD_PTR dwData, BOOL bIsValueList = FALSE);
	CMFCPropertyGridProperty* AddProp(CMFCPropertyGridProperty* pGroup, UINT idName, _variant_t val, UINT idComment, DWORD_PTR dwData, LPCTSTR pszValidChars = nullptr, void* pData = nullptr);
	void SearchVal(void* pData, DWORD_PTR& dwData, _variant_t& val, float& searchVal, float eps = 0.001f);
	void SearchValField(void* pData, const DWORD_PTR& dwData, _variant_t& val, float CPipeAndNode::* searchVal, float eps = 0.001f);
	void DelGroup(DWORD_PTR dwData);
	void AddOtvod(UINT* arrIDS);
	static void ToFloat(const COleVariant& val, float& x);
	void ToFloat(const COleVariant& val, DWORD_PTR dwData);
	static void ToFloat(COleVariant& val);
	static void ToStr(const COleVariant& val, CStringA& x);
	void ToStr(const COleVariant& val, DWORD_PTR dwData);
	void SavePropExpandState(CMFCPropertyGridProperty* pProp);
	std::map<DWORD_PTR, BOOL> m_mapExpanded;
	std::multimap<DWORD_PTR, float *> m_mapProp;
	std::multimap<DWORD_PTR, float> m_mapPropVal;
	std::set<DWORD_PTR> m_setPGroups;
	void FillNodeForces(void);
	int m_nNodesSelected;
	int m_nPipesSelected;
	int m_nPipeNo;
};



