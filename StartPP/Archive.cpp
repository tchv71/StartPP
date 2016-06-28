#include "stdafx.h"
#include "Archive.h"
#include "wx/mstream.h"
#include "wx/datstrm.h"


CArchive::CArchive(const wxString& fileName, bool bStoring) :
	m_bStoring(bStoring), m_stream(fileName), m_memistream(m_stream),
	wxDataOutputStream(m_stream), wxDataInputStream(m_stream)
{
}

CArchive::CArchive(bool bStoring): 
	m_bStoring(bStoring), m_memistream(nullptr, 0), wxDataOutputStream(m_memostream),
	wxDataInputStream(m_memistream), m_stream(_T(""))
{
}

CArchive::CArchive(wxMemoryInputStream *pStream, bool bStoring) :
	m_bStoring(bStoring), m_memistream(*pStream), wxDataOutputStream(m_memostream),
	wxDataInputStream(m_memistream), m_stream(_T(""))
{
}


CArchive::~CArchive()
{
}
