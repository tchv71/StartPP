// NewNodeDialog.cpp: файл реализации
//

#include "stdafx.h"
#include "resource.h"
#include "NewNodeDialog.h"
#include "afxdialogex.h"
#include <math.h>

// диалоговое окно CNewNodeDialog

IMPLEMENT_DYNAMIC(CNewNodeDialog, CDialogEx)

CNewNodeDialog::CNewNodeDialog(CWnd* pParent, CPipes& pipes)
	: CDialogEx(CNewNodeDialog::IDD, pParent), m_pipes(pipes)
	  , m_nNewNode(0)
	  , m_nPipes(2)
{
}

CNewNodeDialog::~CNewNodeDialog()
{
}

void CNewNodeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_btnCheck);
	DDX_Control(pDX, IDC_RADIO1, m_btnRadio);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_nNewNode);
	DDX_Text(pDX, IDC_EDIT2, m_nPipes);
	DDX_Control(pDX, IDC_EDIT2, m_ePipes);
	DDX_Control(pDX, IDC_EDIT3, m_eDist);
}


BEGIN_MESSAGE_MAP(CNewNodeDialog, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CNewNodeDialog::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, &CNewNodeDialog::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CNewNodeDialog::OnBnClickedRadio2)
	END_MESSAGE_MAP()


// обработчики сообщений CNewNodeDialog


INT_PTR CNewNodeDialog::DoModal()
{
	// TODO: добавьте специализированный код или вызов базового класса

	return CDialogEx::DoModal();
}

extern LPCTSTR LoadStr(UINT nID);


void CNewNodeDialog::OnOK()
{
	UpdateData(TRUE);
	int NewNode;
	float Dist[100];
	int NumDist = 0;
	bool WasGap = false;
	int nIdx = m_combo.GetCurSel();
	NewNode = m_nNewNode;
	if (m_btnRadio.GetCheck() == BST_CHECKED)
	{
		for (int i = 0; i < m_eDist.GetLineCount(); i++ , NumDist++)
		{
			CString str;
			TCHAR buf[100];
			m_eDist.GetLine(i, buf, 100);
			str = buf;
			if (str.Trim() != "")
				Dist[i] = float(_wtof(str));
			else
			{
				if (WasGap)
				{
					AfxMessageBox(IDS_MORE_ONE_BLANK_LINE);
					return;
				}
				WasGap = true;
				Dist[i] = -1;
			}
		}
	}
	else
	{
		NumDist = m_nPipes;
		WasGap = true;
	}
	if (!WasGap) Dist[NumDist++] = -1;
	//Pipes->rst->Filter="NAYZ="+eNewNode->Text;
	//Pipes->rst->Filtered=TRUE;
	//if (Pipes->rst->FindFirst()) {
	//	MessageDlg("Узел "+eNewNode->Text+" уже существует",mtError,
	//		TMsgDlgButtons() <<mbOK,0);
	//	Pipes->rst->Filtered=FALSE;
	//	Pipes->rst->Bookmark=bm;
	//	return;
	//}
	CPipeAndNode p = m_pipes.m_vecPnN[nIdx];
	float dx = p.m_OSIX,
		dy = p.m_OSIY,
		dz = p.m_OSIZ,
		oldLen = sqrt(dx * dx + dy * dy + dz * dz);
	if (m_btnRadio.GetCheck() != BST_CHECKED)
	{
		if (NumDist < 2)
		{
			AfxMessageBox(LoadStr(IDS_PIPES_MUSTBE_MORE1));
			return;
		}
		for (int i = 0; i < NumDist - 1; i++) Dist[i] = oldLen / NumDist;
		Dist[NumDist - 1] = -1;
	}
	float DistSum = 0;
	for (int i = 0; i < NumDist; i++)
		if (fabs(Dist[i] + 1) > 0.0001) DistSum += Dist[i];
	if (DistSum >= oldLen)
	{
		AfxMessageBox(LoadStr(IDS_DIST_SUM_MORE_PIPE_LEN));
		return;
	}
	m_pipes.SetINDX(nIdx, NumDist);
	int IDX_F = int(p.m_INDX);
	int NewStrNode = NewNode, NewEndNode = NewNode + NumDist - 2;
	CPipeAndNode p1;
	m_pipes.CopyValues(p1, p);
	m_pipes.m_vecPnN.insert(m_pipes.m_vecPnN.begin() + nIdx, NumDist - 1, p);
	for (int i = NewStrNode; i <= NewEndNode; i++ , nIdx++)
	{
		CPipeAndNode& p2 = m_pipes.m_vecPnN[nIdx];
		p2.m_NAYZ = float(i == NewStrNode ? int(p.m_NAYZ) : i - 1);
		p2.m_KOYZ = float(i);
		p2.m_INDX = float(IDX_F);
		float len = (fabs(Dist[i - NewNode] + 1) > 0.0001) ? Dist[i - NewNode] : (oldLen - DistSum);
		p2.m_OSIX = dx * len / oldLen;
		p2.m_OSIY = dy * len / oldLen;
		p2.m_OSIZ = dz * len / oldLen;
		IDX_F += 100;
		p2.m_MNEA = "";
		p2.m_SILX = 0.0f;
		if ((m_btnCheck.GetState() & BST_CHECKED) != 0)
		{
			p2.m_MNEO = "ск";
			p2.m_KOTR = 0.3f;
		}
		else
		{
			p2.m_MNEO = "";
			p2.m_KOPR = 0.0f;
		}
	}
	float len = (fabs(Dist[NumDist - 1] + 1) > 0.0001) ? Dist[NumDist - 1] : (oldLen - DistSum);
	CPipeAndNode& p2 = m_pipes.m_vecPnN[nIdx];

	p2.m_NAYZ = float(NewEndNode);
	p2.m_OSIX = p2.m_OSIX * len / oldLen;;
	p2.m_OSIY = p2.m_OSIY * len / oldLen;
	p2.m_OSIZ = p2.m_OSIZ * len / oldLen;
	p2.m_INDX = float(IDX_F);
	m_pipes.m_nIdx = nIdx;
	CDialogEx::OnOK();
}


BOOL CNewNodeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int nMaxNodeNum;
	m_pipes.FillCb(&m_combo, nMaxNodeNum);
	m_combo.SetCurSel(int(m_pipes.m_nIdx));
	m_nNewNode = nMaxNodeNum + 1;
	UpdateData(false);
	m_btnCheck.SetCheck(BST_CHECKED);
	m_btnRadio.SetCheck(BST_CHECKED);
	m_eDist.EnableWindow(TRUE);
	m_ePipes.EnableWindow(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
}


void CNewNodeDialog::OnCbnSelchangeCombo1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CNewNodeDialog::OnBnClickedRadio1()
{
	m_eDist.EnableWindow(TRUE);
	m_ePipes.EnableWindow(FALSE);
}


void CNewNodeDialog::OnBnClickedRadio2()
{
	m_eDist.EnableWindow(FALSE);
	m_ePipes.EnableWindow(TRUE);
}


BOOL CNewNodeDialog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: добавьте специализированный код или вызов базового класса

	//return CDialogEx::PreTranslateMessage(pMsg);
	return FALSE;
}

