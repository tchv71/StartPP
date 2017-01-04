// wx/wxt/defs.h
// Copyright (c) 2010-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __WX_EXT_DEFS_H__
#define __WX_EXT_DEFS_H__

#ifndef wxCLASSINFO
#define wxCLASSINFO CLASSINFO
#endif
#ifndef wxDECLARE_EVENT_TABLE
#define wxDECLARE_EVENT_TABLE DECLARE_EVENT_TABLE
#endif
#ifndef wxBEGIN_EVENT_TABLE
#define wxBEGIN_EVENT_TABLE BEGIN_EVENT_TABLE
#endif
#ifndef wxEND_EVENT_TABLE
#define wxEND_EVENT_TABLE END_EVENT_TABLE
#endif
#ifndef wxDECLARE_CLASS
#define wxDECLARE_CLASS DECLARE_CLASS
#endif
#ifndef wxIMPLEMENT_CLASS
#define wxIMPLEMENT_CLASS IMPLEMENT_CLASS
#endif
#ifndef wxDECLARE_DYNAMIC_CLASS
#define wxDECLARE_DYNAMIC_CLASS DECLARE_DYNAMIC_CLASS
#endif
#ifndef wxIMPLEMENT_DYNAMIC_CLASS
#define wxIMPLEMENT_DYNAMIC_CLASS IMPLEMENT_DYNAMIC_CLASS
#endif
#ifndef wxDECLARE_NO_COPY_CLASS
#define wxDECLARE_NO_COPY_CLASS DECLARE_NO_COPY_CLASS
#endif
#ifndef wxDECLARE_APP
#define wxDECLARE_APP DECLARE_APP
#endif
#ifndef wxIMPLEMENT_APP
#define wxIMPLEMENT_APP IMPLEMENT_APP
#endif
#ifndef wxCMD_LINE_DESC_END
#define wxCMD_LINE_DESC_END { wxCMD_LINE_NONE, NULL, NULL, NULL, wxCMD_LINE_VAL_NONE, 0x0 }
#endif
#ifndef wxSTB_DEFAULT_STYLE
#define wxSTB_DEFAULT_STYLE    (wxST_SIZEGRIP|wxFULL_REPAINT_ON_RESIZE)
#endif
#ifndef wxAPPLY
#define wxAPPLY 0x00000020
#endif
#ifndef wxOVERRIDE
#define wxOVERRIDE
#endif

#ifndef wxEVENT_HANDLER_CAST
    #define wxEVENT_HANDLER_CAST( functype, func ) \
        ( wxObjectEventFunction )( wxEventFunction )wxStaticCastEvent( functype, &func )
#endif

#endif // __WX_EXT_DEFS_H__

