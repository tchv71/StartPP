// SpuskDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SpuskDialog.h"
#include "PipesSet.h"
#include "Pipe.h"
#include <math.h>
#include "PipesSet.h"
#include "ArmatSet.h"
#include "Strings.h"
#include <algorithm>

// CSpuskDialog dialog

//IMPLEMENT_DYNAMIC(CSpuskDialog, CDialog)

CSpuskDialog::CSpuskDialog(CWnd* pParent /*=nullptr*/, CVecPnN& PnN)
	: CSpuskBaseDialog(pParent)
	  , m_h(1.0f)
	  , m_H1(1.0f)
	  , m_H2(1.0f)
	  , m_PnN(PnN)
	  , m_Radio(0)
{
	OnInitDialog();
}

CSpuskDialog::~CSpuskDialog()
{
}


BEGIN_MESSAGE_MAP(CSpuskDialog, CDialog)
	EVT_LISTBOX(wxIDC_LIST_DIAM, CSpuskDialog::OnLbnSelchangeListDiam)
END_MESSAGE_MAP()


// CSpuskDialog message handlers

void CSpuskDialog::OnLbnSelchangeListDiam(wxCommandEvent& event)
{
	m_buttonOk->Enable(true);
	event.Skip();
}

extern float sqr(float x);

BOOL CSpuskDialog::OnInitDialog()
{
	m_Radio = 1;
	m_buttonOk->Enable(false);
	//CDialog::OnInitDialog();
	//SetBitmap(IDB_BITMAP_SPUSK);
	CPipesSet set;
	set.m_strPath = DATA_PATH;
	set.m_strTable = _T("Pipes.dbf"); //_T("[Pipes] order by DIAM, PODZ");
	set.Open();
	float oldSet = 0;
	std::vector<float> vecDiams;
	while (!set.IsEOF())
	{
		//CString str;
		//str.Format(_T("%g"), set.m_DIAM);
		vecDiams.push_back(set.m_DIAM);
		set.MoveNext();
	}
	set.Close();
	std::sort(vecDiams.begin(), vecDiams.end());
	for (auto x : vecDiams)
	{
		if (fabs(x-oldSet)>0.1)
			m_listBoxDiam->Append(CString::Format(_T("%g"), x));
		oldSet = x;
	}
	//m_rSpusk.SetCheck(BST_CHECKED);
	return TRUE; // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSpuskDialog::OnOK()
{
	//CDialog::OnOK();
	float s;
	double d;
	if (!m_textCtrl_h->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(_T("Ошибка в параметрах"), wxOK | wxICON_EXCLAMATION);
		return;
	}
	m_h = d;

	if (!m_textCtrl_H1->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(_T("Ошибка в параметрах"), wxOK | wxICON_EXCLAMATION);
		return;
	}
	m_H1 = d;

	if (!m_textCtrl_H2->GetValue().ToCDouble(&d))
	{
		AfxMessageBox(_T("Ошибка в параметрах"), wxOK | wxICON_EXCLAMATION);
		return;
	}
	m_H2 = d;

	if (m_checkBoxUhod->GetValue())
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
	m_Radio = m_notebook->GetSelection()+1;
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
			CString sDiam = m_listBoxDiam->GetString(m_listBoxDiam->GetSelection());
			nNewNode += 1;
			sDiam.ToCDouble(&d);
			p1.m_DIAM = d;
			CPipesSet set;
			set.m_strPath = DATA_PATH;
			set.m_strTable =_T("Pipes.dbf"); // Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ order by DIAM, PODZ"), p1.m_DIAM, int(FALSE));
			set.Open();
			while (!set.IsEOF())
			{
				if (fabs(set.m_DIAM - p1.m_DIAM) > 0.1)
				{
					set.MoveNext();
					continue;
				}
				break;
			}
			p1.m_VETR = set.m_VETR;
			p1.m_VEIZ = set.m_VEIZ;
			p1.m_VEPR = set.m_VEPR;
			p1.m_INDX = float(nNewIDX);
			nNewIDX += 100;
			CArmatSet aset;
			aset.m_strPath = DATA_PATH;
			aset.m_strTable = _T("Armat.dbf"); //Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			while (!aset.IsEOF())
			{
				if (fabs(aset.m_DIAM - p1.m_DIAM) > 0.1)
				{
					aset.MoveNext();
					continue;
				}
				break;
			}
			p1.m_MNEA = STR_OS;
			p1.m_RAOT = aset.m_RAOT;
			p1.m_MARI = set.m_MARI;
			p1.m_NOTO = p.m_NOTO;
			p1.m_RATO = p.m_RATO;
			p1.m_VESA = aset.m_VESA;
			p1.m_VREZKA = _T("");
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
			aset.m_strPath = DATA_PATH;
			aset.m_strTable = _T("Armat.dbf"); //Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			while (!aset.IsEOF())
			{
				if (fabs(aset.m_DIAM - p1.m_DIAM) > 0.1)
				{
					aset.MoveNext();
					continue;
				}
				break;
			}
			p2.m_MNEA = STR_AR;
			p2.m_RAOT = aset.m_RAOT1;
			p2.m_VESA = aset.m_VESA1;
			p2.m_VREZKA = _T("");
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
				p1.m_MNEO = STR_NP;
				p1.m_KOTR = 0.3f;
			}
			p1.m_MNEA = _T("");
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
			CString sDiam = m_listBoxDiam->GetString(m_listBoxDiam->GetSelection());
			sDiam.ToCDouble(&d);
			p1.m_DIAM = d;
			CPipesSet set;
			set.m_strPath = DATA_PATH;
			set.m_strTable = _T("Pipes.dbf"); // Format(_T("[Pipes] WHERE DIAM = %g and %d=PODZ order by DIAM, PODZ"), p1.m_DIAM, int(FALSE));
			set.Open();
			while (!set.IsEOF())
			{
				if (fabs(set.m_DIAM - p1.m_DIAM) > 0.1)
				{
					set.MoveNext();
					continue;
				}
				break;
			}
			p1.m_VETR = set.m_VETR;
			p1.m_VEIZ = set.m_VEIZ;
			p1.m_VEPR = set.m_VEPR;
			nNewIDX += 100;
			CArmatSet aset;
			aset.m_strPath = DATA_PATH;
			aset.m_strTable = _T("Armat.dbf"); //Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			while (!aset.IsEOF())
			{
				if (fabs(aset.m_DIAM - p1.m_DIAM) > 0.1)
				{
					aset.MoveNext();
					continue;
				}
				break;
			}
			p1.m_MNEA = STR_OS;
			p1.m_RAOT = aset.m_RAOT;
			p1.m_MARI = set.m_MARI;
			p1.m_NOTO = p.m_NOTO;
			p1.m_RATO = p.m_RATO;
			p1.m_VESA = aset.m_VESA;
			p1.m_VREZKA = _T("");
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
			aset.m_strPath = DATA_PATH;
			aset.m_strTable = _T("Armat.dbf"); //Format(_T("[Armat] WHERE DIAM = %g  order by DIAM"), p1.m_DIAM);
			aset.Open();
			while (!aset.IsEOF())
			{
				if (fabs(aset.m_DIAM - p1.m_DIAM) > 0.1)
				{
					aset.MoveNext();
					continue;
				}
				break;
			}
			p2.m_MNEA = STR_AR;
			p2.m_RAOT = aset.m_RAOT1;
			p2.m_VESA = aset.m_VESA1;
			p2.m_VREZKA = _T("");
			aset.Close();
			set.Close();
			p2.m_INDX = float(nNewIDX);
			//nNewIDX+=100;
			m_PnN.m_vecPnN.push_back(p2);
		}
		break;
	}
}

void CSpuskDialog::EndModal(int retcode)
{
	if (retcode == wxID_OK)
		OnOK();
	CSpuskBaseDialog::EndModal(retcode);
}
