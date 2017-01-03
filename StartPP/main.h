#pragma once
#include <wx/app.h>
#include <wx/event.h>
#include <wx/glcanvas.h>
#include <wx/docview.h>
class wxGLCanvas;

// Define the MainApp
class MainApp : public wxApp
{
public:
    MainApp();
    virtual ~MainApp();

	bool OnInit() override;

	int OnExit() override;

	void SetContext(wxGLCanvas* canvas, bool bRelease = false);
private:
	wxGLContext *m_glContext;
	wxDocManager *m_pDocManager;
    wxLocale m_locale;  // locale we'll be using
};

DECLARE_APP(MainApp)