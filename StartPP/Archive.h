#pragma once
#include "wx/datstrm.h"
#include "wx/wfstream.h"

class CArchive :
	public wxDataOutputStream, public wxDataInputStream
{
	wxFileStream m_stream;
	bool m_bStoring;
public:
	CArchive(const wxString& fileName, bool m_bStoring);
	~CArchive();
	bool IsStoring() { return m_bStoring; };
};

