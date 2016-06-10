#include "stdafx.h"
#include "PropertiesWnd.h"
#include "StartPPDoc.h"
#include "MainFrame.h"
#include "Strings.h"
#include <wx/fileconf.h>

CStartPPDoc::CStartPPDoc()
{
}

CStartPPDoc::~CStartPPDoc()
{

}

void CStartPPDoc::OnRecordNext()
{
	if (m_pipes.m_nIdx == m_pipes.m_vecPnN.size() - 1)
		return;
	m_pipes.m_nIdx++;
	SyncSel();
}


void CStartPPDoc::OnRecordPrev()
{
	if (m_pipes.m_nIdx == 0)
		return;
	m_pipes.m_nIdx--;
	SyncSel();
}

void CStartPPDoc::SyncSel(void)
{
	UpdateData(TRUE);
	CPipeAndNode& p = m_pipes.CurPipe();
	vecSel.clear();
	vecSel.SelNAYZ = int(m_pFrame->GetPropWnd()->m_PropMode == E_NODE ? p.m_KOYZ : p.m_NAYZ);
	vecSel.SelKOYZ = int(p.m_KOYZ);
	vecSel.insert(SelStr(vecSel.SelNAYZ, vecSel.SelKOYZ));
	UpdateData(FALSE);
}


BOOL CStartPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPipeAndNode p;
	p.m_KOYZ = 1;
	p.m_MNEO = _T("мо");
	m_pipes.m_vecPnN.push_back(p);
	p.m_MNEO = _T("");
	p.m_RADA = 16.0f;
	p.m_RATE = 150.0f;
	p.m_KOPE = 0.8f;
	p.m_NAMA = _T("20");
	p.m_KOPR = 1.0f;
	p.m_OSIX = 1.0f;
	p.m_NAYZ = 1;
	p.m_KOYZ = 2;
	m_pipes.m_vecPnN.push_back(p);
	m_pipes.m_nIdx = 1;
	vecSel.insert(SelStr(1, 2));
	m_pFrame->GetPropWnd()->m_PropMode = E_PIPE;

	UpdateAllViews(nullptr);
	UpdateData(FALSE);
	return TRUE;
}

void CStartPPDoc::OnImportDbf()
{
	wxFileDialog dlg(m_pFrame, wxFileSelectorPromptStr, wxEmptyString, wxEmptyString, "*i.dbf");
	wxFileConfig fcf(_T("StartPP"),wxEmptyString,_T("StartPP"),wxEmptyString,wxCONFIG_USE_LOCAL_FILE);
	CString strDir; //AfxGetApp()->GetProfileString(_T("Settings"), _T("ImportDbf"));
	fcf.Read(_T("ImportDbf"),&strDir,_T(""));
	if (!strDir.IsEmpty())
		dlg.SetDirectory(strDir);
	//	dlg.m_ofn.lpstrInitialDir = strDir;
	if (dlg.ShowModal() == wxID_OK)
	{
		//AfxGetApp()->m_pDocManager->OpenDocumentFile(nullptr,FALSE);
		CString strFile = dlg.GetFilename();
		//SetTitle(strFile);
		CString strFolder = dlg.GetDirectory();
		//AfxGetApp()->WriteProfileString(_T("Settings"), _T("ImportDbf"), strFolder);
		fcf.Write(_T("ImportDbf"), strFolder);
		fcf.Flush();
		m_StartPPSet.m_strPath = strFolder;
		m_StartPPSet.m_strTable = strFile;
		//m_strPathName = strFolder + _T("/") + strFile;
		m_pipes.m_vecPnN.clear();
		m_pipes.m_nIdx = 0;
		try
		{
			m_StartPPSet.SetOldSet(false);
			m_StartPPSet.Open();
		}
		catch (std::exception)
		{
			m_StartPPSet.SetOldSet(true);
			m_StartPPSet.Open();
			//e->Delete();
		}
		while (!m_StartPPSet.IsEOF())
		{
			m_pipes.m_vecPnN.push_back(m_StartPPSet);
			m_StartPPSet.MoveNext();
		}
		m_StartPPSet.Close();

		/*		POSITION pos = GetFirstViewPosition();
				while (pos != nullptr)
				{
					CView* pView = GetNextView(pos);
					ASSERT_VALID(pView);
					pView->OnInitialUpdate();
				}
        */
		UpdateData(FALSE);
	}
	else
		OnCloseDocument();
}

void CStartPPDoc::SetUndo(void)
{
	if (m_vecUndo.size() != 0 && m_pipes.m_vecPnN.size() == m_vecUndo[m_vecUndo.size() - 1].vec.m_vecPnN.size())
	{
		std::vector<CPipeAndNode>& vecTop = m_vecUndo[m_vecUndo.size() - 1].vec.m_vecPnN;
		unsigned i;
		for (i = 0; i < vecTop.size(); i++)
		{
			if (memcmp(&vecTop[i], &m_pipes.m_vecPnN[i], sizeof(CPipeAndNode)) != 0)
				break;
		}
		if (i == vecTop.size())
			return;
	}
	m_vecUndo.push_back(SUndo(m_pipes, vecSel));
	m_nUndoPos = m_vecUndo.size() - 1;
}



void CStartPPDoc::UpdateData(bool bSaveAndValidate)
{
	CDataExchange dx(m_pFrame, bSaveAndValidate);
	m_pFrame->GetPropWnd()->DoDataExchange(&dx, &m_pipes.CurPipe(), this);
	//m_pFrame->m_wndPipeTable.DoDataExchange(&dx, this);
	if (!bSaveAndValidate)
	{
		SetUndo();
		UpdateAllViews(nullptr); // Selection is changed
	}
}

void CStartPPDoc::PnNIsUpdated(void)
{
	m_bModified = true;
	SetUndo();
	UpdateAllViews(nullptr);
}


CPipeAndNode* CStartPPDoc::GetPrevPnN(int NAYZ)
{
	for (unsigned i = 0; i < m_pipes.m_vecPnN.size(); i++)
		if (fabs(m_pipes.m_vecPnN[i].m_KOYZ - NAYZ) < 1e-3f)
			return &m_pipes.m_vecPnN[i];
	return nullptr;
}


void CStartPPDoc::RotateThisAndOthers(float fAngle)
{
	m_bvecRotated.resize(m_pipes.m_vecPnN.size());
	for (unsigned i = 0; i < m_bvecRotated.size(); i++)
		m_bvecRotated[i] = false;
	RotateOne(m_pipes.m_nIdx, fAngle);
	RotateAll(int(m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ), fAngle);
}

void CStartPPDoc::RotateThisAndOthers(CPipeAndNode* pPnN, float fAngle)
{
	m_bvecRotated.resize(m_pipes.m_vecPnN.size());
	int nIdx = 0;
	for (unsigned i = 0; i < m_bvecRotated.size(); i++)
	{
		m_bvecRotated[i] = false;
		if (pPnN->m_NAYZ == m_pipes.m_vecPnN[i].m_NAYZ && pPnN->m_KOYZ == m_pipes.m_vecPnN[i].m_KOYZ)
			nIdx = i;
	}
	RotateOne(nIdx, fAngle);
	RotateAll(int(m_pipes.m_vecPnN[nIdx].m_KOYZ), fAngle);
}


extern float Round(float x, int N);


void CStartPPDoc::RotateOne(size_t recNo, float fAngle)
{
	float x, y, x1, y1;
	x = m_pipes.m_vecPnN[recNo].m_OSIX;
	y = m_pipes.m_vecPnN[recNo].m_OSIY;
	m_bvecRotated[recNo] = true;
	x1 = Round(x * cos(fAngle) - y * sin(fAngle), 3);
	y1 = Round(x * sin(fAngle) + y * cos(fAngle), 3);
	m_pipes.m_vecPnN[recNo].m_OSIX = x1;
	m_pipes.m_vecPnN[recNo].m_OSIY = y1;
}


void CStartPPDoc::RotateAll(int NAYZ, float fAngle)
{
	unsigned i = 0;
	bool bFound = false;
	for (; i < m_pipes.m_vecPnN.size(); i++)
		if (fabs(m_pipes.m_vecPnN[i].m_NAYZ - NAYZ) < 1e-3f)
		{
			bFound = true;
			break;
		}
	while (bFound)
	{
		if (!m_bvecRotated[i])
		{
			RotateOne(i, fAngle);
			RotateAll(int(m_pipes.m_vecPnN[i].m_KOYZ), fAngle);
		}
		i++;
		bFound = false;
		for (; i < m_pipes.m_vecPnN.size(); i++)
			if (fabs(m_pipes.m_vecPnN[i].m_NAYZ - NAYZ) < 1e-3f)
			{
				bFound = true;
				break;
			}
	}
}


void CStartPPDoc::Select(int NAYZ, int KOYZ)
{
	vecSel.SelNAYZ = NAYZ;
	vecSel.SelKOYZ = KOYZ;
	if (NAYZ < 0 || KOYZ < 0)
	{
		vecSel.clear();
		return;
	}
	if (vecSel.size() == 0)
	{
		vecSel.insert(SelStr(NAYZ, KOYZ));
	}
	else if (vecSel.size() == 1)
	{
		vecSel.clear();
		vecSel.insert(SelStr(NAYZ, KOYZ));
	}
	if (NAYZ == KOYZ)
	{
		for (unsigned i = 0; i < m_pipes.m_vecPnN.size(); i++)
			if (fabs(m_pipes.m_vecPnN[i].m_KOYZ - NAYZ) < 1e-3f)
			{
				UpdateData(TRUE);
				m_pipes.m_nIdx = i;
				m_pFrame->GetPropWnd()->m_PropMode = E_NODE;
				UpdateData(FALSE);
				break;
			}
		return;
	}

	for (unsigned i = 0; i < m_pipes.m_vecPnN.size(); i++)
		if (fabs(m_pipes.m_vecPnN[i].m_NAYZ - NAYZ) < 1e-3f && fabs(m_pipes.m_vecPnN[i].m_KOYZ - KOYZ) < 1e-3f)
		{
			UpdateData(TRUE);
			m_pipes.m_nIdx = i;
			m_pFrame->GetPropWnd()->m_PropMode = E_PIPE;
			UpdateData(FALSE);
			break;
		}
}

void CStartPPDoc::UpdateAllViews(void *)
{
}

void CStartPPDoc::Serialize(CArchive& ar)
{
	UNREFERENCED_PARAMETER(ar);
}

#ifdef _DEBUG
void CStartPPDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CStartPPDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

void CStartPPDoc::DeleteSelected(void)
{
	std::vector<CPipeAndNode> vecRemained;
	std::vector<CPipeAndNode> vecSelected;
	for (auto& x : m_pipes.m_vecPnN)
	{
		if (!vecSel.Contains(x.m_NAYZ, x.m_KOYZ))
			vecRemained.push_back(x);
		else
			vecSelected.push_back(x);
	}
	CPipeArray arrRemained;
	arrRemained.copy_pipes(vecRemained);
	if (!arrRemained.CheckConnectivity())
	{
		if (AfxMessageBox(LoadStr(IDS_UNITE_NODES_Q), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			while (!vecSelected.empty())
			{
				CPipeArray arrSelected(vecSelected);
				std::set<int> setSelNodes;
				arrSelected.CheckConnectivity();
				std::multimap<int, Pipe>& pipes = arrSelected.GetPipes();
				for (auto& x : pipes)
					if (x.second.Drawed)
					{
						setSelNodes.insert(x.second.StrP);
						setSelNodes.insert(x.second.EndP);
						for (auto its = vecSelected.begin(); its != vecSelected.end(); ++its)
							if (int(its->m_NAYZ) == x.second.StrP && int(its->m_KOYZ) == x.second.EndP)
							{
								vecSelected.erase(its);
								break;
							}
					}
				std::set<int> setNodesUnite;
				for (auto& x : setSelNodes)
					if (arrRemained.InCount(x) > 0 || arrRemained.OutCount(x) > 0)
						setNodesUnite.insert(x);
				int nNewNum = *setNodesUnite.begin();
				for (auto it = vecRemained.begin(); it != vecRemained.end(); ++it)
				{
					if (setNodesUnite.find(int(it->m_NAYZ)) != setNodesUnite.end())
						it->m_NAYZ = float(nNewNum);
					if (setNodesUnite.find(int(it->m_KOYZ)) != setNodesUnite.end())
						it->m_KOYZ = float(nNewNum);
				}
			}
		}
	}
	vecSel.clear();
	vecSel.SelNAYZ = vecSel.SelKOYZ = -1;
	m_pipes.m_vecPnN = vecRemained;
	m_pipes.m_nIdx = 0;
	PnNIsUpdated();
}

bool CStartPPDoc::IsSelConnected(void)
{
	std::vector<CPipeAndNode> vecCopy;
	for (auto it = m_pipes.m_vecPnN.begin(); it != m_pipes.m_vecPnN.end(); ++it)
		if (vecSel.Contains(it->m_NAYZ, it->m_KOYZ))
			vecCopy.push_back(*it);
	CPipeArray pipeArr;
	pipeArr.copy_pipes(vecCopy);
	return pipeArr.CheckConnectivity();
}
