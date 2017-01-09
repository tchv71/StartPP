#pragma once
#ifdef __WXGTK__
#include "GL/glx.h"
#endif
#ifdef __WXMAC__
#include <OpenGL/OpenGL.h>
#endif

class CDibGlSurface 
{
public:
	CDibGlSurface(const wxSize& size,CDC*pDC);
	~CDibGlSurface();
	void InitializeGlobal();
	void CleanUp();
	void DoDraw(wxDC *pDC, wxRect rect);
protected:
	wxSize m_size;
#ifdef __WXMSW__
public:
	HBITMAP CreateDIBSurface();
	BOOL PrepareDIBSurface() const;
	HDC hDC;
protected:
	HDC hMemDC;
	HGLRC hglRC;
	HBITMAP hBm, hBmOld;
	//HPALETTE hPal, hPalOld; //hPal, hPalOld, binInfo will only be used when running in 8 bit mode.
	LPVOID lpBits;
#endif
#ifdef __WXGTK__
	//GLXPbuffer PBDC;
	Display *dis;
	Pixmap m_pixmap;
	GLXContext m_PBRC;
	GLXPixmap m_pm;
#endif
#ifdef __WXMAC__
	CGLContextObj context;
	GLuint m_framebuffer1;
	GLuint m_colorRenderbuffer1;
	GLuint m_depthRenderbuffer;
#endif
};

