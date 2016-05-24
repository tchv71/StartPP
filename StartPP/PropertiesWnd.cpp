#include "stdafx.h"

#include "PropertiesWnd.h"
#include "resource.h"
#include "StartPPDoc.h"
#include "PipeAndNode.h"
#include "PipesSet.h"
#include "TroinicsSet.h"
#include "Material.h"
#include <math.h>
#ifndef WX
#include "afxspinbuttonctrl.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
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

	E_UZ_SILVES,
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
} EFields;

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd() : m_propLPlan(nullptr), m_propAPlanRel(nullptr), m_pIzdProp(nullptr),
                                   m_pDoc(nullptr), m_PropMode(E_NONE), m_oPropMode(E_NONE)
                                   , m_nNodesSelected(0), m_nPipesSelected(0), m_nPipeNo(0)
{
	m_nComboHeight = 0;
	m_pPnN = nullptr;
	m_propX = m_propY = m_propZ = m_propLen = m_propAPlan = m_propAProf = m_propUklon = nullptr;
	m_propNagr = nullptr;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
#ifndef WX
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropChange)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
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
#else
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropChange)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
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
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// обработчики сообщений CResourceViewBar

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() - (m_nComboHeight + cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy(0, 0, 100, 200);
	//rectDummy.SetRectEmpty();

	// Создать поле со списком:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | /*CBS_SORT |*/ WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VSCROLL;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Не удалось создать поле со списком \"Свойства\" \n");
		return -1; // не удалось создать
	}

	m_wndObjectCombo.SetCurSel(0);
	m_wndObjectCombo.SetMinVisibleItems(5);
	m_wndObjectCombo.SetExtendedUI(TRUE);
	SetPropListFont();

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect(&rectCombo);

	m_nComboHeight = rectCombo.Height();

	m_wndPropList.SetListDelimiter(_T(';'));

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Не удалось создать сетку свойств\n");
		return -1; // не удалось создать
	}

	InitPropList();
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Заблокирован */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(IDR_PROPERTIES, 0, 0, TRUE /* Заблокирован */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// Все команды будут перенаправлены через этот элемент управления, а не через родительскую рамку:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: добавьте сюда код обработчика команд
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: добавьте сюда код обработчика команд обновления интерфейса пользователя
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: добавьте сюда код обработчика команд
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: добавьте сюда код обработчика команд обновления интерфейса пользователя
}

void CPropertiesWnd::InitPropList()
{
	//SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties(FALSE);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	//m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

inline float DegToRad(float x)
{
	return x * atan(1.0f) / 45;
}

inline float RadToDeg(float x)
{
	return x * 45 / atan(1.0f);
}


void CPropertiesWnd::CAngles::calc_angles(float x, float y, float z)
{
	l_gen = sqrt(x * x + y * y + z * z);
	l_plan = sqrt(x * x + y * y);
	if (fabs(x) + fabs(y) < 0.001f)
	{
		a_plan = 0;
		a_prof = (z > 0) ? 90.0f : -90.0f;
		if (fabs(z) < 0.001f)
			a_prof = 0;
		uklon = 0;
	}
	else
	{
		a_prof = RadToDeg(atan(z / l_plan));
		if (fabs(x) < 0.001)
		{
			a_plan = (y > 0) ? 90.0f : -90.0f;
		}
		else
		{
			a_plan = RadToDeg(atan(y / x));
			if (x < 0)
				a_plan = (y < 0) ? -180.0f + a_plan : 180.0f + a_plan;
		}
		if (fabs(z) < 0.001f)
			uklon = 0;
		else
			uklon = z / l_plan * 1000;
	}
}

void CPropertiesWnd::CAngles::GetRelAngle(CStartPPDoc* m_pDoc, CPipeAndNode* pPnN)
{
	CPipeAndNode* prevPnN = m_pDoc->GetPrevPnN(int(pPnN->m_NAYZ));
	while (prevPnN && fabs(prevPnN->m_OSIX) + fabs(prevPnN->m_OSIY) < 1e-3f)
		prevPnN = m_pDoc->GetPrevPnN(int(prevPnN->m_NAYZ));
	if (prevPnN)
	{
		float x = prevPnN->m_OSIX;
		float y = prevPnN->m_OSIY;
		//float z=prevPnN->m_OSIZ;
		if (fabs(x) + fabs(y) < 0.001f)
			a_plan_prev = 0;
		else if (fabs(x) < 0.001)
		{
			a_plan_prev = (y > 0) ? 90.0f : -90.0f;
		}
		else
		{
			a_plan_prev = RadToDeg(atan(y / x));
			if (x < 0)
				a_plan_prev = (y < 0) ? -180.0f + a_plan_prev : 180.0f + a_plan_prev;
		}
	}
	else
		a_plan_prev = 0;
	a_plan_rel = a_plan - a_plan_prev;
	if (a_plan_rel > 180)
		a_plan_rel = a_plan_rel - 360;
	else if (a_plan_rel < -180)
		a_plan_rel = a_plan_rel + 360;
	if (fabs(pPnN->m_OSIX) + fabs(pPnN->m_OSIY) < 1e-3f)
		a_plan_rel = 0;
}


float Round(float x, int N)
{
	float f = 1.0f;
	for (int i = 0; i < N; i++) f *= 10.0f;
	return x > 0 ? int(x * f + 0.5f) / f : int(x * f - 0.5f) / f;
}

CString S_Round(float x, int N)
{
	CString str;
	str.Format(_T("%d"), N);
	str = CString("%.") + str + CString("f");
	CString str1;
	str1.Format(str, Round(x, N));
	return str1;
}

_variant_t S_RoundV(float x, int N)
{
	return _variant_t(S_Round(x, N));
}

LPCTSTR LoadStr(UINT nID)
{
	static TCHAR str[256];
	AfxLoadString(nID, str);
	return str;
}

void CPropertiesWnd::SavePropExpandState(CMFCPropertyGridProperty* pProp)
{
	if (!pProp->IsGroup())
		return;
	m_mapExpanded[pProp->GetData()] = pProp->IsExpanded();
	int nSubitems = pProp->GetSubItemsCount();
	for (int i = 0; i < nSubitems; i++)
	{
		CMFCPropertyGridProperty* pSubItem = pProp->GetSubItem(i);
		if (pSubItem->IsGroup())
			SavePropExpandState(pSubItem);
	}
}


#define AFX_PROP_HAS_SPIN 0x4

class CMFCSpinButtonCtrlMy : public CMFCSpinButtonCtrl
{
public:
	BOOL GetIsButtonUp()
	{
		return m_bIsButtonPressedUp;
	}

	BOOL GetIsButtonDown()
	{
		return m_bIsButtonPressedDown;
	}
};


class CMFCPropertyGridProperty1: public CMFCPropertyGridProperty
{
public:
	CMFCPropertyGridProperty1(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = nullptr, DWORD_PTR dwData = 0,
	                          LPCTSTR lpszEditMask = nullptr, LPCTSTR lpszEditTemplate = nullptr, LPCTSTR lpszValidChars = nullptr) : CMFCPropertyGridProperty(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars)
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

	CMFCSpinButtonCtrlMy* GetSpinCtrl()
	{
		return reinterpret_cast<CMFCSpinButtonCtrlMy *>(m_pWndSpin);
	}

	BOOL IsSubItem(CMFCPropertyGridProperty* pProp) const
	{
		return CMFCPropertyGridProperty::IsSubItem(pProp);
	}
};

void CPropertiesWnd::DoDataExchange(CDataExchange* pDx, CPipeAndNode* pPnN, CStartPPDoc* pDoc)
{
	if (pPnN == nullptr)
	{
		m_pPnN = nullptr;
		m_wndPropList.RemoveAll();
		m_wndPropList.RedrawWindow();
		return;
	}
	if (pDx->m_bSaveAndValidate)
	{
		pDx->m_bEditLastControl = FALSE;
		//*pPnN = m_PnN;
		//if (m_propNagr!= nullptr)
		//m_bExpandNagr = m_propNagr->IsExpanded();
		int nCount = m_wndPropList.GetPropertyCount();
		for (int i = 0; i < nCount; i++)
			SavePropExpandState(m_wndPropList.GetProperty(i));
		return;
	}
	m_pDoc = pDoc;
	//m_PnN = *pPnN;
	//m_pPnN=&m_PnN;
	m_pPnN = pPnN;
	//m_wndPropList.RemoveAll();
	CString strPipe;
	//if (m_oPropMode != m_PropMode)
	//m_wndPropList.RemoveAll();
	m_oPropMode = m_PropMode;
	if (pDx->m_pDlgWnd != this)
	{
		int nCurSel = m_wndObjectCombo.GetCurSel();
		if (m_PropMode == E_PIPE)
			nCurSel = 0;
		if (m_PropMode == E_NODE)
			nCurSel = 1;
		//m_PropMode = E_NONE;
		m_wndObjectCombo.ResetContent();
		if (m_pDoc->vecSel.size() < 2)
		{
			strPipe.Format(LoadStr(IDS_FORMAT_PIPE), m_pPnN->m_NAYZ, m_pPnN->m_KOYZ);
			m_wndObjectCombo.AddString(strPipe);
			strPipe.Format(LoadStr(IDS_FORMAT_NODE), m_pPnN->m_KOYZ);
			m_wndObjectCombo.AddString(strPipe);
			m_wndObjectCombo.SetCurSel(nCurSel);
			m_nNodesSelected = m_nPipesSelected = 1;
		}
		else
		{
			m_wndObjectCombo.AddString(LoadStr(IDS_FORMAT_MANY_PIPES));
			m_nNodesSelected = m_nPipesSelected = 0;
			for each (auto& x in m_pDoc->vecSel)
			{
				if (x.SelNAYZ == x.SelKOYZ)
				{
					strPipe.Format(IDS_FORMAT_NODE2, x.SelNAYZ);
					m_nNodesSelected++;
				}
				else
				{
					strPipe.Format(LoadStr(IDS_FORMAT_PIPE2), x.SelNAYZ, x.SelKOYZ);
					m_nPipesSelected++;
				}
				m_wndObjectCombo.AddString(strPipe);
			}
			m_wndObjectCombo.SetCurSel(0);
		}
	}
	m_mapProp.clear();
	m_mapPropVal.clear();
	m_setPGroups.clear();
	m_nPipeNo = 0;
	if (m_oPropMode == E_PIPE)
	{
		CMFCPropertyGridProperty* pProp = m_wndPropList.FindItemByData(E_GROUP_ADDITIONAL);
		if (pProp)
		{
			CMFCPropertyGridProperty* pFocus = m_wndPropList.GetCurSel();
			if (pFocus && dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->IsSubItem(pFocus))
				m_wndPropList.SetCurSel(nullptr,FALSE);
			m_wndPropList.DeleteProperty(pProp, FALSE, FALSE);
		}
		for each (const CPipeAndNode& x in m_pDoc->m_pipes.m_vecPnN)
			if (m_pDoc->vecSel.Contains(x.m_NAYZ, x.m_KOYZ))
			{
				m_pPnN = const_cast<CPipeAndNode*>(&x);
				m_nPipeNo++;
				FillPipeProps();
			}
	}
	else
	{
		CMFCPropertyGridProperty* pProp = m_wndPropList.FindItemByData(E_GROUP_NAGR);
		if (pProp)
		{
			CMFCPropertyGridProperty* pFocus = m_wndPropList.GetCurSel();
			if (pFocus && dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->IsSubItem(pFocus))
				m_wndPropList.SetCurSel(nullptr,FALSE);
			m_wndPropList.DeleteProperty(pProp, FALSE, FALSE);
		}

		for each (auto& x in m_pDoc->m_pipes.m_vecPnN)
			if (m_pDoc->vecSel.Contains(x.m_KOYZ, x.m_KOYZ))
			{
				m_pPnN = const_cast<CPipeAndNode*>(&x);
				m_nPipeNo++;
				FillNodeProps();
			}
		for each (auto& x in m_pDoc->m_pipes.m_vecPnN)
			if (m_pDoc->vecSel.Contains(x.m_KOYZ, x.m_KOYZ))
			{
				m_pPnN = const_cast<CPipeAndNode*>(&x);
				FillNodeForces();
			}
	}
	for (int i = 0; i < m_wndPropList.GetPropertyCount();)
	{
		CMFCPropertyGridProperty* pProp = m_wndPropList.GetProperty(i);
		if (m_setPGroups.find(pProp->GetData()) == m_setPGroups.end())
		{
			CMFCPropertyGridProperty* pFocus = m_wndPropList.GetCurSel();
			if (pFocus && dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->IsSubItem(pFocus))
				m_wndPropList.SetCurSel(nullptr,FALSE);
			m_wndPropList.DeleteProperty(pProp, FALSE, FALSE);
		}
		else
			i++;
	}
	m_wndPropList.AdjustLayout();
	for each (auto c in m_mapExpanded)
	{
		CMFCPropertyGridProperty* p = m_wndPropList.FindItemByData(c.first);
		if (p)
			p->Expand(c.second);
	}
}

static bool bAddGroup;

CMFCPropertyGridProperty* CPropertiesWnd::AddPGroup(UINT idName, DWORD_PTR dwData, BOOL bIsValueList)
{
	TCHAR strName[256];
	AfxLoadString(idName, strName);
	m_setPGroups.insert(dwData);
	bAddGroup = false;
	CMFCPropertyGridProperty* p = m_wndPropList.FindItemByData(dwData);
	if (p)
	{
		p->SetName(strName);
		return p;
	}
	bAddGroup = true;
	p = new CMFCPropertyGridProperty1(strName, dwData, bIsValueList);
	return p;
}

static bool bAdd = true;

static inline bool FCompare(float x1, float x2, float eps = 0.001f)
{
	return fabs(x1 - x2) < eps;
}


CMFCPropertyGridProperty* CPropertiesWnd::AddProp(CMFCPropertyGridProperty* pGroup, UINT idName, _variant_t val, UINT idComment, DWORD_PTR dwData, LPCTSTR pszValidChars, void* pData)
{
	TCHAR strName[256];
	AfxLoadString(idName, strName);
	TCHAR strComment[256];
	AfxLoadString(idComment, strComment);
	CSelVec& vec = m_pDoc->vecSel;
	size_t n = vec.size();
	if (n == 0)
		vec.insert(SelStr(vec.SelNAYZ, vec.SelKOYZ));
	//if (dwData>=100 || (dwData>=1 && dwData<=50))
	{
		switch (dwData)
		{
		case E_MATERIAL:
		case E_MATOTV:
		case E_TR_MAT:
		case E_MATOTV_SV:
		case E_MATOTV_OF:
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
				if (*reinterpret_cast<CStringA *>(it->second) != val.bstrVal)
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
			SearchVal(pData, dwData, val, a2.a_plan_rel);
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
				switch (dwData)
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
				for (auto it = m_mapPropVal.find(dwData); it != m_mapPropVal.end() && it->first == dwData; ++it)
					if (!FCompare(f, it->second))
						val = _variant_t(_T(""));
				m_mapPropVal.insert(std::make_pair(dwData, f));
			}
			break;
		case E_PIPE_TYPE:
			{
				CPipeAndNode* pPnN = static_cast<CPipeAndNode*>(pData);
				for (auto it = m_mapPropVal.find(dwData); it != m_mapPropVal.end() && it->first == dwData; ++it)
					if (!FCompare(it->second, pPnN->m_NAGV))
						val = _variant_t(_T(""));
				m_mapPropVal.insert(std::make_pair(dwData, pPnN->m_NAGV));
			}
			break;
		default:
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
				if (!FCompare(*(it->second), *static_cast<float *>(pData)))
					val = _variant_t(_T(""));
			break;
		}
		if (pData)
			m_mapProp.insert(std::make_pair(dwData, static_cast<float*>(pData)));
	}

	bAdd = false;
	CMFCPropertyGridProperty* p = m_wndPropList.FindItemByData(dwData);
	//if (p && p->GetValue().vt != val.vt)
	//	m_wndPropList.DeleteProperty(p);
	if (p)
	{
		if (m_nPipeNo == m_nPipesSelected) p->SetValue(val);
		return p;
	}
	bAdd = true;
	p = new CMFCPropertyGridProperty1(strName, val, strComment, dwData, nullptr, nullptr, pszValidChars);
	if (pGroup)
		pGroup->AddSubItem(p);
	return p;
}

void CPropertiesWnd::SearchVal(void* pData, DWORD_PTR& dwData, _variant_t& val, float& searchVal, float eps)
{
	CPipeAndNode* pPnN = static_cast<CPipeAndNode*>(pData);
	a2.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
	for (auto it = m_mapPropVal.find(dwData); it != m_mapPropVal.end() && it->first == dwData; ++it)
		if (!FCompare(it->second, searchVal, eps))
			val = _variant_t(_T(""));
	m_mapPropVal.insert(std::make_pair(dwData, searchVal));
}

void CPropertiesWnd::SearchValField(void* pData, const DWORD_PTR& dwData, _variant_t& val, float CPipeAndNode::* searchVal, float eps)
{
	CPipeAndNode* pPnN = static_cast<CPipeAndNode*>(pData);
	for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		if (!FCompare(reinterpret_cast<CPipeAndNode*>(it->second) ->* searchVal, pPnN ->* searchVal, eps))
			val = _variant_t(_T(""));
}


void AddMaterial(CMFCPropertyGridProperty* pProp)
{
	CMaterial set;
	pProp->RemoveAllOptions();
	set.m_strPath = _T(".");
	set.m_strTable = _T("[MATUP]  order by NOM");
	set.Open();
	while (!set.IsEOF())
	{
		CString str;
		str = set.m_MAT;
		pProp->AddOption(str);
		set.MoveNext();
	}
	set.Close();
	pProp->AllowEdit(FALSE);
}

void CPropertiesWnd::FillPipeProps()
{
	CString strValidChars = _T("-0123456789,.");
	CMFCPropertyGridProperty* pGroup1 = AddPGroup(IDS_OSN, E_GROUP_OSN);
	bool bAddGroup1 = bAddGroup;
	CMFCPropertyGridProperty* pProp;
	pProp = AddProp(pGroup1, IDS_NODE_BEG, S_RoundV(m_pPnN->m_NAYZ, 0), IDS_NODE_BEG_C, E_NAYZ, nullptr, &m_pPnN->m_NAYZ);
	pProp->Enable(FALSE);
	pProp = AddProp(pGroup1, IDS_NODE_END, S_RoundV(m_pPnN->m_KOYZ, 0), IDS_NODE_END_C, E_KOYZ, nullptr, &m_pPnN->m_KOYZ);
	pProp->Enable(FALSE);
	bool bPodzem = fabs(m_pPnN->m_NAGV + 1) < 1e-6;
	TCHAR str[256];
	AfxLoadString(bPodzem ? IDS_PODZEM : IDS_NADZEM, str);
	pProp = AddProp(pGroup1, IDS_PIPE_TYPE, str, IDS_PIPE_TYPE, E_PIPE_TYPE, nullptr, m_pPnN);
	TCHAR strBuf[256];
	AfxLoadString(IDS_NADZEM, strBuf);
	pProp->AddOption(strBuf);
	AfxLoadString(IDS_PODZEM, strBuf);
	pProp->AddOption(strBuf);
	pProp->AllowEdit(FALSE);

	CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_GEOM, E_GROUP_GEOM);
	m_propX = pProp = AddProp(pGroup2, IDS_PROJ_X, S_RoundV(m_pPnN->m_OSIX, 3), IDS_PROJ_X_C, E_OSIX, strValidChars, &m_pPnN->m_OSIX);
	m_propY = pProp = AddProp(pGroup2, IDS_PROJ_Y, S_RoundV(m_pPnN->m_OSIY, 3), IDS_PROJ_Y_C, E_OSIY, strValidChars, &m_pPnN->m_OSIY);
	m_propZ = pProp = AddProp(pGroup2, IDS_PROJ_Z, S_RoundV(m_pPnN->m_OSIZ, 3), IDS_PROJ_Z_C, E_OSIZ, strValidChars, &m_pPnN->m_OSIZ);
	a1.calc_angles(m_pPnN->m_OSIX, m_pPnN->m_OSIY, m_pPnN->m_OSIZ);
	m_propLPlan = pProp = AddProp(pGroup2, IDS_LEN_PLAN, S_RoundV(a1.l_plan, 3), IDS_LEN_PLAN_C, E_LEN_PLAN, strValidChars, m_pPnN);
	m_propLen = pProp = AddProp(pGroup2, IDS_LEN_GEN, S_RoundV(a1.l_gen, 3), IDS_LEN_GEN_C, E_LEN_TOTAL, strValidChars, m_pPnN);
	m_propAPlan = pProp = AddProp(pGroup2, IDS_APLAN_ABS, S_RoundV(a1.a_plan, 0), IDS_APLAN_ABS_C, E_ANG_PLAN_ABS, strValidChars, m_pPnN);
	//pProp->EnableSpinControl(TRUE, -180, 180);
	a1.GetRelAngle(m_pDoc, m_pPnN);
	m_propAPlanRel = pProp = AddProp(pGroup2, IDS_APLAN_REL, _variant_t(long(Round(a1.a_plan_rel, 0))), IDS_APLAN_REL_C, E_ANG_PLAN_REL, strValidChars, m_pPnN);
	if (pProp->GetOriginalValue().vt == pProp->GetValue().vt)
		pProp->SetOriginalValue(pProp->GetValue());
	dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->EnableSpinControl(TRUE, -180, 180);
	m_propAProf = pProp = AddProp(pGroup2, IDS_APROF, S_RoundV(a1.a_prof, 1), IDS_APROF_C, E_ANG_PROF, strValidChars, m_pPnN);
	dynamic_cast<CMFCPropertyGridProperty1*>(pProp)->EnableSpinControl(TRUE, -90, 90);
	m_propUklon = pProp = AddProp(pGroup2, IDS_UKLON, S_RoundV(a1.uklon, 0), IDS_UKLON_C, E_UKLON, strValidChars, m_pPnN);
	if (bAddGroup) pGroup1->AddSubItem(pGroup2);

	CString s;
	s.Format(_T("%g"), m_pPnN->m_DIAM);
	pProp = AddProp(pGroup1, IDS_DIAM, _variant_t(s), IDS_DIAM_C, E_DIAM, strValidChars, m_pPnN);
	pProp->RemoveAllOptions();
	set.m_strPath = _T(".");
	set.m_strTable.Format(_T("[Pipes] where %d=PODZ order by DIAM"), int(bPodzem));
	set.Open();
	while (!set.IsEOF())
	{
		CString str1;
		str1.Format(_T("%g"), set.m_DIAM);
		pProp->AddOption(str1);
		set.MoveNext();
	}
	set.Close();
	pProp = AddProp(pGroup1, IDS_MATERIAL, _variant_t(m_pPnN->m_NAMA), IDS_MATERIAL_C, E_MATERIAL, nullptr, &m_pPnN->m_NAMA);
	AddMaterial(pProp);
	AddProp(pGroup1, IDS_NOTO, S_RoundV(m_pPnN->m_NTOS, 1), IDS_NOTO_C, E_NTOS, strValidChars, &m_pPnN->m_NTOS);
	AddProp(pGroup1, IDS_RATO, S_RoundV(m_pPnN->m_RTOS, 2), IDS_RATO_C, E_RTOS, strValidChars, &m_pPnN->m_RTOS);
	AddProp(pGroup1, IDS_RADA, S_RoundV(m_pPnN->m_RADA, 1), IDS_RADA_C, E_RADA, strValidChars, &m_pPnN->m_RADA);
	AddProp(pGroup1, IDS_DABI, S_RoundV(m_pPnN->m_DABI, 1), IDS_DABI_C, E_DABI, strValidChars, &m_pPnN->m_DABI);
	AddProp(pGroup1, IDS_RATE, S_RoundV(m_pPnN->m_RATE, 1), IDS_RATE_C, E_RATE, strValidChars, &m_pPnN->m_RATE);

	CMFCPropertyGridProperty* pGroup3 = AddPGroup(IDS_POG_VESA, E_GROUP_VESA, TRUE);
	AddProp(pGroup3, IDS_VETR, S_RoundV(m_pPnN->m_VETR, 2), IDS_VETR_C, E_VETR, strValidChars, &m_pPnN->m_VETR);
	AddProp(pGroup3, IDS_VEIZ, S_RoundV(m_pPnN->m_VEIZ, 2), IDS_VEIZ_C, E_VEIZ, strValidChars, &m_pPnN->m_VEIZ);
	AddProp(pGroup3, IDS_VEPR, S_RoundV(m_pPnN->m_VEPR, 2), IDS_VEPR_C, E_VEPR, strValidChars, &m_pPnN->m_VEPR);
	if (bAddGroup) pGroup1->AddSubItem(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = AddPGroup(IDS_ADDITIONAL, E_GROUP_ADDITIONAL);
	AddProp(pGroup4, IDS_KOPE, S_RoundV(m_pPnN->m_KOPE, 2), IDS_KOPE_C, E_KOPE, strValidChars, &m_pPnN->m_KOPE);
	AddProp(pGroup4, IDS_KOPR, S_RoundV(m_pPnN->m_KOPR, 2), IDS_KOPR_C, E_KOPR, strValidChars, &m_pPnN->m_KOPR);
	if (bAddGroup1) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	if (!bPodzem)
	{
		CMFCPropertyGridProperty* pGroup5 = AddPGroup(IDS_ADD_NAGR, E_GROUP_ADD_NAGR, TRUE);
		if (bAddGroup)
			pGroup4->AddSubItem(pGroup5);
		AddProp(pGroup5, IDS_NAGV, S_RoundV(m_pPnN->m_NAGV, 0), IDS_NAGV_C, E_NAGV, strValidChars, &m_pPnN->m_NAGV);
		AddProp(pGroup5, IDS_NAGX, S_RoundV(m_pPnN->m_NAGX, 0), IDS_NAGX_C, E_NAGX, strValidChars, &m_pPnN->m_NAGX);
		AddProp(pGroup5, IDS_NAGY, S_RoundV(m_pPnN->m_NAGY, 0), IDS_NAGY_C, E_NAGY, strValidChars, &m_pPnN->m_NAGY);
		AddProp(pGroup5, IDS_NAGZ, S_RoundV(m_pPnN->m_NAGZ, 0), IDS_NAGZ_C, E_NAGZ, strValidChars, &m_pPnN->m_NAGZ);
		if (bAddGroup)
		{
			m_wndPropList.AdjustLayout();
		}
	}
	else
	{
		CMFCPropertyGridProperty* pGroup5 = AddPGroup(IDS_GRUNT, E_GROUP_GRUNT);
		AddProp(pGroup5, IDS_DIAM_KOZHUX, S_RoundV(m_pPnN->m_NAGX, 0), IDS_DIAM_KOZHUX_C, E_DIAM_KOZHUX, strValidChars, &m_pPnN->m_NAGX);
		CMFCPropertyGridProperty* pGroup7 = AddPGroup(IDS_GLUB, E_GROUP_GLUB,TRUE);
		AddProp(pGroup7, IDS_BEG_GLUB, S_RoundV(m_pPnN->m_OS_TR1, 2), IDS_BEG_GLUB_C, E_OS_TR_BEG, strValidChars, &m_pPnN->m_OS_TR1);
		AddProp(pGroup7, IDS_END_GLUB, S_RoundV(m_pPnN->m_OS_TR2, 2), IDS_END_GLUB, E_OS_TR_END, strValidChars, &m_pPnN->m_OS_TR2);
		if (bAddGroup) pGroup5->AddSubItem(pGroup7);
		pGroup7 = AddPGroup(IDS_VIZA, E_GROUP_VIZA,TRUE);
		AddProp(pGroup7, IDS_BEG_GLUB, S_RoundV(m_pPnN->m_VIZA, 2), IDS_BEG_GLUB_C, E_VIZA_BEG, strValidChars, &m_pPnN->m_VIZA);
		AddProp(pGroup7, IDS_END_GLUB, S_RoundV(m_pPnN->m_VIZA2, 2), IDS_END_GLUB_C, E_VIZA_END, strValidChars, &m_pPnN->m_VIZA2);
		if (bAddGroup) pGroup5->AddSubItem(pGroup7);

		AddProp(pGroup5, IDS_SHTR, S_RoundV(m_pPnN->m_SHTR, 1), IDS_SHTR_C, E_SHTR, strValidChars, &m_pPnN->m_SHTR);
		int n = int(m_pPnN->m_NAGZ * 10.0f + 0.5f);
		int nSide = n % 10;
		n /= 100;
		int nUp = n % 10;
		n /= 100;
		int nDown = n;
		CMFCPropertyGridProperty* pGroup6 = AddPGroup(IDS_GRUNT_TYPE, E_GROUP_GRUNT_TYPE,TRUE);
		AddProp(pGroup6, IDS_GRUNT_UP, _variant_t(nUp), IDS_GRUNT_UP_C, E_GRTYPE_UP, strValidChars, &m_pPnN->m_NAGZ);
		AddProp(pGroup6, IDS_GRUNT_OSN, _variant_t(nDown), IDS_GRUNT_OSN_C, E_GRTYPE_OSN, strValidChars, &m_pPnN->m_NAGZ);
		AddProp(pGroup6, IDS_GRUNT_SIDE, _variant_t(nSide), IDS_GRUNT_SIDE_C, E_GRTYPE_SIDE, strValidChars, &m_pPnN->m_NAGZ);
		if (bAddGroup) pGroup5->AddSubItem(pGroup6);

		if (bAddGroup) m_wndPropList.AddProperty(pGroup5, FALSE,FALSE);
	}
	if (!m_wndPropList.FindItemByData(pGroup4->GetData()))
		m_wndPropList.AddProperty(pGroup4, FALSE,FALSE);
}

void CPropertiesWnd::DelGroup(DWORD_PTR dwData)
{
	CMFCPropertyGridProperty* p = m_wndPropList.FindItemByData(dwData);
	if (p) m_wndPropList.DeleteProperty(p);
}

void CPropertiesWnd::AddOtvod(UINT* arrIDS)
{
	CMFCPropertyGridProperty* pGroup1 = AddPGroup(arrIDS[0], arrIDS[1]);
	AddProp(pGroup1, IDS_OTV_RAD, S_RoundV(m_pPnN->m_RAOT, 2), IDS_OTV_RAD_C, arrIDS[2], nullptr, &m_pPnN->m_RAOT);
	AddProp(pGroup1, IDS_OTV_VES, S_RoundV(m_pPnN->m_VESA, 1), IDS_OTV_VES_C, arrIDS[3], nullptr, &m_pPnN->m_VESA);
	CMFCPropertyGridProperty* pProp = AddProp(pGroup1, IDS_OTV_MAT, _variant_t(m_pPnN->m_MARI), IDS_OTV_MAT_C, arrIDS[4], nullptr, &m_pPnN->m_MARI);
	AddMaterial(pProp);
	AddProp(pGroup1, IDS_OTV_NOTO, S_RoundV(m_pPnN->m_NOTO, 1), IDS_OTV_NOTO_C, arrIDS[5], nullptr, &m_pPnN->m_NOTO);
	AddProp(pGroup1, IDS_OTV_RATO, S_RoundV(m_pPnN->m_RATO, 1), IDS_OTV_RATO_C, arrIDS[6], nullptr, &m_pPnN->m_RATO);
	if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
}

void CPropertiesWnd::FillNodeProps()
{
	CMFCPropertyGridProperty* pProp;
	if (m_nNodesSelected == 1)
	{
		pProp = AddProp(nullptr, IDS_NODE, _variant_t(long(m_pPnN->m_KOYZ)), IDS_NODE_C, E_END_NODE);
		m_setPGroups.insert(pProp->GetData());
		pProp->Enable(FALSE);
		if (bAdd) m_wndPropList.AddProperty(pProp, FALSE, FALSE);
	}
	CString strIzd;
	UINT nID;
	if (m_pPnN->m_MNEA == "ар")
		nID = IDS_ARMAT;
	else if (m_pPnN->m_MNEA == "ои")
		nID = IDS_OTVIZ;
	else if (m_pPnN->m_MNEA == "ос")
		nID = IDS_OTVSV;
	else if (m_pPnN->m_MNEA == "оф")
		nID = IDS_OTVFL;
	else if (m_pPnN->m_MNEA == "ко")
		nID = IDS_KO;
	else if (m_pPnN->m_MNEA == "ку")
		nID = IDS_KU;
	else if (m_pPnN->m_MNEA == "тр")
		nID = IDS_TR;
	else if (m_pPnN->m_VREZKA == "св")
		nID = IDS_VREZKA;
	else
		nID = IDS_NONE;
	strIzd = LoadStr(nID);
	if (m_nNodesSelected == 1)
	{
		m_pIzdProp = pProp = AddProp(nullptr, IDS_IZD, _variant_t(strIzd), IDS_IZD_C, E_IZD_TYPE);
		m_setPGroups.insert(pProp->GetData());
		pProp->AllowEdit(FALSE);
		pProp->RemoveAllOptions();
		TCHAR str[256];
		AfxLoadString(IDS_NONE, str);
		pProp->AddOption(str);
		if (m_pPnN->m_TIDE == "")
		{
			if (m_pPnN->m_MNEO != "мо")
			{
				AfxLoadString(IDS_ARMAT, str);
				pProp->AddOption(str);
			}
			if (m_pPnN->m_MNEO == "")
			{
				AfxLoadString(IDS_OTVIZ, str);
				pProp->AddOption(str);
				AfxLoadString(IDS_OTVSV, str);
				pProp->AddOption(str);
				AfxLoadString(IDS_OTVFL, str);
				pProp->AddOption(str);
				AfxLoadString(IDS_KO, str);
				pProp->AddOption(str);
				AfxLoadString(IDS_KU, str);
				pProp->AddOption(str);
				AfxLoadString(IDS_TR, str);
				pProp->AddOption(str);
				AfxLoadString(IDS_VREZKA, str);
				pProp->AddOption(str);
			}
		}
		if (bAdd) m_wndPropList.AddProperty(pProp, FALSE,FALSE);
	}
	if (m_pPnN->m_MNEA == "ар")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(nID, E_GROUP_IZD);

		AddProp(pGroup1, IDS_AR_LEN, S_RoundV(m_pPnN->m_RAOT, 1), IDS_AR_LEN_C, E_ARM_LEN, nullptr, &m_pPnN->m_RAOT);
		AddProp(pGroup1, IDS_AR_VES, S_RoundV(m_pPnN->m_VESA, 1), IDS_AR_VES_C, E_ARM_VES, nullptr, &m_pPnN->m_VESA);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	else if (m_pPnN->m_MNEA == "ои")
	{
		UINT arrIDS[] = {nID, E_GROUP_OTVIZ, E_RAOT, E_VESOTV, E_MATOTV, E_NOTO_OTV, E_RATO_OTV};
		AddOtvod(arrIDS);
	}
	else if (m_pPnN->m_MNEA == "ос")
	{
		UINT arrIDS[] = {nID, E_GROUP_OTVSV, E_RAOT_SV, E_VESOTV_SV, E_MATOTV_SV, E_NOTO_SV, E_RATO_SV};
		AddOtvod(arrIDS);
	}
	else if (m_pPnN->m_MNEA == "оф")
	{
		UINT arrIDS[] = {nID, E_GROUP_OTVFL, E_RAOT_OF, E_VESOTV_OF, E_MATOTV_OF, E_NOTO_OF, E_RATO_OF};
		AddOtvod(arrIDS);
	}
	else if (m_pPnN->m_MNEA == "ко")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(nID, E_GROUP_KO);
		pProp = AddProp(pGroup1, IDS_KO_SEFF, S_RoundV(m_pPnN->m_RAOT, 1), IDS_KO_SEFF_C, E_KO_SEFF, nullptr, &m_pPnN->m_RAOT);
		pProp->AllowEdit(TRUE);
		AddProp(pGroup1, IDS_KO_PODATL, S_RoundV(m_pPnN->m_KOTR, 5), IDS_KO_PODATL_C, E_KO_PODATL, nullptr, &m_pPnN->m_KOTR);
		AddProp(pGroup1, IDS_KO_OS_HOD, S_RoundV(m_pPnN->m_DIGI, 1), IDS_KO_OS_HOD_C, E_KO_OS_HOD, nullptr, &m_pPnN->m_DIGI);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	else if (m_pPnN->m_MNEA == "ку")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(nID, E_GROUP_KU);
		AddProp(pGroup1, IDS_KU_PODATL, S_RoundV(m_pPnN->m_KOTR, 5), IDS_KU_PODATL_C, E_KU_PODATL, nullptr, &m_pPnN->m_KOTR);
		AddProp(pGroup1, IDS_KU_LEN, S_RoundV(m_pPnN->m_DIGI, 1), IDS_KU_LEN, E_KU_LEN, nullptr, &m_pPnN->m_DIGI);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	else if (m_pPnN->m_MNEA == "тр")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(nID, E_GROUP_TR);
		pProp = AddProp(pGroup1, IDS_TR_MAT, _variant_t(m_pPnN->m_MARI), IDS_TR_MAT_C, E_TR_MAT, nullptr, &m_pPnN->m_MARI);
		AddMaterial(pProp);
		AddProp(pGroup1, IDS_TR_VES, S_RoundV(m_pPnN->m_VESA, 1),IDS_TR_VES_C, E_TR_VES, nullptr, &m_pPnN->m_VESA);
		CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_MAGISTRAL, 2013);
		AddProp(pGroup2, IDS_MAG_NOTO, S_RoundV(m_pPnN->m_NOTO, 1), IDS_MAG_NOTO_C, E_TR_NOTO_MAG, nullptr, &m_pPnN->m_NOTO);
		AddProp(pGroup2, IDS_MAG_RATO, S_RoundV(m_pPnN->m_RATO, 1), IDS_MAG_RATO_C, E_TR_RATO_MAG, nullptr, &m_pPnN->m_RATO);
		AddProp(pGroup2, IDS_MAG_LEN, S_RoundV(m_pPnN->m_KORPUS, 0), IDS_MAG_LEN_C, E_TR_LEN_MAG, nullptr, &m_pPnN->m_KORPUS);
		if (bAddGroup) pGroup1->AddSubItem(pGroup2);
		pGroup2 = AddPGroup(IDS_OTV, 2014);
		pProp = AddProp(pGroup2, IDS_OTV_DIAM, _variant_t(long(m_pPnN->m_NONE)), IDS_OTV_DIAM_C, E_TR_DIAM_OTV, nullptr, m_pPnN);
		CTroinicsSet set1;
		set1.m_strPath = _T(".");
		set1.m_strTable.Format(_T("[Troinics] where DIAM=%g order by DIAMSH"), m_pPnN->m_DIAM);
		set1.Open();
		while (!set1.IsEOF())
		{
			CString str;
			str.Format(_T("%g"), set1.m_DIAMSH);
			pProp->AddOption(str);
			set1.MoveNext();
		}
		set1.Close();
		AddProp(pGroup2, IDS_OTVL_NOTO, S_RoundV(m_pPnN->m_VEYS, 1), IDS_OTVL_NOTO_C, E_TR_NOTO_OTV, nullptr, &m_pPnN->m_VEYS);
		AddProp(pGroup2, IDS_OTVL_RATO, S_RoundV(m_pPnN->m_DIGI, 1), IDS_OTVL_RATO_C, E_TR_RATO_OTV, nullptr, &m_pPnN->m_DIGI);
		AddProp(pGroup2, IDS_OTVL_VYS, S_RoundV(m_pPnN->m_SILX, 1), IDS_OTVL_VYS_C, E_TR_VYS_OTV, nullptr, &m_pPnN->m_SILX);
		if (bAddGroup) pGroup1->AddSubItem(pGroup2);
		pGroup2 = AddPGroup(IDS_NAKL, E_GROUP_NAKL);
		AddProp(pGroup2, IDS_NAKL_NOTO, S_RoundV(m_pPnN->m_DEFZ, 1), IDS_NAKL_NOTO_C, E_TR_NOTO_NAKL, nullptr, &m_pPnN->m_DEFZ);
		AddProp(pGroup2, IDS_NAKL_SHIR, S_RoundV(m_pPnN->m_RASG, 1), IDS_NAKL_SHIR_C, E_TR_SHIR_NAKL, nullptr, &m_pPnN->m_RASG);
		if (bAddGroup) pGroup1->AddSubItem(pGroup2);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	else if (m_pPnN->m_VREZKA == "св")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(nID, E_GROUP_VREZKA);
		AddProp(pGroup1, IDS_VR_KOPR, S_RoundV(m_pPnN->m_DEFY, 1), IDS_VR_KOPR_C, E_VR_KOPR, nullptr, &m_pPnN->m_DEFY);
		CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_VR_NAKL, 2017);
		AddProp(pGroup2, IDS_VR_NAKL_NOTO, S_RoundV(m_pPnN->m_DEFZ, 1), IDS_VR_NAKL_NOTO_C, E_VR_NOTO_NAKL, nullptr, &m_pPnN->m_DEFZ);
		AddProp(pGroup2, IDS_VR_NAKL_SHIR, S_RoundV(m_pPnN->m_RASG, 1), IDS_VR_NAKL_SHIR_C, E_VR_SHIR_NAKL, nullptr, &m_pPnN->m_RASG);
		if (bAddGroup) pGroup1->AddSubItem(pGroup2);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}

	CString strOpor;
	UINT nIDOpor = IDS_NONE;
	if (m_pPnN->m_MNEO == "мо")
		nIDOpor = IDS_MERT;
	else if (m_pPnN->m_MNEO == "ск")
		nIDOpor = IDS_SK;
	else if (m_pPnN->m_MNEO == "нп")
		nIDOpor = IDS_NAPR;
	else if (m_pPnN->m_MNEO == "пр")
		nIDOpor = IDS_UPR;
	else if (m_pPnN->m_MNEO == "пд")
		nIDOpor = IDS_ZHESTK_PODV;
	AfxLoadString(nIDOpor, strOpor.GetBufferSetLength(100));
	strOpor.ReleaseBuffer();
	if (m_nNodesSelected == 1)
	{
		pProp = AddProp(nullptr, IDS_OPOR, _variant_t(strOpor), IDS_OPOR_C, E_OPOR_TYPE);
		m_setPGroups.insert(pProp->GetData());
		pProp->RemoveAllOptions();
		pProp->AllowEdit(FALSE);
		pProp->AddOption(LoadStr(IDS_NONE));
		if (m_pPnN->m_TIDE == "")
		{
			if (m_pPnN->m_MNEA == "")
			{
				pProp->AddOption(LoadStr(IDS_MERT));
			}
			if (m_pPnN->m_MNEA == "ар" || m_pPnN->m_MNEA == "")
			{
				pProp->AddOption(LoadStr(IDS_SK));
				pProp->AddOption(LoadStr(IDS_NAPR));
				if (fabs(m_pPnN->m_NAGV + 1) > 1e-6f)
				{
					pProp->AddOption(LoadStr(IDS_UPR));
					pProp->AddOption(LoadStr(IDS_ZHESTK_PODV));
				}
			}
		}
		if (bAdd) m_wndPropList.AddProperty(pProp, FALSE,FALSE);
	}
	if (m_nNodesSelected > 1 && m_pPnN->m_MNEO == "мо")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(IDS_MERT_O, E_GROUP_MO);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}

	if (m_pPnN->m_MNEO == "ск" || m_pPnN->m_MNEO == "нп")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(m_pPnN->m_MNEO == "ск" ? IDS_SK_O : IDS_NAPR_O, m_pPnN->m_MNEO == "ск" ? E_GROUP_SK : E_GROUP_NP);
		AddProp(pGroup1, IDS_SK_KOTR, S_RoundV(m_pPnN->m_KOTR, 1), IDS_SK_KOTR_C, m_pPnN->m_MNEO == "ск" ? E_SK_KOTR : E_NP_KOTR, nullptr, &m_pPnN->m_KOTR);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	else if (m_pPnN->m_MNEO == "пр")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(IDS_UPR_O, E_GROUP_UPR_OP);
		AddProp(pGroup1, IDS_UPR_NTG, _variant_t(long(m_pPnN->m_SEOP)), IDS_UPR_NTG_C, E_UOP_NTG, nullptr, &m_pPnN->m_SEOP);
		AddProp(pGroup1, IDS_UPR_IZM_NAGR, S_RoundV(m_pPnN->m_NOTO, 1), IDS_UPR_IZM_NAGR, E_UOP_IZM_NAGR, nullptr, &m_pPnN->m_NOTO);
		AddProp(pGroup1, IDS_UPR_KZAP, S_RoundV(m_pPnN->m_RATO, 1), IDS_UPR_KZAP_C, E_UOP_KZAP, nullptr, &m_pPnN->m_RATO);
		AddProp(pGroup1, IDS_UPR_PODD_US, S_RoundV(m_pPnN->m_VEYS, 1), IDS_UPR_PODD_US_C, E_UOP_PODD_US, nullptr, &m_pPnN->m_VEYS);
		AddProp(pGroup1, IDS_UPR_PODATL, S_RoundV(m_pPnN->m_KOTR, 5), IDS_UPR_PODATL_C, E_UOP_PODATL, nullptr, &m_pPnN->m_KOTR);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	else if (m_pPnN->m_MNEO == "пд")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(nIDOpor, E_GROUP_PD_ZHESTK);
		AddProp(pGroup1, IDS_ZHP_LEN_TYAGI, S_RoundV(m_pPnN->m_DIGI, 1), IDS_ZHP_LEN_TYAGI_C, E_ZHP_LEN_TYAGI, nullptr, &m_pPnN->m_DIGI);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
	CString strDef;
	UINT nIDDef = IDS_NONE;
	if (m_pPnN->m_TIDE == "рс")
		nIDDef = IDS_RAST;
	else if (m_pPnN->m_TIDE == "сж")
		nIDDef = IDS_SG;
	AfxLoadString(nIDDef, strDef.GetBufferSetLength(100));
	strDef.ReleaseBuffer();
	if (m_nNodesSelected == 1)
	{
		pProp = AddProp(nullptr, IDS_DEF, _variant_t(strDef), IDS_DEF_C, E_DEF_TYPE);
		m_setPGroups.insert(pProp->GetData());
		pProp->RemoveAllOptions();
		pProp->AllowEdit(FALSE);
		pProp->AddOption(LoadStr(IDS_NONE));
		if (m_pPnN->m_MNEA == "" && m_pPnN->m_MNEO == "")
		{
			pProp->AddOption(LoadStr(IDS_RAST));
			pProp->AddOption(LoadStr(IDS_SG));
		}
		if (bAdd) m_wndPropList.AddProperty(pProp, FALSE,FALSE);
	}
	if (m_pPnN->m_TIDE == "рс" || m_pPnN->m_TIDE == "сж")
	{
		CMFCPropertyGridProperty* pGroup1 = AddPGroup(m_pPnN->m_TIDE == "рс" ? IDS_RAST : IDS_SG, m_pPnN->m_TIDE == "рс" ? E_GROUP_DEF_TYPE_RS : E_GROUP_DEF_TYPE_SG);
		AddProp(pGroup1, m_pPnN->m_TIDE == "рс" ? IDS_DEF_RAST : IDS_DEF_SG, S_RoundV(m_pPnN->m_RASG, 0), IDS_DEF_RSTSG_C, m_pPnN->m_TIDE == "рс" ? E_DEF_VAL_RAST : E_DEF_VAL_SG, nullptr, &m_pPnN->m_RASG);
		if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
	}
}

void CPropertiesWnd::FillNodeForces(void)
{
	CMFCPropertyGridProperty* pGroup1 = m_propNagr = AddPGroup(IDS_NAGR, E_GROUP_NAGR);
	CMFCPropertyGridProperty* pGroup2 = AddPGroup(IDS_NAGR_VES_ADD, E_GROUP_NAGR_VES_ADD);
	AddProp(pGroup2, IDS_UZ_SILVES, S_RoundV(m_pPnN->m_VESZ, 1), IDS_UZ_SILVES_C, E_UZ_SILVES, nullptr, &m_pPnN->m_VESZ);
	AddProp(pGroup2, IDS_UZ_MOMVESX, S_RoundV(m_pPnN->m_VESX, 1),IDS_UZ_MOMVESX_C, E_UZ_VES_MOMX, nullptr, &m_pPnN->m_VESX);
	AddProp(pGroup2, IDS_UZ_MOMVESY, S_RoundV(m_pPnN->m_VESY, 1), IDS_UZ_MOMVESY_C2, E_UZ_VES_MOMY, nullptr, &m_pPnN->m_VESY);
	if (bAddGroup) pGroup1->AddSubItem(pGroup2);

	pGroup2 = AddPGroup(IDS_NAGR_NONVES_ADD, E_GROUP_NAGR_NONVES_ADD);
	AddProp(pGroup2, IDS_UZ_SILX, S_RoundV(m_pPnN->m_SILX, 1),IDS_UZ_SILX_C, E_UZ_SILX, nullptr, &m_pPnN->m_SILX);
	AddProp(pGroup2, IDS_UZ_SILY, S_RoundV(m_pPnN->m_SILY, 1), IDS_UZ_SILY_C2, E_UZ_SILY, nullptr, &m_pPnN->m_SILY);
	AddProp(pGroup2, IDS_UZ_SILZ, S_RoundV(m_pPnN->m_SILZ, 1), IDS_UZ_SILZ_C, E_UZ_SILZ, nullptr, &m_pPnN->m_SILZ);
	AddProp(pGroup2, IDS_UZ_MOMX, S_RoundV(m_pPnN->m_MOMX, 1), IDS_UZ_MOMX_C, E_UZ_MOMX, nullptr, &m_pPnN->m_MOMX);
	AddProp(pGroup2, IDS_UZ_MOMY, S_RoundV(m_pPnN->m_MOMY, 1), IDS_UZ_MOMY_C, E_UZ_MOMY, nullptr, &m_pPnN->m_MOMY);
	AddProp(pGroup2, IDS_UZ_MOMZ, S_RoundV(m_pPnN->m_MOMZ, 1), IDS_UZ_MOMZ_C, E_UZ_MOMZ, nullptr, &m_pPnN->m_MOMZ);
	if (bAddGroup) pGroup1->AddSubItem(pGroup2);
	if (bAddGroup) m_wndPropList.AddProperty(pGroup1, FALSE,FALSE);
}


void CPropertiesWnd::RecalcXYZ()
{
	DWORD_PTR dwFocus = m_wndPropList.GetCurSel()->GetData();

	CDataExchange dx(this, TRUE);
	DoDataExchange(&dx, m_pPnN, m_pDoc);
	CDataExchange dx1(this, FALSE);
	DoDataExchange(&dx1, m_pPnN, m_pDoc);
	m_wndPropList.SetCurSel(m_wndPropList.FindItemByData(dwFocus));
}

void CPropertiesWnd::ToFloat(COleVariant& val)
{
	CString strVal = val.bstrVal;
	strVal.Replace(_T("."),_T(","));
	val.vt = VT_R4;
	swscanf_s(strVal.GetBuffer(), _T("%f"), &val.fltVal);
}

void CPropertiesWnd::ToFloat(const COleVariant& val, float& x)
{
	if (val.vt == VT_R4)
	{
		x = val.fltVal;
		return;
	}
	if (val.vt == VT_I4)
	{
		x = float(val.lVal);
		return;
	}

	CString strVal = val.bstrVal;
	strVal.Replace(_T("."),_T(","));
	swscanf_s(strVal.GetBuffer(), _T("%f"), &x);
}

void CPropertiesWnd::ToFloat(const COleVariant& val, DWORD_PTR dwData)
{
	float x;
	if (val.vt == VT_R4)
		x = val.fltVal;
	if (val.vt == VT_I4)
		x = float(val.lVal);
	else
	{
		CString strVal = val.bstrVal;
		strVal.Replace(_T("."),_T(","));
		swscanf_s(strVal.GetBuffer(), _T("%f"), &x);
	}
	for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		*(it->second) = x;
}

void CPropertiesWnd::ToStr(const COleVariant& val, CStringA& x)
{
	x = val.bstrVal;
}

void CPropertiesWnd::ToStr(const COleVariant& val, DWORD_PTR dwData)
{
	for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		*reinterpret_cast<CStringA *>(it->second) = val.bstrVal;
}

template <typename T1, typename T2>
size_t OffsetOf(T1* val, T2* base)
{
	return (reinterpret_cast<BYTE *>(val) - reinterpret_cast<BYTE *>(base));
}

template <typename T1, typename T2>
CPipeAndNode* GetPnN(float* ptr, T1* val, T2* base)
{
	return reinterpret_cast<CPipeAndNode *>(reinterpret_cast<BYTE *>(ptr) - OffsetOf(val, base));
}


bool bUpdatedByParent = false;


LRESULT CPropertiesWnd::OnPropChange(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = reinterpret_cast<CMFCPropertyGridProperty*>(lParam);
	DWORD_PTR dwData = pProp->GetData();
	COleVariant val = pProp->GetOriginalValue();
	COleVariant valNew = pProp->GetValue();
	//bool bPodzem = fabs(m_pPnN->m_NAGV+1)<1e-6;

	switch (dwData)
	{
	case E_PIPE_TYPE:
		{
			CString strVal = valNew.bstrVal;
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				TCHAR strPodzem[256];
				AfxLoadString(IDS_PODZEM, strPodzem);
				bool bPodzem1 = strVal == strPodzem;
				set.m_strPath = _T(".");
				set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by DIAM, PODZ"),
				                                                                                    pPnN->m_DIAM, int(bPodzem1));
				set.Open();
				if (bPodzem1)
				{
					if (pPnN->m_NAGV != -1)
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
		for (int i = 0; i < pProp->GetSubItemsCount(); i++)
			OnPropChange(0, LPARAM(pProp->GetSubItem(i)));
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
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.l_plan = valNew.fltVal;
				pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
				pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
			}
			RecalcXYZ();
		}
		break;
	case E_LEN_TOTAL: // Длина участка
		{
			ToFloat(valNew);
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				float scl;
				if (a1.l_gen < 1e-6f)
				{
					scl = 1.0f;
					m_pPnN->m_OSIX = valNew.fltVal;
				}
				else
					scl = valNew.fltVal / a1.l_gen;

				pPnN->m_OSIX = Round(pPnN->m_OSIX * scl, 3);
				pPnN->m_OSIY = Round(pPnN->m_OSIY * scl, 3);
				pPnN->m_OSIZ = Round(pPnN->m_OSIZ * scl, 3);
			}
			RecalcXYZ();
			break;
		}
	case E_ANG_PLAN_ABS: // Угол в плане абсолютный
		ToFloat(valNew);
		for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		{
			CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
			a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
			a1.a_plan = float(valNew.fltVal);
			pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
			pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
		}
		RecalcXYZ();
		break;
	case E_ANG_PLAN_REL: // Угол в плане относительно предыдущего участка
		{
			float ang;
			if (valNew.vt == VT_BSTR)
			{
				CString strVal = valNew.bstrVal;
				swscanf_s(strVal, _T("%d"), &valNew.intVal);
				valNew.vt = VT_I4;
			}

			if (valNew.vt == VT_I4)
			{
				if (valNew.intVal == val.intVal + 1)
				{
					pProp->SetValue(val.intVal < 0 ? _variant_t(0l) : _variant_t(90l));
				}
				else if (valNew.intVal == val.intVal - 1)
				{
					pProp->SetValue(val.intVal > 0 ? _variant_t(0l) : _variant_t(-90l));
				}
				pProp->SetOriginalValue(pProp->GetValue());
				valNew = pProp->GetValue();
				ToFloat(valNew, ang);
			}
			else
			{
				ToFloat(valNew, ang);
			}
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
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
			if (valNew.vt == VT_BSTR)
			{
				CString strVal = valNew.bstrVal;
				swscanf_s(strVal, _T("%d"), &valNew.intVal);
				valNew.vt = VT_I4;
			}
			if (val.vt == VT_BSTR)
			{
				CString strVal = val.bstrVal;
				if (strVal.GetLength() > 0)
					swscanf_s(strVal, _T("%d"), &val.intVal);
				else
					val.intVal = 0;
				val.vt = VT_I4;
			}
			CMFCSpinButtonCtrlMy* pSpin = dynamic_cast<CMFCPropertyGridProperty1 *>(pProp)->GetSpinCtrl();
			if (pSpin)
			{
				if (pSpin->GetIsButtonUp())
				{
					bButtons = true;
					pProp->SetValue(val.intVal < 0 ? _variant_t(0l) : _variant_t(90l));
				}
				else if (pSpin->GetIsButtonDown())
				{
					bButtons = true;
					pProp->SetValue(val.intVal > 0 ? _variant_t(0l) : _variant_t(-90l));
				}
				else
				{
					if (valNew.intVal == 1)
					{
						bButtons = true;
						pProp->SetValue(val.intVal < 0 ? _variant_t(0l) : _variant_t(90l));
					}
					else if (valNew.intVal == - 1)
					{
						bButtons = true;
						pProp->SetValue(val.intVal > 0 ? _variant_t(0l) : _variant_t(-90l));
					}
				}
				ToFloat(pProp->GetValue(), ang);
			}
			else
			{
				ToFloat(valNew, ang);
			}
			pProp->SetOriginalValue(variant_t(S_Round(ang, 1)));
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
				a1.a_prof = ang;
				if (bButtons)
				{
					if (a1.a_prof == 0.0f)
					{
						if (a1.l_plan < 0.001f)
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
					if (a1.l_plan < 0.001f)
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
		for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		{
			CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
			a1.calc_angles(pPnN->m_OSIX, pPnN->m_OSIY, pPnN->m_OSIZ);
			a1.uklon = valNew.fltVal;
			a1.a_prof = RadToDeg(atan(a1.uklon / 1000));
			//a1.l_plan = a1.l_gen*cos(DegToRad(a1.a_prof));
			pPnN->m_OSIX = Round(a1.l_plan * cos(DegToRad(a1.a_plan)), 3);
			pPnN->m_OSIY = Round(a1.l_plan * sin(DegToRad(a1.a_plan)), 3);
			pPnN->m_OSIZ = Round(a1.l_plan * tan(DegToRad(a1.a_prof)), 3);
		}
		RecalcXYZ();
		break;
	case E_DIAM:
		for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		{
			CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
			CPipesSet set;
			ToFloat(valNew, pPnN->m_DIAM);
			bool b_podzem = fabs(pPnN->m_NAGV + 1) < 1e-6;
			set.m_strPath = _T(".");
			set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ  order by DIAM, PODZ"),
			                                                                                    pPnN->m_DIAM, int(b_podzem));
			set.Open();
			//while (!set.IsEOF())
			{
				pPnN->m_NAMA = set.m_NAMA;
				pPnN->m_NTOS = set.m_NTOS;
				pPnN->m_RTOS = set.m_NTOS - set.m_RTOS;
				pPnN->m_VETR = set.m_VETR;
				pPnN->m_VEIZ = set.m_VEIZ;
				pPnN->m_VEPR = set.m_VEPR;
				if (b_podzem)
				{
					pPnN->m_NAGX = set.m_DIIZ;
					pPnN->m_SHTR = set.m_SHTR;
				}
				pPnN->m_RAOT = set.m_RAOT;
				pPnN->m_MARI = set.m_MARI;
				pPnN->m_NOTO = set.m_NOTO;
				pPnN->m_RATO = set.m_NOTO - set.m_RATO;
				if (pPnN->m_MNEA == "ко")
				{
					m_pPnN->m_RAOT = set.m_SEFF;
					m_pPnN->m_KOTR = set.m_KPOD;
				}
			}
			set.Close();
		}
		RecalcXYZ();
		break;
	case E_MATERIAL:
		ToStr(valNew, dwData);
		break;
	case E_OS_TR_BEG:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_OS_TR1, m_pPnN);
				pPnN->m_OS_TR1 = valNew.fltVal;
				pPnN->m_VIZA = pPnN->m_OS_TR1 - pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for (auto p = &(arr.InFirst(int(pPnN->m_NAYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_OS_TR2 = pPnN->m_OS_TR1;
						p->m_pPnN->m_VIZA2 = p->m_pPnN->m_OS_TR2 - p->m_pPnN->m_NAGX / 2000;
					}
				for (auto p = &arr.OutFirst(int(pPnN->m_NAYZ), cnt); arr.HasOut(cnt); p = &arr.OutNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_OS_TR1 = pPnN->m_OS_TR1;
						p->m_pPnN->m_VIZA = p->m_pPnN->m_OS_TR1 - p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if (!bUpdatedByParent) RecalcXYZ();
		break;
	case E_OS_TR_END:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_OS_TR2, m_pPnN);
				pPnN->m_OS_TR2 = valNew.fltVal;
				pPnN->m_VIZA2 = pPnN->m_OS_TR2 - pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for (Pipe* p = &(arr.InFirst(int(pPnN->m_KOYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_OS_TR2 = pPnN->m_OS_TR2;
						p->m_pPnN->m_VIZA2 = p->m_pPnN->m_OS_TR2 - p->m_pPnN->m_NAGX / 2000;
					}
				for (Pipe* p = &(arr.OutFirst(int(pPnN->m_KOYZ), cnt)); arr.HasOut(cnt); p = &arr.OutNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_OS_TR1 = pPnN->m_OS_TR2;
						p->m_pPnN->m_VIZA = p->m_pPnN->m_OS_TR1 - p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if (!bUpdatedByParent) RecalcXYZ();
		break;
	case E_VIZA_BEG:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_VIZA, m_pPnN);
				pPnN->m_VIZA = valNew.fltVal;
				pPnN->m_OS_TR1 = pPnN->m_VIZA + pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for (Pipe* p = &(arr.InFirst(int(pPnN->m_NAYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_VIZA2 = pPnN->m_VIZA;
						p->m_pPnN->m_OS_TR2 = p->m_pPnN->m_VIZA2 + p->m_pPnN->m_NAGX / 2000;
					}
				for (Pipe* p = &(arr.OutFirst(int(pPnN->m_NAYZ), cnt)); arr.HasOut(cnt); p = &arr.OutNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_VIZA = pPnN->m_VIZA;
						p->m_pPnN->m_OS_TR1 = p->m_pPnN->m_VIZA + p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if (!bUpdatedByParent) RecalcXYZ();
		break;
	case E_VIZA_END:
		{
			ToFloat(valNew);
			CPipeArray arr;
			arr.copy_pipes(m_pDoc->m_pipes.m_vecPnN);
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = GetPnN(it->second, &m_pPnN->m_VIZA2, m_pPnN);
				pPnN->m_VIZA2 = valNew.fltVal;
				pPnN->m_OS_TR2 = pPnN->m_VIZA2 + pPnN->m_NAGX / 2000;
				CPipeArrayContext cnt;
				for (Pipe* p = &(arr.InFirst(int(pPnN->m_KOYZ), cnt)); arr.HasIn(cnt); p = &arr.InNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_VIZA2 = pPnN->m_VIZA2;
						p->m_pPnN->m_OS_TR2 = p->m_pPnN->m_VIZA2 + p->m_pPnN->m_NAGX / 2000;
					}
				for (Pipe* p = &(arr.OutFirst(int(pPnN->m_KOYZ), cnt)); arr.HasOut(cnt); p = &arr.OutNext(cnt))
					if (p->Podzem)
					{
						p->m_pPnN->m_VIZA = pPnN->m_VIZA2;
						p->m_pPnN->m_OS_TR1 = p->m_pPnN->m_VIZA + p->m_pPnN->m_NAGX / 2000;
					}
			}
		}
		if (!bUpdatedByParent) RecalcXYZ();
		break;
	case E_GRTYPE_UP:
	case E_GRTYPE_OSN:
	case E_GRTYPE_SIDE:
		for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
		{
			int n = int((*(it->second)) * 10 + 0.5f);
			int nSide = n % 10;
			n /= 100;
			int nUp = n % 10;
			n /= 100;
			int nDown = n;
			switch (dwData)
			{
			case E_GRTYPE_UP:
				nUp = valNew.intVal;
				break;
			case E_GRTYPE_OSN:
				nDown = valNew.intVal;
				break;
			case E_GRTYPE_SIDE:
				nSide = valNew.intVal;
				break;
			}
			*it->second = Round(float(nSide) / 10 + nUp * 10 + nDown * 1000, 1);
		}
		break;
	case E_IZD_TYPE:
		{
			CString strVal = valNew.bstrVal;
			seta.m_strPath = _T(".");
			seta.m_strTable.Format(_T("[Armat] WHERE DIAM = %g order by DIAM"),
			                                                                  m_pPnN->m_DIAM);
			if (!seta.Open())
				AfxMessageBox(_T("Can't open Pipes.dbf"));
			TCHAR strNone[256];
			AfxLoadString(IDS_NONE, strNone);
			if (strVal == strNone)
			{
				m_pPnN->m_MNEA = "";
				m_pPnN->m_VREZKA = "";
			}
			else if (strVal == LoadStr(IDS_ARMAT))
			{
				m_pPnN->m_MNEA = "ар";
				m_pPnN->m_RAOT = seta.m_RAOT1;
				m_pPnN->m_VESA = seta.m_VESA1;
				m_pPnN->m_VREZKA = "";
			}
			else if (strVal == LoadStr(IDS_OTVIZ))
			{
				m_pPnN->m_MNEA = "ои";
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = "";
			}
			else if (strVal == LoadStr(IDS_OTVSV))
			{
				m_pPnN->m_MNEA = "ос";
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = "";
			}
			else if (strVal == LoadStr(IDS_OTVFL))
			{
				m_pPnN->m_MNEA = "оф";
				m_pPnN->m_RAOT = seta.m_RAOT;
				m_pPnN->m_NOTO = seta.m_NOTO;
				m_pPnN->m_RATO = seta.m_NOTO - seta.m_RATO;
				m_pPnN->m_VESA = seta.m_VESA;
				m_pPnN->m_MARI = m_pPnN->m_NAMA;
				m_pPnN->m_VREZKA = "";
			}
			else if (strVal == LoadStr(IDS_KO))
			{
				set.m_strPath = _T(".");
				set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g order by DIAM"),
				                                                                 m_pPnN->m_DIAM);
				set.Open();
				m_pPnN->m_MNEA = "ко";
				m_pPnN->m_RAOT = set.m_SEFF;
				m_pPnN->m_KOTR = set.m_KPOD;
				m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = "";
				set.Close();
			}
			else if (strVal == LoadStr(IDS_KU))
			{
				m_pPnN->m_MNEA = "ку";
				m_pPnN->m_KOTR = m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = "";
			}
			else if (strVal == LoadStr(IDS_TR))
			{
				m_pPnN->m_MNEA = "тр";
				m_pPnN->m_KOTR = m_pPnN->m_DIGI = 0;
				m_pPnN->m_VREZKA = "";
			}

			else if (strVal == LoadStr(IDS_VREZKA))
			{
				m_pPnN->m_VREZKA = "св";
				m_pPnN->m_MNEA = "";
			}
			seta.Close();
			CDataExchange dx(this, FALSE);
			DoDataExchange(&dx, m_pPnN, m_pDoc);
		}
		break;

	case E_OPOR_TYPE:
		{
			CString strVal = valNew.bstrVal;
			if (strVal == LoadStr(IDS_NONE))
				ToStr(_variant_t(_T("")), m_pPnN->m_MNEO);
			else if (strVal == LoadStr(IDS_MERT))
			{
				ToStr(_variant_t(_T("мо")), m_pPnN->m_MNEO);
			}
			else if (strVal == LoadStr(IDS_SK))
			{
				ToStr(_variant_t(_T("ск")), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.3f), m_pPnN->m_KOTR);
			}
			else if (strVal == LoadStr(IDS_NAPR))
			{
				ToStr(_variant_t(_T("нп")), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.3f), m_pPnN->m_KOTR);
			}
			else if (strVal == LoadStr(IDS_UPR))
			{
				ToStr(_variant_t(_T("пр")), m_pPnN->m_MNEO);
				ToFloat(_variant_t(1.0f), m_pPnN->m_SEOP);
				ToFloat(_variant_t(35.0f), m_pPnN->m_NOTO);
				ToFloat(_variant_t(1.0f), m_pPnN->m_RATO);
				ToFloat(_variant_t(0.0f), m_pPnN->m_VEYS);
				ToFloat(_variant_t(0.0f), m_pPnN->m_KOTR);
			}
			else if (strVal == LoadStr(IDS_ZHESTK_PODV))
			{
				ToStr(_variant_t(_T("пд")), m_pPnN->m_MNEO);
				ToFloat(_variant_t(0.0f), m_pPnN->m_DIGI);
			}
			OnLBChange();
			break;
		}
	case E_DEF_TYPE:
		{
			CString strVal = valNew.bstrVal;
			if (strVal == LoadStr(IDS_NONE))
				m_pPnN->m_TIDE = "";
			else if (strVal == LoadStr(IDS_RAST))
			{
				m_pPnN->m_TIDE = "рс";
				//m_pPnN->m_RASG=0.0f;
			}
			else if (strVal == LoadStr(IDS_SG))
			{
				m_pPnN->m_TIDE = "сж";
				//m_pPnN->m_RASG=0.0f;
			}
			OnLBChange();
		}
		break;
	case E_MATOTV:
	case E_TR_MAT:
	case E_MATOTV_SV:
	case E_MATOTV_OF:
		ToStr(valNew, dwData);
		break;
	case E_TR_DIAM_OTV:
		{
			for (auto it = m_mapProp.find(dwData); it != m_mapProp.end() && it->first == dwData; ++it)
			{
				CPipeAndNode* pPnN = reinterpret_cast<CPipeAndNode*>(it->second);
				ToFloat(valNew, pPnN->m_NONE);
				CTroinicsSet set1;
				set1.m_strPath = _T(".");
				set1.m_strTable.Format(_T("[Troinics] WHERE DIAM = %g and DIAMSH = %g"),
				                                                                       pPnN->m_DIAM, pPnN->m_NONE);
				if (!set1.Open())
					AfxMessageBox(_T("Can't open Pipes.dbf"));
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
	return 0;
}


void CPropertiesWnd::OnLBChange(void)
{
	int nSel = m_wndObjectCombo.GetCurSel();
	if (m_pDoc->vecSel.size() >= 2)
	{
		//m_wndObjectCombo.SetCurSel(0);
		if (nSel != 0)
		{
			auto it = m_pDoc->vecSel.begin();
			// ReSharper disable once CppPossiblyErroneousEmptyStatements
			for (int i = nSel - 1; i > 0; i--) ++it;
			int b = it->SelNAYZ;
			int e = it->SelKOYZ;
			m_pDoc->vecSel.clear();
			m_pDoc->Select(b, e);
		}
		return;
	}

	if (nSel == 0)
	{
		m_pDoc->Select(int(m_pPnN->m_NAYZ), int(m_pPnN->m_KOYZ));
	}
	else
	{
		m_pDoc->Select(int(m_pPnN->m_KOYZ), int(m_pPnN->m_KOYZ));
	}
}


void CPropertiesWnd::OnPropMert()
{
	if (!m_pPnN) return;
	m_wndObjectCombo.SetCurSel(1);
	if (m_pPnN->m_MNEO == "мо")
		m_pPnN->m_MNEO = "";
	else
		m_pPnN->m_MNEO = "мо";
	m_pDoc->PnNIsUpdated();
	OnLBChange();
}

void CPropertiesWnd::OnUpdatePropMert(CCmdUI* pCmdUI)
{
	if (!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->SetCheck(m_pPnN->m_MNEO == "мо");
	pCmdUI->Enable(m_pPnN->m_MNEA == "" && m_pPnN->m_TIDE == "");
}

void CPropertiesWnd::OnPropSk()
{
	if (!m_pPnN) return;
	m_wndObjectCombo.SetCurSel(1);
	if (m_pPnN->m_MNEO == "ск")
		m_pPnN->m_MNEO = "";
	else
	{
		m_pPnN->m_MNEO = "ск";
		m_pPnN->m_KOTR = 0.3f;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChange();
}

void CPropertiesWnd::OnUpdatePropSk(CCmdUI* pCmdUI)
{
	if (!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->SetCheck(m_pPnN->m_MNEO == "ск");
	pCmdUI->Enable((m_pPnN->m_MNEA == "" || m_pPnN->m_MNEA == "ар") && m_pPnN->m_TIDE == "");
}

void CPropertiesWnd::OnPropNapr()
{
	if (!m_pPnN) return;
	m_wndObjectCombo.SetCurSel(1);
	if (m_pPnN->m_MNEO == "нп")
		m_pPnN->m_MNEO = "";
	else
	{
		m_pPnN->m_MNEO = "нп";
		m_pPnN->m_KOTR = 0.3f;
	}
	m_pDoc->PnNIsUpdated();
	OnLBChange();
}

void CPropertiesWnd::OnUpdatePropNapr(CCmdUI* pCmdUI)
{
	if (!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->SetCheck(m_pPnN->m_MNEO == "нп");
	pCmdUI->Enable((m_pPnN->m_MNEA == "" || m_pPnN->m_MNEA == "ар") && m_pPnN->m_TIDE == "");
}

void CPropertiesWnd::OnPropOtvSv()
{
	if (!m_pPnN) return;
	m_wndObjectCombo.SetCurSel(1);
	if (m_pPnN->m_MNEA == "ос")
		m_pPnN->m_MNEA = "";
	else
	{
		m_pPnN->m_MNEA = "ос";
	}
	m_pDoc->PnNIsUpdated();
	OnLBChange();
	m_pIzdProp = m_wndPropList.FindItemByData(E_IZD_TYPE);
	if (m_pIzdProp && m_pPnN->m_MNEA == "ос")
		OnPropChange(0, LPARAM(m_pIzdProp));
}

void CPropertiesWnd::OnUpdatePropOtvSv(CCmdUI* pCmdUI)
{
	if (!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->SetCheck(m_pPnN->m_MNEA == "ос");
	pCmdUI->Enable(m_pPnN->m_MNEO == "" && m_pPnN->m_TIDE == "");
}

void CPropertiesWnd::OnPropOtvIz()
{
	if (!m_pPnN) return;
	m_wndObjectCombo.SetCurSel(1);
	if (m_pPnN->m_MNEA == "ои")
		m_pPnN->m_MNEA = "";
	else
	{
		m_pPnN->m_MNEA = "ои";
	}
	m_pDoc->PnNIsUpdated();
	OnLBChange();
	if (m_pPnN->m_MNEA == "ои")
		OnPropChange(0, LPARAM(m_pIzdProp));
}

void CPropertiesWnd::OnUpdatePropOtvIz(CCmdUI* pCmdUI)
{
	if (!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->SetCheck(m_pPnN->m_MNEA == "ои");
	pCmdUI->Enable(m_pPnN->m_MNEO == "" && m_pPnN->m_TIDE == "");
}

void CPropertiesWnd::OnPropArm()
{
	if (!m_pPnN) return;
	m_wndObjectCombo.SetCurSel(1);
	if (m_pPnN->m_MNEA == "ар")
		m_pPnN->m_MNEA = "";
	else
	{
		m_pPnN->m_MNEA = "ар";
	}
	m_pDoc->PnNIsUpdated();
	OnLBChange();
	if (m_pPnN->m_MNEA == "ар")
		OnPropChange(0, LPARAM(m_pIzdProp));
}

void CPropertiesWnd::OnUpdatePropArm(CCmdUI* pCmdUI)
{
	if (!m_pPnN || !m_pDoc || m_pDoc->vecSel.size() > 1)
	{
		pCmdUI->Enable(FALSE);
		return;
	}
	pCmdUI->SetCheck(m_pPnN->m_MNEA == "ар");
	pCmdUI->Enable((m_pPnN->m_MNEO == "" || m_pPnN->m_MNEO == "ск" || m_pPnN->m_MNEO == "нп") && m_pPnN->m_TIDE == "");
}

