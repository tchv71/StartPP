#pragma once
#include "wx/datstrm.h"
#include "wx/wfstream.h"
#include "wx/mstream.h"

class wxMemoryOutputStream;

class CArchive :
	public wxDataOutputStream, public wxDataInputStream
{
protected:
	wxMemoryInputStream m_memistream;
	wxMemoryOutputStream m_memostream;
    wxOutputStream m_output;
	bool m_bStoring;
public:
	enum { store = 1, load = 0 };
	//CArchive(const wxString& fileName, bool m_bStoring);
	//CArchive(bool m_bStoring);
	CArchive(wxMemoryInputStream *pStream, bool m_bStoring);
	CArchive(wxFileOutputStream& stream, bool bStoring=true);
	CArchive(wxFileInputStream& stream, bool bStoring = false);
	~CArchive();
	bool IsStoring() { return m_bStoring; };
};

