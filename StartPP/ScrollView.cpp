#include "stdafx.h"
#include "StartPPView.h"


IMPLEMENT_DYNCREATE(CView, CWnd)

BEGIN_EVENT_TABLE(CView,CWnd)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(CScrollView, CView)
END_EVENT_TABLE()

CView::CView()
{
	
}
CView::~CView()
{
	
}
#ifdef _DEBUG
void CView::Dump(CDumpContext&) const
{
}

void CView::AssertValid() const
{
}
#endif

void CView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
{
	
}


BOOL CView::DoPrintPreview(UINT nIDResource, CView* pPrintView, CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState)
{
	return FALSE;
}

BOOL CView::DoPreparePrinting(CPrintInfo* pInfo)
{
	return FALSE;
}

DROPEFFECT CView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	return 0;
}

DROPEFFECT CView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	return 0;
}

void CView::OnDragLeave()
{
	
}

BOOL CView::OnScroll(UINT nScrollCode, UINT nPos, ::BOOL bDoScroll)
{
	return FALSE;
}

BOOL CView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	return FALSE;
}

BOOL CView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	return FALSE;
}

DROPEFFECT CView::OnDropEx(COleDataObject* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
{
	return 0;
}

DROPEFFECT CView::OnDragScroll(DWORD dwKeyState, CPoint point)
{
	return 0;
}

void CView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
}

void CView::OnInitialUpdate()
{
	
}

void CView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	
}

void CView::OnActivateFrame(UINT nState, CFrameWnd* pFrameWnd)
{
	
}

BOOL CView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	return FALSE;

}

BOOL CView::PreCreateWindow(CREATESTRUCT& cs)
{
	return FALSE;
}

void CView::PostNcDestroy()
{
	
}

int CView::Create()
{
	return 0;
}

void CView::OnDestroy()
{
	
}

void CView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	
}

void CView::OnDraw(CDC* pDC)
{
}

BOOL CView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return FALSE;
}


void CView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
}

void CView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
}

void CView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	
}

void CView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView)
{
	
}


CScrollBar* CView::GetScrollBarCtrl(int nBar) const
{
	return nullptr;
}


IMPLEMENT_DYNAMIC(CScrollView,CView)

CScrollView::CScrollView()
{
	
}

void CScrollView::SetScrollSizes(int nMapMode, CSize sizeTotal, const CSize& sizePage, const CSize& sizeLine)
{
	
}

void CScrollView::CenterOnPoint(CPoint ptCenter)
{
	
}

#ifdef _DEBUG
void CScrollView::Dump(CDumpContext&) const
{
	
}

void CScrollView::AssertValid() const
{
	
}
#endif


BOOL CScrollView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll)
{
	return FALSE;
}

CSize CScrollView::GetWheelScrollDistance(CSize sizeDistance, BOOL bHorz, BOOL bVert)
{
	return CSize(0, 0);
}

CScrollView::~CScrollView()
{
	
}

void CScrollView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	
}

BOOL CScrollView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	return FALSE;
}

void CScrollView::OnSize(UINT nType, int cx, int cy)
{
	
}

const CSize CScrollView::sizeDefault = CSize(0, 0);


void CScrollView::DoDataExchange(CDataExchange* pDX)
{
	
}

void CScrollView::OnDraw(CDC* pDC)
{
}
