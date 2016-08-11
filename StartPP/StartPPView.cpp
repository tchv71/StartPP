// StartPPView.cpp : реализация класса CStartPPView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "StartPP.h"
#endif

//#include <atltypes.h>
#include "Archive.h"
#include "StartPPSet.h"
#include "StartPPDoc.h"
#include "StartPPView.h"
//#include "MainFrm.h"
#include "DistDialog.h"
#include "PrintHelper.h"
#include "Resource.h"
#include "Strings.h"
#include "wxcrafter.h"
#include <math.h>
#include <wx/dcbuffer.h>
#include "main.h"
#include "MainFrame.h"
#include "Strings.h"
#include "wx/clipbrd.h"
#include "wxGLCanvasViewWnd.h"
#include "wx/aui/auibook.h"

//extern LPCTSTR LoadStr(UINT nID);


// CStartPPView
wxIMPLEMENT_DYNAMIC_CLASS(CStartPPView, wxView)
/*

BEGIN_MESSAGE_MAP(CStartPPView, CScrollView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CStartPPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ZOOM_IN, &CStartPPView::OnZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CStartPPView::OnZoomOut)
	ON_COMMAND(ID_ZOOM_ALL, &CStartPPView::OnZoomAll)
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_COMMAND(ID_ZOOM_WIN, &CStartPPView::OnZoomWin)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_WIN, &CStartPPView::OnUpdateZoomWin)
	ON_COMMAND(ID_PAN, &CStartPPView::OnPan)
	ON_UPDATE_COMMAND_UI(ID_PAN, &CStartPPView::OnUpdatePan)
	ON_COMMAND(ID_ROTATE, &CStartPPView::OnRotate)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, &CStartPPView::OnUpdateRotate)
	ON_COMMAND(ID_SELECT, &CStartPPView::OnSelect)
	ON_UPDATE_COMMAND_UI(ID_SELECT, &CStartPPView::OnUpdateSelect)
	ON_WM_SETCURSOR()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_VIEW_NODE_NUMS, &CStartPPView::OnViewNodeNums)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NODE_NUMS, &CStartPPView::OnUpdateViewNodeNums)
	ON_COMMAND(ID_VIEW_SIZES, &CStartPPView::OnViewSizes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SIZES, &CStartPPView::OnUpdateViewSizes)
	ON_COMMAND(ID_VIEW_APROF, &CStartPPView::OnViewAprof)
	ON_UPDATE_COMMAND_UI(ID_VIEW_APROF, &CStartPPView::OnUpdateViewAprof)
	ON_COMMAND(ID_VIEW_ELEMENTS, &CStartPPView::OnViewElements)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ELEMENTS, &CStartPPView::OnUpdateViewElements)
	ON_COMMAND(ID_VIEW_NODES, &CStartPPView::OnViewNodes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NODES, &CStartPPView::OnUpdateViewNodes)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SHOW_OGL, &CStartPPView::OnShowOgl)
	ON_UPDATE_COMMAND_UI(ID_SHOW_OGL, &CStartPPView::OnUpdateShowOgl)
	ON_UPDATE_COMMAND_UI(ID_DIST, &CStartPPView::OnUpdateDist)
	ON_COMMAND(ID_DIST, &CStartPPView::OnDist)
	ON_COMMAND(ID_VIEW_3DVIEWS_TOP, &CStartPPView::OnProj)
	ON_COMMAND(ID_VIEW_3DVIEWS_BACK, &CStartPPView::OnView3dviewsBack)
	ON_COMMAND(ID_VIEW_3DVIEWS_BOTTOM, &CStartPPView::OnView3dviewsBottom)
	ON_COMMAND(ID_VIEW_3DVIEWS_DIMETRY, &CStartPPView::OnView3dviewsDimetry)
	ON_COMMAND(ID_VIEW_3DVIEWS_FRONT, &CStartPPView::OnView3dviewsFront)
	ON_COMMAND(ID_VIEW_3DVIEWS_LEFT, &CStartPPView::OnView3dviewsLeft)
	ON_COMMAND(ID_VIEW_3DVIEWS_NE_ISO, &CStartPPView::OnView3dviewsNeIso)
	ON_COMMAND(ID_VIEW_3DVIEWS_NW_ISO, &CStartPPView::OnView3dviewsNwIso)
	ON_COMMAND(ID_VIEW_3DVIEWS_RIGHT, &CStartPPView::OnView3dviewsRight)
	ON_COMMAND(ID_VIEW_3DVIEWS_SE_ISO, &CStartPPView::OnView3dviewsSeIso)
	ON_COMMAND(ID_VIEW_3DVIEWS_SW_ISO, &CStartPPView::OnView3dviewsSwIso)
	ON_COMMAND(ID_VIEW_3DVIEWS_TOP, &CStartPPView::OnView3dviewsTop)
	ON_COMMAND(ID_EDIT_COPY, &CStartPPView::OnEditCopy)
	ON_WM_CHAR()
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CStartPPView::OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CStartPPView::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CStartPPView::OnEditCut)
	END_MESSAGE_MAP()
*/
BEGIN_EVENT_TABLE(CStartPPView, wxView)
	EVT_LEFT_DOWN(CStartPPView::OnLButtonDown)
	EVT_MOTION(CStartPPView::OnMouseMove)
	EVT_LEFT_UP(CStartPPView::OnLButtonUp)
	EVT_MOUSEWHEEL(CStartPPView::OnMouseWheel)
	EVT_SCROLL(CStartPPView::OnScroll)
	EVT_PAINT(CStartPPView::OnPaint)
	EVT_SIZE(CStartPPView::OnSize)
	EVT_MIDDLE_DOWN(CStartPPView::OnMButtonDown)
	EVT_MIDDLE_UP(CStartPPView::OnMButtonUp)
	EVT_CONTEXT_MENU(CStartPPView::OnContextMenu)
	EVT_TOOL(MainFrameBaseClass::wxID_ViewZoomIn, CStartPPView::OnZoomIn)
	EVT_TOOL(MainFrameBaseClass::wxID_ViewZoomOut, CStartPPView::OnZoomOut)
	EVT_TOOL(MainFrameBaseClass::wxID_ZOOM_ALL, CStartPPView::OnZoomAll)
	EVT_TOOL(MainFrameBaseClass::wxID_PAN, CStartPPView::OnPan)
	EVT_TOOL(MainFrameBaseClass::wxID_ZOOM_WIN, CStartPPView::OnZoomWin)
	EVT_TOOL(MainFrameBaseClass::wxID_ROTATE, CStartPPView::OnRotate)
	EVT_TOOL(MainFrameBaseClass::wxID_SELECT, CStartPPView::OnSelect)

	EVT_UPDATE_UI(MainFrameBaseClass::wxID_VIEW_NODE_NUMS, CStartPPView::OnUpdateViewNodeNums)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_VIEW_SIZES, CStartPPView::OnUpdateViewSizes)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_VIEW_APROF, CStartPPView::OnUpdateViewAprof)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_VIEW_ELEMENTS, CStartPPView::OnUpdateViewElements)
	EVT_UPDATE_UI(MainFrameBaseClass::wxID_VIEW_NODES, CStartPPView::OnUpdateViewNodes)
	EVT_TOOL(MainFrameBaseClass::wxID_VIEW_NODE_NUMS, CStartPPView::OnViewNodeNums)
	EVT_TOOL(MainFrameBaseClass::wxID_VIEW_SIZES, CStartPPView::OnViewSizes)
	EVT_TOOL(MainFrameBaseClass::wxID_VIEW_APROF, CStartPPView::OnViewAprof)
	EVT_TOOL(MainFrameBaseClass::wxID_VIEW_ELEMENTS, CStartPPView::OnViewElements)
	EVT_TOOL(MainFrameBaseClass::wxID_VIEW_NODES, CStartPPView::OnViewNodes)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_TOP, CStartPPView::OnView3dviewsTop)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_BACK, CStartPPView::OnView3dviewsBack)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_BOTTOM, CStartPPView::OnView3dviewsBottom)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_DIMETRY, CStartPPView::OnView3dviewsDimetry)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_FRONT, CStartPPView::OnView3dviewsFront)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_LEFT, CStartPPView::OnView3dviewsLeft)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_RIGHT, CStartPPView::OnView3dviewsRight)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_NE_ISO, CStartPPView::OnView3dviewsNeIso)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_NW_ISO, CStartPPView::OnView3dviewsNwIso)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_SE_ISO, CStartPPView::OnView3dviewsSeIso)
	EVT_MENU(MainFrameBaseClass::wxID_VIEW_3DVIEWS_SW_ISO, CStartPPView::OnView3dviewsSwIso)
	EVT_MENU(MainFrameBaseClass::wxID_PROJ, CStartPPView::OnProj)
	EVT_MENU(wxID_COPY, CStartPPView::OnEditCopy)
	EVT_MENU(wxID_CUT, CStartPPView::OnEditCut)

	EVT_MENU(MainFrameBaseClass::wxID_SHOW_OGL, CStartPPView::OnShowOgl)
	EVT_TIMER(wxID_ANY, CStartPPView::OnTimer)
END_EVENT_TABLE()
// создание/уничтожение CStartPPView

static bool  m_bInTabCloseHandler = false;


CStartPPView::CStartPPView(wxGLCanvas *parent)
	: wxView(), m_bShowOGL(false),
	  m_ScrPresenter(&m_pipeArray, m_rot, m_ViewSettings),
	  m_OglPresenter(&m_pipeArray, &m_rend, m_rot, m_ViewSettings, parent),
	  DownX(0), DownY(0), Down(false), Xorg1(0), Yorg1(0), z_rot1(0), x_rot1(0), bZoomed(false),
	  m_bInitialized(false)
	  , m_nView(0), m_menu(nullptr), m_wnd(parent),
	  m_bCut(false),
	  m_Timer(this)
{
	Create();
	//m_pFrame = static_cast<CMainFrame *>(AfxGetApp()->m_pMainWnd);
	m_rot.SetPredefinedView(DPT_Top);
	MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
	frame->GetAuiBook()->Connect(wxEVT_AUINOTEBOOK_PAGE_CLOSE, wxAuiNotebookEventHandler(CStartPPView::OnPageClose), nullptr, this);
	frame->GetAuiBook()->Connect(wxEVT_AUINOTEBOOK_PAGE_CHANGED, wxAuiNotebookEventHandler(CStartPPView::OnPageChanged), nullptr, this);
}

CStartPPView::~CStartPPView()
{
	//wxWindow* pWnd = wxGetApp().GetTopWindow();
	//wxWindow* pPanel = static_cast<MainFrame*>(pWnd)->GetGlPanel();
	static_cast<wxGLCanvasViewWnd*>(m_wnd)->SetChildView(nullptr);
	m_wnd->SetEventHandler(m_wnd);
	m_rend.ReleaseWindow();
}


void CStartPPView::OnTimer(wxTimerEvent& event)
{
	event.Skip();
	GetDocument()->m_pFrame->GetStatusBar()->SetStatusText(_T(""));
}
//void CStartPPView::OnInitialUpdate()

// печать CStartPPView


void CStartPPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	//AFXPrintPreview(this);
#endif
}




//IDR_POPUP_EDIT MENU
//BEGIN
//    POPUP "Редактировать"
//    BEGIN
//        MENUITEM "&Вырезать\tCtrl+X",           ID_EDIT_CUT
//        MENUITEM "&Копировать\tCtrl+C",         ID_EDIT_COPY
//        MENUITEM "Вст&авить\tCtrl+V",           ID_EDIT_PASTE
//        MENUITEM SEPARATOR
//        MENUITEM "Пока&зать все",               ID_ZOOM_ALL
//        MENUITEM "&Панорамирование",            ID_PAN
//        MENUITEM "Вра&щение",                   ID_ROTATE
//        MENUITEM "В&ыбор",                      ID_SELECT
//        MENUITEM SEPARATOR
//        MENUITEM "&Новый участок...",           ID_NEW_PIPE
//        MENUITEM "У&далить участки...",         ID_DEL_PIPE
//        MENUITEM "&Pазмножить участок...",      ID_MULT_PIPE
//        MENUITEM "Раз&бить участок...",         ID_NEW_NODE
//        MENUITEM "Коп&ировать параметры участка...", ID_COPY_PIPE_PARAMS
//        MENUITEM SEPARATOR
//        MENUITEM "Уда&лить узел...",            ID_DEL_NODE
//        MENUITEM "П&eредвинуть узел...",        ID_MOVE_NODE
//        MENUITEM "Перену&меровать узлы",        ID_RENUM_PIPES
//    END
//END

void CStartPPView::OnContextMenu(wxContextMenuEvent & event)
{

	if (!m_menu)
	{
		m_menu = new wxMenu();
		wxMenuItem* pItem = m_menu->Append(wxID_CUT,wxT("&Вырезать\tCtrl-X"));
		pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_CUT, wxART_MENU, wxDefaultSize));
		pItem = m_menu->Append(wxID_COPY,wxT("&Копировать\tCtrl-C"));
		pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_COPY, wxART_MENU, wxDefaultSize));
		pItem = m_menu->Append(wxID_PASTE,wxT("Вст&авить\tCtrl-V"));
		pItem->SetBitmap(wxArtProvider::GetBitmap(wxART_PASTE, wxART_MENU, wxDefaultSize));
		m_menu->AppendSeparator();
		pItem = m_menu->Append(MainFrameBaseClass::wxID_ZOOM_ALL,wxT("Пока&зать все"));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolViewZoomAll")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_PAN,wxT("&Панорамирование"));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolViewPan")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_ROTATE,wxT("Вра&щение"));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolViewRotate")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_SELECT,wxT("В&ыбор"));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolViewSelect")));
		m_menu->AppendSeparator();
		pItem = m_menu->Append(MainFrameBaseClass::wxID_NEW_PIPE,wxT("&Новый участок..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolNewPipe")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_DEL_PIPE, wxT("У&далить участки..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolDelPipe")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_MULT_PIPE, wxT("&Pазмножить участок..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolMultPipe")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_NEW_NODE, wxT("Раз&бить участок..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolNewNode")));
 		pItem = m_menu->Append(MainFrameBaseClass::wxID_COPY_PIPE_PARAMS, wxT("Коп&ировать параметры участка..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolCopyPipeParams")));
		m_menu->AppendSeparator();
		pItem = m_menu->Append(MainFrameBaseClass::wxID_DEL_NODE, wxT("Уда&лить узел..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolDelNode")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_MOVE_NODE, wxT("П&eредвинуть узел..."));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolMoveNode")));
		pItem = m_menu->Append(MainFrameBaseClass::wxID_RENUM_PIPES, wxT("Перену&меровать узлы"));
		pItem->SetBitmap(wxXmlResource::Get()->LoadBitmap(wxT("ToolRenumPipes")));
 	}
	m_wnd->PopupMenu(m_menu);
	event.Skip();
}



// обработчики сообщений CStartPPView


void CStartPPView::OnPaint(wxPaintEvent &event)
{
	wxClientDC dc(m_wnd);
	OnDraw(&dc);
	event.Skip();
}

void CStartPPView::OnDraw(CDC* pDC)
{
	double sx=0;
	double sy=0;
	pDC->GetUserScale(&sx,&sy);
	if (!pDC->IsKindOf(wxCLASSINFO(wxClientDC)))
	{
		OnPrint(pDC, nullptr);
		return;
	}
	//ScrollWindow(0,0);
	if (m_bShowOGL)
	{
		//m_OglPresenter.ghDC = pDC->AcquireHDC();
		//if (false && !dynamic_cast<CPaintDC*>(pDC))
		//{
		//	CRect clr;
		//	GetClientRect(&clr);
		//	m_OglPresenter.PrepareBmp(pDC,m_hWnd,clr);
		//}

		tmpPipeArray.copy_pipes_1(m_ScrPresenter.PipeArr, &m_rot); // Схема в исходном положении
		m_OglPresenter.PipeArr = &tmpPipeArray;
		GetDocument()->vecSel.SelNAYZ = int(GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx].m_NAYZ);
		GetDocument()->vecSel.SelKOYZ = int(GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx].m_KOYZ);
		//OGLShowPipes->rst=ShowPipes->rst;
		//m_ViewSettings.ShowNapr;
		CRect clr = m_wnd->GetClientRect();
		m_OglPresenter.Draw(clr, false);
	}
	else
	{
		//pDC->SetViewportOrg(0, 0);
		CRect clr;
		clr.SetSize(pDC->GetSize());//= m_wnd->GetClientRect();
		if (clr.GetWidth()==0 || clr.GetHeight()==0)
			return;
		clr.SetWidth(clr.GetWidth()/sx);
		clr.SetHeight(clr.GetHeight()/sy);
#if 1
		wxBufferedDC bdc(pDC,clr.GetSize());
		bdc.SetBackground(*wxWHITE_BRUSH);
		bdc.Clear();
		m_ScrPresenter.Draw(&bdc, &m_rot, clr);
#else
		wxBitmap bmp(clr.GetSize());
		wxMemoryDC memDC;
		memDC.SelectObject(bmp);
		memDC.SetBrush(*wxWHITE_BRUSH);
        memDC.Clear();
		memDC.SetPen(*wxWHITE_PEN);
		memDC.DrawRectangle(0,0,clr.GetWidth(),clr.GetHeight());
		m_ScrPresenter.Draw(&memDC, &m_rot, clr);
		pDC->Blit(wxPoint(0,0),clr.GetSize(),&memDC,wxPoint(0,0));
#endif
		return;
		/*
		SIZE szDoc;
		szDoc.x =LONG((m_ScrPresenter.x_max - m_ScrPresenter.x_min) *m_ScrPresenter.ScrScale + 2 *clr.GetWidth());
		szDoc.y =LONG((m_ScrPresenter.y_max - m_ScrPresenter.y_min) *m_ScrPresenter.ScrScale + 2 *clr.GetHeight());
		SetScrollSizes(MM_TEXT, szDoc);
		CPoint pt(LONG(clr.GetWidth() - m_ScrPresenter.x_min*m_ScrPresenter.ScrScale -  m_ScrPresenter.Xorg),
			LONG(clr.GetHeight() + m_ScrPresenter.y_max*m_ScrPresenter.ScrScale-  m_ScrPresenter.Yorg));
		SetScrollPos(SB_HORZ, pt.x);
		SetScrollPos(SB_VERT, pt.y);
		*/
	}
}


//void CStartPPView::OnSize(UINT nType, int cx, int cy)
void CStartPPView::OnSize(wxSizeEvent& event)
{
	if (m_wnd == nullptr)
		return;
	if (event.GetId() != m_wnd->GetId())
		return;
	int cx = event.m_size.x;
	int cy = event.m_size.y;
	//wxView::OnSize(0, cx, cy);
	if (m_OldSize.x == 0)
	{
		m_OldSize = CSize(cx, cy);
		return;
	}
	if (!m_bInitialized) return;
	if (cx == 0 || cy == 0)
		return;
	float S = float(cx) / m_OldSize.x;
	CRect clr =	m_wnd->GetClientRect();
	float cx1 = clr.x + float(clr.width) / 2;
	float cy1 = clr.y + float(clr.height) / 2;
	m_ViewSettings.ScrScale *= S;
	m_ViewSettings.Xorg = (m_ViewSettings.Xorg - float(m_OldSize.x) / 2) * S + cx1;
	m_ViewSettings.Yorg = (m_ViewSettings.Yorg - float(m_OldSize.y) / 2) * S + cy1;
	m_OldSize = CSize(cx, cy);
	Update();
	event.Skip();
}

void CStartPPView::Update()
{
	wxClientDC dc(m_wnd);
	OnDraw(&dc);
}

void CStartPPView::SetDocnameInTab() const
{
	wxString name = GetDocument()->GetUserReadableName();
	if (GetDocument()->IsModified())
		name += _T("*");
	MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
	wxAuiNotebook *pBook = frame->GetAuiBook();
	pBook->SetPageText(pBook->GetSelection(), name);
}

void CStartPPView::OnUpdate(wxView *sender, wxObject *hint)
{
	if (hint && (size_t)hint==2)
	{
		SetDocnameInTab();
		return;
	}

	m_ScrPresenter.pvecSel = m_OglPresenter.pvecSel = &(GetDocument()->vecSel);
	if(hint)
	{
		SetDocnameInTab();
		OnSetCursor();
		m_rot.SetPredefinedView(DPT_Top);
		m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
		m_ScrPresenter.DrawMain(true);

		CRect clr = m_wnd->GetClientRect();
		m_OldSize = CSize(clr.width, clr.height);
		//SetScaleToFitSize(clr.Size());
		CSize sz(0, 0);
		//SetScrollSizes(wxMM_TEXT, sz); //clr.Size());
		//CScrollView::OnInitialUpdate();
		m_bInitialized = true;
		//m_pFrame->	m_wndViewToolBar.RestoreOriginalstate();
		m_ScrPresenter.ZoomAll(clr, 40);
		return;
	}
	//CPipePresenter *p=m_bShowOGL? &m_OglPresenter : &m_ScrPresenter;
	m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	m_OglPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	if (GetDocument()->vecSel.size() <= 1)
	{
		CStartPPDoc *pDoc = GetDocument();
		
		SelStr S;
		if (pDoc->vecSel.size() == 1 && pDoc->vecSel.begin()->SelNAYZ == pDoc->vecSel.begin()->SelKOYZ)
		{
			S.SelNAYZ = S.SelKOYZ = int(pDoc->m_pipes.m_vecPnN[pDoc->m_pipes.m_nIdx].m_KOYZ);
		}
		else
		{
			S.SelNAYZ = int(pDoc->m_pipes.m_vecPnN[pDoc->m_pipes.m_nIdx].m_NAYZ);
			S.SelKOYZ = int(pDoc->m_pipes.m_vecPnN[pDoc->m_pipes.m_nIdx].m_KOYZ);
		}
		if (pDoc->vecSel.size() == 1)
		{
			pDoc->vecSel.clear();
			pDoc->vecSel.insert(S);
		}
		else
			pDoc->vecSel.insert(S);
	}
	Update();
}

enum E_STATE
{
    ST_PAN = 1,
    ST_SELECT,
    ST_ROTATE,
    ST_ZOOM_WIN,
    ST_SELECT_NODE
};

E_STATE state = E_STATE::ST_PAN, o_state;


//void CStartPPView::OnLButtonDown(UINT nFlags, CPoint point)
void CStartPPView::OnLButtonDown(wxMouseEvent& event)
{
	//m_ScrPresenter.SaveViewState();
	//if (PaintBox1->PopupMenu) oPopupMenu=PaintBox1->PopupMenu;
	//crSave=PaintBox1->Cursor;
	if (event.GetId() != m_wnd->GetId())
		return;

	CPoint point = event.GetPosition();
    if (!m_wnd->GetClientRect().Contains(point))
        return;
	m_wnd->CaptureMouse();//SetCapture();
    CString strPos = CString::Format(wxT("(%d,%d)"), point.x, point.y);
    LPCTSTR sPos = strPos;
	DownX = point.x;
	DownY = point.y;
	Down = TRUE;
	MovePt = point;
	//PaintBox1->Canvas->Pen->Color = clBlack;
	//PaintBox1->Canvas->Pen->Style = psDot;    //psDash;
	Xorg1 = m_ViewSettings.Xorg;
	Yorg1 = m_ViewSettings.Yorg;
	m_rot.GetRot(z_rot1, x_rot1);
	if (state == ST_SELECT)
	{
		CScreenPipePresenter* p = m_bShowOGL ? &m_OglPresenter : &m_ScrPresenter;
		if (event.AltDown())
			p->SelectPipeSegment(point.x, point.y);
		else if (event.ShiftDown())
			p->SelectPipesTo(point.x, point.y, event.ControlDown());
		else
			p->SelectPipe(point.x, point.y, event.ControlDown());
		GetDocument()->Select(GetDocument()->vecSel.SelNAYZ, GetDocument()->vecSel.SelKOYZ);
		//SetSel();
		Update();
	}
	else if (state == ST_PAN)
	{
		//PaintBox1->Cursor = TCursor(crHandGrab);
	}
	else if (state == ST_ROTATE)
	{
		tmpPipeArray.copy_pipes_1(&m_pipeArray, &m_rot); // Схема в исходном положении
	}
	else if (state == ST_SELECT_NODE)
	{
		CScreenPipePresenter* p = m_bShowOGL ? &m_OglPresenter : &m_ScrPresenter;
		CVecPnN& pipes = GetDocument()->m_pipes;
		CSelVec& sel = GetDocument()->vecSel;
		std::set<int> setNodes;
		std::vector<CPipeAndNode> vecCopy;
		for (auto& x : pipes.m_vecPnN)
			if (sel.Contains(x.m_NAYZ, x.m_KOYZ))
			{
				vecCopy.push_back(x);
				setNodes.insert(int(x.m_NAYZ));
				setNodes.insert(int(x.m_KOYZ));
			}
		p->IntSelectPipe(point.x, point.y, &setNodes);
		if (sel.SelNAYZ >= 0)
		{
			state = o_state;
			OnSetCursor();
			GetDocument()->m_pFrame->GetStatusBar()->SetStatusText(wxT(""));

			Update();

			wxClipboard *pClipboard = wxClipboard::Get();
			pClipboard->Open();//OpenClipboard();
			//EmptyClipboard();
			int nBaseNode = int(sel.SelNAYZ);
			int nNumPipes = int(vecCopy.size());
			wxMemoryOutputStream ms;
			wxDataOutputStream ar(ms);
			ar << nBaseNode << nNumPipes;
			for (auto it = vecCopy.begin(); it != vecCopy.end(); ++it)
				it->Serialize(ar);
			size_t cbBlock = static_cast<size_t>(ms.GetLength());
			void* pBlock = ms.GetOutputStreamBuffer()->GetBufferStart();
			wxCustomDataObject *pDataObject = new wxCustomDataObject(wxDataFormat(wxT("StartPP")));
			pDataObject->SetData(cbBlock, pBlock);
			pClipboard->AddData(pDataObject);
			ms.GetOutputStreamBuffer()->SetBufferIO(nullptr, (size_t) 0);
			pClipboard->Close();
			pClipboard->Flush();
			//dataObject.Free();
			if (m_bCut)
				GetDocument()->DeleteSelected();
			GetDocument()->m_pFrame->GetStatusBar()->SetStatusText(IDS_PIPES_COPIED);
			m_Timer.StartOnce(1000);
		}
	}

	//	StatusBar1->Panels->Items[1]->Text = "";
	;
	bZoomed = false;
	event.Skip();
	//CScrollView::OnLButtonDown(nFlags, point);
}

wxPoint CenterPoint(const wxRect rc)
{
	return wxPoint(rc.x + rc.width / 2, rc.y + rc.height / 2);
}

void CStartPPView::OnMouseMove(wxMouseEvent& event)
{
	if (event.GetId() != m_wnd->GetId())
		return;
	CPoint point = event.GetPosition();
	if (!Down) return;
	if (state == ST_ZOOM_WIN)
	{
		if (!m_bShowOGL)
		{
			wxClientDC dc(m_wnd);
			CDC* pDC = &dc;
			pDC->SetBrush(wxNullBrush);
			CPen pen(wxWHITE->GetRGB(), 1, wxPENSTYLE_DOT);
			pDC->SetPen(pen);
			pDC->SetLogicalFunction(wxXOR);
			pDC->DrawRectangle(DownX, DownY, MovePt.x-DownX+1, MovePt.y-DownY+1);
			MovePt = point;
			pDC->DrawRectangle(DownX, DownY, MovePt.x-DownX+1, MovePt.y-DownY+1);
			pDC->DrawRectangle(10,10,100,100);
			pDC->DrawRectangle(10,10,100,100);
		}
		else
		{
			wxClientDC dc(m_wnd);
			CRect clr = m_wnd->GetClientRect();
			CRect rc(DownX, DownY, point.x, point.y);
			m_OglPresenter.DrawDottedRect(&dc, rc, clr);
		}
	}
	else if (state == ST_ROTATE)
	{
		CRect clr =	m_wnd->GetClientRect();
		CPoint ptCenter = CenterPoint(clr);
		CPoint ptDown(DownX, DownY);
		m_ViewSettings.Rotate(m_rot, ptCenter, point, ptDown, z_rot1, x_rot1, Xorg1, Yorg1);
		//       if (!NoFile) // ShowPipes->copy_pipes(Table1,Rot);
		CPipeArray RotatedPipeArray(&tmpPipeArray, &m_rot);
		m_ScrPresenter.SetPipeArray(&RotatedPipeArray);
		wxClientDC dc(m_wnd);
		OnDraw(&dc);
		//OnPaint();

		m_ScrPresenter.SetPipeArray(&m_pipeArray);
	}
	else if (state == ST_PAN)
	{
		m_ViewSettings.Translate(point.x - DownX, point.y - DownY);
		Update();
		DownX = point.x;
		DownY = point.y;

		//        StatusBar1->Panels->Items[1]->Text ="["+IntToStr(X)+","+IntToStr(Y)+"]";
	};
	event.Skip();
	//CScrollView::OnMouseMove(nFlags, point);
}


void CStartPPView::OnLButtonUp(wxMouseEvent& event)
{
	if (event.GetId() != m_wnd->GetId())
		return;
	if (m_wnd->HasCapture())
		m_wnd->ReleaseMouse();//ReleaseCapture();
	CPoint point = event.GetPosition();
 	Down = false;
	//PaintBox1->Cursor = crSave;

	//   ReleaseCapture();
	//if (!bZoomed&& oPopupMenu) PaintBox1->PopupMenu=oPopupMenu;
	//if (Button==mbRight) return;
	if (state == ST_ZOOM_WIN)
	{
		CRect clr = m_wnd->GetClientRect();
		//PaintBox1->Canvas->Pen->Mode = pmNotXor;
		//PaintBox1->Canvas->Rectangle(DownX, DownY, MovePt.x, MovePt.y);
		//        Cross(DownX,DownY,MovePt.x,MovePt.y);
		int clw = clr.GetWidth(), clh = clr.GetHeight();
		int WinX = abs(point.x - DownX), WinY = abs(point.y - DownY);
		if ((WinX == 0) || (WinY == 0))
			return;
		float SclX = clw / float(WinX), SclY = clh / float(WinY);
		float SclF = (SclX < SclY) ? SclX : SclY;
		CPoint pt = CenterPoint(clr);
		m_ViewSettings.Translate(pt.x - (point.x + DownX) / 2, pt.y - (point.y + DownY) / 2);

		Zoom(SclF);
	}
	else if (state == ST_ROTATE)
	{
		//ShowPipes->PopFlags();
		m_ScrPresenter.SetPipeArray(&m_pipeArray);
		m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
		Update();
	}
	else if (state == ST_PAN)
	{
		//PaintBox1->Cursor = TCursor(crHandFlat);
		m_ViewSettings.Translate(point.x - DownX, point.y - DownY);
		Update();
	}

	//CScrollView::OnLButtonUp(nFlags, point);
}


void CStartPPView::Zoom(float S)
{
	CPoint pt = CenterPoint(m_wnd->GetClientRect());
	m_ViewSettings.Zoom(S, pt);
	Update();
}


void CStartPPView::OnMouseWheel(wxMouseEvent& event)
{
	if (event.GetId() != m_wnd->GetId())
		return;
	CPoint pt = event.GetPosition();
	//bZoomed=true;
	//PaintBox1->PopupMenu=nullptr;
	//float Sc=float(DownY-Y)/100;
	CRect clr = m_wnd->GetClientRect();
	//pt = ScreenToClient(pt);
	float S = (event.GetWheelRotation() > 0) ? 1.3f : 1 / (1.3f);
	//ShowPipes->RestoreViewState();
	m_ViewSettings.Zoom(S, pt);
	Update();
	event.Skip();
	//return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CStartPPView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	//return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}

const float fZoomFactor = 1.5f;

void CStartPPView::OnZoomIn(wxCommandEvent& event)
{
	Zoom(fZoomFactor);
	event.Skip();
}


void CStartPPView::OnZoomOut(wxCommandEvent& event)
{
	Zoom(1 / fZoomFactor);
	event.Skip();
}


void CStartPPView::OnZoomAll(wxCommandEvent& event)
{
	m_ScrPresenter.ZoomAll(m_wnd->GetClientRect(), 40);
	Update();
	event.Skip();
}


void CStartPPView::OnMButtonDown(wxMouseEvent& event)
{
	if (event.GetId() != m_wnd->GetId())
		return;
	CPoint point = event.GetPosition();
    if (!m_wnd->GetClientRect().Contains(point))
        return;
	Down = TRUE;
	DownX = point.x;
	DownY = point.y;
	o_state = state;
	state = ST_PAN;
	OnSetCursor();
	event.Skip();
	//SetCapture();
	//CScrollView::OnMButtonDown(nFlags, point);
}


void CStartPPView::OnMButtonUp(wxMouseEvent& event)
{
	if (event.GetId() != m_wnd->GetId())
		return;
	//ReleaseCapture();
	CPoint point = event.GetPosition();
	state = o_state;
	OnSetCursor();
	Down = false;
	m_ViewSettings.Translate(point.x - DownX, point.y - DownY);
	Update();
	event.Skip();
	//CScrollView::OnMButtonUp(nFlags, point);
}


void CStartPPView::OnZoomWin(wxCommandEvent& event)
{
	state = ST_ZOOM_WIN;
	OnSetCursor();
	event.Skip();
}


void CStartPPView::OnUpdateZoomWin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_ZOOM_WIN);
}


void CStartPPView::OnPan(wxCommandEvent& event)
{
	state = ST_PAN;
	OnSetCursor();
	event.Skip();
}


void CStartPPView::OnUpdatePan(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_PAN);
}


void CStartPPView::OnRotate(wxCommandEvent& event)
{
	state = ST_ROTATE;
	OnSetCursor();
	event.Skip();
}


void CStartPPView::OnUpdateRotate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_ROTATE);
}


void CStartPPView::OnSelect(wxCommandEvent& event)
{
	state = ST_SELECT;
	OnSetCursor();
	//GetOwner()->SendMessage(WM_SETMESSAGESTRING, IDS_SELECT_MODE_HELPSTRING);
	event.Skip();
}


void CStartPPView::OnUpdateSelect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_SELECT);
}


BOOL CStartPPView::OnSetCursor()
{
	UINT nCursorIDs[] =
	{
		IDC_PAN, // ST_PAN
		IDC_SELECT, // ST_SELECT
		IDC_ROTATE, // ST_ROTATE
		IDC_ZOOM, // ST_ZOOM
		IDC_SELECT
	};
	wxString curName;
	wxPoint ptSpot(15,15);
	if (state==ST_SELECT || state==ST_SELECT_NODE)
	{
		curName = wxT("Select");
		ptSpot = wxPoint(15,16);
	}
	else if (state==ST_PAN)
		curName = wxT("Pan");
	else if (state==ST_ROTATE)
		curName = wxT("Rotate");
	else if (state==ST_ZOOM_WIN)
		curName = wxT("Zoom");
	if (!curName.IsEmpty())
	{
		wxBitmap bmp = wxXmlResource::Get()->LoadBitmap(curName);
		wxImage img(32,32);
		img = bmp.ConvertToImage();
		img.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_X, ptSpot.x);
		img.SetOption(wxIMAGE_OPTION_CUR_HOTSPOT_Y, ptSpot.y);
		wxCursor cur(img);
		m_wnd->SetCursor(cur);
		return TRUE;
	}
	//::SetCursor(AfxGetApp()->LoadCursor(nCursorIDs[state - 1]));
	m_wnd->SetCursor(wxCURSOR_ARROW);
	if (state == ST_SELECT)
		;//GetOwner()->SendMessage(WM_SETMESSAGESTRING, IDS_SELECT_MODE_HELPSTRING);

	return TRUE;
}

void CStartPPView::OnScroll(wxScrollEvent& event)
{
	event.Skip();
	//int xOrig = x;
/*	wxEventType t = event.GetEventType();
	if(event.GetOrientation()==wxHORIZONTAL)
	{
		int x = event.GetPosition();
		if (t==wxEVT_SCROLL_TOP)
			x = 0;
		else if (t==wxEVT_SCROLL_BOTTOM)
			x = INT_MAX;
		else if (t==wxEVT_SCROLL_LINEUP)
			x -= m_lineDev.x;
		else if (t==wxEVT_SCROLL_LINEDOWN)
			x += m_lineDev.x;
		else if (t==wxEVT_SCROLL_PAGEUP)
			x -= m_pageDev.x;
		else if (t==wxEVT_SCROLL_PAGEDOWN)
			x += m_pageDev.x;
		CRect clr = m_wnd->GetClientRect();

		//SetScrollPos(SB_HORZ, x);
		m_ViewSettings.Xorg = clr.GetWidth() - m_ScrPresenter.x_min * m_ViewSettings.ScrScale - x;
	}
	else
	{
		int y = event.GetPosition();
		if (t==wxEVT_SCROLL_TOP)
			y = 0;
		else if (t==wxEVT_SCROLL_BOTTOM)
			y = INT_MAX;
		else if (t==wxEVT_SCROLL_LINEUP)
			y -= m_lineDev.y;
		else if (t==wxEVT_SCROLL_LINEDOWN)
			y += m_lineDev.y;
		else if (t==wxEVT_SCROLL_PAGEUP)
			y -= m_pageDev.y;
		else if (t==wxEVT_SCROLL_PAGEDOWN)
			y += m_pageDev.y;
		CRect clr = m_wnd->GetClientRect();
		//SetScrollPos(SB_VERT, y);
		m_ViewSettings.Yorg = clr.GetHeight() + m_ScrPresenter.y_max * m_ViewSettings.ScrScale - y;
	}
	Update();*/
	//CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}





void CStartPPView::OnViewNodeNums(wxCommandEvent& event)
{
	m_ViewSettings.ShowNums = !m_ViewSettings.ShowNums;
	Update();
	event.Skip();
}


void CStartPPView::OnUpdateViewNodeNums(wxUpdateUIEvent& event)
{
	event.Check(m_ViewSettings.ShowNums);
	//event.Skip();
}


void CStartPPView::OnViewSizes(wxCommandEvent& event)
{
	m_ViewSettings.ShowDims = !m_ViewSettings.ShowDims;
	Update();
	event.Skip();
}


void CStartPPView::OnUpdateViewSizes(wxUpdateUIEvent& event)
{
	event.Check(m_ViewSettings.ShowDims);
}


void CStartPPView::OnViewAprof(wxCommandEvent& event)
{
	m_ViewSettings.ShowAProf = !m_ViewSettings.ShowAProf;
	Update();
	event.Skip();
}


void CStartPPView::OnUpdateViewAprof(wxUpdateUIEvent& event)
{
	event.Check(m_ViewSettings.ShowAProf);
	//event.Skip();
}


void CStartPPView::OnViewElements(wxCommandEvent& event)
{
	m_ViewSettings.ShowElms = !m_ViewSettings.ShowElms;
	Update();
	event.Skip();
}


void CStartPPView::OnUpdateViewElements(wxUpdateUIEvent& event)
{
	event.Check(m_ViewSettings.ShowElms);
	//event.Skip();
}


void CStartPPView::OnViewNodes(wxCommandEvent& event)
{
	m_ViewSettings.ShowPoints = !m_ViewSettings.ShowPoints;

	Update();
	event.Skip();
}


void CStartPPView::OnUpdateViewNodes(wxUpdateUIEvent& event)
{
	event.Check(m_ViewSettings.ShowPoints);
	//event.Skip();
}


int CStartPPView::Create()
{
	m_rend.BindWindow(nullptr, false, nullptr);
	return 0;
}



void CStartPPView::OnShowOgl(wxCommandEvent& event)
{
	m_bShowOGL = !m_bShowOGL;
	//if (m_bShowOGL)
	//	m_OglPresenter.vecSel = m_ScrPresenter.vecSel;
	//else
	//	m_ScrPresenter.vecSel = m_OglPresenter.vecSel;
	if (!m_bShowOGL)
	{
		MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
		wxAuiNotebook *pBook = frame->GetAuiBook();
		wxWindow* pPanel  = pBook->GetPage(pBook->GetSelection());
		m_wnd->Destroy();
		wxGLCanvas *pGlPanel = new wxGLCanvasViewWnd(this, pPanel);
		wxFont glPanelFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
		pGlPanel->SetFont(glPanelFont);
		pPanel->GetSizer()->Add(pGlPanel, 1, wxALL | wxEXPAND, 5);
		pPanel->GetSizer()->Layout();
		m_OglPresenter.canvas = pGlPanel;
		m_wnd = pGlPanel;
		pGlPanel->SetEventHandler(this);
		
	}
	Update();
	event.Skip();
}


void CStartPPView::OnUpdateShowOgl(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowOGL);
}


void CStartPPView::OnPrint(wxDC *pDC, wxObject *info)
{
	wxDocPrintout *pPrintout = (wxDocPrintout*)info;
	//pDC->SetUserScale(1,1);
	double sx;
	double sy;
	pDC->GetUserScale(&sx, &sy);
	CPrintInfo printInfo;
	CPrintInfo *pInfo=&printInfo;
	printInfo.m_rectDraw = wxRect(pDC->GetSize());
	CViewSettings viewSettings(m_ViewSettings);
	CScreenPipePresenter prn(&m_pipeArray, m_rot, viewSettings);
	*(prn.Result) = *(m_ScrPresenter.Result);
	prn.pvecSel = m_ScrPresenter.pvecSel;
	CRect clr = pInfo->m_rectDraw;
	clr.SetWidth(clr.GetWidth()/sx);
	clr.SetHeight(clr.GetHeight()/sy);
	//pDC->SetBrush(*wxYELLOW_BRUSH);
	//pDC->SetPen(*wxBLACK_PEN);
	//pDC->DrawRectangle(clr);
	int w;
	int h;
	pPrintout->GetPageSizeMM(&w,&h);
	
	double fAspX = clr.GetWidth()/ double(w);
	double fAspY = clr.GetHeight()/ double(h);
	int wp;
	int hp;
	pPrintout->GetPageSizePixels(&wp,&hp);
	wxRect rectPaper = pPrintout->GetPaperRectPixels();
	wxRect rectPage = wxRect(wxSize(wp,hp));
	SFloatRect margins;
	margins.left = -rectPaper.x * double(w) / rectPage.GetWidth();
	margins.right = (rectPaper.x + rectPaper.GetWidth() - rectPage.GetWidth()) * double(w)/ rectPage.GetWidth();
	margins.top = -rectPaper.y * double(h) / rectPage.GetHeight();
	margins.bottom = (rectPaper.y + rectPaper.GetHeight() - rectPage.GetHeight()) * double(h) / rectPage.GetHeight();
	//CPrintHelper::DrawFrame(pDC, clr, GetDocument()->GetFilename(), fAspX, fAspY, margins);

	pDC->SetBrush(*wxWHITE_BRUSH);
	pDC->SetPen(*wxTRANSPARENT_PEN);
	pDC->DrawRectangle(clr);
	CPrintHelper::DrawFrame(pDC, clr, GetDocument()->GetFilename(), fAspX, fAspY, margins);
	if (m_bShowOGL)
	{
		pInfo->m_rectDraw = clr;
		CViewSettings vp(m_ViewSettings);
		m_OglPresenter.Print(pDC, pInfo, &m_rot, nullptr);
		m_ViewSettings = vp;
	}
	else
	{
		CRect rc = m_wnd->GetClientRect();
		//prn.ElemScale = 4;
		float S = float(clr.GetWidth()) / rc.GetWidth();
		CPoint pt = CenterPoint(clr);
		CPoint ptCenter= CenterPoint(rc);
		viewSettings.Zoom(S, pt, &ptCenter);
		//pDC->IntersectClipRect(&clr);
		prn.Draw(pDC, &m_rot, clr);
	}
}


void CStartPPView::OnUpdateDist(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(false);
	if (GetDocument()->vecSel.size() != 2)
		return;
	auto it = GetDocument()->vecSel.begin();
	if (it->SelKOYZ == it++->SelNAYZ &&
	        it->SelKOYZ == it->SelNAYZ)
		pCmdUI->Enable();
}


void CStartPPView::OnDist()
{
	CDistDialog dlg(m_ScrPresenter);
	//dlg.DoModal();
}

void CStartPPView::OnProj(wxCommandEvent& event)
{
	SetRot(m_nView);
	event.Skip();
}

void CStartPPView::OnView3dviewsBack(wxCommandEvent& event)
{
	SetRot(DPT_Back);
	event.Skip();
}

void CStartPPView::OnView3dviewsBottom(wxCommandEvent& event)
{
	SetRot(DPT_Bottom);
	event.Skip();
}

void CStartPPView::OnView3dviewsDimetry(wxCommandEvent& event)
{
	SetRot(DPT_Dimetry);
	event.Skip();
}

void CStartPPView::OnView3dviewsFront(wxCommandEvent& event)
{
	SetRot(DPT_Front);
	event.Skip();
}

void CStartPPView::OnView3dviewsLeft(wxCommandEvent& event)
{
	SetRot(DPT_Left);
	event.Skip();
}

void CStartPPView::OnView3dviewsNeIso(wxCommandEvent& event)
{
	SetRot(DPT_NorthEast);
	event.Skip();
}

void CStartPPView::OnView3dviewsNwIso(wxCommandEvent& event)
{
	SetRot(DPT_NorthWest);
	event.Skip();
}

void CStartPPView::OnView3dviewsRight(wxCommandEvent& event)
{
	SetRot(DPT_Right);
	event.Skip();
}

void CStartPPView::OnView3dviewsSeIso(wxCommandEvent& event)
{
	SetRot(DPT_SouthEast);
	event.Skip();
}

void CStartPPView::OnView3dviewsSwIso(wxCommandEvent& event)
{
	SetRot(DPT_SouthWest);
	event.Skip();
}

void CStartPPView::OnView3dviewsTop(wxCommandEvent& event)
{
	SetRot(DPT_Top);
	event.Skip();
}

int CStartPPView::SetRot(int nView)
{
	LPCTSTR arrViewBmps[] = { wxT("ToolViewPredefView"), wxT("View3dViewBottom"),  wxT("View3dViewLeft"), wxT("View3dViewRight"), wxT("View3dViewFront"), wxT("View3dViewBack"), wxT("View3dViewSWIso"), wxT("View3dViewSEIso"), wxT("View3dViewNEIso"),  wxT("View3dViewNWIso"), wxT("View3dViewDimetry") };
	wxAuiToolBar* pToolBar = GetDocument()->m_pFrame->GetAuibarView();
	wxAuiToolBarItem* pViewTop = pToolBar->FindTool(MainFrameBaseClass::wxID_PROJ);
	pViewTop->SetBitmap(wxXmlResource::Get()->LoadBitmap(arrViewBmps[nView]));
	m_nView = nView;
	m_rot.SetPredefinedView(nView);

	m_ViewSettings.Plan = (nView == DPT_Top);
	m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	wxCommandEvent event;
	OnZoomAll(event);
	return 0;
}


void CStartPPView::OnActivateView(bool bActivate, wxView* pActivateView, wxView* pDeactiveView)
{
	wxView::OnActivateView(bActivate, pActivateView, pDeactiveView);
	if (bActivate)
	{
		CPipePresenter* p = m_bShowOGL ? &m_OglPresenter : &m_ScrPresenter;
		CString strText;
		strText.Format(LoadStr(IDS_FORMAT_UCH_UZL), p->NumPipes, p->NumNodes);
		//static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1, strText);
		if (GetDocument()->vecSel.size() > 0)
		{
			GetDocument()->Select(GetDocument()->vecSel.begin()->SelNAYZ, GetDocument()->vecSel.begin()->SelKOYZ);
			//m_OglPresenter.vecSel = p->vecSel;
		}
		else
		{
			if (GetDocument()->m_pipes.m_vecPnN.size() == 0)
				return;
			CPipeAndNode p1 = GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx];
			GetDocument()->Select(int(p1.m_NAYZ), int(p1.m_KOYZ));
		}
	}
	//CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

bool CStartPPView::OnCreate(wxDocument* pDoc, long)
{
	MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
	wxPanel* panel = new wxPanel(frame->GetAuiBook(), wxID_ANY, wxDefaultPosition, wxSize(-1, -1), wxTAB_TRAVERSAL);

	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(boxSizer);

	wxGLCanvas *pGlPanel = new wxGLCanvasViewWnd(this, panel);
	wxFont glPanelFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	pGlPanel->SetFont(glPanelFont);

	boxSizer->Add(pGlPanel, 1, wxALL | wxEXPAND, 5);
	frame->GetAuiBook()->AddPage(panel,pDoc->GetUserReadableName(), true);

	m_OglPresenter.canvas = pGlPanel;
	m_wnd = pGlPanel;
	pGlPanel->SetEventHandler(this);
	return true;
}

bool CStartPPView::OnClose(bool deleteWindow)
{
	if (!wxView::OnClose(deleteWindow))
		return false;
	if (m_bInTabCloseHandler)
		return true;
	MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
	wxAuiNotebook* book = frame->GetAuiBook();
	wxWindow *pWnd = book->GetCurrentPage();
	wxWindowList& l = pWnd->GetChildren();
	if (l.size() != 0 && l.GetFirst()->GetData() == m_wnd)
	{
		static_cast<wxGLCanvasViewWnd*>(m_wnd)->SetChildView(nullptr);
		m_wnd->SetEventHandler(m_wnd);
		book->DeletePage(book->GetSelection());
	}

	return true;
}

void CStartPPView::OnPageClose(wxAuiNotebookEvent& evt)
{
	m_bInTabCloseHandler = true;
	MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
	wxWindow* window = frame->GetAuiBook()->GetPage(evt.GetSelection());
	wxGLCanvasViewWnd *pWnd = static_cast<wxGLCanvasViewWnd *>(window->GetChildren().GetFirst()->GetData());

	wxCloseEvent event(wxEVT_CLOSE_WINDOW, pWnd->GetId());
	event.SetEventObject(pWnd);
	event.SetCanVeto(true);
	pWnd->OnCloseWindow(event);
	if (event.GetVeto())
		evt.Veto();
	m_bInTabCloseHandler = false;
}

void CStartPPView::OnPageChanged(wxAuiNotebookEvent& evt)
{
	MainFrame *frame = wxStaticCast(wxGetApp().GetTopWindow(), MainFrame);
	wxAuiNotebook *pBook = frame->GetAuiBook();
	int old_selection = evt.GetOldSelection();
	int new_selection = evt.GetSelection();
	// don't do anything if the page doesn't actually change
	if (old_selection == new_selection)
		return;



	// notify old active child that it has been deactivated
	if ((old_selection != -1) && (old_selection < (int)pBook->GetPageCount()))
	{
		wxWindow* pPanel  = pBook->GetPage(old_selection);
		wxGLCanvasViewWnd *pWnd = static_cast<wxGLCanvasViewWnd *>(pPanel->GetChildren().GetFirst()->GetData());

		wxActivateEvent event(wxEVT_ACTIVATE, false, pWnd->GetId());
		event.SetEventObject(pWnd);
		pWnd->OnActivate(event);
	}

	// notify new active child that it has been activated
	if (new_selection != -1)
	{
		wxWindow* pPanel = pBook->GetPage(new_selection);
		wxGLCanvasViewWnd *pWnd = static_cast<wxGLCanvasViewWnd *>(pPanel->GetChildren().GetFirst()->GetData());

		wxActivateEvent event(wxEVT_ACTIVATE, true, pWnd->GetId());
		event.SetEventObject(pWnd);
		pWnd->OnActivate(event);
	}
}

void CStartPPView::OnEditCopy(wxCommandEvent& event)
{
	m_bCut = false;
	OnEditCutCopy();
	event.Skip();
}


void CStartPPView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 27 && state == ST_SELECT_NODE)
	{
		state = o_state;
		//GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	}

	//CScrollView::OnChar(nChar, nRepCnt, nFlags);
}


void CStartPPView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetDocument()->vecSel.size() > 0 && GetDocument()->vecSel.begin()->SelNAYZ >= 0);
}

void CStartPPView::OnEditCut(wxCommandEvent& event)
{
	m_bCut = true;
	OnEditCutCopy();
	event.Skip();
}


void CStartPPView::OnEditCutCopy(void)
{
	if (state == ST_SELECT_NODE)
		return;

	if (!GetDocument()->IsSelConnected())
	{
		AfxMessageBox(IDS_PARTS_NOT_CONNECTED, wxOK | wxICON_EXCLAMATION);
		return;
	}

	o_state = state;
	state = ST_SELECT_NODE;
	OnSetCursor();
	GetDocument()->m_pFrame->GetStatusBar()->SetStatusText(wxString(IDS_SELECT_BASE_NODE));
}


wxPrintout* CStartPPView::OnCreatePrintout()
{
	return new wxStartPPPrintout(this);
}

bool wxStartPPPrintout::OnPrintPage(int page)
{
	wxDC *dc = GetDC();
	// Get the logical pixels per inch of screen and printer
	int ppiScreenX, ppiScreenY;
	GetPPIScreen(&ppiScreenX, &ppiScreenY);
	wxUnusedVar(ppiScreenY);
	int ppiPrinterX, ppiPrinterY;
	GetPPIPrinter(&ppiPrinterX, &ppiPrinterY);
	wxUnusedVar(ppiPrinterY);

	// This scales the DC so that the printout roughly represents the
	// the screen scaling. The text point size _should_ be the right size
	// but in fact is too small for some reason. This is a detail that will
	// need to be addressed at some point but can be fudged for the
	// moment.
	float scale = (float)((float)ppiPrinterX/(float)ppiScreenX);

	// Now we have to check in case our real page size is reduced
	// (e.g. because we're drawing to a print preview memory DC)
	int pageWidth, pageHeight;
	int w, h;
	dc->GetSize(&w, &h);
	GetPageSizePixels(&pageWidth, &pageHeight);
	wxUnusedVar(pageHeight);

	// If printer pageWidth == current DC width, then this doesn't
	// change. But w might be the preview bitmap width, so scale down.
	float overallScale = scale * (float)(w/(float)pageWidth);
	dc->SetUserScale(overallScale, overallScale);

	if (m_printoutView)
	{
		m_printoutView->OnPrint(dc, (wxObject*)this);
	}
	return true;
}	