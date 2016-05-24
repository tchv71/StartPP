// dbfmodel.h
// Copyright (c) 2007-2016 by Troels K. All rights reserved.
// License: wxWindows Library Licence, Version 3.1 - see LICENSE.txt

#ifndef __DBFMODEL_H__
#define __DBFMODEL_H__

#ifndef __DATAMODEL_H__
#include "datamodel.h"
#endif

class wxDBase;
class WXDLLIMPEXP_FWD_BASE wxOutputStream;
class DBFModel : public wxDataModel
{
    typedef wxDataModel base;
public:
    static const wxChar* const FileExt;

    DBFModel(wxDBase*, bool delete_on_exit = false);

// Operations
public:
    void     SetDatabase(wxDBase* database) { m_database = database; }
    wxDBase* GetDatabase() const { return m_database; }

    static bool SaveAs(wxDataModel*, wxOutputStream*);

// Implementation
public:
    virtual ~DBFModel();

// wxDataViewListModel implementation
public:
    virtual unsigned int GetRowCount() const;
    virtual unsigned int GetColumnCount() const;
    virtual bool GetColumn( unsigned int col, wxDataModelColumnInfo*) const;
    virtual int FindColumn(const wxString& colname) const;

// wxDataModel implementation
public:
    virtual void GetValueByRow(      wxVariant&, unsigned int row, unsigned int col) const;
    virtual bool SetValueByRow(const wxVariant&, unsigned int row, unsigned int col);
    virtual bool GetValueByRow(      wxString* , unsigned int row, unsigned int col) const;
    virtual bool SetValueByRow(const wxString& , unsigned int row, unsigned int col);
    virtual size_t GetProperties(wxArrayString*, bool header) const;
    virtual bool IsOpen() const;
    virtual bool IsEditable() const;
    virtual bool AddNew();
    virtual wxString GetDataModelName() const;
    virtual wxString GetTableName() const;
    virtual bool IsRowDeleted(unsigned int row);
    virtual bool DeleteRow(unsigned int row, bool bDelete = true);

#if (wxVERSION_NUMBER >= 2902)
    virtual bool GetAttrByRow(unsigned int row, unsigned int col, wxDataViewItemAttr&) const;
    virtual void GetValue(wxVariant&, const wxDataViewItem&, unsigned int col) const;
#endif
protected:
    bool m_delete_on_exit;
private:
    wxDBase* m_database;
};

#endif // __DBFMODEL_H__
