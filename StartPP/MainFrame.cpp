#include "stdafx.h"
#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "StartPPView.h"

MainFrame::MainFrame(wxDocManager *manager, wxWindow* parent)
    : MainFrameBaseClass(manager, NULL)
{
    // tell wxAuiManager to manage this frame
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
    info.SetCopyright(_("My MainFrame"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Short description goes here"));
    ::wxAboutBox(info);
}

void MainFrame::OnImportDbf(wxCommandEvent& event)
{
    m_doc->OnImportDbf();
	event.Skip();
}
void MainFrame::OnRecordNext(wxCommandEvent& event)
{
    m_doc->OnRecordNext();
	event.Skip();
}
void MainFrame::OnRecordPrevious(wxCommandEvent& event)
{
    m_doc->OnRecordPrev();
	event.Skip();
}


