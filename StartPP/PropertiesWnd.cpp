#include "stdafx.h"

#include "PropertiesWnd.h"

#include "StartPPDoc.h"
#include "PipeAndNode.h"
#include "PipesSet.h"
#include "TroinicsSet.h"
#include "Material.h"
#include <math.h>
#include "Strings.h"
#include "wx/arrstr.h"
#include <wx/xrc/xmlres.h>
#include "wxcrafter.h"
#include <wx/propgrid/advprops.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

enum
{
    E_OSIX = 1,
    E_OSIY,
    E_OSIZ,
    E_LEN_PLAN,
    E_LEN_TOTAL,
    E_ANG_PLAN_ABS,
    E_ANG_PLAN_REL,
    E_ANG_PROF,
    E_UKLON,
    E_DIAM,
    E_MATERIAL,
    E_NTOS,
    E_RTOS,
    E_RADA,
    E_DABI,
    E_RATE,
    E_VETR,
    E_VEIZ,
    E_VEPR,
    E_KOPE,
    E_KOPR,
    E_NAGV,
    E_NAGX,
    E_NAGY,
    E_NAGZ,
    E_DIAM_KOZHUX,
    E_VIZA_BEG,
    E_SHTR,
    E_GRTYPE_UP,
    E_GRTYPE_OSN,
    E_GRTYPE_SIDE,
    E_VIZA_END,
    E_OS_TR_BEG,
    E_OS_TR_END,

    E_PIPE_TYPE = 50,

    E_IZD_TYPE = 100,
    E_OPOR_TYPE,
    E_DEF_TYPE,
    E_UOP_NTG,
    E_UOP_IZM_NAGR,
    E_UOP_KZAP,
    E_UOP_PODD_US,
    E_UOP_PODATL,

    E_ZHP_LEN_TYAGI,

    E_ARM_LEN = 110,
    E_ARM_VES,

    E_RAOT = 134,
    E_VESOTV,
    E_MATOTV,
    E_NOTO_OTV,
    E_RATO_OTV,
    E_RAOT_SV = 160,
    E_VESOTV_SV,
    E_MATOTV_SV,
    E_NOTO_SV,
    E_RATO_SV,

    E_RAOT_OF = 170,
    E_VESOTV_OF,
    E_MATOTV_OF,
    E_NOTO_OF,
    E_RATO_OF,
    E_KO_SEFF = 139,
    E_KO_PODATL,
    E_KO_OS_HOD,
    E_KU_PODATL,
    E_KU_LEN,
    E_TR_MAT,
    E_TR_VES,
    E_TR_NOTO_MAG,
    E_TR_RATO_MAG,
    E_TR_LEN_MAG,
    E_TR_DIAM_OTV,
    E_TR_NOTO_OTV,
    E_TR_RATO_OTV,
    E_TR_VYS_OTV,
    E_TR_NOTO_NAKL,
    E_TR_SHIR_NAKL,
    E_VR_KOPR,
    E_VR_NOTO_NAKL,
    E_VR_SHIR_NAKL,

    E_DEF_VAL_RAST,
    E_DEF_VAL_SG,

    E_SK_KOTR,
    E_NP_KOTR,

    E_UZ_SILVES=300,
    E_UZ_VES_MOMX,
    E_UZ_VES_MOMY,
    E_UZ_SILX,
    E_UZ_SILY,
    E_UZ_SILZ,
    E_UZ_MOMX,
    E_UZ_MOMY,
    E_UZ_MOMZ,

    E_NAYZ = 501,
    E_KOYZ,

    E_GROUP_OSN = 1000,
    E_GROUP_ADDITIONAL,
    E_GROUP_ADD_NAGR,
    E_GROUP_GRUNT,
    E_GROUP_GLUB,
    E_GROUP_VIZA,
    E_GROUP_GRUNT_TYPE,

    E_GROUP_GEOM = 1020,
    E_GROUP_VESA = 1010,

    E_END_NODE = 2000,
    E_GROUP_IZD,
    E_GROUP_OTVIZ,
    E_GROUP_OTVSV,
    E_GROUP_OTVFL,
    E_GROUP_KO,
    E_GROUP_KU,
    E_GROUP_TR,
    E_GROUP_VREZKA,
    E_GROUP_MO,
    E_GROUP_SK,
    E_GROUP_NP,
    E_GROUP_UPR_OP,
    E_GROUP_PD_ZHESTK,
    E_GROUP_DEF_TYPE_RS,
    E_GROUP_DEF_TYPE_SG,
    E_GROUP_NAGR,
    E_GROUP_NAGR_VES_ADD,
    E_GROUP_NAGR_NONVES_ADD,
    E_GROUP_NAKL
};

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

DWORD_PTR CMFCPropertyGridProperty::GetData()
{
	return (DWORD_PTR)GetClientData();
}

CMFCPropertyGridProperty::~CMFCPropertyGridProperty()
{
	    
}

CMFCPropertyGridCtrl::CMFCPropertyGridCtrl(wxWindow* parent, wxWindowID winid, const wxPoint& pos, const wxSize& size, long style, const wxString& name): wxPropertyGridManager(parent, winid, pos, size, style, name)
{
}

CMFCPropertyGridProperty* CMFCPropertyGridCtrl::FindItemByData(DWORD dwData)
{
	for(auto it =  GetGrid()->GetIterator(); *it; it++)
		if (DWORD_PTR((*it)->GetClientData()) == dwData)
		{
			if ((*it)->HasFlag(wxPG_PROP_BEING_DELETED))
			{
				(*it)->SetClientData(nullptr);
				return nullptr;
			}
			return static_cast<CMFCPropertyGridProperty*>(*it);
		}
	return nullptr;
}

CMFCPropertyGridProperty* CMFCPropertyGridCtrl::GetCurSel() const
{
	return static_cast<CMFCPropertyGridProperty*>(GetSelection());
}

void CMFCPropertyGridCtrl::DeleteProperty(CMFCPropertyGridProperty* pProp)
{
	if (GetSelection() == pProp)
		SelectProperty(GetGrid()->GetRoot()->Item(0));
	pProp->ChangeFlag(wxPG_PROP_BEING_DELETED, true);
	wxPropertyGridManager::DeleteProperty(pProp);
}

void CMFCPropertyGridCtrl::DeleteGroup(DWORD dwData)
{
	CMFCPropertyGridProperty *pProp = FindItemByData(dwData);
	if (pProp)
	{
		int nCount = pProp->GetChildCount();
		for (int i=nCount-1; i>=0; i--)
		{
			CMFCPropertyGridProperty* pItem = static_cast<CMFCPropertyGridProperty*>(pProp->Item(i));
			if (pItem->GetChildCount()>0)
				DeleteGroup(pItem->GetData());
			else
				DeleteProperty(pItem);
		}
		DeleteProperty(pProp);
	}
}

CPropertiesWnd::CPropertiesWnd()
	: m_pwndObjectCombo(nullptr), m_pwndPropList(nullptr), m_propLPlan(nullptr)
	, m_propAPlanRel(nullptr)
	, m_pIzdProp(nullptr)
	, m_pOporProp(nullptr)
	, m_pRsGgProp(nullptr)
	, m_pDoc(nullptr)
	, m_PropMode(E_NONE)
	, m_oPropMode(E_NONE)
	, m_nNodesSelected(0)
	, m_nPipesSelected(0)
	, m_nPipeNo(0)
{
	m_nComboHeight = 0;
	m_pPnN = nullptr;
	m_propX = m_propY = m_propZ = m_propLen = m_propAPlan = m_propAProf = m_propUklon = nullptr;
	m_propNagr = nullptr;
}

CPropertiesWnd::CPropertiesWnd(wxWindow* parent,
                               wxWindowID winid,
                               const wxPoint& pos,
                               const wxSize& size,
                               long style,
                               const wxString& name)
	: CDockablePane(parent, winid, pos, size, style, name)
{
	CPropertiesWnd();
	Create();
}

CPropertiesWnd::~CPropertiesWnd()
{
//	this->Disconnect(MainFrameBaseClass::wxID_PROP_MERT, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropMert));
//	this->Disconnect(MainFrameBaseClass::wxID_PROP_SK, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropSk));
//	this->Disconnect(MainFrameBaseClass::wxID_PROP_NAPR, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropNapr));
//	this->Disconnect(MainFrameBaseClass::wxID_PROP_OTV_SV, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropOtvSv));
//	this->Disconnect(MainFrameBaseClass::wxID_PROP_OTV_IZ, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropOtvIz));
//	this->Disconnect(MainFrameBaseClass::wxID_PROP_ARMAT, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropArm));

}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)

	EVT_PG_CHANGING(-1, CPropertiesWnd::OnPropertyGridChange)
	EVT_SET_FOCUS(CPropertiesWnd::OnSetFocus)
	EVT_CHOICE(ID_PropCombobox, CPropertiesWnd::OnLBChange)
	EVT_MENU(ID_RecalcXYZ, CPropertiesWnd::OnRecalcXYZ)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_PROP_MERT, CPropertiesWnd::OnUpdatePropMert)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_PROP_SK, CPropertiesWnd::OnUpdatePropSk)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_PROP_NAPR, CPropertiesWnd::OnUpdatePropNapr)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_PROP_OTV_SV, CPropertiesWnd::OnUpdatePropOtvSv)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_PROP_OTV_IZ, CPropertiesWnd::OnUpdatePropOtvIz)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_PROP_ARMAT, CPropertiesWnd::OnUpdatePropArm)
	
	/*
	        ON_WM_SETTINGCHANGE()
	        ON_CBN_SELCHANGE(1,OnLBChange)
	        ON_COMMAND(ID_PROP_MERT, &CPropertiesWnd::OnPropMert)
	        ON_UPDATE_COMMAND_UI(ID_PROP_MERT, &CPropertiesWnd::OnUpdatePropMert)
	        ON_COMMAND(ID_PROP_SK, &CPropertiesWnd::OnPropSk)
	        ON_UPDATE_COMMAND_UI(ID_PROP_SK, &CPropertiesWnd::OnUpdatePropSk)
	        ON_COMMAND(ID_PROP_NAPR, &CPropertiesWnd::OnPropNapr)
	        ON_UPDATE_COMMAND_UI(ID_PROP_NAPR, &CPropertiesWnd::OnUpdatePropNapr)
	        ON_COMMAND(ID_PROP_OTV_SV, &CPropertiesWnd::OnPropOtvSv)
	        ON_UPDATE_COMMAND_UI(ID_PROP_OTV_SV, &CPropertiesWnd::OnUpdatePropOtvSv)
	        ON_COMMAND(ID_PROP_OTV_IZ, &CPropertiesWnd::OnPropOtvIz)
	        ON_UPDATE_COMMAND_UI(ID_PROP_OTV_IZ, &CPropertiesWnd::OnUpdatePropOtvIz)
	        ON_COMMAND(ID_PROP_ARM, &CPropertiesWnd::OnPropArm)
	        ON_UPDATE_COMMAND_UI(ID_PROP_ARM, &CPropertiesWnd::OnUpdatePropArm)
	*/
END_MESSAGE_MAP()


int CPropertiesWnd::Create()
{
	int style = // default style
	    //wxPG_BOLD_MODIFIED | 
	    // wxPG_AUTO_SORT |
	    // wxPG_HIDE_MARGIN|wxPG_STATIC_SPLITTER |
	    // wxPG_TOOLTIPS |
	    // wxPG_HIDE_CATEGORIES |
	    // wxPG_LIMITED_EDITING |
	    wxPG_TOOLBAR ;//| wxPG_DESCRIPTION;

	// default extra style
	int extraStyle = wxPG_EX_MODE_BUTTONS /*| wxPG_EX_MULTIPLE_SELECTION*/;
	//| wxPG_EX_AUTO_UNSPECIFIED_VALUES
	//| wxPG_EX_GREY_LABEL_WHEN_DISABLED
	//| wxPG_EX_NATIVE_DOUBLE_BUFFERING
	//| wxPG_EX_HELP_AS_TOOLTIPS
	wxBoxSizer* pBoxSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(pBoxSizer);
	m_pwndObjectCombo = new CComboBox(this, ID_PropCombobox);
	pBoxSizer->Add(m_pwndObjectCombo, 0, wxALL | wxEXPAND, 5);
	m_pwndPropList = new CMFCPropertyGridCtrl(this, PGID, wxDefaultPosition, wxDefaultSize, style);
	m_pwndPropList->SetExtraStyle(extraStyle);
	pBoxSizer->Add(m_pwndPropList, 1, wxALL | wxEXPAND, 5);
	pBoxSizer->Fit(this);
	wxToolBar* pToolBar = m_pwndPropList->GetToolBar();
#ifdef __WXMAC__
	//pToolBar->SetBackgroundColour(*wxWHITE);
#endif
	pToolBar->AddSeparator();
	pToolBar->AddTool(MainFrameBaseClass::wxID_PROP_MERT, _("Мертвая опора"), wxXmlResource::Get()->LoadBitmap(wxT("PropMo")), wxNullBitmap, wxITEM_CHECK, _("Мертвая опора"), wxT(""), NULL);
	pToolBar->AddTool(MainFrameBaseClass::wxID_PROP_SK, _("Скользящая опора"), wxXmlResource::Get()->LoadBitmap(wxT("PropSk")), wxNullBitmap, wxITEM_CHECK, _("Скользящая опора"), wxT(""), NULL);
	pToolBar->AddTool(MainFrameBaseClass::wxID_PROP_NAPR, _("Направляющая опора"), wxXmlResource::Get()->LoadBitmap(wxT("PropNapr")), wxNullBitmap, wxITEM_CHECK, _("Направляющая опора"), wxT(""), NULL);
	pToolBar->AddSeparator();
	pToolBar->AddTool(MainFrameBaseClass::wxID_PROP_OTV_SV, _("Отвод сварной"), wxXmlResource::Get()->LoadBitmap(wxT("PropOtvSv")), wxNullBitmap, wxITEM_CHECK, _("Отвод сварной"), wxT(""), NULL);
	pToolBar->AddTool(MainFrameBaseClass::wxID_PROP_OTV_IZ, _("Отвод изогнутый"), wxXmlResource::Get()->LoadBitmap(wxT("PropOtvIz")), wxNullBitmap, wxITEM_CHECK, _("Отвод изогнутый"), wxT(""), NULL);
	pToolBar->AddTool(MainFrameBaseClass::wxID_PROP_ARMAT, _("Арматура"), wxXmlResource::Get()->LoadBitmap(wxT("PropArm")), wxNullBitmap, wxITEM_CHECK, _("Арматура"), wxT(""), NULL);
	pToolBar->Realize();
//	this->Connect(MainFrameBaseClass::wxID_PROP_MERT, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropMert));
//	this->Connect(MainFrameBaseClass::wxID_PROP_SK, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropSk));
//	this->Connect(MainFrameBaseClass::wxID_PROP_NAPR, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropNapr));
//	this->Connect(MainFrameBaseClass::wxID_PROP_OTV_SV, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropOtvSv));
//	this->Connect(MainFrameBaseClass::wxID_PROP_OTV_IZ, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropOtvIz));
//	this->Connect(MainFrameBaseClass::wxID_PROP_ARMAT, wxEVT_MENU, wxCommandEventHandler(CPropertiesWnd::OnPropArm));

	return 0;
}



class CMenu;
class CCmdTarget;



void CPropertiesWnd::OnSetFocus(wxFocusEvent& evt)
{
	evt.Skip();
}



static inline float DegToRad(float x)
{
	return x * atan(1.0f) / 45;
}

static inline float RadToDeg(float x)
{
	return x * 45 / atan(1.0f);
}

void CPropertiesWnd::CAngles::calc_angles(float x, float y, float z)
{
	l_gen = sqrt(x * x + y * y + z * z);
	l_plan = sqrt(x * x + y * y);
	if(fabs(x) + fabs(y) < 0.001f)
	{
		a_plan = 0;
		a_prof = (z > 0) ? 90.0f : -90.0f;
		if(fabs(z) < 0.001f)
			a_prof = 0;
		uklon = 0;
	}
	else
	{
		a_prof = RadToDeg(atan(z / l_plan));
		if(fabs(x) < 0.001)
		{
			a_plan = (y > 0) ? 90.0f : -90.0f;
		}
		else
		{
			a_plan = RadToDeg(atan(y / x));
			if(x < 0)
				a_plan = (y < 0) ? -180.0f + a_plan : 180.0f + a_plan;
		}
		if(fabs(z) < 0.001f)
			uklon = 0;
		else
			uklon = z / l_plan * 1000;
	}
}

void CPropertiesWnd::CAngles::GetRelAngle(CStartPPDoc* m_pDoc, CPipeAndNode* pPnN)
{
	CPipeAndNode* prevPnN = m_pDoc->GetPrevPnN(int(pPnN->m_NAYZ));
	while(prevPnN && fabs(prevPnN->m_OSIX) + fabs(prevPnN->m_OSIY) < 1e-3f)
		prevPnN = m_pDoc->GetPrevPnN(int(prevPnN->m_NAYZ));
	if(prevPnN)
	{
		float x = prevPnN->m_OSIX;
		float y = prevPnN->m_OSIY;
		// float z=prevPnN->m_OSIZ;
		if(fabs(x) + fabs(y) < 0.001f)
			a_plan_prev = 0;
		else if(fabs(x) < 0.001)
		{
			a_plan_prev = (y > 0) ? 90.0f : -90.0f;
		}
		else
		{
			a_plan_prev = RadToDeg(atan(y / x));
			if(x < 0)
				a_plan_prev = (y < 0) ? -180.0f + a_plan_prev : 180.0f + a_plan_prev;
		}
	}
	else
		a_plan_prev = 0;
	a_plan_rel = a_plan - a_plan_prev;
	if(a_plan_rel > 180)
		a_plan_rel = a_plan_rel - 360;
	else if(a_plan_rel < -180)
		a_plan_rel = a_plan_rel + 360;
	if(fabs(pPnN->m_OSIX) + fabs(pPnN->m_OSIY) < 1e-3f)
		a_plan_rel = 0;
}

float Round(float x, int N)
{
	float f = 1.0f;
	for(int i = 0; i < N; i++)
		f *= 10.0f;
	return x > 0 ? int(x * f + 0.5f) / f : int(x * f - 0.5f) / f;
}

CString S_Round(float x, int N)
{
	CString str;
	str = str.Format(_T("%d"), N);
	str = CString(_T("%.")) + str + CString(_T("f"));
	CString str1;
	str1 = str1.Format(str, Round(x, N));
	return str1;
}

_variant_t S_RoundV(float x, int N)
{
	return _variant_t(S_Round(x, N));
}


void CPropertiesWnd::SavePropExpandState(CMFCPropertyGridProperty* pProp)
{
	if(pProp->GetChildCount() == 0)
		return;
	DWORD_PTR dwData = (DWORD_PTR)pProp->GetClientData();
	m_mapExpanded[dwData] = pProp->IsExpanded();
	int nSubitems = pProp->GetChildCount();
	for(int i = 0; i < nSubitems; i++)
	{
		CMFCPropertyGridProperty* pSubItem = static_cast<CMFCPropertyGridProperty*>(pProp->Item(i));
		if(pSubItem->GetChildCount() != 0)
			SavePropExpandState(pSubItem);
	}
}

#define AFX_PROP_HAS_SPIN 0x4
/*
class CMFCSpinButtonCtrlMy : public CMFCSpinButtonCtrl
{
public:
        BOOL GetIsButtonUp() const
        {
                return m_bIsButtonPressedUp;
        }

        BOOL GetIsButtonDown() const
        {
                return m_bIsButtonPressedDown;
        }
};

class CMFCPropertyGridProperty1: public CMFCPropertyGridProperty
{
public:
        CMFCPropertyGridProperty1(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = nullptr,
DWORD_PTR dwData = 0,
                                  LPCTSTR lpszEditMask = nullptr, LPCTSTR lpszEditTemplate = nullptr, LPCTSTR
lpszValidChars = nullptr) : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask,
lpszEditTemplate, lpszValidChars)
        {
        }

        // Group constructor
        CMFCPropertyGridProperty1(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE) :
                CMFCPropertyGridProperty(strGroupName, dwData, bIsValueList)
        {
        }

        void SetValue(const COleVariant& varValue) override
        {
                BOOL bInPlaceEdit = m_bInPlaceEdit;
                if (bInPlaceEdit)
                {
                        OnEndEdit();
                }

                m_varValue = varValue;
                Redraw();

                if (bInPlaceEdit)
                {
                        ASSERT_VALID(m_pWndList);
                        m_pWndList->EditItem(this);
                }
        }

        void EnableSpinControl(BOOL bEnable, int nMin, int nMax)
        {
                m_nMinValue = nMin;
                m_nMaxValue = nMax;

                if (bEnable)
                {
                        m_dwFlags |= AFX_PROP_HAS_SPIN;
                }
                else
                {
                        m_dwFlags &= ~AFX_PROP_HAS_SPIN;
                }
        }

        CMFCSpinButtonCtrlMy* GetSpinCtrl() const
        {
                return reinterpret_cast<CMFCSpinButtonCtrlMy *>(m_pWndSpin);
        }

        BOOL IsSubItem(CMFCPropertyGridProperty* pProp) const
        {
                return CMFCPropertyGridProperty::IsSubItem(pProp);
        }
};
*/
#define CMFCPropertyGridProperty1 CMFCPropertyGridProperty


void CPropertiesWnd::DoDataExchange(CDataExchange* pDx, CPipeAndNode* pPnN, CStartPPDoc* pDoc)
{
	if(pPnN == nullptr)
	{
		m_pPnN = nullptr;
		m_pwndPropList->Clear();
		m_pwndPropList->Refresh();
		return;
	}
	if(pDx->m_bSaveAndValidate)
	{
		//pDx->m_bEditLastControl = FALSE;
		//*pPnN = m_PnN;
		// if (m_propNagr!= nullptr)
		// m_bExpandNagr = m_propNagr->IsExpanded();
		for(auto it = m_pwndPropList->GetGrid()->GetIterator(); *it; it.Next(false))
			SavePropExpandState(static_cast<CMFCPropertyGridProperty*>(*it));
		return;
	}
	m_pDoc = pDoc;
	m_pPnN = pPnN;
	// m_pwndPropList->RemoveAll();
	CString strPipe;
	m_oPropMode = m_PropMode;
	if(pDx->m_pDlgWnd != this)
	{
		int nCurSel = m_pwndObjectCombo->GetCurrentSelection();
		if(m_PropMode == E_PIPE)
			nCurSel = 0;
		if(m_PropMode == E_NODE)
			nCurSel = 1;
		// m_PropMode = E_NONE;
		m_pwndObjectCombo->Clear();
		if(m_pDoc->vecSel.size() < 2)
		{
			strPipe = strPipe.Format(LoadStr(IDS_FORMAT_PIPE), m_pPnN->m_NAYZ, m_pPnN->m_KOYZ);
			m_pwndObjectCombo->AppendString(strPipe);
			strPipe = strPipe.Format(LoadStr(IDS_FORMAT_NODE), m_pPnN->m_KOYZ);
			m_pwndObjectCombo->AppendString(strPipe);
			m_pwndObjectCombo->SetSelection(nCurSel);
			m_nNodesSelected = m_nPipesSelected = 1;
		}
		else
		{
			m_pwndObjectCombo->AppendString(LoadStr(IDS_FORMAT_MANY_PIPES));
			m_nNodesSelected = m_nPipesSelected = 0;
			for(auto& x : m_pDoc->vecSel)
			{
				if(x.SelNAYZ == x.SelKOYZ)
				{
					strPipe = strPipe.Format(IDS_FORMAT_NODE2, x.SelNAYZ);
					m_nNodesSelected++;
				}
				else
				{
					strPipe = strPipe.Format(LoadStr(IDS_FORMAT_PIPE2), x.SelNAYZ, x.SelKOYZ);
					m_nPipesSelected++;
				}
				m_pwndObjectCombo->AppendString(strPipe);
			}
			m_pwndObjectCombo->SetSelection(0);
		}
	}
	m_mapProp.clear();
	m_mapPropVal.clear();
	m_setPGroups.clear();
	m_nPipeNo = 0;
	if(m_oPropMode == E_PIPE)
	{
#if 0
		CMFCPropertyGridProperty* pProp = m_pwndPropList->FindItemByData(E_GROUP_ADDITIONAL);
		if(pProp)
		{
			// CMFCPropertyGridProperty* pFocus = m_pwndPropList->GetCurrentPage();
			// if (pFocus && dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->IsSubItem(pFocus))
			//	m_pwndPropList->SetCurSel(nullptr,FALSE);
			m_pwndPropList->DeleteProperty(pProp);
		}
#else
		//m_pwndPropList->DeleteGroup(E_GROUP_ADDITIONAL);
#endif
		for(const CPipeAndNode& x : m_pDoc->m_pipes.m_vecPnN)
			if(m_pDoc->vecSel.Contains(x.m_NAYZ, x.m_KOYZ))
			{
				m_pPnN = const_cast<CPipeAndNode*>(&x);
				m_nPipeNo++;
				FillPipeProps();
			}
	}
	else
	{
#if 0
		m_pwndPropList->DeleteGroup(E_GROUP_NAGR);
#endif
		if (m_nNodesSelected < 2)
		{
			for (auto& x : m_pDoc->m_pipes.m_vecPnN)
				if (m_pDoc->vecSel.Contains(x.m_KOYZ, x.m_KOYZ))
				{
					m_pPnN = const_cast<CPipeAndNode*>(&x);
					m_nPipeNo++;
					FillNodeProps();
				}
		}
        //if (pProp)
        //	m_pwndPropList->Insert(wxPGPropArg((wxPGProperty*)nullptr),-1, pProp);
		for(auto& x : m_pDoc->m_pipes.m_vecPnN)
			if(m_pDoc->vecSel.Contains(x.m_KOYZ, x.m_KOYZ))
			{
				m_pPnN = const_cast<CPipeAndNode*>(&x);
				FillNodeForces();
			}
	}
	std::set<CMFCPropertyGridProperty*> setDeleted;
	for (;;)
	{
		bool bPropDeleted = false;
		wxPGProperty *pRoot = m_pwndPropList->GetGrid()->GetRoot();
		for(size_t i=0;i<pRoot->GetChildCount(); i++)
		{
			CMFCPropertyGridProperty* pProp = static_cast<CMFCPropertyGridProperty*>(pRoot->Item(i));
			if(m_setPGroups.find((DWORD_PTR)pProp->GetClientData()) == m_setPGroups.end())
			{
				if (setDeleted.find(pProp)==setDeleted.end() && !pProp->HasFlag(wxPG_PROP_BEING_DELETED))
				{
					m_pwndPropList->DeleteProperty(pProp);
					setDeleted.insert(pProp);	
					bPropDeleted = true;
					break;
				}
			}
		}
	    if (!bPropDeleted)
			break;
	}

	for(auto c : m_mapExpanded)
	{
		CMFCPropertyGridProperty* p = m_pwndPropList->FindItemByData(c.first);
		if(p)
		{
			if (c.second)
				m_pwndPropList->Expand(p);
			else
				m_pwndPropList->Collapse(p);
		}
	}
	m_pwndPropList->Refresh();
}

static bool bAddGroup;

CMFCPropertyGridProperty*
CPropertiesWnd::AddPGroup(wxString strName, DWORD_PTR dwData, BOOL bIsValueList, CMFCPropertyGridProperty* pParent)
{
	UNREFERENCED_PARAMETER(bIsValueList);
	m_setPGroups.insert(dwData);
	bAddGroup = false;
	CMFCPropertyGridProperty* p = m_pwndPropList->FindItemByData(dwData);
	if(p)
	{
		p->SetName(strName);
		return p;
	}
	bAddGroup = true;
	p = static_cast<CMFCPropertyGridProperty*>(static_cast<wxPGProperty*>(new wxStringProperty(strName, wxPG_LABEL, bIsValueList ? wxT("<composed>") : wxEmptyString  )));
	p->SetClientData((void*)dwData);
	if(pParent)
		m_pwndPropList->AppendIn(pParent, p);
	else
		m_pwndPropList->Append(p);

	return p;
}

static bool bAdd = true;

static inline bool FCompare(float x1, float x2, float eps = 0.001f)
{
	return fabs(x1 - x2) < eps;
}

CMFCPropertyGridProperty* CPropertiesWnd::AddEnumProp(CMFCPropertyGridProperty* pGroup,
        wxString strName,
        _variant_t val,
        wxString strComment,
        DWORD_PTR dwData,
        LPCTSTR pszValidChars,
        void* pData,
        std::vector<CString> arrOptions,
		bool bExact)
{
    wxPGChoices soc;
	wxArrayString arr(arrOptions.size(), &arrOptions[0]);
	int index =0;
	for(UINT i = 0; i < arrOptions.size(); i++)
	{
		soc.Add(arrOptions[i],i);
		if (arrOptions[i]==val.GetString())
			index = i;
	}
	wxEnumProperty* p = (wxEnumProperty*)CheckExistingProp(pGroup,strName,val,strComment,dwData,pszValidChars,pData);
	if (p)
	{
		p->SetChoices(soc);
		//wxVariant var(index);
		if (!p->HasFlag(wxPG_PROP_BEING_DELETED))
		{
			if (m_nPipeNo == m_nPipesSelected)
			{
				if (dynamic_cast<wxEditEnumProperty*>(p))
					p->SetValue(val);
				else
					p->SetValue(wxVariant(index));
			}
		}
		return static_cast<CMFCPropertyGridProperty*>(static_cast<wxPGProperty*>(p));
	}
	p = bExact ? new wxEnumProperty(strName, wxPG_LABEL, arr,wxArrayInt(),index) : new wxEditEnumProperty(strName, wxPG_LABEL, soc, val.GetString()/*index*/);
	p->SetHelpString(strComment);
	p->SetClientData((void*)dwData);
	if (pGroup)
		m_pwndPropList->AppendIn(pGroup, p);
	else
		m_pwndPropList->Append(p);
	return static_cast<CMFCPropertyGridProperty*>(static_cast<wxPGProperty*>(p));
}

CMFCPropertyGridProperty* CPropertiesWnd::AddMaterialProp(CMFCPropertyGridProperty* pGroup,
        wxString strName,
        _variant_t val,
        wxString strComment,
        DWORD_PTR dwData,
        LPCTSTR pszValidChars,
        void* pData)
{
	CMaterial mset;
	std::vector<CString> arrOptions;
	mset.m_strPath = DATA_PATH;
	mset.m_strTable = _T("Matup.dbf");
	mset.Open();
	while(!mset.IsEOF())
	{
		CString str;
		str = mset.m_MAT;
		arrOptions.push_back(str);
		mset.MoveNext();
	}
	mset.Close();
	return AddEnumProp(pGroup, strName, val, strComment, dwData, pszValidChars, pData, arrOptions);
}

CMFCPropertyGridProperty* CPropertiesWnd::CheckExistingProp(CMFCPropertyGridProperty* pGroup,
                                                            wxString strName,
                                                            _variant_t & val,
                                                            wxString strComment,
                                                            DWORD_PTR dwData,
                                                            LPCTSTR pszValidChars,
                                                            void* pData)
{
	UNREFERENCED_PARAMETER(pszValidChars);
	UNREFERENCED_PARAMETER(pGroup);
	CSelVec& vec = m_pDoc->vecSel;
	size_t n = vec.size();
	if(n == 0)
		vec.insert(SelStr(vec.SelNAYZ, vec.SelKOYZ));
	// if (dwData>=100 || (dwData>=1 && dwData<=50))
	{
		switch(dwData)
		{
			case E_MATERIAL:
			case E_MATOTV:
			case E_TR_MAT:
			case E_MATOTV_SV:
			case E_MATOTV_OF:
				for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
					if(*reinterpret_cast<CStringA*>(it->second) != val.GetString())
						val = _variant_t(_T(""));
				break;
			case E_LEN_PLAN:
				SearchVal(pData, dwData, val, a2.l_plan);
				break;
			case E_LEN_TOTAL:
				SearchVal(pData, dwData, val, a2.l_gen);
				break;
			case E_ANG_PLAN_ABS:
				SearchVal(pData, dwData, val, a2.a_plan);
				break;
			case E_ANG_PLAN_REL:
				SearchVal(pData, dwData, val, a2.a_plan_rel, 1.0);
				break;
			case E_ANG_PROF:
				SearchVal(pData, dwData, val, a2.a_prof, 0.5f);
				break;
			case E_UKLON:
				SearchVal(pData, dwData, val, a2.uklon, 0.5f);
				break;
			case E_DIAM:
				SearchValField(pData, dwData, val, &CPipeAndNode::m_DIAM);
				break;
			case E_TR_DIAM_OTV:
				SearchValField(pData, dwData, val, &CPipeAndNode::m_NONE);
				break;

			case E_GRTYPE_UP:
			case E_GRTYPE_OSN:
			case E_GRTYPE_SIDE:
			{
				int i = int(*static_cast<float*>(pData) * 10.0f + 0.5f);
				int nSide = i % 10;
				i /= 100;
				int nUp = i % 10;
				i /= 100;
				int nDown = i;
				float f = 0.0f;
				switch(dwData)
				{
					case E_GRTYPE_UP:
						f = float(nUp);
						break;
					case E_GRTYPE_OSN:
						f = float(nDown);
						break;
					case E_GRTYPE_SIDE:
						f = float(nSide);
						break;
				}
				for(auto it = m_mapPropVal.find(dwData); it != m_mapPropVal.end() && it->first == dwData; ++it)
					if(!FCompare(f, it->second))
						val = _variant_t(_T(""));
				m_mapPropVal.insert(std::make_pair(dwData, f));
			}
			break;
			case E_PIPE_TYPE:
			{
				CPipeAndNode* pPnN = static_cast<CPipeAndNode*>(pData);
				for(auto it = m_mapPropVal.find(dwData); it != m_mapPropVal.end() && it->first == dwData; ++it)
					if(!FCompare(it->second, pPnN->m_NAGV))
						val = _variant_t(_T(""));
				m_mapPropVal.insert(std::make_pair(dwData, pPnN->m_NAGV));
			}
			break;
			default:
				for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
					if(!FCompare(*(it->second), *static_cast<float*>(pData)))
						val = _variant_t(_T(""));
				break;
		}
		if(pData)
			m_mapProp.insert(std::make_pair(dwData, static_cast<float*>(pData)));
	}

	bAdd = false;
	CMFCPropertyGridProperty* p = m_pwndPropList->FindItemByData(dwData);
	// if (p && p->GetValue().vt != val.vt)
	//	m_pwndPropList->DeleteProperty(p);
	if(p)
	{
		return p;
	}
	return nullptr;
}

CMFCPropertyGridProperty* CPropertiesWnd::AddProp(CMFCPropertyGridProperty* pGroup,
        wxString strName,
        _variant_t val,
        wxString strComment,
        DWORD_PTR dwData,
        LPCTSTR pszValidChars,
        void* pData)
{
	
	CMFCPropertyGridProperty* p = CheckExistingProp(pGroup,strName,val,strComment,dwData,pszValidChars,pData);
	if (p && !p->HasFlag(wxPG_PROP_BEING_DELETED))
	{
		if(m_nPipeNo == m_nPipesSelected)
			p->SetValue(val);
		return p;
	}
	bAdd = true;
	if (val.GetType()=="double")
		p = static_cast<CMFCPropertyGridProperty*>(static_cast<wxPGProperty*>(new wxFloatProperty(strName, wxPG_LABEL, val.GetDouble())));
	else
		p = static_cast<CMFCPropertyGridProperty*>(static_cast<wxPGProperty*>(new wxStringProperty(strName, wxPG_LABEL, val.GetString())));
	p->SetHelpString(strComment);
	p->SetClientData((void*)dwData);
	if(pGroup)
		m_pwndPropList->AppendIn(pGroup, p);
	else
		m_pwndPropList->Append(p);
	return p;
}

void CPropertiesWnd::SearchVal(void* pData, DWORD_PTR& dwData, _variant_t& val, float& searchVal, float eps)
{
	CPipeAndNode* pPnN = static_cast<CPipeAndNode*>(pData);
	a2.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
	if (dwData == E_ANG_PLAN_REL)
		a2.GetRelAngle(m_pDoc, pPnN);
	for(auto it = m_mapPropVal.find(dwData); it != m_mapPropVal.end() && it->first == dwData; ++it)
		if(!FCompare(it->second, searchVal, eps))
			val = _variant_t(_T(""));
	m_mapPropVal.insert(std::make_pair(dwData, searchVal));
}

void CPropertiesWnd::SearchValField(void* pData,
                                    const DWORD_PTR& dwData,
                                    _variant_t& val,
                                    float CPipeAndNode::*searchVal,
                                    float eps)
{
	CPipeAndNode* pPnN = static_cast<CPipeAndNode*>(pData);
	for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		if(!FCompare(reinterpret_cast<CPipeAndNode*>(it->second)->*searchVal, pPnN->*searchVal, eps))
			val = _variant_t(_T(""));
}

void AfxLoadString(wxString id, TCHAR* str)
{
	wcscpy(str, id.t_str());
}

void CPropertiesWnd::FillPipeProps()
{
	CString strValidChars = _T("-0123456789,.");
	CMFCPropertyGridProperty* pGroup1 = AddPGroup(IDS_OSN, E_GROUP_OSN);
	CMFCPropertyGridProperty* pProp;
	pProp =
	    AddProp(pGroup1, IDS_NODE_BEG, S_RoundV(m_pPnN->m_NAYZ, 0), IDS_NODE_BEG_C, E_NAYZ, nullptr, &m_pPnN->m_NAYZ);
	pProp->Enable(FALSE);
	pProp =
	    AddProp(pGroup1, IDS_NODE_END, S_RoundV(m_pPnN->m_KOYZ, 0), IDS_NODE_END_C, E_KOYZ, nullptr, &m_pPnN->m_KOYZ);
	pProp->Enable(FALSE);

	BOOL bPodzem = fabs(m_pPnN->m_NAGV + 1) < 1e-6;
	std::vector<CString> arrOptions;
	TCHAR str[256];
	AfxLoadString(bPodzem ? IDS_PODZEM : IDS_NADZEM, str);
	TCHAR strBuf[256];
	AfxLoadString(IDS_NADZEM, strBuf);
	arrOptions.push_back(strBuf);
	AfxLoadString(IDS_PODZEM, strBuf);
	arrOptions.push_back(strBuf);
	pProp = AddEnumProp(pGroup1, IDS_PIPE_TYPE, str, IDS_PIPE_TYPE, E_PIPE_TYPE, nullptr, m_pPnN, arrOptions, true);

	CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_GEOM, E_GROUP_GEOM, FALSE, pGroup1);
	m_propX = pProp =
	              AddProp(pGroup2, IDS_PROJ_X, S_RoundV(m_pPnN->m_OSIX, 3), IDS_PROJ_X_C, E_OSIX, strValidChars, &m_pPnN->m_OSIX);
	m_propY = pProp =
	              AddProp(pGroup2, IDS_PROJ_Y, S_RoundV(m_pPnN->m_OSIY, 3), IDS_PROJ_Y_C, E_OSIY, strValidChars, &m_pPnN->m_OSIY);
	m_propZ = pProp =
	              AddProp(pGroup2, IDS_PROJ_Z, S_RoundV(m_pPnN->m_OSIZ, 3), IDS_PROJ_Z_C, E_OSIZ, strValidChars, &m_pPnN->m_OSIZ);
	a1.calc_angles(m_pPnN->m_OSIX, m_pPnN->m_OSIY, m_pPnN->m_OSIZ);
	m_propLPlan = pProp =
	                  AddProp(pGroup2, IDS_LEN_PLAN, S_RoundV(a1.l_plan, 3), IDS_LEN_PLAN_C, E_LEN_PLAN, strValidChars, m_pPnN);
	m_propLen = pProp =
	                AddProp(pGroup2, IDS_LEN_GEN, S_RoundV(a1.l_gen, 3), IDS_LEN_GEN_C, E_LEN_TOTAL, strValidChars, m_pPnN);
	m_propAPlan = pProp =
	                  AddProp(pGroup2, IDS_APLAN_ABS, Round(a1.a_plan, 1), IDS_APLAN_ABS_C, E_ANG_PLAN_ABS, strValidChars, m_pPnN);
	pProp->SetAttribute(wxPG_FLOAT_PRECISION,1);
	// pProp->EnableSpinControl(TRUE, -180, 180);
	a1.GetRelAngle(m_pDoc, m_pPnN);
	m_propAPlanRel = pProp = AddProp(pGroup2,
	                                 IDS_APLAN_REL,
	                                 Round(a1.a_plan_rel, 1),
	                                 IDS_APLAN_REL_C,
	                                 E_ANG_PLAN_REL,
	                                 strValidChars,
	                                 m_pPnN);
	pProp->SetAttribute(wxPG_FLOAT_PRECISION,1);
	pProp->SetAttribute(wxPG_ATTR_SPINCTRL_STEP, 13456);
	m_pwndPropList->GetGrid()->SetPropertyEditor(pProp,wxPGEditor_SpinCtrl);
	/*
	        if (pProp->GetOriginalValue().vt == pProp->GetValue().vt)
	                pProp->SetOriginalValue(pProp->GetValue());
	        dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->EnableSpinControl(TRUE, -180, 180);
			 */
	m_propAProf = pProp = AddProp(pGroup2, IDS_APROF, Round(a1.a_prof, 1), IDS_APROF_C, E_ANG_PROF,  strValidChars, m_pPnN);
	pProp->SetAttribute(wxPG_FLOAT_PRECISION,1);
	pProp->SetAttribute(wxPG_ATTR_SPINCTRL_STEP, 13456);
	m_pwndPropList->GetGrid()->SetPropertyEditor(pProp,wxPGEditor_SpinCtrl);
	/*
        dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->EnableSpinControl(TRUE, -90, 90);

	 */
	m_propUklon = pProp =
	                  AddProp(pGroup2, IDS_UKLON, S_RoundV(a1.uklon, 0), IDS_UKLON_C, E_UKLON, strValidChars, m_pPnN);

	arrOptions.clear();

	CString s;
	std::vector<float> vecDiams;
	s = s.Format(_T("%g"), m_pPnN->m_DIAM);
	set.m_strPath = DATA_PATH;
	set.m_strTable = _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] where %d=PODZ order by DIAM"), int(bPodzem));
	set.Open();
	for(; !set.IsEOF(); set.MoveNext())
	{
		if(bPodzem != set.m_PODZ)
			continue;
		//arrOptions.push_back(CString::Format(_T("%g"), set.m_DIAM));
		vecDiams.push_back(set.m_DIAM);
	}
	set.Close();
	std::sort(vecDiams.begin(), vecDiams.end());
	for (auto x : vecDiams)
		arrOptions.push_back(CString::Format(_T("%g"), x));
	pProp = AddEnumProp(pGroup1, IDS_DIAM, _variant_t(s), IDS_DIAM_C, E_DIAM, strValidChars, m_pPnN, arrOptions);
	pProp = AddMaterialProp(
	            pGroup1, IDS_MATERIAL, _variant_t(m_pPnN->m_NAMA), IDS_MATERIAL_C, E_MATERIAL, nullptr, &m_pPnN->m_NAMA);

	AddProp(pGroup1, IDS_NOTO, S_RoundV(m_pPnN->m_NTOS, 1), IDS_NOTO_C, E_NTOS, strValidChars, &m_pPnN->m_NTOS);
	AddProp(pGroup1, IDS_RATO, S_RoundV(m_pPnN->m_RTOS, 2), IDS_RATO_C, E_RTOS, strValidChars, &m_pPnN->m_RTOS);
	AddProp(pGroup1, IDS_RADA, S_RoundV(m_pPnN->m_RADA, 1), IDS_RADA_C, E_RADA, strValidChars, &m_pPnN->m_RADA);
	AddProp(pGroup1, IDS_DABI, S_RoundV(m_pPnN->m_DABI, 1), IDS_DABI_C, E_DABI, strValidChars, &m_pPnN->m_DABI);
	AddProp(pGroup1, IDS_RATE, S_RoundV(m_pPnN->m_RATE, 1), IDS_RATE_C, E_RATE, strValidChars, &m_pPnN->m_RATE);

	CMFCPropertyGridProperty* pGroup3 = AddPGroup(IDS_POG_VESA, E_GROUP_VESA, TRUE, pGroup1);
	AddProp(pGroup3, IDS_VETR, S_RoundV(m_pPnN->m_VETR, 2), IDS_VETR_C, E_VETR, strValidChars, &m_pPnN->m_VETR);
	AddProp(pGroup3, IDS_VEIZ, S_RoundV(m_pPnN->m_VEIZ, 2), IDS_VEIZ_C, E_VEIZ, strValidChars, &m_pPnN->m_VEIZ);
	AddProp(pGroup3, IDS_VEPR, S_RoundV(m_pPnN->m_VEPR, 2), IDS_VEPR_C, E_VEPR, strValidChars, &m_pPnN->m_VEPR);

	CMFCPropertyGridProperty* pGroup4 = AddPGroup(IDS_ADDITIONAL, E_GROUP_ADDITIONAL, FALSE, pGroup1);
	AddProp(pGroup4, IDS_KOPE, S_RoundV(m_pPnN->m_KOPE, 2), IDS_KOPE_C, E_KOPE, strValidChars, &m_pPnN->m_KOPE);
	AddProp(pGroup4, IDS_KOPR, S_RoundV(m_pPnN->m_KOPR, 2), IDS_KOPR_C, E_KOPR, strValidChars, &m_pPnN->m_KOPR);
	if(!bPodzem)
	{
		CMFCPropertyGridProperty* pGroup5 = AddPGroup(IDS_ADD_NAGR, E_GROUP_ADD_NAGR, TRUE);

		AddProp(pGroup5, IDS_NAGV, S_RoundV(m_pPnN->m_NAGV, 0), IDS_NAGV_C, E_NAGV, strValidChars, &m_pPnN->m_NAGV);
		AddProp(pGroup5, IDS_NAGX, S_RoundV(m_pPnN->m_NAGX, 0), IDS_NAGX_C, E_NAGX, strValidChars, &m_pPnN->m_NAGX);
		AddProp(pGroup5, IDS_NAGY, S_RoundV(m_pPnN->m_NAGY, 0), IDS_NAGY_C, E_NAGY, strValidChars, &m_pPnN->m_NAGY);
		AddProp(pGroup5, IDS_NAGZ, S_RoundV(m_pPnN->m_NAGZ, 0), IDS_NAGZ_C, E_NAGZ, strValidChars, &m_pPnN->m_NAGZ);
	}
	else
	{
		CMFCPropertyGridProperty* pGroup5 = AddPGroup(IDS_GRUNT, E_GROUP_GRUNT);
		AddProp(pGroup5,
		        IDS_DIAM_KOZHUX,
		        S_RoundV(m_pPnN->m_NAGX, 0),
		        IDS_DIAM_KOZHUX_C,
		        E_DIAM_KOZHUX,
		        strValidChars,
		        &m_pPnN->m_NAGX);
		CMFCPropertyGridProperty* pGroup7 = AddPGroup(IDS_GLUB, E_GROUP_GLUB, TRUE, pGroup5);
		AddProp(pGroup7,
		        IDS_BEG_GLUB,
		        S_RoundV(m_pPnN->m_OS_TR1, 2),
		        IDS_BEG_GLUB_C,
		        E_OS_TR_BEG,
		        strValidChars,
		        &m_pPnN->m_OS_TR1);
		AddProp(pGroup7,
		        IDS_END_GLUB,
		        S_RoundV(m_pPnN->m_OS_TR2, 2),
		        IDS_END_GLUB,
		        E_OS_TR_END,
		        strValidChars,
		        &m_pPnN->m_OS_TR2);

		pGroup7 = AddPGroup(IDS_VIZA, E_GROUP_VIZA, TRUE, pGroup5);
		AddProp(pGroup7,
		        IDS_BEG_GLUB,
		        S_RoundV(m_pPnN->m_VIZA, 2),
		        IDS_BEG_GLUB_C,
		        E_VIZA_BEG,
		        strValidChars,
		        &m_pPnN->m_VIZA);
		AddProp(pGroup7,
		        IDS_END_GLUB,
		        S_RoundV(m_pPnN->m_VIZA2, 2),
		        IDS_END_GLUB_C,
		        E_VIZA_END,
		        strValidChars,
		        &m_pPnN->m_VIZA2);

		AddProp(pGroup5, IDS_SHTR, S_RoundV(m_pPnN->m_SHTR, 1), IDS_SHTR_C, E_SHTR, strValidChars, &m_pPnN->m_SHTR);
		int n = int(m_pPnN->m_NAGZ * 10.0f + 0.5f);
		int nSide = n % 10;
		n /= 100;
		int nUp = n % 10;
		n /= 100;
		int nDown = n;
		CMFCPropertyGridProperty* pGroup6 = AddPGroup(IDS_GRUNT_TYPE, E_GROUP_GRUNT_TYPE, TRUE, pGroup5);
		AddProp(
		    pGroup6, IDS_GRUNT_UP, _variant_t(nUp), IDS_GRUNT_UP_C, E_GRTYPE_UP, strValidChars, &m_pPnN->m_NAGZ);
		AddProp(pGroup6,
		        IDS_GRUNT_OSN,
		        _variant_t(nDown),
		        IDS_GRUNT_OSN_C,
		        E_GRTYPE_OSN,
		        strValidChars,
		        &m_pPnN->m_NAGZ);
		AddProp(pGroup6,
		        IDS_GRUNT_SIDE,
		        _variant_t(nSide),
		        IDS_GRUNT_SIDE_C,
		        E_GRTYPE_SIDE,
		        strValidChars,
		        &m_pPnN->m_NAGZ);
	}
}


void CPropertiesWnd::AddOtvod(UINT* arrIDS)
{

	CMFCPropertyGridProperty* pGroup1 = m_pIzdProp; //AddPGroup(str0, arrIDS[1]);
	AddProp(pGroup1, IDS_OTV_RAD, S_RoundV(m_pPnN->m_RAOT, 2), IDS_OTV_RAD_C, arrIDS[2], nullptr, &m_pPnN->m_RAOT);
	AddProp(pGroup1, IDS_OTV_VES, S_RoundV(m_pPnN->m_VESA, 1), IDS_OTV_VES_C, arrIDS[3], nullptr, &m_pPnN->m_VESA);
	AddMaterialProp(pGroup1, IDS_OTV_MAT, _variant_t(m_pPnN->m_MARI), IDS_OTV_MAT_C, arrIDS[4], nullptr, &m_pPnN->m_MARI);
	AddProp(pGroup1, IDS_OTV_NOTO, S_RoundV(m_pPnN->m_NOTO, 1), IDS_OTV_NOTO_C, arrIDS[5], nullptr, &m_pPnN->m_NOTO);
	AddProp(pGroup1, IDS_OTV_RATO, S_RoundV(m_pPnN->m_RATO, 1), IDS_OTV_RATO_C, arrIDS[6], nullptr, &m_pPnN->m_RATO);
}

void CPropertiesWnd::FillNodeProps()
{
	CMFCPropertyGridProperty* pProp;
	if(m_nNodesSelected == 1)
	{
		pProp = AddProp(nullptr, IDS_NODE, _variant_t(long(m_pPnN->m_KOYZ)), IDS_NODE_C, E_END_NODE);
		m_setPGroups.insert(DWORD_PTR(pProp->GetClientData()));
		pProp->Enable(FALSE);
	}
	CString strIzd;
	wxString nID;
	if(m_pPnN->m_MNEA == STR_AR)
		nID = IDS_ARMAT;
	else if(m_pPnN->m_MNEA == STR_OI)
		nID = IDS_OTVIZ;
	else if(m_pPnN->m_MNEA == STR_OS)
		nID = IDS_OTVSV;
	else if(m_pPnN->m_MNEA == STR_OF)
		nID = IDS_OTVFL;
	else if(m_pPnN->m_MNEA == STR_KO)
		nID = IDS_KO;
	else if(m_pPnN->m_MNEA == STR_KU)
		nID = IDS_KU;
	else if(m_pPnN->m_MNEA == STR_TR)
		nID = IDS_TR;
	else if(m_pPnN->m_VREZKA == STR_SV)
		nID = IDS_VREZKA;
	else
		nID = IDS_NONE;
	strIzd = LoadStr(nID);
	std::vector<CString> arrOptions;
	if(m_nNodesSelected == 1)
	{
		TCHAR str[256];
		AfxLoadString(IDS_NONE, str);
		arrOptions.push_back(str);
		if(m_pPnN->m_TIDE == _T(""))
		{
			if(m_pPnN->m_MNEO != STR_MO)
			{
				AfxLoadString(IDS_ARMAT, str);
				arrOptions.push_back(str);
			}
			if(m_pPnN->m_MNEO == _T(""))
			{
				AfxLoadString(IDS_OTVIZ, str);
				arrOptions.push_back(str);
				AfxLoadString(IDS_OTVSV, str);
				arrOptions.push_back(str);
				AfxLoadString(IDS_OTVFL, str);
				arrOptions.push_back(str);
				AfxLoadString(IDS_KO, str);
				arrOptions.push_back(str);
				AfxLoadString(IDS_KU, str);
				arrOptions.push_back(str);
				AfxLoadString(IDS_TR, str);
				arrOptions.push_back(str);
				AfxLoadString(IDS_VREZKA, str);
				arrOptions.push_back(str);
			}
		}
 		m_pIzdProp = pProp =
		                 AddEnumProp(nullptr, IDS_IZD, _variant_t(strIzd), IDS_IZD_C, E_IZD_TYPE, nullptr, nullptr, arrOptions);
        m_pIzdProp->DeleteChildren();
		for (size_t i = 0; i < pProp->GetChildCount(); i++)
			pProp->Item(i)->ChangeFlag(wxPG_PROP_BEING_DELETED, true);
		m_setPGroups.insert(DWORD_PTR(pProp->GetClientData()));
	}
	if(m_pPnN->m_MNEA == STR_AR)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pIzdProp;//AddPGroup(nID, E_GROUP_IZD);

		AddProp(
		    pGroup1, IDS_AR_LEN, S_RoundV(m_pPnN->m_RAOT, 1), IDS_AR_LEN_C, E_ARM_LEN, nullptr, &m_pPnN->m_RAOT);
		AddProp(
		    pGroup1, IDS_AR_VES, S_RoundV(m_pPnN->m_VESA, 1), IDS_AR_VES_C, E_ARM_VES, nullptr, &m_pPnN->m_VESA);
	}
	else if(m_pPnN->m_MNEA == STR_OI)
	{
		UINT arrIDS[] = { 0, E_GROUP_OTVIZ, E_RAOT, E_VESOTV, E_MATOTV, E_NOTO_OTV, E_RATO_OTV };
		AddOtvod(arrIDS);
	}
	else if(m_pPnN->m_MNEA == STR_OS)
	{
		UINT arrIDS[] = { 0, E_GROUP_OTVSV, E_RAOT_SV, E_VESOTV_SV, E_MATOTV_SV, E_NOTO_SV, E_RATO_SV };
		AddOtvod(arrIDS);
	}
	else if(m_pPnN->m_MNEA == STR_OF)
	{
		UINT arrIDS[] = { 0, E_GROUP_OTVFL, E_RAOT_OF, E_VESOTV_OF, E_MATOTV_OF, E_NOTO_OF, E_RATO_OF };
		AddOtvod(arrIDS);
	}
	else if(m_pPnN->m_MNEA == STR_KO)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pIzdProp;//AddPGroup(nID, E_GROUP_KO);
		pProp = AddProp(
		            pGroup1, IDS_KO_SEFF, S_RoundV(m_pPnN->m_RAOT, 1), IDS_KO_SEFF_C, E_KO_SEFF, nullptr, &m_pPnN->m_RAOT);
		// pProp->AllowEdit(TRUE);
		AddProp(pGroup1,
		        IDS_KO_PODATL,
		        S_RoundV(m_pPnN->m_KOTR, 5),
		        IDS_KO_PODATL_C,
		        E_KO_PODATL,
		        nullptr,
		        &m_pPnN->m_KOTR);
		AddProp(pGroup1,
		        IDS_KO_OS_HOD,
		        S_RoundV(m_pPnN->m_DIGI, 1),
		        IDS_KO_OS_HOD_C,
		        E_KO_OS_HOD,
		        nullptr,
		        &m_pPnN->m_DIGI);
	}
	else if(m_pPnN->m_MNEA == STR_KU)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pIzdProp;//AddPGroup(nID, E_GROUP_KU);
		AddProp(pGroup1,
		        IDS_KU_PODATL,
		        S_RoundV(m_pPnN->m_KOTR, 5),
		        IDS_KU_PODATL_C,
		        E_KU_PODATL,
		        nullptr,
		        &m_pPnN->m_KOTR);
		AddProp(pGroup1, IDS_KU_LEN, S_RoundV(m_pPnN->m_DIGI, 1), IDS_KU_LEN, E_KU_LEN, nullptr, &m_pPnN->m_DIGI);
	}
	else if(m_pPnN->m_MNEA == STR_TR)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pIzdProp;//AddPGroup(nID, E_GROUP_TR);
		pProp = AddMaterialProp(
		            pGroup1, IDS_TR_MAT, _variant_t(m_pPnN->m_MARI), IDS_TR_MAT_C, E_TR_MAT, nullptr, &m_pPnN->m_MARI);
		AddProp(pGroup1, IDS_TR_VES, S_RoundV(m_pPnN->m_VESA, 1), IDS_TR_VES_C, E_TR_VES, nullptr, &m_pPnN->m_VESA);
		CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_MAGISTRAL, 2013, FALSE, pGroup1);
		AddProp(pGroup2,
		        IDS_MAG_NOTO,
		        S_RoundV(m_pPnN->m_NOTO, 1),
		        IDS_MAG_NOTO_C,
		        E_TR_NOTO_MAG,
		        nullptr,
		        &m_pPnN->m_NOTO);
		AddProp(pGroup2,
		        IDS_MAG_RATO,
		        S_RoundV(m_pPnN->m_RATO, 1),
		        IDS_MAG_RATO_C,
		        E_TR_RATO_MAG,
		        nullptr,
		        &m_pPnN->m_RATO);
		AddProp(pGroup2,
		        IDS_MAG_LEN,
		        S_RoundV(m_pPnN->m_KORPUS, 0),
		        IDS_MAG_LEN_C,
		        E_TR_LEN_MAG,
		        nullptr,
		        &m_pPnN->m_KORPUS);

		pGroup2 = AddPGroup(IDS_OTV, 2014, FALSE, pGroup1);

		std::vector<float> vecDiams;
		CTroinicsSet set1;
		arrOptions.clear();
		set1.m_strPath = DATA_PATH;
		set1.m_strTable =
		    _T("Troinics.dbf"); //.Format(_T("[Troinics] where DIAM=%g order by DIAMSH"), m_pPnN->m_DIAM);
		set1.Open();
		for(; !set1.IsEOF(); set1.MoveNext())
		{
			if(fabs(set1.m_DIAM - m_pPnN->m_DIAM) > 0.1)
				continue;
			//arrOptions.push_back(CString::Format(_T("%g"), set1.m_DIAMSH));
			vecDiams.push_back(set1.m_DIAMSH);
		}
		set1.Close();
		std::sort(vecDiams.begin(), vecDiams.end());
		for (auto x : vecDiams)
			arrOptions.push_back(CString::Format(_T("%g"), x));

		pProp = AddEnumProp(pGroup2,
		                    IDS_OTV_DIAM,
		                    _variant_t(long(m_pPnN->m_NONE)),
		                    IDS_OTV_DIAM_C,
		                    E_TR_DIAM_OTV,
		                    nullptr,
		                    m_pPnN,
		                    arrOptions);
		AddProp(pGroup2,
		        IDS_OTVL_NOTO,
		        S_RoundV(m_pPnN->m_VEYS, 1),
		        IDS_OTVL_NOTO_C,
		        E_TR_NOTO_OTV,
		        nullptr,
		        &m_pPnN->m_VEYS);
		AddProp(pGroup2,
		        IDS_OTVL_RATO,
		        S_RoundV(m_pPnN->m_DIGI, 1),
		        IDS_OTVL_RATO_C,
		        E_TR_RATO_OTV,
		        nullptr,
		        &m_pPnN->m_DIGI);
		AddProp(pGroup2,
		        IDS_OTVL_VYS,
		        S_RoundV(m_pPnN->m_SILX, 1),
		        IDS_OTVL_VYS_C,
		        E_TR_VYS_OTV,
		        nullptr,
		        &m_pPnN->m_SILX);

		pGroup2 = AddPGroup(IDS_NAKL, E_GROUP_NAKL, FALSE, pGroup1);
		AddProp(pGroup2,
		        IDS_NAKL_NOTO,
		        S_RoundV(m_pPnN->m_DEFZ, 1),
		        IDS_NAKL_NOTO_C,
		        E_TR_NOTO_NAKL,
		        nullptr,
		        &m_pPnN->m_DEFZ);
		AddProp(pGroup2,
		        IDS_NAKL_SHIR,
		        S_RoundV(m_pPnN->m_RASG, 1),
		        IDS_NAKL_SHIR_C,
		        E_TR_SHIR_NAKL,
		        nullptr,
		        &m_pPnN->m_RASG);
	}
	else if(m_pPnN->m_VREZKA == STR_SV)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pIzdProp;//AddPGroup(nID, E_GROUP_VREZKA);
		AddProp(
		    pGroup1, IDS_VR_KOPR, S_RoundV(m_pPnN->m_DEFY, 1), IDS_VR_KOPR_C, E_VR_KOPR, nullptr, &m_pPnN->m_DEFY);
		CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_VR_NAKL, 2017, FALSE, pGroup1);
		AddProp(pGroup2,
		        IDS_VR_NAKL_NOTO,
		        S_RoundV(m_pPnN->m_DEFZ, 1),
		        IDS_VR_NAKL_NOTO_C,
		        E_VR_NOTO_NAKL,
		        nullptr,
		        &m_pPnN->m_DEFZ);
		AddProp(pGroup2,
		        IDS_VR_NAKL_SHIR,
		        S_RoundV(m_pPnN->m_RASG, 1),
		        IDS_VR_NAKL_SHIR_C,
		        E_VR_SHIR_NAKL,
		        nullptr,
		        &m_pPnN->m_RASG);
	}

	CString strOpor;
	wxString nIDOpor = IDS_NONE;
	if(m_pPnN->m_MNEO == STR_MO)
		nIDOpor = IDS_MERT;
	else if(m_pPnN->m_MNEO == STR_SK)
		nIDOpor = IDS_SK;
	else if(m_pPnN->m_MNEO == STR_NP)
		nIDOpor = IDS_NAPR;
	else if(m_pPnN->m_MNEO == STR_PR)
		nIDOpor = IDS_UPR;
	else if(m_pPnN->m_MNEO == STR_PD)
		nIDOpor = IDS_ZHESTK_PODV;
	strOpor = nIDOpor;
	if(m_nNodesSelected == 1)
	{
		arrOptions.clear();
		arrOptions.push_back(LoadStr(IDS_NONE));
		if(m_pPnN->m_TIDE == _T(""))
		{
			if(m_pPnN->m_MNEA == _T(""))
			{
				arrOptions.push_back(LoadStr(IDS_MERT));
			}
			if(m_pPnN->m_MNEA == STR_AR || m_pPnN->m_MNEA == _T(""))
			{
				arrOptions.push_back(LoadStr(IDS_SK));
				arrOptions.push_back(LoadStr(IDS_NAPR));
				if(fabs(m_pPnN->m_NAGV + 1) > 1e-6f)
				{
					arrOptions.push_back(LoadStr(IDS_UPR));
					arrOptions.push_back(LoadStr(IDS_ZHESTK_PODV));
				}
			}
		}
		m_pOporProp = pProp = AddEnumProp(
		            nullptr, IDS_OPOR, _variant_t(strOpor), IDS_OPOR_C, E_OPOR_TYPE, nullptr, nullptr, arrOptions);
		pProp->DeleteChildren();
		for (size_t i = 0; i < pProp->GetChildCount(); i++)
			pProp->Item(i)->ChangeFlag(wxPG_PROP_BEING_DELETED, true);
		m_setPGroups.insert((DWORD_PTR)pProp->GetClientData());
	}
	if(m_nNodesSelected > 1 && m_pPnN->m_MNEO == STR_MO)
	{
		AddPGroup(IDS_MERT_O, E_GROUP_MO);
	}

	if(m_pPnN->m_MNEO == STR_SK || m_pPnN->m_MNEO == STR_NP)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pOporProp;// AddPGroup(m_pPnN->m_MNEO == STR_SK ? IDS_SK_O : IDS_NAPR_O, m_pPnN->m_MNEO == STR_SK ? E_GROUP_SK : E_GROUP_NP);
		AddProp(pGroup1,
		        IDS_SK_KOTR,
		        S_RoundV(m_pPnN->m_KOTR, 1),
		        IDS_SK_KOTR_C,
		        m_pPnN->m_MNEO == STR_SK ? E_SK_KOTR : E_NP_KOTR,
		        nullptr,
		        &m_pPnN->m_KOTR);
	}
	else if(m_pPnN->m_MNEO == STR_PR)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pOporProp;// AddPGroup(IDS_UPR_O, E_GROUP_UPR_OP);
		AddProp(pGroup1,
		        IDS_UPR_NTG,
		        _variant_t(long(m_pPnN->m_SEOP)),
		        IDS_UPR_NTG_C,
		        E_UOP_NTG,
		        nullptr,
		        &m_pPnN->m_SEOP);
		AddProp(pGroup1,
		        IDS_UPR_IZM_NAGR,
		        S_RoundV(m_pPnN->m_NOTO, 1),
		        IDS_UPR_IZM_NAGR,
		        E_UOP_IZM_NAGR,
		        nullptr,
		        &m_pPnN->m_NOTO);
		AddProp(pGroup1,
		        IDS_UPR_KZAP,
		        S_RoundV(m_pPnN->m_RATO, 1),
		        IDS_UPR_KZAP_C,
		        E_UOP_KZAP,
		        nullptr,
		        &m_pPnN->m_RATO);
		AddProp(pGroup1,
		        IDS_UPR_PODD_US,
		        S_RoundV(m_pPnN->m_VEYS, 1),
		        IDS_UPR_PODD_US_C,
		        E_UOP_PODD_US,
		        nullptr,
		        &m_pPnN->m_VEYS);
		AddProp(pGroup1,
		        IDS_UPR_PODATL,
		        S_RoundV(m_pPnN->m_KOTR, 5),
		        IDS_UPR_PODATL_C,
		        E_UOP_PODATL,
		        nullptr,
		        &m_pPnN->m_KOTR);
	}
	else if(m_pPnN->m_MNEO == STR_PD)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pOporProp;//AddPGroup(nIDOpor, E_GROUP_PD_ZHESTK);
		AddProp(pGroup1,
		        IDS_ZHP_LEN_TYAGI,
		        S_RoundV(m_pPnN->m_DIGI, 1),
		        IDS_ZHP_LEN_TYAGI_C,
		        E_ZHP_LEN_TYAGI,
		        nullptr,
		        &m_pPnN->m_DIGI);
	}
	CString strDef;
	wxString nIDDef = IDS_NONE;
	if(m_pPnN->m_TIDE == STR_RS)
		nIDDef = IDS_RAST;
	else if(m_pPnN->m_TIDE == STR_SG)
		nIDDef = IDS_SG;
	strDef = nIDDef;
	if(m_nNodesSelected == 1)
	{
		arrOptions.clear();
		arrOptions.push_back(LoadStr(IDS_NONE));
		if(m_pPnN->m_MNEA == _T("") && m_pPnN->m_MNEO == _T(""))
		{
			arrOptions.push_back(LoadStr(IDS_RAST));
			arrOptions.push_back(LoadStr(IDS_SG));
		}
		m_pRsGgProp = pProp =
		    AddEnumProp(nullptr, IDS_DEF, _variant_t(strDef), IDS_DEF_C, E_DEF_TYPE, nullptr, nullptr, arrOptions);
		pProp->DeleteChildren();
		for (size_t i = 0; i < pProp->GetChildCount(); i++)
			pProp->Item(i)->ChangeFlag(wxPG_PROP_BEING_DELETED, true);
		m_setPGroups.insert((DWORD_PTR)pProp->GetClientData());
	}
	if(m_pPnN->m_TIDE == STR_RS || m_pPnN->m_TIDE == STR_SG)
	{
		CMFCPropertyGridProperty* pGroup1 = m_pRsGgProp; 
		    //AddPGroup(m_pPnN->m_TIDE == STR_RS ? IDS_RAST : IDS_SG,
		    //          m_pPnN->m_TIDE == STR_RS ? E_GROUP_DEF_TYPE_RS : E_GROUP_DEF_TYPE_SG);
		AddProp(pGroup1,
		        m_pPnN->m_TIDE == STR_RS ? IDS_DEF_RAST : IDS_DEF_SG,
		        S_RoundV(m_pPnN->m_RASG, 0),
		        IDS_DEF_RSTSG_C,
		        m_pPnN->m_TIDE == STR_RS ? E_DEF_VAL_RAST : E_DEF_VAL_SG,
		        nullptr,
		        &m_pPnN->m_RASG);
	}
}

void CPropertiesWnd::FillNodeForces(void)
{
	CMFCPropertyGridProperty* pGroup1 = m_propNagr = AddPGroup(IDS_NAGR, E_GROUP_NAGR);
	CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_NAGR_VES_ADD, E_GROUP_NAGR_VES_ADD, FALSE, pGroup1);
	AddProp(
	    pGroup2, IDS_UZ_SILVES, S_RoundV(m_pPnN->m_VESZ, 1), IDS_UZ_SILVES_C, E_UZ_SILVES, nullptr, &m_pPnN->m_VESZ);
	AddProp(pGroup2,
	        IDS_UZ_MOMVESX,
	        S_RoundV(m_pPnN->m_VESX, 1),
	        IDS_UZ_MOMVESX_C,
	        E_UZ_VES_MOMX,
	        nullptr,
	        &m_pPnN->m_VESX);
	AddProp(pGroup2,
	        IDS_UZ_MOMVESY,
	        S_RoundV(m_pPnN->m_VESY, 1),
	        IDS_UZ_MOMVESY_C2,
	        E_UZ_VES_MOMY,
	        nullptr,
	        &m_pPnN->m_VESY);

	pGroup2 = AddPGroup(IDS_NAGR_NONVES_ADD, E_GROUP_NAGR_NONVES_ADD, FALSE, pGroup1);
	AddProp(pGroup2, IDS_UZ_SILX, S_RoundV(m_pPnN->m_SILX, 1), IDS_UZ_SILX_C, E_UZ_SILX, nullptr, &m_pPnN->m_SILX);
	AddProp(pGroup2, IDS_UZ_SILY, S_RoundV(m_pPnN->m_SILY, 1), IDS_UZ_SILY_C2, E_UZ_SILY, nullptr, &m_pPnN->m_SILY);
	AddProp(pGroup2, IDS_UZ_SILZ, S_RoundV(m_pPnN->m_SILZ, 1), IDS_UZ_SILZ_C, E_UZ_SILZ, nullptr, &m_pPnN->m_SILZ);
	AddProp(pGroup2, IDS_UZ_MOMX, S_RoundV(m_pPnN->m_MOMX, 1), IDS_UZ_MOMX_C, E_UZ_MOMX, nullptr, &m_pPnN->m_MOMX);
	AddProp(pGroup2, IDS_UZ_MOMY, S_RoundV(m_pPnN->m_MOMY, 1), IDS_UZ_MOMY_C, E_UZ_MOMY, nullptr, &m_pPnN->m_MOMY);
	AddProp(pGroup2, IDS_UZ_MOMZ, S_RoundV(m_pPnN->m_MOMZ, 1), IDS_UZ_MOMZ_C, E_UZ_MOMZ, nullptr, &m_pPnN->m_MOMZ);
}

void CPropertiesWnd::OnRecalcXYZ(wxCommandEvent& event)
{
	DWORD_PTR dwFocus = (DWORD_PTR)(m_pwndPropList->GetSelection() ? m_pwndPropList->GetSelection()->GetClientData() : nullptr);
	CDataExchange dx(this, TRUE);
	DoDataExchange(&dx, m_pPnN, m_pDoc);
	CDataExchange dx1(this, FALSE);
	DoDataExchange(&dx1, m_pPnN, m_pDoc);
	if (dwFocus !=0)
	{
		CMFCPropertyGridProperty *pProp = m_pwndPropList->FindItemByData(dwFocus);
		m_pwndPropList->SelectProperty(pProp, true);
	}
	event.Skip();
}

void  CPropertiesWnd::RecalcXYZ()
{
	wxCommandEvent* pEvent = new wxCommandEvent(wxEVT_MENU,ID_RecalcXYZ);
	pEvent->SetEventObject(this);
	GetEventHandler()->QueueEvent(pEvent);
}

void CPropertiesWnd::ToFloat(COleVariant& val)
{
	double d;
	CString str = val.GetString();
	str.ToCDouble(&d);
	val = d;
}

void CPropertiesWnd::ToFloat(const COleVariant& val, float& x)
{
	if(val.GetType() == _T("double"))
	{
		x = val.GetDouble();
		return;
	}
	if(val.GetType() == _T("long"))
	{
		x = float(val.GetLong());
		return;
	}

	CString strVal = val.GetString();
	strVal.Replace(_T("."), _T(","));
	double d;
	strVal.ToCDouble(&d);
	x = d;
}

void CPropertiesWnd::ToFloat(const COleVariant& val, DWORD_PTR dwData)
{
	float x;
	if(val.GetType() == "double")
		x = val.GetDouble();
	else if(val.GetType() == "long")
		x = float(val.GetLong());
	else
	{
		CString strVal = val.GetString();
		strVal.Replace(_T("."), _T(","));
		double d;
		strVal.ToCDouble(&d);
		x = d;
	}
	for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		*it->second = x;
}

void CPropertiesWnd::ToStr(const COleVariant& val, CStringA& x)
{
	x = val.GetString();
}

void CPropertiesWnd::ToStr(const COleVariant& val, DWORD_PTR dwData)
{
	for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		*reinterpret_cast<CStringA*>(it->second) = val.GetString();
}

template <typename T1, typename T2> size_t OffsetOf(T1* val, T2* base)
{
	return reinterpret_cast<BYTE*>(val) - reinterpret_cast<BYTE*>(base);
}

template <typename T1, typename T2> CPipeAndNode* GetPnN(float* ptr, T1* val, T2* base)
{
	return reinterpret_cast<CPipeAndNode*>(reinterpret_cast<BYTE*>(ptr) - OffsetOf(val, base));
}

bool bUpdatedByParent = false;

void CPropertiesWnd::OnPropChange(CMFCPropertyGridProperty *pProp)
{
	wxPropertyGridEvent event;
	event.SetProperty(pProp);
	event.SetClientData((void *)1);
	OnPropertyGridChange(event);
}

void EnumToStr(COleVariant& valNew, CMFCPropertyGridProperty* pProp)
{
	if (valNew.GetType()=="string")
		return;
	int nChoice = valNew.GetInteger();
	wxEnumProperty *pe = reinterpret_cast<wxEnumProperty*>(pProp);
	valNew = pe->GetChoices()[nChoice].GetText();
}

void CPropertiesWnd::OnPropertyGridChange(wxPropertyGridEvent& event)
{
	CMFCPropertyGridProperty* pProp = static_cast<CMFCPropertyGridProperty*>(event.GetProperty());
	DWORD_PTR evData = (DWORD_PTR)event.GetClientData();
	DWORD_PTR dwData = evData !=0 ? 0 : pProp->GetData();
	COleVariant val = pProp->GetValue();
	COleVariant valNew = event.GetValue();
	event.Skip();
	// bool bPodzem = fabs(m_pPnN->m_NAGV+1)<1e-6;

	switch(dwData)
	{
		case E_PIPE_TYPE:
		{
			EnumToStr(valNew, pProp);
			CString strVal = valNew.GetString();
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				TCHAR strPodzem[256];
				AfxLoadString(IDS_PODZEM, strPodzem);
				BOOL bPodzem1 = strVal == strPodzem;
				set.m_strPath = DATA_PATH;
				set.m_strTable = _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and
				// %d=PODZ  order by
				// DIAM, PODZ"),pPnN->m_DIAM, int(bPodzem1));
				set.Open();
				for(; !set.IsEOF(); set.MoveNext())
					if(set.m_PODZ == bPodzem1 && fabs(set.m_DIAM - pPnN->m_DIAM) < 0.1)
						break;
				if(bPodzem1)
				{
					if(pPnN->m_NAGV != -1)
					{
						pPnN->m_NAGV = -1.0f;
						pPnN->m_NAGY = 0.0f;
						pPnN->m_NAGZ = 1010.1f;
						pPnN->m_NAGX = set.m_DIIZ;
						pPnN->m_SHTR = set.m_SHTR;
						pPnN->m_VIZA = pPnN->m_VIZA2 = 0;
						pPnN->m_OS_TR1 = pPnN->m_OS_TR2 = set.m_DIIZ / 2000;
					}
				}
				else
				{
					pPnN->m_NAGV = pPnN->m_NAGX = pPnN->m_NAGY = pPnN->m_NAGZ = 0.0f;
				}
				set.Close();
			}
			RecalcXYZ();
			break;
		}
		case 0:
		case E_GROUP_GLUB:
		case E_GROUP_VIZA:
		case E_GROUP_GRUNT_TYPE:
		case E_GROUP_ADD_NAGR:
		case E_GROUP_VESA:
			bUpdatedByParent = true;
			for (size_t i = 0; i < pProp->GetChildCount(); i++)
				OnPropChange((CMFCPropertyGridProperty*)pProp->Item(i));
			bUpdatedByParent = false;
			RecalcXYZ();
			break;

		case E_OSIX: // Проекция участка на ось X
		case E_OSIY: // Проекция участка на ось Y
		case E_OSIZ: // Проекция участка на ось Z
			ToFloat(valNew, dwData);
			RecalcXYZ();
			break;
		case E_LEN_PLAN: // Длина участка в плане
		{
			ToFloat(valNew);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.l_plan = valNew.GetDouble();
				pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
				pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
			}
			RecalcXYZ();
		}
		break;
		case E_LEN_TOTAL: // Длина участка
		{
			ToFloat(valNew);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				float scl;
				if(a1.l_gen < 1e-6f)
				{
					scl = 1.0f;
					m_pPnN->m_OSIX = valNew.GetDouble();
				}
				else
					scl = valNew.GetDouble() / a1.l_gen;
				pPnN->m_OSIX = Round(pPnN->m_OSIX * scl, 3);
				pPnN->m_OSIY = Round(pPnN->m_OSIY * scl, 3);
				pPnN->m_OSIZ = Round(pPnN->m_OSIZ * scl, 3);
			}
			RecalcXYZ();
			break;
		}
		case E_ANG_PLAN_ABS: // Угол в плане абсолютный
			ToFloat(valNew);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.a_plan = float(valNew.GetDouble());
				pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
				pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
			}
			RecalcXYZ();
			break;
		case E_ANG_PLAN_REL: // Угол в плане относительно предыдущего участка
		{
			bool bButtons = false;
			float ang;
			if(valNew.GetType() == "string")
			{
				CString strVal = valNew.GetString();
				long d;
				strVal.ToCLong(&d);
				valNew = d;
			}

			double dNew = valNew.GetDouble();
			double dOld = val.GetDouble();
			double step = pProp->GetAttributeAsDouble(wxPG_ATTR_SPINCTRL_STEP, 1.0);
			if (fabs(dNew-dOld-step)<0.0001)
			{
				pProp->SetValue(dOld < 0 ? _variant_t(0.0) : _variant_t(90.0));
				ToFloat(pProp->GetValue(), ang);
				bButtons = true;
			}
			else if (fabs(dOld-dNew-step)<0.0001)
			{
				pProp->SetValue(dOld > 0 ? _variant_t(0.0) : _variant_t(-90.0));
				ToFloat(pProp->GetValue(), ang);
				bButtons = true;
			}
			else
			{
				ToFloat(valNew, ang);
			}
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.GetRelAngle(m_pDoc, pPnN);
				m_pDoc->RotateThisAndOthers(pPnN, DegToRad(ang - a1.a_plan_rel));
			}
			RecalcXYZ();
		}
		break;

		case E_ANG_PROF: // Угол в профиле (азимутальный)
		{
			bool bButtons = false;
			float ang;
			if(valNew.GetType() == "string")
			{
				CString strVal = valNew.GetString();
				double d;
				strVal.ToCDouble(&d);
				valNew = d;
			}
			if(val.GetType() == "string")
			{
				CString strVal = val.GetString();
				if(strVal.Length() > 0)
				{
					long d;
					strVal.ToCLong(&d);
					val = d;
				}
				else
					val = 0l;
			}
			double dNew = valNew.GetDouble();
			double dOld = val.GetDouble();
			double step = pProp->GetAttributeAsDouble(wxPG_ATTR_SPINCTRL_STEP, 1.0);
			if (fabs(dNew-dOld-step)<0.0001)
			{
				pProp->SetValue(dOld < 0 ? _variant_t(0.0) : _variant_t(90.0));
				ToFloat(pProp->GetValue(), ang);
				bButtons = true;
			}
			else if (fabs(dOld-dNew-step)<0.0001)
			{
				pProp->SetValue(dOld > 0 ? _variant_t(0.0) : _variant_t(-90.0));
				ToFloat(pProp->GetValue(), ang);
				bButtons = true;
			}
			/*
			CMFCSpinButtonCtrlMy* pSpin = dynamic_cast<CMFCPropertyGridProperty1 *>(pProp)->GetSpinCtrl();
			if (pSpin)
			{
			        if (pSpin->GetIsButtonUp())
			        {
			                bButtons = true;
			                pProp->SetValue(val.GetLong() < 0 ? _variant_t(0l) : _variant_t(90l));
			        }
			        else if (pSpin->GetIsButtonDown())
			        {
			                bButtons = true;
			                pProp->SetValue(val.GetLong() > 0 ? _variant_t(0l) : _variant_t(-90l));
			        }
			        else
			        {
			                if (valNew.GetLong() == 1)
			                {
			                        bButtons = true;
			                        pProp->SetValue(val.GetLong() < 0 ? _variant_t(0l) : _variant_t(90l));
			                }
			                else if (valNew.GetLong() == - 1)
			                {
			                        bButtons = true;
			                        pProp->SetValue(val.GetLong() > 0 ? _variant_t(0l) : _variant_t(-90l));
			                }
			        }
			        ToFloat(pProp->GetValue(), ang);
			}*/
			else
			{
				ToFloat(valNew, ang);
			}
			//pProp->SetValue(_variant_t(S_Round(ang, 1)));
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.a_prof = ang;
				if(bButtons)
				{
					if(a1.a_prof == 0.0f)
					{
						if(a1.l_plan < 0.001f)
						{
							a1.l_plan = a1.l_gen;
							a1.a_plan = a1.a_plan_prev;
						}
						pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
						pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
						pPnN->m_OSIZ = 0.0f;
					}
					else
					{
						pPnN->m_OSIX = pPnN->m_OSIY = 0.0f;
						pPnN->m_OSIZ = Round(a1.l_gen * sin(DegToRad(a1.a_prof)), 3);
					}
				}
				else
				{
					if(a1.l_plan < 0.001f)
					{
						a1.l_plan = a1.l_gen;
						a1.a_plan = a1.a_plan_prev;
					}
					a1.l_gen = a1.l_plan / cos(DegToRad(a1.a_prof));
					pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
					pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
					pPnN->m_OSIZ = Round(a1.l_gen * sin(DegToRad(a1.a_prof)), 3);
				}
			}
			RecalcXYZ();
		}
		break;
		case E_UKLON: // Уклон
			ToFloat(valNew);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.uklon = valNew.GetDouble();
				a1.a_prof = RadToDeg(atan(a1.uklon / 1000));
				// a1.l_plan = a1.l_gen*cos(DegToRad(a1.a_prof));
				pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
				pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
				pPnN->m_OSIZ = Round(a1.l_plan * tan(DegToRad(a1.a_prof)), 3);
			}
			RecalcXYZ();
			break;
		case E_DIAM:
			EnumToStr(valNew, pProp);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				CPipesSet pset;
				ToFloat(valNew, pPnN->m_DIAM);
				BOOL b_podzem = fabs(pPnN->m_NAGV + 1) < 1e-6;
				pset.m_strPath = DATA_PATH;
				pset.m_strTable =
				    _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by
				// DIAM, PODZ"),pPnN->m_DIAM, int(b_podzem));
				pset.Open();
				// while (!set.IsEOF())
				for(; !pset.IsEOF(); pset.MoveNext())
					if(pset.m_PODZ == b_podzem && fabs(pset.m_DIAM - pPnN->m_DIAM) < 0.1)
						break;
				{
					pPnN->m_NAMA = pset.m_NAMA;
					pPnN->m_NTOS = pset.m_NTOS;
					pPnN->m_RTOS = pset.m_NTOS - pset.m_RTOS;
					pPnN->m_VETR = pset.m_VETR;
					pPnN->m_VEIZ = pset.m_VEIZ;
					pPnN->m_VEPR = pset.m_VEPR;
					if(b_podzem)
					{
						pPnN->m_NAGX = pset.m_DIIZ;
						pPnN->m_SHTR = pset.m_SHTR;
					}
					pPnN->m_RAOT = pset.m_RAOT;
					pPnN->m_MARI = pset.m_MARI;
					pPnN->m_NOTO = pset.m_NOTO;
					pPnN->m_RATO = pset.m_NOTO - pset.m_RATO;
					if(pPnN->m_MNEA == STR_KO)
					{
						m_pPnN->m_RAOT = pset.m_SEFF;
						m_pPnN->m_KOTR = pset.m_KPOD;
					}
				}
				pset.Close();
			}
			RecalcXYZ();
			break;
		case E_MATERIAL:
			EnumToStr(valNew, pProp);
			ToStr(valNew, dwData);
			break;
		case E_OS_TR_BEG:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_OS_TR1, m_pPnN);
				pPnN->m_OS_TR1 = valNew.GetDouble();
				pPnN->m_VIZA = pPnN->m_OS_TR1 - pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(auto p = &(arr.InFirst(int(pPnN->m_NAYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR2 = pPnN->m_OS_TR1;
						p->m_pPnN->m_VIZA2 = p->m_pPnN->m_OS_TR2 - p->m_pPnN->m_NAGX / 2000;
					}
				for(auto p = &arr.OutFirst(int(pPnN->m_NAYZ), cnt); arr.HasOut(cnt); p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR1 = pPnN->m_OS_TR1;
						p->m_pPnN->m_VIZA = p->m_pPnN->m_OS_TR1 - p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_OS_TR_END:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_OS_TR2, m_pPnN);
				pPnN->m_OS_TR2 = valNew.GetDouble();
				pPnN->m_VIZA2 = pPnN->m_OS_TR2 - pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(Pipe* p = &(arr.InFirst(int(pPnN->m_KOYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR2 = pPnN->m_OS_TR2;
						p->m_pPnN->m_VIZA2 = p->m_pPnN->m_OS_TR2 - p->m_pPnN->m_NAGX / 2000;
					}
				for(Pipe* p = &(arr.OutFirst(int(pPnN->m_KOYZ), cnt)); arr.HasOut(cnt);
				        p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_OS_TR1 = pPnN->m_OS_TR2;
						p->m_pPnN->m_VIZA = p->m_pPnN->m_OS_TR1 - p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_VIZA_BEG:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_VIZA, m_pPnN);
				pPnN->m_VIZA = valNew.GetDouble();
				pPnN->m_OS_TR1 = pPnN->m_VIZA + pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(Pipe* p = &(arr.InFirst(int(pPnN->m_NAYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA2 = pPnN->m_VIZA;
						p->m_pPnN->m_OS_TR2 = p->m_pPnN->m_VIZA2 + p->m_pPnN->m_NAGX / 2000;
					}
				for(Pipe* p = &(arr.OutFirst(int(pPnN->m_NAYZ), cnt)); arr.HasOut(cnt);
				        p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA = pPnN->m_VIZA;
						p->m_pPnN->m_OS_TR1 = p->m_pPnN->m_VIZA + p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_VIZA_END:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_VIZA2, m_pPnN);
				pPnN->m_VIZA2 = valNew.GetDouble();
				pPnN->m_OS_TR2 = pPnN->m_VIZA2 + pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for(Pipe* p = &(arr.InFirst(int(pPnN->m_KOYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA2 = pPnN->m_VIZA2;
						p->m_pPnN->m_OS_TR2 = p->m_pPnN->m_VIZA2 + p->m_pPnN->m_NAGX / 2000;
					}
				for(Pipe* p = &(arr.OutFirst(int(pPnN->m_KOYZ), cnt)); arr.HasOut(cnt);
				        p = &arr.OutNext(cnt))
					if(p->Podzem)
					{
						p->m_pPnN->m_VIZA = pPnN->m_VIZA2;
						p->m_pPnN->m_OS_TR1 = p->m_pPnN->m_VIZA + p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if(!bUpdatedByParent)
			RecalcXYZ();
		break;
		case E_GRTYPE_UP:
		case E_GRTYPE_OSN:
		case E_GRTYPE_SIDE:
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				int n = int((*(it->second)) * 10 + 0.5f);
				int nSide = n % 10;
				n /= 100;
				int nUp = n % 10;
				n /= 100;
				int nDown = n;
				switch(dwData)
				{
					case E_GRTYPE_UP:
						nUp = valNew.GetLong();
						break;
					case E_GRTYPE_OSN:
						nDown = valNew.GetLong();
						break;
					case E_GRTYPE_SIDE:
						nSide = valNew.GetLong();
						break;
				}
				*it->second = Round(float(nSide) / 10 + nUp * 10 + nDown * 1000, 1);
			}
			break;
		case E_IZD_TYPE:
		{
			EnumToStr(valNew, pProp);
			CString strVal = valNew.GetString();
			seta.m_strPath = DATA_PATH;
			seta.m_strTable =
			    _T("Armat.dbf"); // Format(_T("[Armat] WHERE DIAM = %g order by DIAM"), m_pPnN->m_DIAM);
			if(!seta.Open())
				AfxMessageBox(_T("Can't open Armat.dbf"), wxOK);
			for(; !seta.IsEOF(); seta.MoveNext())
				if(fabs(seta.m_DIAM - m_pPnN->m_DIAM) < 0.1)
					break;
			TCHAR strNone[256];
			AfxLoadString(IDS_NONE, strNone);
			if(strVal == strNone)
			{
				m_pPnN->m_MNEA = _T("");
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_ARMAT))
			{
				m_pPnN->m_MNEA = STR_AR;
				m_pPnN->m_RAOT = seta.m_RAOT1;
				m_pPnN->m_VESA = seta.m_VESA1;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_OTVIZ))
			{
				m_pPnN->m_MNEA = STR_OI;
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_OTVSV))
			{
				m_pPnN->m_MNEA = STR_OS;
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_OTVFL))
			{
				m_pPnN->m_MNEA = STR_OF;
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_KO))
			{
				set.m_strPath = DATA_PATH;
				set.m_strTable =
				    _T("Pipes.dbf"); // set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g order by
				// DIAM"), m_pPnN->m_DIAM);
				set.Open();
				for(; !set.IsEOF(); set.MoveNext())
					if(fabs(set.m_DIAM - m_pPnN->m_DIAM) < 0.1)
						break;
				m_pPnN->m_MNEA = STR_KO;
				m_pPnN->m_RAOT = set.m_SEFF;
				m_pPnN->m_KOTR = set.m_KPOD;
				m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = _T("");
				set.Close();
			}
			else if(strVal == LoadStr(IDS_KU))
			{
				m_pPnN->m_MNEA = STR_KU;
				m_pPnN->m_KOTR = m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = _T("");
			}
			else if(strVal == LoadStr(IDS_TR))
			{
				m_pPnN->m_MNEA = STR_TR;
				m_pPnN->m_KOTR = m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = _T("");
			}

			else if(strVal == LoadStr(IDS_VREZKA))
			{
				m_pPnN->m_VREZKA = STR_SV;
				m_pPnN->m_MNEA = _T("");
			}
			seta.Close();
			CDataExchange dx(this, FALSE);
			DoDataExchange(&dx, m_pPnN, m_pDoc);
		}
		break;

		case E_OPOR_TYPE:
		{
			EnumToStr(valNew, pProp);
			CString strVal = valNew.GetString();
			if (strVal == LoadStr(IDS_NONE))
				ToStr(_variant_t(_T("")), m_pPnN->m_MNEO);
			else if(strVal == LoadStr(IDS_MERT))
			{
				ToStr(_variant_t(STR_MO), m_pPnN->m_MNEO);
			}
			else if(strVal == LoadStr(IDS_SK))
			{
				ToStr(_variant_t(STR_SK), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.3f), m_pPnN->m_KOTR);
			}
			else if(strVal == LoadStr(IDS_NAPR))
			{
				ToStr(_variant_t(STR_NP), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.3f), m_pPnN->m_KOTR);
			}
			else if(strVal == LoadStr(IDS_UPR))
			{
				ToStr(_variant_t(STR_PR), m_pPnN->m_MNEO);
				ToFloat(_variant_t(1.0f), m_pPnN->m_SEOP);
				ToFloat(_variant_t(35.0f), m_pPnN->m_NOTO);
				ToFloat(_variant_t(1.0f), m_pPnN->m_RATO);
				ToFloat(_variant_t(0.0f), m_pPnN->m_VEYS);
				ToFloat(_variant_t(0.0f), m_pPnN->m_KOTR);
			}
			else if(strVal == LoadStr(IDS_ZHESTK_PODV))
			{
				ToStr(_variant_t(STR_PD), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.0f), m_pPnN->m_DIGI);
			}
			OnLBChanged();
			break;
		}
		case E_DEF_TYPE:
		{
			EnumToStr(valNew, pProp);
			CString strVal = valNew.GetString();
			if(strVal == LoadStr(IDS_NONE))
				m_pPnN->m_TIDE = _T("");
			else if(strVal == LoadStr(IDS_RAST))
			{
				m_pPnN->m_TIDE = STR_RS;
				// m_pPnN->m_RASG=0.0f;
			}
			else if(strVal == LoadStr(IDS_SG))
			{
				m_pPnN->m_TIDE = STR_SG;
				// m_pPnN->m_RASG=0.0f;
			}
			OnLBChanged();
		}
		break;
		case E_MATOTV:
		case E_TR_MAT:
		case E_MATOTV_SV:
		case E_MATOTV_OF:
			EnumToStr(valNew, pProp);
			ToStr(valNew, dwData);
			break;
		case E_TR_DIAM_OTV:
		{
			EnumToStr(valNew, pProp);
			for(auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				ToFloat(valNew, pPnN->m_NONE);
				CTroinicsSet set1;
				set1.m_strPath = DATA_PATH;
				set1.m_strTable = _T("Troinics.dbf"); // set1.m_strTable.Format(_T("[Troinics] WHERE DIAM =
				// %g and DIAMSH =
				// %g"), pPnN->m_DIAM, pPnN->m_NONE);
				if(!set1.Open())
					AfxMessageBox(_T("Can't open Troinics.dbf"), wxOK);
				for(; !set1.IsEOF(); set1.MoveNext())
					if(fabs(set1.m_DIAM - m_pPnN->m_DIAM) < 0.1 &&
					        fabs(set1.m_DIAMSH - m_pPnN->m_NONE) < 0.1)
						break;

				pPnN->m_NOTO = set1.m_NTSTM;
				pPnN->m_RATO = set1.m_NTSTM - set1.m_RTSTM;
				pPnN->m_VEYS = set1.m_NTSTSH;
				pPnN->m_DIGI = set1.m_NTSTSH - set1.m_RTSTSH;
				pPnN->m_SILX = float(set1.m_VIS_SHTU);
				pPnN->m_RASG = set1.m_WIDTHNAK;
				pPnN->m_DEFZ = set1.m_THINKNAK;
				pPnN->m_VESA = set1.m_VES;
				pPnN->m_KORPUS = float(set1.m_KORPUS);
				pPnN->m_MARI = pPnN->m_NAMA;
				set1.Close();
			}
			RecalcXYZ();
			break;
		}
		default:
			ToFloat(valNew, dwData);
			break;
	}
	m_pDoc->PnNIsUpdated();
}

void CPropertiesWnd::Clear()
{
	m_pDoc = nullptr;
	m_pPnN = nullptr;
	m_pwndPropList->GetGrid()->Clear();
	m_pwndObjectCombo->Clear();
}

void CPropertiesWnd::OnLBChanged()
{
	wxCommandEvent event;
	OnLBChange(event);
}

void CPropertiesWnd::OnLBChange(wxCommandEvent& event)
{
	event.Skip();
	int nSel = m_pwndObjectCombo->GetSelection();
	if (!m_pDoc)
		return;
	if(m_pDoc->vecSel.size() >= 2)
	{
		// m_pwndObjectCombo->SetCurSel(0);
		if(nSel != 0)
		{
			auto it = m_pDoc->vecSel.begin();
			// ReSharper disable once CppPossiblyErroneousEmptyStatements
			for(int i = nSel - 1; i > 0; i--)
				++it;
			int b = it->SelNAYZ;
			int e = it->SelKOYZ;
			m_pDoc->vecSel.clear();
			m_pDoc->Select(b, e);
		}
		return;
	}

	if(nSel == 0)
	{
		m_pDoc->Select(int(m_pPnN->m_NAYZ), int(m_pPnN->m_KOYZ));
	}
	else
	{
		m_pDoc->Select(int(m_pPnN->m_KOYZ), int(m_pPnN->m_KOYZ));
	}
}

void CPropertiesWnd::OnPropMert(wxCommandEvent& event)
{
	if(!m_pPnN)
		return;
	m_pwndObjectCombo->Select(1);
	if(m_pPnN->m_MNEO == STR_MO)
		m_pPnN->m_MNEO = _T("");
	else
		m_pPnN->m_MNEO = STR_MO;
	m_pDoc->PnNIsUpdated();
	OnLBChanged();
	event.Skip();
}

void CPropertiesWnd::OnUpdatePropMert(wxUpdateUIEvent& event)
{
	event.Enable(m_pPnN && m_pDoc && m_pDoc->vecSel.size() <= 1 && m_pPnN->m_MNEA == _T("") && m_pPnN->m_TIDE == _T(""));
	if (m_pPnN)
		event.Check(m_pPnN->m_MNEO == STR_MO);
}

void CPropertiesWnd::OnPropSk(wxCommandEvent& event)
{
	if(!m_pPnN)
		return;
	m_pwndObjectCombo->Select(1);
	if(m_pPnN->m_MNEO == STR_SK)
		m_pPnN->m_MNEO = _T("");
	else
	{
		m_pPnN->m_MNEO = STR_SK;
		m_pPnN->m_KOTR = 0.3f;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChanged();
	event.Skip();
}

void CPropertiesWnd::OnUpdatePropSk(wxUpdateUIEvent& event)
{
	if(!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		event.Enable(false);
		return;
	}
	event.Check(m_pPnN->m_MNEO == STR_SK);
	event.Enable((m_pPnN->m_MNEA == _T("") || m_pPnN->m_MNEA == STR_AR) && m_pPnN->m_TIDE == _T(""));
}

void CPropertiesWnd::OnPropNapr(wxCommandEvent& event)
{
	if(!m_pPnN)
		return;
	m_pwndObjectCombo->Select(1);
	if(m_pPnN->m_MNEO == STR_NP)
		m_pPnN->m_MNEO = _T("");
	else
	{
		m_pPnN->m_MNEO = STR_NP;
		m_pPnN->m_KOTR = 0.3f;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChanged();
	event.Skip();
}

void CPropertiesWnd::OnUpdatePropNapr(wxUpdateUIEvent& event)
{
	if(!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		event.Enable(FALSE);
		return;
	}
	event.Check(m_pPnN->m_MNEO == STR_NP);
	event.Enable((m_pPnN->m_MNEA == _T("") || m_pPnN->m_MNEA == STR_AR) && m_pPnN->m_TIDE == _T(""));
}

void CPropertiesWnd::OnPropOtvSv(wxCommandEvent& event)
{
	if(!m_pPnN)
		return;
	m_pwndObjectCombo->Select(1);
	if(m_pPnN->m_MNEA == STR_OS)
		m_pPnN->m_MNEA = _T("");
	else
	{
		m_pPnN->m_MNEA = STR_OS;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChanged();
	m_pIzdProp = m_pwndPropList->FindItemByData(E_IZD_TYPE);
	if (m_pIzdProp && m_pPnN->m_MNEA == STR_OS)
	  OnPropChange(m_pIzdProp);
	event.Skip();
}

void CPropertiesWnd::OnUpdatePropOtvSv(wxUpdateUIEvent& event)
{
	if(!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		event.Enable(FALSE);
		return;
	}
	event.Check(m_pPnN->m_MNEA == STR_OS);
	event.Enable(m_pPnN->m_MNEO == _T("") && m_pPnN->m_TIDE == _T(""));
}

void CPropertiesWnd::OnPropOtvIz(wxCommandEvent& event)
{
	if(!m_pPnN)
		return;
	m_pwndObjectCombo->Select(1);
	if(m_pPnN->m_MNEA == STR_OI)
		m_pPnN->m_MNEA = _T("");
	else
	{
		m_pPnN->m_MNEA = STR_OI;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChanged();
	if (m_pPnN->m_MNEA == STR_OI)
		OnPropChange(m_pIzdProp);
	event.Skip();
}

void CPropertiesWnd::OnUpdatePropOtvIz(wxUpdateUIEvent& event)
{
	if(!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		event.Enable(FALSE);
		return;
	}
	event.Check(m_pPnN->m_MNEA == STR_OI);
	event.Enable(m_pPnN->m_MNEO == _T("") && m_pPnN->m_TIDE == _T(""));
}

void CPropertiesWnd::OnPropArm(wxCommandEvent& event)
{
	if(!m_pPnN)
		return;
	m_pwndObjectCombo->Select(1);
	if(m_pPnN->m_MNEA == STR_AR)
		m_pPnN->m_MNEA = _T("");
	else
	{
		m_pPnN->m_MNEA = STR_AR;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChanged();
	if (m_pPnN->m_MNEA == STR_AR)
		OnPropChange(m_pIzdProp);
	event.Skip();
}

void CPropertiesWnd::OnUpdatePropArm(wxUpdateUIEvent& event)
{
	if(!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		event.Enable(FALSE);
		return;
	}
	event.Check(m_pPnN->m_MNEA == STR_AR);
	event.Enable((m_pPnN->m_MNEO == _T("") || m_pPnN->m_MNEO == STR_SK || m_pPnN->m_MNEO == STR_NP) && m_pPnN->m_TIDE == _T(""));
}
