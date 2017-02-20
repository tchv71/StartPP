#include "stdafx.h"
#include "MainFrame.h"
#include <wx/aboutdlg.h>
#include "PropertiesWnd.h"
#include "PipeTable.h"
#include <wx/utils.h>

BEGIN_EVENT_TABLE(MainFrame,MainFrameBaseClass)
	EVT_MENU(MainFrame::wxID_ImportDbf, MainFrame::OnImportDbf)
END_EVENT_TABLE()

MainFrame::MainFrame(wxDocManager *manager, wxWindow* parent)
    : MainFrameBaseClass(manager, static_cast<wxFrame*>(parent))
{
    //m_mgr->AddPane(m_auibarFilter, wxAuiPaneInfo().Caption(wxT("Фильтры")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).Fixed().CaptionVisible(true).MaximizeButton(false).CloseButton(true).MinimizeButton(false).PinButton(false).ToolbarPane());
    //m_mgr->AddPane(m_auibarView, wxAuiPaneInfo().Caption(wxT("Навигация")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).CaptionVisible(true).MaximizeButton(false).CloseButton(false).MinimizeButton(false).PinButton(false).ToolbarPane());
    //m_mgr->AddPane(m_auibarOperations, wxAuiPaneInfo().Caption(wxT("Операции")).Direction(wxAUI_DOCK_TOP).Layer(0).Row(0).Position(0).CaptionVisible(true).MaximizeButton(false).CloseButton(false).MinimizeButton(false).PinButton(false).ToolbarPane());
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	m_simpleBookPanel->SetSizer(boxSizer);

	m_propWnd = new CPropertiesWnd(m_simpleBookPanel, wxID_ANY);
	boxSizer->Add(m_propWnd, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));
	SetSize(100,100);
    wxPersistenceManager::Get().Restore(this);

	GetPropWnd()->GetPropList()->GetGrid()->SetSplitterPosition(200);
	wxConfigBase *pConfig = wxConfigBase::Get();
	wxString strPersp;
	if (pConfig && !wxGetKeyState(WXK_SHIFT))
	{
		pConfig->Read(wxT("perspective"), &strPersp, wxEmptyString);
	}
	if (!strPersp.IsEmpty())
		GetMgr()->LoadPerspective(strPersp);
#ifdef __WXMAC__
    m_menuFile->Delete(m_menuItemFileExit);
#endif
 	
}

MainFrame::~MainFrame()
{
}

void MainFrame::SetDocument(wxDocument *pdoc)
{
    if (m_doc != pdoc)
    {
        m_doc = static_cast<CStartPPDoc*>(pdoc);
        m_grid912->SetTable(new PipeTable(),true);
		m_grid912->SetColFormat();
        m_grid912->ForceRefresh();
    }
}

void MainFrame::RefreshGrid()
{
	m_grid912->ForceRefresh();
}


void MainFrame::OnExit(wxCommandEvent& event)
{
	wxConfigBase *pConfig = wxConfigBase::Get();
	wxString strPersp =	GetMgr()->SavePerspective();
	if (pConfig)
	{
		pConfig->Write(wxT("perspective"), strPersp);
	}
	wxUnusedVar(event);
    Close();
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxUnusedVar(event);
    wxAboutDialogInfo info;
    info.SetCopyright(_("(c) Dmitry Tsvetkov aka tchv,2016"));
	info.SetVersion(_("1.0.1.10"));
    info.SetLicence(_("GPL v2 or later"));
    info.SetDescription(_("Cross-platform Start Preprocessor"));
    ::wxAboutBox(info);
}

void MainFrame::OnImportDbf(wxCommandEvent& event)
{
	CStartPPDoc *pDoc = static_cast<CStartPPDoc*>(GetDocumentManager()->CreateNewDocument());
	pDoc->OnImportDbf(event);
}

CPropertiesWnd* MainFrame::GetPropWnd() const
{
	return m_propWnd;
}	
