// dbfutil.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

class WXDLLIMPEXP_FWD_CORE wxFindReplaceData;
class WXDLLIMPEXP_FWD_CORE wxFindReplaceDialog;

class wxDBase;
class wxDataModel;

extern wxString dbf_getstruct_c(wxDBase*);
extern size_t dbf_getproperties(wxDBase*, wxArrayString*, bool header = true);

class DataModelFind
{
public:
    DataModelFind();
    virtual ~DataModelFind();
    void ShowDialog(wxWindow* parent, int flags);
    bool FindNext(const wxDataModel*, const wxString&, unsigned int* row);

    wxFindReplaceData* GetData() const { return m_data; }
    wxFindReplaceDialog* GetDialog() const { return m_dlg; }
    void OnCloseDialog(wxWindow* dlg);
private:
    wxFindReplaceDialog* m_dlg;
    wxFindReplaceData* m_data;
    unsigned int row;
    unsigned int column;
};
