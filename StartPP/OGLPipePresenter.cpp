//---------------------------------------------------------------------------
#include "stdafx.h"
#include <math.h>
#include "OGLPipePresenter.h"
#include "Colors.h"
#include "Rotate.h"
#include "GLFontRenderer.h"
//#include "MainFrm.h"
#ifdef __WXMAC__
#include "glu.h"
#else
#include "GL/glu.h"
#endif
//#include "resource.h"
#include "Strings.h"
#include "main.h"
#include "DibGlSurface.h"
#include <cmath>
extern float Round(float x, int N);

//---------------------------------------------------------------------------
//#pragma package(smart_init)

#define OGL_INIT_ONCE


inline float sgn(float x)
{
	return (x > 0) ? 1.0f : -1.0f;
}

void errorCallback(GLenum errorCode)
{
	AfxMessageBox(CString(gluErrorString(errorCode)),wxOK | wxICON_EXCLAMATION);
}

//static GLuint texture1;

void COGLPipePresenter::DrawTexts()
{
	for (const auto& s : m_vecTexts)
	{
		AddTextFrom2(s.p, s.Dist, s.ang, s.size, s.txt, s.Rotation, s.TextMode, s.pw);
	}
	m_vecTexts.clear();
}

void COGLPipePresenter::SetupLighting() const
{
	GLfloat MaterialAmbient[] = {
		0.1f, 0.1f, 0.1f, 1.0f
	};
	GLfloat MaterialDiffuse[] = {
		0.1f, 1.0f, 1.0f, 1.0f
	};
	GLfloat MaterialSpecular[] = {
		0.8f, 0.8f, 0.8f, 1.0f
	};
	GLfloat MaterialShininess[] = {
		30.0f
	};
	GLfloat AmbientLightPosition[] = {
		0.2f, .2f, 1.0f, 0.0f
	};
	GLfloat LightAmbient[] = {
		0.2f, 0.2f, 0.2f, 1.0f
	};
	glMaterialfv(GL_FRONT, GL_AMBIENT, MaterialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MaterialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, MaterialShininess);
	glLightfv(GL_LIGHT0, GL_POSITION, AmbientLightPosition);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);
	//    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
	if (m_ViewSettings.ShowNapr)
	{
		//#define TEX_WIDTH 256
		//Graphics::TBitmap *bitmap = new Graphics::TBitmap; 
		//bitmap->LoadFromFile(MainForm1->Table2->DatabaseName + "\\Napr.bmp" );
		//GLubyte TexImage[4 *TEX_WIDTH]; 
		//for(int i = 0; i < TEX_WIDTH; i++ ) {
		//   TexImage[4 *i] = (GLbyte)GetRValue(bitmap->Canvas->Pixels[i][0]);
		//   TexImage[4 *i + 1] = (GLbyte)GetGValue(bitmap->Canvas->Pixels[i][0]);
		//   TexImage[4 *i + 2] = (GLbyte)GetBValue(bitmap->Canvas->Pixels[i][0]);
		//   TexImage[4 *i + 3] = (GLbyte)255; 
		//};
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glGenTextures(1, &texture1);
		//glBindTexture(GL_TEXTURE_1D, texture1);
		//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, TEX_WIDTH, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
		//TexImage);
		//delete bitmap; 
		//glEnable(GL_TEXTURE_1D);
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}

void box(float dx, float dy, float dz)
{
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(- dx / 2, - dy / 2, dz / 2);
	glVertex3f(dx / 2, - dy / 2, dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glVertex3f(- dx / 2, dy / 2, dz / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(- dx / 2, - dy / 2, - dz / 2);
	glVertex3f(dx / 2, - dy / 2, - dz / 2);
	glVertex3f(dx / 2, dy / 2, - dz / 2);
	glVertex3f(- dx / 2, dy / 2, - dz / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(- dx / 2, - dy / 2, - dz / 2);
	glVertex3f(- dx / 2, dy / 2, - dz / 2);
	glVertex3f(- dx / 2, dy / 2, dz / 2);
	glVertex3f(- dx / 2, - dy / 2, dz / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(dx / 2, - dy / 2, - dz / 2);
	glVertex3f(dx / 2, dy / 2, - dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glVertex3f(dx / 2, - dy / 2, dz / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(- dx / 2, - dy / 2, - dz / 2);
	glVertex3f(dx / 2, - dy / 2, - dz / 2);
	glVertex3f(dx / 2, - dy / 2, dz / 2);
	glVertex3f(- dx / 2, - dy / 2, dz / 2);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(- dx / 2, dy / 2, - dz / 2);
	glVertex3f(dx / 2, dy / 2, - dz / 2);
	glVertex3f(dx / 2, dy / 2, dz / 2);
	glVertex3f(- dx / 2, dy / 2, dz / 2);
	glEnd();
}

float sin_arr[13], cos_arr[13];

void SetColor(TColor c, bool Selected);

//const float M_PI = 3.1415926f;

void COGLPipePresenter::draw_styk(float l_gen, float rad, float str_x_rot, float
                                  str_tg_2, float end_tg_2, float t1, float t2, bool DrawEnd) const
{
	if (m_ViewSettings.ShowNapr)
		glColor3f(1, 1, 1);
	for (int i = 0; i < 12; i++)
	{
		sin_arr[i] = sinf(2 * float(M_PI) * i / 12);
		cos_arr[i] = cosf(2 * float(M_PI) * i / 12);
	}
	sin_arr[12] = sin_arr[0];
	cos_arr[12] = cos_arr[0];
	CRotator Rot(0, 0, str_x_rot);
	for (int i = 0; i < 12; i++)
	{
		float ang = 2 * float(M_PI) * i / 12;
		float ang1 = 2 * float(M_PI) * (i + 1) / 12;
		glBegin(GL_QUADS); //      LINE_LOOP);
		glNormal3f(0, sin_arr[i], cos_arr[i]);
		float x = rad * sinf(ang + str_x_rot) * str_tg_2;
		float y = rad * sinf(ang + str_x_rot);
		float z = rad * cosf(ang + str_x_rot);
		Rot.x_rotate(x, y, z);
		glTexCoord1f(1 - t1);
		glVertex3f(x, y, z);
		glTexCoord1f(1 - t2);
		glVertex3f(l_gen + rad * sin_arr[i] * end_tg_2, rad * sin_arr[i], rad * cos_arr[i]);
		glNormal3f(0, sin_arr[i + 1], cos_arr[i + 1]);
		glVertex3f(l_gen + rad * sin_arr[i + 1] * end_tg_2, rad * sin_arr[i + 1], rad * cos_arr[i + 1]);
		x = rad * sinf(ang1 + str_x_rot) * str_tg_2;
		y = rad * sinf(ang1 + str_x_rot);
		z =	rad * cosf(ang1 + str_x_rot);
		Rot.x_rotate(x, y, z);
		glTexCoord1f(1 - t1);
		glVertex3f(x, y, z);
		glEnd();
	}
	if (!DrawEnd) return;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 12; i++)
	{
		float ang = 2 * float(M_PI) * i / 12;
		//float ang1 = 2 *M_PI *(i + 1) / 12;
		glNormal3f(0, sin_arr[i], cos_arr[i]);
		float x = rad * sinf(ang + str_x_rot) * str_tg_2;
		float y = rad * sinf(ang + str_x_rot);
		float z = rad * cosf(ang + str_x_rot);
		Rot.x_rotate(x, y, z);
		glTexCoord1f(1 - t2);
		glVertex3f(l_gen + rad * sin_arr[i] * end_tg_2, rad * sin_arr[i], rad * cos_arr[i]);
		glNormal3f(0, sin_arr[i + 1], cos_arr[i + 1]);
		glVertex3f(l_gen + rad * sin_arr[i + 1] * end_tg_2, rad * sin_arr[i + 1], rad * cos_arr[i + 1]);
	}
	glEnd();
}

enum TPipeEnds
{
	PE_NONE,
	PE_OTVOD,
	PE_STYK,
	PE_ARMAT,
	PE_KO,
	PE_KU
};

void set_pipe_end1(TPipeEnds& pipe_end, TNodeElement el)
{
	switch (el)
	{
	case elOtvodS:
	case elOtvodI:
	case elOtvodF:
		pipe_end = PE_OTVOD;
		break;
	case elArmat:
		pipe_end = PE_ARMAT;
		break;
	case elCompOs:
		pipe_end = PE_KO;
		break;
	case elCompUg:
		pipe_end = PE_KU;
		break;
	default:
		pipe_end = PE_STYK;
	}
}

void set_pipe_end2(TPipeEnds& pipe_end, TNodeElement el)
{
	switch (el)
	{
	case elArmat:
		pipe_end = PE_ARMAT;
		break;
	case elCompOs:
		pipe_end = PE_KO;
		break;
	case elCompUg:
		pipe_end = PE_KU;
		break;
	default:
		pipe_end = PE_NONE;
	}
}

void Cone(float height, float Rad1, float Rad2)
{
	glPushMatrix();
	glColor3f(1, 0, 1);
	glRotatef(90, 0, 1, 0);
	GLUquadricObj* quadObj = gluNewQuadric();
	//       gluQuadricTexture(quadObj, GL_TRUE);
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, Rad1, Rad2, height, 12, 2);
	gluDeleteQuadric(quadObj);
	glPopMatrix();
}

void Cylinder(float height, float Rad)
{
	Cone(height, Rad, Rad);
}

void Sphere(float Rad)
{
	GLUquadricObj* quadObj = gluNewQuadric();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluSphere(quadObj, Rad, 12, 12);
	gluDeleteQuadric(quadObj);
}

typedef unsigned char byte;

void SetColor(TColor c, bool Selected)
{
	c = Selected ? clYellow : c;
	{
		wxColour cl(c);
		byte r = cl.Red();
		byte g = cl.Green();;
		byte b = cl.Blue();
		glColor3f(float(r) / 256, float(g) / 256, float(b) / 256);
		GLfloat MaterialSpecular[] = {
			0.8f, 0.8f, 0.8f, 1.0f
		};
		glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
	}
}

void SetPipeColor(const Pipe &p, bool Selected)
{
	TColor c;
	if (p.P_type > Max_pipe_type)
		if (p.P_type == INVALID_LOOP)
		{
			c = INVALID_LOOP_COLOR;
		}
		else
			c = getPipeColor(0);
	else
		c = getPipeColor(p.P_type);
	SetColor(c, Selected);
}

const int KO_SECTIONS = 3;

void COGLPipePresenter::AddLine(const float *p1, const float *p2, int NAYZ, const Pipe &p)
{
	{
		float px1 = p1[0], py1 = p1[1], pz1 = p1[2], px2 = p2[0], py2 = p2[1], pz2 = p2[2];
		m_rot.Rotate(px1, py1, pz1);
		m_rot.Rotate(px2, py2, pz2);
		int x1 = ToScrX(px1), y1 = ToScrY(py1);
		int x2 = ToScrX(px2), y2 = ToScrY(py2);
		Interval_ pi;
		pi.StrP = NAYZ;
		pi.EndP = p.EndP;
		pi.x1 = x1;
		pi.y1 = y1;
		pi.x2 = x2;
		pi.y2 = y2;
		pi.Diam = p.Diam / 2000 * m_ViewSettings.ScrScale;
		m_pPipeArr->Intervals.push_back(pi);
	}

	glPushMatrix();
	bool Selected = m_pvecSel->Contains(NAYZ, p.EndP);
	bool NodeSelected = m_pvecSel->Contains(p.EndP, p.EndP);
	bool NodeSelectedF = m_pvecSel->Contains(NAYZ, NAYZ);

	SetPipeColor(p, Selected);
	float x = p.dx, y = p.dy, z = p.dz;
	CAngles a;
	a.calc_angles(x,y,z);
	glTranslatef(p1[0], p1[1], p1[2]);
	glRotatef(a.a_plan, 0, 0, 1);
	glRotatef(- a.a_prof, 0, 1, 0);
	glPushMatrix();
	// Ось X - вдоль трубы
	Pipe pn, // Следующий участок
	     pp={}; // Предыдущий участок
	float pn_len;
	float pp_len;
	float pn_cos = 1;
	float pp_cos = 1;
	float str_x_rot = 0;
	float str_tg_2;
	float end_tg_2;
	// Тангенс половинного угла между следующим и текущим участком
	CPipeArrayContext cnt;

	//      Ret_pipe r=m_pPipeArr->Ret[NAYZ][0];
	TPipeEnds pe_start = PE_NONE, pe_end = PE_NONE;
	if (m_pPipeArr->HasOut(p.EndP))
	{
		pn = m_pPipeArr->OutFirst(p.EndP, cnt);
		pn_len = sqrtf(pn.dx * pn.dx + pn.dy * pn.dy + pn.dz * pn.dz);
		if (!m_pPipeArr->HasOutNext(cnt) && // Только 1 выходящий участок
			fabs(pn_len) > 0.00001)
		{
			if (fabs(fabs(pn_cos = ((p.dx * pn.dx + p.dy * pn.dy + p.dz * pn.dz) / (a.l_gen * pn_len))
			) - 1) > 0.0001)
				set_pipe_end1(pe_end, p.MNEA);
			else
				set_pipe_end2(pe_end, p.MNEA);
		}
	}
	if (m_pPipeArr->HasIn(p.StrP))
	{
		pp = m_pPipeArr->InFirst(p.StrP, cnt);
		pp_len = sqrtf(pp.dx * pp.dx + pp.dy * pp.dy + pp.dz * pp.dz);
		Pipe p_tmp;
		if (!m_pPipeArr->HasInNext(cnt))
		{ // Только 1 входящий участок
			m_pPipeArr->OutFirst(p.StrP, cnt);
			if (!m_pPipeArr->HasOutNext(cnt) && fabs(pp_len) > 0.00001)
			{
				if (fabs(fabs(pp_cos = ((p.dx * pp.dx + p.dy * pp.dy + p.dz * pp.dz) / (a.l_gen *
					pp_len))) - 1) > 0.0001)
					set_pipe_end1(pe_start, pp.MNEA);
				else
					set_pipe_end2(pe_start, pp.MNEA);
			}
			if (pp.StrP == 0)
			{
				p_tmp = pp;
				p_tmp.Diam = p.Diam;
				AddOpor(p_tmp);
				if (NodeSelectedF)
				{
					SetColor(0, true);
					Sphere(p.Diam * 1.5f / 2000);
				}
			}
		}
	}
	CRotator Rot(DegToRad(- a.a_plan), 0, 0);
	Rot.z_rotate(pn.dx, pn.dy, pn.dz);
	if (pe_start != PE_NONE)
		Rot.z_rotate(pp.dx, pp.dy, pp.dz);
	Rot.SetRot(0, DegToRad(a.a_prof), 0);
	Rot.y_rotate(pn.dx, pn.dy, pn.dz);
	if (pe_start != PE_NONE)
		Rot.y_rotate(pp.dx, pp.dy, pp.dz);
	if (pe_end != PE_NONE)
	{
		float ang = (fabs(pn.dy) < 0.0001) ? 2 * atanf(1.0f) * sgn(pn.dz) : atanf(pn.dz / pn.dy);
		glRotatef(RadToDeg(ang), 1, 0, 0);
		Rot.SetRot(0, 0, - ang);
		Rot.x_rotate(pn.dx, pn.dy, pn.dz); // Перешли в С.К., лежащую в
		// плоскости 2-х труб
		// ось X || 1-й трубе
		if (pe_start != PE_NONE)
			Rot.x_rotate(pp.dx, pp.dy, pp.dz);
		float x1 = (1 - pn_cos) / (1 + pn_cos);
		if (x1 < 0)
			x1 = 0;
		end_tg_2 = sqrtf(x1) * sgn(- pn.dy);
	}
	else
	{
		end_tg_2 = 0;
	}
	if (pe_start != PE_NONE)
	{
		str_x_rot = fabs(pp.dy) < 0.0001f ? 2 * atanf(1.0f) * sgn(pp.dz) : atanf(pp.dz / pp.dy);
		Rot.SetRot(0, 0, - str_x_rot);
		Rot.x_rotate(pp.dx, pp.dy, pp.dz); // Перешли в С.К., лежащую в
		float x1 = (1 - pp_cos) / (1 + pp_cos);
		if (x1 < 0)
			x1 = 0;
		str_tg_2 = sqrtf(x1) * sgn(- pp.dy);
	}
	else
	{
		str_tg_2 = 0;
	}
	float styk_len = a.l_gen;
	switch (pe_start)
	{
	case PE_OTVOD:
		glTranslatef(pp.R_Otv * fabsf(str_tg_2), 0, 0);
		styk_len -= pp.R_Otv * fabsf(str_tg_2);
		str_tg_2 = 0;
		break;
	case PE_ARMAT:
		Cone(pp.R_Otv / 2, pp.Diam / 2000 / 4, pp.Diam / 2000);
		glTranslatef(pp.R_Otv / 2, 0, 0);
		styk_len -= pp.R_Otv / 2;
		str_tg_2 = 0;
		break;
	case PE_KO:
		break;
	case PE_KU:
		Cylinder(pp.R_Otv / 2, pp.Diam / 2000);
		glTranslatef(pp.R_Otv / 2, 0, 0);
		styk_len -= pp.R_Otv / 2;
		str_tg_2 = 0;
	case PE_NONE: break;
	case PE_STYK: break;
	default: break;
	}
	switch (pe_end)
	{
	case PE_OTVOD:
		styk_len -= p.R_Otv * fabsf(end_tg_2);
		end_tg_2 = 0;
		break;
	case PE_ARMAT:
	case PE_KO:
	case PE_KU:
		styk_len -= p.R_Otv / 2;
		end_tg_2 = 0;
	case PE_NONE: break;
	case PE_STYK: break;
	default: break;
	}
	SetPipeColor(p, Selected);
	float t1 = 0, t2 = 0;
	if (fabs(p.NaprDop) >= 0.1)
	{
		t1 = p.NaprStr / p.NaprDop * (256.0f - 44.0f) / 256.0f;
		t2 = p.NaprEnd / p.NaprDop * (256.0f - 44.0f) / 256.0f;
	}
	draw_styk(styk_len, p.Diam / 2000, str_x_rot, str_tg_2, end_tg_2, t1, t2, true);
	glTranslatef(styk_len, 0, 0);
	switch (pe_end)
	{
	case PE_OTVOD:
		{
			float betta = acosf(pn_cos) * sgn(pn.dy);
			const int N = 4;
			styk_len = 2 * p.R_Otv * fabsf(sinf(betta / (2 * N)));
			float styk_tan = tanf(betta / (2 * N));
			glRotatef(RadToDeg(betta / N / 2), 0, 0, 1);
			for (int i = 0; i < N; i++)
			{
				SetColor(clRed, NodeSelected);
				draw_styk(styk_len, p.Diam / 2000, 0, styk_tan, -styk_tan, 0, 0, i == N - 1);
				glTranslatef(styk_len, 0, 0);
				glRotatef(RadToDeg(betta / N), 0, 0, 1);
			}
		}
		break;
	case PE_ARMAT:
		Cone(p.R_Otv / 2, p.Diam / 2000, p.Diam / 2000 / 4);
		break;
	case PE_KO:
		// Осевой компенсатор
		for (int i = 0; i < KO_SECTIONS; i++)
		{
			Cone(p.R_Otv / 2 / KO_SECTIONS, p.Diam / 2000, p.Diam * 1.5f / 2000.0f);
			glTranslatef(p.R_Otv / 2 / KO_SECTIONS, 0, 0);
			Cone(p.R_Otv / 2 / KO_SECTIONS, p.Diam * 1.5f / 2000, p.Diam / 2000.0f);
			glTranslatef(p.R_Otv / 2 / KO_SECTIONS, 0, 0);
		}
		break;
	case PE_KU:
		// Угловой компенсатор
		Cylinder(p.R_Otv / 2, p.Diam / 2000);
		glTranslatef(p.R_Otv / 2, 0, 0);
		glColor3f(1, 0, 1);
		Sphere(p.Diam * 1.5f / 2000);
	case PE_NONE: break;
	case PE_STYK: break;
	default: break;
	}
	glPopMatrix();
	glTranslatef(a.l_gen, 0, 0);
	AddOpor(p);
	if (NodeSelected)
	{
		SetColor(0, true);
		Sphere(p.Diam * 1.5f / 2000);
	}
	glPopMatrix();
}

void COGLPipePresenter::AddOpor(const Pipe &p) const
{
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glDisable(GL_TEXTURE_1D);
	GLfloat MaterialSpecular[] = {
		0, 0, 0, 1.0
	};
	glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);
	glRotatef(90, 0, 1, 0);
	float Diam = p.Diam / 1000;
	switch (p.MNEO)
	{
	case elMertOp:
		box(Diam * 1.5f, Diam * 1.5f, Diam * 0.5f);
		break;
	case elSkOp:
		glTranslatef(Diam / 2 + Diam / 4, 0, 0);
		box(Diam / 2, Diam * 1.5f, Diam * 1.5f);
		break;
	case elNaprOp:
		glTranslatef(Diam / 2 * 1.5f / 2, 0, 0);
		box(Diam * 1.5f / 2, Diam * 1.5f, Diam * 1.5f);
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
	case elGestPd: break;
	case elUprOp: break;
	case elSelect: break;
	case elTroinic: break;
	default: break;
	}
	if (m_ViewSettings.ShowNapr)
		glEnable(GL_TEXTURE_1D);
	glPopMatrix();
}

void COGLPipePresenter::AddNodeElement(const float *p, TNodeElement el, float ang)
{
	wxUnusedVar(p);
	wxUnusedVar(el);
	wxUnusedVar(ang);
};

void COGLPipePresenter::AddLineFrom(const float *p1, const float *p2, float Dist, float ang)
{
	wxUnusedVar(p1);
	wxUnusedVar(p2);
	wxUnusedVar(Dist);
	wxUnusedVar(ang);
};

void COGLPipePresenter::AddPodushFrom(const float *p1, const float *p2, float Dist, float ang)
{
	wxUnusedVar(p1);
	wxUnusedVar(p2);
	wxUnusedVar(Dist);
	wxUnusedVar(ang);
};

void COGLPipePresenter::AddCircle(const float *p, float rad)
{
	wxUnusedVar(p);
	wxUnusedVar(rad);
}

void COGLPipePresenter::PushMatrixes(bool bInvertY) const
{
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	if (bInvertY)
		glOrtho(0, double(m_ClientRect.GetWidth()), double(m_ClientRect.GetHeight()), 0, -1, 1);
	else
		glOrtho(0, double(m_ClientRect.GetWidth()), 0, double(m_ClientRect.GetHeight()), -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
}

void COGLPipePresenter::PopMatrixes()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glDisable(GL_LIGHTING);
}


void COGLPipePresenter::AddNodeNum(const float *p, float Dist, float ang, int NodeNum, float rad)
{
	SPoint pt = m_Points[NodeNum];
	if (pt.set)
		return;
	pt.x = p[0];
	pt.y = p[1];
	pt.z = p[2];
	pt.set = true;
	m_Points[NodeNum] = pt;

    const double NARROW_COEFF = 0.7;
	glColor3f(0, 0, 0);
	CString str = CString::Format(_T("%d"), NodeNum);
	rad /= 2.0f;
	//AddTextFrom(p,Dist,ang,int(rad*20/25),str,0,0);
	//TEXTMETRIC tm;
	CSize sz = m_pRenderer->GetFontExtent(SVF_NODENUMS, str.c_str()/*&tm*/);
	float pw = CurPipe.Diam / 1000 * m_ViewSettings.ScrScale;
	Dist += (pw / 2);
	float _x = p[0], _y = p[1], _z = p[2];

	double x;// = ToScrX(_x) - Dist * m_ElemScale * sin(ang);//int x = int(ToScrX(_x) - Dist * m_ElemScale * sin(ang));
	double y;// = ToScrY(_y) - Dist * m_ElemScale * cos(ang);//int y = int(ToScrY(_y) - Dist * m_ElemScale * cos(ang));
    double z;// = _z;//
    Project(_x,_y,_z,x,y,z, true);
    x-= Dist * m_ElemScale * sin(ang);
    y-= Dist * m_ElemScale * cos(ang);
    z = (0.5-z)*2;

	int th = sz.y;
	int tw = int(sz.x * (1 + NARROW_COEFF) / 2);
	//glDepthRange(1, 0);

	PushMatrixes();
	glColor3ub(255, 0, 0);
	glBegin(GL_LINE_LOOP);
	constexpr int nSegments = 16;
	double M_2PI = 8 * atan(1.0);
	for (int i = 0; i < nSegments; i++)
	{
		glVertex3d(x + rad * sin(i * M_2PI / nSegments), y + rad * cos(i * M_2PI / nSegments), z);
	}
	glEnd();

	glBegin(GL_LINES);
	int x1 = int(x + rad * m_ElemScale * sin(ang)), y1 = int(y + rad * m_ElemScale * cos(ang));
	glVertex3f(float(x1), float(y1), float(z));
	glVertex3f(x1 + 2 * nTickSize * m_ElemScale * sinf(ang), y1 + 2 * nTickSize * m_ElemScale * cosf(ang), float(z));
	glEnd();

	glColor3ub(255, 255, 255);
	//SetColor(wxYELLOW->GetPixel(), false);
	GLfloat MaterialSpecular[] = {
		0.8f, 0.8f, 0.8f, 1.0f
	};
	glMaterialfv(GL_FRONT, GL_SPECULAR, MaterialSpecular);

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < nSegments; i++)
	{
		glVertex3d(x + rad * sin(i * M_2PI / nSegments), y + rad * cos(i * M_2PI / nSegments), z-0.001);
	}
	glEnd();
	glPolygonOffset(0, 0);
	glColor3f(0, 0, 0);
	//glRasterPos3d(x - tw / 2, y + th / 2, 1);
	glPushMatrix();
	glTranslated(x - tw / 2, y + th / 2, z);
	glScaled(1,-1,1);
	glScaled(NARROW_COEFF,1,1);
	//glTranslated(0,0,-0.1);
	m_pRenderer->DrawText(str.c_str(), SVF_NODENUMS);
	glPopMatrix();

	PopMatrixes();
	glEnable(GL_LIGHTING);
};

extern float CalcAng(float, float);
//extern float RadToDeg(float x);
extern float NormAng(float ang);

void COGLPipePresenter::AddTextFrom2(const float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode, float pw) const
{
	glDisable(GL_LIGHTING);
	size *= 15;
	size /= 12;

	//TEXTMETRIC tm;
	CSize sz = m_pRenderer->GetFontExtent(SVF_DIMS, txt.c_str()/*&tm*/);
	//sz.x=tm.tmAveCharWidth*txt.Length();
	if (Dist < 0)
		Dist -= pw;
	else
		Dist += pw;
	//float dx = CurPipe.dx, dy = CurPipe.dy, dz = CurPipe.dz;
	//m_rot.Rotate(dx, dy, dz);
	//ang = CalcAng(dx, dy);
	//ang = -NormAng(ang);
	float px = p[0], py = p[1], pz = p[2];
	//Dist+= CurPipe.Diam/1000;///2;//*m_ViewSettings.ScrScale;
	//m_rot.Rotate(px, py, pz);

	//int x = int(ToScrX(px) - Dist * sin(ang));
	//int y = int(ToScrY(py) - Dist * cos(ang));
	double x;// = ToScrX(_x) - Dist * m_ElemScale * sin(ang);//int x = int(ToScrX(_x) - Dist * m_ElemScale * sin(ang));
	double y;// = ToScrY(_y) - Dist * m_ElemScale * cos(ang);//int y = int(ToScrY(_y) - Dist * m_ElemScale * cos(ang));
	double z;// = _z;//
	Project(px, py, pz, x, y, z, false);
	x -= Dist * m_ElemScale * sin(ang);
	y += Dist * m_ElemScale * cos(ang);
	z = (0.5 - z) * 2;

	//Rotation =ang;//+atan(1.0f)*2;
	float tw = -sz.x-2;// *size / -m_pRenderer->GetFontSize(SVF_DIMS);
	float th = -sz.y;// *size / -m_pRenderer->GetFontSize(SVF_DIMS);
	float tx = (tw * cosf(Rotation) - th * sinf(Rotation));
	float ty = (tw * sinf(Rotation) + th * cosf(Rotation));

	PushMatrixes(false);

	glColor3b(0, 0, 0);
	float angG = RadToDeg(Rotation);
	glTranslatef(float(x) - tx / 2, float(y) - ty / 2, float(z));//+ty),1);
	glRotatef(angG, 0, 0, 1);
	if (TextMode == tOVERLINE)
	{
		glBegin(GL_LINES);
		glVertex3f(0, (size + th-4) / 2, 0);
		glVertex3f(tw, (size + th-4) / 2, 0);
		glEnd();
	}
#if 0
	glBegin(GL_LINE_LOOP);
		glVertex3f(0,0,0);
		glVertex3f(0,th,0);
		glVertex3f(tw,th,0);
		glVertex3f(tw,0,0);
	glEnd();
#endif
	glTranslatef(tw,th,0);
	//glScalef(float(size), float(size), float(size));
	m_pRenderer->DrawText(txt.c_str(),SVF_DIMS);
	PopMatrixes();
	glEnable(GL_LIGHTING);
}
void COGLPipePresenter::AddTextFrom(const float* p, float Dist, float ang, int size, CString txt, float Rotation, int TextMode)
{
	STextInfo s;
	s.p[0] = p[0];
	s.p[1] = p[1];
	s.p[2] = p[2];
	s.Dist = Dist;
	s.ang = ang;
	s.size = size;
	s.txt = txt;
	s.Rotation = Rotation;
	s.TextMode = TextMode;
	s.pw = CurPipe.Diam / 1000 * m_ViewSettings.ScrScale / 2;

	m_vecTexts.push_back(s);
}

void COGLPipePresenter::Add2TextFrom(float* p, float Dist, float ang, int size,
                                     CString txt, CString txt1, float Rotation)
{
	AddTextFrom(p, Dist, ang, size, txt, Rotation, tNONE);
	AddTextFrom(p, Dist + size, ang, size, txt1, Rotation, tOVERLINE);
};

//extern LPCTSTR LoadStr(UINT nID);
#define LoadStr(x) x


void COGLPipePresenter::AddVertLine(const float *strPoint, float dz)
{
	float Dist = 40;
	CString txt1 = (dz > 0) ? LoadStr(IDS_PODJOM) : LoadStr(IDS_OPUSK),
		txt2 = CString::Format(_T("h=%.1f"), dz);

	CSize sz = m_pRenderer->GetFontExtent(SVF_TEXT, txt1.c_str());
	CSize sz1 = m_pRenderer->GetFontExtent(SVF_TEXT, txt2.c_str());
	int w = std::max(sz.x,sz1.x);
	int h = std::max(sz.y,sz1.y);
	//int w1 = w + w / 4;
	//    h+=h/5;
	int x = ToScrX(strPoint[0]), y = ToScrY(strPoint[1]);
	PushMatrixes();
	glDisable(GL_LIGHTING);
	glColor3b(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3i(x, y, 1);
	x += int(Dist * m_ElemScale / 2);
	y -= int(Dist * m_ElemScale);
	glVertex3i(x, y, 1);
	glVertex3i(x, y, 1);
	x += w;
	glVertex3i(x, y, 1);
	glEnd();
	x -= w;
	y -= h / 4;
	//float size = 15;
	glTranslated(x, y, 1);
	glScaled(1,-1,1);
	m_pRenderer->DrawText(txt1.c_str(), SVF_TEXT);
	glTranslated(0,-(h+h/5),0);

	m_pRenderer->DrawText( txt2.c_str(), SVF_TEXT);
	PopMatrixes();
	glEnable(GL_LIGHTING);
}

void COGLPipePresenter::Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z)
{
	m_rot.Rotate(x, y, z);
};

GLvoid COGLPipePresenter::initializeGL() const
{
	glClearColor(1, 1, 1, 1);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_LINE_SMOOTH);
	set_view();
	SetupLighting();
}

COGLPipePresenter::COGLPipePresenter(CPipeArray* PipeArray, CGLFontRenderer* rend, CRotator& _rot, CViewSettings& _viewSettings, wxGLCanvas* parent):
	CScreenPipePresenter(PipeArray, _rot, _viewSettings), m_pRenderer(rend),canvas(parent)
{
	Scl = 15;
}

void COGLPipePresenter::set_view() const
{
	float width = float(m_ClientRect.GetWidth()), height = float(m_ClientRect.GetHeight());
	glViewport(m_ClientRect.GetLeft(), m_ClientRect.GetTop(), m_ClientRect.GetWidth(), m_ClientRect.GetHeight());
	//  aspect = (GLfloat) width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -(z_max + 2) * m_ViewSettings.ScrScale, -(z_min - 2) * m_ViewSettings.ScrScale);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

COGLPipePresenter::~COGLPipePresenter()
{
}

void COGLPipePresenter::DrawCoordSys() const
{
	glEnable(GL_LIGHTING);
	glClear(GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, m_ClientRect.GetWidth(), 0, m_ClientRect.GetHeight(), -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_position[] = {0,0,1,0};
	glLightfv(GL_LIGHT0,GL_POSITION, light_position);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_FALSE);
	glShadeModel(GL_SMOOTH);

	float xr = RadToDeg(m_rot.Fx_rot);
	float zr = RadToDeg(m_rot.Fz_rot);

    for (int i=0; i<2; i++)
    {
        glPushMatrix();
        glTranslatef(50, 50, 0);
        glRotatef(xr, 1, 0, 0);
        glRotatef(zr, 0, 0, 1);
        glColor3f(0, 0, 1);
        DrawAxe('Z',i==0);
        glRotatef(90, 0, 1, 0);
        glColor3f(1, 0, 0);
        DrawAxe('X',i==0);
        glRotatef(-90, 1, 0, 0);
        glColor3f(0, 1, 0);
        DrawAxe('Y',i==0);
        glColor3f(0, 0, 0);
        glPopMatrix();
    }
}


void COGLPipePresenter::Project(double x, double y, double z, double& wx, double& wy, double& wz, bool bInvertY)
{
	double		MVM[16];
	double		PJM[16];
	int			VP[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, MVM);
	glGetDoublev(GL_PROJECTION_MATRIX, PJM);
	glGetIntegerv(GL_VIEWPORT, VP);
	gluProject(x, y, z, MVM, PJM, VP, &wx, &wy, &wz);
    if (bInvertY)
        wy = VP[3]-wy;
}

void COGLPipePresenter::DrawAxe(char Name, bool bAxe) const
{
	glPushMatrix();
	if (bAxe)
    {
        GLUquadricObj* quadObj = gluNewQuadric();

        gluQuadricDrawStyle(quadObj, GLU_FILL);
        gluQuadricNormals(quadObj, GLU_SMOOTH);
        gluCylinder(quadObj, 2, 2, 30, 10, 2);

        glTranslatef(0, 0, 30);

        gluDisk(quadObj, 5, 0, 10, 2);
        gluCylinder(quadObj, 5, 0, 15, 10, 2);
        gluDeleteQuadric(quadObj);
    }
    else
    {
        glTranslatef(0, 0, 50);
        double wx;
        double wy;
        double wz;
        double x=0, y=0, z=0;
        Project(x, y, z, wx, wy, wz);
        PushMatrixes(false);
        wz = (0.5-wz)*2;
        CSize sz = m_pRenderer->GetFontExtent(SVF_TEXT, wxString(Name).c_str());
        glTranslated(wx-sz.x/2, wy, wz);
        glDisable(GL_LIGHTING);
        m_pRenderer->DrawText(wxString(Name).c_str(), SVF_TEXT );
        glEnable(GL_LIGHTING);
        PopMatrixes();
    }
	glPopMatrix();
}


//const float AxisSize=30;
void COGLPipePresenter::Draw(CRect ClientRect, bool bPrinting)
{
	//wglMakeCurrent(ghDC, ghRC);
	//unsigned long s_start = timeGetTime();
	wxGetApp().SetContext(canvas);
	//return;
	m_ClientRect = ClientRect;
	DrawMain(true);
	initializeGL();

	glTranslatef(m_ViewSettings.Xorg, - m_ViewSettings.Yorg + m_ClientRect.GetHeight(), 0);
	glRotatef(RadToDeg(m_rot.Fx_rot), 1, 0, 0);
	glRotatef(RadToDeg(m_rot.Fz_rot), 0, 0, 1);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_NORMALIZE);
	glScalef(m_ViewSettings.ScrScale, m_ViewSettings.ScrScale, m_ViewSettings.ScrScale);
	//glBindTexture(GL_TEXTURE_1D, texture1);
	try
	{
		//#ifdef OGL_INIT_ONCE
#if 0
   if(m_bNewGeometry) {
      glNewList(1, GL_COMPILE_AND_EXECUTE);
      DrawMain(false);
      glEndList();
      m_bNewGeometry = false;
   }
   else
   glCallList(1);
#else
		DrawMain(false);
		DrawTexts();
#endif
	}
	catch (...)
	{
	}
	DrawCoordSys();
	if (!bPrinting)
		canvas->SwapBuffers();
	//StatusBar1->Panels->Items[1]->Text = IntToStr(timeGetTime() - s_start) + " мсек";
	//wglMakeCurrent(nullptr, nullptr);
	CString strText = CString::Format(LoadStr(IDS_FORMAT_UCH_UZL), m_NumPipes, m_NumNodes);
	//static_cast<CMainFrame*>(AfxGetMainWnd())->m_wndStatusBar.SetPaneText(1, strText);

	//               "Участков:"+IntToStr(m_NumPipes)+
	//              "  Узлов:"+IntToStr(m_NumNodes);
	//   DrawAxis(AxisSize,0,0,'X',Rot);
	//   DrawAxis(0,AxisSize,0,'Y',Rot);
	//   DrawAxis(0,0,AxisSize,'Z',Rot);
	//     wglMakeCurrent(nullptr,nullptr);
	//wxGetApp().SetContext(canvas, true);
}

void COGLPipePresenter::DrawDottedRect(const CRect& rc, CRect clr)
{
	Draw(clr, true);
	int x1 = rc.GetLeft(), y1 = rc.GetTop(), x2 = rc.GetRight(), y2 = rc.GetBottom();
	int VP[4];
	glGetIntegerv(GL_VIEWPORT, VP);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(0, 0, 0);
	glDisable(GL_DEPTH_TEST);
	glOrtho(0.0, VP[2], VP[3], 0, -1, 1); // Установка экранной СК
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xCCCC);
	//glLineWidth(1);
	glDisable(GL_LINE_SMOOTH);
	glBegin(GL_LINE_LOOP); // Ограничивающий прямоугольник
	glVertex3d(x1, y1, 0);
	glVertex3d(x1, y2, 0);
	glVertex3d(x2, y2, 0);
	glVertex3d(x2, y1, 0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	canvas->SwapBuffers();
}

//void COGLPipePresenter::InitGLScene()
//{
///*	glClearColor(1, 1, 1, 1);
//	glClearDepth(1.0);
//	glEnable(GL_DEPTH_TEST);
//	//float width=MainForm1->PaintBox1->Width,
//	//      height=MainForm1->PaintBox1->Height;
//	//    GLfloat aspect;
//	glViewport(0, 0, render.bmRect.GetRight(), render.bmRect.GetBottom());
//	//  aspect = (GLfloat) width / height;
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, render.bmRect.GetRight(), 0, render.bmRect.GetBottom(), -10000, 10000
//	);
//	//            (z_min-1)*m_ViewSettings.ScrScale,(z_max+1)*m_ViewSettings.ScrScale);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	SetupLighting();*/
//}


void COGLPipePresenter::Print(CDC* pDC, const wxRect& rectPrint)
{
#if defined(__WXMSW__) || defined(__WXGTK__) || defined(__WXMAC__)
	wxSize renderSize;
	CViewSettings saveSettings = m_ViewSettings;
	float fAspPrn = float(rectPrint.GetHeight()) / rectPrint.GetWidth();
	float fAspScr = float(m_ClientRect.GetHeight()) / m_ClientRect.GetWidth();
	CRect clr1(m_ClientRect);
	if (fAspPrn > fAspScr)
	{
		renderSize.x = m_ClientRect.GetWidth();
        renderSize.y = int(m_ClientRect.GetHeight() * fAspPrn / fAspScr);
		m_ClientRect.SetBottom(renderSize.y);
	}
	else
	{
        renderSize.x = int(m_ClientRect.GetWidth() / fAspPrn * fAspScr);
        m_ClientRect.SetRight(renderSize.x);
		renderSize.y = m_ClientRect.GetHeight();
	}
	double dLowScale = 1.0;
	renderSize.x/=dLowScale; renderSize.y/=dLowScale;
	m_ViewSettings.ScrScale /= dLowScale;
	m_ViewSettings.Xorg /= dLowScale; m_ViewSettings.Yorg /= dLowScale;
	m_ClientRect.width /= dLowScale; m_ClientRect.height /= dLowScale;
	clr1.width = clr1.width/dLowScale; clr1.height = clr1.height/dLowScale;

	CDibGlSurface render(renderSize, pDC);
	initializeGL();
	CGLFontRenderer *renderer = m_pRenderer;
	CGLFontRenderer r;
	m_pRenderer = &r;
	EFontType ft = FT_PolygonFont;
	SLogFont arrFonts[] = {
		{ 10, FT_TextureFont },
		{ 16, ft },
		{ 16, ft }
	};
	m_pRenderer->BuildAllFonts(arrFonts);
	if (fAspPrn > fAspScr)
		m_ViewSettings.Yorg += (renderSize.y - clr1.GetHeight()) / 2;
	else
		m_ViewSettings.Xorg += (renderSize.x - clr1.GetWidth()) / 2;

	glTranslatef(m_ViewSettings.Xorg, - m_ViewSettings.Yorg + m_ClientRect.GetHeight(), 0);
	glRotatef(RadToDeg(m_rot.Fx_rot), 1, 0, 0);
	glRotatef(RadToDeg(m_rot.Fz_rot), 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glScalef(m_ViewSettings.ScrScale, m_ViewSettings.ScrScale, m_ViewSettings.ScrScale);
	glEnable(GL_NORMALIZE);
	DrawMain(false);
	DrawCoordSys();
	glFinish();
	render.DoDraw(pDC, rectPrint);
	m_pRenderer = renderer;
	m_ViewSettings = saveSettings;
#endif
}


