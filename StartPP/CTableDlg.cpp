#include "stdafx.h"
#include "CTableDlg.h"

CTableDlg::CTableDlg(CWnd* pParent, LPCTSTR pszDbfName, LPCTSTR pszCopyDbfName) :
	CPipesTableBaseDlg(pParent),
	m_strDbfName(pszDbfName),
	m_strCopyDbfName(pszCopyDbfName),
	m_menu(nullptr)
{
}

CTableDlg::~CTableDlg()
{
}

BOOL CTableDlg::OnInitDialog()
{
	wxCopyFile(m_strDbfName, m_strCopyDbfName);
	return TRUE;
}

void CTableDlg::EndModal(int retcode)
{
	if (retcode == wxID_OK)
	{
		wxCopyFile(m_strCopyDbfName, m_strDbfName);
	}
	wxRemoveFile(m_strCopyDbfName);
	CTableDlg::EndModal(retcode);
}
