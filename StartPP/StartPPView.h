// StartPPView.h : интерфейс класса CStartPPView
//
#include "Rotate.h"
#include "PipePresenter.h"
#include "GLRenderer.h"
#include "OGLPipePresenter.h"
#include <wx/scrolwin.h>

#pragma once

class CStartPPSet;
class CMainFrame;

class CStartPPView : public wxScrolledWindow//CScrollView
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void Zoom(float S);
	//	afx_msg void OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
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

