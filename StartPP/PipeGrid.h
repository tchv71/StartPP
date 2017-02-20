#pragma once

#include <wx/grid.h>

class PipeGrid : public wxGrid
{
protected:
	bool m_bExternalSelection;
	wxDECLARE_EVENT_TABLE();

public:
	PipeGrid(wxWindow *pWin, wxStandardID id, const wxPoint point, wxSize size, int i);

	virtual ~PipeGrid();
	void SetColFormat();

	void OnGridSelectCell(wxGridEvent& event);
	void OnGridRangeSelect(wxGridRangeSelectEvent& event);
	void BeginSelect() { m_bExternalSelection = true; }
	void EndSelect() { m_bExternalSelection = false; }
};

