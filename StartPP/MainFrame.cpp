#include "stdafx.h"
#include "MainFrame.h"
#include <wx/aboutdlg.h>

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
    // tell wxAuiManager to manage this frame
	m_wndProp = new CPropertiesWnd(this);
	m_mgr->AddPane(m_wndProp, wxAuiPaneInfo().
                  Name(wxT("propgrid")).Caption(wxT("Property Grid Pane")).
                  Left().Layer(1).Position(1).
                  CloseButton(true).MaximizeButton(true));
	m_mgr->Update();
	m_doc.m_pFrame = this;
	m_doc.OnNewDocument();
	GetView()->SetDocument(&m_doc);
	GetView()->OnInitialUpdate();
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
    m_doc.OnImportDbf();
	event.Skip();
}
void MainFrame::OnRecordNext(wxCommandEvent& event)
{
    m_doc.OnRecordNext();
	event.Skip();
}
void MainFrame::OnRecordPrevious(wxCommandEvent& event)
{
    m_doc.OnRecordPrev();
	event.Skip();
}

