#include "stdafx.h"
#include "Archive.h"
#include "wx/mstream.h"
#include "wx/datstrm.h"


CArchive::CArchive(const wxString& fileName, bool bStoring) : m_bStoring(bStoring), m_stream(fileName), wxDataOutputStream(m_stream), wxDataInputStream(m_stream)
{
}

CArchive::CArchive(wxMemoryOutputStream *pStream, bool bStoring): m_bStoring(bStoring), wxDataOutputStream(*pStream), wxDataInputStream(wxMemoryInputStream(*pStream)), m_stream(_T(""))
{
}


CArchive::~CArchive()
{
}
