// wxbase.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include <wx/html/htmprint.h>

#include "wx/ext/base.h"

#ifdef __WINDOWS__
#include "contrib/smapi.cpp"
#endif

wxIMPLEMENT_CLASS(wxFileLoadedHint, wxObject);

//static
const std::string XmlWriter::EndTagLeftChars = "</";
//static
const std::string XmlWriter::DefaultEncoding = "utf8";
//static
const std::string XmlWriter::DefaultTabString = std::string(3, ' ');


//static
const std::string HtmlTextWriter::EndTagLeftChars = "</";
//static
const std::string HtmlTextWriter::DefaultEncoding = "utf8";
//static
const std::string HtmlTextWriter::DefaultTabString = std::string(3, ' ');

HtmlTextWriter::HtmlTextWriter() : TextWriter()
{
    m_encoding = DefaultEncoding, m_tabString = DefaultTabString;
    m_open = true;
}

//static
std::string HtmlTextWriter::Escape(const std::string& data)
{
    std::string buffer;
    buffer.reserve(data.size());
    for(std::string::const_iterator it = data.begin(); it != data.end(); it++)
    {
        switch(*it)
        {
            case '&':  buffer.append("&amp;");  break;
            case '\"': buffer.append("&quot;"); break;
            case '\'': buffer.append("&apos;"); break;
            case '<':  buffer.append("&lt;");   break;
            case '>':  buffer.append("&gt;");   break;
            case ' ':  buffer.append("&nbsp;"); break;
            default:   buffer.append(1, *it);   break;
        }
    }
    return buffer;
}

bool wxRemoveFile(wxFFile* file)
{
    bool ok = true;

    if (file->IsOpened())
    {
        wxString filename = file->GetName();

        file->Close();
        wxLogNull no_log;
        ok = wxRemoveFile(filename);
    }
    return ok;
}

#ifdef __WINDOWS__
bool wxSendMail(const wxFileName& fileName)
{
    wxMailMessage msg(wxEmptyString, wxEmptyString, wxEmptyString, wxEmptyString, fileName.GetFullPath(), fileName.GetFullName());

    wxMapiSession mapi;
    mapi.Logon(wxEmptyString, wxEmptyString);
    return mapi.Send(msg);
}
#endif

//static
const wxChar* const wxXmlResourceHelper::FileExt = wxT("xrc");
//static
const wxChar* const wxXmlResourceHelper::FileExtCompressed = wxT("xrs");
//static
const wxChar* const wxXmlResourceHelper::DefaultFolder = wxT("xmlres");

//static
void wxXmlResourceHelper::Init()
{
   wxXmlResource::Get()->InitAllHandlers();
}

bool wxCreateFileFromMemory(const void* buf, size_t buf_len, const wxFileName& filename, wxFFile* file_ptr)
{
    wxFFile file;
    bool ok = filename.FileExists();

    if (ok)
    {
         // file exists
        ok = file.Open(filename.GetFullPath(), wxT("rb"));
        if (ok)
        {
            ok = (wxFileOffset(buf_len) == file.Length());
            if (!ok)
            {
                // exists but wrong length
                file.Close();
                wxRemoveFile(filename.GetFullPath());
            }
        }
    }
    if (!ok)
    {
        // create file
        ok =  file.Open(filename.GetFullPath(), wxT("wb"))
           && (buf_len == file.Write(buf, buf_len))
           && file.Flush();
    }

    if (ok && file_ptr)
    {
        file_ptr->Attach(file.fp(), file.GetName());
        file.Detach();
    }
    return ok;
}

//static
bool wxXmlResourceHelper::LoadFromMemory(const void* buf, size_t buf_len, const wxString& fullname, wxFFile* file_ptr)
{
    wxFileName filename(wxFileName::GetTempDir(), fullname);
    bool ok;

    filename.AppendDir(filename.GetName()); // subfolder named after file title
    ok = filename.DirExists() || filename.Mkdir();
    if (ok)
        ok = wxCreateFileFromMemory(buf, buf_len, filename, file_ptr);
    if (ok)
        ok = LoadFromFile(filename);
    return ok;
}

//static
bool wxXmlResourceHelper::LoadFromFile(const wxFileName& filename)
{
   return wxXmlResource::Get()->Load(filename.GetFullPath());
}

//static
bool wxXmlResourceHelper::LoadFromFile(const char* srcmodule, const wxString& fullname)
{
    wxFileName filename(wxString::FromAscii(srcmodule));

    filename.RemoveLastDir();
    filename.AppendDir(DefaultFolder);
    filename.SetFullName(fullname);
    return LoadFromFile(filename);
}

wxArtID wxID2ArtID(int wx_id)
{
   wxArtID str;
   static const struct _MAP
   {
      int id;
#if (wxVERSION_NUMBER >= 2902)
      const char* id_art;
#else
      const wxChar* id_art;
#endif
   } aMap[] =
   {
      { wxID_UP            , wxART_GO_UP           },
      { wxID_DOWN          , wxART_GO_DOWN         },
      { wxID_BACKWARD      , wxART_GO_BACK         },
      { wxID_FORWARD       , wxART_GO_FORWARD      },
      { wxID_EXIT          , wxART_QUIT            },
      { wxID_CLOSE         , wxART_QUIT            },
      { wxID_HELP          , wxART_HELP            },
      { wxID_ABOUT         , wxART_HELP            },
      { wxID_COPY          , wxART_COPY            },
      { wxID_CUT           , wxART_CUT             },
      { wxID_PASTE         , wxART_PASTE           },
      { wxID_DELETE        , wxART_DELETE          },
      { wxID_NEW           , wxART_NEW             },
      { wxID_UNDO          , wxART_UNDO            },
      { wxID_REDO          , wxART_REDO            },
      { wxID_FIND          , wxART_FIND            },
      { wxID_REPLACE       , wxART_FIND_AND_REPLACE},
      { wxID_REPLACE_ALL   , wxART_FIND_AND_REPLACE},
      { wxID_OPEN          , wxART_FILE_OPEN       },
      { wxID_SAVE          , wxART_FILE_SAVE       },
      { wxID_SAVEAS        , wxART_FILE_SAVE_AS    },
      { wxID_HOME          , wxART_GO_HOME         },
      { wxID_REMOVE        , wxART_DEL_BOOKMARK    },
      { wxID_PRINT         , wxART_PRINT           },
      { wxID_PRINT_SETUP   , wxART_PRINT           },
      { wxID_PREVIEW       , wxART_PREVIEW         },
      { wxID_PREFERENCES   , wxART_PREFERENCES     },
      { wxID_SETUP         , wxART_SETUP           },
      { wxID_VIEW_DETAILS  , wxART_REPORT_VIEW     },
      { wxID_VIEW_LIST     , wxART_LIST_VIEW       },
      { wxID_ZOOM_IN       , wxART_ZOOM_IN         },
      { wxID_ZOOM_OUT      , wxART_ZOOM_OUT        },
      { wxID_ZOOM_100      , wxART_ZOOM_100        },
      { wxID_ADD           , wxART_ADD             }
   };
   for (size_t i = 0; i < WXSIZEOF(aMap); i++)
   {
      if (aMap[i].id == wx_id)
      {
         str = aMap[i].id_art;
         break;
      }
   }
   return str;
}

wxString wxGetStockLabelEx(wxWindowID id, long flags)
{
    #define STOCKITEM(stockid, label) \
        case stockid:                 \
            stockLabel = label;       \
            break;

   wxString stockLabel;
   switch (id)
   {
     STOCKITEM(wxID_ICONIZE_FRAME,            _("&Minimize"))
     STOCKITEM(wxID_VIEW_SORTNAME,            _("&Sort by name"))
     STOCKITEM(wxID_VIEW_SORTTYPE,            _("&Sort by type"))
     STOCKITEM(wxID_VIEW_SORTDATE,            _("&Sort by date"))
     STOCKITEM(wxID_VIEW_SORTSIZE,            _("&Sort by size"))
     STOCKITEM(wxID_VIEW_LIST,                _("&List mode"))
     STOCKITEM(wxID_VIEW_DETAILS,             _("&Details mode"))
     STOCKITEM(wxID_VIEW_LARGEICONS,          _("&Large icons mode"))
     STOCKITEM(wxID_VIEW_SMALLICONS,          _("&Small icons mode"))
     STOCKITEM(wxID_SETUP          ,          _("&Setup..."))
      default:
         //if (id == wxXRCID_GOTO) stockLabel = _("&Goto...");
         //else if (id == wxXRCID_RUN) stockLabel = _("&Run");
         break;
   }
#undef STOCKITEM
   if (!stockLabel.empty())
   {
       if ( !(flags & wxSTOCK_WITH_MNEMONIC) )
           stockLabel = wxStripMenuCodes(stockLabel);
#if (wxVERSION_NUMBER >= 2901)
       if (flags & wxSTOCK_WITHOUT_ELLIPSIS)
       {
           wxString baseLabel;
           if ( stockLabel.EndsWith(wxT("..."), &baseLabel) )
               stockLabel = baseLabel;
       }
#else
       // handled below
#endif
   }
   else
      stockLabel = wxGetStockLabel(id, flags);
#if (wxVERSION_NUMBER < 2901)
   if (flags & wxSTOCK_WITHOUT_ELLIPSIS)
   {
      wxString baseLabel;
      if ( stockLabel.EndsWith(wxT("..."), &baseLabel) )
         stockLabel = baseLabel;
   }
#endif
   return stockLabel;
}

#define HASBIT(value, bit)      (((value) & (bit)) != 0)

//static
bool wxClipboardHelper::Set(wxDataObject* def, wxDataObject* primary)
{
#if wxUSE_DATAOBJ && wxUSE_CLIPBOARD
    wxClipboard* clipboard = wxTheClipboard;
    bool was_open = clipboard->IsOpened();
    bool ok = was_open || clipboard->Open();

    if (ok)
    {
        if (def)
        {
            clipboard->UsePrimarySelection(false);
            ok = clipboard->SetData(def);
            if (ok)
                def = NULL;
        }
    #ifndef __WXMSW__
        if (primary)
        {
            clipboard->UsePrimarySelection(true);
            ok = clipboard->SetData(primary);
            clipboard->UsePrimarySelection(false);
            if (ok)
                primary = NULL;
        }
    #endif // __WXMSW__
        if (!was_open)
            clipboard->Close();
        //clipboard->Flush(); // else emu and wxc is freezing
    }
    delete def;
    delete primary;
    return ok;
#else
    return false;
#endif
}

//static
bool wxClipboardHelper::SetText(const wxString& str, Type clip_type)
{
#if wxUSE_DATAOBJ && wxUSE_CLIPBOARD
    return Set(HASBIT(clip_type, Default) ? new wxTextDataObject(str) : NULL,
               HASBIT(clip_type, Primary) ? new wxTextDataObject(str) : NULL);
#else
    return false;
#endif
}

void HtmlTextParagraph::Render(HtmlTextWriter* writer_ptr) const
{
    HtmlTextWriter& writer = *writer_ptr;
    writer.WriteFullBeginTag("p");
    if (Weight == HtmlTextWeight_Bold)
        writer.WriteFullBeginTag("b");
    writer.Write(Text);
    if (Weight == HtmlTextWeight_Bold)
        writer.WriteEndTag("b");
    writer.WriteEndTag("p");
    writer.WriteBreak();
    writer.WriteLine();
}

void HtmlTable::Render(HtmlTextWriter* writer_ptr) const
{
    char str[80];
    HtmlTextWriter& writer = *writer_ptr;

    writer.WriteBeginTag("table");
        _snprintf(str, WXSIZEOF(str), "%d", Border);
        writer.WriteAttribute("border", str);
        writer.Write(wxHtmlTextWriter::TagRightChar); writer.WriteLine(); writer.IncreaseIndent();
        writer.WriteFullBeginTag("tbody"); writer.WriteLine(); writer.IncreaseIndent();

            for (HtmlTableVector::const_iterator it_row = List.begin(); it_row != List.end(); it_row++)
            {
                writer.WriteFullBeginTag("tr"); writer.WriteLine(); writer.IncreaseIndent();
                size_t column = 0;
                for (std_string_vector::const_iterator it_col = it_row->ColumnTextArray.begin(); it_col != it_row->ColumnTextArray.end(); it_col++)
                {
                    writer.WriteBeginTag("td");

                    if ( (it_col == it_row->ColumnTextArray.begin()) && (PercentArray.size() > column))
                    {
                        _snprintf(str, WXSIZEOF(str), " width=\"%d%%\"", PercentArray[column]);
                        writer.Write(str);
                    }
                    if (it_row->ColumnAttribute.size() > column)
                        writer.Write(std::string(" ") + it_row->ColumnAttribute[column]);
                    writer.Write(wxHtmlTextWriter::TagRightChar);
                    writer.Write(*it_col);
                    writer.WriteEndTag("td"); writer.WriteLine();
                    column++;
                }
                writer.DecreaseIndent();
                writer.WriteEndTag("tr"); writer.WriteLine();
            }
        writer.DecreaseIndent();
        writer.WriteEndTag("tbody"); writer.WriteLine(); writer.DecreaseIndent();
    writer.WriteEndTag("table"); writer.WriteLine();
}

wxHtmlTableWriter::~wxHtmlTableWriter()
{
    for (HtmlItemVector::iterator it = List.begin(); it != List.end(); it++)
        delete *it;
}

void wxHtmlTableWriter::SaveFile(wxOutputStream* stream, std::string encoding)
{
    wxHtmlTextWriter writer(stream);
    writer.SetEncoding(encoding);

    writer.WriteFullBeginTag("html"); writer.WriteLine(); writer.IncreaseIndent();
        writer.WriteFullBeginTag("head"); writer.WriteLine(); writer.IncreaseIndent();
            writer.WriteBeginTag("meta");
                writer.WriteAttribute("content", std::string("text/html; charset=") + writer.GetEncoding());
                writer.Write(wxHtmlTextWriter::TagRightChar); writer.WriteLine();
                writer.WriteFullBeginTag("title");
                    writer.Write(Title);
                writer.WriteEndTag("title"); writer.WriteLine();
                writer.DecreaseIndent();
        writer.WriteEndTag("head"); writer.WriteLine();
        writer.WriteFullBeginTag("body"); writer.WriteLine(); writer.IncreaseIndent();
            for (HtmlItemVector::const_iterator it = List.begin(); it != List.end(); it++)
                (*it)->Render(&writer);
        writer.DecreaseIndent();
        writer.WriteEndTag("body"); writer.WriteLine(); writer.DecreaseIndent();
    writer.WriteEndTag("html"); writer.WriteLine();
    writer.Close();
}

/////////////////////////////////////////////////////////////////////////////
