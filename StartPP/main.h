#pragma once
#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include <wx/propgrid/propgrid.h>
#include <wx/docview.h>
#include "StartPPDoc.h"
#include "StartPPView.h"
// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() : m_glContext(nullptr), m_pDocManager(nullptr) {}
    virtual ~MainApp() {}

    virtual bool OnInit() {
		if (!wxApp::OnInit())
			return false;
        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );
		wxImage::AddHandler(new wxGIFHandler);
		m_pDocManager = new wxDocManager;
		//wxPGInitResourceModule();

        MainFrame *mainFrame = new MainFrame(m_pDocManager);
        SetTopWindow(mainFrame);
		    //// Create a document manager
		//// Create a template relating drawing documents to their views
		new wxDocTemplate(m_pDocManager, "StartPP doc", "*.spd", "", "spd",
                      "StartPP doc", "StartPP View",
                      CLASSINFO(CStartPPDoc), CLASSINFO(CStartPPView));

		mainFrame->SetDocument(m_pDocManager->CreateNewDocument());
		SetInstance(this);
        return GetTopWindow()->Show();
    }
	virtual int OnExit()
	{
		delete m_pDocManager;
		wxImage::CleanUpHandlers();
		delete m_glContext;
		return wxApp::OnExit();
	}
	void SetContext(wxGLCanvas *canvas, bool bRelease=false)
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
private:
	wxGLContext *m_glContext;
	wxDocManager *m_pDocManager;
};

DECLARE_APP(MainApp)