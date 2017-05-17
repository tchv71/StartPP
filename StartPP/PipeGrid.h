#pragma once

#include "stdafx.h"
#include <wx/grid.h>
#include "StartPPDoc.h"

class PipeGrid : public wxGrid
{
protected:
	bool m_bExternalSelection;
	wxDECLARE_EVENT_TABLE();
	wxGridTableBase* m_pTable;
public:
	PipeGrid(wxWindow *pWin, wxStandardID id, const wxPoint point, wxSize size, int i);

	virtual ~PipeGrid();
	void SetColFormat();
	void ResetTable();
	void RefreshGrid(CStartPPDoc *pDoc);


	void OnGridSelectCell(wxGridEvent& event);
	void OnGridRangeSelect(wxGridRangeSelectEvent& event);
	void BeginSelect() { m_bExternalSelection = true; }
	void EndSelect() { m_bExternalSelection = false; }

};

