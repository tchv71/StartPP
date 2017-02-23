//
// Created by Дмитрий Цветков on 18.02.17.
//

#ifndef STARTPP_CPROPVALUED_H
#define STARTPP_CPROPVALUED_H


#include <map>
#include "stdafx.h"
#include "ArmatSet.h"
#include "PipesSet.h"
#include "PipeAndNode.h"

enum
{
	E_OSIX = 1,
	E_OSIY,
	E_OSIZ,
	E_LEN_PLAN,
	E_LEN_TOTAL,
	E_ANG_PLAN_ABS,
	E_ANG_PLAN_REL,
	E_ANG_PROF,
	E_UKLON,
	E_DIAM,
	E_MATERIAL,
	E_NTOS,
	E_RTOS,
	E_RADA,
	E_DABI,
	E_RATE,
	E_VETR,
	E_VEIZ,
	E_VEPR,
	E_KOPE,
	E_KOPR,
	E_NAGV,
	E_NAGX,
	E_NAGY,
	E_NAGZ,
	E_DIAM_KOZHUX,
	E_VIZA_BEG,
	E_SHTR,
	E_GRTYPE_UP,
	E_GRTYPE_OSN,
	E_GRTYPE_SIDE,
	E_VIZA_END,
	E_OS_TR_BEG,
	E_OS_TR_END,

	E_PIPE_TYPE = 50,

	E_IZD_TYPE = 100,
	E_OPOR_TYPE,
	E_DEF_TYPE,
	E_UOP_NTG,
	E_UOP_IZM_NAGR,
	E_UOP_KZAP,
	E_UOP_PODD_US,
	E_UOP_PODATL,

	E_ZHP_LEN_TYAGI,

	E_ARM_LEN = 110,
	E_ARM_VES,

	E_RAOT = 134,
	E_VESOTV,
	E_MATOTV,
	E_NOTO_OTV,
	E_RATO_OTV,
	E_RAOT_SV = 160,
	E_VESOTV_SV,
	E_MATOTV_SV,
	E_NOTO_SV,
	E_RATO_SV,

	E_RAOT_OF = 170,
	E_VESOTV_OF,
	E_MATOTV_OF,
	E_NOTO_OF,
	E_RATO_OF,
	E_KO_SEFF = 139,
	E_KO_PODATL,
	E_KO_OS_HOD,
	E_KU_PODATL,
	E_KU_LEN,
	E_TR_MAT,
	E_TR_VES,
	E_TR_NOTO_MAG,
	E_TR_RATO_MAG,
	E_TR_LEN_MAG,
	E_TR_DIAM_OTV,
	E_TR_NOTO_OTV,
	E_TR_RATO_OTV,
	E_TR_VYS_OTV,
	E_TR_NOTO_NAKL,
	E_TR_SHIR_NAKL,
	E_VR_KOPR,
	E_VR_NOTO_NAKL,
	E_VR_SHIR_NAKL,

	E_DEF_VAL_RAST,
	E_DEF_VAL_SG,

	E_SK_KOTR,
	E_NP_KOTR,

	E_UZ_SILVES=300,
	E_UZ_VES_MOMX,
	E_UZ_VES_MOMY,
	E_UZ_SILX,
	E_UZ_SILY,
	E_UZ_SILZ,
	E_UZ_MOMX,
	E_UZ_MOMY,
	E_UZ_MOMZ,

	E_NAYZ = 501,
	E_KOYZ,

	E_GROUP_OSN = 1000,
	E_GROUP_ADDITIONAL,
	E_GROUP_ADD_NAGR,
	E_GROUP_GRUNT,
	E_GROUP_GLUB,
	E_GROUP_VIZA,
	E_GROUP_GRUNT_TYPE,

	E_GROUP_GEOM = 1020,
	E_GROUP_VESA = 1010,

	E_END_NODE = 2000,
	E_GROUP_IZD,
	E_GROUP_OTVIZ,
	E_GROUP_OTVSV,
	E_GROUP_OTVFL,
	E_GROUP_KO,
	E_GROUP_KU,
	E_GROUP_TR,
	E_GROUP_VREZKA,
	E_GROUP_MO,
	E_GROUP_SK,
	E_GROUP_NP,
	E_GROUP_UPR_OP,
	E_GROUP_PD_ZHESTK,
	E_GROUP_DEF_TYPE_RS,
	E_GROUP_DEF_TYPE_SG,
	E_GROUP_NAGR,
	E_GROUP_NAGR_VES_ADD,
	E_GROUP_NAGR_NONVES_ADD,
	E_GROUP_NAKL
};


class CPropValued
{
protected:
	CPipesSet set;
	CArmatSet seta;

	CStartPPDoc* m_pDoc;
	CPipeAndNode* m_pPnN;
	std::multimap<DWORD_PTR, float*> m_mapProp;
	std::multimap<DWORD_PTR, float> m_mapPropVal;
	bool bUpdatedByParent;

	static void ToFloat(wxVariant & val);

	static void ToStr(const wxVariant & val, CStringA& x);

	void ToFloat(const wxVariant & val, DWORD_PTR dwData);

	void ToStr(const wxVariant & val, DWORD_PTR dwData);

	static void ToFloat(const wxVariant & val, float& x);

public:
	CPropValued();

	//void OnPropertyGridChanged(wxPropertyGridEvent& event);

	virtual void RecalcXYZ();
	virtual void OnLBChanged();
	virtual void DoDataExchange(CDataExchange *pExchange, CPipeAndNode *pNode, CStartPPDoc *pDoc);

	void OnValueChanged(DWORD_PTR dwData, wxVariant &val, wxVariant &valNew, bool bButtons);

};


#endif //STARTPP_CPROPVALUED_H
