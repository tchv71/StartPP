#pragma once

//---------------------------------------------------------------------------
typedef struct _Render
{
	HDC hDC, hMemDC;
	HGLRC hglRC;
	HBITMAP hBm, hBmOld;
	RECT bmRect;
	HPALETTE hPal, hPalOld; //hPal, hPalOld, binInfo will only be used when running in 8 bit mode.
	BYTE biInfo[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
	LPVOID lpBits;
} RENDER;


class CDibGlSurface : public RENDER
{
public:
	CDibGlSurface();
	~CDibGlSurface();
	void InitializeGlobal();
	void CleanUp();
	HBITMAP CreateDIBSurface();
	BOOL PrepareDIBSurface() const;
};

