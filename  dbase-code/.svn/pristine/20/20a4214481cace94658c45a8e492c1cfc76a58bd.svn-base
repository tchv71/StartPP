// appframe.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __APPFRAME_H__
#define __APPFRAME_H__

/////////////////////////////////////////////////////////////////////////////
// MainFrame

class MDIWindowMenuEvtHandler;
class WXDLLIMPEXP_FWD_ADV wxAboutDialogInfo;

class MainFrame : public wxDocMDIParentFrame
{
    typedef wxDocMDIParentFrame base;
    wxDECLARE_CLASS(MainFrame);
protected:
    MDIWindowMenuEvtHandler* m_windowMenuEvtHandler;
public:
    MainFrame();

    bool Create(wxDocManager*, const wxString& title, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize);

    virtual void SetMenuBar(wxMenuBar*);
    virtual ~MainFrame();
#ifdef __WINDOWS__
    virtual bool MSWTranslateMessage(WXMSG*) wxOVERRIDE;
#endif

    static void GetVersionInfo(wxAboutDialogInfo*);
protected:
    wxMenuBar* CreateMenuBar() const;
    wxToolBar* CreateToolBar();

protected:
    void OnStatusBar        (wxCommandEvent&);
    void OnToolBar          (wxCommandEvent&);
    void OnFullscreen       (wxCommandEvent&);
    void OnWindowsDialog    (wxCommandEvent&);
    void OnUpdateFullscreen (wxUpdateUIEvent&);
    void OnUpdateStatusBar  (wxUpdateUIEvent&);
    void OnUpdateToolBar    (wxUpdateUIEvent&);
    void OnOpenExample      (wxCommandEvent&);
    wxDECLARE_EVENT_TABLE();
};

#endif // __APPFRAME_H__
