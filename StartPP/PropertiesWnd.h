#pragma once
#include "stdafx.h"
#include "PipeAndNode.h"
#include "PipesSet.h"
#include "ArmatSet.h"
#include "CPropValued.h"
#include <set>

#include <wx/propgrid/manager.h>
#include <wx/propgrid/propgrid.h>

class wxToolBar;
// typedef wxPropertyGridManager CMFCPropertyGridCtrl;
// stypedef wxPGProperty CMFCPropertyGridProperty;
typedef wxWindow CWnd;
class CCmdUI;
class CDataExchange;
typedef wxVariant _variant_t;
typedef wxVariant COleVariant;
//typedef unsigned long DWORD;
#define afx_msg
class CMFCPropertyGridProperty : public wxPGProperty
{
public:
	DWORD_PTR GetData() const;
	virtual ~CMFCPropertyGridProperty();
};

class CMFCPropertyGridCtrl : public wxPropertyGridManager
{
public:
	CMFCPropertyGridCtrl(wxWindow* parent,
	                     wxWindowID winid = wxID_ANY,
	                     const wxPoint& pos = wxDefaultPosition,
	                     const wxSize& size = wxDefaultSize,
	                     long style = wxTAB_TRAVERSAL | wxNO_BORDER,
	                     const wxString& name = wxString(_T("PropWnd")));

	CMFCPropertyGridProperty* FindItemByData(DWORD dwData);
	CMFCPropertyGridProperty* GetCurSel() const;
	void DeleteProperty(CMFCPropertyGridProperty* pProp);
	void DeleteGroup(DWORD dwData);
};

class CPropertiesToolBar : public CMFCToolBar
{
};

class CStartPPDoc;

enum EPropMode { E_NONE, E_PIPE, E_NODE };

class CPropertiesWnd : public CDockablePane, public CPropValued
{
    // Создание
public:
    CPropertiesWnd();
    CPropertiesWnd(wxWindow* parent,
                   wxWindowID winid = wxID_ANY,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                   const wxString& name = wxString(_T("PropWnd")));
//    void AdjustLayout(); // override;
	CMFCPropertyGridCtrl* GetPropList() { return m_pwndPropList; }
    // Атрибуты
	void OnPropertyGridChange(wxPropertyGridEvent& event);

public:
protected:
    // CFont m_fntPropList;
    CComboBox* m_pwndObjectCombo;
    // CPropertiesToolBar m_wndToolBar;
    CMFCPropertyGridCtrl* m_pwndPropList;

    // Реализация
public:
    virtual ~CPropertiesWnd();

protected:
    int Create();
    void OnSetFocus(wxFocusEvent& evt);
//    afx_msg void OnExpandAllProperties();
//    afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
    afx_msg void OnLBChange(wxCommandEvent& event);
    afx_msg void OnLBChanged();

    DECLARE_MESSAGE_MAP()
    void FillPipeProps();
    void FillNodeProps();

//    void InitPropList();
//    void SetPropListFont();

    CAngles a1, a2;

    //CMFCPropertyGridProperty* m_propX;
    //CMFCPropertyGridProperty* m_propY;
    //CMFCPropertyGridProperty* m_propZ;
    //CMFCPropertyGridProperty* m_propLen;
    //CMFCPropertyGridProperty* m_propLPlan;
    //CMFCPropertyGridProperty* m_propAPlan;
    //CMFCPropertyGridProperty* m_propAPlanRel;
    //CMFCPropertyGridProperty* m_propAProf;
    //CMFCPropertyGridProperty* m_propUklon;

    //CMFCPropertyGridProperty* m_propNagr;
    CMFCPropertyGridProperty* m_pIzdProp;
	//CMFCPropertyGridProperty* m_pOporProp;
	//CMFCPropertyGridProperty* m_pRsGgProp;

	void OnRecalcXYZ(wxCommandEvent& event);
    void RecalcXYZ();

    int m_nComboHeight;

public:
    EPropMode m_PropMode;
    EPropMode m_oPropMode;
    void DoDataExchange(CDataExchange* pDx, CPipeAndNode* pPnN, CStartPPDoc* pDoc);
	void OnPropChange(CMFCPropertyGridProperty *pProp);

	void Clear();

	CPipeAndNode m_PnN;
    //	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    afx_msg void OnPropMert(wxCommandEvent& event);
    afx_msg void OnUpdatePropMert(wxUpdateUIEvent& event);
    afx_msg void OnPropSk(wxCommandEvent& event);
    afx_msg void OnUpdatePropSk(wxUpdateUIEvent& event);
    afx_msg void OnPropNapr(wxCommandEvent& event);
    afx_msg void OnUpdatePropNapr(wxUpdateUIEvent& event);
    afx_msg void OnPropOtvSv(wxCommandEvent& event);
    afx_msg void OnUpdatePropOtvSv(wxUpdateUIEvent& event);
    afx_msg void OnPropOtvIz(wxCommandEvent& event);
    afx_msg void OnUpdatePropOtvIz(wxUpdateUIEvent& event);
    afx_msg void OnPropArm(wxCommandEvent& event);
    afx_msg void OnUpdatePropArm(wxUpdateUIEvent& event);

protected:
    CMFCPropertyGridProperty* AddPGroup(wxString strName,
                                        DWORD_PTR dwData,
                                        BOOL bIsValueList = FALSE,
                                        CMFCPropertyGridProperty* pParent = nullptr);
    CMFCPropertyGridProperty* CheckExistingProp(CMFCPropertyGridProperty* pGroup,
                                                wxString strName,
                                                _variant_t & val,
                                                wxString strComment,
                                                DWORD_PTR dwData,
                                                LPCTSTR pszValidChars = nullptr,
                                                void* pData = nullptr);
    CMFCPropertyGridProperty* AddProp(CMFCPropertyGridProperty* pGroup,
                                      wxString strName,
                                      _variant_t val,
                                      wxString strComment,
                                      DWORD_PTR dwData,
                                      LPCTSTR pszValidChars = nullptr,
                                      void* pData = nullptr);
    CMFCPropertyGridProperty* AddEnumProp(CMFCPropertyGridProperty* pGroup,
                                          wxString strName,
                                          _variant_t val,
                                          wxString strComment,
                                          DWORD_PTR dwData,
                                          LPCTSTR pszValidChars = nullptr,
                                          void* pData = nullptr,
                                          std::vector<CString> arrOptions = std::vector<CString>(),
										 bool bExact=false);
    CMFCPropertyGridProperty* AddMaterialProp(CMFCPropertyGridProperty* pGroup,
                                              wxString strName,
                                              _variant_t val,
                                              wxString strComment,
                                              DWORD_PTR dwData,
                                              LPCTSTR pszValidChars = nullptr,
                                              void* pData = nullptr);
    void SearchVal(void* pData, DWORD_PTR& dwData, _variant_t& val, float& searchVal, float eps = 0.001f);
    void SearchValField(void* pData,
                        const DWORD_PTR& dwData,
                        _variant_t& val,
                        float CPipeAndNode::*searchVal,
                        float eps = 0.001f);
//    void DelGroup(DWORD_PTR dwData) const;
    void AddOtvod(UINT* arrIDS);

	void SavePropExpandState(CMFCPropertyGridProperty* pProp);
    std::map<DWORD_PTR, BOOL> m_mapExpanded;
	std::set<DWORD_PTR> m_setPGroups;
    void FillNodeForces(void);
    int m_nNodesSelected;
    int m_nPipesSelected;
    int m_nPipeNo;

};
