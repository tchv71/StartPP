// SpuskDialog.cpp : implementation file
//

#include "stdafx.h"
#include "StartPP.h"
#include "SpuskDialog.h"
#include "PipesSet.h"
#include "Pipe.h"
#include <math.h>
#include "PipesSet.h"
#include "ArmatSet.h"

// CSpuskDialog dialog

IMPLEMENT_DYNAMIC(CSpuskDialog, CDialog)

CSpuskDialog::CSpuskDialog(CWnd* pParent /*=nullptr*/, CVecPnN& PnN)
	: CDialog(CSpuskDialog::IDD, pParent)
	  , m_h(1.0f)
	  , m_H1(1.0f)
	  , m_H2(1.0f)
	  , m_PnN(PnN)
	  , m_Radio(0)
{
}

CSpuskDialog::~CSpuskDialog()
{
}

void CSpuskDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DIAM, m_lstDiam);
	DDX_Control(pDX, IDC_CHECK1, m_rSpusk);
	DDX_Control(pDX, IDC_IMAGE, m_Image);
	if (!pDX->m_bSaveAndValidate) DDX_Check(pDX, IDC_RADIO1, m_Radio);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Text(pDX,IDC_EDIT1, m_h);
	DDX_Text(pDX,IDC_EDIT2, m_H1);
	DDX_Text(pDX,IDC_EDIT3, m_H2);
}


BEGIN_MESSAGE_MAP(CSpuskDialog, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_DIAM, &CSpuskDialog::OnLbnSelchangeListDiam)
	ON_BN_CLICKED(IDC_RADIO1, &CSpuskDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSpuskDialog::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSpuskDialog::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CSpuskDialog::OnBnClickedRadio4)
	END_MESSAGE_MAP()


// CSpuskDialog message handlers

void CSpuskDialog::OnLbnSelchangeListDiam()
{
	m_btnOk.EnableWindow();
}

extern float sqr(float x);

BOOL CSpuskDialog::OnInitDialog()
{
	m_Radio = 1;
	CDialog::OnInitDialog();
	SetBitmap(IDB_BITMAP_SPUSK);
	CPipesSet set;
	set.m_strPath = _T(".");
	set.m_strTable = _T("[Pipes] order by DIAM, PODZ");
	set.Open();
	float oldSet = 0;
	while (!set.IsEOF())
	{
		CString str;
		str.Format(_T("%g"), set.m_DIAM);
		if (set.m_DIAM != oldSet)
			m_lstDiam.AddString(str);

		oldSet = set.m_DIAM;
		set.MoveNext();
	}
	set.Close();
	m_rSpusk.SetCheck(BST_CHECKED);
	return TRUE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSpuskDialog::OnBnClickedRadio1()
{
	m_Radio = 1;
	SetBitmap(IDB_BITMAP_SPUSK);
}

void CSpuskDialog::OnBnClickedRadio2()
{
	m_Radio = 2;
	SetBitmap(IDB_VREZ45);
}

void CSpuskDialog::OnBnClickedRadio3()
{
	m_Radio = 3;
	SetBitmap(IDB_GUS);
}

void CSpuskDialog::OnBnClickedRadio4()
{
	m_Radio = 4;
	SetBitmap(IDB_PARALEL);
}

void CSpuskDialog::SetBitmap(int bmId)
{
	HBITMAP bmp = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(bmId));
	m_Image.SetBitmap(bmp);
}

void CSpuskDialog::OnOK()
{
	CDialog::OnOK();
	float s;
	if (m_rSpusk.GetCheck() == BST_CHECKED)
		s = 1;
	else
		s = -1;
	CPipeAndNode p = m_PnN.m_vecPnN[m_PnN.m_nIdx];
	float dx = p.m_OSIX * s, dy = p.m_OSIY * s;
	float s1 = sqrt(sqr(dx) + sqr(dy));
	dx /= s1;
	dy /= s1;
	CPipes pipe(m_PnN.m_nIdx, m_PnN.m_vecPnN);
	CPipeAndNode p1;
	pipe.CopyValues(p1, p);
	int nNewIDX = 0, nNewNode = 0;
	for (unsigned i = 0; i < m_PnN.m_vecPnN.size(); i++)
	{
		if (int(m_PnN.m_vecPnN[i].m_INDX) >= nNewIDX)
		{
			nNewIDX = int(m_PnN.m_vecPnN[i].m_INDX);
		}
		if (int(m_PnN.m_vecPnN[i].m_KOYZ) >= nNewNode)
		{
			nNewNode = int(m_PnN.m_vecPnN[i].m_KOYZ);
		}
	}
	nNewNode += 1;
	nNewIDX += 100;
	switch (m_Radio)
	{
	case 1:
	case 2:
	case 4:
		{
			p1.m_OSIX = dy * m_h;
			p1.m_OSIY = -dx * m_h;
			if (m_Radio == 1)
				p1.m_OSIZ = -m_h;
			else if (m_Radio == 2)
				p1.m_OSIZ = m_h;
			else
				p1.m_OSIZ = 0;

			p1.m_NAYZ = p.m_KOYZ;
			p1.m_KOYZ = float(nNewNode);
			p1.m_INDX = float(nNewIDX);
			CString sDiam;
			nNewNode += 1;
			m_lstDiam.GetText(m_lstDiam.GetCurSel(), sDiam);
			p1.m_DIAM = float(_wtof(sDiam));
			CPipesSet set;
			set.m_strPath = _T(".");
			set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ order by DIAM, PODZ"),
			                                                                                   p1.m_DIAM, int(FALSE));
			set.Open();
			p1.m_VETR = set.m_VETR;
			p1.m_VEIZ = set.m_VEIZ;
			p1.m_VEPR = set.m_VEPR;
			p1.m_INDX = float(nNewIDX);
			nNewIDX += 100;
			CArmatSet aset;
			aset.m_strPath = _T(".");
			aset.m_strTable.Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			p1.m_MNEA = "ос";
			p1.m_RAOT = aset.m_RAOT;
			p1.m_MARI = set.m_MARI;
			p1.m_NOTO = p.m_NOTO;
			p1.m_RATO = p.m_RATO;
			p1.m_VESA = aset.m_VESA;
			p1.m_VREZKA = "";
			aset.Close();
			m_PnN.m_vecPnN.push_back(p1);

			CPipeAndNode p2;
			pipe.CopyValues(p2, p1);
			p2.m_NAYZ = p1.m_KOYZ;
			p2.m_KOYZ = float(nNewNode++);
			if (m_Radio == 4)
			{
				p2.m_OSIX = -dx * m_H1 * s;
				p2.m_OSIY = -dy * m_H1 * s;
				p2.m_OSIZ = 0;
			}
			else
			{
				p2.m_OSIX = dy * m_H1;
				p2.m_OSIY = -dx * m_H1;
				p2.m_OSIZ = 0;
			}
			aset.m_strPath = _T(".");
			aset.m_strTable.Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			p2.m_MNEA = "ар";
			p2.m_RAOT = aset.m_RAOT1;
			p2.m_VESA = aset.m_VESA1;
			p2.m_VREZKA = "";
			aset.Close();
			set.Close();
			p2.m_INDX = float(nNewIDX);
			nNewIDX += 100;
			m_PnN.m_vecPnN.push_back(p2);

			pipe.CopyValues(p1, p2);
			p1.m_NAYZ = p2.m_KOYZ;
			p1.m_KOYZ = float(nNewNode);
			if (m_Radio == 4)
			{
				p1.m_OSIX = -dx * m_H2 * s;
				p1.m_OSIY = -dy * m_H2 * s;
				p1.m_OSIZ = 0;
			}
			else
			{
				p1.m_OSIX = dy * m_H2;
				p1.m_OSIY = -dx * m_H2;
				p1.m_OSIZ = 0;
			}
			if (m_Radio == 1)
			{
				p1.m_MNEO = "нп";
				p1.m_KOTR = 0.3f;
			}
			p1.m_MNEA = "";
			p1.m_INDX = float(nNewIDX);
			//nNewIDX+=100;
			m_PnN.m_vecPnN.push_back(p1);
		}
		break;
	case 3:
		{
			p1.m_OSIX = dy * m_h;
			p1.m_OSIY = -dx * m_h;
			p1.m_OSIZ = m_h;
			p1.m_NAYZ = p.m_KOYZ;
			p1.m_KOYZ = float(nNewNode++);
			p1.m_INDX = float(nNewIDX);
			CString sDiam;
			m_lstDiam.GetText(m_lstDiam.GetCurSel(), sDiam);
			p1.m_DIAM = float(_wtof(sDiam));
			CPipesSet set;
			set.m_strPath = _T(".");
			set.m_strTable.Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ order by DIAM, PODZ"),
			                                                                                   p1.m_DIAM, int(FALSE));
			set.Open();
			p1.m_VETR = set.m_VETR;
			p1.m_VEIZ = set.m_VEIZ;
			p1.m_VEPR = set.m_VEPR;
			nNewIDX += 100;
			CArmatSet aset;
			aset.m_strPath = _T(".");
			aset.m_strTable.Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			p1.m_MNEA = "ос";
			p1.m_RAOT = aset.m_RAOT;
			p1.m_MARI = set.m_MARI;
			p1.m_NOTO = p.m_NOTO;
			p1.m_RATO = p.m_RATO;
			p1.m_VESA = aset.m_VESA;
			p1.m_VREZKA = "";
			aset.Close();
			m_PnN.m_vecPnN.push_back(p1);

			p1.m_OSIX = dy * m_H1;
			p1.m_OSIY = -dx * m_H1;
			p1.m_OSIZ = 0;
			p1.m_NAYZ = p1.m_KOYZ;
			p1.m_KOYZ = float(nNewNode++);
			p1.m_INDX = float(nNewIDX);
			nNewIDX += 100;
			m_PnN.m_vecPnN.push_back(p1);

			p1.m_OSIX = dy * m_h;
			p1.m_OSIY = -dx * m_h;
			p1.m_OSIZ = -m_h;
			p1.m_NAYZ = p1.m_KOYZ;
			p1.m_KOYZ = float(nNewNode++);
			p1.m_INDX = float(nNewIDX);
			nNewIDX += 100;
			m_PnN.m_vecPnN.push_back(p1);

			CPipeAndNode p2;
			pipe.CopyValues(p2, p1);

			p2.m_NAYZ = p1.m_KOYZ;
			p2.m_KOYZ = float(nNewNode);
			p2.m_OSIX = dy * m_H2;
			p2.m_OSIY = -dx * m_H2;
			p2.m_OSIZ = 0;
			aset.m_strPath = _T(".");
			aset.m_strTable.Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			p2.m_MNEA = "ар";
			p2.m_RAOT = aset.m_RAOT1;
			p2.m_VESA = aset.m_VESA1;
			p2.m_VREZKA = "";
			aset.Close();
			set.Close();
			p2.m_INDX = float(nNewIDX);
			//nNewIDX+=100;
			m_PnN.m_vecPnN.push_back(p2);
		}
		break;
	}
}

