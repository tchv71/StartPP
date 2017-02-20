#include "stdafx.h"
#include <wx/window.h>
#include "PipeGrid.h"
#include "PipeTable.h"
#include "Material.h"

PipeGrid::PipeGrid()
{
}

PipeGrid::~PipeGrid()
{
}

PipeGrid::PipeGrid(wxWindow *pWin, wxStandardID id, const wxPoint point, wxSize size, int i) :
		wxGrid(pWin, id, point, size,i)
{
	UseNativeColHeader(true);
}

void PipeGrid::SetColFormat()
{
	SetColFormatFloat(0,-1,3);
	SetColFormatFloat(1,-1,3);
	SetColFormatFloat(2,-1,3);
	SetColFormatFloat(3,-1,3);
	SetColFormatFloat(4,-1,3);
	SetColFormatFloat(5,-1,1);
	SetColFormatFloat(6,-1,1);
	SetColFormatFloat(7,-1,1);
	SetColFormatFloat(8,-1,0);
	SetColFormatFloat(9,-1,0);
    for (int i=0;i<GetNumberRows();i++)
    {
         CMaterial setMaterial;
         setMaterial.m_strPath = DATA_PATH;
         setMaterial.m_strTable = _T("Matup.dbf");// _T("[MATUP]  order by NOM");
         setMaterial.Open();
         wxArrayString ar;
         while (!setMaterial.IsEOF())
         {
             ar.Add(CString(setMaterial.m_MAT));
             setMaterial.MoveNext();
         }
         wxGridCellEditor* pEdit = new wxGridCellChoiceEditor(ar);
         SetCellEditor(i, 10, pEdit);
    }
	SetColFormatFloat(11,-1,1);
	SetColFormatFloat(12,-1,2);
	SetColFormatFloat(13,-1,1);
	SetColFormatFloat(14,-1,1);
	SetColFormatFloat(15,-1,1);

}

