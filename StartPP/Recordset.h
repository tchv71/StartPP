#pragma once
#include "wx/object.h"
#include "dbf_wx.h"
#include "stdafx.h"

class CRecordset;
#define SQL_VARCHAR 1

/*============================================================================*/
// CFieldExchange - for field exchange
class CFieldExchange
{
	// Attributes
public:
	enum RFX_Operation
	{
		BindParam,          // register users parameters with ODBC SQLBindParameter
		RebindParam,        //  migrate param values to proxy array before Requery
		BindFieldToColumn,  // register users fields with ODBC SQLBindCol
		BindFieldForUpdate, // temporarily bind columns before update (via SQLSetPos)
		UnbindFieldForUpdate,   // unbind columns after update (via SQLSetPos)
		Fixup,              // Set string lengths, clear status bits
		MarkForAddNew,      // Prepare fields and flags for addnew operation
		MarkForUpdate,      // Prepare fields and flags for update operation
		Name,               // append dirty field name
		NameValue,          // append dirty name=value
		Value,              // append dirty value or parameter marker
		SetFieldNull,       // Set status bit for null value
		StoreField,         // archive values of current record
		LoadField,          // reload archived values into current record
		AllocCache,         // allocate cache used for dirty field check
		AllocMultiRowBuffer,    // allocate buffer holding multi rows of data
		DeleteMultiRowBuffer,   // delete buffer holding multi rows of data
#ifdef _DEBUG
		DumpField,          // dump bound field name and value
#endif
	};
	UINT m_nOperation;  // Type of exchange operation
	//CRecordset* m_prs;  // recordset handle

	enum {
		SQL_PARAM_INPUT,
		SQL_PARAM_OUTPUT,
		SQL_PARAM_INPUT_OUTPUT
	};
	// Operations
	enum FieldType
	{
		noFieldType = -1,
		outputColumn = 0,
		param = SQL_PARAM_INPUT,
		inputParam = param,
		outputParam = SQL_PARAM_OUTPUT,
		inoutParam = SQL_PARAM_INPUT_OUTPUT,
	};

	// Indicate purpose of subsequent RFX calls
	void SetFieldType(UINT nFieldType)
	{
		UNREFERENCED_PARAMETER(nFieldType);
	};

	// Implementation
};



class CDumpContext;
class CDatabase;

class CRecordset : public wxObject
{
	CString m_strDefaultConnect;
	CString m_strDefaultSQL;
    wxDBase m_dbf;
    bool m_bIsEOF;
    CFieldExchange m_fieldExchange;
public:
	CRecordset(CDatabase* pdb);
	~CRecordset();
	int m_nFields;
	enum { dynaset } m_nDefaultType;

	virtual CString GetDefaultConnect() { return m_strDefaultConnect; };
	virtual CString GetDefaultSQL() { return m_strDefaultSQL; };
	virtual void DoFieldExchange(CFieldExchange* pFX)
	{
		UNREFERENCED_PARAMETER(pFX);
	}
	bool Open();
	bool IsEOF();
	void MoveNext();
	void Close();
    void RFX_Single(CFieldExchange* pFX, LPCTSTR szName, float& value);
    void RFX_Text(CFieldExchange* pFX, LPCTSTR szName, CStringA &value,
        // Default max length for char and varchar, default datasource type
        int nMaxLength = 255, int nColumnType = SQL_VARCHAR, short nScale = 0);
    // boolean data
    void RFX_Bool(CFieldExchange* pFX, LPCTSTR szName, BOOL& value);
    void RFX_Int(CFieldExchange* pFX, LPCTSTR szName, int& value);

#ifdef _DEBUG
	virtual void AssertValid() const {};
	virtual void Dump(CDumpContext& dc) const
	{
		UNREFERENCED_PARAMETER(dc);
	};
#endif
};