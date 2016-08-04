#pragma once
#include "wx\glcanvas.h"

class wxView;

class wxGLCanvasViewWnd :
	public wxGLCanvas
{
public:
	wxGLCanvasViewWnd(wxView * view, wxWindow *parent);

	~wxGLCanvasViewWnd();
	void SetChildView(wxView *view) { m_childView = view; }
protected:
	void OnActivate(wxActivateEvent& event);
	void OnCloseWindow(wxCloseEvent& event);
	wxView *m_childView;
};

