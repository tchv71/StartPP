// appdoc.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

class DocManager : public wxDocManagerEx
{
    typedef wxDocManagerEx base;
    wxDECLARE_CLASS(DocManager);
public:
    DocManager(App*);
    virtual wxDocument* CreateDocument(const wxString& path, long flags);
#if (wxVERSION_NUMBER >= 2901)
    virtual wxPreviewFrame* CreatePreviewFrame(wxPrintPreviewBase*, wxWindow* parent, const wxString& title) wxOVERRIDE;
#endif
    wxDocument* CreateExampleDocument(const wxString& fullname);
protected:
    void OnOpenContainingFolder(wxCommandEvent&);
    void OnUpdateNeedSaved(wxUpdateUIEvent&);
    wxDECLARE_EVENT_TABLE();
};

#ifdef __DBF_HPP__
class NewDatabaseParm
{
public:
    NewDatabaseParm() : Version(0) {}

    wxFileName FileName;
    int Version;
    DBaseFieldVector vector;
};
class DbfStruct
{
public:
    wxString Name;
    int      Version;
    DBaseFieldVector Vector;
};
class DbfExampleVector : public std::vector<DbfStruct>
{
public:
    DbfExampleVector();
    wxArrayString GetNames() const;
    const_iterator Find(const wxString& name) const;
};
extern const DbfExampleVector PUB_DbfExampleVector;
#endif
