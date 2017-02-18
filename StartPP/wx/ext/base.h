// wx/ext/base.h
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __WX_EXT_BASE_H__
#define __WX_EXT_BASE_H__

#ifndef __WX_EXT_TRUNK_H__
#include "wx/ext/trunk.h"
#endif

class WXDLLIMPEXP_FWD_BASE wxFFile;

#define wxART_APP          wxART_MAKE_ART_ID(wxART_APP)

class wxArrayFileName : public std::vector<wxFileName> {};

#ifdef _WX_ARTPROV_H_
#define wxART_PREVIEW      wxART_MAKE_ART_ID(wxART_PREVIEW)
#define wxART_PREFERENCES  wxART_MAKE_ART_ID(wxART_PREFERENCES)
#define wxART_SETUP        wxART_MAKE_ART_ID(wxART_SETUP)
#define wxART_ZOOM_100     wxART_MAKE_ART_ID(wxART_ZOOM_100)
#if (wxVERSION_NUMBER < 3000)
#define wxART_PLUS         wxART_MAKE_ART_ID(wxART_PLUS)
#define wxART_MINUS        wxART_MAKE_ART_ID(wxART_MINUS)
#endif
#define wxART_ADD          wxART_PLUS
#define wxART_REMOVE       wxART_MINUS
#define wxART_ZOOM_IN      wxART_PLUS
#define wxART_ZOOM_OUT     wxART_MINUS
extern wxArtID wxID2ArtID(int wx_id);
#endif

extern bool wxRemoveFile(wxFFile*);
extern bool wxSendMail(const wxFileName&);

class wxClipboardHelper
{
public:
    enum Type
    {
        Default = 1, // use the normal clipboard
        Primary = 2, // use the primary clipboard
        Both    = 3  // use both clipboards (only valid for set functions)
    };
    // Set the text to the specified clipboard(s).
    static bool SetText(const wxString& str, Type clip_type = Default);

    static bool Set(wxDataObject* def, wxDataObject* primary = NULL);
};

class wxXmlResourceHelper
{
public:
    static const wxChar* const FileExt;
    static const wxChar* const FileExtCompressed;
    static const wxChar* const DefaultFolder;

    static void Init();

    static bool LoadFromFile(const wxFileName&);
    static bool LoadFromFile(const char* srcmodule, const wxString& filename);
    static bool LoadFromMemory(const void* buf, size_t buf_len, const wxString& filename, wxFFile* tempfile = NULL);
};

#define wxMessageBoxCaption      wxGetApp().GetAppDisplayName()

#ifdef _WX_STOCKITEM_H_
#if (wxVERSION_NUMBER < 2901)
#define wxSTOCK_WITHOUT_ELLIPSIS 4
#define wxSTOCK_FOR_BUTTON (wxSTOCK_WITH_MNEMONIC | wxSTOCK_WITHOUT_ELLIPSIS)
#endif
#define wxSTOCK_PLAINTEXT wxSTOCK_WITHOUT_ELLIPSIS
extern wxString wxGetStockLabelEx(wxWindowID, long flags = wxSTOCK_WITH_MNEMONIC);
#endif

inline wxString wxItoa(int value) { return wxString::Format(wxT("%d"), value); }

template <class T>
inline T vector_join(const T& vec1, const T& vec2)
{
    T temp;
    temp.insert(temp.end(), vec1.begin(), vec1.end());
    temp.insert(temp.end(), vec2.begin(), vec2.end());
    return temp;
}

class wxFileLoadedHint : public wxObject
{
    wxDECLARE_CLASS(wxFileLoadedHint);
};

#ifdef _WX_INTL_H_
class wxLocaleEx : public wxLocale
{
public:
    bool Init(wxLanguage lang = wxLANGUAGE_DEFAULT, int flags = wxLOCALE_LOAD_DEFAULT)
    {
    #if (wxVERSION_NUMBER >= 2900) // trac.wxwidgets.org/ticket/15257
        if (lang == wxLANGUAGE_DEFAULT)
            lang = (wxLanguage)GetSystemLanguage();
    #endif
        return wxLocale::Init(lang, flags);
    }
};
#endif

class TextWriter
{
public:
    TextWriter() : m_indent(0), m_linePos(0), m_encoding(), m_tabString()
    {
    }
    virtual ~TextWriter()
    {
    }

    virtual bool IsOpen() const = 0;
    virtual void Close() = 0;

    void SetEncoding(const std::string& encoding) { m_encoding = encoding; }
    void SetTabString(const std::string& tabstring) { m_tabString = tabstring; }
    std::string GetEncoding() const { return m_encoding; }
    std::string GetTabString() const { return m_tabString; }
    int GetIndent() const { return m_indent; }
    virtual std::string GetNewLine() const
    {
        return "\n";
    }
    void Write(const std::string& str)
    {
        if (m_linePos == 0)
            for (int i = 0; i < m_indent; i++)
                DoWrite(m_tabString);
        m_linePos += DoWrite(str);
    }
    void Write(char ch)
    {
        Write(std::string(1, ch));
    }
    void WriteLine(const std::string& str = std::string())
    {
        Write(str + GetNewLine());
        m_linePos = 0;
    }
    void WriteLine(char ch)
    {
        WriteLine(std::string(1, ch));
    }
    void IncreaseIndent()
    {
        m_indent++;
    }
    void DecreaseIndent()
    {
        wxASSERT(m_indent != 0);
        m_indent--;
    }
protected:
    virtual size_t DoWrite(const std::string& str) = 0;

    int m_indent;
    size_t m_linePos;
    std::string m_encoding;
    std::string m_tabString;
};

typedef std::vector<std::string> std_string_vector;

class XmlWriter : public TextWriter
{
public:
    static const char TagLeftChar = '<';
    static const char TagRightChar = '>';
    static const std::string EndTagLeftChars;
    static const std::string DefaultEncoding; // utf8
    static const std::string DefaultTabString; // 3 spaces

    XmlWriter() : m_open(true), m_ElementOpened(false)
    {
        m_tabString = DefaultTabString, m_encoding = DefaultEncoding;
    }
    virtual ~XmlWriter()
    {
        if (IsOpen())
            Close();
    }
    bool Open(const std::string& tableName)
    {
        m_TableName = tableName;
        WriteLine("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
        WriteStartElement(tableName);

        return true;
    }
    virtual void Close()
    {
        WriteEndElement();
        m_open = false;
        m_linePos = 0;
        m_indent = 0;
    }

    void WriteStartElement(const std::string& elmName)
    {
        if (m_indent && m_ElementOpened)
            WriteLine(TagRightChar);
        Write(TagLeftChar);
        Write(elmName);
        ElementList.push_back(elmName);
        m_indent++;
        m_ElementOpened = true;
    }
    void WriteElement(const std::string& elmName, const std::string& text)
    {
        if (m_ElementOpened)
        {
            WriteLine(TagRightChar);
            m_ElementOpened = false;
        }
        WriteStartElement(elmName);
        Write(TagRightChar);
        m_ElementOpened = false;
        Write(text);
        WriteEndElement();
    }
    void WriteEndElement()
    {
        if (m_ElementOpened)
        {
            WriteLine(TagRightChar);
            m_ElementOpened = false;
        }
        m_indent--;
        std::string elmName = ElementList.back();
        ElementList.pop_back();
        Write(EndTagLeftChars);
        WriteLine(elmName + TagRightChar);
    }
    void WriteAttribute(const std::string& attrName, const std::string& text)
    {
        Write(' ');
        Write(attrName + "=\"");
        Write(text + "\"");
    }
    void WriteAttribute(const std::string& attrName, const bool& value)
    {
        WriteAttribute(attrName, std::string(value ? "true" : "false"));
    }
    void WriteAttribute(const std::string& attrName, const int& n)
    {
        char temp[80];
        snprintf(temp, sizeof(temp)/sizeof(temp[0]), "%d", n);
        Write(' ');
        Write(attrName + "=\"");
        Write(temp);
        Write("\"");
    }
    virtual bool IsOpen() const { return m_open; }
protected:
    bool m_open;
    std::string m_TableName;
    std_string_vector ElementList;
    bool m_ElementOpened;
};

class wxXmlWriter : public XmlWriter
{
    typedef XmlWriter base;
public:
    wxXmlWriter() : XmlWriter(), m_stream(NULL) {}

    bool Open(const std::string& tableName, wxOutputStream* stream)
    {
        m_stream = stream;
        return base::Open(tableName);
    }
    virtual void Close()
    {
        base::Close();
        m_stream = NULL;
    }
    virtual std::string GetNewLine() const
    {
    #ifdef __WINDOWS__
        return "\r\n";
    #elif defined(__WXOSX__)
        return "\r";
    #else
        return base::GetNewLine();
    #endif
    }
protected:
    virtual size_t DoWrite(const std::string& str)
    {
        return m_stream->Write(str.c_str(), str.length()).LastWrite();
    }
private:
    wxOutputStream* m_stream;
};

class HtmlTextWriter : public TextWriter
{
public:
    static const char TagLeftChar = '<';
    static const char TagRightChar = '>';
    static const std::string EndTagLeftChars;
    static const std::string DefaultEncoding; // utf8
    static const std::string DefaultTabString; // 3 spaces

    HtmlTextWriter();

    virtual ~HtmlTextWriter()
    {
        if (IsOpen())
            Close();
    }
    virtual bool IsOpen() const { return m_open; }

    void WriteBeginTag(const std::string& tagName)
    {
        Write(TagLeftChar);
        Write(tagName);
    }
    void WriteFullBeginTag(const std::string& tagName)
    {
        WriteBeginTag(tagName + TagRightChar);
    }
    void WriteEndTag(const std::string& tagName)
    {
        Write(EndTagLeftChars + tagName + TagRightChar);
    }
    void WriteAttribute(const std::string& name, const std::string& value)
    {
        Write(' ');
        Write(name);
        Write("=\"");
        Write(value);
        Write('\"');
    }
    void WriteBreak()
    {
        Write("<br/>");
    }
    virtual void Close()
    {
        m_linePos = 0;
        m_indent = 0;
        m_open = false;
    }
    static std::string Escape(const std::string&);
protected:
    bool m_open;
};

class wxHtmlTextWriter : public HtmlTextWriter
{
    typedef HtmlTextWriter base;
public:
    wxHtmlTextWriter(wxOutputStream* stream) : HtmlTextWriter(), m_stream(stream) {}
    virtual void Close()
    {
        base::Close();
        m_stream = NULL;
    }
    virtual std::string GetNewLine() const
    {
    #ifdef __WINDOWS__
        return "\r\n";
    #elif defined(__WXOSX__)
        return "\r";
    #else
        return base::GetNewLine();
    #endif
    }
protected:
    virtual size_t DoWrite(const std::string& str)
    {
        return m_stream->Write(str.c_str(), str.length()).LastWrite();
    }
private:
    wxOutputStream* m_stream;
};

class HtmlItem
{
public:
    virtual ~HtmlItem() {}
    virtual void Render(HtmlTextWriter*) const = 0;
};

enum HtmlTextWeight
{
    HtmlTextWeight_Normal,
    HtmlTextWeight_Bold
};

class HtmlTextParagraph : public HtmlItem
{
public:
    std::string Text;
    HtmlTextWeight Weight;

    HtmlTextParagraph(const std::string& str, HtmlTextWeight weight = HtmlTextWeight_Normal)
    {
        Text = str, Weight = weight;
    }
    virtual void Render(HtmlTextWriter*) const;

    static std::string ToBold(const std::string& str)
    {
        return std::string("<b>") + str + "</b>";
    }
};

class HtmlTableRow
{
public:
    std_string_vector ColumnTextArray;
    std_string_vector ColumnAttribute;
};
typedef std::vector<HtmlTableRow> HtmlTableVector;

class HtmlTable : public HtmlItem
{
public:
    HtmlTableVector List;
    std::vector<int> PercentArray;
    int Border;
    HtmlTable() : HtmlItem(), Border(1) {}
    virtual void Render(HtmlTextWriter*) const;
    virtual ~HtmlTable() {}
};

typedef std::vector<HtmlItem*> HtmlItemVector;

class wxHtmlTableWriter : public wxObject
{
public:
    std::string Title;
    HtmlItemVector List;
    void SaveFile(wxOutputStream*, std::string encoding = HtmlTextWriter::DefaultEncoding);
    virtual ~wxHtmlTableWriter();
};

#endif // __WX_EXT_BASE_H__
