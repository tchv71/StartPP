#pragma once
#include "PipePresenter.h"
#include <set>

class CScreenPipePresenter : public CPipePresenter
{
protected:
	CDC* cnv;
	CRect m_ClientRect;

	int ToScrX(float x);
	int ToScrY(float y);
	void DrawList(float* p, const POINT* list, float ang);
	void DrawAxis(float x, float y, float z, char Name, CRotator* Rot);

	void AddNodeElement(float* p, TNodeElement el, float ang) override;
	void AddLine(float* p1, float* p2, int NAYZ, Pipe& p) override;
	virtual void AddLineFrom(float* p1, float* p2, float Dist, float ang);
	void AddPodushFrom(float* p1, float* p2, float Dist, float ang) override;
	void AddCircle(float* p, float rad) override;
	void AddNodeNum(float* p, float Dist, float ang, int NodeNum, float rad) override;
	virtual void Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) override;

	void AddTextFrom(float* p, float Dist, float ang, int size,
	                 CString txt, float Rotation, int TextMode) override;
	void Add2TextFrom(float* p, float Dist, float ang, int size,
	                  CString txt, CString txt1, float Rotation) override;
	void AddVertLine(float* strPoint, float dz) override;
	//float oScrScale,oXorg,oYorg;
	void SelectPS_In(int NAYZ, int type);
	void SelectPS_Out(int KOYZ, int type);
	std::vector<SelStr> SelectPipesTo_In(int NAYZ);
	std::vector<SelStr> SelectPipesTo_Out(int NAYZ);

public:
	CString FontName;
	float ElemScale;
	void IntSelectPipe(int X, int Y, std::set<int>* pNodeSet = nullptr);
	void SelectPipe(int X, int Y, bool bAdd);
	void SelectPipesTo(int X, int Y, bool bAdd);
	void SelectPipeSegment(int X, int Y);
	void Draw(CDC* pCanvas, CRotator* Rot, CRect ClientRect);
	void ZoomAll(const CRect clr, int Border);
	CScreenPipePresenter(CPipeArray* PipeArray, CRotator& _rot, CViewSettings& view_se_view_settings);
	~CScreenPipePresenter();
	//void  SaveViewState();
	//void  RestoreViewState();
};

inline int CScreenPipePresenter::ToScrX(float x)
{
	return int(floor(m_ViewSettings.Xorg + x * m_ViewSettings.ScrScale + 0.5f));
}

inline int CScreenPipePresenter::ToScrY(float y)
{
	return int(floor(m_ViewSettings.Yorg - y * m_ViewSettings.ScrScale + 0.5f));
}

