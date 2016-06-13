#pragma once
#include <wx/app.h>
#include <wx/event.h>
#include "MainFrame.h"
#include <wx/image.h>
#include <wx/propgrid/propgrid.h>
// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp() : m_glContext(nullptr) {}
    virtual ~MainApp() {}

    virtual bool OnInit() {
        // Add the common image handlers
        wxImage::AddHandler( new wxPNGHandler );
        wxImage::AddHandler( new wxJPEGHandler );

        MainFrame *mainFrame = new MainFrame(NULL);
        SetTopWindow(mainFrame);
        return GetTopWindow()->Show();
    }
	virtual int OnExit()
	{
		delete m_glContext;
		return wxApp::OnExit();
	}
	wxGLContext& GetContext(wxGLCanvas *canvas)
	{
		wxGLContext *glContext;
		if ( !m_glContext )
		{
			// Create the OpenGL context for the first mono window which needs it:
			// subsequently created windows will all share the same context.
			m_glContext = new wxGLContext(canvas);
		}
		glContext = m_glContext;
		glContext->SetCurrent(*canvas);

		return *glContext;
	}
private:
	wxGLContext *m_glContext;
};

DECLARE_APP(MainApp)