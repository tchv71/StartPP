// GLFontRenderer.cpp: implementation of the CGLFontRenderer class.
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
#include "GLFontRenderer.h"
#include <wx/filename.h>

//#define USE_FONT_BITMAPS

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLFontRenderer::CGLFontRenderer()
{
	memset(m_fonts, 0, sizeof(m_fonts));
	memset(m_arrLogFonts, 0, sizeof(m_arrLogFonts));
}

CGLFontRenderer::~CGLFontRenderer()
{
	ReleaseAllFonts();
}


#ifndef __WXMSW__
#define S_OK 0
#endif


#ifndef __WXMSW__
typedef const char * LPCSTR;
typedef long LONG;
#endif

CString CGLFontRenderer::GetRenderString()
{
	CString str;
	str += LPCSTR(glGetString(GL_RENDERER));
	str += _T(" ");
	str += LPCSTR(glGetString(GL_VENDOR));
	str += _T(" ");
	str += LPCSTR(glGetString(GL_VERSION));
	return str;
}

void CGLFontRenderer::BuildFont(ESvFont fontNo, const SLogFont* pLogFont)
{
   
    wxString strPath = DATA_PATH+"/arial.ttf";
    const char *szFile = strPath.c_str();//"LiberationMono-BoldItalic.ttf";
	//const char *szFile = "LiberationMono-BoldItalic.ttf";
	switch (pLogFont->fType)
	{
	case FT_BitmapFont:
		m_fonts[fontNo] = new FTGLBitmapFont(szFile);
		break;
	case FT_OutlineFont:
		m_fonts[fontNo] = new FTGLOutlineFont(szFile);
		break;
	case FT_PixmapFont:
		m_fonts[fontNo] = new FTGLPixmapFont(szFile);
		break;
	case FT_PolygonFont:
		m_fonts[fontNo] = new FTGLPolygonFont(szFile);
		break;
	case FT_TextureFont:
		m_fonts[fontNo] = new FTGLTextureFont(szFile);
		break;
	}

	m_fonts[fontNo]->FaceSize(pLogFont->lfHeight);
	//if (fontNo == SVF_NODENUMS || fontNo == SVF_TEXT)
	//{
	//	m_fonts[fontNo]->FaceSize(16);
	//}
	//else
	//	m_fonts[fontNo]->FaceSize(10);
}

void CGLFontRenderer::ReleaseFont(ESvFont fontNo)
{
	delete m_fonts[fontNo];
	m_fonts[fontNo] = nullptr;
	//glDeleteLists(m_fontBases[fontNo], 256); // Delete All 256 Characters
	//::DeleteObject(m_fonts[fontNo]);
}

CSize CGLFontRenderer::GetFontExtent(ESvFont fontNo, LPCTSTR pszText)
{
	FTBBox box = m_fonts[fontNo]->BBox(pszText);
	return CSize((int) (box.Upper().X() - box.Lower().X()), box.Upper().Y() - box.Lower().Y());
}

void CGLFontRenderer::BuildAllFonts(const SLogFont arrLogFonts[], float fScale)
{
	if (arrLogFonts != nullptr)
	{
		memcpy(m_arrLogFonts, arrLogFonts, sizeof(m_arrLogFonts));
	}
	for (int i = 0; i < SVF_SIZE; i++)
	{
		m_arrLogFonts[i].lfHeight = int(m_arrLogFonts[i].lfHeight * fScale);
		BuildFont(ESvFont(i), m_arrLogFonts + i);
	}
}

void CGLFontRenderer::ReleaseAllFonts()
{
	for (int i = 0; i < SVF_SIZE; i++)
		ReleaseFont(ESvFont(i));
}

void CGLFontRenderer::DrawText(LPCTSTR txt, ESvFont fontNo ) const
{
	m_fonts[fontNo]->Render(txt);
}

float CGLFontRenderer::GetFontSize(ESvFont fontNo) const
{
	return m_arrLogFonts[fontNo].lfHeight;//m_fontSizes[fontNo];
}
