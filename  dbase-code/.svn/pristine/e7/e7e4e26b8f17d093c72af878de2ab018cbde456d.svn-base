// dbfdlgs.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

class DBaseFieldVector;
class NewDatabaseParm;
struct _DBF_FIELD_INFO;

#ifdef __DBF_HPP__
class NewDatabaseParm
{
public:
    NewDatabaseParm() : Version(0) {}

    wxFileName FileName;
    int Version;
    DBaseFieldVector vector;
};
#endif

extern bool DoModal_NewDatabase(wxWindow* parent, const wxString& caption, NewDatabaseParm*);

extern bool DoModal_Structure(wxWindow* parent, const wxString& caption, DBaseFieldVector*, int* version);

extern bool DoModal_FieldEdit(wxWindow* parent, struct _DBF_FIELD_INFO*, const wxString& caption);

