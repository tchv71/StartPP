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
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to the path to a TrueType font */
/* #undef FONT_FILE */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <GLUT/glut.h> header file. */
/* #undef HAVE_GLUT_GLUT_H */

/* Define to 1 if you have the <GL/glut.h> header file. */
#define HAVE_GL_GLUT_H 1

/* Define to 1 if you have the <GL/glu.h header */
#define HAVE_GL_GLU_H 1

/* Define to 1 if you have the <GL/gl.h header */
#define HAVE_GL_GL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <OpenGL/glu.h header */
/* #undef HAVE_OPENGL_GLU_H */

/* Define to 1 if you have the <OpenGL/gl.h header */
/* #undef HAVE_OPENGL_GL_H */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `wcsdup' function. */
#define HAVE_WCSDUP 1

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "sam@zoy.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "FTGL"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "FTGL 2.1.3~rc5"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "ftgl"

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.1.3~rc5"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */

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

class FTFont;

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
	void DrawText(LPCTSTR txt, ESvFont fontNo );
	float GetFontSize(ESvFont fontNo);
protected:
	unsigned int m_fontBases[SVF_SIZE];
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


	FTFont* m_fonts[SVF_SIZE]; // Windows Font ID
	SLogFont m_arrLogFonts[SVF_SIZE];
	// Printing
protected:
	void ReleaseFont(ESvFont fontNo);
};
#endif // !defined(AFX_GLRENDERER_H__C29F2A7B_8CBD_4EAD_B373_AD7756A84629__INCLUDED_)


