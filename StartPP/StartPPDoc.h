// StartPPDoc.h : интерфейс класса CStartPPDoc
//


#pragma once
#include "StartPPSet.h"
#include <vector>
#include "PipeDesc.h"
#include "TempHistory.h"
#include "VecPnN.h"
#include "PipePresenter.h"
class CMainFrame : public CWnd
{
public:
	CPropertiesWnd m_wndProperties;
};
#ifdef WX
class CDocument
{
public:
	bool m_bModified;
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void UpdateAllViews(void*) {};
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
#endif

class CStartPPDoc : public CDocument
{
protected: // создать только из сериализации
	CStartPPDoc();
	DECLARE_DYNCREATE(CStartPPDoc)

	// Атрибуты
public:
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
	CMainFrame* m_pFrame;
	CSelVec vecSel;
	UINT m_nClipFormat;

	// Операции
public:

	// Переопределение
public:
	BOOL OnNewDocument() override;
	void Serialize(CArchive& ar) override;
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS


	// Реализация
public:
	virtual ~CStartPPDoc();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

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
	void UpdateData(bool bSaveAndValidate);
	void PnNIsUpdated(void);
	CPipeAndNode* GetPrevPnN(int NAYZ);
	void RotateThisAndOthers(float fAngle);
	void RotateThisAndOthers(CPipeAndNode* pPnP, float fAngle);
	void RotateOne(size_t recNo, float fAngle);
	void RotateAll(int NAYZ, float fAngle);
	std::vector<bool> m_bvecRotated;
	void Select(int NAYZ, int KOYZ);
	afx_msg void OnNewPipe();
	afx_msg void OnDelPipe();
	afx_msg void OnMultPipe();
	afx_msg void OnCopyPipeParams();
	afx_msg void OnInvertPipe();
	afx_msg void OnNewNode();
	afx_msg void OnDelNode();
	afx_msg void OnMoveNode();
	afx_msg void OnRenumPipes();
	void SetUndo(void);
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnRedo();
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnImportDbf();
	afx_msg void OnPipeDesc();
	afx_msg void OnExportIni();
	afx_msg void OnPipeTable();
	BOOL OnOpenDocument(LPCTSTR lpszPathName) override;
	void OnArmatTable(void);
	void OnTroinicsTable(void);
	afx_msg void OnSpusk();
	afx_msg void OnAddSchem();
	void OnCloseDocument() override;
	void SyncSel(void);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	void DeleteSelected(void);
	void Renum(std::vector<CPipeAndNode>& vec, std::map<int, int>& mapRenum, int FirstNum);
	bool IsSelConnected(void);
};

