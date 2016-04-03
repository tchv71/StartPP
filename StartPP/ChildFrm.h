// ChildFrm.h : интерфейс класса CChildFrame
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

	// Атрибуты
public:

	// Операции
public:

	// Переопределение
	BOOL PreCreateWindow(CREATESTRUCT& cs) override;

	// Реализация
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	void AssertValid() const override;
	void Dump(CDumpContext& dc) const override;
#endif

	// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
};

