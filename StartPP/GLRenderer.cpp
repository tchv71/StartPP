// GLRenderer.cpp: implementation of the CGLRenderer class.
//
//////////////////////////////////////////////////////////////////////
// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited

#include "stdafx.h"
#ifdef __WXMAC__
#include <gl.h>
#else
#include <GL/gl.h>
#endif
#include <FTGL/ftgl.h>
#include "GLRenderer.h"

//#define USE_FONT_BITMAPS

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLRenderer::CGLRenderer()
{
	memset(m_fontBases, 0, sizeof(m_fontBases));
	memset(m_fonts, 0, sizeof(m_fonts));
	memset(m_arrLogFonts, 0, sizeof(m_arrLogFonts));
}

CGLRenderer::~CGLRenderer()
{
	ReleaseAllFonts();
}


#ifndef __WXMSW__
#define S_OK 0
#endif


HRESULT CGLRenderer::ReleaseWindow(void)
{
	ReleaseAllFonts();
	return S_OK;
}

HRESULT CGLRenderer::BindWindow(HWND hBindWnd, bool bSoftOGL, const SLogFont arrLogFonts[])
{
	BuildAllFonts(m_arrLogFonts);
	return S_OK;
}


#ifndef __WXMSW__
typedef const char * LPCSTR;
typedef long LONG;
#endif

CString CGLRenderer::GetRenderString()
{
	CString str;
	str += LPCSTR(glGetString(GL_RENDERER));
	str += _T(" ");
	str += LPCSTR(glGetString(GL_VENDOR));
	str += _T(" ");
	str += LPCSTR(glGetString(GL_VERSION));
	return str;
}


void CGLRenderer::BuildFont(ESvFont fontNo, const LOGFONT* pLogFont)
{
	const char *szFile = "../Data/arial.ttf";//"LiberationMono-BoldItalic.ttf";
	//const char *szFile = "LiberationMono-BoldItalic.ttf";

	m_fonts[fontNo] = new FTGLPolygonFont(szFile);//FTGLTextureFont(szFile);

	if (fontNo==SVF_VALUES || fontNo == SVF_RUS)
	{
		m_fonts[fontNo]->FaceSize(16);
	}
	else
		m_fonts[fontNo]->FaceSize(10);
}

void CGLRenderer::ReleaseFont(ESvFont fontNo)
{
	delete m_fonts[fontNo];
	m_fonts[fontNo] = nullptr;
	//glDeleteLists(m_fontBases[fontNo], 256); // Delete All 256 Characters
	m_fontBases[fontNo] = 0;
	//::DeleteObject(m_fonts[fontNo]);
}

CSize CGLRenderer::GetFontExtent(ESvFont fontNo, LPCTSTR pszText, TEXTMETRIC* ptm)
{
	FTBBox box = m_fonts[fontNo]->BBox(pszText);
	return CSize(box.Upper().X()-box.Lower().X(), box.Upper().Y()-box.Lower().Y());
}

void CGLRenderer::BuildAllFonts(const SLogFont arrLogFonts[], float fScale)
{
	if (arrLogFonts != nullptr)
	{
		memcpy(m_arrLogFonts, arrLogFonts, sizeof(m_arrLogFonts));
	}
	for (int i = 0; i < SVF_SIZE; i++)
	{
		m_arrLogFonts[i].lfHeight = long(m_arrLogFonts[i].lfHeight * fScale);
		BuildFont(ESvFont(i), m_arrLogFonts + i);
	}
}

void CGLRenderer::ReleaseAllFonts()
{
	for (int i = 0; i < SVF_SIZE; i++)
		ReleaseFont(ESvFont(i));
}

void CGLRenderer::DrawText(LPCTSTR txt, ESvFont fontNo )
{
	m_fonts[fontNo]->Render(txt, wcslen(txt));
}

float CGLRenderer::GetFontSize(ESvFont fontNo)
{
	return 14;//m_fontSizes[fontNo];
}
