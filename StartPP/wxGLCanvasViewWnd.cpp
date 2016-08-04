#include "stdafx.h"
#include <wx/docview.h>
#include "wxGLCanvasViewWnd.h"


wxGLCanvasViewWnd::wxGLCanvasViewWnd(wxView * view, wxWindow *parent) : wxGLCanvas(parent), m_childView(view)
{
	this->Connect(wxEVT_ACTIVATE, wxActivateEventHandler(wxGLCanvasViewWnd::OnActivate), nullptr, this);
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(wxGLCanvasViewWnd::OnCloseWindow), nullptr, this);
}

wxGLCanvasViewWnd::~wxGLCanvasViewWnd()
{
	if (m_childView)
	{
		// notice that we must call wxView::Close() and OnClose() called from
		// it in any case, even if we know that we are going to close anyhow
		m_childView->Close(false);

		m_childView->Activate(false);

		// it is important to reset m_childView frame pointer to NULL before
		// deleting it because while normally it is the frame which deletes the
		// view when it's closed, the view also closes the frame if it is
		// deleted directly not by us as indicated by its doc child frame
		// pointer still being set
		m_childView->SetDocChildFrame(NULL);
		wxDELETE(m_childView);
	}
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
		m_childView->SetDocChildFrame(NULL);
		wxDELETE(m_childView);
	}
}

