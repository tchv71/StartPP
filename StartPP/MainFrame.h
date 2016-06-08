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
	CPropertiesWnd* GetPropWnd() { return m_wndProp; }
protected:
    virtual void OnRecordNext(wxCommandEvent& event);
    virtual void OnRecordPrevious(wxCommandEvent& event);
    virtual void OnImportDbf(wxCommandEvent& event);
	CPropertiesWnd* m_wndProp;
};
#endif // MAINFRAME_H
