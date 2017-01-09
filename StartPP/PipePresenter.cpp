//---------------------------------------------------------------------------
#include "stdafx.h"

#include "PipePresenter.h"
#include "Rotate.h"
#include "PipeAndNode.h"
#include "Colors.h"
//#include "GlRenderer.h"
#include "HSV2RGB.h"
#include <stdlib.h>

extern float Round(float x, int N);
//---------------------------------------------------------------------------
TColor Pipe_Colors[] = {clGreen,clBlue,clGreen,clAqua,clNavy,clMaroon,clPurple};

TColor getPipeColor(int nColor)
{
	int H = (nColor * 101 + 120) % 360;
	int S = 100;
	int V = 60;//100;

	return CHSV2RGB::Hsv2Rgb(H, S, V); //Pipe_Colors[nColor>Max_pipe_type? 0 : nColor];
}


//---------------------------------------------------------
CPipePresenter::CPipePresenter(CPipeArray* PipeArray, CRotator& _rot, CViewSettings& _viewSettings):
	m_ViewSettings(_viewSettings), NumPipes(0), NumNodes(0), rot(_rot), pvecSel(nullptr),
	x_min(0), x_max(0), y_min(0), y_max(0), z_min(0), z_max(0)
{
	PeremScale = 100;
	//ShowPerem = ShowNapr = false;

	PipeArr = PipeArray;
	Scl = 10;
	PointSize = 4;
	OtvodSize = 2 * PointSize;
	//ShowElms = ShowDims = ShowPoints = ShowNums = true;
	//ShowAProf = ShowDiam = false;

	//rst=nullptr;
	Result = new TResult;
};

CPipePresenter::~CPipePresenter()
{
	delete Result;
}

void CPipePresenter::SetBounds(float* p)
{
	float p1[3] = {p[0],p[1],p[2]};
	Rotate(p1[0], p1[1], p1[2]);
	x_min = (p1[0] > x_min) ? x_min : p1[0];
	x_max = (p1[0] < x_max) ? x_max : p1[0];
	y_min = (p1[1] > y_min) ? y_min : p1[1];
	y_max = (p1[1] < y_max) ? y_max : p1[1];
	z_min = (p1[2] > z_min) ? z_min : p1[2];
	z_max = (p1[2] < z_max) ? z_max : p1[2];
}

//inline float max(float x,float y)
//{
//	return (x>y)?x:y;
//}
void CPipePresenter::Format(CString& txt, float val)
{
	val = Round(val, 3);
	txt = CString::Format(_T("%g"), val);
	if (txt.Find(_T(",")) == -1 && txt.Find(_T("."))==-1)
		txt += _T(",0");
}

extern float CalcAng(float dx, float dy);
extern float NormAng(float ang);
extern float CalcAngProf(float x, float y, float z);
float Sgn(float x);

void CViewSettings::Rotate(CRotator& rot, const CPoint& ptCenter, const CPoint& pt, const CPoint& ptDown, FLOAT_TYPE z_rot1, FLOAT_TYPE x_rot1, FLOAT_TYPE Xorg1, FLOAT_TYPE Yorg1)
{
	int cx = ptCenter.x;
	int cy = ptCenter.y;
	rot.SetRot(z_rot1, x_rot1);
	float zr = (pt.x - ptDown.x) * atan(1.0f) / 45 / 2;
	float xr = (pt.y - ptDown.y) * atan(1.0f) / 45 / 2;
	float x = (cx - Xorg1) / ScrScale;
	float y = (Yorg1 - cy) / ScrScale;
	float z = y * sin(x_rot1) / cos(x_rot1);
	rot.Rotate_1(x, y, z);
	Plan = false;
	rot.SetRot(z_rot1 + zr, x_rot1 + xr);
	rot.Rotate(x, y, z);
	Xorg = cx - x * ScrScale;
	Yorg = cy + y * ScrScale;
}

void CViewSettings::Zoom(float S, const CPoint& pt, CPoint* ptCenter)
{
	int cx = pt.x;
	int cy = pt.y;
	ScrScale *= S;
	if (ptCenter)
	{
		Xorg = (Xorg - ptCenter->x) * S + cx;
		Yorg = (Yorg - ptCenter->y) * S + cy;
	}
	else
	{
		Xorg = (Xorg - cx) * S + cx;
		Yorg = (Yorg - cy) * S + cy;
	}
}

void CViewSettings::Translate(int dx, int dy)
{
	Xorg += dx;
	Yorg += dy;
}

// Нарисовать один участок трубы
void CPipePresenter::DrawPipe(int NAYZ, Pipe& p, float* startPoint, float* endPoint)
{
	float midPoint[3];
	float dx, dy, dz;

	float ang, ang1, ang2, ang3, NumPointDist;
	bool IsStartPoint, Mirror = false;
	Pipe p1;
	bool Otvod;
	float l, L1;

	CurPipe = p;
	dx = p.dx;
	dy = p.dy;
	dz = p.dz;
	Rotate(dx, dy, dz);
	ang = CalcAng(dx, dy);
	ang3 = ang;
	ang2 = NormAng(ang);
	IsStartPoint = (NAYZ == 0);
	if (!IsStartPoint)
	{
		NumPipes++;
		AddLine(startPoint, endPoint, NAYZ, p);

		for (int i = 0; i < 3; i++) midPoint[i] = (startPoint[i] + endPoint[i]) / 2;

		// ---------------------------- Простановка размера ----------------------
		if (m_ViewSettings.ShowDims)
		{
			if (!m_ViewSettings.Plan || (m_ViewSettings.Plan && (dx * dx + dy * dy != 0)))
			{
				if (p.Podush)
					AddPodushFrom(startPoint, endPoint, PointSize / 2, ang2);
				if (p.Podzem)
				{
					CString txt;
					if (m_ViewSettings.Plan)
					{
						txt=txt.Format(_T("%.1f"), CalcAngProf(dx, dy, dz));
						if (txt.Right(2) == _T(",0")) txt = txt.Left(txt.Length() - 2);
						txt = txt + _T("°");
						if (m_ViewSettings.ShowAProf)
							AddTextFrom(midPoint, Scl, ang2, TextSmall, txt, ang2, tNONE);
						Format(txt, sqrt(dx * dx + dy * dy));
					}
					else
					{
						Format(txt, sqrt(dx * dx + dy * dy + dz * dz));
					};
					CString txt1 = CString::Format(_T("%.1f %.1f"), p.VIZA, p.VIZA2);
					Add2TextFrom(midPoint, Scl, ang2 + 4 * atan(1.0f), TextSmall, txt, txt1, ang2);
				}
				else
				{
					if (m_ViewSettings.Plan)
					{
						CString txt;
						Format(txt, sqrt(dx * dx + dy * dy));
						AddTextFrom(midPoint, Scl, ang2 + 4 * atan(1.0f), TextSmall, txt, ang2, tNONE);
						txt=txt.Format(_T("%.1f"), CalcAngProf(dx, dy, dz));
						if (txt.Right(2) == _T(",0")||txt.Right(2)==_T(".0")) txt = txt.Left(txt.Length() - 2);
						txt = txt + _T("°");
#ifdef SHOW_INDX
						AddTextFrom(midPoint,Scl,ang2, 10, p.INDX,ang2,tNONE);
#else
						if (m_ViewSettings.ShowAProf) AddTextFrom(midPoint, Scl, ang2, TextSmall, txt, ang2, tNONE);
#endif
					}
					else
					{
						CString txt;
						Format(txt, sqrt(dx * dx + dy * dy + dz * dz));
						AddTextFrom(midPoint, Scl, ang2 + 4 * atan(1.0f), TextSmall, txt, ang2, tNONE);
					}
				}
			}
			else
			{ // Вертикальный участок в плане
				AddVertLine(endPoint, dz);
			}
		}
	} // !IsStartPoint
	NumPointDist = Scl * 2;
	CPipeArrayContext cnt;
	p1.EndP = -1;
	if (PipeArr->HasOut(p.EndP))
		p1 = PipeArr->OutFirst(p.EndP, cnt);
	Pipe p2;
	p2.EndP = -1;
	if (p1.EndP >= 0 && PipeArr->HasOutNext(cnt))
		p2 = PipeArr->OutNext(cnt);
	if (p2.EndP >= 0)
	{
		Rotate(p2.dx, p2.dy, p2.dz);
		float ang4 = CalcAng(p2.dx, p2.dy);
		Rotate(p1.dx, p1.dy, p1.dz);
		ang1 = CalcAng(p1.dx, p1.dy);
		if (fabs(ang4 - ang) < fabs(ang1 - ang))
		{
			Pipe tmp = p1;
			p1 = p2;
			p2 = tmp;
		}
	}
	if (p1.EndP >= 0)
	{
		Mirror = false;
		Rotate(p1.dx, p1.dy, p1.dz);
		ang1 = CalcAng(p1.dx, p1.dy);
		if ((fabs(p1.dx) + fabs(p1.dy)) < 0.001)
		{
			// Вертикальный участок - следующий
			p1.EndP = -1;
			if (PipeArr->HasOut(p1.EndP))
				p1 = PipeArr->OutFirst(p1.EndP, cnt);
			ang1 = (p1.EndP >= 0) ? CalcAng(p1.dx, p1.dy) : ang;
		};
		if ((fabs(p.dx) + fabs(p.dy)) < 0.001)
		{
			// Вертикальный участок - текущий
			if (PipeArr->HasIn(NAYZ))
			{
				p1 = PipeArr->InFirst(NAYZ, cnt);
				ang = (p1.EndP >= 0) ? CalcAng(p1.dx, p1.dy) : ang1;
			}
			else
				ang = ang1;
			ang2 = NormAng(ang);

			Mirror = true;
			NumPointDist = 2.2f * Scl;
		};
		if (IsStartPoint)
			ang = ang1;
		else
		{
			if (fabs(ang1 - ang) > 0.01)
			{
				if (ang1 > ang)
					ang = (ang + ang1) / 2 + 4 * atan(1.0f);
				else
					ang = (ang + ang1) / 2;
			}
			else
				ang = ang2;
		};
		if (p2.EndP >= 0)
		{
			if (Sgn(p2.dx) == -Sgn(sin(ang)) && Sgn(p2.dy) == Sgn(cos(ang)))
				Mirror = !Mirror;
		}
	}
	else // Крайний узел на чертеже
		ang = ang2;
	if (Mirror) ang = ang + 4 * atan(1.0f);

	// ----- Рисование опор и изделий в узле
	switch (p.MNEO)
	{
	case elMertOp:
	case elUprOp:
	case elGestPd:
		AddNodeElement(endPoint, p.MNEO, ang);
		NumPointDist = Scl * 4.0f;
		break;
	case elSkOp:
		AddNodeElement(endPoint, elSkOp, ang);
		NumPointDist = Scl * 2.5f;
		break;
	case elNaprOp:
		AddNodeElement(endPoint, elNaprOp, ang);
		NumPointDist = Scl * 2.0f;
		break;
	case elNone: break;
	case elCompOs: break;
	case elCompUg: break;
	case elArmat: break;
	case elOtvodS: break;
	case elOtvodI: break;
	case elOtvodF: break;
	case elDiamChange: break;
	case elRast: break;
	case elSg: break;
	case elSelect: break;
	case elTroinic: break;
	default: break;
	}

	Otvod = false;
	switch (p.MNEA)
	{
	case elCompOs:
	case elCompUg:
	case elArmat:
		AddNodeElement(endPoint, p.MNEA, ang);
		NumPointDist = std::max(NumPointDist,Scl * 2);
		break;
	case elOtvodS:
	case elOtvodI:
	case elOtvodF:
		Otvod = true;
		break;
	case elTroinic:
		AddNodeElement(endPoint, elTroinic, ang);
		NumPointDist = Scl * 2.0f;
		break;
	case elNone: break;
	case elMertOp: break;
	case elSkOp: break;
	case elNaprOp: break;
	case elDiamChange: break;
	case elRast: break;
	case elSg: break;
	case elGestPd: break;
	case elUprOp: break;
	case elSelect: break;
	default: break;
	}

	switch (p.TIDE)
	{
	case elRast:
	case elSg:
		AddNodeElement(endPoint, p.TIDE, ang);
		NumPointDist = std::max(NumPointDist,Scl * 2.5f);
		break;
	case elNone: break;
	case elMertOp: break;
	case elSkOp: break;
	case elNaprOp: break;
	case elCompOs: break;
	case elCompUg: break;
	case elArmat: break;
	case elOtvodS: break;
	case elOtvodI: break;
	case elOtvodF: break;
	case elDiamChange: break;
	case elGestPd: break;
	case elUprOp: break;
	case elSelect: break;
	case elTroinic: break;
	default: break;
	}

	//---------- Рисование перехода диаметров -------------------------
	if (p.EndP >= 0)
	{
		p1.EndP = -1;
		if (PipeArr->HasOut(p.EndP))
			p1 = PipeArr->OutFirst(p.EndP, cnt);
		if (p1.EndP >= 0 && !PipeArr->HasOutNext(cnt))
		{ // Только один выходящий участок
			if (p.Diam != p1.Diam)
			{
				l = sqrt(p.dx * p.dx + p.dy * p.dy + p.dz * p.dz);
				L1 = sqrt(p1.dx * p1.dx + p1.dy * p1.dy + p1.dz * p1.dz);
				if ((l != 0) && (L1 != 0) &&
					(fabs(p1.dx / L1 - p.dx / l) < 0.0001) &&
					(fabs(p1.dy / L1 - p.dy / l) < 0.0001) &&
					(fabs(p1.dz / L1 - p.dz / l) < 0.0001))
				{
					AddNodeElement(endPoint, elDiamChange,
					               p.Diam > p1.Diam ? ang3 : ang3 + 4 * atan(1.0f));
					NumPointDist = std::max(NumPointDist,Scl * 2);
				}
			}
		}
	}
	//--------------------- Простановка маркера точки --------------------
	if (m_ViewSettings.ShowPoints)
	{
		if (Otvod)
		{
			AddCircle(endPoint, OtvodSize);
		}
		AddCircle(endPoint, PointSize);
		AddCircle(startPoint, PointSize);
	}
	//------------------- Простановка отметки выбора узла ---------------
	if (pvecSel->SelNAYZ == pvecSel->SelKOYZ && pvecSel->SelNAYZ == p.EndP)
		AddNodeElement(endPoint, elSelect, atan(1.0f));

	if (pvecSel->Contains(p.EndP, p.EndP))
		AddNodeElement(endPoint, elSelect, atan(1.0f));
	//--------------------- Простановка номера точки --------------------
	if (NAYZ != 0)
	{
		if (!Points[NAYZ].set) NumNodes++;
		if (m_ViewSettings.ShowNums)
			AddNodeNum(startPoint, NumPointDist, ang2, NAYZ, 25);
		Points[NAYZ].set = true;
	}
	if (p.EndP >= 0 && !Points[p.EndP].set) NumNodes++;
	if (m_ViewSettings.ShowNums)
		AddNodeNum(endPoint, NumPointDist, ang, p.EndP, 25);
	if (p.EndP >= 0)
		Points[p.EndP].set = true;
	//--------------------------------------------------------------------
};


void CPipePresenter::DrawPipes(int NAYZ, float* L, bool NoDraw)
{
	float E[3];
	Pipe* p;
	CPipeArrayContext cnt;
	SetBounds(L);
	// --------- Рисуем трубы, исходящие из узла
	for (p = &(PipeArr->OutFirst(NAYZ, cnt)); PipeArr->HasOut(cnt);)
	{
		if (!p->Drawed)
		{
			p->Drawed = true;
			p->Seen = true;
			E[0] = L[0] + p->dx;
			E[1] = L[1] + p->dy;
			E[2] = L[2] + p->dz;
			SetBounds(E);
			if (!NoDraw) DrawPipe(NAYZ, *p, L, E);
			if (PipeArr->InCount(NAYZ) <= 1 && PipeArr->OutCount(NAYZ) <= 1)
			{
				NAYZ = p->EndP;
				p = &PipeArr->OutFirst(p->EndP, cnt);
				L[0] = E[0];
				L[1] = E[1];
				L[2] = E[2];
				continue;
			}
			DrawPipes(p->EndP, E, NoDraw);
			if (NAYZ == 0) return;
		}
		p = &PipeArr->OutNext(cnt);
	};
	//--------- Рисуем трубы, входящие в узел
	for (p = &(PipeArr->InFirst(NAYZ, cnt)); PipeArr->HasIn(cnt);)
	{
		if (!p->Drawed)
		{
			p->Drawed = true;
			p->Seen = true;
			E[0] = L[0] - p->dx;
			E[1] = L[1] - p->dy;
			E[2] = L[2] - p->dz;
			SetBounds(E);
			if (!NoDraw) DrawPipe(p->StrP, *p, E, L);
			if (PipeArr->InCount(NAYZ) <= 1 && PipeArr->OutCount(p->StrP) <= 1)
			{
				NAYZ = p->StrP;
				p = &PipeArr->InFirst(p->StrP, cnt);
				L[0] = E[0];
				L[1] = E[1];
				L[2] = E[2];
				continue;
			}
			if (p->StrP != 0) DrawPipes(p->StrP, E, NoDraw);
		}
		p = &PipeArr->InNext(cnt);
	}
};

void CPipePresenter::ScanBounds(int NAYZ, float* L)
{
	float E[3];
	Pipe* p;
	CPipeArrayContext cnt;
	SetBounds(L);
	// --------- Рисуем трубы, исходящие из узла
	bool succ = PipeArr->HasOut(NAYZ);
	for (p = &(PipeArr->OutFirst(NAYZ, cnt)); succ;)
	{
		if (!p->Seen)
		{
			p->Seen = true;
			E[0] = L[0] + p->dx;
			E[1] = L[1] + p->dy;
			E[2] = L[2] + p->dz;
			SetBounds(E);
			ScanBounds(p->EndP, E);
			if (NAYZ == 0) return;
		}
		succ = PipeArr->HasOutNext(cnt);
		if (succ) p = &(PipeArr->OutNext(cnt));
	};
	//--------- Рисуем трубы, входящие в узел
	succ = PipeArr->HasIn(NAYZ);
	for (p = &(PipeArr->InFirst(NAYZ, cnt)); succ;)
	{
		if (!p->Seen)
		{
			p->Seen = true;
			E[0] = L[0] - p->dx;
			E[1] = L[1] - p->dy;
			E[2] = L[2] - p->dz;
			SetBounds(E);
			if (p->StrP != 0) ScanBounds(p->StrP, E);
		}
		succ = PipeArr->HasInNext(cnt);
		if (succ) p = &(PipeArr->InNext(cnt));
	}
}


void CPipePresenter::init_pipes()
{
	//for (int i = 0; i<MaxPipes;i++)
	//	Points[i].set = FALSE;
	Points.clear();
	PipeArr->Init();
	PipeArr->Intervals.clear();
}


void CPipePresenter::copy_pipes(const std::vector<CPipeAndNode>& vec)
{
	//rst = tbl;
	PipeArr->Intervals.clear();
	x_min = x_max = y_min = y_max = 0;
	Points.clear();
	PipeArr->copy_pipes(vec, &rot);
	Result->copy();
}

void CPipePresenter::DrawMain(bool NoDraw)
{
	int i;
	bool Found;
	bool First = true;
	float Space = 20;
	NumPipes = 0;
	NumNodes = 0;
	x_min = x_max = y_min = y_max = z_min = z_max = 0;
	init_pipes();
	do
	{
		Found = false;
		PipeArr->FindNotDrawn(i, Found);
		if (Found)
		{
			float firstPoint[3] = {0,0,0};
			if (!First)
			{
				float ox_min = x_min, ox_max = x_max,
					oy_min = y_min, oy_max = y_max,
					oz_min = z_min, oz_max = z_max;
				x_min = x_max = y_min = y_max = z_min = z_max = 0;
				ScanBounds(i, firstPoint);
				if ((x_max - x_min) > (y_max - y_min))
				{
					firstPoint[0] = (ox_min + ox_max) / 2 - (x_max + x_min) / 2;
					firstPoint[1] = oy_min - Space - y_max;
				}
				else
				{
					firstPoint[0] = ox_max + Space - x_min;
					firstPoint[1] = (oy_min + oy_max) / 2 - (y_max + y_min) / 2;
				}
				x_min = ox_min;
				x_max = ox_max;
				y_min = oy_min;
				y_max = oy_max;
				z_min = oz_min;
				z_max = oz_max;
			}
			else First = false;
			DrawPipes(i, firstPoint, NoDraw);
			//        cnv->Rectangle(ToScrX(x_min),ToScrY(y_min),ToScrX(x_max),ToScrY(y_max));
		}
	}
	while (Found);
}
