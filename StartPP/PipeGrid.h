#pragma once

#include <wx/grid.h>

class PipeGrid : public wxGrid
{
public:
	PipeGrid();

	PipeGrid(wxWindow *pWin, wxStandardID id, const wxPoint point, wxSize size, int i);

	~PipeGrid();
	void SetColFormat();
};

