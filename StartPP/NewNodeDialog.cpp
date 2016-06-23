// NewNodeDialog.cpp: файл реализации
//

#include "stdafx.h"
//#include "resource.h"
#include "NewNodeDialog.h"
#include <math.h>
#include "Strings.h"

// диалоговое окно CNewNodeDialog

CNewNodeDialog::CNewNodeDialog(CWnd* pParent, CPipes& pipes)
	: CNewNodeBaseDialog(pParent), m_pipes(pipes)
	  , m_nNewNode(0)
	  , m_nPipes(2)
{
	OnInitDialog();
}

CNewNodeDialog::~CNewNodeDialog()
{
}

/*
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
*/

BEGIN_MESSAGE_MAP(CNewNodeDialog, CNewNodeBaseDialog)
	EVT_RADIOBUTTON(wxID_RADIO1, CNewNodeDialog::OnBnClickedRadio1)
	EVT_RADIOBUTTON(wxID_RADIO2, CNewNodeDialog::OnBnClickedRadio2)
END_MESSAGE_MAP()


// обработчики сообщений CNewNodeDialog



//extern LPCTSTR LoadStr(UINT nID);


void CNewNodeDialog::OnOK()
{
	//UpdateData(TRUE);
	long l;
	m_textCtrlFirstNode->GetValue().ToCLong(&l); m_nNewNode = l;
	m_textCtrlNumPipes->GetValue().ToCLong(&l); m_nPipes = l;
	int NewNode;
	float Dist[100];
	int NumDist = 0;
	bool WasGap = false;
	int nIdx = m_choice->GetSelection();
	NewNode = m_nNewNode;
	if (m_radioButton1->GetValue())
	{
		for (int i = 0; i < m_textCtrlLengths->GetNumberOfLines(); i++ , NumDist++)
		{
			CString str = m_textCtrlLengths->GetLineText(i);
			if (str.Trim() != _T(""))
				Dist[i] = float(_wtof(str));
			else
			{
				if (WasGap)
				{
					AfxMessageBox(IDS_MORE_ONE_BLANK_LINE, wxOK);
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
	if (!m_radioButton1->GetValue())
	{
		if (NumDist < 2)
		{
			AfxMessageBox(LoadStr(IDS_PIPES_MUSTBE_MORE1), wxOK);
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
		AfxMessageBox(LoadStr(IDS_DIST_SUM_MORE_PIPE_LEN), wxOK);
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
		if (m_checkBoxSkop->GetValue())
		{
			p2.m_MNEO = _T("ск");
			p2.m_KOTR = 0.3f;
		}
		else
		{
			p2.m_MNEO = _T("");
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
	//CDialogEx::OnOK();
}


BOOL CNewNodeDialog::OnInitDialog()
{
	//CDialogEx::OnInitDialog();
	int nMaxNodeNum;
	m_pipes.FillCb(m_choice, nMaxNodeNum);
	m_choice->SetSelection(int(m_pipes.m_nIdx));
	m_nNewNode = nMaxNodeNum + 1;
	m_textCtrlFirstNode->SetValue(CString::Format(_T("%d"), m_nNewNode));
	m_textCtrlNumPipes->SetValue(_T("2"));
	//UpdateData(false);
	//m_btnCheck.SetCheck(BST_CHECKED);
	//m_radioButton1->SetCheck(BST_CHECKED);
	//m_eDist.EnableWindow(TRUE);
	//m_ePipes.EnableWindow(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
}



void CNewNodeDialog::OnBnClickedRadio1(wxCommandEvent& event)
{
	m_textCtrlLengths->Enable(true);
	m_textCtrlNumPipes->Enable(false);
	event.Skip();
}


void CNewNodeDialog::OnBnClickedRadio2(wxCommandEvent& event)
{
	m_textCtrlLengths->Enable(false);
	m_textCtrlNumPipes->Enable(true);
	event.Skip();
}


void CNewNodeDialog::EndModal(int retcode)
{
	if (retcode == wxID_OK)
		OnOK();
	CNewNodeBaseDialog::EndModal(retcode);
}

