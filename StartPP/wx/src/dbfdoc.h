// dbfdoc.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __DBFDOC_H__
#define __DBFDOC_H__

/////////////////////////////////////////////////////////////////////////////
// DBFDocument

class wxDBase;
class DBaseFieldVector;
class DBFDocument : public wxDocument
{
    typedef wxDocument base;
    wxDECLARE_DYNAMIC_CLASS(DBFDocument);
public:
    DBFDocument();

    wxDBase* GetDatabase() const { return m_database; }
    wxString GetTablename() const;
    wxFileName GetFilename() const { return wxFileName(base::GetFilename()); }
    void SetFilename(const wxFileName& fileName, bool notifyViews = false) { return base::SetFilename(fileName.GetFullPath(), notifyViews); }
    bool IsEditable() const;

    bool StructDialog(wxWindow* parent);

// Implementation
public:
    virtual ~DBFDocument();
    virtual bool OnNewDocument() wxOVERRIDE;
    virtual bool SaveAs() wxOVERRIDE;
    virtual bool IsModified() const wxOVERRIDE;
    virtual void Modify(bool mod) wxOVERRIDE;
    virtual bool OnCloseDocument() wxOVERRIDE;
    virtual bool DeleteContents() wxOVERRIDE;

    bool AttachStream(wxInputStream&, const wxString& filePath);
    bool OnNewDocument(const wxString& title, const DBaseFieldVector&, int version);
protected:
    virtual bool DoSaveDocument(const wxString& filePath) wxOVERRIDE;
    virtual bool DoOpenDocument(const wxString& filePath) wxOVERRIDE;

// Attributes
protected:
    wxDBase* m_database;
    wxInputStream* m_stream;
};

/////////////////////////////////////////////////////////////////////////////
// DBFDocTemplate

class wxRecentFileList;

#ifndef wxDocTemplateClassInfo_Defined
#define wxDocTemplateClassInfo_Defined
class wxDocTemplateClassInfo
{
public:
    wxDocTemplateClassInfo() {}
    wxDocTemplateClassInfo(wxClassInfo* doc, wxClassInfo* view, wxClassInfo* frame) : m_doc(doc), m_view(view), m_frame(frame) { }

    wxClassInfo* m_doc;
    wxClassInfo* m_view;
    wxClassInfo* m_frame;
};
#endif

class DBFDocTemplate : public wxDocTemplate
{
    typedef wxDocTemplate base;
    wxDECLARE_CLASS(DBFDocTemplate);
    static DBFDocTemplate* ms_instance;
    DBFDocTemplate(wxDocManager*, const wxDocTemplateClassInfo&, wxRecentFileList*);
protected:
    const wxClassInfo* m_frameClassInfo;
    wxRecentFileList* m_mru;

    virtual wxFrame* CreateViewFrame(wxView*);
    virtual wxDocument* CreateDocument(const wxString& path, long flags) wxOVERRIDE;
public:
    static const wxDocTemplateClassInfo m_DefaultClassInfo;
    static DBFDocTemplate* Create(wxDocManager*, wxRecentFileList*);
    static wxIcon GetIcon();
    wxRecentFileList* GetRecentFileList() const { return m_mru; }

    static DBFDocTemplate* GetInstance() { return ms_instance; }

    friend class DBFView;
};

#endif // __DBFDOC_H__
