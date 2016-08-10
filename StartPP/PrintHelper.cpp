#include "stdafx.h"
#include "PrintHelper.h"
#include "Colors.h"
//#include "shlwapi.h"

CPrintHelper::CPrintHelper(void)
{
}

CPrintHelper::~CPrintHelper(void)
{
}

struct SFloatRect
{
	float left, top, right, bottom;
};


static void ShrinkRect
(
	CRect& r, // Ñæèìàåìûé ïðÿìîóãîëüíèê
	SFloatRect* offset, // Çàçîðû ïî êðàÿì, ìì
	float fAspX,
	float fAspY // Ìàñøòàá ïî îñÿì X è Y
)
{
	r.x += LONG(offset->left * fAspX);
	r.y += LONG(offset->top * fAspY);
	r.width -= LONG((offset->left+offset->right) * fAspX);
	r.height -= LONG((offset->top+offset->bottom) * fAspY);
}

static void MovePoint(int& pos, float fDesired/*mm*/, float fGap/*mm*/, float fAsp, int nDir)
{
	float fVal = fDesired > fGap + 0.5f ? fDesired - fGap : 0.5f;
	pos += int(fVal * fAsp + 0.5f) * nDir;
}


void CPrintHelper::DrawPageBorder
(
	CDC* pDC,
	CRect& r,
	float fAspX,
	float fAspY,
	int W,
	int H,
	CString strFileName
)
{
	SFloatRect PortraitShrink = {20, 5, 5, 5},
		LandscapeShrink = {5, 20, 5, 5};
	SFloatRect sPrinterGaps = // mm
		{
			0,//pDC->GetDeviceOrigin().x / fAspX,
			0,//pDC->GetDeviceOrigin().y / fAspY,
			0,//(pDC->GetSizeMM().x - pDC->GetDeviceOrigin().x - W) / fAspX,
			0//(pDC->GetSizeMM().y - pDC->GetDeviceOrigin().y - H) / fAspY
		};

	//	int PW = pDC->GetDeviceCaps(PHYSICALWIDTH);
	//	int POX = pDC->GetDeviceCaps(PHYSICALOFFSETX);
	//	int lX =pDC->GetDeviceCaps(HORZRES);
	//	int szX =pDC->GetDeviceCaps(HORZSIZE);

	ShrinkRect(r, (H > W) ? &PortraitShrink : &LandscapeShrink, fAspX, fAspY);
	bool bPortrait = (H > W);
	SFloatRect* pShRc = bPortrait ? &PortraitShrink : &LandscapeShrink;
	MovePoint(r.x, pShRc->left, sPrinterGaps.left, fAspX, 1);
	MovePoint(r.y, pShRc->top, sPrinterGaps.top, fAspY, 1);
	MovePoint(r.width, pShRc->right, sPrinterGaps.right, fAspX, -1);
	MovePoint(r.height, pShRc->bottom, sPrinterGaps.bottom, fAspY, -1);

	pDC->DrawRectangle(r); // Îãðàíè÷èâàþùèé ïðÿìîóãîëüíèê

	int nGap = int(2 * fAspX);
	//PathCompactPath(pDC->GetSafeHdc(), strFileName.GetBuffer(MAX_PATH), r.right - r.left - 2 * nGap);
	//strFileName.ReleaseBuffer();

	CSize szText = pDC->GetTextExtent(strFileName);

	int nFieldHeigh = szText.y * 3 / 2;

	pDC->DrawText(strFileName,r.GetLeft()+ nGap, r.GetTop() + szText.y / 4);
	r.y += nFieldHeigh;
	r.height -= nFieldHeigh;
	pDC->DrawLine(r.GetLeft(), r.GetTop(), r.GetRight(), r.GetTop());
	SFloatRect Shrink = {1, 1, 1, 1};
	ShrinkRect(r, &Shrink, fAspX, fAspY);
}


void CPrintHelper::DrawFrame(CDC* pDC, CRect& rcDib, CString strFileName, double fAspX, double fAspY)
{
	wxSize sz = rcDib.GetSize();


	wxSize szPPI = pDC->GetPPI();
	//float fAspX = double(/*szPPI.GetWidth())/25.4/sx;//*/sz.GetWidth())/szMM.GetWidth(); // pix/mm
	//float fAspY = double(/*szPPI.GetHeight())/25.4/sy;//*/sz.GetHeight())/szMM.GetHeight();
	CSize m_szPage = sz;
	wxPoint pt = pDC->GetDeviceOrigin();
	//m_szPage.cx = pDC->GetDeviceCaps(HORZRES);
	//m_szPage.cy = pDC->GetDeviceCaps(VERTRES);

	int nLineWidth = int(0.3f/*mm*/ * fAspX + 0.5); // pix
	wxPen pen(wxColor(0,0,0), nLineWidth, wxPENSTYLE_SOLID);
	pDC->SetPen(pen);
	//CPen* pOldPen = pDC->SelectObject(&pen);
	//CFont font;
	//font.CreateFont(12 * pDC->GetDeviceCaps(LOGPIXELSY) / 72, 0, 0, 0,FW_NORMAL, 0, 0, 0,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
	//CFont* pOldFont = pDC->SelectObject(&font);
	DrawPageBorder(pDC, rcDib, fAspX, fAspY, m_szPage.GetWidth(), m_szPage.GetHeight(), strFileName);
	//pDC->SelectObject(pOldFont);
	//pDC->SelectObject(pOldPen);
}

