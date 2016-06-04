// wxgui.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include "wx/ext/gui.h"
#include "wx/ext/docview.h"

wxIMPLEMENT_CLASS(wxViewEx, wxView);
wxIMPLEMENT_DYNAMIC_CLASS(wxTrunkListView, wxListView);

static wxString GetDefaultPath(const wxFileName& fileName)
{
    wxString str = fileName.GetPath();
    if (str.empty())
        str = wxGetCwd();
    return str;
}

int wxLoadFileSelector(wxWindow* parent, wxFileName* fileName, const wxArrayString& extensions)
{
    const wxString filter = wxJoin(extensions, wxT('|'), 0);
    wxString defaultPath = GetDefaultPath(*fileName);
    wxString caption = wxGetStockLabelEx(wxID_OPEN, wxSTOCK_PLAINTEXT);
    wxFileDialog fileDialog(parent, caption, defaultPath, fileName->GetFullName(), filter, wxFD_DEFAULT_STYLE_OPEN | wxFD_CHANGE_DIR);

    if (fileDialog.ShowModal() != wxID_OK)
        return wxNOT_FOUND;
    fileName->Assign(fileDialog.GetPath());
    return fileDialog.GetFilterIndex();
}

int wxSaveFileSelector(wxWindow* parent, wxFileName* fileName, const wxArrayString& extensions)
{
    const wxString filter = wxJoin(extensions, wxT('|'), 0);
    const wxString ext = wxString(wxT(".")) + fileName->GetExt();
    wxString defaultPath = GetDefaultPath(*fileName);
    wxString caption = wxGetStockLabelEx(wxID_SAVE, wxSTOCK_PLAINTEXT);
    wxFileDialog fileDialog(parent, caption, defaultPath, fileName->GetFullName(), filter, wxFD_DEFAULT_STYLE_SAVE | wxFD_CHANGE_DIR);

    if (!fileName->GetExt().empty())
        for (wxArrayString::const_iterator it = extensions.begin(); it != extensions.end(); it++)
            if (it->EndsWith(ext))
            {
                int index = (int)(it - extensions.begin());
                fileDialog.SetFilterIndex(index);
                break;
            }

    if (fileDialog.ShowModal() != wxID_OK)
        return wxNOT_FOUND;
    fileName->Assign(fileDialog.GetPath());
    return fileDialog.GetFilterIndex();
}

bool wxWindow_Toggle(wxWindow* wnd)
{
   wxWindow* parent = wnd->GetParent();
   const bool show = !wnd->IsShown();

   wnd->Show(show);
   if (wxIS_KIND_OF(parent, wxFrame))
      wxStaticCast(parent, wxFrame)->SendSizeEvent(); // needed when mdi
   else
      parent->Layout(); // needed when non-mdi
   return show;
}

void wxFrame_ClonePosition(wxFrame* wnd, wxWindow* otherwindow /*= NULL*/)
{
    otherwindow = otherwindow ? wxGetTopLevelParent(otherwindow) : wxTheApp->GetTopWindow();
    wxFrame* topframe = wxStaticCast(otherwindow, wxFrame);

    if (topframe->IsMaximized())
        wnd->Maximize();
    else if (topframe->IsFullScreen())
        wnd->Maximize();
    else
    {
        wxRect rect = topframe->GetScreenRect();

        wnd->SetSize(rect);
    }
}

void wxFrame_ToggleFullScreen(wxFrame* wnd, long style)
{
   wnd->ShowFullScreen(!wnd->IsFullScreen(), style);
}

void wxFrame_OnUpdateFullScreen(wxFrame* wnd, wxUpdateUIEvent& event)
{
   event.Check(wnd->IsFullScreen());
}

#if wxUSE_ACCEL

/*static*/
wxAcceleratorEntry wxAcceleratorHelper::GetStockAccelerator(wxWindowID id)
{
    wxAcceleratorEntry ret;

    #define STOCKITEM(stockid, flags, keycode)      \
        case stockid:                               \
            ret.Set(flags, keycode, stockid);       \
            break;

    switch (id)
    {
    #if (wxVERSION_NUMBER < 2903)
        STOCKITEM(wxID_PRINT,                wxACCEL_CTRL,'P')
        STOCKITEM(wxID_UNDO,                 wxACCEL_CTRL,'Z')
    #endif
        STOCKITEM(wxID_PREVIEW,              wxACCEL_CTRL | wxACCEL_SHIFT,'P')
        STOCKITEM(wxID_SAVEAS,               wxACCEL_CTRL | wxACCEL_SHIFT,'S')
        STOCKITEM(wxID_SELECTALL,            wxACCEL_CTRL,'A')
        STOCKITEM(wxID_REDO,                 wxACCEL_CTRL,'Y')
        //STOCKITEM(wxID_PREFERENCES,          wxACCEL_CTRL,'T')
        STOCKITEM(wxID_ICONIZE_FRAME,        wxACCEL_ALT,WXK_FULLSCREEN)
        STOCKITEM(wxID_REFRESH,              wxACCEL_NORMAL, WXK_F5)
        STOCKITEM(wxID_PROPERTIES,           wxACCEL_ALT,WXK_RETURN)
        STOCKITEM(wxID_BACKWARD,             wxACCEL_ALT , WXK_LEFT)
        STOCKITEM(wxID_FORWARD,              wxACCEL_ALT , WXK_RIGHT)
        STOCKITEM(wxID_HELP,                 wxACCEL_NORMAL, WXK_HELP_F1)
        STOCKITEM(wxID_REPLACE,              wxACCEL_CTRL,'H')
        STOCKITEM(wxID_EXIT,                 wxACCEL_CTRL, 'Q')
        STOCKITEM(wxID_CLOSE,                wxACCEL_CTRL, 'W')
        STOCKITEM(wxID_CLEAR,                wxACCEL_NORMAL, WXK_DELETE)
        STOCKITEM(wxID_ABOUT,                wxACCEL_SHIFT, WXK_HELP_F1)
        default:
            ret = wxGetStockAccelerator(id);
            break;
    }

    #undef STOCKITEM


#if (wxVERSION_NUMBER >= 2902)
    wxASSERT(ret.IsOk());
#else
    // trac.wxwidgets.org/ticket/12444
    // trac.wxwidgets.org/ticket/12445
#endif
    return ret;
}

#endif // wxUSE_ACCEL

wxString wxMenuItem_GetText(const wxMenuItem* item)
{
   wxString str = item->GetItemLabel();
#ifdef __WXGTK__
   str.Replace(wxString('_'), wxString('&'));
#endif
   return str;
}

#define ACCELSTR_SEP "   "

/*static*/
bool wxAcceleratorHelper::SetAccelText(wxMenuItem* item, const wxString& accel, bool append)
{
   wxString str = wxMenuItem_GetText(item);
   wxString ch_sep = wxT("\t");
   const int sep = str.Find(ch_sep);

   if (wxNOT_FOUND == sep)
   {
   }
   else if (append)
      ch_sep = wxT(ACCELSTR_SEP);
   else
      str.Truncate(sep);
   item->SetItemLabel(wxString::Format(wxT("%s%s%s"),
      str.wx_str(),
      ch_sep.wx_str(),
      accel.wx_str()));
   return true;
}

static wxString wxGetAccelText(int flags, wxKeyCode keyCode)
{
    // wxAcceleratorEntry.ToString() produces silly text
#if (wxVERSION_NUMBER >= 2901)
    const wxChar sep = '+'; // the new wx default
#else
    const wxChar sep = '-'; // the old annoying wx default
#endif
    wxArrayString as;
    if (flags & wxACCEL_CTRL)
        as.push_back(_("Ctrl"));
    if (flags & wxACCEL_ALT)
        as.push_back(_("Alt"));
    if (flags & wxACCEL_SHIFT)
        as.push_back(_("Shift"));
    switch (keyCode)
    {
        case WXK_INSERT         : as.push_back(_("Insert" )); break;
        case WXK_PAGEUP         : as.push_back(_("PgUp"   )); break;
        case WXK_PAGEDOWN       : as.push_back(_("PgDn"   )); break;
        case WXK_HOME           : as.push_back(_("Home"   )); break;
        case WXK_END            : as.push_back(_("End"    )); break;
        case WXK_RETURN         : as.push_back(_("Return" )); break;
        case WXK_DELETE         : as.push_back(_("Del"    )); break;
        case WXK_SPACE          : as.push_back(_("Space"  )); break;
        case WXK_NUMPAD_ADD     : as.push_back(_("Num+"   )); break;
        case WXK_NUMPAD_SUBTRACT: as.push_back(_("Num-"   )); break;
        case WXK_BACK           : as.push_back(_("Back"   )); break;
        default:
            if ( (keyCode >= WXK_F1) && (keyCode <= WXK_F24) )
                as.push_back(wxString::Format(wxT("F%d"), keyCode - WXK_F1 + 1));
            else
            {
                wxASSERT(keyCode >= ' ');
                as.push_back((wxChar)keyCode);
            }
            break;
    }
    return wxJoin(as, sep, 0);
}

static wxString wxGetAccelText(const wxAcceleratorEntry& accel)
{
   return wxGetAccelText(accel.GetFlags(), (wxKeyCode)accel.GetKeyCode());
}

/*static*/
void wxAcceleratorHelper::SetAccelText(wxMenuBar* menu, const wxAcceleratorVector& array)
{
    for (wxAcceleratorVector::const_iterator it = array.begin(); it != array.end(); it++)
    {
        const wxAcceleratorEntry& entry = *it;
        wxMenuItem* item = menu->FindItem(entry.GetCommand());

        if (item)
            wxAcceleratorHelper::SetAccelText(item, wxGetAccelText(entry), true);
    }
}

wxString wxToolBarTool_MakeShortHelp(const wxString& rstr, const wxAcceleratorVector& accel, int id)
{
   wxString str = rstr;

   if ((!accel.empty()) && (!str.empty()))
   {
      wxString strAccel;

      for (wxAcceleratorVector::const_iterator it = accel.begin(); it != accel.end(); it++)
      {
         const wxAcceleratorEntry& element = *it;

         if (element.GetCommand() == id)
         {
            if (!strAccel.empty())
                strAccel+=wxT(ACCELSTR_SEP);
            strAccel+=wxGetAccelText(element);
         }
      }
      if (!strAccel.empty())
         str+=wxString::Format(wxT(" (%s)"), strAccel.wx_str());
   }
   return str;
}

/////////////////////////////////////////////////////////////////////////////
// wxRecentFileList

wxRecentFileList::wxRecentFileList(size_t maxFiles, wxWindowID idBase)
{
    m_fileHistory = m_DeleteMe = new wxFileHistory(maxFiles, idBase);
}

wxRecentFileList::wxRecentFileList(wxFileHistory* fileHistory) : m_fileHistory(fileHistory), m_DeleteMe(NULL)
{
}

wxRecentFileList::~wxRecentFileList()
{
    delete m_DeleteMe;
}

void wxRecentFileList::Attach(wxMenuBar* menubar)
{
    wxMenu* submenu;
    wxMenuItem* item = menubar->FindItem(m_fileHistory->GetBaseId(), &submenu);

    submenu->Delete(item);
    m_fileHistory->UseMenu(submenu);
    m_fileHistory->AddFilesToMenu(submenu);
}

bool wxRecentFileList::Detach(wxMenuBar* menubar)
{
    const wxList& list = m_fileHistory->GetMenus();

    for (wxList::const_iterator it = list.begin();
         it != list.end();
         it++)
    {
        wxMenu* menu = wxStaticCast(*it, wxMenu);

        if (menu->GetMenuBar() == menubar)
        {
            m_fileHistory->RemoveMenu(menu);
            return true;
        }
    }
    return false;
}

void wxRecentFileList::Attach(wxFrame* frame)
{
    Attach(frame->GetMenuBar());
}

bool wxRecentFileList::Detach(wxFrame* frame)
{
    return Detach(frame->GetMenuBar());
}

void wxRecentFileList::Load(wxConfigBase* config, const wxString& configPath)
{
    if (NULL == config)
        config = wxConfigBase::Get();
    config->SetPath(configPath.empty() ? wxT("MRU") : configPath);
    m_fileHistory->Load(*config);
    config->SetPath(wxT("/"));
}

void wxRecentFileList::Save(wxConfigBase* config, const wxString& configPath)
{
    if (NULL == config)
        config = wxConfigBase::Get();
    config->SetPath(configPath.empty() ? wxT("MRU") : configPath);
    m_fileHistory->Save(*config);
    config->SetPath(wxT("/"));
}

int wxRecentFileList::IndexFromID(wxWindowID id) const
{
    const wxFileHistory* impl = GetImplementation();

    return (   (id >= impl->GetBaseId())
            && (id < (impl->GetBaseId() + impl->GetMaxFiles()))
           )
            ? id - impl->GetBaseId()
            : wxNOT_FOUND;
}

void wxRecentFileList::AddFileToHistory(const wxString& file)
{
    GetImplementation()->AddFileToHistory(file);
}

bool wxRecentFileList::GetFile(size_t index, wxString* str) const
{
    const wxFileHistory* impl = GetImplementation();
    bool ok = (index < impl->GetCount());

    if (ok && str)
        *str = impl->GetHistoryFile(index);
    return ok;
}

/////////////////////////////////////////////////////////////////////////////
// MDIWindowMenuEvtHandler

MDIWindowMenuEvtHandler::MDIWindowMenuEvtHandler(wxMDIParentFrame* wnd) : wxEvtHandler(), m_target_wnd(NULL)
{
    wxMenu* windowMenu = wnd->GetWindowMenu();

    if (windowMenu)
    {
        windowMenu->AppendSeparator();
        windowMenu->Append(wxID_CLOSE, _("Cl&ose"), _("Close window"));
        windowMenu->Append(wxID_CLOSE_ALL, _("Close A&ll"), _("Close all open windows"));
        wnd->PushEventHandler(this);
        m_target_wnd = wnd;
    }
}

MDIWindowMenuEvtHandler::~MDIWindowMenuEvtHandler()
{
    if (m_target_wnd)
        m_target_wnd->RemoveEventHandler(this);
}

wxBEGIN_EVENT_TABLE(MDIWindowMenuEvtHandler, wxEvtHandler)
    EVT_MENU(wxID_CLOSE_ALL, MDIWindowMenuEvtHandler::OnCloseAll)
    EVT_UPDATE_UI(wxID_CLOSE, MDIWindowMenuEvtHandler::OnUpdateNeedWindow)
    EVT_UPDATE_UI(wxID_CLOSE_ALL, MDIWindowMenuEvtHandler::OnUpdateNeedWindow)
wxEND_EVENT_TABLE()

void MDIWindowMenuEvtHandler::OnUpdateNeedWindow(wxUpdateUIEvent& event)
{
    event.Enable(m_target_wnd->GetActiveChild() != NULL);
}

void MDIWindowMenuEvtHandler::OnCloseAll(wxCommandEvent&)
{
    const wxWindowList list = m_target_wnd->GetChildren(); // make a copy of the window list

    for (wxWindowList::const_iterator i = list.begin();
         i != list.end();
         i++)
    {
        if (wxDynamicCast(*i, wxMDIChildFrame))
        {
            if (!(*i)->Close())
            {
                // Close was vetoed
                break;
            }
        }
    }
}

wxStdDialogButtonSizer* wxCreateStdDialogButtonSizer(wxWindow* parent, long flags)
{
    wxStdDialogButtonSizer* buttonpane = new wxStdDialogButtonSizer();

    if ((flags & wxOK) && (flags & wxCANCEL))
    {
        buttonpane->AddButton(new wxButton(parent, wxID_OK));
        buttonpane->AddButton(new wxButton(parent, wxID_CANCEL));
        buttonpane->GetAffirmativeButton()->SetDefault();
    }
    else if (flags & wxOK)
    {
        buttonpane->AddButton(new wxButton(parent, wxID_OK));
        buttonpane->GetAffirmativeButton()->SetDefault();
    }
    else if (flags & wxCANCEL)
    {
        buttonpane->AddButton(new wxButton(parent, wxID_CANCEL, _("Cl&ose")));
        buttonpane->GetCancelButton()->SetDefault();
    }
    if (flags & wxAPPLY)
        buttonpane->AddButton(new wxButton(parent, wxID_APPLY, _("&Apply")));
    buttonpane->Realize();

    //parent->GetSizer()->Add(new wxStaticLine(parent), 0, wxEXPAND | wxALL, 5); // separator
    parent->GetSizer()->Add(buttonpane, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

    return buttonpane;
}

bool wxGetSingleChoiceIndex(int* index, const wxString& message,
                            const wxString& caption,
                            const wxArrayString& choices,
                            wxWindow* parent)
{
    wxSingleChoiceDialog dialog(parent, message, caption, choices);
    wxIcon icon = wxArtProvider::GetIcon(wxART_APP);
    if (icon.IsOk())
        dialog.SetIcon(icon);
    dialog.SetSelection(*index);

    if (dialog.ShowModal() != wxID_OK)
        return false;
    *index = dialog.GetSelection();
    return true;
}

#if (wxVERSION_NUMBER < 2900)
static unsigned char wxColourBase_AlphaBlend(unsigned char fg, unsigned char bg, double alpha)
{
    double result = bg + (alpha * (fg - bg));
    result = wxMax(result,   0.0);
    result = wxMin(result, 255.0);
    return (unsigned char)result;
}

static void wxColourBase_ChangeLightness(unsigned char* r, unsigned char* g, unsigned char* b, int ialpha)
{
    if (ialpha == 100) return;

    // ialpha is 0..200 where 0 is completely black
    // and 200 is completely white and 100 is the same
    // convert that to normal alpha 0.0 - 1.0
    ialpha = wxMax(ialpha,   0);
    ialpha = wxMin(ialpha, 200);
    double alpha = ((double)(ialpha - 100.0))/100.0;

    unsigned char bg;
    if (ialpha > 100)
    {
        // blend with white
        bg = 255;
        alpha = 1.0 - alpha;  // 0 = transparent fg; 1 = opaque fg
    }
    else
    {
        // blend with black
        bg = 0;
        alpha = 1.0 + alpha;  // 0 = transparent fg; 1 = opaque fg
    }

    *r = wxColourBase_AlphaBlend(*r, bg, alpha);
    *g = wxColourBase_AlphaBlend(*g, bg, alpha);
    *b = wxColourBase_AlphaBlend(*b, bg, alpha);
}

static wxColour wxColourBase_ChangeLightness(const wxColour& colour, int ialpha)
{
    wxByte r = colour.Red();
    wxByte g = colour.Green();
    wxByte b = colour.Blue();
    wxColourBase_ChangeLightness(&r, &g, &b, ialpha);
    return wxColour(r,g,b);
}
#endif

#if (wxVERSION_NUMBER < 2905)
void wxTrunkListView::EnableAlternateRowColours(bool enable)
{
    if (enable)
    {
        // Determine the alternate rows colour automatically from the
        // background colour.
        const wxColour bgColour = GetBackgroundColour();

        // Depending on the background, alternate row color
        // will be 3% more dark or 50% brighter.
    #if (wxVERSION_NUMBER >= 2900)
        int alpha = (bgColour.GetRGB() > 0x808080) ? 97 : 150;
        m_alternateRowColour.SetBackgroundColour(bgColour.ChangeLightness(alpha));
    #else
        int alpha = ((bgColour.Red() | (bgColour.Green() << 8) | (bgColour.Blue() << 16)) > 0x808080) ? 97 : 150;
        m_alternateRowColour.SetBackgroundColour(wxColourBase_ChangeLightness(bgColour, alpha));
    #endif
    }
    else
    {
        m_alternateRowColour.SetBackgroundColour(wxColour());
    }
}

wxListItemAttr* wxTrunkListView::OnGetItemAttr(long row) const
{
    return (m_alternateRowColour.GetBackgroundColour().IsOk() && (row % 2))
        ? wxConstCast(&m_alternateRowColour, wxListItemAttr)
        : base::OnGetItemAttr(row);
}
#endif

#if (wxVERSION_NUMBER < 2900)
bool wxTrunkListView::GetSubItemRect( long row, long col, wxRect& rect, int code) const
{
    bool ok = base::GetItemRect(row, rect, code);

    if (ok)
    {
      for (int i = 0/*, count = ctrl.GetColumnCount()*/; ; i++)
      {
         const int width = GetColumnWidth(i);

         if (i < col)
            rect.x+=width;
         else if (i == col)
         {
            rect.width = width;
            break;
         }
         else
         {
            ok = false;
            break;
         }
      }
    }
    return ok;
}
#endif

long wxTrunkListView::HitTest(const wxPoint& point, int* flags, long* col) const
{
    int rFlags;
    const long row = base::HitTest(point, rFlags);

    if (col && (row != wxNOT_FOUND))
    {
      const int offset = GetScrollPos(wxHORIZONTAL);
      int pos = 0;

      *col = -1;
      for (int i = 0, count = GetColumnCount(); i < count; i++)
      {
         pos += GetColumnWidth(i);
         if ((point.x + offset) < pos)
         {
            *col = i;
            break;
         }
      }
    }
    if (flags) *flags = rFlags;
    return row;
}

bool wxTrunkListView::EndEditLabel(bool cancel)
{
#ifdef __WXMSW__
    #if (wxVERSION_NUMBER >= 2901)
        return base::EndEditLabel(cancel);
    #else
      HWND hwnd = ListView_GetEditControl((HWND)GetHWND());
      bool ok = (hwnd != NULL);
      if (ok)
      {
      #ifdef ListView_CancelEditLabel
         if (cancel && (wxApp::GetComCtl32Version() >= 600))
         {
            ListView_CancelEditLabel((HWND)GetHWND());
            return ok;
         }
      #endif
         if (::IsWindowVisible(hwnd))
            ::SendMessage(hwnd, WM_KEYDOWN, cancel ? VK_ESCAPE : VK_RETURN, 0);
         else
            ::SendMessage(hwnd, WM_CLOSE, 0, 0);
      }
      return ok;
    #endif
#else
    return false;
#endif
}

bool wxShowTextDialog(wxWindow* parent, wxString* text, const wxString& caption, int te_style, const wxSize& size)
{
    long style_editable = wxTextEntryDialogStyle;
    long style_readonly = wxCANCEL | wxWS_EX_VALIDATE_RECURSIVELY;
    long style = ((te_style & wxTE_READONLY) ? style_readonly : style_editable) | (te_style & wxTE_MULTILINE);

    class MyTextEntryDialog : public wxTextEntryDialog
    {
    public:
        MyTextEntryDialog(wxWindow *parent,
                          const wxString& message,
                          const wxString& caption,
                          const wxString& value,
                          long style)
            : wxTextEntryDialog(parent, message, caption, value, style) {}
        void SetReadOnly()
        {
            m_textctrl->SetEditable(false);
        }
    } dialog(parent, wxEmptyString, caption.empty() ? wxGetTextFromUserPromptStr : caption, *text, style);
    if (te_style & wxTE_READONLY)
    {
        dialog.SetReadOnly();
        dialog.FindWindow(wxID_CANCEL)->SetLabel(wxGetStockLabel(wxID_CLOSE));
    }
    wxIcon icon = wxArtProvider::GetIcon(wxART_APP, wxART_FRAME_ICON);
    if (icon.IsOk())
        dialog.SetIcon(icon);
    if ( (style & wxTE_MULTILINE) && (size == wxDefaultSize) )
        dialog.SetSize(600, 500);
    else
        dialog.SetSize(size);
    dialog.Center();
    bool ok = (wxID_OK == dialog.ShowModal());
    if (ok)
        *text = dialog.GetValue();
    return ok;
}

void wxFrame_SetInitialPosition(wxFrame* wnd, const wxPoint& pos, const wxSize& size, int margin_pct)
{
   if (size == wxDefaultSize)
   {
      wxRect rect = wxGetClientDisplayRect();
      wxSize size(
         (rect.width  * (100 - margin_pct*2))/100,
         (rect.height * (100 - margin_pct*2))/100);

      wnd->SetSize(size);
   }
   if (pos == wxDefaultPosition)
      wnd->Center();
}

#if (wxVERSION_NUMBER < 2905)
// static
wxDocVector wxTrunkDocView::GetDocumentsVector(const wxDocManager& docManager)
{
    wxDocVector docs;
    const wxList& list = wxConstCast(&docManager, wxDocManager)->GetDocuments();

    for (wxList::const_iterator it = list.begin(); it != list.end(); it++)
        docs.push_back(wxStaticCast(*it, wxDocument));
    return docs;
}
#endif

// static
wxView* wxDocViewHelpers::GetCurrentView(const wxDocument& rdoc)
{
    const wxDocument* doc = &rdoc;
    wxView* view = doc->GetDocumentManager()->GetCurrentView();

    return (view && (view->GetDocument() == doc)) ? view : doc->GetFirstView();
}

// static
void wxDocViewHelpers::GetInfo(const wxDocument& doc, wxArrayString* as)
{
   const wxString fmt = wxT("%s:\t%s");
   wxView* active_view = wxDocViewHelpers::GetCurrentView(doc);
   wxView* view  = active_view ? active_view : doc.GetFirstView();
   wxWindow* frame = view ? view->GetFrame() : NULL;;

   as->push_back(wxString::Format(fmt, wxT("Doc class"), doc.GetClassInfo()->GetClassName()));
   if (view)
      as->push_back(wxString::Format(fmt, wxT("View class"), view->GetClassInfo()->GetClassName()));
   as->push_back(wxString::Format(fmt, wxT("Frame class"), frame ? frame->GetClassInfo()->GetClassName() : wxEmptyString));
   if (frame)
      as->push_back(wxString::Format(fmt, wxT("Frame label"), frame->GetLabel().wx_str()));
   as->push_back(wxString::Format(fmt, wxT("GetFilename"), doc.GetFilename().wx_str()));
   as->push_back(wxString::Format(fmt, wxT("GetTitle"), doc.GetTitle().wx_str()));
   as->push_back(wxString::Format(fmt, wxT("GetUserReadableName"), doc.GetUserReadableName().wx_str()));
   as->push_back(wxString::Format(fmt, wxT("IsModified"), doc.IsModified() ? _("Yes") : _("No")));
   as->push_back(wxString::Format(fmt, wxT("GetDocumentSaved"), doc.GetDocumentSaved() ? _("Yes") : _("No")));
   as->push_back(wxString::Format(fmt, wxT("GetDocumentName"), doc.GetDocumentName().wx_str()));
}

