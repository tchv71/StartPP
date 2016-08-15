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
	GLXPbuffer PBDC;
	GLXContext PBRC;
#endif
#ifdef __WXMAC__
	CGLContextObj context;
#endif
};

