// dbfdoc.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include "wx/ext/gui.h"

#include "../../ioapi/zlib.h"
#include "../../ioapi/ioapi.h"
#include "../../bool.h"
#include "../../dbf.h"
#include "../../dbf.hpp"
#include "../../dbf.inl"
#include "../../dbf_wx.h"
#include "../../dbf_wx.inl"
#include "dbfdoc.h"
#include "dbfdlgs.h"
#include "wxstreamc.h"
#include "dbfart.h"

wxIMPLEMENT_DYNAMIC_CLASS(DBFDocument, wxDocument);

DBFDocument::DBFDocument() : wxDocument(), m_database(new wxDBase()), m_stream(NULL)
{
}

DBFDocument::~DBFDocument()
{
    delete m_database;
}

wxString DBFDocument::GetTablename() const
{
    wxASSERT(m_database);
    DBF_INFO info;
    m_database->GetInfo(&info);
    return wxConvertMB2WX(info.tablename);
}

// Since text windows have their own method for saving to/loading from files,
// we override OnSave/OpenDocument instead of Save/LoadObject
bool DBFDocument::DoSaveDocument(const wxString& WXUNUSED(filename))
{
    /*
    DBFView* view = (DBFView*)GetFirstView();
    if (!view->textsw->SaveFile(filename))
        return false;
        */
    Modify(false);
    return true;
}

bool DBFDocument::AttachStream(wxInputStream& stream, const wxString& filePath)
{
    const wxFileName fileName(filePath);
    struct zlib_filefunc_def_s api;
    bool ok;

    ::fill_filefunc(&api, &stream);
    ok = m_database->Attach(&stream, &api, dbf_editmode_readonly, dbf_charconv_default, NULL, fileName.GetName());
    if (ok)
    {
        m_stream = &stream;
        SetTitle(fileName.GetFullPath());
        SetFilename(fileName.GetFullPath(), true);
        wxFileLoadedHint hint;
        UpdateAllViews(NULL, &hint);
    }
    else
        wxLogError(_("Bad file format in file \"%s\"."), fileName.GetFullPath().wx_str());
    return ok;
}

bool DBFDocument::DeleteContents()
{
    bool ok = base::DeleteContents();
    wxDELETE(m_stream);
    if (m_database->IsOpen())
        m_database->Close();
    return ok;
}

bool DBFDocument::DoOpenDocument(const wxString& filePath)
{
    const wxFileName fileName(filePath);
    //wxFileInputStream stream(fileName.GetFullPath());
    //bool ok = stream.IsOk();
    bool ok = fileName.FileExists();

    if (ok)
    {
        ok = m_database->Open(fileName, dbf_editmode_editable);
        if (!ok)
            ok = m_database->Open(fileName, dbf_editmode_readonly);
        if (ok)
        {
            SetTitle(fileName.GetFullPath());
            wxFileLoadedHint hint;
            UpdateAllViews(NULL, &hint);
        }
        else
            wxLogError(_("Bad file format in file \"%s\"."), fileName.GetFullPath().wx_str());
    }
    else
        wxLogError(_("Failed to open the file \"%s\" for reading."), fileName.GetFullPath().wx_str());
    return ok;
}

bool DBFDocument::IsModified() const
{
   //return m_database->IsOpen() && m_database->IsModified();
    return base::IsModified();
}

void DBFDocument::Modify(bool mod)
{
    base::Modify(mod);
}

bool DBFDocument::OnCloseDocument()
{
    bool ok = base::OnCloseDocument();

    return ok;
}

bool DBFDocument::IsEditable() const
{
    return m_database->IsOpen() && m_database->IsEditable();
}

bool DBFDocument::StructDialog(wxWindow* parent)
{
    wxDBase* db = GetDatabase();
    DBF_INFO info;
    DBF_FIELD_INFO field_info;
    DBaseFieldVector vec;

    db->GetInfo(&info);

    for (size_t i = 0; ; i++)
    {
        if (db->GetFieldInfo((dbf_uint)i, &field_info))
            vec.push_back(field_info);
        else
            break;
    }
    return ::DoModal_Structure(parent, wxEmptyString, &vec, &info.version);
}

bool DBFDocument::OnNewDocument()
{
    bool ok = base::OnNewDocument();
    if (ok)
    {
        NewDatabaseParm parm;
        parm.FileName = wxFileName(GetDocumentManager()->GetLastDirectory(), GetTitle(), GetDocumentTemplate()->GetDefaultExtension());

        ok = ::DoModal_NewDatabase(wxTheApp->GetTopWindow(), wxGetStockLabelEx(wxID_NEW, wxSTOCK_WITHOUT_ELLIPSIS), &parm);
        if (ok)
        {
            DBaseCreateParm temp;
            temp.vector  = parm.vector;
            temp.version = parm.Version;
            ok = m_database->Create(parm.FileName, temp);
        }
        if (ok)
        {
            SetTitle(parm.FileName.GetFullName());
            SetFilename(parm.FileName, true);
            wxFileLoadedHint hint;
            UpdateAllViews(NULL, &hint);
            GetDocumentManager()->AddFileToHistory(parm.FileName.GetFullPath());
        }
    }
    return ok;
}

bool DBFDocument::OnNewDocument(const wxString& title, const DBaseFieldVector& vec, int version)
{
    bool ok = base::OnNewDocument();
    if (ok)
    {
        base::SetFilename(title);
        ok = SaveAs();
    }
    if (ok)
    {
        DBaseCreateParm temp;
        temp.vector  = vec;
        temp.version = version;
        ok = m_database->Create(GetFilename(), temp);
    }
    if (ok)
    {
        wxFileLoadedHint hint;
        UpdateAllViews(NULL, &hint);
    }
    return ok;
}

bool DBFDocument::SaveAs()
{
    bool ok = base::SaveAs();

    if (ok)
    {
    }
    return ok;
}

/////////////////////////////////////////////////////////////////////////////
// DBFDocTemplate

#include "dbfview.h"
#include "dbfframe.h"

wxIMPLEMENT_CLASS(DBFDocTemplate, wxDocTemplate);

//static
DBFDocTemplate* DBFDocTemplate::ms_instance = NULL;

//static
const wxDocTemplateClassInfo DBFDocTemplate::m_DefaultClassInfo(wxCLASSINFO(DBFDocument), wxCLASSINFO(DBFView), wxCLASSINFO(DBFFrame));

DBFDocTemplate::DBFDocTemplate(wxDocManager* docManager,
                                         const wxDocTemplateClassInfo& classInfo,
                                         wxRecentFileList* mru) : wxDocTemplate(docManager, 
        wxString::Format(_("%s Files"), wxT(DBF_FORMAT_NAME)), wxString(wxT("*.")) + wxDBase::FileExt,
        wxT(""), wxDBase::FileExt, wxT("dbf doc"), wxT("dbf view"),
        classInfo.m_doc, classInfo.m_view), m_frameClassInfo(classInfo.m_frame), m_mru(mru)
{
    ms_instance = this;
}

//static
DBFDocTemplate* DBFDocTemplate::Create(wxDocManager* docManager, wxRecentFileList* mru)
{
   return new DBFDocTemplate(docManager, m_DefaultClassInfo, mru);
}

//static
wxIcon DBFDocTemplate::GetIcon()
{
    return wxArtProvider::GetIcon(DBF_ART_DATABASEDOC);
}

wxFrame* DBFDocTemplate::CreateViewFrame(wxView* view)
{
    DBFFrame* subframe = wxStaticCast(m_frameClassInfo->CreateObject(), DBFFrame);

    if (subframe->Create(wxStaticCast(wxTheApp->GetTopWindow(), wxMDIParentFrame), view, m_mru))
        subframe->SetIcon(GetIcon());
    else
        wxDELETE(subframe);
    return subframe;
}

wxDocument* DBFDocTemplate::CreateDocument(const wxString& path, long flags)
{
    wxDocument* doc = base::CreateDocument(path, flags);
    return doc;
}

/////////////////////////////////////////////////////////////////////////////
