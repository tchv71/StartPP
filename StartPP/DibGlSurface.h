#pragma once
#ifdef __WXGTK__
#include "GL/glx.h"
#endif
#ifdef __WXMAC__
#include <OpenGL/OpenGL.h>
#endif

class wxGLCanvas;
class CDibGlSurface 
{
public:
	CDibGlSurface(const wxSize& size);
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
	BYTE biInfo[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
	LPVOID lpBits;
#endif
#ifdef __WXGTK__
	//GLXPbuffer PBDC;
	Pixmap m_pixmap;
	GLXContext PBRC;
	GLXPixmap m_pm;
    //wxGLCanvas *m_pCanvas;
#endif
#ifdef __WXMAC__
	CGLContextObj context;
#endif
};

