// GLRenderer.h: interface for the CGLRenderer class.
//
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_)
#define AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wx/defs.h"

#ifndef __WXMSW__
struct LOGFONT
{
	long lfHeight;
};

class TEXTMETRIC;
class PIXELFORMATDESCRIPTOR;
typedef DWORD HRESULT;

struct GLYPHMETRICSFLOAT
{
	float gmfCellIncX;
	float gmfBlackBoxY;
};
typedef void* HDC;
typedef void* HFONT;
typedef void* HGLRC;

#endif
typedef LOGFONT SLogFont;



enum ESvFont
{
	SVF_AXES=0,
	SVF_VALUES,
	SVF_RUS,
	SVF_SIZE // The number of SV fonts
};


class CGLRenderer
{
public:
	CGLRenderer();
	virtual ~CGLRenderer(void);
public:
	void ReleaseAllFonts();
	void BuildAllFonts(const SLogFont arrLogFonts[] = nullptr, float fScale = 1.0f);
	CSize GetFontExtent(ESvFont fontNo, LPCTSTR pszText, TEXTMETRIC* ptm);
	//bool Select(CViewGeometry *pGeometry, CPoint pt, FLOAT_TYPE fDepth);
	CString GetRenderString();
	// IFemRenderer support
	HRESULT BindWindow(HWND hBindWnd, bool bSoftOGL, const SLogFont arrLogFonts[]);
	HRESULT BindDc(HDC hDc, bool bSoftOGL);
	HRESULT ReleaseWindow(void);
	//HRESULT Render(CViewGeometry *pGeometry, SViewOptions *pViewOptions, CDrawOptions *pDrawOptions);
	void BuildFont(ESvFont fontNo, const LOGFONT* pLogFont);
	UINT m_fontBases[SVF_SIZE];
	float m_fontSizes[SVF_SIZE];
	GLYPHMETRICSFLOAT m_gmfs[SVF_SIZE][256]; // Storage For Information About Our Outline Font Characters

protected:
	void CreateRGBPalette(HDC hDC, PIXELFORMATDESCRIPTOR& pfd);
	int ChoosePixelFormatEx
	(
		HDC hdc,
		int* pnColorBits,
		int* pnDepthBits,
		int* pnWantDoubleBuffer,
		int* pnWantAcceleration
	);
	bool bSetupPixelFormat(DWORD dwFlags, bool Soft);
	bool SetDCPixelFormat(HDC hDC, DWORD dwFlags);

	HWND m_hWnd;


	HFONT m_fonts[SVF_SIZE]; // Windows Font ID
	SLogFont m_arrLogFonts[SVF_SIZE];
	// Printing
public:
	HDC m_hMemDC;
	HGLRC m_hMemRC;

protected:
	void ReleaseFont(ESvFont fontNo);
};
#endif // !defined(AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_)


