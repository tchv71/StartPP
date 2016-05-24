// dbfart.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include "wx/ext/base.h"

#if (wxVERSION_NUMBER < 3000)
#include "../art/help.xpm"
#include "../art/plus.xpm"
#endif
#include "../art/tango/print-preview16.xpm"
#include "../art/app.xpm"
#include "../art/database.xpm"
#include "../art/edit.xpm"

#include "dbfart.h"

/////////////////////////////////////////////////////////////////////////////
// DBFArtProvider

class DBFArtProvider : public wxArtProvider
{
    typedef wxArtProvider base;
public:
protected:
    virtual wxBitmap CreateBitmap(const wxArtID&, const wxArtClient&, const wxSize&);
};

#define ART_DEF_XPM(artid, xpmRc) \
    if (id == (artid)) return wxBitmapHelpersEx::NewFromXPMData(xpmRc##_xpm);
#define ART_DEF_PNG(artid, pngRc) \
    if (id == (artid)) return wxBitmapHelpersEx::NewFromPNGData(pngRc##_png, WXSIZEOF(pngRc##_png));

wxBitmap DBFArtProvider::CreateBitmap(const wxArtID& id, const wxArtClient& client, const wxSize& size)
{
    ART_DEF_XPM(wxART_APP, app)
#if (wxVERSION_NUMBER < 3000)
    ART_DEF_XPM(wxART_HELP      , help)
    ART_DEF_XPM(wxART_PLUS      , plus)
#endif
    ART_DEF_XPM(wxART_PREVIEW, print_preview16)
    ART_DEF_XPM(DBF_ART_DATABASEDOC, database)
    ART_DEF_XPM(DBF_ART_EDIT, edit)
    return wxNullBitmap;
}

/////////////////////////////////////////////////////////////////////////////
// DBFArtModule
// trac.wxwidgets.org/ticket/12519

class DBFArtModule : public wxModule
{
    wxDECLARE_DYNAMIC_CLASS(DBFArtModule);
public:
    DBFArtModule() : wxModule() {}

    virtual bool OnInit()
    { 
        wxArtProvider::Push(new DBFArtProvider());
        return true;
    }
    virtual void OnExit()
    {
    }
};

wxIMPLEMENT_DYNAMIC_CLASS(DBFArtModule, wxModule);

/////////////////////////////////////////////////////////////////////////////
