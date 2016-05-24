// app.h
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __APP_H__
#define __APP_H__

class CommandLine
{
// Attributes
public:
    wxArrayFileName m_fileNames;

// Construction
public:
    CommandLine();
};

/////////////////////////////////////////////////////////////////////////////
// App

class wxRecentFileList;
class DBFResource;

class App : public wxAppEx
{
    typedef wxAppEx base;
public:
    App();

    virtual ~App();
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
    virtual void OnInitCmdLine(wxCmdLineParser&) wxOVERRIDE;
    virtual bool OnCmdLineParsed(wxCmdLineParser&) wxOVERRIDE;

    wxRecentFileList* GetRecentFileList() const { return m_mru; }
    wxDocument* OpenExample(const wxString& fileName);

protected:
    wxDocManager* CreateDocManager();

protected:
    void OnMenuAbout(wxCommandEvent&);
    void OnFileSend(wxCommandEvent&);
    wxDECLARE_EVENT_TABLE();

protected:
    wxRecentFileList* m_mru;
private:
    CommandLine       m_cmdline;
    wxLocaleEx        m_locale;
    DBFResource*      m_res;
    friend class DocManager;
};

wxDECLARE_APP(App);

#endif // __APP_H__
