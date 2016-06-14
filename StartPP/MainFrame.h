#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "StartPPDoc.h"
#include <wx/aui/aui.h>
#include "PropertiesWnd.h"

class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
	CStartPPDoc m_doc;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    virtual void OnZoomWindow(wxCommandEvent& event);
    virtual void OnPan(wxCommandEvent& event);
    virtual void OnRotate(wxCommandEvent& event);
    virtual void OnSelect(wxCommandEvent& event);
    virtual void OnZoomAll(wxCommandEvent& event);
    virtual void OnZoomIn(wxCommandEvent& event);
    virtual void OnZoomOut(wxCommandEvent& event);
    virtual void OnViewTop(wxCommandEvent& event);
    virtual void OnShowOgl(wxCommandEvent& event);
    virtual void OnRecordNext(wxCommandEvent& event);
    virtual void OnRecordPrevious(wxCommandEvent& event);
    virtual void OnImportDbf(wxCommandEvent& event);
};
#endif // MAINFRAME_H
