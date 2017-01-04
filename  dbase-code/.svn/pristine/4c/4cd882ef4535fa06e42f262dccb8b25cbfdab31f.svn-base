// dbfframe.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __DBFFRAME_H__
#define __DBFFRAME_H__

/////////////////////////////////////////////////////////////////////////////
// DBFFrame

class wxRecentFileList;
class wxAcceleratorVector;
class DBFFrame : public wxDocMDIChildFrame
{
    wxDECLARE_DYNAMIC_CLASS(DBFFrame);
    typedef wxDocMDIChildFrame base;
    wxRecentFileList* m_mru;
public:
    DBFFrame();

    bool Create(wxMDIParentFrame*, wxView*, wxRecentFileList*);

#if (wxVERSION_NUMBER < 2900)
    wxMDIParentFrame* GetMDIParent() const;
#endif
    static const wxAcceleratorVector& GetAccelerator();

    virtual ~DBFFrame();
    virtual void SetMenuBar(wxMenuBar*);
#if (wxVERSION_NUMBER < 2900)
   // To get statusbar menu help
    virtual void DoGiveHelp(const wxString& text, bool show) wxOVERRIDE;
#endif
    virtual void Raise() wxOVERRIDE;
    virtual bool Show(bool show = true) wxOVERRIDE { return base::Show(show); }
#ifdef __WXGTK__
    virtual void SetLabel(const wxString& label) wxOVERRIDE
    {
        SetTitle(label);
    }
#endif

protected:
    wxMenuBar* CreateMenuBar() const;
protected:
    wxDECLARE_EVENT_TABLE();
};

#endif // __DBFFRAME_H__
