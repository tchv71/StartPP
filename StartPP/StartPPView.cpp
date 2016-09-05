// StartPPView.cpp : реализация класса CStartPPView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "StartPP.h"
#endif

#include <atltypes.h>
#include "StartPPSet.h"
#include "StartPPDoc.h"
#include "StartPPView.h"
#include "MainFrm.h"
#include "DistDialog.h"
#include "PrintHelper.h"
#include "resource.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern LPCTSTR LoadStr(UINT nID);


// CStartPPView

IMPLEMENT_DYNCREATE(CStartPPView, CScrollView)

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

// создание/уничтожение CStartPPView

CStartPPView::CStartPPView()
	: CScrollView(), m_bShowOGL(false),
	  m_ScrPresenter(&m_pipeArray, m_rot, m_ViewSettings), m_OglPresenter(&m_pipeArray, &m_rend, m_rot, m_ViewSettings), DownX(0), DownY(0), Down(false), Xorg1(0), Yorg1(0), z_rot1(0), x_rot1(0), bZoomed(false),
	  m_bInitialized(false)
	  , m_bCut(false)
{
	m_pFrame = static_cast<CMainFrame *>(AfxGetApp()->m_pMainWnd);
	m_rot.SetPredefinedView(DPT_Top);
	// TODO: добавьте код создания
}

CStartPPView::~CStartPPView()
{
}

void CStartPPView::DoDataExchange(CDataExchange* pDX)
{
	CScrollView::DoDataExchange(pDX);
	//m_pFrame->m_wndProperties.DoDataExchange(pDX, m_pSet);

	// место для вставки функций DDX_Field* для подключения элементов управления к полям базы данных, например
	// DDX_FieldText(pDX, IDC_MYEDITBOX, m_pSet->m_szColumn1, m_pSet);
	// DDX_FieldCheck(pDX, IDC_MYCHECKBOX, m_pSet->m_bColumn2, m_pSet);
	// Для получения дополнительных сведений см. примеры MSDN и ODBC
}

BOOL CStartPPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

void CStartPPView::OnInitialUpdate()
{
	m_rot.SetPredefinedView(DPT_Top);
	m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	m_ScrPresenter.DrawMain(true);
	CRect clr;
	GetClientRect(&clr);
	m_OldSize = clr.Size();
	//SetScaleToFitSize(clr.Size());
	CSize sz(0, 0);
	SetScrollSizes(MM_TEXT, sz); //clr.Size());
	CScrollView::OnInitialUpdate();
	m_bInitialized = true;
	//m_pFrame->	m_wndViewToolBar.RestoreOriginalstate();
	m_ScrPresenter.ZoomAll(clr, 40);

	CDC* pDC = GetDC();
	OnDraw(pDC);
	ReleaseDC(pDC);
	//OnPaint();
}


// печать CStartPPView


void CStartPPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CStartPPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CStartPPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CStartPPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CStartPPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CStartPPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика CStartPPView

#ifdef _DEBUG
void CStartPPView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CStartPPView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CStartPPDoc* CStartPPView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStartPPDoc)));
	return static_cast<CStartPPDoc*>(m_pDocument);
}
#endif //_DEBUG



// обработчики сообщений CStartPPView


void CStartPPView::OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame)
{
	// TODO: добавьте специализированный код или вызов базового класса

	CScrollView::OnActivateFrame(nState, pDeactivateFrame);
}


void CStartPPView::OnDraw(CDC* pDC)
{
	//ScrollWindow(0,0);
	if (m_bShowOGL)
	{
		m_OglPresenter.ghDC = pDC->m_hDC;
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
		m_OglPresenter.m_bNewGeometry = m_ScrPresenter.m_bNewGeometry;
		m_ViewSettings.ShowNapr;
		CRect clr;
		GetClientRect(&clr);
		m_OglPresenter.Draw(clr, false);
		m_ScrPresenter.m_bNewGeometry = m_OglPresenter.m_bNewGeometry;
	}
	else
	{
		pDC->SetViewportOrg(0, 0);
		CRect clr;
		GetClientRect(&clr);
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		HBITMAP HBmp = ::CreateCompatibleBitmap(pDC->m_hDC, clr.Width(), clr.Height());
		HBITMAP hBm = HBITMAP(memDC.SelectObject(HBmp));
		CPen pen(PS_SOLID, 0,RGB(255,255,255));
		CPen* pOldPen;
		CBrush br(RGB(255,255,255));
		pOldPen = memDC.SelectObject(&pen);
		memDC.SelectObject(&br);
		memDC.Rectangle(&clr);
		memDC.SelectObject(pOldPen);
		m_ScrPresenter.Draw(&memDC, &m_rot, clr);
		pDC->BitBlt(0, 0, clr.Width(), clr.Height(), &memDC, 0, 0,SRCCOPY);
		memDC.SelectObject(hBm);
		::DeleteObject(HBmp);
		return;
		/*
		SIZE szDoc;
		szDoc.cx =LONG((m_ScrPresenter.x_max - m_ScrPresenter.x_min) *m_ScrPresenter.ScrScale + 2 *clr.Width());
		szDoc.cy =LONG((m_ScrPresenter.y_max - m_ScrPresenter.y_min) *m_ScrPresenter.ScrScale + 2 *clr.Height());       
		SetScrollSizes(MM_TEXT, szDoc);
		CPoint pt(LONG(clr.Width() - m_ScrPresenter.x_min*m_ScrPresenter.ScrScale -  m_ScrPresenter.Xorg),
			LONG(clr.Height() + m_ScrPresenter.y_max*m_ScrPresenter.ScrScale-  m_ScrPresenter.Yorg)); 
		SetScrollPos(SB_HORZ, pt.x);
		SetScrollPos(SB_VERT, pt.y);
		*/
	}
}


void CStartPPView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);
	if (m_OldSize.cx == 0)
	{
		m_OldSize = CSize(cx, cy);
		return;
	}
	if (!m_bInitialized) return;
	if (cx == 0 || cy == 0)
		return;
	float S = float(cx) / m_OldSize.cx;
	CRect clr;
	GetClientRect(&clr);
	CPoint pt = clr.CenterPoint();
	int cx1 = pt.x;
	int cy1 = pt.y;
	m_ViewSettings.ScrScale *= S;
	m_ViewSettings.Xorg = (m_ViewSettings.Xorg - float(m_OldSize.cx) / 2) * S + cx1;
	m_ViewSettings.Yorg = (m_ViewSettings.Yorg - float(m_OldSize.cy) / 2) * S + cy1;
	m_OldSize = CSize(cx, cy);
	Invalidate();
}


void CStartPPView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	//CPipePresenter *p=m_bShowOGL? &m_OglPresenter : &m_ScrPresenter;
	m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	m_OglPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	m_ScrPresenter.pvecSel = m_OglPresenter.pvecSel = &(GetDocument()->vecSel);
	if (GetDocument()->vecSel.size() <= 1)
	{
		SelStr S;
		if (GetDocument()->vecSel.size() == 1 && GetDocument()->vecSel.begin()->SelNAYZ == GetDocument()->vecSel.begin()->SelKOYZ)
		{
			S.SelNAYZ = S.SelKOYZ = int(GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx].m_KOYZ);
		}
		else
		{
			S.SelNAYZ = int(GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx].m_NAYZ);
			S.SelKOYZ = int(GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx].m_KOYZ);
		}
		if (GetDocument()->vecSel.size() == 1)
		{
			GetDocument()->vecSel.clear();
			GetDocument()->vecSel.insert(S);
		}
		else
			GetDocument()->vecSel.insert(S);
	}
	Invalidate();
}

enum E_STATE
	{
		ST_PAN=1,
		ST_SELECT,
		ST_ROTATE,
		ST_ZOOM_WIN,
		ST_SELECT_NODE
	} state = ST_PAN, o_state;


void CStartPPView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	//m_ScrPresenter.SaveViewState();
	//if (PaintBox1->PopupMenu) oPopupMenu=PaintBox1->PopupMenu;
	//crSave=PaintBox1->Cursor;
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
		SHORT ks = GetKeyState(VK_MENU);
		if (ks & 0x8000)
			p->SelectPipeSegment(point.x, point.y);
		else if ((nFlags & MK_SHIFT) != 0)
			p->SelectPipesTo(point.x, point.y, (nFlags & MK_CONTROL) != 0);
		else
			p->SelectPipe(point.x, point.y, (nFlags & MK_CONTROL) != 0);
		GetDocument()->Select(GetDocument()->vecSel.SelNAYZ, GetDocument()->vecSel.SelKOYZ);
		//SetSel();
		m_ScrPresenter.m_bNewGeometry = true;
		Invalidate();
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
		for each (auto& x in pipes.m_vecPnN)
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
			RedrawWindow();
			OpenClipboard();
			EmptyClipboard();
			int nBaseNode = int(sel.SelNAYZ);
			int nNumPipes = int(vecCopy.size());
			CMemFile mf;
			CArchive ar(&mf, CArchive::store);
			ar << nBaseNode << nNumPipes;
			for (auto it = vecCopy.begin(); it != vecCopy.end(); ++it)
				it->Serialize(ar);
			ar.Close();
			size_t cbBlock = static_cast<size_t>(mf.GetLength());
			BYTE* pBlock = mf.Detach();
			HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, cbBlock);
			BYTE* pClip = static_cast<BYTE *>(GlobalLock(hglb));
			memcpy(pClip, pBlock, cbBlock);
			GlobalUnlock(hglb);
			free(pBlock);
			SetClipboardData(GetDocument()->m_nClipFormat, hglb);
			CloseClipboard();
			GetOwner()->SendMessage(WM_SETMESSAGESTRING, IDS_PIPES_COPIED);
			if (m_bCut)
				GetDocument()->DeleteSelected();
		}
	}

	//	StatusBar1->Panels->Items[1]->Text = "";
	;
	bZoomed = false;

	CScrollView::OnLButtonDown(nFlags, point);
}


void CStartPPView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!Down) return;
	if (state == ST_ZOOM_WIN)
	{
		if (!m_bShowOGL)
		{
			CDC* pDC = GetDC();
			int nOldRop = pDC->SetROP2(R2_XORPEN);
			CPen pen(PS_DOT, 1, RGB(0, 0, 0));
			CPen* pOldPen = pDC->SelectObject(&pen);
			HGDIOBJ hOldBrush = pDC->SelectObject(::GetStockObject(NULL_BRUSH));
			pDC->Rectangle(DownX, DownY, MovePt.x, MovePt.y);
			MovePt = point;
			pDC->Rectangle(DownX, DownY, MovePt.x, MovePt.y);
			pDC->SetROP2(nOldRop);
			pDC->SelectObject(hOldBrush);
			pDC->SelectObject(pOldPen);
			ReleaseDC(pDC);
		}
		else
		{
			CRect clr;
			GetClientRect(&clr);
			CDC* pDC = GetDC();
			CRect rc(DownX, DownY, point.x, point.y);
			m_OglPresenter.DrawDottedRect(pDC, rc, clr);
			ReleaseDC(pDC);
		}
	}
	else if (state == ST_ROTATE)
	{
		CRect clr;
		GetClientRect(&clr);
		CPoint ptCenter = clr.CenterPoint();
		CPoint ptDown(DownX, DownY);
		m_ViewSettings.Rotate(m_rot, ptCenter, point, ptDown, z_rot1, x_rot1, Xorg1, Yorg1);
		//       if (!NoFile) // ShowPipes->copy_pipes(Table1,Rot);
		CPipeArray RotatedPipeArray(&tmpPipeArray, &m_rot);
		m_ScrPresenter.SetPipeArray(&RotatedPipeArray);
		CDC* pDC = GetDC();
		OnDraw(pDC);
		ReleaseDC(pDC);
		//OnPaint();

		m_ScrPresenter.SetPipeArray(&m_pipeArray);
	}
	else if (state == ST_PAN)
	{
		m_ViewSettings.Translate(point.x - DownX, point.y - DownY);
		Invalidate();
		DownX = point.x;
		DownY = point.y;

		//        StatusBar1->Panels->Items[1]->Text ="["+IntToStr(X)+","+IntToStr(Y)+"]";
	};
	CScrollView::OnMouseMove(nFlags, point);
}


void CStartPPView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	Down = false;
	//PaintBox1->Cursor = crSave;

	//   ReleaseCapture();
	//if (!bZoomed&& oPopupMenu) PaintBox1->PopupMenu=oPopupMenu;
	//if (Button==mbRight) return;
	if (state == ST_ZOOM_WIN)
	{
		CRect clr;
		GetClientRect(&clr);
		//PaintBox1->Canvas->Pen->Mode = pmNotXor;
		//PaintBox1->Canvas->Rectangle(DownX, DownY, MovePt.x, MovePt.y);
		//        Cross(DownX,DownY,MovePt.x,MovePt.y);
		int clw = clr.Width(), clh = clr.Height();
		int WinX = abs(point.x - DownX), WinY = abs(point.y - DownY);
		if ((WinX == 0) || (WinY == 0))
			return;
		float SclX = clw / float(WinX), SclY = clh / float(WinY);
		float SclF = (SclX < SclY) ? SclX : SclY;
		CPoint pt = clr.CenterPoint();
		m_ViewSettings.Translate(pt.x - (point.x + DownX) / 2, pt.y - (point.y + DownY) / 2);

		Zoom(SclF);
	}
	else if (state == ST_ROTATE)
	{
		//ShowPipes->PopFlags();
		m_ScrPresenter.SetPipeArray(&m_pipeArray);
		m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
		Invalidate();
	}
	else if (state == ST_PAN)
	{
		//PaintBox1->Cursor = TCursor(crHandFlat);
		m_ViewSettings.Translate(point.x - DownX, point.y - DownY);
		Invalidate();
	}

	CScrollView::OnLButtonUp(nFlags, point);
}


void CStartPPView::Zoom(float S)
{
	CRect clr;
	GetClientRect(&clr);
	CPoint pt = clr.CenterPoint();
	m_ViewSettings.Zoom(S, pt);
	Invalidate();
}


BOOL CStartPPView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//bZoomed=true;
	//PaintBox1->PopupMenu=nullptr;
	//float Sc=float(DownY-Y)/100;
	CRect clr;
	GetClientRect(&clr);
	ScreenToClient(&pt);
	float S = (zDelta > 0) ? 1.3f : 1 / (1.3f);
	//ShowPipes->RestoreViewState();
	m_ViewSettings.Zoom(S, pt);
	CDC* pDC = GetDC();
	OnDraw(pDC);//OnPaint();
	ReleaseDC(pDC);
	Invalidate();
	return TRUE;
	//return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL CStartPPView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	//return CScrollView::OnEraseBkgnd(pDC);
	return TRUE;
}

const float fZoomFactor = 1.5f;

void CStartPPView::OnZoomIn()
{
	Zoom(fZoomFactor);
}


void CStartPPView::OnZoomOut()
{
	Zoom(1 / fZoomFactor);
}


void CStartPPView::OnZoomAll()
{
	CRect clr;
	GetClientRect(&clr);
	m_ScrPresenter.ZoomAll(clr, 40);
	Invalidate();
}


void CStartPPView::OnMButtonDown(UINT nFlags, CPoint point)
{
	Down = TRUE;
	DownX = point.x;
	DownY = point.y;
	o_state = state;
	state = ST_PAN;
	OnSetCursor(this, 0, 0);
	SetCapture();
	CScrollView::OnMButtonDown(nFlags, point);
}


void CStartPPView::OnMButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	state = o_state;
	Down = false;
	m_ViewSettings.Translate(point.x - DownX, point.y - DownY);
	Invalidate();
	CScrollView::OnMButtonUp(nFlags, point);
}


void CStartPPView::OnZoomWin()
{
	state = ST_ZOOM_WIN;
}


void CStartPPView::OnUpdateZoomWin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_ZOOM_WIN);
}


void CStartPPView::OnPan()
{
	state = ST_PAN;
}


void CStartPPView::OnUpdatePan(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_PAN);
}


void CStartPPView::OnRotate()
{
	state = ST_ROTATE;
}


void CStartPPView::OnUpdateRotate(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_ROTATE);
}


void CStartPPView::OnSelect()
{
	state = ST_SELECT;
	GetOwner()->SendMessage(WM_SETMESSAGESTRING, IDS_SELECT_MODE_HELPSTRING);
}


void CStartPPView::OnUpdateSelect(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(state == ST_SELECT);
}


BOOL CStartPPView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	UINT nCursorIDs[] =
		{
			IDC_PAN, // ST_PAN
			IDC_SELECT, // ST_SELECT
			IDC_ROTATE, // ST_ROTATE
			IDC_ZOOM, // ST_ZOOM
			IDC_SELECT
		};

	::SetCursor(AfxGetApp()->LoadCursor(nCursorIDs[state - 1]));
	if (state == ST_SELECT)
		GetOwner()->SendMessage(WM_SETMESSAGESTRING, IDS_SELECT_MODE_HELPSTRING);

	return TRUE;
}


void CStartPPView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int x = GetScrollPos(SB_HORZ);
	//int xOrig = x;

	switch (nSBCode)
	{
	case SB_TOP:
		x = 0;
		break;
	case SB_BOTTOM:
		x = INT_MAX;
		break;
	case SB_LINEUP:
		x -= m_lineDev.cx;
		break;
	case SB_LINEDOWN:
		x += m_lineDev.cx;
		break;
	case SB_PAGEUP:
		x -= m_pageDev.cx;
		break;
	case SB_PAGEDOWN:
		x += m_pageDev.cx;
		break;
	case SB_THUMBTRACK:
		x = nPos;
		break;
	}
	CRect clr;
	GetClientRect(&clr);

	SetScrollPos(SB_HORZ, x);
	m_ViewSettings.Xorg = clr.Width() - m_ScrPresenter.x_min * m_ViewSettings.ScrScale - x;
	Invalidate();
	//CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CStartPPView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	//SetScrollPos(SB_VERT, nPos);
	int y = GetScrollPos(SB_VERT);
	//int yOrig = y;

	switch (nSBCode)
	{
	case SB_TOP:
		y = 0;
		break;
	case SB_BOTTOM:
		y = INT_MAX;
		break;
	case SB_LINEUP:
		y -= m_lineDev.cy;
		break;
	case SB_LINEDOWN:
		y += m_lineDev.cy;
		break;
	case SB_PAGEUP:
		y -= m_pageDev.cy;
		break;
	case SB_PAGEDOWN:
		y += m_pageDev.cy;
		break;
	case SB_THUMBTRACK:
		y = nPos;
		break;
	}
	CRect clr;
	GetClientRect(&clr);
	SetScrollPos(SB_VERT, y);
	m_ViewSettings.Yorg = clr.Height() + m_ScrPresenter.y_max * m_ViewSettings.ScrScale - y;
	Invalidate();
	//CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CStartPPView::OnViewNodeNums()
{
	m_ViewSettings.ShowNums = !m_ViewSettings.ShowNums;
	Invalidate();
}


void CStartPPView::OnUpdateViewNodeNums(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_ViewSettings.ShowNums);
}


void CStartPPView::OnViewSizes()
{
	m_ViewSettings.ShowDims = !m_ViewSettings.ShowDims;
	Invalidate();
}


void CStartPPView::OnUpdateViewSizes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_ViewSettings.ShowDims);
}


void CStartPPView::OnViewAprof()
{
	m_ViewSettings.ShowAProf = !m_ViewSettings.ShowAProf;
	Invalidate();
}


void CStartPPView::OnUpdateViewAprof(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_ViewSettings.ShowAProf);
}


void CStartPPView::OnViewElements()
{
	m_ViewSettings.ShowElms = !m_ViewSettings.ShowElms;
	Invalidate();
}


void CStartPPView::OnUpdateViewElements(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_ViewSettings.ShowElms);
}


void CStartPPView::OnViewNodes()
{
	m_ViewSettings.ShowPoints = !m_ViewSettings.ShowPoints;

	Invalidate();
}


void CStartPPView::OnUpdateViewNodes(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_ViewSettings.ShowPoints);
}


int CStartPPView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_rend.BindWindow(GetSafeHwnd(), false, nullptr);
	m_OglPresenter.ghDC = m_rend.m_hMemDC;
	m_OglPresenter.ghRC = m_rend.m_hMemRC;

	return 0;
}


void CStartPPView::OnDestroy()
{
	CScrollView::OnDestroy();

	m_rend.ReleaseWindow();
}


void CStartPPView::OnShowOgl()
{
	m_bShowOGL = !m_bShowOGL;
	//if (m_bShowOGL)
	//	m_OglPresenter.vecSel = m_ScrPresenter.vecSel;
	//else
	//	m_ScrPresenter.vecSel = m_OglPresenter.vecSel;
	Invalidate();
}


void CStartPPView::OnUpdateShowOgl(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowOGL);
}


void CStartPPView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: добавьте специализированный код или вызов базового класса

	CScrollView::OnPrepareDC(pDC, pInfo);
}


void CStartPPView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	CViewSettings viewSettings(m_ViewSettings);
	CScreenPipePresenter prn(&m_pipeArray, m_rot, viewSettings);
	*(prn.Result) = *(m_ScrPresenter.Result);
	prn.pvecSel = m_ScrPresenter.pvecSel;
	CRect clr = pInfo->m_rectDraw;
	CPrintHelper::DrawFrame(pDC, clr, m_pDocument->GetPathName());
	if (m_bShowOGL)
	{
		pInfo->m_rectDraw = clr;
		CViewSettings vp(m_ViewSettings);
		m_OglPresenter.Print(pDC, pInfo, &m_rot, GetSafeHwnd());
		m_ViewSettings = vp;
	}
	else
	{
		CRect rc;
		GetClientRect(&rc);
		prn.ElemScale = 4;
		float S = float(clr.Width()) / rc.Width();
		CPoint pt = clr.CenterPoint();
		CPoint ptCenter(rc.Size().cx / 2, rc.Size().cy / 2);
		viewSettings.Zoom(S, pt, &ptCenter);
		pDC->IntersectClipRect(&clr);
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
	CDistDialog dlg(m_bShowOGL ? m_OglPresenter : m_ScrPresenter);
	dlg.DoModal();
}

void CStartPPView::OnProj(void)
{
	SetRot(DPT_Top);
}

void CStartPPView::OnView3dviewsBack()
{
	SetRot(DPT_Back);
}

void CStartPPView::OnView3dviewsBottom()
{
	SetRot(DPT_Bottom);
}

void CStartPPView::OnView3dviewsDimetry()
{
	SetRot(DPT_Dimetry);
}

void CStartPPView::OnView3dviewsFront()
{
	SetRot(DPT_Front);
}

void CStartPPView::OnView3dviewsLeft()
{
	SetRot(DPT_Left);
}

void CStartPPView::OnView3dviewsNeIso()
{
	SetRot(DPT_NorthEast);
}

void CStartPPView::OnView3dviewsNwIso()
{
	SetRot(DPT_NorthWest);
}

void CStartPPView::OnView3dviewsRight()
{
	SetRot(DPT_Right);
}

void CStartPPView::OnView3dviewsSeIso()
{
	SetRot(DPT_SouthEast);
}

void CStartPPView::OnView3dviewsSwIso()
{
	SetRot(DPT_SouthWest);
}

void CStartPPView::OnView3dviewsTop()
{
	SetRot(DPT_Top);
}

int CStartPPView::SetRot(int nView)
{
	m_rot.SetPredefinedView(nView);

	m_ViewSettings.Plan = (nView == DPT_Top);
	m_ScrPresenter.copy_pipes(GetDocument()->m_pipes.m_vecPnN);
	OnZoomAll();
	return 0;
}

void CStartPPView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	if (bActivate)
	{
		CPipePresenter* p = m_bShowOGL ? &m_OglPresenter : &m_ScrPresenter;
		CString strText;
		strText.Format(LoadStr(IDS_FORMAT_UCH_UZL), p->NumPipes, p->NumNodes);
		static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1, strText);
		if (GetDocument()->vecSel.size() > 0)
		{
			GetDocument()->Select(GetDocument()->vecSel.begin()->SelNAYZ, GetDocument()->vecSel.begin()->SelKOYZ);
			//m_OglPresenter.vecSel = p->vecSel;
		}
		else
		{
			CPipeAndNode p1 = GetDocument()->m_pipes.m_vecPnN[GetDocument()->m_pipes.m_nIdx];
			GetDocument()->Select(int(p1.m_NAYZ), int(p1.m_KOYZ));
		}
	}
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


void CStartPPView::OnEditCopy()
{
	m_bCut = false;
	OnEditCutCopy();
}


void CStartPPView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 27 && state == ST_SELECT_NODE)
	{
		state = o_state;
		GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	}

	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}


void CStartPPView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetDocument()->vecSel.size() > 0 && GetDocument()->vecSel.begin()->SelNAYZ >= 0);
}

void CStartPPView::OnEditCut()
{
	m_bCut = true;
	OnEditCutCopy();
}


void CStartPPView::OnEditCutCopy(void)
{
	if (state == ST_SELECT_NODE)
		return;

	if (!GetDocument()->IsSelConnected())
	{
		AfxMessageBox(IDS_PARTS_NOT_CONNECTED, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	o_state = state;
	state = ST_SELECT_NODE;
	GetOwner()->SendMessage(WM_SETMESSAGESTRING, IDS_SELECT_BASE_NODE);
}

