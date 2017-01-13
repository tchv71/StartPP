//---------------------------------------------------------------------------
#ifndef ShowPipesH
#define ShowPipesH
#include <vector>
#include <map>
#include <set>
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


struct SelStr
{
	SelStr(int N, int K) : SelNAYZ(N), SelKOYZ(K)
	{
	};

	SelStr() : SelNAYZ(-1), SelKOYZ(-1)
	{
	};

	int SelNAYZ;
	int SelKOYZ;
};

inline bool operator<(const SelStr& _Left, const SelStr& _Right)
{
	return _Left.SelNAYZ < _Right.SelNAYZ ||
		(!(_Right.SelNAYZ < _Left.SelNAYZ) && _Left.SelKOYZ < _Right.SelKOYZ);
}

typedef std::set<SelStr> SelVec;


class CSelVec : protected SelVec
{
public:
	int SelNAYZ, SelKOYZ;

	bool Contains(float S, float E)
	{
		return find(SelStr(int(S), int(E))) != end();
	}

	bool Contains(int S, int E)
	{
		return find(SelStr(S, E)) != end();
	}

	size_t size() const
	{
		return SelVec::size();
	}

	SelVec::iterator begin()
	{
		return SelVec::begin();
	}

	SelVec::iterator end()
	{
		return SelVec::end();
	}

	void clear()
	{
		SelVec::clear();
	}

	std::pair<iterator,bool> insert(const SelStr& val)
	{
		return SelVec::insert(val);
	}

	void erase(const SelStr& val)
	{
		SelVec::erase(val);
	}
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
	void Zoom(float S, const CPoint& pt, CPoint* ptCenter = nullptr);
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

	Pipe CurPipe;
	float Scl;
	float PointSize, OtvodSize;
	static const int nTickSize = 5;


	virtual void AddNodeElement(float* p, TNodeElement el, float ang) =0;
	virtual void AddLine(float* p1, float* p2, int NAYZ, Pipe& p) =0;
	virtual void AddPodushFrom(float* p1, float* p2, float Dist, float ang) =0;
	virtual void AddCircle(float* p, float rad) =0;
	virtual void AddNodeNum(float* p, float Dist, float ang, int NodeNum, float rad) =0;
	virtual void AddTextFrom(const float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode) =0;
	virtual void Add2TextFrom(float* p, float Dist, float ang, int size, CString txt, CString txt1, float Rotation) =0;
	virtual void AddVertLine(float* strPoint, float dz) =0;
	virtual void Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) =0;

	void DrawPipe(int NAYZ, Pipe& p, float* startPoint, float* endPoint);
	void DrawPipes(int NAYZ, float* L, bool NoDraw);
	void SetBounds(float* P);
	void ScanBounds(int NAYZ, float* L);
public:
	CViewSettings& m_ViewSettings;
	int NumPipes;
	int NumNodes;
	void DrawMain(bool NoDraw);

	struct SPoint
	{
		SPoint() : set(false), x(0), y(0), z(0)
		{
		};

		bool set;
		float x, y, z;
	};

	std::map<int, SPoint> Points;

	CRotator& rot;
	//TTable *rst;
	CSelVec* pvecSel;

	CPipeArray* PipeArr;
	TResult* Result;

	CPipePresenter(CPipeArray* PipeArray, CRotator& _rot, CViewSettings& _ViewSettings);

	void SetPipeArray(CPipeArray* PipeArray)
	{
		PipeArr = PipeArray;
	};

	void init_pipes(void);
	void copy_pipes(const std::vector<CPipeAndNode>& vec);
	float PeremScale;
	//	void  PushFlags(void);
	//	void  PopFlags(void);
	float x_min, x_max, y_min, y_max, z_min, z_max;
	virtual ~CPipePresenter();
	static void Format(CString& txt, float val);
};

extern TColor getPipeColor(int nColor);


//class TStatusBar;

#endif

