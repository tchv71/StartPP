// dbflist.h - editable
// Copyright (c) 2007-2015 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __DATALIST_H__
   #include "datalist.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// DBFListCtrl

class DBFListCtrl : public DataModelListCtrl
{
    typedef DataModelListCtrl base;
public:
    DBFListCtrl();
    virtual ~DBFListCtrl();

    void AssociateModel(DBFModel* model) { base::AssociateModel(model); }
          DBFModel* GetModel()       { return (DBFModel*)base::GetModel(); }
    const DBFModel* GetModel() const { return (DBFModel*)base::GetModel(); }

    bool Edit(long row, long col);
    virtual bool Edit();

    DataModelListCtrlAdaptor* GetAdaptor() { return &m_adaptor; }

    void OnUpdateNeedSel_Deleted(wxUpdateUIEvent&);
    void OnUpdateNeedSel_NotDeleted(wxUpdateUIEvent&);

#if !USE_DATALISTVIEW
    virtual wxListItemAttr* OnGetItemAttr(long row) const;
#endif
protected:
#if !USE_DATALISTVIEW
    void OnDblClick(wxListCellEvent&);
#endif
    wxDECLARE_EVENT_TABLE();

#if !USE_DATALISTVIEW
    wxListItemAttr m_attr;
#endif
private:
    DataModelListCtrlAdaptor m_adaptor;
};
