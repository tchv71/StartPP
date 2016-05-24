// dbfview.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __DBFVIEW_H__
#define __DBFVIEW_H__

/////////////////////////////////////////////////////////////////////////////
// DBFView

class WXDLLIMPEXP_FWD_CORE wxFindReplaceDialog;
class WXDLLIMPEXP_FWD_CORE wxFindDialogEvent;

class DBFDocument;
class DBFWindow;
class DataModelFind;
class wxDataModel;

class DBFView : public wxViewEx
{
    typedef wxViewEx base;
    wxDECLARE_DYNAMIC_CLASS(DBFView);
public:
    DBFView();

    DBFDocument* GetDocument() const;
    DBFWindow* GetWindow() const;
    wxWindow* GetModalParent() const;

// Implementation
public:
    virtual ~DBFView();
    virtual bool OnClose(bool deleteWindow = true) wxOVERRIDE;
    virtual bool OnCreate(wxDocument*, long flags) wxOVERRIDE;
    virtual void OnUpdate(wxView* sender, wxObject* hint = NULL) wxOVERRIDE;
    virtual wxPrintout* OnCreatePrintout() wxOVERRIDE;
protected:
    void OnStructClipboard(wxCommandEvent&);
    void OnStruct(wxCommandEvent&);
    void OnProperties(wxCommandEvent&);
    void OnFileExport(wxCommandEvent&);
   
    void OnUpdateNeedSel (wxUpdateUIEvent&);
    void OnSelectAll     (wxCommandEvent&);
    void OnUpdateSelectAll(wxUpdateUIEvent&);
    void OnAdd           (wxCommandEvent&);
    void OnEdit          (wxCommandEvent&);
    void OnUpdateNeedEditable(wxUpdateUIEvent&);
    void OnUndelete      (wxCommandEvent&);
    void OnUpdateNeedSel_Deleted(wxUpdateUIEvent&);
    void OnDelete        (wxCommandEvent&);
    void OnUpdateNeedSel_NotDeleted(wxUpdateUIEvent&);
    void OnDeleteAll     (wxCommandEvent&);
    void OnGoto          (wxCommandEvent&);
    void OnCopy          (wxCommandEvent&);
    void OnCopyPath      (wxCommandEvent&);
    void OnFindDialog    (wxCommandEvent&);
    void OnFindAgain     (wxCommandEvent&);
    void OnFindEvent     (wxFindDialogEvent&);
    wxDECLARE_EVENT_TABLE();

private:
    DataModelFind* m_find;

    void OnFindEvent(wxEventType, const wxString&, wxFindReplaceDialog*);

    friend class DBFWindow;
};

#endif // __DBFVIEW_H__
