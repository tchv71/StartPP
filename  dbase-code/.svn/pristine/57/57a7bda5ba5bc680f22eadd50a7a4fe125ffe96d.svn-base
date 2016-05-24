// appdoc.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include "wx/ext/gui.h"

#include "app.h"
#include "dbfdoc.h"
#include "appframe.h"
#include "../../bool.h"
#include "../../dbf.h"
#include "../../dbf.hpp"
#include "../../dbf_wx.h"
#include "appdoc.h"

wxIMPLEMENT_CLASS(DocManager, wxDocManagerEx);

wxBEGIN_EVENT_TABLE(DocManager, wxDocManagerEx)
    EVT_MENU(XRCID("folder")         , DocManager::OnOpenContainingFolder)
    EVT_UPDATE_UI(XRCID("folder")    , DocManager::OnUpdateNeedSaved)
    EVT_UPDATE_UI(wxID_ADD           , DocManager::OnUpdateDisableIfNoDoc)
    EVT_UPDATE_UI(wxID_FIND          , DocManager::OnUpdateDisableIfNoDoc)
    EVT_UPDATE_UI(wxID_DELETE        , DocManager::OnUpdateDisableIfNoDoc)
    EVT_UPDATE_UI(XRCID("edit")      , DocManager::OnUpdateDisableIfNoDoc)
    EVT_UPDATE_UI(XRCID("struct")    , DocManager::OnUpdateDisableIfNoDoc)
    EVT_UPDATE_UI(XRCID("pack")      , DocManager::OnUpdateDisableIfNoDoc)
    EVT_UPDATE_UI(XRCID("export")    , DocManager::OnUpdateDisableIfNoDoc)
wxEND_EVENT_TABLE()

void DocManager::OnOpenContainingFolder(wxCommandEvent&)
{
    const wxDocument* doc = GetCurrentDocument();
    wxBusyCursor busy;
    wxLaunchDefaultApplication(wxFileName(doc->GetFilename()).GetPath());
}

void DocManager::OnUpdateNeedSaved(wxUpdateUIEvent& event)
{
    const wxDocument* doc = GetCurrentDocument();
    event.Enable(doc && doc->GetDocumentSaved());
}

wxDocument* DocManager::CreateDocument(const wxString& path, long flags)
{
    wxDocument* doc;
#if (wxVERSION_NUMBER >= 2901)
    doc = base::CreateDocument(path, flags);
    if (doc)
    {
        wxWindow* frame = doc->GetDocumentWindow();
        frame->SendSizeEvent();
        frame->Show();
    }
#else
    doc = base::CreateDocument(path, flags);
    if (doc)
    {
        wxWindow* frame = doc->GetDocumentWindow();
        frame->Show();
        wxTrunkDocView::ActivateDocument(doc); // as in trunk wxDocManager::CreateDocument()
    }
#endif
    return doc;
}

DocManager::DocManager(App* app) : wxDocManagerEx()
{
    wxRecentFileList* mru = new wxRecentFileList(GetFileHistory());

    app->m_mru = mru;
    DBFDocTemplate::Create(this, mru);
}

#if (wxVERSION_NUMBER >= 2901)
wxPreviewFrame* DocManager::CreatePreviewFrame(wxPrintPreviewBase* preview,
                                               wxWindow *parent,
                                               const wxString& title)
{
    wxPreviewFrame* frame = base::CreatePreviewFrame(preview, parent, title);
    ::wxFrame_ClonePosition(frame); // Clone main frame position
    return frame;
}
#endif

wxDocManager* App::CreateDocManager()
{
    DocManager* docManager = new DocManager(this);

    return docManager;
}

wxDocument* DocManager::CreateExampleDocument(const wxString& fullname)
{
    wxDocTemplate* docTemplate = FindTemplateForPath(wxString(wxT("*.")) + wxDBase::FileExt);
    wxDocument* doc = NULL;
    DbfExampleVector::const_iterator it = PUB_DbfExampleVector.Find(fullname);

    if (it != PUB_DbfExampleVector.end())
    {
        doc = docTemplate ? docTemplate->CreateDocument(wxEmptyString, wxDOC_NEW) : NULL;
        if (doc)
        {
            bool ok;

            if (wxDynamicCast(doc, DBFDocument))
            {
                DBFDocument* dbf_doc = wxStaticCast(doc, DBFDocument);

                ok = dbf_doc->OnNewDocument(it->Name, it->Vector, it->Version);
            }
            else
                ok = false;

            if (ok)
            {
                doc->GetDocumentWindow()->Show();
                wxTrunkDocView::ActivateDocument(doc);
            }
            else
            {
                doc->GetDocumentManager()->CloseDocument(doc);
                doc = NULL;
            }
        }
    }
    return doc;
}

class DbfStructCalendar3 : public DbfStruct
{
public:
    DbfStructCalendar3() : DbfStruct()
    {
        Name = wxT("calendar.3");
        Version = 3;
        const DBF_FIELD_INFO fields[] =
        {
          { "DATE"    , DBF_DATA_TYPE_DATE   , DBF_LEN_DATE, 0 },
          { "TEXT"    , DBF_DATA_TYPE_CHAR   , 80, 0 },
          { "ANNIVERS", DBF_DATA_TYPE_BOOLEAN, DBF_LEN_BOOLEAN, 0 }
        };
        Vector.assign(fields, fields + WXSIZEOF(fields));
    }
};
class DbfStructTimestamp4 : public DbfStruct
{
public:
    DbfStructTimestamp4() : DbfStruct()
    {
        Name = wxT("timestamp.4");
        Version = 4;
        const DBF_FIELD_INFO fields[] =
        {
          { "TIMESTAMP", DBF_DATA_TYPE_DATETIME, 0, 0 }
        };
        Vector.assign(fields, fields + WXSIZEOF(fields));
    }
};

DbfExampleVector::DbfExampleVector()
{
    const DbfStruct array[] =
    {
        DbfStructCalendar3(),
        DbfStructTimestamp4()
    };
    assign(array, array + WXSIZEOF(array));
}

wxArrayString DbfExampleVector::GetNames() const
{
    wxArrayString as;
    for (const_iterator it = begin(); it != end(); it++)
        as.push_back(it->Name);
    return as;
}

DbfExampleVector::const_iterator DbfExampleVector::Find(const wxString& name) const
{
    for (const_iterator it = begin(); it != end(); it++)
    {
        if (0 == name.CmpNoCase(it->Name))
            return it;
    }
    return end();
}

const DbfExampleVector PUB_DbfExampleVector;


/////////////////////////////////////////////////////////////////////////////
