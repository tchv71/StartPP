#pragma once
#include "Archive.h"

class CPipeAndNode
{
public:
	CPipeAndNode(void);
	~CPipeAndNode(void);
	float m_NAYZ;
	float m_KOYZ;
	float m_OSIX;
	float m_OSIY;
	float m_OSIZ;
	CStringA m_NAMA;
	float m_DIAM;
	float m_NTOS;
	float m_RTOS;
	float m_RATE;
	float m_RADA;
	float m_VETR;
	float m_VEIZ;
	float m_VEPR;
	float m_KOPE;
	float m_KOPR;
	float m_KOYS;
	float m_KORA;
	CStringA m_MNEA;
	CStringA m_MNEO;
	float m_DABI;
	float m_RAOT;
	float m_DIGI;
	CStringA m_MARI;
	float m_NOTO;
	float m_RATO;
	float m_KOTR;
	float m_VESA;
	float m_SEOP;
	float m_VEYS;
	CStringA m_PELI;
	CStringA m_PEYG;
	CStringA m_TIDE;
	float m_RASG;
	float m_DEFX;
	float m_DEFY;
	float m_DEFZ;
	float m_DEME;
	float m_NAGV;
	float m_NAGX;
	float m_NAGY;
	float m_NAGZ;
	float m_VESX;
	float m_VESY;
	float m_VESZ;
	float m_SILX;
	float m_SILY;
	float m_SILZ;
	float m_MOMX;
	float m_MOMY;
	float m_MOMZ;
	float m_NAAN;
	float m_NABA;
	float m_VIZA;
	float m_SHTR;
	float m_VIVO;
	float m_INDX;
	float m_NONE;
	CStringA m_VREZKA;
	CStringA m_TEXT;
	float m_KOR;
	float m_VIZA2;
	float m_OS_TR1;
	float m_OS_TR2;
	float m_KORPUS;
	BOOL m_TYPE_KOMP;
	double m_L_KOMP;

	void Serialize(CArchive& ar);
};

