#include "stdafx.h"
#include "DibGlSurface.h"



CDibGlSurface::CDibGlSurface(const wxSize& size) : m_size(size)
#ifdef __WXMSW__
	,hDC(nullptr),hMemDC(nullptr),hglRC(nullptr),hBm(nullptr),hBmOld(nullptr),lpBits(nullptr)
#endif

{
}

CDibGlSurface::~CDibGlSurface()
{
}

#ifdef __WXMSW__

void CDibGlSurface::InitializeGlobal()
{
	hMemDC = CreateCompatibleDC(hDC);
	hBm = CreateDIBSurface();
	hBmOld = HBITMAP(SelectObject(hMemDC, hBm));
	if (!PrepareDIBSurface())
		wxMessageBox(_T("The pixel format of the memory DC is not set properly"));
	hglRC = wglCreateContext(hMemDC);
	wglMakeCurrent(hMemDC, hglRC);
}


//***********************************************************************
// Function:	CDibGlSurface::CleanUp
//

//**********************************************************************
void CDibGlSurface::CleanUp()
{
	if (hglRC)
	{
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(hglRC);
	}
	//DeleteObject(hPal);
	hBm = HBITMAP(SelectObject(hMemDC, hBmOld));
	DeleteObject(hBm);
	DeleteDC(hMemDC);

}

void CDibGlSurface::DoDraw(wxDC* pDC, wxRect rectPrint)
{
	CDC::TempHDC tempHdc(*pDC);
	StretchDIBits(tempHdc.GetHDC(), rectPrint.GetLeft(), rectPrint.GetTop()
		, rectPrint.GetWidth(), rectPrint.GetHeight(), 0, 0, m_size.x,
		m_size.y, lpBits, reinterpret_cast<BITMAPINFO *>(biInfo),
		DIB_RGB_COLORS, SRCCOPY);
}

#define WIDTHBYTES(bits)  (((bits) + 31)/32 * 4)


//***********************************************************************
// Function:	CreateDIBSurface
//

// Purpose:		reates a DIB section as the drawing surface for gl calls
//
// Parameters:
//
// Returns:
//	  HBITMAP
//


//**********************************************************************
HBITMAP CDibGlSurface::CreateDIBSurface()
{
	BITMAPINFO* pbi = reinterpret_cast<BITMAPINFO *>(biInfo);
	ZeroMemory(pbi, sizeof(BITMAPINFO));
	if (!hDC)
		return nullptr;
	pbi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbi->bmiHeader.biWidth = m_size.GetWidth();
	pbi->bmiHeader.biHeight = m_size.GetHeight();
	pbi->bmiHeader.biPlanes = 1;
	pbi->bmiHeader.biBitCount = WORD(GetDeviceCaps(hDC, PLANES) * GetDeviceCaps(hDC, BITSPIXEL));
	pbi->bmiHeader.biCompression = BI_RGB;
	pbi->bmiHeader.biSizeImage = WIDTHBYTES(DWORD(pbi->bmiHeader.biWidth) *pbi->bmiHeader.biBitCount) *
		pbi->bmiHeader.biHeight;
	return CreateDIBSection(hDC, pbi, DIB_RGB_COLORS, &lpBits, nullptr,	DWORD(0));
}


//***********************************************************************
// Function:	CDibGlSurface::PrepareDIBSurface
//
// Purpose:		Selects the DIB section into a memory DC and sets the pixel
//				format of the memory DC. A palette is created if the app is
//				running on a 8 bit device.
//
// Parameters:
//	  void
//
// Returns:
//	  BOOL
//


//**********************************************************************
BOOL CDibGlSurface::PrepareDIBSurface(void) const
{
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
		1, // version number
		PFD_DRAW_TO_WINDOW | PFD_DRAW_TO_BITMAP | PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,
		// RGBA type
		24, // 24-bit color depth
		0, 0, 0, 0, 0, 0, // color bits ignored
		0, // no alpha buffer
		0, // shift bit ignored
		0, // no accumulation buffer
		0, 0, 0, 0, // accum bits ignored
		32, // 32-bit z-buffer
		0, // no stencil buffer
		0, // no auxiliary buffer
		PFD_MAIN_PLANE, // main layer
		0, // reserved
		0, 0, 0 // layer masks ignored
	};
	BOOL bRet = TRUE;
	int nIndex;
	pfd.cColorBits = byte(GetDeviceCaps(hDC, PLANES) * GetDeviceCaps(hDC, BITSPIXEL));
	nIndex = ChoosePixelFormat(hMemDC, &pfd);
	if (!nIndex)
		bRet = FALSE;
	DescribePixelFormat(hMemDC, nIndex, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	if (!SetPixelFormat(hMemDC, nIndex, &pfd))
		bRet = FALSE;

	//   if (bRet && pfd.dwFlags & PFD_NEED_PALETTE)
	//     CreateRGBPalette();
	return bRet;
}
#endif
