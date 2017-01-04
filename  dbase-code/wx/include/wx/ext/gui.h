// wx/ext/gui.h
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __WX_EXT_GUI_H__
#define __WX_EXT_GUI_H__

#ifndef __WX_EXT_BASE_H__
#include "wx/ext/base.h"
#endif

class WXDLLIMPEXP_FWD_CORE wxFileHistory;
class WXDLLIMPEXP_FWD_BASE wxConfigBase;
class WXDLLIMPEXP_FWD_CORE wxMenuBar;
class WXDLLIMPEXP_FWD_CORE wxMenuItem;

#define WXK_HELP_F1    WXK_F1
#define WXK_FULLSCREEN WXK_F11

#define wxFD_DEFAULT_STYLE_OPEN (wxFD_OPEN | wxFD_FILE_MUST_EXIST)
#define wxFD_DEFAULT_STYLE_SAVE (wxFD_SAVE | wxFD_OVERWRITE_PROMPT)

class WXDLLIMPEXP_FWD_CORE wxDataObject;
class WXDLLIMPEXP_FWD_CORE wxMDIParentFrame;

extern void wxFrame_ToggleFullScreen(wxFrame*, long style);
extern void wxFrame_OnUpdateFullScreen(wxFrame*, wxUpdateUIEvent&);
extern void wxFrame_ClonePosition(wxFrame*, wxWindow* otherwindow = NULL);
extern bool wxWindow_Toggle(wxWindow*);
extern wxStdDialogButtonSizer* wxCreateStdDialogButtonSizer(wxWindow* parent, long flags);
extern int wxLoadFileSelector(wxWindow* parent, wxFileName*, const wxArrayString& extensions);
extern int wxSaveFileSelector(wxWindow* parent, wxFileName*, const wxArrayString& extensions);
extern bool wxGetSingleChoiceIndex(int* index, const wxString& message,
                                    const wxString& caption,
                                    const wxArrayString& choices,
                                    wxWindow *parent = NULL);

#ifdef _WX_MSGDLG_H_BASE_
extern bool wxShowTextDialog(wxWindow* parent, wxString* text, const wxString& caption = wxMessageBoxCaptionStr, int te_style = 0, const wxSize& size = wxDefaultSize);
inline bool wxShowTextDialog(wxWindow* parent, const wxString& text, const wxString& caption = wxEmptyString, int te_style = 0, const wxSize& size = wxDefaultSize)
{
    wxString temp = text;
    return wxShowTextDialog(parent, &temp, caption, te_style | wxTE_READONLY, size);
}
#endif

#if defined(_WX_EVENT_H_) || defined(_WX_EVENT_H__)
inline void wxPostCommandEvent(wxEvtHandler* dest, wxEventType commandType, int id)
{
    wxCommandEvent event(commandType, id);
    if (dest == NULL)
        dest = wxTheApp->GetTopWindow();
    wxPostEvent(dest, event);
}

inline void wxPostMenuCommand(wxEvtHandler* dest, int id)
{
    wxPostCommandEvent(dest, wxEVT_COMMAND_MENU_SELECTED, id);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// wxRecentFileList
// wxFileHistory is confusing and difficult to use, esp in MDI:
// wrap up the eccentricities

class wxRecentFileList
{
public:
    wxRecentFileList(size_t maxFiles = 9, wxWindowID idBase = wxID_FILE1);
    wxRecentFileList(wxFileHistory*);
    virtual ~wxRecentFileList();

    void Load(wxConfigBase* config = NULL, const wxString& configPath = wxEmptyString);
    void Save(wxConfigBase* config = NULL, const wxString& configPath = wxEmptyString);

    void Attach(wxMenuBar*);
    void Attach(wxFrame*);
    bool Detach(wxMenuBar*);
    bool Detach(wxFrame*);

    wxFileHistory* GetImplementation() const
    {
        return m_fileHistory;
    }

    void AddFileToHistory(const wxString& file);
    void AddFileToHistory(const wxFileName& fileName)
    {
        AddFileToHistory(fileName.GetFullPath());
    }
    bool GetFile(size_t, wxString*) const;
    bool GetFile(size_t index, wxFileName* fileName) const
    {
        wxString str;
        if (!GetFile(index, &str))
            return false;
        if (fileName)
            *fileName = str;
        return true;
    }

    int IndexFromID(wxWindowID) const;
    int IsInRange(wxWindowID id) const
    {
        return wxNOT_FOUND != IndexFromID(id);
    }
private:
    wxFileHistory* m_fileHistory;
    wxFileHistory* m_DeleteMe;
};

extern void wxFrame_SetInitialPosition(wxFrame*,
                    const wxPoint& pos = wxDefaultPosition,
                    const wxSize& size = wxDefaultSize, int margin_pct = 5);

#ifdef _WX_DOCH__
class wxViewEx : public wxView
{
    typedef wxView base;
    wxDECLARE_CLASS(wxViewEx);
public:
    wxViewEx() : wxView(), m_viewWindow(NULL)
    {
    }

    void SetWindow(wxWindow* window) { m_viewWindow = window; } // trac.wxwidgets.org/ticket/13040
    wxWindow* GetWindow() const { return m_viewWindow; }

    virtual void OnDraw(wxDC*)
    {
    }
private:
    wxWindow* m_viewWindow;
};
#endif

/////////////////////////////////////////////////////////////////////////////
// MDIWindowMenuEvtHandler

class MDIWindowMenuEvtHandler : public wxEvtHandler
{
protected:
    wxMDIParentFrame* m_target_wnd;
public:
    MDIWindowMenuEvtHandler(wxMDIParentFrame*);

    virtual ~MDIWindowMenuEvtHandler();
protected:
    void OnClose(wxCommandEvent&);
    void OnCloseAll(wxCommandEvent&);
    void OnUpdateNeedWindow(wxUpdateUIEvent&);
    wxDECLARE_EVENT_TABLE();
};

#ifdef _WX_LISTCTRL_H_BASE_
class wxTrunkListView : public wxListView
{
    typedef wxListView base;
    wxDECLARE_DYNAMIC_CLASS(wxTrunkListView);
public:
#if (wxVERSION_NUMBER < 2905)
    void SetAlternateRowColour(const wxColour& colour) { m_alternateRowColour.SetBackgroundColour(colour); }
    void EnableAlternateRowColours(bool enable = true);
    virtual wxListItemAttr* OnGetItemAttr(long row) const;
    long AppendColumn(const wxString& heading,
                      wxListColumnFormat format = wxLIST_FORMAT_LEFT,
                      int width = -1)
    {
        return InsertColumn(GetColumnCount(), heading, format, width);
    }
#endif

    void SelectAll()
    {
        for (int i = 0; i < GetItemCount(); i++)
            SetItemState(i, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }

    void SelectNone()
    {
        for (int i = 0; i < GetItemCount(); i++)
            SetItemState(i, 0, wxLIST_STATE_SELECTED);
    }

    long GetSelectedRow(wxString* str = NULL) const
    {
        long row = GetFirstSelected();

        if (str && (wxNOT_FOUND != row))
            *str = GetItemText(row);
        return row;
    }

    bool SelectRow(long row, bool focus = true)
    {
        bool ok = (row != wxNOT_FOUND) && (row < GetItemCount());
        if (ok)
        {
            bool on = true;

            SetItemState(row, on ? wxLIST_STATE_SELECTED : 0, wxLIST_STATE_SELECTED);
            if (focus)
            {
                SetItemState(row, wxLIST_STATE_FOCUSED, wxLIST_STATE_FOCUSED);
                EnsureVisible(row);
            }
        }
        return ok;
    }

    bool HasSelection() const
    {
        return (GetFirstSelected() != wxNOT_FOUND);
    }

    int GetSelections( wxArrayInt& sel ) const
    {
        for (long row = GetFirstSelected(); row != wxNOT_FOUND; row = GetNextSelected(row))
            sel.push_back(row);
        return (int)sel.size();
    }

#if (wxVERSION_NUMBER < 2900)
    bool GetSubItemRect( long row, long col, wxRect& rect, int code = wxLIST_RECT_BOUNDS ) const;
#endif
    long HitTest(const wxPoint&, int* flags, long* col) const;
    bool EndEditLabel(bool cancel);

    bool RefreshSubItem(long row, long col, bool eraseBackground = true)
    {
        wxRect rect;
        bool ok = GetSubItemRect(row, col, rect);

        if (ok)
        {
            rect.x+=1, rect.width-=2;
            RefreshRect(rect, eraseBackground);
        }
        return ok;
    }

#if (wxVERSION_NUMBER < 2900)
    wxString GetItemText(long row, long col = 0) const
    {
       wxString str;
       wxListItem info;

       info.m_itemId = row;
       info.m_col = col;
       info.m_mask = wxLIST_MASK_TEXT;
       if (GetItem(info))
          str = info.m_text;
       return str;
    }
#endif
private:
#if (wxVERSION_NUMBER < 2905)
    // user defined color to draw row lines, may be invalid
    wxListItemAttr m_alternateRowColour;
#endif
};
#endif

#if wxUSE_ACCEL
class wxAcceleratorVector : public std::vector<wxAcceleratorEntry> // inline class, not exported
{
public:
    wxAcceleratorTable ToArray() const
    {
        return wxAcceleratorTable((int)size(), &at(0));
    }
};

class wxAcceleratorHelper
{
public:
    static wxAcceleratorEntry GetStockAccelerator(wxWindowID);
    static void SetAccelText(wxMenuBar*, const wxAcceleratorVector&);
    static bool SetAccelText(wxMenuItem*, const wxString& accel, bool append);
};
extern wxString wxToolBarTool_MakeShortHelp(const wxString&, const wxAcceleratorVector& accel, int id);
#endif

#endif // __WX_EXT_GUI_H__
