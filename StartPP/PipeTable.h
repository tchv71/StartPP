#pragma once

#include <wx/generic/grid.h>
#include "StartPPDoc.h"

class PipeTable : public wxGridTableBase
{
protected:
	CPipeAndNode * getPipeAndNode(int row, CStartPPDoc *&pDoc) const;
	CStartPPDoc * GetCurDoc() const;

public:
	PipeTable();
	~PipeTable();

	double GetValueAsDouble(int row, int col) wxOVERRIDE;
	bool GetValueAsBool(int row, int col) wxOVERRIDE;
	void SetValueAsBool(int row, int col, bool value) wxOVERRIDE;
	wxString GetValue(int row, int col) wxOVERRIDE;
    void SetValue(int row, int col, const wxString& value) wxOVERRIDE;

    int GetNumberRows() wxOVERRIDE;
    int GetNumberCols() wxOVERRIDE;


	wxString GetRowLabelValue(int row) wxOVERRIDE;
	wxString GetColLabelValue(int col) wxOVERRIDE;
	wxString GetTypeName(int row, int col) wxOVERRIDE;
	void SetValueAsDouble(int row, int col, double value) wxOVERRIDE;
	bool CanGetValueAs(int row, int col, const wxString& typeName) wxOVERRIDE;
	bool CanSetValueAs(int row, int col, const wxString &typeName) wxOVERRIDE;
};
