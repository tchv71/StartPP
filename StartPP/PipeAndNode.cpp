#include "stdafx.h"
#include "PipeAndNode.h"


CPipeAndNode::CPipeAndNode(void)
{
	m_NAYZ = 0.0;
	m_KOYZ = 0.0;
	m_OSIX = 0.0;
	m_OSIY = 0.0;
	m_OSIZ = 0.0;
	m_NAMA = "";
	m_DIAM = 0.0;
	m_NTOS = 0.0;
	m_RTOS = 0.0;
	m_RATE = 0.0;
	m_RADA = 0.0;
	m_VETR = 0.0;
	m_VEIZ = 0.0;
	m_VEPR = 0.0;
	m_KOPE = 0.0;
	m_KOPR = 0.0;
	m_KOYS = 0.0;
	m_KORA = 0.0;
	m_MNEA = "";
	m_MNEO = "";
	m_DABI = 0.0;
	m_RAOT = 0.0;
	m_DIGI = 0.0;
	m_MARI = "";
	m_NOTO = 0.0;
	m_RATO = 0.0;
	m_KOTR = 0.0;
	m_VESA = 0.0;
	m_SEOP = 0.0;
	m_VEYS = 0.0;
	m_PELI = "";
	m_PEYG = "";
	m_TIDE = "";
	m_RASG = 0.0;
	m_DEFX = 0.0;
	m_DEFY = 0.0;
	m_DEFZ = 0.0;
	m_DEME = 0.0;
	m_NAGV = 0.0;
	m_NAGX = 0.0;
	m_NAGY = 0.0;
	m_NAGZ = 0.0;
	m_VESX = 0.0;
	m_VESY = 0.0;
	m_VESZ = 0.0;
	m_SILX = 0.0;
	m_SILY = 0.0;
	m_SILZ = 0.0;
	m_MOMX = 0.0;
	m_MOMY = 0.0;
	m_MOMZ = 0.0;
	m_NAAN = 0.0;
	m_NABA = 0.0;
	m_VIZA = 0.0;
	m_SHTR = 0.0;
	m_VIVO = 0.0;
	m_INDX = 0.0;
	m_NONE = 0.0;
	m_VREZKA = "";
	m_TEXT = "";
	m_KOR = 0.0;
	m_VIZA2 = 0.0;
	m_OS_TR1 = 0.0;
	m_OS_TR2 = 0.0;
	m_KORPUS = 0;
	m_TYPE_KOMP = FALSE;
	m_L_KOMP = 0.0;
}


CPipeAndNode::~CPipeAndNode(void)
{
}


void CPipeAndNode::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_NAYZ;
		ar << m_KOYZ;
		ar << m_OSIX;
		ar << m_OSIY;
		ar << m_OSIZ;
		ar << m_NAMA;
		ar << m_DIAM;
		ar << m_NTOS;
		ar << m_RTOS;
		ar << m_RATE;
		ar << m_RADA;
		ar << m_VETR;
		ar << m_VEIZ;
		ar << m_VEPR;
		ar << m_KOPE;
		ar << m_KOPR;
		ar << m_KOYS;
		ar << m_KORA;
		ar << m_MNEA;
		ar << m_MNEO;
		ar << m_DABI;
		ar << m_RAOT;
		ar << m_DIGI;
		ar << m_MARI;
		ar << m_NOTO;
		ar << m_RATO;
		ar << m_KOTR;
		ar << m_VESA;
		ar << m_SEOP;
		ar << m_VEYS;
		ar << m_PELI;
		ar << m_PEYG;
		ar << m_TIDE;
		ar << m_RASG;
		ar << m_DEFX;
		ar << m_DEFY;
		ar << m_DEFZ;
		ar << m_DEME;
		ar << m_NAGV;
		ar << m_NAGX;
		ar << m_NAGY;
		ar << m_NAGZ;
		ar << m_VESX;
		ar << m_VESY;
		ar << m_VESZ;
		ar << m_SILX;
		ar << m_SILY;
		ar << m_SILZ;
		ar << m_MOMX;
		ar << m_MOMY;
		ar << m_MOMZ;
		ar << m_NAAN;
		ar << m_NABA;
		ar << m_VIZA;
		ar << m_SHTR;
		ar << m_VIVO;
		ar << m_INDX;
		ar << m_NONE;
		ar << m_VREZKA;
		ar << m_TEXT;
		ar << m_KOR;
		ar << m_VIZA2;
		ar << m_OS_TR1;
		ar << m_OS_TR2;
		ar << m_KORPUS;
		ar << m_TYPE_KOMP;
		ar << m_L_KOMP;
	}
	else
	{
		ar >> m_NAYZ;
		ar >> m_KOYZ;
		ar >> m_OSIX;
		ar >> m_OSIY;
		ar >> m_OSIZ;
		ar >> m_NAMA;
		ar >> m_DIAM;
		ar >> m_NTOS;
		ar >> m_RTOS;
		ar >> m_RATE;
		ar >> m_RADA;
		ar >> m_VETR;
		ar >> m_VEIZ;
		ar >> m_VEPR;
		ar >> m_KOPE;
		ar >> m_KOPR;
		ar >> m_KOYS;
		ar >> m_KORA;
		ar >> m_MNEA;
		ar >> m_MNEO;
		ar >> m_DABI;
		ar >> m_RAOT;
		ar >> m_DIGI;
		ar >> m_MARI;
		ar >> m_NOTO;
		ar >> m_RATO;
		ar >> m_KOTR;
		ar >> m_VESA;
		ar >> m_SEOP;
		ar >> m_VEYS;
		ar >> m_PELI;
		ar >> m_PEYG;
		ar >> m_TIDE;
		ar >> m_RASG;
		ar >> m_DEFX;
		ar >> m_DEFY;
		ar >> m_DEFZ;
		ar >> m_DEME;
		ar >> m_NAGV;
		ar >> m_NAGX;
		ar >> m_NAGY;
		ar >> m_NAGZ;
		ar >> m_VESX;
		ar >> m_VESY;
		ar >> m_VESZ;
		ar >> m_SILX;
		ar >> m_SILY;
		ar >> m_SILZ;
		ar >> m_MOMX;
		ar >> m_MOMY;
		ar >> m_MOMZ;
		ar >> m_NAAN;
		ar >> m_NABA;
		ar >> m_VIZA;
		ar >> m_SHTR;
		ar >> m_VIVO;
		ar >> m_INDX;
		ar >> m_NONE;
		ar >> m_VREZKA;
		ar >> m_TEXT;
		ar >> m_KOR;
		ar >> m_VIZA2;
		ar >> m_OS_TR1;
		ar >> m_OS_TR2;
		ar >> m_KORPUS;
		ar >> m_TYPE_KOMP;
		ar >> m_L_KOMP;
	}
}

