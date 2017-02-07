#include "stdafx.h"
#include "ScreenPipePresenter.h"
//#include "MainFrm.h"
#include "Colors.h"
#include "Rotate.h"
//#include "resource.h"
#include "Strings.h"
#include "wx/graphics.h"
#include <cmath>
//extern LPCTSTR LoadStr(UINT nID);

using namespace std;

//extern float RadToDeg(float x);

const POINT MertOp[] = {{0, 0},{0, 5},
	{-3, 5},{3, 5},
	{-3, 5},{-1, 7},
	{-1, 5},{1, 7},
	{1, 5},{3, 7},
	{100, 100}};

const POINT SkOp[] = {{1,-3},{1, 3},
	{1, 3},{-1, 3},
	{-1, 3},{-1,-3},
	{-1,-3},{1,-3},
	{100,100}};

const POINT NaprOp[] = {{-3, 1},{3, 1},
	{-3,-1},{3,-1},
	{0, -1},{0,-3},
	{100,100}};

const POINT UprOp[] = {{0, 0},{2, 1},
	{2, 1},{-2, 3},
	{-2, 3},{2, 5},
	{2, 5},{0, 6},
	{0, 6},{0, 7},
	{-2, 7},{2, 7},
	{100,100}};

const POINT GestPd[] = {{0, 0},{0, 7},
	{-2, 7},{2, 7},
	{100,100}};

const POINT Armat[] = {{-4,-3},{4, 3},
	{4, 3},{4,-3},
	{4,-3},{-4, 3},
	{-4, 3},{-4,-3},
	{100,100}};

const POINT CompOs[] = {{3, 2},{-2, 2},
	{-2, 2},{-3, 1},
	{-3, 1},{-3,-1},
	{-3,-1},{-2,-2},
	{-2,-2},{3,-2},
	{100,100}};

const POINT CompUg[] = {{-3,-2},{-3, 2},
	{-3, 2},{-1,-2},
	{-1,-2},{-1, 2},
	{-1, 2},{1,-2},
	{1,-2},{1, 2},
	{1, 2},{3,-2},
	{3,-2},{3, 2},
	{100,100}};

const POINT DiamChange[] =
{{3, 0},{-2, 3},
	{-2, 3},{-2,-3},
	{-2,-3},{3, 0},
	{100,100}};

const POINT Sg[] =
{{-2, 3},{-2,-3},
	{-2, 2},{-4, 2},
	{-4, 2},{-3, 1},
	{-4, 2},{-3, 3},
	{-2,-2},{-4,-2},
	{-4,-2},{-3,-1},
	{-4,-2},{-3,-3},
	{100,100}};

const POINT Rast[] =
{{-2, 3},{-2,-3},
	{-2, 2},{-4, 2},
	{-2, 2},{-3, 1},
	{-2, 2},{-3, 3},
	{-2,-2},{-4,-2},
	{-2,-2},{-3,-1},
	{-2,-2},{-3,-3},
	{100,100}};

const POINT Select[] =
{{0,-5},{0,5},
	{5,0},{-5,0},
	{100,100}};

const POINT Troinic[] =
{{2,-2},{2, 2},
	{2, 2},{-2, 2},
	{-2, 2},{-2,-2},
	{-2,-2},{2,-2},
	{100,100}};

float elSize = 3;

void CScreenPipePresenter::DrawList(const float *p, const POINT* list, float ang) const
{
	int x = ToScrX(p[0]), y = ToScrY(p[1]);
	float s = sin(ang) * elSize * ElemScale;
	float c = cos(ang) * elSize * ElemScale;
	while (list->x != 100)
	{
		//cnv->MoveTo(int(floor(x + (list->x) * c + (list->y) * s + 0.5f)),
		//            int(floor(y - (list->x) * s + (list->y) * c + 0.5f)));
		//list++;
		//cnv->LineTo(int(floor(x + (list->x) * c + (list->y) * s + 0.5f)),
		//            int(floor(y - (list->x) * s + (list->y) * c + 0.5f)), );
		//list++;
		cnv->DrawLine(int(floor(x + (list->x) * c + (list->y) * s + 0.5f)), int(floor(y - (list->x) * s + (list->y) * c + 0.5f)),
			int(floor(x + (list[1].x) * c + (list[1].y) * s + 0.5f)), int(floor(y - (list[1].x) * s + (list[1].y) * c + 0.5f)));
		list += 2;
	}
}

void CScreenPipePresenter::AddNodeElement(const float *p, TNodeElement el, float ang)
{
	if (el == elSelect)
	{
		DrawList(p, Select, ang);
		return;
	}
	if (m_ViewSettings.ShowElms)
	{
		switch (el)
		{
		case elMertOp:
			DrawList(p, MertOp, ang);
			DrawList(p, MertOp, ang + 4 * atan(1.0f));
			break;
		case elSkOp:
			DrawList(p, SkOp, ang);
			break;
		case elNaprOp:
			DrawList(p, NaprOp, ang);
			break;
		case elArmat:
			DrawList(p, Armat, ang);
			break;
		case elCompOs:
			DrawList(p, CompOs, ang);
			break;
		case elCompUg:
			DrawList(p, CompUg, ang);
			break;
		case elUprOp:
			DrawList(p, UprOp, ang + 4 * atan(1.0f));
			break;
		case elGestPd:
			DrawList(p, GestPd, ang + 4 * atan(1.0f));
			break;

		case elDiamChange:
			elSize /= 2;
			DrawList(p, DiamChange, ang);
			elSize *= 2;
			break;
		case elRast:
			DrawList(p, Rast, ang);
			DrawList(p, Rast, ang + 4 * atan(1.0f));
			break;
		case elSg:
			DrawList(p, Sg, ang);
			DrawList(p, Sg, ang + 4 * atan(1.0f));
			break;
		case elTroinic:
			DrawList(p, Troinic, ang);
			break;
		case elNone: break;
		case elOtvodS: break;
		case elOtvodI: break;
		case elOtvodF: break;
		case elSelect: break;
		default: break;
		}
	}
}

const float SelectAperture = 10;

void CScreenPipePresenter::AddLine(const float *p1, const float *p2, int NAYZ, const Pipe &p)
{
	CPen cnvPen;
	int x1 = ToScrX(p1[0]), y1 = ToScrY(p1[1]);
	int x2 = ToScrX(p2[0]), y2 = ToScrY(p2[1]);

	TColor clr;
	if (p.P_type > Max_pipe_type)
		if (p.P_type == INVALID_LOOP)
		{
			clr = INVALID_LOOP_COLOR;
			//	cnv->Pen->Style=psDash;
		}
		else
			clr = getPipeColor(0);
	else
		clr = getPipeColor(p.P_type);
	wxPenStyle ps = wxPENSTYLE_SOLID;
	//for (unsigned i = 0; i<m_pvecSel->size(); i++)
	if (m_pvecSel->Contains(NAYZ, p.EndP))
	{
		ps = wxPENSTYLE_DOT ;
	}
	CPen pen(clr, 1, ps);
	cnv->SetPen(pen);

	//float pw=p.Diam/1000*m_ViewSettings.ScrScale;
	//           if (pw<1) pw=1;
	//if (ShowDiam && p.P_type!=INVALID_LOOP) cnv->Pen->Width=pw;
	//else cnv->pen->Width=ElemScale;
	/*
		if (rst!=nullptr &&(NAYZ==rst->FieldValues["NAYZ"])&&
			(p.EndP==rst->FieldValues["KOYZ"]))
			cnv->Pen->Style=psDot;
	*/
	cnv->DrawLine(x1, y1, x2, y2);
	//cnv->SelectObject(pOldPen);
	//cnv->Pen->Width=ElemScale;
	//cnv->Pen->Style=psSolid;

	Interval_ pi;
	pi.StrP = NAYZ;
	pi.EndP = p.EndP;
	pi.x1 = x1;
	pi.y1 = y1;
	pi.x2 = x2;
	pi.y2 = y2;
	pi.dx = p.dx;
	pi.dy = p.dy;
	pi.dz = p.dz;
	if (p.P_type == INVALID_LOOP)
		m_rot.Rotate_1(pi.dx, pi.dy, pi.dz);
	pi.Diam = SelectAperture;
	m_pPipeArr->Intervals.push_back(pi);
	/*
	if (ShowPerem) {
		//TColor oldc=cnv->Pen->Color;
		//cnv->Pen->Color=clBlack;
		float dx=m_pResult->Perem[NAYZ].dx,
			dy=m_pResult->Perem[NAYZ].dy,
			dz=m_pResult->Perem[NAYZ].dz;
		int   px1,py1,px2,py2;
		m_rot.Rotate(dx, dy, dz);

		px1=ToScrX(p1[0]+PeremScale*dx/1000);
		py1=ToScrY(p1[1]+PeremScale*dy/1000);

		dx=m_pResult->Perem[p.EndP].dx;
		dy=m_pResult->Perem[p.EndP].dy;
		dz=m_pResult->Perem[p.EndP].dz;
		m_rot.Rotate(dx, dy, dz);
		px2=ToScrX(p2[0]+PeremScale*dx/1000);
		py2=ToScrY(p2[1]+PeremScale*dy/1000);
		cnv->MoveTo(px1,py1);
		cnv->LineTo(px2,py2);
		float p2_[3]={p2[0]+PeremScale*dx/1000,p2[1]+PeremScale*dy/1000,p2[1]+PeremScale*dz/1000};
		AddCircle(p2_,PointSize);
		//cnv->Pen->Color=clGray;
		cnv->LineTo(x2,y2);
		//cnv->Pen->Color=oldc;
	}
	*/
	//cnv->SelectObject(pOldPen);
}

void CScreenPipePresenter::AddLineFrom(const float *p1, const float *p2, float Dist, float ang)
{
	int x1 = int(ToScrX(p1[0]) - Dist * ElemScale * sin(ang));
	int y1 = int(ToScrY(p1[1]) - Dist * ElemScale * cos(ang));
	int x2 = int(ToScrX(p2[0]) - Dist * ElemScale * sin(ang));
	int y2 = int(ToScrY(p2[1]) - Dist * ElemScale * cos(ang));
	cnv->DrawLine(x1, y1, x2, y2);
}

void CScreenPipePresenter::AddPodushFrom(const float *p1, const float *p2, float Dist, float ang)
{
	//cnv->Pen->Style=psDot;
	CPen pen(wxColor(static_cast<unsigned long>(COLORREF(clBlack))), 1, wxPENSTYLE_DOT);
	//CPen* oldPen = cnv->SelectObject(&pen);
	cnv->SetPen(pen);
	AddLineFrom(p1, p2, Dist, ang);
	AddLineFrom(p1, p2, Dist, ang + 4 * atan(1.0f));
	//cnv->Pen->Style=psSolid;
	//cnv->SelectObject(oldPen);
}

void CScreenPipePresenter::AddCircle(const float *p, float rad)
{
	int x = ToScrX(p[0]), y = ToScrY(p[1]);
	//int nBrush;
	//HGDIOBJ  hOldBrush= cnv->SelectObject(::GetStockObject(NULL_BRUSH));
	//cnv->SetBkMode(TRANSPARENT);
	//COLORREF colr1 = cnv->GetDCPenColor();
	if (fabs(rad - PointSize) < 0.0001)
	{
		//	cnv->Brush->Style=bsSolid;
		COLORREF colr1 = clBlack;// cnv->GetDCPenColor();
		CBrush br(colr1);
		cnv->SetBrush(br);
		cnv->DrawCircle(x,y,int(rad/2 * ElemScale + 0.5f));
		//cnv->SelectObject(oldBrush);
		//	cnv->Brush->Color=cnv->Pen->Color;
	}
	else
	{
		//cnv->Brush->Style=bsClear;
		TColor clr = getPipeColor(CurPipe.P_type > Max_pipe_type ? 0 : CurPipe.P_type);
		CPen pen(clr);
		cnv->SetBrush(wxNullBrush);
		//cnv->SelectObject(&pen);

		cnv->DrawCircle(x, y, int(rad/2 * ElemScale + 0.5f));
		//cnv->SelectObject(hOldBrush);
	}
	//cnv->Brush->Style=bsClear;
}


void CScreenPipePresenter::AddTextFrom(const float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode)
{
#ifdef __WXGTK__
	size = int(size*0.7);
#endif
	wxFont fnt(double(size*ElemScale)*72/cnv->GetPPI().x, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	if (TextMode & tCONDENSE)
	{
#ifdef __WXMSW__
		fnt.SetPixelSize(wxSize(LONG((ElemScale * size) / 3.5), size*ElemScale));
#endif
	}
	cnv->SetFont(fnt);

	if (m_ViewSettings.ShowDiam)
	{
		float pw = CurPipe.Diam / 1000 * m_ViewSettings.ScrScale;
		Dist += (pw / 2);
	}

	int x = int(ToScrX(p[0]) - Dist * ElemScale * sin(ang));
	int	y = int(ToScrY(p[1]) - Dist * ElemScale * cos(ang));
	CSize sz = cnv->GetTextExtent(txt);
	int tw = sz.GetX();
	int th = sz.GetY();
	int tx = int(tw * cos(-Rotation) - th * sin(-Rotation));
	int	ty = int(tw * sin(-Rotation) + th * cos(-Rotation));
#ifdef __WXMSW__
	cnv->DrawRotatedText(txt, x - tx / 2, y - ty / 2, Rotation *  45 / atan(1.0f));
#else
	wxGraphicsContext *pContext = cnv->GetGraphicsContext();
	pContext->PushState();
	if (TextMode & tCONDENSE)
	{
		pContext->Translate(x - tx / 4, y - ty / 2);
		pContext->Scale(0.5,1);
	}
	else
	{
		pContext->Translate(x - tx / 2, y - ty / 2);
	}
	cnv->DrawRotatedText(txt, 0, 0, Rotation *  45 / atan(1.0f));
	pContext->PopState();
#endif

	if (TextMode & tOVERLINE)
	{
		int tx1 = int(tw / 2 * cos(-Rotation) - (th / 2 - 2) * sin(-Rotation));
		int tx2 = int(-tw / 2 * cos(-Rotation) - (th / 2 - 2) * sin(-Rotation));
		int	ty1 = int(tw / 2 * sin(-Rotation) + (th / 2 - 2) * cos(-Rotation));
		int	ty2 = int(-tw / 2 * sin(-Rotation) + (th / 2 - 2) * cos(-Rotation));
		cnv->SetPen(*wxBLACK_PEN);
		cnv->DrawLine(x - tx1, y - ty1, x - tx2, y - ty2);
	}
}

void CScreenPipePresenter::Add2TextFrom(float* p, float Dist, float ang, int size,
                                        CString txt, CString txt1, float Rotation)
{
	AddTextFrom(p, Dist, ang, size, txt, Rotation, tNONE);
	AddTextFrom(p, Dist + (TextSmall), ang, size, txt1, Rotation, tOVERLINE);
}

float sqr(float x)
{
	return (x) * (x);
}

void CScreenPipePresenter::AddNodeNum(const float *p, float Dist, float ang, int NodeNum, float rad)
{
	//CPen* pOldPen;
	TColor clr;
	SPoint pt = m_Points[NodeNum];
	if (pt.set)
	{
		if (sqrt(sqr(p[0]-pt.x) +sqr(p[1]-pt.y) + sqr(p[2] - pt.z)) < 0.1)
			return;
		else
		{
			clr = clYellow;
			//cnv->Pen->Color=clYellow;
			Pipe pnt;
			pnt.EndP = NodeNum;
			pnt.dx = p[0] - pt.x;
			pnt.dy = p[1] - pt.y;
			pnt.dz = p[2] - pt.z;
			pnt.P_type = INVALID_LOOP;
			float p2[3] = {pt.x,pt.y,pt.z};
			AddLine(p, p2, NodeNum, pnt);
		}
	}
	else
	{
		clr = clRed;
		//cnv->Pen->Color=clRed;

		pt.x = p[0];
		pt.y = p[1];
		pt.z = p[2];
		pt.set = true;
		m_Points[NodeNum] = pt;
	}
	CPen pen(clr);
	cnv->SetPen(pen);
	//cnv->Brush->Style=bsClear
	cnv->SetBackgroundMode(wxTRANSPARENT);
	cnv->SetBrush(wxNullBrush);
	//cnv->SetBackgroundMode(TRANSPARENT);
	CString str =  CString::Format(_T("%d"), NodeNum);
	if (m_ViewSettings.ShowDiam)
	{
		float pw = CurPipe.Diam / 1000 * m_ViewSettings.ScrScale;
		Dist += (pw / 2);
	}
	int x = int(ToScrX(p[0]) - Dist * ElemScale * sin(ang)),
		y = int(ToScrY(p[1]) - Dist * ElemScale * cos(ang));
	cnv->DrawCircle(x, y, rad/2 * ElemScale);
	int x1 = int(x + rad / 2 * ElemScale * sin(ang));
	int y1 = int(y + rad / 2 * ElemScale * cos(ang));
	cnv->DrawLine(x1, y1, int(x1 + nTickSize * ElemScale * sin(ang)), int(y1 + nTickSize * ElemScale * cos(ang)));
	//cnv->SelectObject(pOldPen);
	AddTextFrom(p, Dist, ang, int(rad * 20 / 25), str, 0, tCONDENSE);
}

void CScreenPipePresenter::Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z)
{
	wxUnusedVar(x);
	wxUnusedVar(y);
	wxUnusedVar(z);
}

//inline int max(int x,int y)
//{
//	return (x>y)?x:y;
//}


void CScreenPipePresenter::AddVertLine(const float *strPoint, float dz)
{
	float Dist = 40;
	CString txt1 = LoadStr((dz > 0) ? IDS_PODJOM : IDS_OPUSK),
		txt2;
	txt2 = CString::Format(_T("h=%.1f"), dz);
	CSize sz = cnv->GetTextExtent(txt1);
	CSize sz1 = cnv->GetTextExtent(txt2);
	int w = std::max(sz.GetX(),sz1.GetX());
	int h = std::max(sz.GetY(),sz1.GetY());
	//int w1=w+w/4;
	//    h+=h/5;
	int x = ToScrX(strPoint[0]), y = ToScrY(strPoint[1]);
	//TColor oldClr=cnv->Pen->Color;
	//cnv->Pen->Color=clBlack;
	CPen pen(COLORREF(0));
	cnv->SetPen(pen);
	cnv->DrawLine(x, y, x+ int(Dist * ElemScale / 2), y-int(Dist * ElemScale));
	x += int(Dist * ElemScale / 2);
	y -= int(Dist * ElemScale);
	cnv->DrawLine(x, y, x+w, y);
	x += w;
	//cnv->DrawLine(x, y, x- w/2, y-h);
	x -= w / 2;
	y -= h;
	cnv->DrawText(txt1 ,x - sz.GetX() / 2, y);
	y += h + h / 5;
	cnv->DrawText(txt2, x - sz1.GetX() / 2, y);
	//cnv->SelectObject(pOldPen);
	//cnv->Pen->Color=oldClr;
}


const float AxisSize = 30;
const float NamePos = 1.25;
//const float NameHeight=20;
const POINT AxisPos = {40,-40};


void CScreenPipePresenter::Draw(CDC* pCanvas, CRotator* Rot, CRect ClientRect)
{
	cnv = pCanvas;
	m_ClientRect = ClientRect;
	m_rot = *Rot;
	cnv->SetPen(CPen(*wxBLACK));
	DrawMain(false);
	//static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1, strText);

	//	"Участков:"+IntToStr(m_NumPipes)+
	//	"  Узлов:"+IntToStr(m_NumNodes);
	DrawAxis(AxisSize, 0, 0, 'X');
	DrawAxis(0, AxisSize, 0, 'Y');
	DrawAxis(0, 0, AxisSize, 'Z');
}


float Dist(float x1, float y1, float x2, float y2)
{
	float dx = x2 - x1, dy = y2 - y1;
	float d = sqrt(dx * dx + dy * dy);
	return d;
}

// Расстояние до прямой
float DistToLine(float x, float y, // Исходная точка
                 float x1, float y1,// 1-я точка прямой
                 float x2, float y2)// 2-я точка прямой
{
	return ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / Dist(x1, y1, x2, y2);
}

// Расстояние до отрезка
float DistToInterval
(float x, float y, // Исходная точка
 float x1, float y1,// 1-я точка прямой
 float x2, float y2)// 2-я точка прямой
{
	float d1;
	if (Dist(x1, y1, x2, y2) < 0.0001) return Dist(x, y, x1, y1);
	d1 = -DistToLine(x, y, x1, y1, x1 - y2 + y1, y1 + x2 - x1);
	if (d1 < 0) return Dist(x, y, x1, y1);
	else if (d1 > Dist(x1, y1, x2, y2))
		return Dist(x, y, x2, y2);
	else return fabs(DistToLine(x, y, x1, y1, x2, y2));
}


void CScreenPipePresenter::IntSelectPipe(int X, int Y, std::set<int>* pNodeSet) const
{
	int SelectedInterval = -1;
	m_pvecSel->SelNAYZ = m_pvecSel->SelKOYZ = -1;
	float MinDist = 100;
	float MinDistUzl = MinDist;
	Interval_* pi;
	for (unsigned i = 0; i < m_pPipeArr->Intervals.size(); i++)
	{
		pi = &(m_pPipeArr->Intervals[i]);
		float d;
		if (!pNodeSet)
		{
			d = DistToInterval(float(X), float(Y), float(pi->x1), float(pi->y1), float(pi->x2), float(pi->y2));
			if ((d < pi->Diam || d < SelectAperture) && (d < MinDist))
			{
				MinDist = d;
				SelectedInterval = i;
			}
		}
		d = Dist(float(X), float(Y), float(pi->x1), float(pi->y1));
		if ((d < pi->Diam || d < SelectAperture) && d < MinDistUzl && (pNodeSet == nullptr || (pNodeSet->find(pi->StrP) != pNodeSet->end())))
		{
			MinDistUzl = d;
			m_pvecSel->SelNAYZ = m_pvecSel->SelKOYZ = pi->StrP;
			SelectedInterval = i;
		}
		d = Dist(float(X), float(Y), float(pi->x2), float(pi->y2));
		if ((d < pi->Diam || d < SelectAperture) && d < MinDistUzl && (pNodeSet == nullptr || (pNodeSet->find(pi->EndP) != pNodeSet->end())))
		{
			MinDistUzl = d;
			m_pvecSel->SelNAYZ = m_pvecSel->SelKOYZ = pi->EndP;
			SelectedInterval = i;
		}
	}
	if (SelectedInterval >= 0 && m_pvecSel->SelNAYZ == -1)
	{
		m_pvecSel->SelNAYZ = m_pPipeArr->Intervals[SelectedInterval].StrP;
		m_pvecSel->SelKOYZ = m_pPipeArr->Intervals[SelectedInterval].EndP;
		//if (NAYZ==KOYZ) {

		//	StatusBar1->Panels->Items[1]->Text =
		//		"Нестыковка dx="+FormatFloat("0.0##",Intervals[SelectedInterval].dx)+
		//		"   dy="+FormatFloat("0.0##",Intervals[SelectedInterval].dy)+
		//		"   dz="+FormatFloat("0.0##",Intervals[SelectedInterval].dz);

		//} else {
		//	StatusBar1->Panels->Items[1]->Text =
		//		"Выбран участок ["+IntToStr(NAYZ)+
		//		","+IntToStr(KOYZ)+"]";
		//	TLocateOptions Opts;
		//	Opts.Clear();
		//	Opts << loPartialKey;
		//	Variant locvalues[2];
		//	locvalues[0] = Variant(NAYZ);
		//	locvalues[1] = Variant(KOYZ);
		//	//       rst->Close();
		//	//       rst->Open();
		//	rst->Locate("NAYZ;KOYZ", VarArrayOf(locvalues, 1), Opts);
		//}
	}
}

void CScreenPipePresenter::SelectPipe(int X, int Y, bool bAdd) const
{
	IntSelectPipe(X, Y);
	if (!bAdd)
		m_pvecSel->clear();

	if (m_pvecSel->SelNAYZ != -1 && m_pvecSel->SelKOYZ != -1)
	{
		SelStr s(m_pvecSel->SelNAYZ, m_pvecSel->SelKOYZ);
		if (m_pvecSel->Contains(s.SelNAYZ, s.SelKOYZ))
		{
			m_pvecSel->erase(s);
			return;
		}
		m_pvecSel->insert(s);
	}
}

void CScreenPipePresenter::SelectPipesTo(int X, int Y, bool bAdd)
{
	SelStr s_from(m_pvecSel->SelNAYZ, m_pvecSel->SelKOYZ);
	IntSelectPipe(X, Y);
	if (m_pvecSel->SelNAYZ == -1 && m_pvecSel->SelKOYZ == -1)
	{
		m_pvecSel->SelNAYZ = s_from.SelNAYZ;
		m_pvecSel->SelKOYZ = s_from.SelKOYZ;
	}

	if (!bAdd)
		m_pvecSel->clear();

	m_pPipeArr->Init();

	std::vector<SelStr> vecPath;
	//SelStr s(m_pvecSel->SelNAYZ, m_pvecSel->SelKOYZ);
	if (!bAdd)
		m_pvecSel->insert(s_from);
	vecPath = SelectPipesTo_Out(s_from.SelNAYZ);
	if (vecPath.empty())
		vecPath = SelectPipesTo_In(s_from.SelNAYZ);
	for (auto& x : vecPath)
		m_pvecSel->insert(x);
}

std::vector<SelStr> CScreenPipePresenter::SelectPipesTo_In(int NAYZ)
{
	std::vector<SelStr> vecPath;
	CPipeArrayContext cnt;
	for (Pipe* p = &m_pPipeArr->InFirst(NAYZ, cnt); m_pPipeArr->InCount(NAYZ) == 1; (NAYZ = p->StrP) , p = &m_pPipeArr->InFirst(NAYZ, cnt))
	{
		if (p->Seen)
			continue;
		p->Seen = true;
		CPipeArrayContext cnt1;
		for (Pipe* p1 = &m_pPipeArr->OutFirst(p->EndP, cnt1); m_pPipeArr->HasOut(cnt1); p1 = &m_pPipeArr->OutNext(cnt1))
			if (!p1->Seen)
			{
				p1->Seen = true;
				auto vecPathRet = SelectPipesTo_Out(p1->EndP);
				if (!vecPathRet.empty())
				{
					vecPath.push_back(SelStr(p1->StrP, p1->EndP));
					for (auto x : vecPathRet)
						vecPath.push_back(x);
					return vecPath;
				}
			}
		vecPath.push_back(SelStr(p->StrP, p->EndP));
		if (p->StrP == m_pvecSel->SelNAYZ && p->EndP == m_pvecSel->SelKOYZ)
			return vecPath;
	}
	if (m_pPipeArr->InCount(NAYZ) > 1)
	{
		for (auto p = &m_pPipeArr->InFirst(NAYZ, cnt); m_pPipeArr->HasIn(cnt); p = &m_pPipeArr->InNext(cnt))
		{
			p->Seen = true;
			if (p->StrP == m_pvecSel->SelNAYZ && p->EndP == m_pvecSel->SelKOYZ)
			{
				vecPath.push_back(SelStr(p->StrP, p->EndP));
				return vecPath;
			}
			auto vecPathRet = SelectPipesTo_In(p->StrP);
			if (!vecPathRet.empty())
			{
				vecPath.push_back(SelStr(p->StrP, p->EndP));

				for (auto& x : vecPathRet)
					vecPath.push_back(x);
				return vecPath;
			}
		}
	}
	vecPath.clear();
	return vecPath;
}

std::vector<SelStr> CScreenPipePresenter::SelectPipesTo_Out(int NAYZ)
{
	std::vector<SelStr> vecPath;
	CPipeArrayContext cnt;
	for (auto p = &m_pPipeArr->OutFirst(NAYZ, cnt); m_pPipeArr->OutCount(NAYZ) == 1; (NAYZ = p->EndP) , p = &m_pPipeArr->OutFirst(NAYZ, cnt))
	{
		if (p->Seen)
			continue;
		p->Seen = true;
		CPipeArrayContext cnt1;
		for (Pipe* p1 = &m_pPipeArr->InFirst(p->StrP, cnt1); m_pPipeArr->HasIn(cnt1); p1 = &m_pPipeArr->InNext(cnt1))
			if (!p1->Seen)
			{
				p1->Seen = true;
				auto vecPathRet = SelectPipesTo_In(p1->StrP);
				if (!vecPathRet.empty())
				{
					vecPath.push_back(SelStr(p1->StrP, p1->EndP));
					for (auto& x : vecPathRet)
						vecPath.push_back(x);
					return vecPath;
				}
			}
		vecPath.push_back(SelStr(p->StrP, p->EndP));
		if (p->StrP == m_pvecSel->SelNAYZ && p->EndP == m_pvecSel->SelKOYZ)
			return vecPath;
	}
	if (m_pPipeArr->OutCount(NAYZ) > 1)
	{
		for (auto p = &m_pPipeArr->OutFirst(NAYZ, cnt); m_pPipeArr->HasOut(cnt); p = &m_pPipeArr->OutNext(cnt))
		{
			p->Seen = true;
			if (p->StrP == m_pvecSel->SelNAYZ && p->EndP == m_pvecSel->SelKOYZ)
			{
				vecPath.push_back(SelStr(p->StrP, p->EndP));
				return vecPath;
			}
			auto vecPathRet = SelectPipesTo_Out(p->EndP);
			if (!vecPathRet.empty())
			{
				vecPath.push_back(SelStr(p->StrP, p->EndP));
				for (auto& x : vecPathRet)
					vecPath.push_back(x);
				return vecPath;
			}
			vecPathRet = SelectPipesTo_Out(p->EndP);
		}
	}
	vecPath.clear();
	return vecPath;
}


void CScreenPipePresenter::SelectPipeSegment(int X, int Y)
{
	IntSelectPipe(X, Y);
	m_pvecSel->clear();
	Pipe* p;
	m_pPipeArr->Init();
	if (!m_pPipeArr->HasOut(m_pvecSel->SelNAYZ) && !m_pPipeArr->HasIn(m_pvecSel->SelNAYZ))
		return;
	CPipeArrayContext cnt;
	SelStr s(m_pvecSel->SelNAYZ, m_pvecSel->SelKOYZ);
	// ReSharper disable once CppPossiblyErroneousEmptyStatements
	for (p = &m_pPipeArr->OutFirst(s.SelNAYZ, cnt); p->EndP != s.SelKOYZ && m_pPipeArr->HasOut(cnt); p = &m_pPipeArr->OutNext(cnt));
	p->Seen = true;
	m_pvecSel->insert(s);
	SelectPS_Out(s.SelKOYZ, p->P_type);
	SelectPS_In(s.SelNAYZ, p->P_type);
};

void CScreenPipePresenter::SelectPS_In(int NAYZ, int type)
{
	if (!m_pPipeArr->HasIn(NAYZ))
		return;
	CPipeArrayContext cnt;
	for (Pipe* p = &m_pPipeArr->InFirst(NAYZ, cnt); m_pPipeArr->HasIn(cnt); p = &m_pPipeArr->InNext(cnt))
	{
		if (p->P_type == type && !p->Seen && p->StrP > 0)
		{
			p->Seen = true;
			m_pvecSel->insert(SelStr(p->StrP, p->EndP));
			SelectPS_In(p->StrP, type);
			SelectPS_Out(p->EndP, type);
		}
	}
};


void CScreenPipePresenter::SelectPS_Out(int KOYZ, int type)
{
	if (!m_pPipeArr->HasOut(KOYZ))
		return;
	CPipeArrayContext cnt;
	for (Pipe* p = &m_pPipeArr->OutFirst(KOYZ, cnt); m_pPipeArr->HasOut(cnt); p = &m_pPipeArr->OutNext(cnt))
	{
		if (p->P_type == type && !p->Seen && p->StrP > 0)
		{
			p->Seen = true;
			m_pvecSel->insert(SelStr(p->StrP, p->EndP));
			SelectPS_In(p->StrP, type);
			SelectPS_Out(p->EndP, type);
		}
	}
}


void CScreenPipePresenter::ZoomAll(const CRect clr, int Border)
{
	int clw = clr.GetWidth() - Border;
	int clh = clr.GetHeight() - Border;
	DrawMain(true);
	float WinX = (x_max - x_min);
	float WinY = (y_max - y_min);
	float xc = (x_max + x_min) / 2, yc = (y_max + y_min) / 2;
	if (WinX == 0) WinX = 1;
	if (WinY == 0) WinY = 1;
	float SclX = clw / WinX;
	float SclY = clh / WinY;
	float SclF = (SclX < SclY) ? SclX : SclY;
	m_ViewSettings.ScrScale = SclF;
	m_ViewSettings.Xorg = (clr.GetLeftTop().x + clr.GetBottomRight().x) / 2 - xc * m_ViewSettings.ScrScale;
	m_ViewSettings.Yorg = (clr.GetLeftTop().y + clr.GetBottomRight().y) / 2 + yc * m_ViewSettings.ScrScale;
};


void CScreenPipePresenter::DrawAxis(float x, float y, float z, char Name) const
{
	m_rot.Rotate(x, y, z);
	//cnv->Pen->Color=clBlack;
	cnv->SetPen(*wxBLACK_PEN);
	cnv->DrawLine(int(m_ClientRect.GetLeftTop().x + AxisPos.x * ElemScale),
	    int(m_ClientRect.GetBottomRight().y + AxisPos.y * ElemScale),
		int(m_ClientRect.GetLeftTop().x + (AxisPos.x + x) * ElemScale),
	    int(m_ClientRect.GetBottomRight().y + (AxisPos.y - y) * ElemScale));
	CString strName(Name);
	CSize sz = cnv->GetTextExtent(strName);
	int tw = sz.GetX();
	int th = sz.GetY();
	//cnv->Font->Color=clBlack;
	//cnv->Brush->Style=bsClear;
	//   PaintBox1->Canvas->Brush->Color=clWhite;
	cnv->DrawText(strName, int(m_ClientRect.GetLeftTop().x + (AxisPos.x + x * NamePos) * ElemScale - tw / 2),
	             int(m_ClientRect.GetBottomRight().y + (AxisPos.y - y * NamePos) * ElemScale - th / 2));
}


CScreenPipePresenter::CScreenPipePresenter(CPipeArray* PipeArray, CRotator& _rot, CViewSettings& _viewSettings) : CPipePresenter(PipeArray, _rot, _viewSettings), cnv(nullptr)
{
	ElemScale = 1;
	FontName = "Times New Roman";
}


CScreenPipePresenter::~CScreenPipePresenter()
{
	//
}

void CScreenPipePresenter::SetClientRect(const CRect& clr)
{
	m_ClientRect = clr;
}


void TResult::copy()
{
	//TTable *res=new TTable(nullptr);
	//res->DatabaseName=MainForm1->Table1->DatabaseName;
	//res->TableName=GetPartialName(MainForm1->Table1->TableName)+"pr.dbf";
	//TPoint3D p={0,0,0};
	//for (int i=0;i<MaxPipes;i++) Perem[i]=p;
	//if (res->Exists) {
	//	res->Open();
	//	res->First();
	//	while (!res->Eof) {
	//		int n=res->FieldValues["YZL"];
	//		Perem[n].dx=res->FieldValues["LIX"];
	//		Perem[n].dy=res->FieldValues["LIY"];
	//		Perem[n].dz=res->FieldValues["LIZ"];
	//		res->Next();
	//	}
	//	res->Close();
	//}
	//delete res;
}


//void  CScreenPipePresenter::SaveViewState()
//{
//	oScrScale=m_ViewSettings.ScrScale;
//	oXorg=m_ViewSettings.Xorg; oYorg=m_ViewSettings.Yorg;
//}
//
//void  CScreenPipePresenter::RestoreViewState()
//{
//	m_ViewSettings.ScrScale=oScrScale;
//	m_ViewSettings.Xorg=oXorg; m_ViewSettings.Yorg=oYorg;
//}


