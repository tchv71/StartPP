#include "stdafx.h"

#include "main.h"
#include "MainFrame.h"
#include <wx/image.h>
#include <wx/propgrid/propgrid.h>
#include <wx/docview.h>
#include "StartPPDoc.h"
#include "StartPPView.h"
#include "wx/config.h"
#include "wx/dir.h"
#include <string>
#include <wx/help.h>
#ifdef __WXMSW__
	#include <wx/msw/helpchm.h>
#else
	#include <wx/html/helpctrl.h>
#endif
#include "wx/fs_zip.h"


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
#ifdef __WXMAC__
	wxDir d;
	if (!d.Exists(DATA_PATH))
	{
		d.Make(DATA_PATH, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
		wxStringList files(_T("arial.ttf"),_T("Armat.dbf"),_T("Matup.dbf"),_T("Pipes.dbf"),_T("Troinics.dbf"),NULL);
		wxString strFrom = GetAppName()+_T(".app/Contents/Data/");
		for (int i=0; i<files.size(); i++)
			wxCopyFile(strFrom+files[i], DATA_PATH+_T("/")+files[i]);
	}
#endif
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
	
#ifdef __WXMSW__
	// Create an MS HTML Help controller
	m_helpController = new wxCHMHelpController;
#else
	// Create a wxWidgets HTML Help controller
	m_helpController = new wxHtmlHelpController;
#endif
	// Initialize the help controller with the base
	// name of the help file. In practice you should pass
	// an absolute pathname. You may omit the extension
	// for portability.
	wxFileSystem::AddHandler(new wxZipFSHandler);

	m_helpController->Initialize(wxT("StartPP"));
	bool bRes = m_helpController->LoadFile();

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

