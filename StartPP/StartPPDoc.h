// StartPPDoc.h : интерфейс класса CStartPPDoc
//


#pragma once
#include "StartPPSet.h"
#include <vector>
#include "PipeDesc.h"
#include "TempHistory.h"
#include "VecPnN.h"
#include "PipePresenter.h"
#include <wx/docview.h>

class MainFrame;
class CCmdUI;


class CStartPPDoc : public wxDocument
{
protected: // создать только из сериализации
    wxDECLARE_NO_COPY_CLASS(CStartPPDoc);
    wxDECLARE_DYNAMIC_CLASS(CStartPPDoc);

	// Атрибуты
public:
	CStartPPDoc();
	CStartPPSet m_StartPPSet;
	CVecPnN m_pipes;
	CPipeDesc m_PipeDesc;
	CTempHistory m_TempHistory;

	struct SUndo
	{
		SUndo(const CVecPnN& v, const CSelVec& s) : vec(v), sel(s)
		{
		};

		CVecPnN vec;
		CSelVec sel;
	};

	std::vector<SUndo> m_vecUndo;
	size_t m_nUndoPos;
	MainFrame* m_pFrame;
	CSelVec vecSel;
	UINT m_nClipFormat;

	// Операции
public:
	// Переопределение
public:
	bool OnNewDocument() override;
	void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS


	// Реализация
public:
	virtual ~CStartPPDoc();

	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	afx_msg void OnRecordFirst();
	afx_msg void OnRecordLast();
	afx_msg void OnRecordNext();
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
public:
	wxString GetPathName() const { return wxString(_T("")); }
	void UpdateAllViews(wxView *sender = NULL, wxObject *hint = NULL) override;
	void UpdateData(bool bSaveAndValidate);
	void PnNIsUpdated(void);
	CPipeAndNode* GetPrevPnN(int NAYZ);
	void RotateThisAndOthers(float fAngle);
	void RotateThisAndOthers(CPipeAndNode* pPnP, float fAngle);
	void RotateOne(size_t recNo, float fAngle);
	void RotateAll(int NAYZ, float fAngle);
	std::vector<bool> m_bvecRotated;
	void Select(int NAYZ, int KOYZ);
	afx_msg void OnNewPipe(wxCommandEvent& event);
	afx_msg void OnDelPipe(wxCommandEvent& event);
	afx_msg void OnMultPipe(wxCommandEvent& event);
	afx_msg void OnCopyPipeParams(wxCommandEvent& event);
	afx_msg void OnInvertPipe(wxCommandEvent& event);
	afx_msg void OnNewNode(wxCommandEvent& event);
	afx_msg void OnDelNode(wxCommandEvent& event);
	afx_msg void OnMoveNode(wxCommandEvent& event);
	afx_msg void OnRenumPipes(wxCommandEvent& event);
	void SetUndo(void);
	afx_msg void OnUndo(wxCommandEvent& event);
	afx_msg void OnUpdateUndo(wxUpdateUIEvent& event);
	afx_msg void OnRedo(wxCommandEvent& event);
	afx_msg void OnUpdateRedo(wxUpdateUIEvent& event);
	afx_msg void OnImportDbf();
	afx_msg void OnPipeDesc();
	afx_msg void OnExportIni();
	afx_msg void OnPipeTable();
	bool OnOpenDocument(const wxString& filename) override
	{
		UNREFERENCED_PARAMETER(filename);
		return TRUE;
	};
	void OnArmatTable(void);
	void OnTroinicsTable(void);
	afx_msg void OnSpusk(wxCommandEvent& event);
	afx_msg void OnAddSchem();
	bool OnCloseDocument() override { return true; };
	void SyncSel(void);
	afx_msg void OnEditPaste(wxCommandEvent& event);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	void DeleteSelected(void);
	void Renum(std::vector<CPipeAndNode>& vec, std::map<int, int>& mapRenum, int FirstNum);
	bool IsSelConnected(void);
};

