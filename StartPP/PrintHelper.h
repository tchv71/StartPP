#pragma once

class CPrintHelper
{
public:
	CPrintHelper(void);
	~CPrintHelper(void);
	static void DrawFrame(CDC* pDC, CRect& rcDib, CString strFileName);
	static void DrawPageBorder
	(
		CDC* pDC,
		CRect& r,
		float fAspX,
		float fAspY,
		int W,
		int H,
		CString strFileName
	);
};

