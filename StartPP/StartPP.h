// StartPP.h : главный файл заголовка для приложения StartPP
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif


// CStartPPApp:
// О реализации данного класса см. StartPP.cpp
//

class CStartPPApp : public CWinAppEx
{
public:
	CStartPPApp();


	// Переопределение
public:
	BOOL InitInstance() override;
	int ExitInstance() override;

	// Реализация
	UINT m_nAppLook;
	BOOL m_bHiColorIcons;

	void PreLoadState() override;
	void LoadCustomState() override;
	void SaveCustomState() override;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnImportDbf();
};

extern CStartPPApp theApp;

