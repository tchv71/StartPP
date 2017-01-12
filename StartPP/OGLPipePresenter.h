//---------------------------------------------------------------------------
#ifndef OGLShowPipesH
#define OGLShowPipesH
//#include <GL/gl.h>
#include <wx/glcanvas.h>
//#include <printers.hpp>
#include "ScreenPipePresenter.h"

class CGLFontRenderer;
#ifndef __WXMSW__
typedef void* HGLRC;
typedef void* HBITMAP;
typedef void* LPVOID;
typedef void* HDC;
#endif

class CPrintDialog;

struct CPrintInfo // Printing information structure
{
	CPrintInfo() {};
	~CPrintInfo() {};

	CRect m_rectDraw;        // rectangle defining current usable page area
};


class COGLPipePresenter: public CScreenPipePresenter
{
	void SetupLighting() const;
	void draw_styk(float l_gen, float rad, float str_x_rot, float str_tg_2, float end_tg_2, float t1, float t2, bool DrawEnd) const;
//	void InitGLScene();
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
	void DrawCoordSys() const;
	static void Project(double x, double y, double z, double& wx, double& wy, double& wz, bool bInvertY=false);
	void DrawAxe(char Name) const;
public:
	GLvoid initializeGL() const;
	COGLPipePresenter(CPipeArray* PipeArray, CGLFontRenderer* rend, CRotator& _rot, CViewSettings& _viewSettings, wxGLCanvas *parent);
	CGLFontRenderer* m_pRenderer;
	void Draw(CRect ClientRect, bool Printing);
	void DrawDottedRect(const CRect& rc, CRect clr);

	~COGLPipePresenter();
	void AddOpor(Pipe& p) const;
	void Print(CDC* pDC, const wxRect& rectPrint);
private:
	void set_view() const;
public:
	void PushMatrixes(bool bInvertY=true) const;
	static void PopMatrixes(void);
	wxGLCanvas *canvas;
};

CString GetPartialName(CString Name);


#endif

