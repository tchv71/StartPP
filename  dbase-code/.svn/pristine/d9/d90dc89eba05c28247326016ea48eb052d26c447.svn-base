// dbfutil.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include <wx/fdrepdlg.h>

#include "dbfutil.h"
#include "wx/ext/base.h"
#include "datamodel.h"

#include "../../ioapi/zlib.h"
#include "../../ioapi/ioapi.h"
#include "../../bool.h"
#include "../../dbf.h"
#include "../../dbf.hpp"
#include "../../dbf.inl"
#include "../../dbf_wx.h"
#include "../../dbf_wx.inl"

#define C_ASSERT_(n,e) typedef char __C_ASSERT__##n[(e)?1:-1]

wxString dbf_getstruct_c(wxDBase* db)
{
    wxArrayString as;
    wxString str;
    DBF_INFO info;
    dbf_uint i;
    DBF_FIELD_INFO field_info;
    wxString name;
    const wxChar* const type_array[] =
    {
        wxT("DBF_DATA_TYPE_CHAR"),
        wxT("DBF_DATA_TYPE_INTEGER"),
        wxT("DBF_DATA_TYPE_FLOAT"),
        wxT("DBF_DATA_TYPE_DATE"),
        wxT("DBF_DATA_TYPE_TIME"),
        wxT("DBF_DATA_TYPE_DATETIME"),
        wxT("DBF_DATA_TYPE_MEMO"),
        wxT("DBF_DATA_TYPE_BOOLEAN")
    };
    C_ASSERT_(1,WXSIZEOF(type_array) == DBF_DATA_TYPE_ENUMCOUNT);

    db->GetInfo(&info);
    const wxString title = wxConvertMB2WX(info.tablename);
    const wxString fieldname = wxString::Format(wxT("%s_fields"), title.wx_str());

    // enum
    str.Printf(wxT("enum dbf_%s"), title.wx_str());
    as.push_back(str);
    as.push_back(wxT("{"));
    for (i = 0; ; i++)
    {
        if (!db->GetFieldInfo(i, &field_info))
            break;
        name = wxConvertMB2WX(field_info.name);
        name.MakeLower();
        str.Printf(wxT("   dbf_%s_%s,"), title.wx_str(), name.wx_str());
        as.push_back(str);
    }
    str.Printf(wxT("   dbf_%s_enumcount"), title.wx_str());
    as.push_back(str);
    as.push_back(wxT("};"));

    as.push_back(wxEmptyString);
    // struct
    str.Printf(wxT("const DBF_FIELD_INFO %s[] ="), fieldname.wx_str());
    as.push_back(str);
    as.push_back(wxT("{"));
    for (i = 0; ; i++)
    {
        if (!db->GetFieldInfo(i, &field_info))
            break;
        name = wxConvertMB2WX(field_info.name);
        str.Printf(wxT("   { %-11s, %-21s,%3d,%3d },"),
         //-(int)(WXSIZEOF(info.name)+1),
             wxString::Format(wxT("\"%s\""), name.wx_str()).wx_str(),
             type_array[field_info.type],
             (int)field_info.length,
             field_info.decimals
         );
        as.push_back(str);
    }
    as.push_back(wxT("};"));
    str = wxString::Format(wxT("C_ASSERT(dbf_%s_enumcount == WXSIZEOF(%s));"), title.wx_str(), fieldname.wx_str());
    as.push_back(str);
    return wxJoin(as, '\n', 0);
}

size_t dbf_getproperties(wxDBase* db, wxArrayString* as_ptr, bool header)
{
    wxArrayString as;
    wxString temp;

    if (header)
    {
        DBF_INFO info;
        wxDateTime dt;
        wxString name;
        wxString format;

        db->GetInfo(&info, &dt);
        name = wxConvertMB2WX(info.tablename);
        format = wxConvertMB2WX(info.format);

        temp.Printf(_("Table name:\t%s"), name.wx_str());  as.push_back(temp);
        temp.Printf(_("Format:\t%s"), format.wx_str()); as.push_back(temp);
        temp.Printf(_("Memo file:\t%s"), info.memo ? _("Yes") : _("No")); as.push_back(temp);
        temp.Printf(_("Record count:\t%d"), info.recordcount); as.push_back(temp);
        temp.Printf(_("Modified:\t%s"), info.modified ? _("Yes") : _("No")); as.push_back(temp);
        if (dt.IsValid())
            temp.Printf(_("Last changed:\t%s"), dt.Format(wxT("%x")).wx_str()); as.push_back(temp);
        temp.Printf(_("Field count:\t%d"), info.fieldcount); as.push_back(temp);
    }
    for (dbf_uint i = 0; ; i++)
    {
        static const wxChar* const type_array[] =
        {
            wxT("Char"),
            wxT("Number"),
            wxT("Float"),
            wxT("Date"),
            wxT("Time"),
            wxT("DateTime"),
            wxT("Memo"),
            wxT("Logical")
        };
        C_ASSERT_(1,WXSIZEOF(type_array) == DBF_DATA_TYPE_ENUMCOUNT);
        DBF_FIELD_INFO info;
        wxString name;

        if (!db->GetFieldInfo(i, &info))
            break;
        name = wxConvertMB2WX(info.name);
        temp.Printf(wxT("%d\t%s:\t%s\t%s"),
         (int)i,
         name.wx_str(),
         type_array[info.type],
         info.decimals
            ? wxString::Format(wxT("%d:%d"), (int)info.length, info.decimals).wx_str()
            : wxString::Format(wxT("%d"), (int)info.length).wx_str()
         );
        as.push_back(temp);
    }
    if (as_ptr)
        *as_ptr = as;
    return as.size();
}

/////////////////////////////////////////////////////////////////////////////
// DataModelFind

DataModelFind::DataModelFind()
{
    m_dlg = NULL;
    m_data = new wxFindReplaceData();
    m_data->SetFlags(wxFR_DOWN);
    row = 0;
    column = 0;
}

DataModelFind::~DataModelFind()
{
    delete m_dlg;
    delete m_data;
}

void DataModelFind::ShowDialog(wxWindow* parent, int flags)
{
    if (m_dlg == NULL)
    {
        m_dlg = new wxFindReplaceDialog
                        (
                            parent,
                            m_data,
                            wxGetStockLabelEx(wxID_FIND, wxSTOCK_PLAINTEXT),
                            flags
                        );
    }
    m_dlg->Show();
    m_dlg->Raise();
}

bool DataModelFind::FindNext(const wxDataModel* model, const wxString& find_str, unsigned int* row_ptr)
{
    bool found = false;
    const wxString find_upr = find_str.Upper();

    for (row = 0 + *row_ptr; row < model->GetRowCount(); row++)
    {
        for (; (column < model->GetColumnCount()) && !found; column++)
        {
            wxString str;
            model->GetValueByRow(&str, row, column);

            found = (m_data->GetFlags() & wxFR_MATCHCASE)
                ? (wxNOT_FOUND != str.Find(find_str))
                : (wxNOT_FOUND != str.Upper().Find(find_upr));
            if (found)
                *row_ptr = row;
        }
        if (found)
        {
            wxDELETE(m_dlg);
            break;
        }
        else
            column = 0;
    }
    if (column == model->GetColumnCount())
    {
        column = 0;
        row++;
    }
    if (row == model->GetRowCount())
        row = column = 0;
    return found;
}

void DataModelFind::OnCloseDialog(wxWindow* dlg)
{
    if (dlg == m_dlg)
        m_dlg = NULL;
    else
        wxFAIL_MSG( _("unexpected event") );
    dlg->Destroy();
}
