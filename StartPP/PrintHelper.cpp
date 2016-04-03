#include "StdAfx.h"
#include "PrintHelper.h"
#include "Colors.h"
#include "shlwapi.h"

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
	RECT& r, // Сжимаемый прямоугольник
	SFloatRect* offset, // Зазоры по краям, мм
	float fAspX,
	float fAspY // Масштаб по осям X и Y
)
{
	r.top += LONG(offset->top * fAspY);
	r.right -= LONG(offset->right * fAspX);
	r.bottom -= LONG(offset->bottom * fAspY);
	r.left += LONG(offset->left * fAspX);
}

static void MovePoint(long& pos, float fDesired/*mm*/, float fGap/*mm*/, float fAsp, int nDir)
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
			pDC->GetDeviceCaps(PHYSICALOFFSETX) / fAspX,
			pDC->GetDeviceCaps(PHYSICALOFFSETY) / fAspY,
			(pDC->GetDeviceCaps(PHYSICALWIDTH) - pDC->GetDeviceCaps(PHYSICALOFFSETX) - W) / fAspX,
			(pDC->GetDeviceCaps(PHYSICALHEIGHT) - pDC->GetDeviceCaps(PHYSICALOFFSETY) - H) / fAspY
		};

	//	int PW = pDC->GetDeviceCaps(PHYSICALWIDTH);
	//	int POX = pDC->GetDeviceCaps(PHYSICALOFFSETX);
	//	int lX =pDC->GetDeviceCaps(HORZRES);
	//	int szX =pDC->GetDeviceCaps(HORZSIZE);

	//ShrinkRect(r, (H > W) ? &PortraitShrink : &LandscapeShrink, fAspX, fAspY);
	bool bPortrait = (H > W);
	SFloatRect* pShRc = bPortrait ? &PortraitShrink : &LandscapeShrink;
	MovePoint(r.left, pShRc->left, sPrinterGaps.left, fAspX, 1);
	MovePoint(r.top, pShRc->top, sPrinterGaps.top, fAspY, 1);
	MovePoint(r.right, pShRc->right, sPrinterGaps.right, fAspX, -1);
	MovePoint(r.bottom, pShRc->bottom, sPrinterGaps.bottom, fAspY, -1);

	pDC->MoveTo(r.left, r.top); // Ограничивающий прямоугольник
	pDC->LineTo(r.right, r.top);
	pDC->LineTo(r.right, r.bottom);
	pDC->LineTo(r.left, r.bottom);
	pDC->LineTo(r.left, r.top);

	int nGap = int(2 * fAspX);
	PathCompactPath(pDC->GetSafeHdc(), strFileName.GetBuffer(MAX_PATH), r.right - r.left - 2 * nGap);
	strFileName.ReleaseBuffer();

	CSize szText = pDC->GetTextExtent(strFileName);

	int nFieldHeigh = szText.cy * 3 / 2;

	pDC->TextOut(r.left + nGap, r.top + szText.cy / 4, strFileName);
	r.top += nFieldHeigh;
	pDC->MoveTo(r.left, r.top);
	pDC->LineTo(r.right, r.top);
	SFloatRect Shrink = {1, 1, 1, 1};
	ShrinkRect(r, &Shrink, fAspX, fAspY);
}


void CPrintHelper::DrawFrame(CDC* pDC, CRect& rcDib, CString strFileName)
{
	float fAspX = pDC->GetDeviceCaps(LOGPIXELSX) / 25.4f; //float(m_szPage.cx)/szPageMM.cx; // pix/mm
	float fAspY = pDC->GetDeviceCaps(LOGPIXELSY) / 25.4f; //float(m_szPage.cy)/szPageMM.cy;
	CSize m_szPage;
	m_szPage.cx = pDC->GetDeviceCaps(HORZRES);
	m_szPage.cy = pDC->GetDeviceCaps(VERTRES);

	int nLineWidth = int(0.3f/*mm*/ * fAspX + 0.5); // pix
	CPen pen(PS_SOLID, nLineWidth, COLORREF(clBlack));
	CPen* pOldPen = pDC->SelectObject(&pen);
	CFont font;
	font.CreateFont(12 * pDC->GetDeviceCaps(LOGPIXELSY) / 72, 0, 0, 0,FW_NORMAL, 0, 0, 0,RUSSIAN_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,_T("Arial"));
	CFont* pOldFont = pDC->SelectObject(&font);
	DrawPageBorder(pDC, rcDib, fAspX, fAspY, m_szPage.cx, m_szPage.cy, strFileName);
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

