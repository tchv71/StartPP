// StartPPView.h : интерфейс класса CStartPPView
//
#pragma once

#include "Rotate.h"
#include "PipePresenter.h"
#include "ScreenPipePresenter.h"
#include "GLRenderer.h"
#include "OGLPipePresenter.h"
#include <wx/scrolwin.h>


class CStartPPSet;
class CMainFrame;

/*============================================================================*/
// class CView is the client area UI for a document

class CPrintDialog;     // forward reference (see afxdlgs.h)
class CPreviewView;     // forward reference (see afxpriv.h)
class CSplitterWnd;     // forward reference (see afxext.h)
class COleServerDoc;    // forward reference (see afxole.h)
class CPrintInfo;
class CPrintPreviewState;

#ifndef __WXMSW__
class CREATESTRUCT;
class LPCREATESTRUCT;
#endif
class AFX_CMDHANDLERINFO;
typedef DWORD DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)

typedef DWORD DROPEFFECT;
class COleDataObject;   // forward reference (see afxole.h)
class CDumpContext;
class CDocument;
class CStartPPDoc;

class CView : public CWnd
{
	friend class CWinAppEx;

	DECLARE_DYNAMIC(CView)
	// Constructors
protected:
	CView();

	// Attributes
public:
	CDocument* GetDocument() const;

	// Operations
public:
	// for standard printing setup (override OnPreparePrinting)
	BOOL DoPreparePrinting(CPrintInfo* pInfo);

	// Overridables
public:
	//virtual BOOL IsSelected(const CObject* pDocItem) const; // support for OLE

															// OLE scrolling support (used for drag/drop as well)
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE);

	// OLE drag/drop support
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual BOOL OnDrop(COleDataObject* pDataObject,
		DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDropEx(COleDataObject* pDataObject,
		DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	virtual DROPEFFECT OnDragScroll(DWORD dwKeyState, CPoint point);

	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

	virtual void OnInitialUpdate(); // called first time after construct

protected:
	// Activation
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView,
		CView* pDeactiveView);
	virtual void OnActivateFrame(UINT nState, CFrameWnd* pFrameWnd);

	// General drawing/updating
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnDraw(CDC* pDC);

	// Printing support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	// must override to enable printing and print preview

	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Advanced: end print preview mode, move to point
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point,
		CPreviewView* pView);

	// Implementation
public:
	virtual ~CView();
#ifdef _DEBUG
	virtual void Dump(CDumpContext&) const;
	virtual void AssertValid() const;
#endif //_DEBUG

	// Advanced: for implementing custom print preview
	BOOL DoPrintPreview(UINT nIDResource, CView* pPrintView,
		CRuntimeClass* pPreviewViewClass, CPrintPreviewState* pState);

	virtual void CalcWindowRect(LPRECT lpClientRect,
		UINT nAdjustType = 1/*adjustBorder*/);
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	static CSplitterWnd* GetParentSplitter(
		const CWnd* pWnd, BOOL bAnyState);

protected:
	CDocument* m_pDocument;
	BOOL m_bInitialRedraw;

public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PostNcDestroy();

	// friend classes that call protected CView overridables
	friend class CDocument;
	friend class CDocTemplate;
	friend class CPreviewView;
	//friend class CFrameWnd;
	friend class CMDIFrameWnd;
	friend class CMDIChildWnd;
	friend class CSplitterWnd;
	friend class COleServerDoc;
	friend class CDocObjectServer;

	afx_msg int Create();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);

	// Print client support: used for interaction with Windows task bar
	afx_msg LRESULT OnPrintClient(CDC* pDC, UINT nFlags);

	// commands
	afx_msg void OnUpdateSplitCmd(CCmdUI* pCmdUI);
	afx_msg BOOL OnSplitCmd(UINT nID);
	afx_msg void OnUpdateNextPaneMenu(CCmdUI* pCmdUI);
	afx_msg BOOL OnNextPaneCmd(UINT nID);

	// not mapped commands - must be mapped in derived class
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();

	DECLARE_MESSAGE_MAP()
};

/*============================================================================*/
// class CScrollView supports simple scrolling and scaling

class _AFX_MOUSEANCHORWND;
#define SIZE CSize

class CScrollView : public CView
{
	DECLARE_DYNAMIC(CScrollView)

	// Constructors
protected:
	CScrollView();

public:
	static const SIZE sizeDefault;
	// used to specify default calculated page and line sizes

	// in logical units - call one of the following Set routines
	void SetScaleToFitSize(SIZE sizeTotal);
	void SetScrollSizes(int nMapMode, SIZE sizeTotal,
		const SIZE& sizePage = sizeDefault,
		const SIZE& sizeLine = sizeDefault);

	// Attributes
public:
	CPoint GetScrollPosition() const;       // upper corner of scrolling
	CSize GetTotalSize() const;             // logical size

	void CheckScrollBars(BOOL& bHasHorzBar, BOOL& bHasVertBar) const;

	// for device units
	CPoint GetDeviceScrollPosition() const;
	void GetDeviceScrollSizes(int& nMapMode, SIZE& sizeTotal,
		SIZE& sizePage, SIZE& sizeLine) const;

	// Operations
public:
	void ScrollToPosition(POINT pt);    // set upper left position
	void FillOutsideRect(CDC* pDC, CBrush* pBrush);
	void ResizeParentToFit(BOOL bShrinkOnly = TRUE);
	BOOL DoMouseWheel(UINT fFlags, short zDelta, CPoint point);

	// Implementation
protected:
	_AFX_MOUSEANCHORWND* m_pAnchorWindow; // window for wheel mouse anchor
	friend class _AFX_MOUSEANCHORWND;
	int m_nMapMode;				 // mapping mode for window creation
	CSize m_totalLog;           // total size in logical units (no rounding)
	CSize m_totalDev;           // total size in device units
	CSize m_pageDev;            // per page scroll size in device units
	CSize m_lineDev;            // per line scroll size in device units

	BOOL m_bCenter;             // Center output if larger than total size
	BOOL m_bInsideUpdate;       // internal state for OnSize callback
	void CenterOnPoint(CPoint ptCenter);
	void ScrollToDevicePosition(POINT ptDev); // explicit scrolling no checking

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnDraw(CDC* pDC);      // pass on pure virtual

	void UpdateBars();          // adjust scrollbars etc
	BOOL GetTrueClientSize(CSize& size, CSize& sizeSb);
	// size with no bars
	void GetScrollBarSizes(CSize& sizeSb);
	void GetScrollBarState(CSize sizeClient, CSize& needSb,
		CSize& sizeRange, CPoint& ptMove, BOOL bInsideClient);

public:
	virtual ~CScrollView();
#ifdef _DEBUG
	void Dump(CDumpContext&) const override;
	void AssertValid() const override;
#endif //_DEBUG
	virtual void CalcWindowRect(LPRECT lpClientRect,
	                            UINT nAdjustType = 1 /* adjustBorder*/)
	{
	}

	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL) override;

	virtual CSize GetWheelScrollDistance(CSize sizeDistance,
		BOOL bHorz, BOOL bVert);

	// scrolling implementation support for OLE
	BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE) override;
	BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll = TRUE) override;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//afx_msg BOOL OnMouseWheel(UINT fFlags, short zDelta, CPoint point);
	afx_msg LRESULT HandleMButtonDown(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPrintClient(CDC* pDC, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};


class CStartPPView : public CScrollView
{
protected: // создать только из сериализации
	CStartPPView();
	DECLARE_DYNCREATE(CStartPPView)

public:
	CMainFrame* m_pFrame;
	// Атрибуты
public:
	bool m_bShowOGL;
	CViewSettings m_ViewSettings;
	CStartPPDoc* GetDocument() const;
	CRotator m_rot;
	CPipeArray m_pipeArray;
	CScreenPipePresenter m_ScrPresenter;
	CGLRenderer m_rend;
	COGLPipePresenter m_OglPresenter;
	int DownX, DownY;
	BOOL Down;
	float Xorg1, Yorg1;
	float z_rot1, x_rot1;
	bool bZoomed;
	bool m_bInitialized;
	CPoint MovePt;
	CPipeArray tmpPipeArray;
	CSize m_OldSize;
	//TCursor crSave;
	// Операции
public:

	// Переопределение
public:
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;
protected:
	void DoDataExchange(CDataExchange* pDX) override; // поддержка DDX/DDV
	void OnInitialUpdate() override; // вызывается в первый раз после конструктора
	BOOL OnPreparePrinting(CPrintInfo* pInfo) override;
	void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) override;
	void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) override;

	// Реализация
public:
	virtual ~CStartPPView();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif


	// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	void OnActivateFrame(UINT nState, CFrameWnd* pDeactivateFrame) override;
	void OnDraw(CDC* /*pDC*/) override;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/) override;
	
	void OnLButtonDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnLButtonUp(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
	
	void Zoom(float S);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnZoomAll();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnZoomWin();
	afx_msg void OnUpdateZoomWin(CCmdUI* pCmdUI);
	afx_msg void OnPan();
	afx_msg void OnUpdatePan(CCmdUI* pCmdUI);
	afx_msg void OnRotate();
	afx_msg void OnUpdateRotate(CCmdUI* pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnScroll(wxScrollEvent& event);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewNodeNums();
	afx_msg void OnUpdateViewNodeNums(CCmdUI* pCmdUI);
	afx_msg void OnViewSizes();
	afx_msg void OnUpdateViewSizes(CCmdUI* pCmdUI);
	afx_msg void OnViewAprof();
	afx_msg void OnUpdateViewAprof(CCmdUI* pCmdUI);
	afx_msg void OnViewElements();
	afx_msg void OnUpdateViewElements(CCmdUI* pCmdUI);
	afx_msg void OnViewNodes();
	afx_msg void OnUpdateViewNodes(CCmdUI* pCmdUI);
	afx_msg int Create();
	afx_msg void OnDestroy();
	afx_msg void OnShowOgl();
	afx_msg void OnUpdateShowOgl(CCmdUI* pCmdUI);
	void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = nullptr) override;
	void OnPrint(CDC* pDC, CPrintInfo* pInfo) override;
	afx_msg void OnUpdateDist(CCmdUI* pCmdUI);
	afx_msg void OnDist();
	void OnProj(void);
	afx_msg void OnView3dviewsBack();
	afx_msg void OnView3dviewsBottom();
	afx_msg void OnView3dviewsDimetry();
	afx_msg void OnView3dviewsFront();
	afx_msg void OnView3dviewsLeft();
	afx_msg void OnView3dviewsNeIso();
	afx_msg void OnView3dviewsNwIso();
	afx_msg void OnView3dviewsRight();
	afx_msg void OnView3dviewsSeIso();
	afx_msg void OnView3dviewsSwIso();
	afx_msg void OnView3dviewsTop();
	int SetRot(int nView);
protected:
	void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) override;
public:
	afx_msg void OnEditCopy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	//	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	//	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
protected:
	bool m_bCut;
public:
	void OnEditCutCopy(void);
};

#ifndef _DEBUG  // отладочная версия в MFCApplication1View.cpp

inline CStartPPDoc* CStartPPView::GetDocument() const
   { return reinterpret_cast<CStartPPDoc*>(m_pDocument); }
#endif

