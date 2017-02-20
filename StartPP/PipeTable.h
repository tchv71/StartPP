#pragma once

#include <wx/generic/grid.h>
#include "StartPPDoc.h"

class PipeTable : public wxGridTableBase
{
public:
    virtual wxString GetValue(int row, int col) wxOVERRIDE;
    virtual void SetValue(int row, int col, const wxString& value) wxOVERRIDE;
    PipeTable();
    ~PipeTable();

    int GetNumberRows() wxOVERRIDE;
    int GetNumberCols() wxOVERRIDE;

	CStartPPDoc * GetCurDoc();

	virtual wxString GetRowLabelValue(int row) wxOVERRIDE;

	virtual wxString GetColLabelValue(int col) wxOVERRIDE;

	wxString GetTypeName(int row, int col) override;

	void SetValueAsDouble(int row, int col, double value) override;

	bool CanSetValueAs(int row, int col, const wxString &typeName) override;
};
