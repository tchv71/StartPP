// wx/wxt/trunk.h
// Copyright (c) 2010-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __WX_EXT_TRUNK_H__
#define __WX_EXT_TRUNK_H__

#ifndef __WX_EXT_DEFS_H__
#include "wx/ext/defs.h"
#endif

#if (wxVERSION_NUMBER < 2905)
#include <vector>
typedef std::vector<wxDocument*> wxDocVector;
#define wxALIGN_INVALID ((wxAlignment)-1)
#endif

#ifdef _WX_DOCH__
class wxTrunkDocView
{
public:
#if (wxVERSION_NUMBER >= 2905)
    static inline wxDocVector GetDocumentsVector(const wxDocManager& docManager)
    {
        return docManager.GetDocumentsVector();
    }
#else
    static wxDocVector GetDocumentsVector(const wxDocManager&);
#endif
    static inline void ActivateDocument(wxDocument* doc)
    {
    #if (wxVERSION_NUMBER >= 2905)
        doc->Activate();
    #else
        doc->GetDocumentWindow()->Raise();
    #endif
    }
};
#endif

#if defined(_WX_ABOUTDLG_H_) && (wxVERSION_NUMBER < 2900)
inline void wxAboutBox(const wxAboutDialogInfo& info, wxWindow* WXUNUSED(parent))
{
    wxAboutBox(info);
}
#endif

#if (wxVERSION_NUMBER < 2900)
extern bool wxLaunchDefaultApplication(const wxString& path, int flags = 0);
#endif

/////////////////////////////////////////////////////////////////////////////
// wxAppEx

class wxAppEx : public wxApp
{
    typedef wxApp base;
#if (wxVERSION_NUMBER < 2900)
protected:
    wxString m_appDisplayName;
public:
    wxString GetAppDisplayName() const { return m_appDisplayName; }

    void SetAppName(const wxString& name)
    {
        base::SetAppName(name);
        if (m_appDisplayName.empty())
         SetAppDisplayName(name);
    }
    void SetAppDisplayName(const wxString& name) { m_appDisplayName = name; }
#endif
};

/////////////////////////////////////////////////////////////////////////////
// wxDocManagerEx

class wxDocManagerEx : public wxDocManager
{
    wxDECLARE_CLASS(wxDocManagerEx);
protected:
#if (wxVERSION_NUMBER < 2900)
    void OnUpdateDisableIfNoDoc(wxUpdateUIEvent& event)
    {
        event.Enable( GetCurrentDocument() != NULL );
    }
#endif
};

#if (wxVERSION_NUMBER < 2900)
inline wxString wxJoin(const wxArrayString& as, wxChar sep, wxChar escape = wxT('\\'))
{
    wxString str;
    wxUnusedVar(escape);

    for (wxArrayString::const_iterator it = as.begin();
        it != as.end();
        it++)
    {
        if (it != as.begin())
            str+=sep;
        str+=*it;
    }
    return str;
}
#endif

#if (wxVERSION_NUMBER < 2902)
#define _WX_VERSIONINFO_H_

class wxVersionInfo
{
public:
    wxVersionInfo(const wxString& name,
                  int major,
                  int minor,
                  int micro = 0,
                  const wxString& description = wxString(),
                  const wxString& copyright = wxString())
    {
        m_name = name;
        m_major = major;
        m_minor = minor;
        m_micro = micro;
        m_description = description;
        m_copyright = copyright;
    }

    // Default copy ctor, assignment operator and dtor are ok.


    const wxString& GetName() const { return m_name; }

    int GetMajor() const { return m_major; }
    int GetMinor() const { return m_minor; }
    int GetMicro() const { return m_micro; }

    wxString ToString() const
    {
        return HasDescription() ? GetDescription() : GetVersionString();
    }

    wxString GetVersionString() const
    {
        wxString str;
        str << m_name << wxT(' ') << GetMajor() << wxT('.') << GetMinor();
        if ( GetMicro() )
            str << wxT('.') << GetMicro();

        return str;
    }

    bool HasDescription() const { return !m_description.empty(); }
    const wxString& GetDescription() const { return m_description; }

    bool HasCopyright() const { return !m_copyright.empty(); }
    const wxString& GetCopyright() const { return m_copyright; }

private:
    wxString m_name,
             m_description,
             m_copyright;

    int m_major,
        m_minor,
        m_micro;
};

#endif // _WX_VERSIONINFO_H_

#ifdef _WX_BITMAP_H_BASE_
#if (wxVERSION_NUMBER >= 2900)
class wxBitmapHelpersEx : public wxBitmapHelpers
#else
class wxBitmapHelpersEx
#endif
{
public:
    static inline wxBitmap NewFromXPMData(const char* const* xpmData)
    {
        return wxBitmap(xpmData);
    }
#if (wxVERSION_NUMBER < 2900)
    static wxBitmap NewFromPNGData(const void* data, size_t size);
#endif
};
#endif

#if (wxVERSION_NUMBER < 3000)
class wxAddRemoveAdaptor
{
public:
    // Default ctor and trivial but virtual dtor.
    wxAddRemoveAdaptor() { }
    virtual ~wxAddRemoveAdaptor() { }

    // Override to return the associated control.
    virtual wxWindow* GetItemsCtrl() const = 0;

    // Override to return whether a new item can be added to the control.
    virtual bool CanAdd() const = 0;

    // Override to return whether the currently selected item (if any) can be
    // removed from the control.
    virtual bool CanRemove() const = 0;

    // Called when an item should be added, can only be called if CanAdd()
    // currently returns true.
    virtual void OnAdd() = 0;

    // Called when the current item should be removed, can only be called if
    // CanRemove() currently returns true.
    virtual void OnRemove() = 0;

private:
    wxDECLARE_NO_COPY_CLASS(wxAddRemoveAdaptor);
};
#endif

#endif // __WX_EXT_TRUNK_H__
