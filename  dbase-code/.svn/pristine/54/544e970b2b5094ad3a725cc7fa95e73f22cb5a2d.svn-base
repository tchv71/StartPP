// dbflist.cpp
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#include "precomp.h"

#include "wx/ext/gui.h"

#include "../../ioapi/zlib.h"
#include "../../ioapi/ioapi.h"
#include "../../bool.h"
#include "../../dbf.h"
#include "../../dbf.hpp"
#include "../../dbf.inl"
#include "../../dbf_wx.h"

#include "datamodel.h"
#include "datalist.h"
#include "dbfmodel.h"
#include "dbflist.h"

/////////////////////////////////////////////////////////////////////////////
// DBFListCtrl

DBFListCtrl::DBFListCtrl() : DataModelListCtrl(), m_adaptor(this)
{
}

DBFListCtrl::~DBFListCtrl()
{
}

wxBEGIN_EVENT_TABLE(DBFListCtrl, DataModelListCtrl)
    //EVT_COMMAND_LEFT_DCLICK(wxID_ANY, DBFListCtrl::OnDblClick)
#if !USE_DATALISTVIEW
    EVT_LIST_CELL_DCLICK(wxID_ANY, DBFListCtrl::OnDblClick)
#endif
wxEND_EVENT_TABLE()

#if !USE_DATALISTVIEW
class FieldEdit : public wxTextCtrl
{
    typedef wxTextCtrl base;
    wxDECLARE_DYNAMIC_CLASS(FieldEdit);
public:
    wxRect m_fixate;
    void Fixate(const wxRect& rect)
    {
      m_fixate = rect;
      SetSize(rect);
    }
protected:
    void OnMove( wxMoveEvent&);
    wxDECLARE_EVENT_TABLE();
};

wxIMPLEMENT_DYNAMIC_CLASS(FieldEdit, wxTextCtrl)

wxBEGIN_EVENT_TABLE(FieldEdit, wxTextCtrl)
    EVT_MOVE(FieldEdit::OnMove)
wxEND_EVENT_TABLE()

void FieldEdit::OnMove(wxMoveEvent& event)
{
   // Windows wants us to move to the first column, adjust pos
   event.Skip();
   Fixate(m_fixate);
}
#endif

bool DBFListCtrl::Edit(long row, long col)
{
#if USE_DATALISTVIEW
    wxDataViewItem item = RowToItem(row);
    EditItem(item, GetColumn(col));
    return true;
#else
    wxRect rect;
    bool ok = GetSubItemRect(row, col, rect);

    if (ok)
    {
        EnsureVisible(row);
        m_column_clicked = col;
        FieldEdit* edit = wxStaticCast(EditLabel(row, wxCLASSINFO(FieldEdit)), FieldEdit);
        ok = (NULL != edit);
        if (ok)
        {
            edit->SetValue(GetItemText(row, col));
            edit->SelectAll();
            rect.height+=3;
            edit->Fixate(rect);
        }
    }
    return ok;
#endif
}

bool DBFListCtrl::Edit()
{
#if USE_DATALISTVIEW
    base::Edit();
    return true;
#else
    ScrollList(-GetScrollPos(wxHORIZONTAL), 0);
    return Edit((size_t)GetSelectedRow(), 0);
#endif
}

#if !USE_DATALISTVIEW
void DBFListCtrl::OnDblClick(wxListCellEvent& event)
{
    wxUnusedVar(event);
    if (!IsEditable()) return;

    if (GetEditWindowID())
    {
        if (HasSelection())
            wxPostMenuCommand(GetParent(), GetEditWindowID());
    }
    else
        Edit((size_t)event.GetRow(), event.GetColumn());
}
#endif

void DBFListCtrl::OnUpdateNeedSel_Deleted(wxUpdateUIEvent& event)
{
    event.Enable(GetModel() && GetModel()->IsOpen() && GetAdaptor()->IsDeletedInSelection());
}

void DBFListCtrl::OnUpdateNeedSel_NotDeleted(wxUpdateUIEvent& event)
{
    event.Enable(GetModel() && GetModel()->IsOpen() && GetAdaptor()->IsUndeletedInSelection());
}

#if !USE_DATALISTVIEW
wxListItemAttr* DBFListCtrl::OnGetItemAttr(long row) const
{
    wxListItemAttr* attr = base::OnGetItemAttr(row);
    DBFModel* db = const_cast<DBFModel*>(GetModel()); // unconst

    if (db->IsRowDeleted(row))
    {
        const wxColour gray = wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT);
        wxListItemAttr* mine = wxConstCast(&m_attr, wxListItemAttr);

        if (attr)
            mine->AssignFrom(*attr);
        mine->SetTextColour(gray);
        attr = mine;
    }
    return attr;
}
#endif
