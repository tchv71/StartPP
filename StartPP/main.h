#pragma once
#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include <wx/propgrid/propgrid.h>
// Define the MainApp
class SetCurrent;
class SetCurrent;
class MainApp : public wxApp
{
public:
    MainApp() : m_glContext(nullptr) {}
    virtual ~MainApp() {}

    virtual bool OnInit() {
        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );
		wxImage::AddHandler(new wxGIFHandler);
        MainFrame *mainFrame = new MainFrame(NULL);
        SetTopWindow(mainFrame);
        return GetTopWindow()->Show();
    }
	virtual int OnExit()
	{
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
};

DECLARE_APP(MainApp)