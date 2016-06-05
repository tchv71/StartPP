#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "StartPPDoc.h"

class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxWindow* parent);
    virtual ~MainFrame();
	CStartPPDoc m_doc;
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
protected:
    virtual void OnRecordNext(wxCommandEvent& event);
    virtual void OnRecordPrevious(wxCommandEvent& event);
    virtual void OnImportDbf(wxCommandEvent& event);
};
#endif // MAINFRAME_H
