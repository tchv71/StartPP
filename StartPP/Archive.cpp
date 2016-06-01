#include "stdafx.h"
#include "Archive.h"


CArchive::CArchive(const wxString& fileName, bool bStoring) : m_bStoring(bStoring), m_stream(fileName), wxDataOutputStream(m_stream), wxDataInputStream(m_stream)
{
}


CArchive::~CArchive()
{
}
