//---------------------------------------------------------------------------
#ifndef ShowPipesH
#define ShowPipesH
#include <vector>
#include <map>
//#include <set>
#include "PipeAndNode.h"
#include "PipeArray.h"
#include "Colors.h"
#include "SvTypes.h"

//---------------------------------------------------------------------------

#define INVALID_LOOP 10000
#define INVALID_LOOP_COLOR clRed

const int Max_pipe_type = 100;
const int TextSmall = 12;

//const int MaxPipes=1000;

class CRotator;


struct TPoint3D
{
	float dx, dy, dz;
};

class TResult
{
public:
	//TPoint3D Perem[MaxPipes];
	void copy();
};



class CViewSettings
{
public:
	CViewSettings() : Plan(true), ScrScale(0), Xorg(0), Yorg(0)
	{
		ShowPerem = ShowNapr = false;
		ShowElms = ShowDims = ShowPoints = ShowNums = true;
		ShowAProf = ShowDiam = false;
	}

	void Rotate(CRotator& rot, const CPoint& ptCenter, const CPoint& pt, const CPoint& ptDown, FLOAT_TYPE z_rot1, FLOAT_TYPE x_rot1, FLOAT_TYPE Xorg1, FLOAT_TYPE Yorg1);
	void Zoom(float S, const CPoint &pt, const CPoint *ptCenter = nullptr);
	void Translate(int dx, int dy);
	bool Plan;
	float ScrScale, Xorg, Yorg;
	bool ShowElms, ShowDiam, ShowDims, ShowPoints, ShowNums, ShowAProf;
	bool ShowPerem, ShowNapr;
};

class CPipePresenter
{
protected:
	enum
	{
		tNONE=0,
		tUNDERLINE=1,
		tCONDENSE=2,
		tOVERLINE=4
	};

	CViewSettings& m_ViewSettings;
public:
	struct SPoint
	{
		SPoint() : set(false), x(0), y(0), z(0)
		{
		};

		bool set;
		float x, y, z;
	};

	std::map<int, SPoint> m_Points;
protected:
	CRotator& m_rot;
	//TTable *rst;

public:
	CSelVec* m_pvecSel;
	CPipeArray* m_pPipeArr;
	TResult* m_pResult;
protected:
	Pipe CurPipe;
	float Scl;
	float PointSize, OtvodSize;
	static const int nTickSize = 5;
    mutable float m_fMaxDist;


	virtual void AddNodeElement(const float *p, TNodeElement el, float ang) =0;
	virtual void AddLine(const float *p1, const float *p2, int NAYZ, const Pipe &p) =0;
	virtual void AddPodushFrom(const float *p1, const float *p2, float Dist, float ang) =0;
	virtual void AddCircle(const float *p, float rad) =0;
	virtual void AddNodeNum(const float *p, float Dist, float ang, int NodeNum, float rad) =0;
	virtual void AddTextFrom(const float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode) =0;
	virtual void Add2TextFrom(float* p, float Dist, float ang, int size, CString txt, CString txt1, float Rotation) =0;
	virtual void AddVertLine(const float *strPoint, float dz) =0;
	virtual void Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) =0;

	void DrawPipe(int NAYZ, const Pipe &p, const float *startPoint, const float *endPoint);
	void DrawPipes(int NAYZ, float* L, bool NoDraw);
	void SetBounds(float* P);
	void ScanBounds(int NAYZ, float* L);
public:
	int m_NumPipes;
	int m_NumNodes;
	void DrawMain(bool NoDraw);


	CPipePresenter(CPipeArray* PipeArray, CRotator& _rot, CViewSettings& _ViewSettings);

	void SetPipeArray(CPipeArray* PipeArray)
	{
		m_pPipeArr = PipeArray;
	};

	void init_pipes(void);
	void copy_pipes(const std::vector<CPipeAndNode>& vec);
	float PeremScale;
	//	void  PushFlags(void);
	//	void  PopFlags(void);
	float x_min, x_max, y_min, y_max, z_min, z_max;
	virtual ~CPipePresenter();
	static void Format(CString& txt, float val);

	void
	DrawDims(int NAYZ, const Pipe &p, const float *startPoint, const float *endPoint, float dx, float dy, float dz,
			 float ang2);

	void DetemineAngles(int NAYZ, const Pipe &p, float &ang2, float &ang);

	void DrawDiamChange(const Pipe &p, const float *endPoint, float ang3, float &NumPointDist);

	void DrawNodeElements(const Pipe &p, const float *endPoint, float ang, float &NumPointDist, bool &Otvod);

	void DrawPointMark(const float *startPoint, const float *endPoint, bool Otvod);

	void DrawNodeSelection(const Pipe &p, const float *endPoint);

	void DrawNodeNum(int NAYZ, const Pipe &p, const float *startPoint, const float *endPoint, float ang, float ang2,
					 float NumPointDist);
};

extern TColor getPipeColor(int nColor);


//class TStatusBar;

#endif

