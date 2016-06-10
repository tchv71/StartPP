#pragma once
#include "wx/datstrm.h"
#include "wx/wfstream.h"
#include "wx/mstream.h"

class wxMemoryOutputStream;

class CArchive :
	public wxDataOutputStream, public wxDataInputStream
{
	wxFileStream m_stream;
	wxMemoryInputStream m_memistream;
	bool m_bStoring;
public:
	enum { store = 1, load = 0 };
	CArchive(const wxString& fileName, bool m_bStoring);
	CArchive(wxMemoryOutputStream *pStream, bool m_bStoring);
	void Close() { m_stream.Close(); }
	~CArchive();
	bool IsStoring() { return m_bStoring; };
};

