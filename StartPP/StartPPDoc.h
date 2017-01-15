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
class CPropertiesWnd;

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
		}
		SUndo(const SUndo& other)
		{
			vec = other.vec;
			sel = other.sel;
		}
		SUndo() {}

		CVecPnN vec;
		CSelVec sel;
	};

	std::vector<SUndo> m_vecUndo;
	size_t m_nUndoPos;
	size_t m_nSaveUndoPos;
	MainFrame* m_pFrame;
	CSelVec vecSel;
	UINT m_nClipFormat;

	// Операции
public:
	// Переопределение
public:
	bool OnNewDocument() override;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS


	// Реализация
public:
	virtual ~CStartPPDoc();
	void OnRecordNext(wxCommandEvent& event);
	void OnRecordPrev(wxCommandEvent& event);
	void OnRecordLast(wxCommandEvent& event);
	void OnRecordFirst(wxCommandEvent& event);
	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	bool DoSaveDocument(const wxString& file) wxOVERRIDE;
	bool SaveAs() wxOVERRIDE;
	bool DoOpenDocument(const wxString& file) wxOVERRIDE;

public:
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);

	//wxString GetPathName() const { return wxString(_T("")); }
	void UpdateAllViews(wxView *sender = NULL, wxObject *hint = NULL) override;
	void UpdateData(bool bSaveAndValidate);
	void PnNIsUpdated(void);
	void Modify(bool mod) wxOVERRIDE;
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
    void OnSelectAll(wxCommandEvent& event);
	void SetUndo(void);
	afx_msg void OnUndo(wxCommandEvent& event);
	afx_msg void OnUpdateUndo(wxUpdateUIEvent& event);
	afx_msg void OnRedo(wxCommandEvent& event);
	afx_msg void OnUpdateRedo(wxUpdateUIEvent& event);
	afx_msg void OnImportDbf(wxCommandEvent& event);
	afx_msg void OnPipeDesc(wxCommandEvent& event);
	afx_msg void OnExportIni(wxCommandEvent& event);
	afx_msg void OnPipeTable(wxCommandEvent& event);
	void OnArmatTable(wxCommandEvent& event);
	void OnTroinicsTable(wxCommandEvent& event);

	afx_msg void OnSpusk(wxCommandEvent& event);
	afx_msg void RenumAndAddToPipes(CVecPnN p);
	void OnAddSchem(wxCommandEvent& event);
	bool OnCloseDocument() override { return true; };
	void SyncSel(void);
	CPropertiesWnd* GetPropWnd() const;
	afx_msg void OnEditPaste(wxCommandEvent& event);
	afx_msg void OnUpdateEditPaste(wxUpdateUIEvent& event);
	void DeleteSelected(void);
	void Renum(std::vector<CPipeAndNode>& vec, std::map<int, int>& mapRenum, int FirstNum);
	bool IsSelConnected(void);
	bool ProcessEvent(wxEvent& event) wxOVERRIDE;
	void OnUpdatePropMert(wxUpdateUIEvent& event);
    void OnUpdatePropSk(wxUpdateUIEvent& event);
    void OnUpdatePropNapr(wxUpdateUIEvent& event);
    void OnUpdatePropOtvSv(wxUpdateUIEvent& event);
    void OnUpdatePropOtvIz(wxUpdateUIEvent& event);
    void OnUpdatePropArm(wxUpdateUIEvent& event);
	void OnPropMert(wxCommandEvent& event);
	void OnPropSk(wxCommandEvent& event);
	void OnPropNapr(wxCommandEvent& event);
	void OnPropOtvSv(wxCommandEvent& event);
	void OnPropOtvIz(wxCommandEvent& event);
	void OnPropArm(wxCommandEvent& event);
};

