// dbfdlgs.cpp
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

#include "dbfdlgs.h"

#define C_ASSERT_(n,e) typedef char __C_ASSERT__##n[(e)?1:-1]

static const wxChar* const MOD_aszType[] =
{
    wxT("Char"),
    wxT("Number"),
    wxT("Float"),
    wxT("Date"),
    wxT("Time"),
    wxT("DateTime"), /* non standard */
    wxT("Memo"),     /* non standard */
    wxT("Logical")
};
C_ASSERT_(1,WXSIZEOF(MOD_aszType) == DBF_DATA_TYPE_ENUMCOUNT);

/////////////////////////////////////////////////////////////////////////////
// StructListView

class StructListView : public wxTrunkListView
{
    typedef wxTrunkListView base;
    wxDECLARE_DYNAMIC_CLASS(StructListView);
public:
    DBaseFieldVector* m_vector;

    enum col
    {
        col_name,
        col_type,
        col_length,
        //col_decimals,
        col_enumcount
    };

   StructListView();
   void Init(DBaseFieldVector*);
   void Refresh();
   void Add(const DBF_FIELD_INFO&);

// Implementation
public:
   virtual ~StructListView();
   virtual wxString OnGetItemText(long item, long col) const wxOVERRIDE;
};

wxIMPLEMENT_DYNAMIC_CLASS(StructListView, wxTrunkListView);

StructListView::StructListView() : wxTrunkListView(), m_vector(NULL)
{
}

StructListView::~StructListView()
{
}

void StructListView::Init(DBaseFieldVector* vec)
{
    const wxChar* aszType[] =
    {
      wxT("Name"),
      wxT("Type"),
      wxT("Length"),
      //wxT("Decimals")
    };
    C_ASSERT_(1, col_enumcount == WXSIZEOF(aszType));
    size_t i;
    m_vector = vec;

    for (i = 0; i < WXSIZEOF(aszType); i++)
      AppendColumn(aszType[i], (i == col_length) ? wxLIST_FORMAT_RIGHT : wxLIST_FORMAT_LEFT, 80);

    Refresh();
    SelectRow(0);
    SetFocus();
}

void StructListView::Refresh()
{
    SetItemCount((long)m_vector->size());
    base::Refresh();
}

void StructListView::Add(const DBF_FIELD_INFO& info)
{
    m_vector->push_back(info);
    Refresh();
    SelectRow((long)(m_vector->size() - 1));
}

wxString StructListView::OnGetItemText(long item, long col) const
{
    wxString str;
    const DBF_FIELD_INFO& info = m_vector->at(item);

    switch (col)
    {
      case col_name:
         str = wxConvertMB2WX(info.name); break;
      case col_type:
         str = MOD_aszType[info.type]; break;
      case col_length:
         str = info.decimals
            ? wxString::Format(wxT("%d:%d"), info.length, info.decimals)
            : wxString::Format(wxT("%d"), info.length);
         break;
         /*
      case col_decimals:
         str = wxItoa(info.decimals); break;
         */
    }
    return str;
}

/////////////////////////////////////////////////////////////////////////////
// StructListViewAdaptor

class StructListViewAdaptor : public wxAddRemoveAdaptor
{
public:
    StructListViewAdaptor(StructListView* list = NULL) : m_listCtrl(list)
    {
    }
    void SetItemsCtrl(StructListView* list)
    {
         m_listCtrl = list;
    }
    wxWindow* GetItemsCtrl() const wxOVERRIDE
    {
        return m_listCtrl;
    }
    bool CanAdd() const wxOVERRIDE
    {
        return true;
    }
    bool CanRemove() const wxOVERRIDE
    {
        // We must have a selected item in order to be able to delete it.
        return m_listCtrl->HasSelection();
    }
    void OnAdd() wxOVERRIDE
    {
        DBF_FIELD_INFO info = { "", DBF_DATA_TYPE_CHAR, 10, 0 };

        if (::DoModal_FieldEdit(wxGetTopLevelParent(m_listCtrl), &info, _("Add Field")))
            m_listCtrl->Add(info);
    }
    void OnRemove() wxOVERRIDE
    {
        const long selection = m_listCtrl->GetSelectedRow();
        m_listCtrl->m_vector->erase(m_listCtrl->m_vector->begin() + selection);
        m_listCtrl->Refresh();
    }
private:
    StructListView* m_listCtrl;
};

/////////////////////////////////////////////////////////////////////////////
// DatabaseValidator

class DatabaseValidator : public wxGenericValidator
{
    wxDECLARE_CLASS(DatabaseValidator);
    typedef wxGenericValidator base;
public:
    DatabaseValidator(int* val) : wxGenericValidator(val)
    {
    }
#if (wxVERSION_NUMBER >= 2902)
    DatabaseValidator(wxFileName* val) : wxGenericValidator(val)
    {
    }
#else
    DatabaseValidator(wxFileName* val) : wxGenericValidator((bool*)NULL)
    {
        Initialize();
        m_pFileName = val;
    }
#endif
    DatabaseValidator(const DatabaseValidator& copyFrom) : wxGenericValidator((bool*)NULL)
    {
        Initialize();
        Copy(copyFrom);
    }
    bool Copy(const DatabaseValidator& copyFrom)
    {
        m_pFileName = copyFrom.m_pFileName;
        return base::Copy(copyFrom);
    }
    void Initialize()
    {
    #if (wxVERSION_NUMBER < 2902)
        m_pFileName = NULL;
    #endif
        base::Initialize();
    }

    virtual wxObject* Clone() const wxOVERRIDE { return new DatabaseValidator(*this); }
    virtual bool TransferToWindow() wxOVERRIDE;
    virtual bool TransferFromWindow() wxOVERRIDE;
    static const intptr_t version_array[];
private:
#if (wxVERSION_NUMBER < 2902)
    wxFileName* m_pFileName;
#endif
};

//static
const intptr_t DatabaseValidator::version_array[] = { 3, 4, 7 };

wxIMPLEMENT_CLASS(DatabaseValidator, wxGenericValidator);

bool DatabaseValidator::TransferToWindow()
{
    if (wxDynamicCast(m_validatorWindow, wxComboBox) && m_pInt)
    {
        wxComboBox* pControl = (wxComboBox*)m_validatorWindow;

        for (size_t i = 0; i < WXSIZEOF(version_array); i++)
        {
            if (version_array[i] == *m_pInt)
            {
                pControl->SetSelection(i);
                return true;
            }
        }
    }
#if (wxVERSION_NUMBER < 2902)
    if (wxDynamicCast(m_validatorWindow, wxTextCtrl) && m_pFileName)
    {
        wxTextCtrl* pControl = (wxTextCtrl*) m_validatorWindow;
        pControl->ChangeValue(m_pFileName->GetFullPath()); // not SetValue()
        return true;
    }
#endif
    return base::TransferToWindow();
}

bool DatabaseValidator::TransferFromWindow()
{
    if (wxDynamicCast(m_validatorWindow, wxComboBox) && m_pInt)
    {
        wxComboBox* pControl = (wxComboBox*)m_validatorWindow;

        *m_pInt = version_array[pControl->GetSelection()];
        return true;
    }
#if (wxVERSION_NUMBER < 2902)
    if (wxDynamicCast(m_validatorWindow, wxTextCtrl) && m_pFileName)
    {
        wxTextCtrl* pControl = wxStaticCast(m_validatorWindow, wxTextCtrl);
        wxString str = pControl->GetValue();
        *m_pFileName = wxFileName(str);
        return true;
    }
#endif
    return base::TransferFromWindow();
}

/////////////////////////////////////////////////////////////////////////////
// DbfStructPanel

class DbfStructPanel : public wxPanel
{
    typedef wxPanel base;
public:
    DbfStructPanel();

    bool Create(wxWindow* parent, DBaseFieldVector*, int* version);

    const StructListView* GetList() const { return m_listCtrl; }
    void SwapItems(long i1, long i2);

// Implementation
public:
    virtual ~DbfStructPanel();

protected:
    void OnAdd(wxCommandEvent&);
    void OnEdit(wxCommandEvent&);
    void OnDelete(wxCommandEvent&);
    void OnDoubleClick(wxCommandEvent&);
    void OnUpdateNeedSel(wxUpdateUIEvent&);
    void OnUpdateAdd(wxUpdateUIEvent&);
    void OnUpdateDelete(wxUpdateUIEvent&);
    void OnUpdateUpDown(wxUpdateUIEvent&);
    void OnUpItem(wxCommandEvent&);
    void OnDownItem(wxCommandEvent&);
    wxDECLARE_EVENT_TABLE();

private:
    StructListView* m_listCtrl;
    StructListViewAdaptor m_adaptor;
};

wxBEGIN_EVENT_TABLE(DbfStructPanel, wxPanel)
    EVT_BUTTON(wxID_ADD        , DbfStructPanel::OnAdd)
    EVT_BUTTON(wxID_DELETE     , DbfStructPanel::OnDelete)
    EVT_BUTTON(XRCID("edit")   , DbfStructPanel::OnEdit)
    EVT_BUTTON(wxID_UP         , DbfStructPanel::OnUpItem)
    EVT_BUTTON(wxID_DOWN       , DbfStructPanel::OnDownItem)

    EVT_UPDATE_UI(wxID_ADD     , DbfStructPanel::OnUpdateAdd)
    EVT_UPDATE_UI(wxID_DELETE  , DbfStructPanel::OnUpdateDelete)
    EVT_UPDATE_UI(XRCID("edit"), DbfStructPanel::OnUpdateNeedSel)
    EVT_COMMAND_LEFT_DCLICK(XRCID("list"), DbfStructPanel::OnDoubleClick)
    EVT_UPDATE_UI(wxID_UP  , DbfStructPanel::OnUpdateUpDown)
    EVT_UPDATE_UI(wxID_DOWN, DbfStructPanel::OnUpdateUpDown)
wxEND_EVENT_TABLE();

DbfStructPanel::DbfStructPanel() : wxPanel(), m_listCtrl(NULL)
{
}

bool DbfStructPanel::Create(wxWindow* parent, DBaseFieldVector* vec, int* version)
{
    bool ok = wxXmlResource::Get()->LoadPanel(this, parent, wxT("struct"));

    if (ok)
    {
        m_listCtrl = XRCCTRL(*this, "list", StructListView);
        m_listCtrl->Init(vec);
        m_adaptor.SetItemsCtrl(m_listCtrl);
        wxBitmapButton* wnd;
        
        wxComboBox* cb = XRCCTRL(*this, "version", wxComboBox);
        for (size_t i = 0; i < WXSIZEOF(DatabaseValidator::version_array); i++)
        {
            wxString str = wxItoa(DatabaseValidator::version_array[i]);
            cb->Append(str);
        }
        cb->SetValidator(DatabaseValidator(version));

        wxArtClient artClient = wxART_BUTTON;
        wnd = wxStaticCast(FindWindow(wxID_DELETE), wxBitmapButton);
        wnd->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_DELETE, artClient));
        wnd = wxStaticCast(FindWindow(wxID_ADD), wxBitmapButton);
        wnd->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_PLUS, artClient));
        wnd = wxStaticCast(FindWindow(wxID_UP), wxBitmapButton);
        wnd->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_GO_UP, artClient));
        wnd = wxStaticCast(FindWindow(wxID_DOWN), wxBitmapButton);
        wnd->SetBitmapLabel(wxArtProvider::GetBitmap(wxART_GO_DOWN, artClient));
    }
    return ok;
}

DbfStructPanel::~DbfStructPanel()
{
}

void DbfStructPanel::SwapItems(long i1, long i2)
{
    DBF_FIELD_INFO temp2 = m_listCtrl->m_vector->at(i2);
    m_listCtrl->m_vector->at(i2) = m_listCtrl->m_vector->at(i1);
    m_listCtrl->m_vector->at(i1) = temp2;
    m_listCtrl->Refresh();
}

void DbfStructPanel::OnUpItem(wxCommandEvent&)
{
    const long selection = m_listCtrl->GetSelectedRow();
    SwapItems(selection - 1, selection);
    m_listCtrl->SelectRow(selection - 1);
}

void DbfStructPanel::OnDownItem(wxCommandEvent&)
{
    const long selection = m_listCtrl->GetSelectedRow();
    SwapItems(selection + 1, selection);
    m_listCtrl->SelectRow(selection + 1);
}

void DbfStructPanel::OnAdd(wxCommandEvent&)
{
    m_adaptor.OnAdd();
}

void DbfStructPanel::OnDoubleClick(wxCommandEvent& event)
{
    const long selection = m_listCtrl->GetSelectedRow();
    if (selection != wxNOT_FOUND)
        OnEdit(event);
}

void DbfStructPanel::OnEdit(wxCommandEvent&)
{
    const long selection = m_listCtrl->GetSelectedRow();
    DBF_FIELD_INFO info = m_listCtrl->m_vector->at(selection);

    if (::DoModal_FieldEdit(wxGetTopLevelParent(this), &info, _("Edit Field")))
    {
       m_listCtrl->m_vector->at(selection) = info;
       m_listCtrl->Refresh();
    }
}

void DbfStructPanel::OnDelete(wxCommandEvent&)
{
    m_adaptor.OnRemove();
}

void DbfStructPanel::OnUpdateAdd(wxUpdateUIEvent& event)
{
    event.Enable(m_adaptor.CanAdd());
}

void DbfStructPanel::OnUpdateDelete(wxUpdateUIEvent& event)
{
    event.Enable(m_adaptor.CanRemove());
}

void DbfStructPanel::OnUpdateUpDown(wxUpdateUIEvent& event)
{
    const long selection = m_listCtrl->GetSelectedRow();
    wxWindow* wnd = wxStaticCast(event.GetEventObject(), wxWindow);
    switch (event.GetId())
    {
        case wxID_UP:
            wnd->Enable((m_listCtrl->GetItemCount() > 1) && (selection != 0) && (selection != wxNOT_FOUND));
            break;
        case wxID_DOWN:
            wnd->Enable((m_listCtrl->GetItemCount() > 1) && (selection != wxNOT_FOUND) && (selection < (m_listCtrl->GetItemCount() - 1)));
            break;
    }
}

void DbfStructPanel::OnUpdateNeedSel(wxUpdateUIEvent& event)
{
    event.Enable(m_listCtrl->HasSelection());
}

/////////////////////////////////////////////////////////////////////////////
// StructureDialog

class StructureDialog : public wxDialog
{
    typedef wxDialog base;
public:
    StructureDialog() : wxDialog(), Version(0)
    {
    }
    bool Create(wxWindow* parent, const wxString& caption, int version, const DBaseFieldVector& vector)
    {
        bool ok = base::Create(parent, wxID_ANY, caption.empty() ? wxString(_("Structure")) : caption, 
                               wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
        if (ok)
        {
            Version = version;
            m_vector = vector;
            DbfStructPanel* panel = new DbfStructPanel();
            ok = panel->Create(this, &m_vector, &Version);
            if (ok)
            {
                wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
                topSizer->Add(panel, 1, wxEXPAND);
                topSizer->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), wxSizerFlags().Align(wxEXPAND).Border());
                SetSizerAndFit(topSizer);
                CenterOnParent();
                GetSizer()->SetSizeHints(this);
                SetExtraStyle(GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY);
                SetIcon(wxArtProvider::GetIcon(wxART_APP));
            }
        }
        return ok;
    }
    int Version;
    DBaseFieldVector m_vector;
protected:
    void OnUpdateNeedData(wxUpdateUIEvent&);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(StructureDialog, wxDialog)
    EVT_UPDATE_UI(wxID_OK, StructureDialog::OnUpdateNeedData)
wxEND_EVENT_TABLE();

void StructureDialog::OnUpdateNeedData(wxUpdateUIEvent& event)
{
    event.Enable(!m_vector.empty());
}

bool DoModal_Structure(wxWindow* parent, const wxString& caption, DBaseFieldVector* vector, int* version)
{
    StructureDialog dlg;
    bool ok = dlg.Create(parent, caption, *version, *vector);
    if (ok)
    {
        ok = (wxID_OK == dlg.ShowModal());
        if (ok)
        {
            *vector = dlg.m_vector;
            *version = dlg.Version;
        }
    }
    /*
        if (ok && fileName.IsOk() && !db->IsOpen())
        {
           CreateParm parm;
           parm.vector = dlg.m_vector;
           ok = db->Create(fileName, parm);
        }
    */
    return ok;
}

/////////////////////////////////////////////////////////////////////////////
// BrowseFilePanel

class BrowseFilePanel : public wxPanel
{
    typedef wxPanel base;
    wxDECLARE_DYNAMIC_CLASS(BrowseFilePanel);
public:
    bool Create(wxWindow* parent, wxFileName* fileName)
    {
        bool ok = wxXmlResource::Get()->LoadPanel(this, parent, wxT("browse_file_panel"));
        if (ok)
            XRCCTRL(*this, "filename", wxTextCtrl)->SetValidator(DatabaseValidator(fileName));
        return ok;
    }
    virtual bool TransferDataFromWindow() wxOVERRIDE;
    wxWindow* GetModalParent() const { return GetParent(); }
protected:
    void OnBrowse(wxCommandEvent&);
    wxDECLARE_EVENT_TABLE();
};

wxIMPLEMENT_DYNAMIC_CLASS(BrowseFilePanel, wxPanel);

wxBEGIN_EVENT_TABLE(BrowseFilePanel, wxPanel)
    EVT_BUTTON(XRCID("browse"), BrowseFilePanel::OnBrowse)
wxEND_EVENT_TABLE();

bool BrowseFilePanel::TransferDataFromWindow()
{
    bool ok = base::TransferDataFromWindow();
    if (ok)
    {
        wxTextCtrl* edit = XRCCTRL(*this, "filename", wxTextCtrl);
        wxFileName fileName = edit->GetValue();

        if (fileName.FileExists())
            ok = (wxOK == wxMessageBox(_("File exists. Overwrite ?"), wxMessageBoxCaptionStr, wxOK | wxCANCEL | wxICON_QUESTION, GetModalParent()));
    }
    return ok;
}

void BrowseFilePanel::OnBrowse(wxCommandEvent&)
{
    wxTextCtrl* edit = XRCCTRL(*this, "filename", wxTextCtrl);
    wxFileName fileName = edit->GetValue();
    wxArrayString extensions;

    extensions.push_back(wxString::Format(_("dBASE Files (%s)|*%c%s"), wxDBase::FileExt, wxFILE_SEP_EXT, wxDBase::FileExt));
    extensions.push_back(wxString::Format(_("All Files (%s)|%s"), wxT("*"), wxALL_FILES_PATTERN));
    if (wxSaveFileSelector(GetModalParent(), &fileName, extensions))
        edit->SetValue(fileName.GetFullPath());
}

/////////////////////////////////////////////////////////////////////////////
// NewDatabaseDialog

class NewDatabaseDialog : public wxDialog
{
    typedef wxDialog base;
public:
    bool Create(wxWindow* parent, const wxString& caption)
    {
        bool ok = base::Create(parent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
        if (ok)
        {
            wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

            BrowseFilePanel* panelBrowse = new BrowseFilePanel();
            if (panelBrowse->Create(this, &Data.FileName))
            {
                topSizer->Add(panelBrowse, 0, wxEXPAND);
                m_panelBrowse = panelBrowse;
            }

            DbfStructPanel* panelStruct = new DbfStructPanel();
            if (panelStruct->Create(this, &Data.vector, &Data.Version))
            {
                topSizer->Add(panelStruct, 1, wxEXPAND);
                m_panelStruct = panelStruct;
            }
            topSizer->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), wxSizerFlags().Expand().Border(/*wxTOP | wxBOTTOM*/));
            SetSizerAndFit(topSizer);
            CenterOnParent();
            GetSizer()->SetSizeHints(this);
            SetExtraStyle(GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY);
            SetIcon(wxArtProvider::GetIcon(wxART_NEW));
        }
        return ok;
    }
    NewDatabaseParm Data;

    BrowseFilePanel* m_panelBrowse;
    DbfStructPanel* m_panelStruct;

protected:
    void OnUpdateNeedData(wxUpdateUIEvent&);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(NewDatabaseDialog, wxDialog)
    EVT_UPDATE_UI(wxID_OK, NewDatabaseDialog::OnUpdateNeedData)
wxEND_EVENT_TABLE();

void NewDatabaseDialog::OnUpdateNeedData(wxUpdateUIEvent& event)
{
    wxListView* list = XRCCTRL(*m_panelStruct, "list", StructListView);
    wxTextCtrl* edit = XRCCTRL(*m_panelBrowse, "filename", wxTextCtrl);
    event.Enable(list->GetItemCount() && !edit->IsEmpty());
}

bool DoModal_NewDatabase(wxWindow* parent, const wxString& caption, NewDatabaseParm* parm)
{
    NewDatabaseDialog dlg;
    dlg.Data = *parm;
    bool ok = dlg.Create(parent, caption);
    if (ok)
    {
        ok = (wxID_OK == dlg.ShowModal());
        if (ok)
            *parm = dlg.Data;
        /*
        if (ok && fileName->IsOk() && !db->IsOpen())
        {
           CreateParm parm;
           parm.vector = dlg.m_vector;
           ok = db->Create(fileName, parm);
        }
        */
    }
    return ok;
}

/////////////////////////////////////////////////////////////////////////////
// DbfFieldPanel

class DbfFieldPanel : public wxPanel
{
    typedef wxPanel base;
    wxDECLARE_CLASS(DbfFieldPanel);
public:
    DbfFieldPanel();

    bool Create(wxWindow* parent, wxWindowID);

    virtual bool TransferDataFromWindow();

protected:
    void OnUpdateLength(wxUpdateUIEvent&);
    void OnUpdateDecimals(wxUpdateUIEvent&);
    wxDECLARE_EVENT_TABLE();

    friend class FieldEditDialog;

public:
    wxString m_name;
    int m_type;
    int m_length;
    int m_decimals;
protected:
    wxTextCtrl* m_edit0;
    wxComboBox* m_edit1;
    wxTextCtrl* m_edit2;
    wxTextCtrl* m_edit3;
};

wxIMPLEMENT_CLASS(DbfFieldPanel, wxPanel);

wxBEGIN_EVENT_TABLE(DbfFieldPanel, wxPanel)
    EVT_UPDATE_UI(XRCID("edit2"), DbfFieldPanel::OnUpdateLength)
    EVT_UPDATE_UI(XRCID("edit3"), DbfFieldPanel::OnUpdateDecimals)
wxEND_EVENT_TABLE();

void DbfFieldPanel::OnUpdateLength(wxUpdateUIEvent& event)
{
    const bool boolean = (m_edit1->GetSelection() == DBF_DATA_TYPE_BOOLEAN);
    const bool memo    = (m_edit1->GetSelection() == DBF_DATA_TYPE_MEMO);

    event.Enable(!(boolean || memo));
    if (boolean)
       m_edit2->SetLabel(wxT("1"));
    else if (memo)
       m_edit2->SetLabel(wxT("10"));
}

void DbfFieldPanel::OnUpdateDecimals(wxUpdateUIEvent& event)
{
    const bool flt = (m_edit1->GetSelection() == DBF_DATA_TYPE_FLOAT);

    event.Enable(flt);
    if (!flt)
       m_edit3->SetLabel(wxT("0"));
}

DbfFieldPanel::DbfFieldPanel() : wxPanel()
{
}

bool DbfFieldPanel::Create(wxWindow* parent, wxWindowID id)
{
    bool ok = wxXmlResource::Get()->LoadPanel(this, parent, wxT("field_edit"));

    if (ok)
    {
        SetId(id);
        m_edit0 = XRCCTRL(*this, "edit0", wxTextCtrl);
        m_edit1 = XRCCTRL(*this, "edit1", wxComboBox);
        m_edit2 = XRCCTRL(*this, "edit2", wxTextCtrl);
        m_edit3 = XRCCTRL(*this, "edit3", wxTextCtrl);

    #if (wxVERSION_NUMBER >= 3100)
        m_edit0->ForceUpper();
    #endif

        for (size_t i = 0; i < WXSIZEOF(MOD_aszType); i++)
        {
             m_edit1->Append(MOD_aszType[i], (void*)i);
            //m_combo->GetClientData()
        }
        m_edit0->SetValidator(wxGenericValidator(&m_name    ));
        m_edit1->SetValidator(wxGenericValidator(&m_type    ));
        m_edit2->SetValidator(wxGenericValidator(&m_length  ));
        m_edit3->SetValidator(wxGenericValidator(&m_decimals));
    }
    return ok;
}

bool DbfFieldPanel::TransferDataFromWindow()
{
    bool ok = base::TransferDataFromWindow();

    if (ok)
    {
        m_name.Truncate(DBF_DBASE3_FIELDNAMELENGTH);
        m_name.MakeUpper();
    }
    return ok;
}

/////////////////////////////////////////////////////////////////////////////
// FieldEditDialog

class FieldEditDialog : public wxDialog
{
    typedef wxDialog base;
public:
    bool Create(wxWindow* parent, const wxString& caption, const DBF_FIELD_INFO& info)
    {
        bool ok = base::Create(parent, wxID_ANY, caption.empty() ? wxString(_("Field edit")) : caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
        if (ok)
        {
            DbfFieldPanel* panel = new DbfFieldPanel();
            ok = panel->Create(this, XRCID("panel"));
            if (ok)
            {
                wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
                topSizer->Add(panel, 1, wxEXPAND);
                topSizer->Add(CreateStdDialogButtonSizer(wxOK | wxCANCEL), wxSizerFlags().Expand().Border());
                SetSizerAndFit(topSizer);
                CenterOnParent();
                GetSizer()->SetSizeHints(this);
                SetExtraStyle(GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY);
                SetIcon(wxArtProvider::GetIcon(wxART_APP));
                m_info = info;
                panel->m_name = wxConvertMB2WX(m_info.name);
                panel->m_type = m_info.type;
                panel->m_length = (int)m_info.length;
                panel->m_decimals = m_info.decimals;
            }
        }
        return ok;
    }
    DBF_FIELD_INFO m_info;

    virtual bool TransferDataFromWindow();
protected:
    void OnUpdateNeedData(wxUpdateUIEvent&);
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(FieldEditDialog, wxDialog)
    EVT_UPDATE_UI(wxID_OK, FieldEditDialog::OnUpdateNeedData)
wxEND_EVENT_TABLE();

bool FieldEditDialog::TransferDataFromWindow()
{
    bool ok = base::TransferDataFromWindow();

    if (ok)
    {
        DbfFieldPanel* panel = XRCCTRL(*this, "panel", DbfFieldPanel);

        strncpy(m_info.name, panel->m_name.mb_str(), WXSIZEOF(m_info.name));
        m_info.type     = (dbf_data_type)panel->m_type;
        m_info.length   = panel->m_length;
        m_info.decimals = panel->m_decimals;
    }
    return ok;
}


void FieldEditDialog::OnUpdateNeedData(wxUpdateUIEvent& event)
{
    DbfFieldPanel* panel = XRCCTRL(*this, "panel", DbfFieldPanel);

    bool enable = !(   panel->m_edit0->GetValue().empty()
                   || (panel->m_edit1->GetSelection() == wxNOT_FOUND)
                   || panel->m_edit2->GetValue().empty()
                   || panel->m_edit3->GetValue().empty());

    event.Enable(enable);
}

bool DoModal_FieldEdit(wxWindow* parent, DBF_FIELD_INFO* info, const wxString& caption)
{
    FieldEditDialog dlg;
    bool ok = dlg.Create(parent, caption, *info);
    if (ok)
    {
        ok = (wxID_OK == dlg.ShowModal());
        if (ok)
            *info = dlg.m_info;
   }
   return ok;
}

/////////////////////////////////////////////////////////////////////////////
// WindowsPanel

class WindowsPanel : public wxPanel
{
    typedef wxPanel base;
public:
    WindowsPanel();

    bool Create(wxWindow* parent, const wxDocVector&);

    wxDocument* GetDocument(int item)
    {
        return wxStaticCast(m_listBox->GetClientData(item), wxDocument);
    }
    int GetSelection() const
    {
        return m_selection;
    }
protected:
    void OnClose(wxCommandEvent&);
    void OnActivate(wxCommandEvent&);
    void OnUpdateNeedSel(wxUpdateUIEvent&);
    void OnDblClick(wxCommandEvent&);
    wxDECLARE_EVENT_TABLE();

protected:
    wxListBox* m_listBox;
    int m_selection;
};

wxBEGIN_EVENT_TABLE(WindowsPanel, wxPanel)
    EVT_BUTTON(wxID_CLOSE, WindowsPanel::OnClose)
    EVT_BUTTON(XRCID("activate"), WindowsPanel::OnActivate)
    EVT_UPDATE_UI(wxID_CLOSE, WindowsPanel::OnUpdateNeedSel)
    EVT_UPDATE_UI(XRCID("activate"), WindowsPanel::OnUpdateNeedSel)
    EVT_LISTBOX_DCLICK(wxID_ANY, WindowsPanel::OnDblClick)
wxEND_EVENT_TABLE()

WindowsPanel::WindowsPanel() : wxPanel(), m_listBox(NULL), m_selection(wxNOT_FOUND)
{
}

bool WindowsPanel::Create(wxWindow* parent, const wxDocVector& docs)
{
    bool ok = wxXmlResource::Get()->LoadPanel(this, parent, wxT("windows"));

    if (ok)
    {
        m_listBox = XRCCTRL(*this, "list", wxListBox);

        for (wxDocVector::const_iterator it = docs.begin(); it != docs.end(); it++)
        {
            wxDocument* doc = *it;
            wxDocManager* docManager = doc->GetDocumentManager();
            wxString text = doc->GetFilename();

            if (text.empty())
                text = doc->GetTitle();
            int index = m_listBox->Append(text, doc);

            if (doc == docManager->GetCurrentDocument())
                m_listBox->SetSelection(index);
        }
    }
    return ok;
}

void WindowsPanel::OnUpdateNeedSel(wxUpdateUIEvent& event)
{
    wxArrayInt selections;

    event.Enable(0 != m_listBox->GetSelections(selections));
}

void WindowsPanel::OnClose(wxCommandEvent&)
{
    wxArrayInt selections;

    m_listBox->GetSelections(selections);
    for (wxArrayInt::const_reverse_iterator it = selections.rbegin(); it != selections.rend(); it++)
    {
        int index = *it;
        wxDocument* doc = GetDocument(index);

        if (doc->GetDocumentManager()->CloseDocument(doc))
            m_listBox->Delete(index);
    }
}

void WindowsPanel::OnActivate(wxCommandEvent&)
{
    wxArrayInt selections;

    m_listBox->GetSelections(selections);
    m_selection = selections[0];
    wxStaticCast(GetParent(), wxDialog)->EndModal(wxID_OK);
}

void WindowsPanel::OnDblClick(wxCommandEvent& event)
{
    switch (event.GetSelection())
    {
        case wxNOT_FOUND:
            event.Skip(); break;
        default:
            m_selection = event.GetSelection();
            wxStaticCast(GetParent(), wxDialog)->EndModal(wxID_OK);
            break;
    }
}

class WindowsDialog : public wxDialog
{
    typedef wxDialog base;
public:
    WindowsDialog() : wxDialog(), m_panel(NULL) {}

    bool Create(wxWindow* parent, const wxDocVector& docs, const wxString& caption)
    {
        bool ok = base::Create(parent, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
        if (ok)
        {
            WindowsPanel* panel = new WindowsPanel();
            ok = panel->Create(this, docs);
            if (ok)
            {
                m_panel = panel;
                wxStdDialogButtonSizer* buttonpane = CreateStdDialogButtonSizer(wxOK);
                buttonpane->GetAffirmativeButton()->SetId(wxID_CANCEL);
                buttonpane->SetAffirmativeButton(NULL);

                wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
                topSizer->Add(panel, 1, wxEXPAND | wxRIGHT, 5);
                topSizer->Add(buttonpane, wxSizerFlags().Align(wxEXPAND).Border());
                SetSizerAndFit(topSizer);
                CenterOnParent();
                GetSizer()->SetSizeHints(this);
                SetExtraStyle(GetExtraStyle() | wxWS_EX_VALIDATE_RECURSIVELY);
                SetIcon(wxArtProvider::GetIcon(wxART_APP));
            }
        }
        return ok;
    }
    WindowsPanel* GetPanel() const { return m_panel; }
    wxDocument* GetSelection() const
    {
        return GetPanel()->GetDocument(GetPanel()->GetSelection());
    }
private:
    WindowsPanel* m_panel;
};

void DoModal_Windows(wxWindow* parent, const wxDocVector& docs, const wxString& caption)
{
    WindowsDialog dlg;
    if (dlg.Create(parent, docs, caption))
    {
        if (wxID_OK == dlg.ShowModal())
            wxTrunkDocView::ActivateDocument(dlg.GetSelection());
    }
}

/////////////////////////////////////////////////////////////////////////////
