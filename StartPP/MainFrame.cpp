#include "stdafx.h"
#include "MainFrame.h"
#include <wx/aboutdlg.h>

MainFrame::MainFrame(wxWindow* parent)
    : MainFrameBaseClass(parent)
{
	m_doc.m_pFrame = this;
	m_doc.OnNewDocument();
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
}
void MainFrame::OnRecordNext(wxCommandEvent& event)
{
    m_doc.OnRecordNext();
}
void MainFrame::OnRecordPrevious(wxCommandEvent& event)
{
    m_doc.OnRecordPrev();
}
void MainFrame::OnMo(wxCommandEvent& event)
{
}
