#include "stdafx.h"
#include <wx/docview.h>
#include "wxGLCanvasViewWnd.h"

wxBEGIN_EVENT_TABLE(wxGLCanvasViewWnd, wxGLCanvas)
	EVT_CLOSE(wxGLCanvasViewWnd::OnCloseWindow)
wxEND_EVENT_TABLE()

const int attribList[] = { WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 24, 0 };

wxGLCanvasViewWnd::wxGLCanvasViewWnd(wxView * view, wxWindow *parent) : wxGLCanvas(parent,-1, attribList), m_childView(view)
{
}

wxGLCanvasViewWnd::~wxGLCanvasViewWnd()
{

}

void wxGLCanvasViewWnd::OnActivate(wxActivateEvent& event)
{
	if (m_childView)
		m_childView->Activate(event.GetActive());
}

void wxGLCanvasViewWnd::OnCloseWindow(wxCloseEvent& event)
{
	if (m_childView)
	{
		// notice that we must call wxView::Close() and OnClose() called from
		// it in any case, even if we know that we are going to close anyhow
		if (!m_childView->Close(false) && event.CanVeto())
		{
			event.Veto();
			return;
		}

		m_childView->Activate(false);

		// it is important to reset m_childView frame pointer to NULL before
		// deleting it because while normally it is the frame which deletes the
		// view when it's closed, the view also closes the frame if it is
		// deleted directly not by us as indicated by its doc child frame
		// pointer still being set
		m_childView->SetDocChildFrame(nullptr);
		wxDELETE(m_childView);
	}
}

