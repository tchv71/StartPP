#include "stdafx.h"
#include "DibGlSurface.h"
#include <wx/image.h>
#include <wx/bitmap.h>

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
#include "GL/glut.h"
#include "GL/gl.h"
#define GL_GLEXT_PROTOTYPES 1
#include "GL/glext.h"
extern "C" {
GLAPI void APIENTRY glColorMaski (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GLAPI void APIENTRY glGetBooleani_v (GLenum target, GLuint index, GLboolean *data);
GLAPI void APIENTRY glGetIntegeri_v (GLenum target, GLuint index, GLint *data);
GLAPI void APIENTRY glEnablei (GLenum target, GLuint index);
GLAPI void APIENTRY glDisablei (GLenum target, GLuint index);
GLAPI GLboolean APIENTRY glIsEnabledi (GLenum target, GLuint index);
GLAPI void APIENTRY glBeginTransformFeedback (GLenum primitiveMode);
GLAPI void APIENTRY glEndTransformFeedback (void);
GLAPI void APIENTRY glBindBufferRange (GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
GLAPI void APIENTRY glBindBufferBase (GLenum target, GLuint index, GLuint buffer);
GLAPI void APIENTRY glTransformFeedbackVaryings (GLuint program, GLsizei count, const GLchar *const*varyings, GLenum bufferMode);
GLAPI void APIENTRY glGetTransformFeedbackVarying (GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLsizei *size, GLenum *type, GLchar *name);
GLAPI void APIENTRY glClampColor (GLenum target, GLenum clamp);
GLAPI void APIENTRY glBeginConditionalRender (GLuint id, GLenum mode);
GLAPI void APIENTRY glEndConditionalRender (void);
GLAPI void APIENTRY glVertexAttribIPointer (GLuint index, GLint size, GLenum type, GLsizei stride, const void *pointer);
GLAPI void APIENTRY glGetVertexAttribIiv (GLuint index, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetVertexAttribIuiv (GLuint index, GLenum pname, GLuint *params);
GLAPI void APIENTRY glVertexAttribI1i (GLuint index, GLint x);
GLAPI void APIENTRY glVertexAttribI2i (GLuint index, GLint x, GLint y);
GLAPI void APIENTRY glVertexAttribI3i (GLuint index, GLint x, GLint y, GLint z);
GLAPI void APIENTRY glVertexAttribI4i (GLuint index, GLint x, GLint y, GLint z, GLint w);
GLAPI void APIENTRY glVertexAttribI1ui (GLuint index, GLuint x);
GLAPI void APIENTRY glVertexAttribI2ui (GLuint index, GLuint x, GLuint y);
GLAPI void APIENTRY glVertexAttribI3ui (GLuint index, GLuint x, GLuint y, GLuint z);
GLAPI void APIENTRY glVertexAttribI4ui (GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
GLAPI void APIENTRY glVertexAttribI1iv (GLuint index, const GLint *v);
GLAPI void APIENTRY glVertexAttribI2iv (GLuint index, const GLint *v);
GLAPI void APIENTRY glVertexAttribI3iv (GLuint index, const GLint *v);
GLAPI void APIENTRY glVertexAttribI4iv (GLuint index, const GLint *v);
GLAPI void APIENTRY glVertexAttribI1uiv (GLuint index, const GLuint *v);
GLAPI void APIENTRY glVertexAttribI2uiv (GLuint index, const GLuint *v);
GLAPI void APIENTRY glVertexAttribI3uiv (GLuint index, const GLuint *v);
GLAPI void APIENTRY glVertexAttribI4uiv (GLuint index, const GLuint *v);
GLAPI void APIENTRY glVertexAttribI4bv (GLuint index, const GLbyte *v);
GLAPI void APIENTRY glVertexAttribI4sv (GLuint index, const GLshort *v);
GLAPI void APIENTRY glVertexAttribI4ubv (GLuint index, const GLubyte *v);
GLAPI void APIENTRY glVertexAttribI4usv (GLuint index, const GLushort *v);
GLAPI void APIENTRY glGetUniformuiv (GLuint program, GLint location, GLuint *params);
GLAPI void APIENTRY glBindFragDataLocation (GLuint program, GLuint color, const GLchar *name);
GLAPI GLint APIENTRY glGetFragDataLocation (GLuint program, const GLchar *name);
GLAPI void APIENTRY glUniform1ui (GLint location, GLuint v0);
GLAPI void APIENTRY glUniform2ui (GLint location, GLuint v0, GLuint v1);
GLAPI void APIENTRY glUniform3ui (GLint location, GLuint v0, GLuint v1, GLuint v2);
GLAPI void APIENTRY glUniform4ui (GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
GLAPI void APIENTRY glUniform1uiv (GLint location, GLsizei count, const GLuint *value);
GLAPI void APIENTRY glUniform2uiv (GLint location, GLsizei count, const GLuint *value);
GLAPI void APIENTRY glUniform3uiv (GLint location, GLsizei count, const GLuint *value);
GLAPI void APIENTRY glUniform4uiv (GLint location, GLsizei count, const GLuint *value);
GLAPI void APIENTRY glTexParameterIiv (GLenum target, GLenum pname, const GLint *params);
GLAPI void APIENTRY glTexParameterIuiv (GLenum target, GLenum pname, const GLuint *params);
GLAPI void APIENTRY glGetTexParameterIiv (GLenum target, GLenum pname, GLint *params);
GLAPI void APIENTRY glGetTexParameterIuiv (GLenum target, GLenum pname, GLuint *params);
GLAPI void APIENTRY glClearBufferiv (GLenum buffer, GLint drawbuffer, const GLint *value);
GLAPI void APIENTRY glClearBufferuiv (GLenum buffer, GLint drawbuffer, const GLuint *value);
GLAPI void APIENTRY glClearBufferfv (GLenum buffer, GLint drawbuffer, const GLfloat *value);
GLAPI void APIENTRY glClearBufferfi (GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
GLAPI const GLubyte *APIENTRY glGetStringi (GLenum name, GLuint index);
GLAPI GLboolean APIENTRY glIsRenderbuffer (GLuint renderbuffer);
GLAPI void APIENTRY glBindRenderbuffer (GLenum target, GLuint renderbuffer);
GLAPI void APIENTRY glDeleteRenderbuffers (GLsizei n, const GLuint *renderbuffers);
GLAPI void APIENTRY glGenRenderbuffers (GLsizei n, GLuint *renderbuffers);
GLAPI void APIENTRY glRenderbufferStorage (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI void APIENTRY glGetRenderbufferParameteriv (GLenum target, GLenum pname, GLint *params);
GLAPI GLboolean APIENTRY glIsFramebuffer (GLuint framebuffer);
GLAPI void APIENTRY glBindFramebuffer (GLenum target, GLuint framebuffer);
GLAPI void APIENTRY glDeleteFramebuffers (GLsizei n, const GLuint *framebuffers);
GLAPI void APIENTRY glGenFramebuffers (GLsizei n, GLuint *framebuffers);
GLAPI GLenum APIENTRY glCheckFramebufferStatus (GLenum target);
GLAPI void APIENTRY glFramebufferTexture1D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI void APIENTRY glFramebufferTexture2D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
GLAPI void APIENTRY glFramebufferTexture3D (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
GLAPI void APIENTRY glFramebufferRenderbuffer (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
GLAPI void APIENTRY glGetFramebufferAttachmentParameteriv (GLenum target, GLenum attachment, GLenum pname, GLint *params);
GLAPI void APIENTRY glGenerateMipmap (GLenum target);

GLAPI void APIENTRY glBlitFramebuffer (GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
GLAPI void APIENTRY glRenderbufferStorageMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
GLAPI void APIENTRY glFramebufferTextureLayer (GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
GLAPI void *APIENTRY glMapBufferRange (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
GLAPI void APIENTRY glFlushMappedBufferRange (GLenum target, GLintptr offset, GLsizeiptr length);
GLAPI void APIENTRY glBindVertexArray (GLuint array);
GLAPI void APIENTRY glDeleteVertexArrays (GLsizei n, const GLuint *arrays);
GLAPI void APIENTRY glGenVertexArrays (GLsizei n, GLuint *arrays);
GLAPI GLboolean APIENTRY glIsVertexArray (GLuint array);
}
#endif


CDibGlSurface::CDibGlSurface(const wxSize& size) : m_size(size)
#ifdef __WXMSW__
	,hDC(nullptr),hMemDC(nullptr),hglRC(nullptr),hBm(nullptr),hBmOld(nullptr),lpBits(nullptr)
#endif
#ifdef __WXGTK__
	, PBDC(0), PBRC(0)
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

#if defined(__WXMSW__) || defined(__WXGTK__) || defined (__WXMAC__)
void CDibGlSurface::DoDraw(wxDC* pDC, wxRect rectPrint)
{
#if 0// defined(__WXMSW__)
	CDC::TempHDC tempHdc(*pDC);
	StretchDIBits(tempHdc.GetHDC(), rectPrint.GetLeft(), rectPrint.GetTop()
		, rectPrint.GetWidth(), rectPrint.GetHeight(), 0, 0, m_size.x,
		m_size.y, lpBits, reinterpret_cast<BITMAPINFO *>(biInfo),
		DIB_RGB_COLORS, SRCCOPY);
#else
	wxSize sizeSave = m_size;
	m_size.x = (m_size.x / 2 + 1) * 2;
	BYTE* pixels = new BYTE[3 * m_size.GetWidth()*m_size.GetHeight()];
	BYTE* pPix = pixels;
	for (int i = 0; i < m_size.GetHeight(); i++)
	{
		glReadPixels(0, m_size.GetHeight() - i - 1, m_size.GetWidth(), 1, GL_RGB, GL_UNSIGNED_BYTE, pPix);
		pPix += m_size.GetWidth() * 3;
	}

	wxImage img(m_size.GetWidth(), m_size.GetHeight(), pixels, NULL, false);

	wxBitmap bmp(img);
	wxMemoryDC memDC;
	memDC.SelectObjectAsSource(bmp);
	m_size = sizeSave;
	pDC->StretchBlit(rectPrint.GetPosition(), rectPrint.GetSize(), &memDC, wxPoint(0, 0), m_size);

	//delete[] pixels;
#endif
}
#endif

#ifdef __WXGTK__
void CDibGlSurface::InitializeGlobal()
{
#if 1
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
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		GLX_STENCIL_SIZE, 8,
		GLX_DEPTH_SIZE, 24,
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
	GLXContext _PBRC = glXCreateNewContext(dpy, config[0], GLX_RGBA_TYPE, FBRC, false);
	PBDC = _PBDC;
	PBRC = _PBRC;
	XFree(config);
	Bool bRes = glXMakeContextCurrent(dpy, _PBDC, _PBDC, _PBRC);

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
#else
	Display *dis=(Display*)wxGetDisplay();
	int scrnum = DefaultScreen( dis );
	Drawable d=glXGetCurrentDrawable();
	int w = m_size.GetWidth();
	int h = m_size.GetHeight();
	Pixmap pixmap=XCreatePixmap(dis, d, w, h, 64);
	int attribList[] =
	{
		GLX_DOUBLEBUFFER, False,
		GLX_RGBA,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_ALPHA_SIZE, 8,
		//GLX_STENCIL_SIZE, 8,
		GLX_DEPTH_SIZE, 16,
		//GLX_RENDER_TYPE, GLX_RGBA_BIT,
		GLX_DRAWABLE_TYPE, GLX_PIXMAP_BIT | GLX_WINDOW_BIT,
		None
	};
	XVisualInfo *vis=glXChooseVisual(dis, scrnum, attribList);
	GLXPixmap pm=glXCreateGLXPixmap(dis, vis, pixmap);
	GLXContext context=glXCreateContext(dis, vis, 0, False);
	glXMakeCurrent(dis, pm, context);
#endif
}

void CDibGlSurface::CleanUp()
{
	//Display *dpy = (Display*)wxGetDisplay();
	//glXDestroyPbuffer(dpy,PBDC);
	//glXDestroyContext(dpy,PBRC);
}

#endif

#ifdef __WXMAC__
void CDibGlSurface::InitializeGlobal()
{

	CGLPixelFormatAttribute attributes[4] =
	{
	  kCGLPFAAccelerated,   // no software rendering
	  kCGLPFAOpenGLProfile, // core profile with the version stated below
	  (CGLPixelFormatAttribute) kCGLOGLPVersion_3_2_Core,
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

/*	glGenRenderbuffers(1, &m_depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffer_width, framebuffer_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);*/
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		printf("Failed to make complete framebuffer object %x\n",status);
	else
		printf("Success, finally did it!");
}

void CDibGlSurface::CleanUp()
{
	CGLSetCurrentContext( NULL );
	CGLDestroyContext( context );
}

#endif
