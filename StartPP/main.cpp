﻿#include "stdafx.h"

#include "main.h"
#include "MainFrame.h"
#include <wx/image.h>
#include <wx/propgrid/propgrid.h>
#include <wx/docview.h>
#include "StartPPDoc.h"
#include "StartPPView.h"
#include "wx/config.h"

IMPLEMENT_APP(MainApp)

MainApp::MainApp() : m_glContext(nullptr), m_pDocManager(nullptr), m_locale(wxLANGUAGE_RUSSIAN) 
{
}

MainApp::~MainApp()
{
	wxDELETE(m_pDocManager);
	wxDELETE(m_glContext);
}

bool MainApp::OnInit()
{

	if (!wxApp::OnInit())
		return false;
	SetAppDisplayName(wxT("Старт Препроцессор"));
	// Add the common image handlers
	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxGIFHandler);
	m_pDocManager = new wxDocManager;
#ifdef __WXMAC__
	wxPGInitResourceModule();
#endif
#ifdef __WXMSW__
	wxLocale::AddCatalogLookupPathPrefix("..");
#endif
	m_locale.AddCatalog(wxT("wxstd"));

	MainFrame *mainFrame = new MainFrame(m_pDocManager);
	SetTopWindow(mainFrame);
	//// Create a document manager
	//// Create a template relating drawing documents to their views
	new wxDocTemplate(m_pDocManager, "StartPP doc", "*.spf", "", "spf",
		"StartPP doc", "StartPP View",
		CLASSINFO(CStartPPDoc), CLASSINFO(CStartPPView));
	m_pDocManager->FileHistoryUseMenu(mainFrame->GetMenuBar()->GetMenu(0));
	m_pDocManager->FileHistoryLoad(*wxConfig::Get());
	mainFrame->SetDocument(m_pDocManager->CreateNewDocument());
	SetInstance(this);
	return GetTopWindow()->Show();
}

int MainApp::OnExit()
{
	m_pDocManager->FileHistorySave(*wxConfig::Get());
	wxImage::CleanUpHandlers();
	return wxApp::OnExit();
}

void MainApp::SetContext(wxGLCanvas* canvas, bool bRelease)
{
	wxGLContext *glContext;
	if ( !m_glContext )
	{
		// Create the OpenGL context for the first mono window which needs it:
		// subsequently created windows will all share the same context.
		m_glContext = new wxGLContext(canvas);
	}
	glContext = m_glContext;
	if (!bRelease)
		glContext->SetCurrent(*canvas);
	else
	{
		//const Window drawable = canvas->GetXWindow();

		//glXMakeContextCurrent( wxGetX11Display(), drawable, drawable, NULL);
 
		//delete m_glContext;
		//m_glContext = NULL;
	}
}
