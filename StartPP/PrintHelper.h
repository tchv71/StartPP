#pragma once
struct SFloatRect
{
	double left, top, right, bottom;
};

class CPrintHelper
{
public:
	CPrintHelper(void);
	~CPrintHelper(void);
	static void DrawPageBorder(CDC* pDC, CRect& r, float fAspX, float fAspY, int W, int H, CString strFileName, SFloatRect sPrinterGaps);
	static void DrawFrame(CDC *pDC, CRect &rcDib, CString strFileName, float fAspX, float fAspY,
                          const SFloatRect &margins);
};

