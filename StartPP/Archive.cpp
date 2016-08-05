#include "stdafx.h"
#include "Archive.h"
#include "wx/mstream.h"
#include "wx/datstrm.h"



CArchive::CArchive(bool bStoring): 
	m_bStoring(bStoring), m_memistream(nullptr, 0), wxDataOutputStream(m_memostream),
	wxDataInputStream(m_memistream)
{
}

CArchive::CArchive(wxMemoryInputStream *pStream, bool bStoring) :
	m_bStoring(bStoring), m_memistream(*pStream), wxDataOutputStream(m_memostream),
	wxDataInputStream(m_memistream)
	//, m_stream(_T(""))
{
}

CArchive::CArchive(wxFileOutputStream& stream, bool bStoring) : wxDataOutputStream(stream), wxDataInputStream(m_memistream),
	//m_stream(_T("")),
	m_memistream(nullptr, 0),
	m_bStoring(bStoring)
{
}

CArchive::CArchive(wxFileInputStream& stream, bool bStoring) :
	//m_stream(_T("")),
	wxDataInputStream(stream),
	wxDataOutputStream(wxOutputStream()), 
	m_memistream(nullptr, 0),
	m_bStoring(bStoring)
{
}

CArchive::~CArchive()
{
}
