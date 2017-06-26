#include "stdafx.h"
#include "DibGlSurface.h"
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/glcanvas.h>
#include <wx/dcgraph.h>
#include <wx/dcprint.h>
#if defined(__WXWIN__) && wxUSE_ENH_METAFILE
	#include "wx/msw/enhmeta.h"
#endif
#ifdef __WXMSW__
#include "GL/gl.h"
#endif

#ifdef __WXMAC__
#include <OpenGL/OpenGL.h>
#include <OpenGL/CGLTypes.h>
#include <OpenGL/CGLCurrent.h>
#include <OpenGL/gl.h>
#endif

#ifdef __WXGTK__
#define GL_GLEXT_PROTOTYPES 1
//#include "GL/glut.h"
#include <gtk/gtk.h>
#ifdef GDK_WINDOWING_X11
#include <gdk/gdkx.h>
#endif

#include "GL/gl.h"
#include "GL/glext.h"
#endif


CDibGlSurface::CDibGlSurface(const wxSize& size, CDC*pDC) : m_size(size)
#ifdef __WXMSW__
	,hDC(nullptr),hMemDC(nullptr),hglRC(nullptr),hBm(nullptr),hBmOld(nullptr),lpBits(nullptr)
#endif
#ifdef __WXGTK__
	//, PBDC(0)
    , m_pixmap(0)
	, m_PBRC(0)
    , m_pm(0)
#endif
{
#ifdef __WXMSW__
	CDC::TempHDC tempDC(*pDC);
	hDC = tempDC.GetHDC();
#endif
	InitializeGlobal();
}

CDibGlSurface::~CDibGlSurface()
{
	CleanUp();
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
	BYTE biInfo[sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)];
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

#if defined(__WXMSW__) || defined(__WXGTK__) || defined (__WXMAC__)
void CDibGlSurface::DoDraw(wxDC* pDC, wxRect rectPrint)
{
	wxSize sizeSave = m_size;
	m_size.x = (m_size.x / 2 + 1) * 2;
	BYTE* pixels = new BYTE[3 * m_size.GetWidth()*m_size.GetHeight()];
	memset(pixels, 127, 3 * m_size.GetWidth()*m_size.GetHeight());
	BYTE* pPix = pixels;
	for (int i = 0; i < m_size.GetHeight(); i++)
	{
		glReadPixels(0, m_size.GetHeight() - i - 1, m_size.GetWidth(), 1, GL_RGB, GL_UNSIGNED_BYTE, pPix);
		pPix += m_size.GetWidth() * 3;
	}
	wxImage img(m_size.GetWidth(), m_size.GetHeight(), pixels, NULL, false);
	wxBitmap bmp(img);
    m_size = sizeSave;

#if 0
	wxMemoryDC memDC;
	memDC.SelectObjectAsSource(bmp);
	pDC->StretchBlit(rectPrint.GetPosition(), rectPrint.GetSize(), &memDC, wxPoint(0, 0), m_size);
#else
    // Намного лучше качество интерполяции
    if (dynamic_cast<wxMemoryDC*>(pDC))
    {
        wxGCDC gc(*dynamic_cast<wxMemoryDC*>(pDC));
        gc.GetGraphicsContext()->DrawBitmap(bmp,rectPrint.x, rectPrint.y, rectPrint.width, rectPrint.height);
    }
    else if (dynamic_cast<wxPrinterDC*>(pDC))
    {
        wxGCDC gc(*dynamic_cast<wxPrinterDC*>(pDC));
        gc.GetGraphicsContext()->DrawBitmap(bmp,rectPrint.x, rectPrint.y, rectPrint.width, rectPrint.height);
    }
#if defined(__WXWIN__) && wxUSE_ENH_METAFILE
	else if (dynamic_cast<wxEnhMetaFileDC*>(pDC))
	{
		wxGCDC gc(*dynamic_cast<wxEnhMetaFileDC*>(pDC));
		gc.GetGraphicsContext()->DrawBitmap(bmp, rectPrint.x, rectPrint.y, rectPrint.width, rectPrint.height);
	}
#endif
#endif
}
#endif

#ifdef __WXGTK__

void CDibGlSurface::InitializeGlobal()
{
#if 0
	Display *dpy = (Display*)wxGetDisplay();
	int scrnum = DefaultScreen( dpy );
	GLXContext FBRC = glXGetCurrentContext();
	GLXDrawable FBDC = glXGetCurrentDrawable();

	if (dpy == NULL)
	{
		throw "unable to get device context";
	}
	if (!FBDC)
	{
		throw "unable to get render context";
	}
	int attrib[] =
	{
		GLX_DOUBLEBUFFER, False,
		//GLX_RED_SIZE, 8,
		//GLX_GREEN_SIZE, 8,
		//GLX_BLUE_SIZE, 8,
		//GLX_ALPHA_SIZE, 8,
		//GLX_STENCIL_SIZE, 0,
		//GLX_DEPTH_SIZE, 16,
		GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT | GLX_WINDOW_BIT,
		None
	};

	int PBattrib[] =
	{
		GLX_PBUFFER_WIDTH, m_size.GetWidth(),
		GLX_PBUFFER_HEIGHT, m_size.GetHeight(),
		GLX_LARGEST_PBUFFER, False,
		None
	};

	// choose a pixel format that meets our minimum requirements
	int count = 0;
	GLXFBConfig *config = glXChooseFBConfig(dpy, scrnum, attrib, &count);

	if(config == NULL || count == 0)
	{
		throw "no fitting pbuffer pixel format found";
	}

	GLXPbuffer _PBDC = glXCreatePbuffer(dpy, config[0], PBattrib);
	GLXContext _PBRC = glXCreateNewContext(dpy, config[0], GLX_RGBA_TYPE, NULL, true);
	PBDC = _PBDC;
	m_PBRC = _PBRC;
	XFree(config);
	Bool bRes = glXMakeCurrent(dpy, _PBDC, _PBRC);
    const unsigned char* str = glGetString(GL_VENDOR);
    return;
	int framebuffer_width = m_size.GetWidth();
	int framebuffer_height = m_size.GetHeight();

	GLuint m_framebuffer1;
	GLuint m_colorRenderbuffer1;
	GLuint m_depthRenderbuffer;

	glGenFramebuffers(1, &m_framebuffer1);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer1);

	glGenRenderbuffers(1, &m_colorRenderbuffer1);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer1);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, framebuffer_width, framebuffer_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer1);
	glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer1);

	glGenRenderbuffers(1, &m_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer_width, framebuffer_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		printf("Failed to make complete framebuffer object %x\n",status);
	else
		printf("Success, finally did it!");

	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebuffer1);
#else
	dis=(Display*)wxGetDisplay();
	int scrnum = DefaultScreen( dis );
	//d=glXGetCurrentDrawable();
	Drawable d=gdk_x11_window_get_xid(gdk_get_default_root_window());
	int w = m_size.GetWidth();
	int h = m_size.GetHeight();
	m_pixmap=XCreatePixmap(dis, d, w, h, 24);
	int attribList[] =
	{
		GLX_RGBA,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_DEPTH_SIZE, 24,
		None
	};
	XVisualInfo *vis=glXChooseVisual(dis, scrnum, attribList);
	
    m_pm = glXCreateGLXPixmap(dis, vis, m_pixmap);
	m_PBRC = glXCreateContext(dis, vis, NULL, True);
	glXMakeCurrent(dis, m_pm, m_PBRC);
	XFree(vis);
#ifndef NDEBUG
    /*const unsigned char* str =*/ glGetString(GL_VENDOR);
#endif
#endif
}

void CDibGlSurface::CleanUp()
{
	glXMakeCurrent(dis,0,NULL);
	glXDestroyContext(dis,m_PBRC);
	glXDestroyGLXPixmap(dis,m_pm);
	XFreePixmap(dis,m_pixmap);
}

#endif

#ifdef __WXMAC__
void CDibGlSurface::InitializeGlobal()
{

	CGLPixelFormatAttribute attributes[4] =
	{
	  kCGLPFAAccelerated,   // no software rendering
	  kCGLPFAOpenGLProfile, // core profile with the version stated below
	  (CGLPixelFormatAttribute) kCGLOGLPVersion_Legacy,
	  (CGLPixelFormatAttribute) 0
	};
	CGLPixelFormatObj pix;
	CGLError errorCode;
	GLint num; // stores the number of possible pixel formats
	errorCode = CGLChoosePixelFormat( attributes, &pix, &num );
	// add error checking here
	errorCode = CGLCreateContext( pix, NULL, &context ); // second parameter can be another context for object sharing
	// add error checking here
	CGLDestroyPixelFormat( pix );

	errorCode = CGLSetCurrentContext( context );
	// add error checking here
    //const unsigned char* str = glGetString(GL_VENDOR);
 	int framebuffer_width = m_size.GetWidth();
	int framebuffer_height = m_size.GetHeight();


	glGenFramebuffers(1, &m_framebuffer1);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer1);

	glGenRenderbuffers(1, &m_colorRenderbuffer1);
	glBindRenderbuffer(GL_RENDERBUFFER, m_colorRenderbuffer1);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, framebuffer_width, framebuffer_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer1);
	glFramebufferRenderbuffer(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_colorRenderbuffer1);

	glGenRenderbuffers(1, &m_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer_width, framebuffer_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
#ifndef NDEBUG
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	wxASSERT (status == GL_FRAMEBUFFER_COMPLETE);
#endif
//	glDrawBuffer(GL_COLOR_ATTACHMENT0);
//	glReadBuffer(GL_COLOR_ATTACHMENT0);
//	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_framebuffer1);
}

void CDibGlSurface::CleanUp()
{
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glDeleteRenderbuffers(1,&m_depthRenderbuffer);
	glDeleteRenderbuffers(1,&m_colorRenderbuffer1);
	glDeleteFramebuffers(1,&m_framebuffer1);
	CGLSetCurrentContext( NULL );
	CGLDestroyContext( context );
}

#endif
