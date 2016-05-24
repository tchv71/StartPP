// dbfview.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include <wx/numdlg.h>
#include <wx/html/htmprint.h>
#include <wx/fdrepdlg.h>

#include "wx/ext/docview.h"

#include "dbfview.h"
#include "dbfdoc.h"
#include "datamodel.h"
#include "datalist.h"
#include "dbfutil.h"
#include "dbfmodel.h"
#include "dbflist.h"
#include "printout.h"

#if USE_DATALISTVIEW
class DbfDateTimeRenderer : public wxDataViewTextRenderer
{
    typedef wxDataViewTextRenderer base;
public:
    DbfDateTimeRenderer(const wxString& varianttype = wxT("datetime"),
                              wxDataViewCellMode mode = wxDATAVIEW_CELL_EDITABLE)
                              : wxDataViewTextRenderer(varianttype, mode)
    {
    }
    virtual bool SetValue(const wxVariant& value)
    {
        wxString str;
        if (!value.IsNull())
        {
            wxDateTime dt = value.GetDateTime();
            str = dt.FormatDate();
        }
        return base::SetValue(wxVariant(str));
    }
};
#endif

/////////////////////////////////////////////////////////////////////////////
// DBFWindow

class DBFWindow : public DBFListCtrl
{
    typedef DBFListCtrl base;
    wxDECLARE_CLASS(DBFWindow);
public:
    DBFWindow(DBFView* view) : DBFListCtrl(), m_datamodel(view->GetDocument()->GetDatabase()), m_view(view)
    {
    }

    bool Create(wxWindow* parent)
    {
       bool ok = base::Create(parent, wxID_ANY);
       if (ok)
           AssociateModel(&m_datamodel);
       return ok;
    }

    virtual ~DBFWindow()
    {
        //AssociateModel(NULL);
    }
#if USE_DATALISTVIEW
    virtual wxDataViewRenderer* GetRenderer(const wxString& datatype) const
    {
        if (wxT("datetime") == datatype)
            return new DbfDateTimeRenderer(datatype, wxDATAVIEW_CELL_EDITABLE);
        return base::GetRenderer(datatype);
    }
#endif
private:
    DBFModel m_datamodel;
    DBFView* m_view;
};

wxIMPLEMENT_CLASS(DBFWindow, DBFListCtrl);

/////////////////////////////////////////////////////////////////////////////
// DBFView

wxIMPLEMENT_DYNAMIC_CLASS(DBFView, wxViewEx);

DBFView::DBFView() : wxViewEx(), m_find(new DataModelFind())
{
}

DBFView::~DBFView()
{
    delete m_find;
}

wxBEGIN_EVENT_TABLE(DBFView, wxViewEx)
    EVT_MENU(XRCID("struct"), DBFView::OnStruct)
    EVT_UPDATE_UI(XRCID("struct"), DBFView::OnUpdateNeedEditable)
    EVT_MENU(XRCID("tool_struct"), DBFView::OnStructClipboard)
    EVT_MENU(wxID_PROPERTIES, DBFView::OnProperties)
    EVT_MENU(XRCID("file_export"), DBFView::OnFileExport)

    EVT_MENU(wxID_SELECTALL       , DBFView::OnSelectAll)
    EVT_UPDATE_UI(wxID_SELECTALL  , DBFView::OnUpdateSelectAll)
    EVT_MENU(wxID_UNDELETE        , DBFView::OnUndelete)
    EVT_UPDATE_UI(wxID_UNDELETE   , DBFView::OnUpdateNeedSel_Deleted)
    EVT_MENU(wxID_ADD             , DBFView::OnAdd)
    EVT_UPDATE_UI(wxID_ADD        , DBFView::OnUpdateNeedEditable)
    EVT_UPDATE_UI(wxID_REPLACE    , DBFView::OnUpdateNeedEditable)
    EVT_MENU(wxID_DELETE          , DBFView::OnDelete)
    EVT_UPDATE_UI(wxID_DELETE     , DBFView::OnUpdateNeedSel_NotDeleted)
    EVT_MENU(wxID_CLEAR           , DBFView::OnDeleteAll)

    EVT_MENU(XRCID("edit")        , DBFView::OnEdit)
    EVT_UPDATE_UI(XRCID("edit")   , DBFView::OnUpdateNeedSel)

    EVT_MENU(XRCID("goto")        , DBFView::OnGoto)
    EVT_MENU(wxID_COPY            , DBFView::OnCopy)
    EVT_UPDATE_UI(wxID_COPY       , DBFView::OnUpdateNeedSel)
    EVT_MENU(XRCID("copy_path")   , DBFView::OnCopyPath)

    EVT_MENU(wxID_FIND            , DBFView::OnFindDialog)
    EVT_MENU(XRCID("find_next")   , DBFView::OnFindAgain)
    EVT_MENU(XRCID("find_prev")   , DBFView::OnFindAgain)
    EVT_FIND(wxID_ANY             , DBFView::OnFindEvent)
    EVT_FIND_NEXT(wxID_ANY        , DBFView::OnFindEvent)
    EVT_FIND_CLOSE(wxID_ANY       , DBFView::OnFindEvent)
wxEND_EVENT_TABLE()

wxWindow* DBFView::GetModalParent() const
{
    return GetDocument()->GetDocumentWindow();
}

bool DBFView::OnCreate(wxDocument* doc, long flags)
{
    bool ok = base::OnCreate(doc, flags);

    if (ok)
    {
        wxFrame* frame = wxStaticCast(doc->GetDocumentTemplate(), DBFDocTemplate)->CreateViewFrame(this);
        DBFWindow* wnd = new DBFWindow(this);

        wxASSERT(frame == GetFrame());
        if (wnd->Create(frame))
            SetWindow(wnd);
        else
            delete wnd;
    }
    return ok;
}

DBFWindow* DBFView::GetWindow() const
{
    return wxStaticCast(base::GetWindow(), DBFWindow);
}

void DBFView::OnStruct(wxCommandEvent&)
{
    if (GetDocument()->StructDialog(GetModalParent()))
    {
    }
}

void DBFView::OnUpdateNeedEditable(wxUpdateUIEvent& event)
{
    event.Enable(GetDocument()->IsEditable());
}

void DBFView::OnUpdate(wxView* sender, wxObject* hint)
{
    if (wxDynamicCast(hint, wxFileLoadedHint))
    {
        //GetWindow()->InitColumns(150, true);
        DBFWindow* wnd = GetWindow();

        wxBusyCursor busy;
        wnd->Freeze();
        wnd->InitColumns();
        if (wnd->GetItemCount() != 0)
            wnd->SelectRow(0);
        wnd->Thaw();
    }
    else
        base::OnUpdate(sender, hint);
}

bool DBFView::OnClose(bool deleteWindow)
{
    bool ok = base::OnClose(deleteWindow);
    if (ok)
    {
        Activate(false);
        GetWindow()->AssociateModel(NULL);
        if (deleteWindow && GetFrame())
        {
            GetFrame()->Destroy();
            SetFrame(NULL);
        }
    }
    return ok;
}

DBFDocument* DBFView::GetDocument() const
{
    return wxStaticCast(base::GetDocument(), DBFDocument);
}

void DBFView::OnStructClipboard(wxCommandEvent&)
{
    const DBFDocument* doc = GetDocument();
    const wxString str = ::dbf_getstruct_c(doc->GetDatabase());
    bool ok = wxClipboardHelper::SetText(str);

    ::wxMessageBox(ok ? _("Struct is now on the Clipboard") : _("Failed to open clipboard"),
        wxMessageBoxCaptionStr, wxOK | wxCENTRE, GetModalParent());
}

void DBFView::OnProperties(wxCommandEvent&)
{
    const DBFDocument* doc = GetDocument();
    const DBFModel datamodel(doc->GetDatabase());
    wxArrayString as[2];

    wxDocViewHelpers::GetInfo(*doc, as + 0);

    datamodel.GetProperties(as + 1, true);
    const wxString str = ::wxJoin(vector_join(as[0], as[1]), '\n', 0);
    ::wxShowTextDialog(GetModalParent(), str, doc->GetFilename().GetFullPath(), wxTE_MULTILINE);
}

void DBFView::OnFileExport(wxCommandEvent&)
{
    const DBFDocument* doc = GetDocument();
    const DBFModel datamodel(doc->GetDatabase());
    DataModelPrintout::ExportFileDialog(GetModalParent(), doc, &datamodel);
}

void DBFView::OnSelectAll(wxCommandEvent&)
{
    GetWindow()->SelectAll();
}

void DBFView::OnUndelete(wxCommandEvent&)
{
    GetWindow()->GetAdaptor()->DeleteSelection(false);
}

void DBFView::OnUpdateSelectAll(wxUpdateUIEvent& event)
{
    GetWindow()->OnUpdateSelectAll(event);
}

void DBFView::OnUpdateNeedSel_Deleted(wxUpdateUIEvent& event)
{
    GetWindow()->OnUpdateNeedSel_Deleted(event);
    if (!GetDocument()->IsEditable())
        event.Enable(false);
}

void DBFView::OnUpdateNeedSel_NotDeleted(wxUpdateUIEvent& event)
{
    GetWindow()->OnUpdateNeedSel_NotDeleted(event);
    if (!GetDocument()->IsEditable())
        event.Enable(false);
}

void DBFView::OnUpdateNeedSel(wxUpdateUIEvent& event)
{
    GetWindow()->OnUpdateNeedSel(event);
    if (!GetDocument()->IsEditable())
        event.Enable(false);
}

void DBFView::OnDeleteAll(wxCommandEvent&)
{
    if (wxOK == wxMessageBox(_("Delete all?"), wxMessageBoxCaptionStr, wxOK | wxCANCEL | wxICON_QUESTION, GetModalParent()))
        GetWindow()->GetAdaptor()->DeleteAll(true);
}

void DBFView::OnDelete(wxCommandEvent&)
{
    if (wxOK == wxMessageBox(_("Delete selection?"), wxMessageBoxCaptionStr, wxOK | wxCANCEL | wxICON_QUESTION, GetModalParent()))
        GetWindow()->GetAdaptor()->OnRemove();
}

void DBFView::OnAdd(wxCommandEvent&)
{
    GetWindow()->GetAdaptor()->OnAdd();
}

void DBFView::OnEdit(wxCommandEvent&)
{
    GetWindow()->Edit();
}

void DBFView::OnGoto(wxCommandEvent&)
{
    DBFWindow* wnd = GetWindow();
    int rowcount = wnd->GetItemCount();
    long row = wnd->GetSelectedRow();
    wxString msg = wxString::Format(_("Row number : 1...%d"), rowcount);

    row = wxGetNumberFromUser(msg, wxEmptyString, _("Goto row"),
                                    row+1, 1, rowcount, GetModalParent());

    if (row > 0)
    {
        wnd->SelectNone();
        wnd->SelectRow(row-1);
    }
}

void DBFView::OnCopy(wxCommandEvent&)
{
    GetWindow()->Copy();
}

void DBFView::OnCopyPath(wxCommandEvent&)
{
    wxClipboardHelper::SetText(GetDocument()->GetFilename().GetFullPath());
}

wxPrintout* DBFView::OnCreatePrintout()
{
    const DBFDocument* doc = GetDocument();
    const DBFModel model(doc->GetDatabase());
    DataModelPrintout* print = new DataModelPrintout(&model, doc->GetTitle());
#if (wxVERSION_NUMBER >= 2900)
    const wxPageSetupDialogData& page = GetDocumentManager()->GetPageSetupDialogData();
    print->SetMargins(page);
#endif
    return print;
}

void DBFView::OnFindDialog(wxCommandEvent&)
{
    m_find->ShowDialog(GetWindow(), wxFR_NOWHOLEWORD | wxFR_NOUPDOWN);
}

void DBFView::OnFindEvent(wxEventType type, const wxString& str, wxFindReplaceDialog* dlg)
{
    const DBFDocument* doc = GetDocument();
    const DBFModel model(doc->GetDatabase());

    if ( (type == wxEVT_COMMAND_FIND) || (type == wxEVT_COMMAND_FIND_NEXT) )
    {
        DBFWindow* wnd = GetWindow();
        unsigned int row = wnd->GetSelectedRow();
        if (m_find->FindNext(&model, str, &row))
        {
            wnd->SelectNone();
            wnd->SelectRow(row);
            wnd->SetFocus();
        }
    }
    else if ( type == wxEVT_COMMAND_FIND_CLOSE )
        m_find->OnCloseDialog(dlg);
    else
        wxLogError(_("Unknown find dialog event!"));
}

void DBFView::OnFindEvent(wxFindDialogEvent& event)
{
    OnFindEvent(event.GetEventType(), event.GetFindString(), event.GetDialog());
}

void DBFView::OnFindAgain(wxCommandEvent& event)
{
    if (event.GetId() == XRCID("find_next"))
    {
        wxString str = m_find->GetData()->GetFindString();
        if (!str.empty())
            OnFindEvent(wxEVT_COMMAND_FIND_NEXT, str, NULL);
    }
    else if (event.GetId() == XRCID("find_prev"))
    {
    }
    else
        wxASSERT(false);
}
