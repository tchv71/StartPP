//---------------------------------------------------------------------------
#ifndef OGLShowPipesH
#define OGLShowPipesH
//#include <GL/gl.h>
#include <wx/glcanvas.h>
//#include <printers.hpp>
#include "ScreenPipePresenter.h"

class CGLRenderer;
#ifndef __WXMSW__
typedef void* HGLRC;
typedef void* HBITMAP;
typedef void* LPVOID;
typedef void* HDC;
#endif

class CPrintDialog;

struct CPrintInfo // Printing information structure
{
	CPrintInfo();
	~CPrintInfo();

	CPrintDialog* m_pPD;     // pointer to print dialog

	BOOL m_bDocObject;       // TRUE if printing by IPrint interface
	BOOL m_bPreview;         // TRUE if in preview mode
	BOOL m_bDirect;          // TRUE if bypassing Print Dialog
	BOOL m_bContinuePrinting;// set to FALSE to prematurely end printing
	UINT m_nCurPage;         // Current page
	UINT m_nNumPreviewPages; // Desired number of preview pages
	CString m_strPageDesc;   // Format string for page number display
	LPVOID m_lpUserData;     // pointer to user created struct
	CRect m_rectDraw;        // rectangle defining current usable page area
	int m_nJobNumber;			 // job number (after StartDoc)

								 // these only valid if m_bDocObject
	UINT m_nOffsetPage;      // offset of first page in combined IPrint job
	DWORD m_dwFlags;         // flags passed to IPrint::Print

	void SetMinPage(UINT nMinPage);
	void SetMaxPage(UINT nMaxPage);
	UINT GetMinPage() const;
	UINT GetMaxPage() const;
	UINT GetFromPage() const;
	UINT GetToPage() const;
	UINT GetOffsetPage() const;
};


class COGLPipePresenter: public CScreenPipePresenter, public wxGLCanvas
{
	void SetupLighting();
	void draw_styk(float l_gen, float rad, float str_x_rot, float str_tg_2, float end_tg_2, float t1, float t2, bool DrawEnd);
	void InitGLScene();
	void AddNodeElement(float* p, TNodeElement el, float ang) override;
	void AddLine(float* p1, float* p2, int NAYZ, Pipe& p) override;
	void AddLineFrom(float* p1, float* p2, float Dist, float ang) override;
	void AddPodushFrom(float* p1, float* p2, float Dist, float ang) override;
	void AddCircle(float* p, float rad) override;
	void AddNodeNum(float* p, float Dist, float ang, int NodeNum, float rad) override;
	void AddTextFrom(float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode) override;
	void Add2TextFrom(float* p, float Dist, float ang, int size, CString txt, CString txt1, float Rotation) override;
	void AddVertLine(float* strPoint, float dz) override;
	void Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) override;
	void DrawCoordSys();
	void DrawAxe(char Name);
public:
	HGLRC ghRC;
	HDC ghDC;
	GLvoid initializeGL();
	void calc_angles(float x, float y, float z);
	COGLPipePresenter(CPipeArray* PipeArray, CGLRenderer* rend, CRotator& _rot, CViewSettings& _viewSettings, wxWindow*parent);
	CGLRenderer* m_pRenderer;
	void Draw(CRect ClientRect, bool Printing);
	void DrawDottedRect(CDC* pDC, const CRect& rc, CRect clr);

	~COGLPipePresenter();
	void AddOpor(Pipe& p);
	void Print(CDC* pDC, CPrintInfo* pInfo, CRotator* Rot, HWND hWnd);
	void PrepareBmp(CDC* pDC, HWND hWnd, CRect ClientRect);
private:
	void set_view();
	wxGLContext context;

public:
	void PushMatrixes(void);
	void PopMatrixes(void);
};

//---------------------------------------------------------------------------
typedef struct _Render
{
	HDC hDC, hMemDC;
	HGLRC hglRC;
	HBITMAP hBm, hBmOld;
	CRect bmRect;
	//HPALETTE hPal, hPalOld; //hPal, hPalOld, binInfo will only be used when running in 8 bit mode.
	//BYTE biInfo[sizeof(BITMAPINFOHEADER) + 256 * sizeof (RGBQUAD)];
	void* lpBits;
} RENDER;

void InitializeGlobal(HWND hWndDlg);
HBITMAP CreateDIBSurface(HWND hWndDlg);
BOOL PrepareDIBSurface(void);
void CreateRGBPalette(void);
void CleanUp(HWND hWndDlg);

CString GetPartialName(CString Name);


#endif

