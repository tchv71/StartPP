// StartPPDoc.cpp : реализация класса CStartPPDoc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "StartPP.h"
#endif


#include "MainFrm.h"
#include "StartPPDoc.h"
#include "NewPipeDialog.h"
#include "DelPipesDialog.h"
#include "MultPipeDialog.h"
#include "CopyParamsDialog.h"
#include "NewNodeDialog.h"
#include "MoveNodeDialog.h"
#include "Pipe.h"
#include "PipeDescDialog.h"
#include "PipesTableDlg.h"
#include "ArmatTableDlg.h"
#include "TroinicsTableDlg.h"
#include "SpuskDialog.h"
#include <propkey.h>
#include <math.h>
#include "AddSchemDlg.h"
#include "Shlwapi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CStartPPDoc

IMPLEMENT_DYNCREATE(CStartPPDoc, CDocument)

BEGIN_MESSAGE_MAP(CStartPPDoc, CDocument)
	ON_COMMAND(ID_RECORD_FIRST, &CStartPPDoc::OnRecordFirst)
	ON_COMMAND(ID_RECORD_LAST, &CStartPPDoc::OnRecordLast)
	ON_COMMAND(ID_RECORD_NEXT, &CStartPPDoc::OnRecordNext)
	ON_COMMAND(ID_RECORD_PREV, &CStartPPDoc::OnRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, &CStartPPDoc::OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, &CStartPPDoc::OnUpdateRecordPrev)
	ON_COMMAND(ID_NEW_PIPE, &CStartPPDoc::OnNewPipe)
	ON_COMMAND(ID_DEL_PIPE, &CStartPPDoc::OnDelPipe)
	ON_COMMAND(ID_MULT_PIPE, &CStartPPDoc::OnMultPipe)
	ON_COMMAND(ID_COPY_PIPE_PARAMS, &CStartPPDoc::OnCopyPipeParams)
	ON_COMMAND(ID_INVERT_PIPE, &CStartPPDoc::OnInvertPipe)
	ON_COMMAND(ID_NEW_NODE, &CStartPPDoc::OnNewNode)
	ON_COMMAND(ID_DEL_NODE, &CStartPPDoc::OnDelNode)
	ON_COMMAND(ID_MOVE_NODE, &CStartPPDoc::OnMoveNode)
	ON_COMMAND(ID_RENUM_PIPES, &CStartPPDoc::OnRenumPipes)
	ON_COMMAND(ID_UNDO, &CStartPPDoc::OnUndo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, &CStartPPDoc::OnUpdateUndo)
	ON_COMMAND(ID_REDO, &CStartPPDoc::OnRedo)
	ON_UPDATE_COMMAND_UI(ID_REDO, &CStartPPDoc::OnUpdateRedo)
	//ON_COMMAND(ID_IMPORT_DBF, &CStartPPDoc::OnImportDbf)
	ON_COMMAND(ID_PIPE_DESC, &CStartPPDoc::OnPipeDesc)
	ON_COMMAND(ID_EXPORT_INI, &CStartPPDoc::OnExportIni)
	ON_COMMAND(ID_PIPE_TABLE, &CStartPPDoc::OnPipeTable)
	ON_COMMAND(ID_ARMAT_TABLE, &CStartPPDoc::OnArmatTable)
	ON_COMMAND(ID_TROINICS_TABLE, &CStartPPDoc::OnTroinicsTable)
	ON_COMMAND(ID_Spusk, &CStartPPDoc::OnSpusk)
	ON_COMMAND(ID_ADD_SCHEM, &CStartPPDoc::OnAddSchem)
	ON_COMMAND(ID_EDIT_PASTE, &CStartPPDoc::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CStartPPDoc::OnUpdateEditPaste)
	END_MESSAGE_MAP()

extern LPCTSTR LoadStr(UINT nID);


// создание/уничтожение CStartPPDoc

CStartPPDoc::CStartPPDoc(): m_nUndoPos(-1)
{
	m_pFrame = static_cast<CMainFrame *>(AfxGetApp()->m_pMainWnd);
	m_nClipFormat = RegisterClipboardFormat(_T("STARTPP_PIPE"));
}

CStartPPDoc::~CStartPPDoc()
{
}

BOOL CStartPPDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CPipeAndNode p;
	p.m_KOYZ = 1;
	p.m_MNEO = "мо";
	m_pipes.m_vecPnN.push_back(p);
	p.m_MNEO = "";
	p.m_RADA = 16.0f;
	p.m_RATE = 150.0f;
	p.m_KOPE = 0.8f;
	p.m_KOPR = 1.0f;
	p.m_OSIX = 1.0f;
	p.m_KOYZ = 2;
	p.m_NAYZ = 1;
	m_pipes.m_vecPnN.push_back(p);
	m_pipes.m_nIdx = 1;

	UpdateAllViews(nullptr);
	UpdateData(FALSE);
	return TRUE;
}


// сериализация CStartPPDoc

void CStartPPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		UpdateData(TRUE);
		m_PipeDesc.Serialize(ar);
		m_pipes.Serialize(ar);
	}
	else
	{
		m_PipeDesc.Serialize(ar);
		m_pipes.Serialize(ar);
		UpdateData(FALSE);
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CStartPPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CStartPPDoc::InitializeSearchContent()
{
	CString strSearchContent;
// Задайте содержимое поиска из данных документа. 
// Части содержимого должны разделяться точкой с запятой ";"

// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CStartPPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS


// диагностика CStartPPDoc

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



// команды CStartPPDoc


void CStartPPDoc::OnRecordFirst()
{
	m_pipes.m_nIdx = 0;
	SyncSel();
}


void CStartPPDoc::OnRecordLast()
{
	m_pipes.m_nIdx = m_pipes.m_vecPnN.size() - 1;
	SyncSel();
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


void CStartPPDoc::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pipes.m_nIdx != m_pipes.m_vecPnN.size() - 1);
}


void CStartPPDoc::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pipes.m_nIdx != 0);
}


void CStartPPDoc::UpdateData(bool bSaveAndValidate)
{
	CDataExchange dx(m_pFrame, bSaveAndValidate);
	m_pFrame->m_wndProperties.DoDataExchange(&dx, &m_pipes.CurPipe(), this);
	m_pFrame->m_wndPipeTable.DoDataExchange(&dx, this);
	if ( !bSaveAndValidate)
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
				m_pFrame->m_wndProperties.m_PropMode = E_NODE;
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
			m_pFrame->m_wndProperties.m_PropMode = E_PIPE;
			UpdateData(FALSE);
			break;
		}
}


void CStartPPDoc::OnNewPipe()
{
	CPipes pipes(m_pipes.m_nIdx, m_pipes.m_vecPnN);
	CNewPipeDialog dlg(nullptr, pipes);
	if (dlg.DoModal() == IDOK)
	{
		m_bModified = true;
		UpdateAllViews(nullptr);
		UpdateData(FALSE);
	}
}


void CStartPPDoc::OnDelPipe()
{
	CDelPipesDialog dlg(nullptr, this);
	dlg.DoModal();
}


void CStartPPDoc::OnMultPipe()
{
	CPipes pipes(m_pipes.m_nIdx, m_pipes.m_vecPnN);
	CMultPipeDialog dlg(nullptr, pipes);
	if (dlg.DoModal() == IDOK)
	{
		m_bModified = true;
		UpdateAllViews(nullptr);
		UpdateData(FALSE);
	}
}


void CStartPPDoc::OnCopyPipeParams()
{
	CPipes pipes(m_pipes.m_nIdx, m_pipes.m_vecPnN);
	CCopyParamsDialog dlg(nullptr, pipes);
	if (dlg.DoModal() == IDOK)
	{
		m_bModified = true;
		UpdateAllViews(nullptr);
		UpdateData(FALSE);
	}
}


void CStartPPDoc::OnInvertPipe()
{
	CPipeAndNode& p = m_pipes.m_vecPnN[m_pipes.m_nIdx];
	float n = p.m_KOYZ;
	p.m_KOYZ = p.m_NAYZ;
	p.m_NAYZ = n;
	p.m_OSIX = -p.m_OSIX;
	p.m_OSIY = -p.m_OSIY;
	p.m_OSIZ = -p.m_OSIZ;
	UpdateAllViews(nullptr);
	UpdateData(FALSE);
}


void CStartPPDoc::OnNewNode()
{
	CPipes pipes(m_pipes.m_nIdx, m_pipes.m_vecPnN);
	CNewNodeDialog dlg(nullptr, pipes);
	if (dlg.DoModal() == IDOK)
	{
		m_bModified = true;
		UpdateAllViews(nullptr);
		UpdateData(FALSE);
	}
}


void CStartPPDoc::OnDelNode()
{
	CString str;
	int nKOYZ = int(m_pipes.m_vecPnN[m_pipes.m_nIdx].m_KOYZ);
	str.Format(LoadStr(IDS_DELETE_NODE_Q), nKOYZ);
	if (AfxMessageBox(str, MB_OKCANCEL) == IDCANCEL)
		return;
	CPipes pipes(m_pipes.m_nIdx, m_pipes.m_vecPnN);
	if (!pipes.FindFirstKOYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_NO_PIPES_UZ), nKOYZ);
		AfxMessageBox(str);
		return;
	}
	if (pipes.FindNextKOYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_2PIPES_IN), nKOYZ);
		AfxMessageBox(str);
		return;
	}

	if (!pipes.FindFirstNAYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_NO_PIPES_OUT), nKOYZ);
		AfxMessageBox(str);
		return;
	}
	if (pipes.FindNextNAYZ(nKOYZ))
	{
		str.Format(LoadStr(IDS_MN_2_PIPES_OUT), nKOYZ);
		AfxMessageBox(str);
		return;
	}
	CPipeAndNode p = m_pipes.m_vecPnN[m_pipes.m_nIdx];
	float dx1 = p.m_OSIX,
		dy1 = p.m_OSIY,
		dz1 = p.m_OSIZ,
		Len1 = sqrt(dx1 * dx1 + dy1 * dy1 + dz1 * dz1);
	pipes.FindFirstNAYZ(nKOYZ);
	CPipeAndNode& p1 = m_pipes.m_vecPnN[pipes.m_SearchIdx];
	//int NewEndNode=int(p1.m_KOYZ);
	float dx2 = p1.m_OSIX,
		dy2 = p1.m_OSIY,
		dz2 = p1.m_OSIZ,
		Len2 = sqrt(dx2 * dx2 + dy2 * dy2 + dz2 * dz2);

	if (fabs(Len1) < 0.001 || fabs(Len2) < 0.001)
	{
		AfxMessageBox(LoadStr(IDS_MN_NULL_LEN));
		return;
	}
	if (fabs(dx1 / Len1 - dx2 / Len2) > 0.001 || fabs(dy1 / Len1 - dy2 / Len2) > 0.001 ||
		fabs(dz1 / Len1 - dz2 / Len2) > 0.001)
	{
		str.Format(LoadStr(IDS_MN_IZLOM1), nKOYZ);
		AfxMessageBox(str);
		return;
	}

	p1.m_NAYZ = p.m_NAYZ;
	p1.m_OSIX = dx1 + dx2;
	p1.m_OSIY = dy1 + dy2;
	p1.m_OSIZ = dz1 + dz2;

	m_pipes.m_vecPnN.erase(m_pipes.m_vecPnN.begin() + m_pipes.m_nIdx);
	m_bModified = true;
	UpdateAllViews(nullptr);
	UpdateData(FALSE);
}


void CStartPPDoc::OnMoveNode()
{
	CPipes pipes(m_pipes.m_nIdx, m_pipes.m_vecPnN);
	CMoveNodeDialog dlg(nullptr, pipes);
	if (dlg.DoModal() == IDOK)
	{
		m_bModified = true;
		UpdateAllViews(nullptr);
		UpdateData(FALSE);
	}
}


void CStartPPDoc::OnRenumPipes()
{
	if (AfxMessageBox(IDS_RENUM_NODES_Q, MB_YESNO) == IDNO)
		return;
	int FirstNum = 1;
	int MaxNodeNum = m_pipes.GetMaxNodeNum();
	m_pipes.RenumPipes(FirstNum, MaxNodeNum);
	m_bModified = true;
	UpdateAllViews(nullptr);
	UpdateData(FALSE);
}


void CStartPPDoc::SetUndo(void)
{
	if (!m_vecUndo.size() == 0 && m_pipes.m_vecPnN.size() == m_vecUndo[m_vecUndo.size() - 1].vec.m_vecPnN.size())
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


void CStartPPDoc::OnUndo()
{
	m_pipes = m_vecUndo[--m_nUndoPos].vec;
	vecSel = m_vecUndo[m_nUndoPos].sel;
	CDataExchange dx(m_pFrame, FALSE);
	m_pFrame->m_wndProperties.DoDataExchange(&dx, &m_pipes.m_vecPnN[m_pipes.m_nIdx], this);

	UpdateAllViews(nullptr);
}


void CStartPPDoc::OnUpdateUndo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nUndoPos > 0);
}


void CStartPPDoc::OnRedo()
{
	m_pipes = m_vecUndo[++m_nUndoPos].vec;
	vecSel = m_vecUndo[m_nUndoPos].sel;
	CDataExchange dx(m_pFrame, FALSE);
	m_pFrame->m_wndProperties.DoDataExchange(&dx, &m_pipes.m_vecPnN[m_pipes.m_nIdx], this);

	UpdateAllViews(nullptr);
}


void CStartPPDoc::OnUpdateRedo(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_nUndoPos + 1 < int(m_vecUndo.size()));
}


void CStartPPDoc::OnImportDbf()
{
	CFileDialog dlg(TRUE, nullptr, nullptr, 6UL, _T("*.dbf|*i.dbf||"), m_pFrame);
	CString strDir = AfxGetApp()->GetProfileString(_T("Settings"), _T("ImportDbf"));
	if (!strDir.IsEmpty())
		dlg.m_ofn.lpstrInitialDir = strDir;

	if (dlg.DoModal() == IDOK)
	{
		//AfxGetApp()->m_pDocManager->OpenDocumentFile(nullptr,FALSE);
		CString strFile = dlg.GetFileTitle();
		SetTitle(strFile);
		CString strFolder = dlg.m_pOFN->lpstrFile;
		::PathRemoveFileSpec(strFolder.GetBuffer());
		strFolder.ReleaseBuffer();
		AfxGetApp()->WriteProfileString(_T("Settings"), _T("ImportDbf"), strFolder);

		m_StartPPSet.m_strPath = strFolder;
		m_StartPPSet.m_strTable = strFile;
		m_strPathName = strFolder + _T("\\") + strFile;
		m_pipes.m_vecPnN.clear();
		m_pipes.m_nIdx = 0;
		try
		{
			m_StartPPSet.SetOldSet(false);
			m_StartPPSet.Open();
		}
		catch (CException* e)
		{
			m_StartPPSet.SetOldSet(true);
			m_StartPPSet.Open();
			e->Delete();
		}
		while (!m_StartPPSet.IsEOF())
		{
			m_pipes.m_vecPnN.push_back(m_StartPPSet);
			m_StartPPSet.MoveNext();
		}
		m_StartPPSet.Close();

		POSITION pos = GetFirstViewPosition();
		while (pos != nullptr)
		{
			CView* pView = GetNextView(pos);
			ASSERT_VALID(pView);
			pView->OnInitialUpdate();
		}
		UpdateData(FALSE);
	}
	else
		OnCloseDocument();
}


void CStartPPDoc::OnPipeDesc()
{
	CPipeDescDialog dlg(m_PipeDesc);
	dlg.DoModal();
}

#include <locale.h>

void CStartPPDoc::OnExportIni()
{
	setlocale(LC_ALL, "");
	CFileDialog dlg(FALSE, _T("ini"), GetTitle(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("*.ini|*.ini||"));
	CString strDir = AfxGetApp()->GetProfileString(_T("Settings"), _T("ExportIni"));
	if (!strDir.IsEmpty())
		dlg.m_ofn.lpstrInitialDir = strDir;
	if (dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		CStdioFile file(str, CFile::modeWrite | CFile::modeCreate | CFile::shareDenyRead);
		m_PipeDesc.WriteIni(file);
		m_TempHistory.WriteIni(file);
		m_pipes.WriteIni(file);
		file.Close();
		str = dlg.GetFolderPath();
		AfxGetApp()->WriteProfileString(_T("Settings"), _T("ExportIni"), str);
	}
}


void CStartPPDoc::OnPipeTable()
{
	CPipesTableDlg dlg;
	dlg.DoModal();
}


BOOL CStartPPDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return TRUE;
}

void CStartPPDoc::OnArmatTable(void)
{
	CArmatTableDlg dlg;
	dlg.DoModal();
}

void CStartPPDoc::OnTroinicsTable(void)
{
	CTroinicsTableDlg dlg;
	dlg.DoModal();
}

void CStartPPDoc::OnSpusk()
{
	CSpuskDialog dlg(nullptr, m_pipes);
	if (dlg.DoModal() == IDOK)
	{
		m_bModified = true;
		UpdateAllViews(nullptr);
		UpdateData(FALSE);
	};
}

void CStartPPDoc::OnAddSchem()
{
	CFileDialog dlg(TRUE, nullptr, nullptr, 6UL, _T("Start PP File (*.spf)|*.spf|Start DBF(*i.dbf)|*i.dbf||"));
	if (dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.GetFileName();
		CString strExt = ::PathFindExtension(strFile);
		if (strExt.CompareNoCase(_T(".dbf")) == 0)
		{
			CString strFolder = dlg.m_pOFN->lpstrFile;
			::PathRemoveFileSpec(strFolder.GetBuffer());
			strFolder.ReleaseBuffer();
			m_StartPPSet.m_strPath = strFolder;
			m_StartPPSet.m_strTable = strFile;
			m_strPathName = strFolder + _T("\\") + strFile;
			try
			{
				m_StartPPSet.SetOldSet(false);
				m_StartPPSet.Open();
			}
			catch (CException* e)
			{
				m_StartPPSet.SetOldSet(true);
				m_StartPPSet.Open();
				e->Delete();
			}
			CVecPnN p;
			while (!m_StartPPSet.IsEOF())
			{
				p.m_vecPnN.push_back(m_StartPPSet);
				m_StartPPSet.MoveNext();
			}
			m_StartPPSet.Close();
			int nMaxNodeNum = m_pipes.GetMaxNodeNum();
			p.RenumPipes(nMaxNodeNum, p.GetMaxNodeNum());
			CAddSchemDlg dlg1(nullptr, m_pipes, p);
			dlg1.DoModal();
		}
		else
		{
			CFileException fe;
			CFile* pFile = GetFile(dlg.GetPathName(),
			                       CFile::modeRead | CFile::shareDenyWrite, &fe);
			if (pFile == nullptr)
			{
				ReportSaveLoadException(dlg.GetPathName(), &fe,
				                        FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
				return;
			}
			CArchive ar(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
			CPipeDesc pd;
			pd.Serialize(ar);
			CVecPnN p;
			p.Serialize(ar);
			int nMaxNodeNum = m_pipes.GetMaxNodeNum();
			p.RenumPipes(nMaxNodeNum, p.GetMaxNodeNum());
			CAddSchemDlg dlg1(nullptr, m_pipes, p);
			dlg1.DoModal();
		}
		POSITION pos = GetFirstViewPosition();
		while (pos != nullptr)
		{
			CView* pView = GetNextView(pos);
			ASSERT_VALID(pView);
			pView->OnInitialUpdate();
		}
		UpdateData(FALSE);
	}
}

void CStartPPDoc::OnCloseDocument()
{
	CDataExchange dx(m_pFrame, FALSE);
	m_pFrame->m_wndProperties.DoDataExchange(&dx, nullptr, this);

	CDocument::OnCloseDocument();
}


void CStartPPDoc::SyncSel(void)
{
	UpdateData(TRUE);
	CPipeAndNode& p = m_pipes.CurPipe();
	vecSel.clear();
	vecSel.SelNAYZ = int(m_pFrame->m_wndProperties.m_PropMode == E_NODE ? p.m_KOYZ : p.m_NAYZ);
	vecSel.SelKOYZ = int(p.m_KOYZ);
	vecSel.insert(SelStr(vecSel.SelNAYZ, vecSel.SelKOYZ));
	UpdateData(FALSE);
}

void CStartPPDoc::Renum(std::vector<CPipeAndNode>& vec, std::map<int, int>& mapRenum, int FirstNum)
{
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		int NAYZ = int(it->m_NAYZ);
		if (NAYZ != 0)
		{
			if (mapRenum[NAYZ] == 0) mapRenum[NAYZ] = FirstNum++;
			it->m_NAYZ = float(mapRenum[NAYZ]);
		}
		int KOYZ = int(it->m_KOYZ);
		if (KOYZ != 0)
		{
			if (mapRenum[KOYZ] == 0) mapRenum[KOYZ] = FirstNum++;
			it->m_KOYZ = float(mapRenum[KOYZ]);
		}
	}
}


void CStartPPDoc::OnEditPaste()
{
	m_pFrame->OpenClipboard();
	HGLOBAL hglb = GetClipboardData(m_nClipFormat);
	BYTE* pData = static_cast<BYTE *>(GlobalLock(hglb));
	size_t cbData = GlobalSize(hglb);
	CMemFile mf(pData, UINT(cbData));
	CArchive ar(&mf, CArchive::load);
	int nBaseNode;
	int nNumPipes;
	ar >> nBaseNode;
	ar >> nNumPipes;
	std::vector<CPipeAndNode> vecPaste;
	for (int i = 0; i < nNumPipes; i++)
	{
		CPipeAndNode p;
		p.Serialize(ar);
		vecPaste.push_back(p);
	}
	ar.Close();
	GlobalUnlock(hglb);
	CloseClipboard();
	CVecPnN& vecPipes = m_pipes;
	int nSelNode = vecSel.begin()->SelNAYZ;
	std::map<int, int> mapRenum;
	mapRenum[nBaseNode] = nSelNode;
	int FirstNum = vecPipes.GetMaxNodeNum() + 1;
	vecSel.clear();
	Renum(vecPaste, mapRenum, FirstNum);
	for (auto it = vecPaste.begin(); it != vecPaste.end(); ++it)
	{
		vecPipes.m_vecPnN.push_back(*it);
		vecSel.insert(SelStr(int(it->m_NAYZ), int(it->m_KOYZ)));
	}
	m_pFrame->m_wndProperties.m_PropMode = E_PIPE;
	m_bModified = TRUE;
	UpdateData(FALSE);
}


void CStartPPDoc::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(IsClipboardFormatAvailable(m_nClipFormat) && vecSel.size() == 1 && vecSel.begin()->SelNAYZ >= 0 && vecSel.begin()->SelNAYZ == vecSel.begin()->SelKOYZ);
}


void CStartPPDoc::DeleteSelected(void)
{
	std::vector<CPipeAndNode> vecRemained;
	std::vector<CPipeAndNode> vecSelected;
	for each (auto& x in m_pipes.m_vecPnN)
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
				for each (auto& x in pipes)
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
				for each (auto& x in setSelNodes)
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

