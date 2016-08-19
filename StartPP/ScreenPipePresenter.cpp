#include "stdafx.h"
#include "ScreenPipePresenter.h"
//#include "MainFrm.h"
#include "Colors.h"
#include "Rotate.h"
//#include "resource.h"
#include "Strings.h"
#include "wx/graphics.h"

//extern LPCTSTR LoadStr(UINT nID);

float Sgn(float x)
{
	if (x > 0) return 1;
	else if (x == 0) return 0;
	else return -1;
}

float CalcAng(float dx, float dy)
{
	float ang;
	if (fabs(dx) + fabs(dy) < 0.001)
		ang = 2 * atan(1.0f);
	else if (fabs(dx) < 0.001) ang = 2 * atan(1.0f) * Sgn(dy);
	else
	{
		ang = atan(dy / dx);
		if (dx < 0)
			ang = dy < 0 ? ang - 4 * atan(1.0f) : ang + 4 * atan(1.0f);
	}
	return ang;
}

extern float RadToDeg(float x);

float CalcAngProf(float x, float y, float z)
{
	float l_plan = sqrt(x * x + y * y);
	if (fabs(x) + fabs(y) < 0.001)
	{
		if (z > 0) return 90;
		else return -90;
	}
	else
	{
		return RadToDeg(atan(z / l_plan));
	}
}

float NormAng(float ang)
{
	float ang2;
	ang2 = ang;
	if (ang2 > 2 * atan(1.0f)) ang2 = ang2 - 4 * atan(1.0f);
	if (ang2 < -2 * atan(1.0f)) ang2 = ang2 + 4 * atan(1.0f);
	if (fabs(ang2 + 2 * atan(1.0f)) < 0.0001) ang2 = 2 * atan(1.0f);
	return ang2;
};


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

void CScreenPipePresenter::DrawList(float* p, const POINT* list, float ang)
{
	int x = ToScrX(p[0]), y = ToScrY(p[1]);
	float s = sin(ang) * elSize * ElemScale, c = cos(ang) * elSize * ElemScale;
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

void CScreenPipePresenter::AddNodeElement(float* p, TNodeElement el, float ang)
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

void CScreenPipePresenter::AddLine(float* p1, float* p2, int NAYZ, Pipe& p)
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
	//for (unsigned i = 0; i<pvecSel->size(); i++)
	if (pvecSel->Contains(NAYZ, p.EndP))
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
	if (p.P_type == INVALID_LOOP)
		rot.Rotate_1(p.dx, p.dy, p.dz);
	pi.dx = p.dx;
	pi.dy = p.dy;
	pi.dz = p.dz;
	pi.Diam = SelectAperture;
	PipeArr->Intervals.push_back(pi);
	/*
	if (ShowPerem) {
		//TColor oldc=cnv->Pen->Color;
		//cnv->Pen->Color=clBlack;
		float dx=Result->Perem[NAYZ].dx,
			dy=Result->Perem[NAYZ].dy,
			dz=Result->Perem[NAYZ].dz;
		int   px1,py1,px2,py2;
		rot.Rotate(dx, dy, dz);

		px1=ToScrX(p1[0]+PeremScale*dx/1000);
		py1=ToScrY(p1[1]+PeremScale*dy/1000);

		dx=Result->Perem[p.EndP].dx;
		dy=Result->Perem[p.EndP].dy;
		dz=Result->Perem[p.EndP].dz;
		rot.Rotate(dx, dy, dz);
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

void CScreenPipePresenter::AddLineFrom(float* p1, float* p2, float Dist, float ang)
{
	int x1 = int(ToScrX(p1[0]) - Dist * ElemScale * sin(ang));
	int y1 = int(ToScrY(p1[1]) - Dist * ElemScale * cos(ang));
	int x2 = int(ToScrX(p2[0]) - Dist * ElemScale * sin(ang));
	int y2 = int(ToScrY(p2[1]) - Dist * ElemScale * cos(ang));
	cnv->DrawLine(x1, y1, x2, y2);
}

void CScreenPipePresenter::AddPodushFrom(float* p1, float* p2, float Dist, float ang)
{
	//cnv->Pen->Style=psDot;
	CPen pen(wxColor((unsigned long)COLORREF(clBlack)), 1, wxPENSTYLE_DOT);
	//CPen* oldPen = cnv->SelectObject(&pen);
	cnv->SetPen(pen);
	AddLineFrom(p1, p2, Dist, ang);
	AddLineFrom(p1, p2, Dist, ang + 4 * atan(1.0f));
	//cnv->Pen->Style=psSolid;
	//cnv->SelectObject(oldPen);
}

void CScreenPipePresenter::AddCircle(float* p, float rad)
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


void CScreenPipePresenter::AddTextFrom(float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode)
{
	//HFONT hfnt;
	//HGDIOBJ hfntPrev;
	//HDC hdc = *cnv;
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
	//LOGFONT lf;
	//ZeroMemory(&lf, sizeof(LOGFONT));
	///* Allocate memory for a LOGFONT structure. */
	//PLOGFONT plf = &lf;//(PLOGFONT) LocalAlloc(LPTR, sizeof(LOGFONT));

	//if (!plf)
	//	return;
	///* Specify a font typeface name and weight. */
	//lstrcpy(plf->lfFaceName, FontName);
	//plf->lfWeight = FW_NORMAL;
	//if (TextMode & tCONDENSE)
	//{
	//	plf->lfWidth = LONG((ElemScale * size) / 3.5);
	//	plf->lfWeight = FW_MEDIUM;
	//}

	//if (TextMode & tUNDERLINE) plf->lfUnderline = TRUE;
	//plf->lfQuality = PROOF_QUALITY;

	///*
	//* Set the background mode to transparent for the
	//* text-output operation.
	//*/

	////SetBkMode(hdc, TRANSPARENT);

	//plf->lfEscapement = LONG(Rotation * 10 * 45 / atan(1.0f));
	//plf->lfHeight = LONG(-size * ElemScale);
	//hfnt = CreateFontIndirect(plf);
	//hfntPrev = ::SelectObject(hdc, hfnt);
	int x = int(ToScrX(p[0]) - Dist * ElemScale * sin(ang)),
		y = int(ToScrY(p[1]) - Dist * ElemScale * cos(ang));
	CSize sz = cnv->GetTextExtent(txt);
	int tw = sz.GetX(), th = sz.GetY();
	int tx = int(tw * cos(-Rotation) - th * sin(-Rotation)),
		ty = int(tw * sin(-Rotation) + th * cos(-Rotation));
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
	//SelectObject(hdc, hfntPrev);
	//DeleteObject(hfnt);
	if (TextMode & tOVERLINE)
	{
		int tx1 = int(tw / 2 * cos(-Rotation) - (th / 2 - 2) * sin(-Rotation)), tx2 = int(-tw / 2 * cos(-Rotation) - (th / 2 - 2) * sin(-Rotation)),
			ty1 = int(tw / 2 * sin(-Rotation) + (th / 2 - 2) * cos(-Rotation)), ty2 = int(-tw / 2 * sin(-Rotation) + (th / 2 - 2) * cos(-Rotation));
		CPen pen(wxColor((COLORREF)clBlack));
		cnv->SetPen(pen);
		//CPen* oldPen = cnv->SelectObject(&pen);
		cnv->DrawLine(x - tx1, y - ty1, x - tx2, y - ty2);
		//cnv->SelectObject(oldPen);
	}

	//    SetBkMode(hdc, OPAQUE);// Reset the background mode to its default.
	//LocalFree((LOCALHANDLE) plf);// Free the memory allocated for the LOGFONT structure.
}

void CScreenPipePresenter::Add2TextFrom(float* p, float Dist, float ang, int size,
                                        CString txt, CString txt1, float Rotation)
{
	AddTextFrom(p, Scl, ang, size, txt, Rotation, tNONE);
	AddTextFrom(p, Scl + (TextSmall), ang, size, txt1, Rotation, tOVERLINE);
}

float sqr(float x)
{
	return (x) * (x);
}

void CScreenPipePresenter::AddNodeNum(float* p, float Dist, float ang, int NodeNum, float rad)
{
	//CPen* pOldPen;
	TColor clr;
	SPoint pt = Points[NodeNum];
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
		Points[NodeNum] = pt;
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
	int x1 = int(x + rad / 2 * ElemScale * sin(ang)), y1 = int(y + rad / 2 * ElemScale * cos(ang));
	cnv->DrawLine(x1, y1, int(x1 + nTickSize * ElemScale * sin(ang)), int(y1 + nTickSize * ElemScale * cos(ang)));
	//cnv->SelectObject(pOldPen);
	AddTextFrom(p, Dist, ang, int(rad * 20 / 25), str, 0, tCONDENSE);
}

void CScreenPipePresenter::Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z)
{
}

//inline int max(int x,int y)
//{
//	return (x>y)?x:y;
//}


void CScreenPipePresenter::AddVertLine(float* strPoint, float dz)
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


void SetCompOsLen(Pipe* p)
{
	p->R_Otv = p->Diam * 2 / 1000;
}

void SetCompUgLen(Pipe* p)
{
	p->R_Otv = p->Diam * 2 / 1000;
}


const float AxisSize = 30;
const float NamePos = 1.25;
//const float NameHeight=20;
const POINT AxisPos = {40,-40};


void CScreenPipePresenter::Draw(CDC* pCanvas, CRotator* Rot, CRect ClientRect)
{
	cnv = pCanvas;
	m_ClientRect = ClientRect;
	rot = *Rot;
	cnv->SetPen(CPen(*wxBLACK));
	DrawMain(false);
	CString strText = CString::Format(LoadStr(IDS_FORMAT_UCH_UZL), NumPipes, NumNodes);
	//static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1, strText);

	//	"Участков:"+IntToStr(NumPipes)+
	//	"  Узлов:"+IntToStr(NumNodes);
	DrawAxis(AxisSize, 0, 0, 'X', Rot);
	DrawAxis(0, AxisSize, 0, 'Y', Rot);
	DrawAxis(0, 0, AxisSize, 'Z', Rot);
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


void CScreenPipePresenter::IntSelectPipe(int X, int Y, std::set<int>* pNodeSet)
{
	int SelectedInterval = -1;
	pvecSel->SelNAYZ = pvecSel->SelKOYZ = -1;
	float MinDist = 100;
	float MinDistUzl = MinDist;
	Interval_* pi;
	for (unsigned i = 0; i < PipeArr->Intervals.size(); i++)
	{
		pi = &(PipeArr->Intervals[i]);
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
			pvecSel->SelNAYZ = pvecSel->SelKOYZ = pi->StrP;
			SelectedInterval = i;
		}
		d = Dist(float(X), float(Y), float(pi->x2), float(pi->y2));
		if ((d < pi->Diam || d < SelectAperture) && d < MinDistUzl && (pNodeSet == nullptr || (pNodeSet->find(pi->EndP) != pNodeSet->end())))
		{
			MinDistUzl = d;
			pvecSel->SelNAYZ = pvecSel->SelKOYZ = pi->EndP;
			SelectedInterval = i;
		}
	}
	if (SelectedInterval >= 0 && pvecSel->SelNAYZ == -1)
	{
		int NAYZ = PipeArr->Intervals[SelectedInterval].StrP;
		int KOYZ = PipeArr->Intervals[SelectedInterval].EndP;
		pvecSel->SelNAYZ = NAYZ;
		pvecSel->SelKOYZ = KOYZ;
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

void CScreenPipePresenter::SelectPipe(int X, int Y, bool bAdd)
{
	IntSelectPipe(X, Y);
	if (!bAdd)
		pvecSel->clear();

	if (pvecSel->SelNAYZ != -1 && pvecSel->SelKOYZ != -1)
	{
		SelStr s(pvecSel->SelNAYZ, pvecSel->SelKOYZ);
		if (pvecSel->Contains(s.SelNAYZ, s.SelKOYZ))
		{
			pvecSel->erase(s);
			return;
		}
		pvecSel->insert(s);
	}
}

void CScreenPipePresenter::SelectPipesTo(int X, int Y, bool bAdd)
{
	SelStr s_from(pvecSel->SelNAYZ, pvecSel->SelKOYZ);
	IntSelectPipe(X, Y);
	if (pvecSel->SelNAYZ == -1 && pvecSel->SelKOYZ == -1)
	{
		pvecSel->SelNAYZ = s_from.SelNAYZ;
		pvecSel->SelKOYZ = s_from.SelKOYZ;
	}

	if (!bAdd)
		pvecSel->clear();

	PipeArr->Init();

	std::vector<SelStr> vecPath;
	//SelStr s(pvecSel->SelNAYZ, pvecSel->SelKOYZ);
	if (!bAdd)
		pvecSel->insert(s_from);
	vecPath = SelectPipesTo_Out(s_from.SelNAYZ);
	if (vecPath.empty())
		vecPath = SelectPipesTo_In(s_from.SelNAYZ);
	for (auto& x : vecPath)
		pvecSel->insert(x);
}

std::vector<SelStr> CScreenPipePresenter::SelectPipesTo_In(int NAYZ)
{
	std::vector<SelStr> vecPath;
	Pipe* p = nullptr;
	CPipeArrayContext cnt;
	for (p = &PipeArr->InFirst(NAYZ, cnt); PipeArr->InCount(NAYZ) == 1; (NAYZ = p->StrP) , p = &PipeArr->InFirst(NAYZ, cnt))
	{
		if (p->Seen)
			continue;
		p->Seen = true;
		CPipeArrayContext cnt1;
		for (Pipe* p1 = &PipeArr->OutFirst(p->EndP, cnt1); PipeArr->HasOut(cnt1); p1 = &PipeArr->OutNext(cnt1))
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
		if (p->StrP == pvecSel->SelNAYZ && p->EndP == pvecSel->SelKOYZ)
			return vecPath;
	}
	if (PipeArr->InCount(NAYZ) > 1)
	{
		for (p = &PipeArr->InFirst(NAYZ, cnt); PipeArr->HasIn(cnt); p = &PipeArr->InNext(cnt))
		{
			p->Seen = true;
			if (p->StrP == pvecSel->SelNAYZ && p->EndP == pvecSel->SelKOYZ)
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
	Pipe* p = nullptr;
	CPipeArrayContext cnt;
	for (p = &PipeArr->OutFirst(NAYZ, cnt); PipeArr->OutCount(NAYZ) == 1; (NAYZ = p->EndP) , p = &PipeArr->OutFirst(NAYZ, cnt))
	{
		if (p->Seen)
			continue;
		p->Seen = true;
		CPipeArrayContext cnt1;
		for (Pipe* p1 = &PipeArr->InFirst(p->StrP, cnt1); PipeArr->HasIn(cnt1); p1 = &PipeArr->InNext(cnt1))
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
		if (p->StrP == pvecSel->SelNAYZ && p->EndP == pvecSel->SelKOYZ)
			return vecPath;
	}
	if (PipeArr->OutCount(NAYZ) > 1)
	{
		for (p = &PipeArr->OutFirst(NAYZ, cnt); PipeArr->HasOut(cnt); p = &PipeArr->OutNext(cnt))
		{
			p->Seen = true;
			if (p->StrP == pvecSel->SelNAYZ && p->EndP == pvecSel->SelKOYZ)
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
	pvecSel->clear();
	Pipe* p = nullptr;
	PipeArr->Init();
	if (!PipeArr->HasOut(pvecSel->SelNAYZ) && !PipeArr->HasIn(pvecSel->SelNAYZ))
		return;
	CPipeArrayContext cnt;
	SelStr s(pvecSel->SelNAYZ, pvecSel->SelKOYZ);
	// ReSharper disable once CppPossiblyErroneousEmptyStatements
	for (p = &PipeArr->OutFirst(s.SelNAYZ, cnt); p->EndP != s.SelKOYZ && PipeArr->HasOut(cnt); p = &PipeArr->OutNext(cnt));
	p->Seen = true;
	pvecSel->insert(s);
	SelectPS_Out(s.SelKOYZ, p->P_type);
	SelectPS_In(s.SelNAYZ, p->P_type);
};

void CScreenPipePresenter::SelectPS_In(int NAYZ, int type)
{
	if (!PipeArr->HasIn(NAYZ))
		return;
	CPipeArrayContext cnt;
	for (Pipe* p = &PipeArr->InFirst(NAYZ, cnt); PipeArr->HasIn(cnt); p = &PipeArr->InNext(cnt))
	{
		if (p->P_type == type && !p->Seen && p->StrP > 0)
		{
			p->Seen = true;
			pvecSel->insert(SelStr(p->StrP, p->EndP));
			SelectPS_In(p->StrP, type);
			SelectPS_Out(p->EndP, type);
		}
	}
};


void CScreenPipePresenter::SelectPS_Out(int KOYZ, int type)
{
	if (!PipeArr->HasOut(KOYZ))
		return;
	CPipeArrayContext cnt;
	for (Pipe* p = &PipeArr->OutFirst(KOYZ, cnt); PipeArr->HasOut(cnt); p = &PipeArr->OutNext(cnt))
	{
		if (p->P_type == type && !p->Seen && p->StrP > 0)
		{
			p->Seen = true;
			pvecSel->insert(SelStr(p->StrP, p->EndP));
			SelectPS_In(p->StrP, type);
			SelectPS_Out(p->EndP, type);
		}
	}
}


void CScreenPipePresenter::ZoomAll(const CRect clr, int Border)
{
	int clw = clr.GetWidth() - Border, clh = clr.GetHeight() - Border;
	DrawMain(true);
	float WinX = (x_max - x_min), WinY = (y_max - y_min);
	float xc = (x_max + x_min) / 2, yc = (y_max + y_min) / 2;
	if (WinX == 0) WinX = 1;
	if (WinY == 0) WinY = 1;
	float SclX = clw / float(WinX), SclY = clh / float(WinY);
	float SclF = (SclX < SclY) ? SclX : SclY;
	m_ViewSettings.ScrScale = SclF;
	m_ViewSettings.Xorg = (clr.GetLeftTop().x + clr.GetBottomRight().x) / 2 - xc * m_ViewSettings.ScrScale;
	m_ViewSettings.Yorg = (clr.GetLeftTop().y + clr.GetBottomRight().y) / 2 + yc * m_ViewSettings.ScrScale;
};


void CScreenPipePresenter::DrawAxis(float x, float y, float z, char Name, CRotator* Rot)
{
	rot.Rotate(x, y, z);
	//cnv->Pen->Color=clBlack;
	wxPen pen(wxColor((COLORREF)clBlack));
	cnv->SetPen(pen);
	cnv->DrawLine(int(m_ClientRect.GetLeftTop().x + AxisPos.x * ElemScale),
	    int(m_ClientRect.GetBottomRight().y + AxisPos.y * ElemScale),
		int(m_ClientRect.GetLeftTop().x + (AxisPos.x + x) * ElemScale),
	    int(m_ClientRect.GetBottomRight().y + (AxisPos.y - y) * ElemScale));
	CString strName(Name);
	CSize sz = cnv->GetTextExtent(strName);
	int tw = sz.GetX(), th = sz.GetY();
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


