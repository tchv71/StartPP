// wxtrunk.cpp
// Copyright (c) 2010-2016 by Troels K. All rights reserved.
// License: wxWindows

#include "precomp.h"
#include "wx/ext/trunk.h"

wxIMPLEMENT_CLASS(wxDocManagerEx, wxDocManager);

#if (wxVERSION_NUMBER < 2900)
#ifdef __WINDOWS__
bool wxLaunchDefaultApplication(const wxString& document, int flags)
{
    wxUnusedVar(flags);

    WinStruct<SHELLEXECUTEINFO> sei;
    sei.lpFile = document.wx_str();
    sei.nShow = SW_SHOWDEFAULT;

    // avoid Windows message box in case of error for consistency with
    // wxLaunchDefaultBrowser() even if don't show the error ourselves in this
    // function
    sei.fMask = SEE_MASK_FLAG_NO_UI;

    if ( ::ShellExecuteEx(&sei) )
        return true;

    return false;
}
#else
bool wxLaunchDefaultApplication(const wxString& document, int flags)
{
    wxUnusedVar(flags);

    // Our best best is to use xdg-open from freedesktop.org cross-desktop
    // compatibility suite xdg-utils
    // (see http://portland.freedesktop.org/wiki/) -- this is installed on
    // most modern distributions and may be tweaked by them to handle
    // distribution specifics.
    wxString path, xdg_open;
    if ( wxGetEnv("PATH", &path) &&
         wxFindFileInPath(&xdg_open, path, "xdg-open") )
    {
        if ( wxExecute(xdg_open + " " + document) )
            return true;
    }

    return false;
}
#endif
#endif

