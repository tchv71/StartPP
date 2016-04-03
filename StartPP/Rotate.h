// Copyright (C) 1998,1999,2000,2003,2004,2005,2006  Dmitry Tcvetkov aka TCHV
//
// All Rights Reserved
//
// Disclaimer : this text is under authority of goverment laws, US and Russian Federation
// Unauthorizing compilation, modification and re-engineering is strictly prohibited
//---------------------------------------------------------------------------
#ifndef RotateH
#define RotateH
#include "SvTypes.h"

struct sRotProjInfo
{
	sRotProjInfo()
	{
		m_fZ_rot = 0;
		m_fX_rot = 0;
	}

	sRotProjInfo(const FLOAT_TYPE& fZrot, const FLOAT_TYPE& fXrot)
	{
		m_fZ_rot = fZrot;
		m_fX_rot = fXrot;
	}

	sRotProjInfo& operator=(const sRotProjInfo& dpi)
	{
		m_fZ_rot = dpi.m_fZ_rot;
		m_fX_rot = dpi.m_fX_rot;
		return *this;
	}

	float m_fZ_rot;
	float m_fX_rot;
};

enum SCDefProjType
{
	DPT_Top,
	DPT_Bottom,
	DPT_Front,
	DPT_Back,
	DPT_Left,
	DPT_Right,
	DPT_SouthEast,
	DPT_SouthWest,
	DPT_NorthWest,
	DPT_NorthEast,
	DPT_Dimetry,
	DPT_Size
};

class CRotator
{
public:
	FLOAT_TYPE Fz_rot;
	FLOAT_TYPE Fy_rot;
	FLOAT_TYPE Fx_rot;
	FLOAT_TYPE z_s;
	FLOAT_TYPE z_c;
	FLOAT_TYPE x_s;
	FLOAT_TYPE x_c;
	FLOAT_TYPE y_s;
	FLOAT_TYPE y_c;
public:
	void z_rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) const;
	void y_rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) const;
	void x_rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) const;
	CRotator(void);

	CRotator(FLOAT_TYPE z_rot, FLOAT_TYPE x_rot)
	{
		SetRot(z_rot, x_rot);
	};

	CRotator(FLOAT_TYPE z_rot, FLOAT_TYPE y_rot, FLOAT_TYPE x_rot)
	{
		SetRot(z_rot, y_rot, x_rot);
	};

	void SetRot(FLOAT_TYPE z_rot, FLOAT_TYPE x_rot);
	void SetRot(FLOAT_TYPE z_rot, FLOAT_TYPE y_rot, FLOAT_TYPE x_rot);
	void GetRot(FLOAT_TYPE& z_rot, FLOAT_TYPE& x_rot) const;
	void Rotate(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) const;
	void Rotate_1(FLOAT_TYPE& x, FLOAT_TYPE& y, FLOAT_TYPE& z) const;

	void SetPredefinedView(int ViewNo);
	static bool GetInfo(int type, sRotProjInfo& info);

	static sRotProjInfo m_Info[DPT_Size];
	//#define x_rot Fx_rot //    FLOAT_TYPE __declspec(property)  x_rot={read=Fx_rot,write=Fx_rot};
	//#define z_rot Fz_rot //   __declspec(property) FLOAT_TYPE z_rot={read=Fz_rot,write=Fz_rot};
};

//---------------------------------------------------------------------------
#endif

