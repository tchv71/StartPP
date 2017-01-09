// GLFontRenderer.h: interface for the CGLFontRenderer class.
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


#ifndef __WXMSW__

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
enum EFontType
{
	FT_BitmapFont,
	FT_OutlineFont,
	FT_PixmapFont,
	FT_PolygonFont,
	FT_TextureFont
};

struct SLogFont
{
	long lfHeight;
	EFontType fType;
};



enum ESvFont
{
	SVF_DIMS=0,
	SVF_NODENUMS,
	SVF_TEXT,
	SVF_SIZE // The number of SV fonts
};


class FTFont;

class CGLFontRenderer
{
public:
	CGLFontRenderer();
	virtual ~CGLFontRenderer(void);
public:
	void ReleaseAllFonts();
	void BuildAllFonts(const SLogFont arrLogFonts[] = nullptr, float fScale = 1.0f);
	CSize GetFontExtent(ESvFont fontNo, LPCTSTR pszText);
	//bool Select(CViewGeometry *pGeometry, CPoint pt, FLOAT_TYPE fDepth);
	static CString GetRenderString();

	void BuildFont(ESvFont fontNo, const SLogFont* pLogFont);
	void DrawText(LPCTSTR txt, ESvFont fontNo );
	float GetFontSize(ESvFont fontNo) const;
protected:
	//unsigned int m_fontBases[SVF_SIZE];
	//float m_fontSizes[SVF_SIZE];
	//GLYPHMETRICSFLOAT m_gmfs[SVF_SIZE][256]; // Storage For Information About Our Outline Font Characters

protected:
	//void CreateRGBPalette(HDC hDC, PIXELFORMATDESCRIPTOR& pfd);
	//int ChoosePixelFormatEx
	//(
	//	HDC hdc,
	//	int* pnColorBits,
	//	int* pnDepthBits,
	//	int* pnWantDoubleBuffer,
	//	int* pnWantAcceleration
	//);
	//bool bSetupPixelFormat(DWORD dwFlags, bool Soft);
	//bool SetDCPixelFormat(HDC hDC, DWORD dwFlags);


	FTFont* m_fonts[SVF_SIZE]; // Windows Font ID
	SLogFont m_arrLogFonts[SVF_SIZE];
	// Printing
protected:
	void ReleaseFont(ESvFont fontNo);
};
#endif // !defined(AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_)


