// StartPPView.h : интерфейс класса CStartPPView
//
#pragma once
#include "stdafx.h"
#include "Rotate.h"
#include "PipePresenter.h"
#include "ScreenPipePresenter.h"
#include "GLFontRenderer.h"
#include "OGLPipePresenter.h"
#include <wx/window.h>
#include <wx/scrolwin.h>
#include <wx/docview.h>
#include <wx/aui/auibook.h>


class CStartPPSet;
class CMainFrame;

/*============================================================================*/
// class CView is the client area UI for a document

class CPrintDialog;     // forward reference (see afxdlgs.h)
class CPreviewView;     // forward reference (see afxpriv.h)
class CSplitterWnd;     // forward reference (see afxext.h)
class COleServerDoc;    // forward reference (see afxole.h)
struct CPrintInfo;
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


class wxStartPPPrintout : public wxDocPrintout
{
public:
	wxStartPPPrintout(wxView* view) : wxDocPrintout(view) {}
	virtual bool OnPrintPage(int page) wxOVERRIDE;
};

class CStartPPView : public wxView
{
protected: // создать только из сериализации
	enum E_STATE
	{
		ST_PAN = 1,
		ST_SELECT,
		ST_ROTATE,
		ST_ZOOM_WIN,
		ST_SELECT_NODE
	};

	E_STATE state,o_state;
	bool m_bActive;
	int m_nPage;
public:
	CStartPPView();
	//DECLARE_DYNCREATE(CStartPPView)

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
	CGLFontRenderer m_rend;
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
	int m_nView;
	//TCursor crSave;
	// Операции
public:

protected:
	void CheckAndActivate() const;
	// Реализация
public:
	virtual ~CStartPPView();
	void OnTimer(wxTimerEvent& event);
	void OnFilePrintPreview();
	// Созданные функции схемы сообщений
protected:
	wxMenu* m_menu;
	afx_msg void OnContextMenu(wxContextMenuEvent & event);
	void OnPaint(wxPaintEvent& event);
	void OnDraw(CDC* /*pDC*/) override;
	wxWindow* m_wnd;
public:
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSize(wxSizeEvent& event);
	void Update() const;
	void SetDocnameInTab() const;
	void OnUpdate(wxView *sender, wxObject *hint = NULL) override;
	
	void OnLButtonDown(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnLButtonUp(wxMouseEvent& event);
	void OnMouseWheel(wxMouseEvent& event);
#ifdef __WXMAC__
	void OnRButtonDown(wxMouseEvent& event);
#endif
	
	void Zoom(float S);
	afx_msg void OnZoomIn(wxCommandEvent& event);
	afx_msg void OnZoomOut(wxCommandEvent& event);
	afx_msg void OnZoomAll(wxCommandEvent& event);
	afx_msg void OnMButtonDown(wxMouseEvent& event);
	afx_msg void OnMButtonUp(wxMouseEvent& event);
	afx_msg void OnZoomWin(wxCommandEvent& event);
	afx_msg void OnUpdateZoomWin(wxUpdateUIEvent& event);
	afx_msg void OnPan(wxCommandEvent& event);
	afx_msg void OnUpdatePan(wxUpdateUIEvent& event);
	afx_msg void OnRotate(wxCommandEvent& event);
	afx_msg void OnUpdateRotate(wxUpdateUIEvent& event);
	afx_msg void OnSelect(wxCommandEvent& event);
	afx_msg void OnUpdateSelect(wxUpdateUIEvent& event);
	afx_msg BOOL OnSetCursor();
	afx_msg void OnScroll(wxScrollEvent& event);
	//afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnViewNodeNums(wxCommandEvent& event);
	afx_msg void OnUpdateViewNodeNums(wxUpdateUIEvent& event);
	afx_msg void OnViewSizes(wxCommandEvent& event);
	afx_msg void OnUpdateViewSizes(wxUpdateUIEvent& event);
	afx_msg void OnViewAprof(wxCommandEvent& event);
	afx_msg void OnUpdateViewAprof(wxUpdateUIEvent& event);
	afx_msg void OnViewElements(wxCommandEvent& event);
	afx_msg void OnUpdateViewElements(wxUpdateUIEvent& event);
	afx_msg void OnViewNodes(wxCommandEvent& event);
	afx_msg void OnUpdateViewNodes(wxUpdateUIEvent& event);
	afx_msg int Create();
	//afx_msg void OnDestroy();
	afx_msg void OnShowOgl(wxCommandEvent& event);
	afx_msg void OnUpdateShowOgl(wxUpdateUIEvent& event);
	void OnPrint(wxDC *dc, wxObject *info) override;
	afx_msg void OnUpdateDist(wxUpdateUIEvent& event);
	void OnDist(wxCommandEvent& event);
	void OnProj(wxCommandEvent& event);
	afx_msg void OnView3dviewsBack(wxCommandEvent& event);
	afx_msg void OnView3dviewsBottom(wxCommandEvent& event);
	afx_msg void OnView3dviewsDimetry(wxCommandEvent& event);
	afx_msg void OnView3dviewsFront(wxCommandEvent& event);
	afx_msg void OnView3dviewsLeft(wxCommandEvent& event);
	afx_msg void OnView3dviewsNeIso(wxCommandEvent& event);
	afx_msg void OnView3dviewsNwIso(wxCommandEvent& event);
	afx_msg void OnView3dviewsRight(wxCommandEvent& event);
	afx_msg void OnView3dviewsSeIso(wxCommandEvent& event);
	afx_msg void OnView3dviewsSwIso(wxCommandEvent& event);
	afx_msg void OnView3dviewsTop(wxCommandEvent& event);
	int SetRot(int nView);

protected:
	void OnActivateView(bool activate,
                                wxView *activeView,
                                wxView *deactiveView) override;
	bool OnCreate(wxDocument *WXUNUSED(doc), long WXUNUSED(flags)) wxOVERRIDE;
	bool OnClose(bool deleteWindow) wxOVERRIDE;
	void OnPageClose(wxAuiNotebookEvent& evt);
	void OnPageClosed(wxAuiNotebookEvent& evt);
	void OnPageChanged(wxAuiNotebookEvent& evt);
	wxPrintout* OnCreatePrintout() wxOVERRIDE;
	void OnMouseCaptureLost(wxMouseCaptureLostEvent& event);
public:
	afx_msg void OnEditCopy(wxCommandEvent& event);
	afx_msg void OnChar(wxKeyEvent& event);
	afx_msg void OnUpdateEditCopy(wxUpdateUIEvent& event);
	//	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	//	afx_msg void OnEditPaste();
	afx_msg void OnEditCut(wxCommandEvent& event);
protected:
	bool m_bCut;
	wxTimer m_Timer;
public:
	void OnEditCutCopy(void);
    wxDECLARE_EVENT_TABLE();
    wxDECLARE_DYNAMIC_CLASS(CStartPPView);
};

inline CStartPPDoc* CStartPPView::GetDocument() const
   { return reinterpret_cast<CStartPPDoc*>(m_viewDocument); }


class wxWindow;
