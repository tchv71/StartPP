#ifndef MAINFRAME_H
#define MAINFRAME_H
#include "wxcrafter.h"
#include "StartPPDoc.h"
#include <wx/aui/aui.h>
#include "PropertiesWnd.h"

class CStartPPView;
class MainFrame : public MainFrameBaseClass
{
public:
    MainFrame(wxDocManager *manager, wxWindow* parent=nullptr);
    virtual ~MainFrame();
	void SetDocument(wxDocument *pdoc) { m_doc = static_cast<CStartPPDoc*>(pdoc); }
	CStartPPDoc* m_doc;
	CStartPPView* GetView() { return m_pView; }
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnImportDbf(wxCommandEvent& event);
protected:
    CStartPPView* m_pView;
	DECLARE_EVENT_TABLE()
};
#endif // MAINFRAME_H
