#pragma once
#include "wx/glcanvas.h"

class wxView;

class wxGLCanvasViewWnd : public wxGLCanvas
{
public:
	wxGLCanvasViewWnd(wxView * view, wxWindow *parent);

	~wxGLCanvasViewWnd();
	void SetChildView(wxView *view) { m_childView = view; }
	wxView* GetChildView() { return m_childView; }
	void OnActivate(wxActivateEvent& event);
	void OnCloseWindow(wxCloseEvent& event);
protected:
	wxDECLARE_EVENT_TABLE();
	wxView *m_childView;
};

class wxPanelViewWnd : public wxPanel
{
public:
    wxPanelViewWnd(wxView * view, wxWindow *parent);

    ~wxPanelViewWnd();
    void SetChildView(wxView *view) { m_childView = view; }
    wxView* GetChildView() { return m_childView; }
    void OnActivate(wxActivateEvent& event);
    void OnCloseWindow(wxCloseEvent& event);
protected:
    wxDECLARE_EVENT_TABLE();
    wxView *m_childView;
};
