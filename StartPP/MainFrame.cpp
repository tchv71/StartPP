#include "stdafx.h"
#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "StartPPView.h"

MainFrame::MainFrame(wxDocManager *manager, wxWindow* parent)
    : MainFrameBaseClass(manager, static_cast<wxFrame*>(parent))
{
    //m_mgr->AddPane(m_auibarFilter, wxAuiPaneInfo().Caption(wxT("Фильтры")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).Fixed().CaptionVisible(true).MaximizeButton(false).CloseButton(true).MinimizeButton(false).PinButton(false).ToolbarPane());
    //m_mgr->AddPane(m_auibarView, wxAuiPaneInfo().Caption(wxT("Навигация")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).CaptionVisible(true).MaximizeButton(false).CloseButton(false).MinimizeButton(false).PinButton(false).ToolbarPane());
    //m_mgr->AddPane(m_auibarOperations, wxAuiPaneInfo().Caption(wxT("Операции")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).CaptionVisible(true).MaximizeButton(false).CloseButton(false).MinimizeButton(false).PinButton(false).ToolbarPane());
	GetPropWnd()->GetPropList()->GetGrid()->SetSplitterPosition(400);
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("(c) Dmitry Tsvetkov aka tchv,2016"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Cross-platform Start Preprocessor"));
    ::wxAboutBox(info);
}

void MainFrame::OnAuibookAuinotebookPageClose(wxAuiNotebookEvent& event)
{
}
