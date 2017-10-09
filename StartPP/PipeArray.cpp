#include "stdafx.h"
#include "PipeArray.h"
#include "Rotate.h"
#include "PipeAndNode.h"
#include "Strings.h"


//-------------- Методы массива труб --------------------------------
Pipe dummy;

bool CPipeArray::HasIn(int NodeNum)
{
	return Ret.find(NodeNum) != Ret.end();
}


Pipe& CPipeArray::InFirst(int NodeNum, CPipeArrayContext& cnt)
{
	cnt.PntNum = NodeNum;
	cnt.Idx = 0;
	ret_iter it = Ret.find(NodeNum);
	return it == Ret.end() ? dummy : it->second->second;
}

bool CPipeArray::HasInNext(CPipeArrayContext cnt) const
{
	int c = int(Ret.count(cnt.PntNum));
	return cnt.Idx + 1 < c;
}

bool CPipeArray::HasIn(CPipeArrayContext cnt) const
{
	int c = int(Ret.count(cnt.PntNum));
	return cnt.Idx < c;
}

Pipe& CPipeArray::InNext(CPipeArrayContext& cnt)
{
	ret_iter it_ret = Ret.find(cnt.PntNum);
	cnt.Idx++;
	for (int i = 0; i < cnt.Idx; i++)
		++it_ret;
	return it_ret == Ret.end() ? dummy : it_ret->second->second;
}


bool CPipeArray::HasOut(int NodeNum)
{
	return pipes.find(NodeNum) != pipes.end();
}

Pipe& CPipeArray::OutFirst(int NodeNum, CPipeArrayContext& cnt)
{
	cnt.PntNum = NodeNum;
	cnt.Idx = 0;
	pipe_iter it = pipes.find(NodeNum);
	return it == pipes.end() ? dummy : it->second;
}

bool CPipeArray::HasOutNext(CPipeArrayContext cnt) const
{
	int c = int(pipes.count(cnt.PntNum));
	return cnt.Idx + 1 < c;
}

bool CPipeArray::HasOut(CPipeArrayContext cnt) const
{
	int c = int(pipes.count(cnt.PntNum));
	return cnt.Idx < c;
}

Pipe& CPipeArray::OutNext(CPipeArrayContext& cnt)
{
	cnt.Idx++;
	pipe_iter it = pipes.find(cnt.PntNum);
	for (int i = 0; i < cnt.Idx; i++)
		++it;
	return it == pipes.end() ? dummy : it->second;
}

void CPipeArray::Init()
{
	Pipe_types.clear();
	for (auto it = pipes.begin(); it != pipes.end(); ++it)
	{
		it->second.Seen = it->second.Drawed = false;
	}
}


void CPipeArray::FindNotDrawn(int& i, bool& Found)
{
	for (auto& x : pipes)
	{
		if (!x.second.Drawed)
		{
			i = x.second.StrP;
			Found = true;
			return;
		}
	}
	Found = false;
	i = -1;
}


//void  CPipeArray::SetLookMode(int NodeNum, TLookMode lm, CPipeArrayContext & cnt)
//{
//	cnt.PntNum=NodeNum;
//	cnt.LookMode=lm;
//	cnt.LookFirst=true;
//}


//bool CPipeArray::HasNext(CPipeArrayContext & cnt)
//{
//	if (cnt.LookFirst)
//		return (cnt.LookMode==LOOK_IN)?HasIn(cnt.PntNum):HasOut(cnt.PntNum);
//	else
//		return (cnt.LookMode==LOOK_IN)?HasInNext(cnt):HasOutNext(cnt);
//}


//Pipe &  CPipeArray::GetPipe(CPipeArrayContext & cnt)
//{
//	if (cnt.LookFirst) {
//		cnt.LookFirst=false;
//		return  (cnt.LookMode==LOOK_IN)?InFirst(cnt.PntNum,cnt):OutFirst(cnt.PntNum,cnt);
//	} else {
//		return  (cnt.LookMode==LOOK_IN)?InNext(cnt):OutNext(cnt);
//	}
//}
struct SFld_rec
{
	TNodeElement el;
	const wchar_t* Mnem;
} fields[] =
{
	{elMertOp,STR_MO},
	{elSkOp,STR_SK},
	{elNaprOp,STR_NP},
	{elCompOs,STR_KO},
	{elCompUg,STR_KU},
	{elArmat,STR_AR},
	{elOtvodS,STR_OS},
	{elOtvodI,STR_OI},
	{elOtvodF,STR_OF},
	{elRast,STR_RS},
	{elSg,STR_SG},
	{elGestPd,STR_PD},
	{elUprOp,STR_PR},
	{elTroinic,STR_TR},
	{elNone,nullptr}
};


void set_field(TNodeElement& dst, const wchar_t* src)
{
	SFld_rec* fld_rec;
	for (fld_rec = fields; fld_rec->Mnem; fld_rec++)
		if (wcscmp(fld_rec->Mnem, src) == 0)
		{
			dst = fld_rec->el;
			return;
		}
	dst = elNone;
}

void CPipeArray::copy_pipes(const std::vector<CPipeAndNode>& vec, const CRotator* Rot)
{
	//TTable *rst=tbl;
	int i,
	    //j,
	    //j1,
	    k;
	int Gr_sver, Gr_osn, Gr_sbok;
	float NAGZ;
	Pipe p;
	//Cur_pipe_type = 1;
	//CString bm=rst->Bookmark;

	//for (i = 0; i<MaxPipes;i++) {
	//	for (j = 0;j<=2;j++) {
	//		pipes[i][j].EndP=-1;
	//		Ret[i][j].StrP=-1;
	//	}
	//}
	pipes.clear();
	Ret.clear();
	Pipe_types.clear();
	// --------------- Копирование схемы в массив
	//if (cb) cb->Items->Clear();
	//rst->First();
	for (unsigned nIdx = 0; nIdx < vec.size(); nIdx++)
	{
		const CPipeAndNode* pPnN = &(vec[nIdx]);
		i = int(pPnN->m_NAYZ);
		k = int(pPnN->m_KOYZ);
		//p=&(pipes[i][j]);
		float dx = pPnN->m_OSIX;
		float dy = pPnN->m_OSIY;
		float dz = pPnN->m_OSIZ;
		if (Rot) Rot->Rotate(dx, dy, dz);
		p.StrP = i;
		p.EndP = k;
		p.dx = dx;
		p.dy = dy;
		p.dz = dz;
		p.Diam = pPnN->m_DIAM;
		p.R_Otv = pPnN->m_RAOT;

		set_field(p.MNEA, pPnN->m_MNEA);
		set_field(p.MNEO, pPnN->m_MNEO);
		set_field(p.TIDE, pPnN->m_TIDE);
		switch (p.MNEA)
		{
		case elCompOs:
		case elCompUg:
			p.R_Otv = pPnN->m_L_KOMP / 1000;
			break;
		case elNone: break;
		case elMertOp: break;
		case elSkOp: break;
		case elNaprOp: break;
		case elArmat: break;
		case elOtvodS: break;
		case elOtvodI: break;
		case elOtvodF: break;
		case elDiamChange: break;
		case elRast: break;
		case elSg: break;
		case elGestPd: break;
		case elUprOp: break;
		case elSelect: break;
		case elTroinic: break;
		default: break;
		}

		p.Drawed = false;
		p.Seen = false;
		p.NaprStr = p.NaprEnd = 0;
		p.NaprDop = 20;
		float n = pPnN->m_NAGV;
		if (n < 0)
		{
			p.VIZA = pPnN->m_VIZA;
			p.VIZA2 = pPnN->m_VIZA2;
			p.Podzem = true;
		}
		else
			p.Podzem = false;
		p.Podush = false;
		p.INDX = int(pPnN->m_INDX);
		if (p.Podzem)
		{
			NAGZ = pPnN->m_NAGZ;
			Gr_osn = int(NAGZ / 1000);
			Gr_sver = int((NAGZ - Gr_osn * 1000) / 10);
			Gr_sbok = int((NAGZ - Gr_osn * 1000 - Gr_sver * 10) * 10 + 0.5);
			if (Gr_sbok == 6 || Gr_sbok == 7) p.Podush = true;
		}
		p.P_type = Set_pipe_type(pPnN);
		p.m_pPnN = const_cast<CPipeAndNode*>(pPnN);
		pipe_iter it = pipes.insert(pipe_pair(i, p));

		Ret.insert(ret_pair(k, it));
		//for (j1 = 0;Ret[k][j1].StrP >= 0;j1++) ;
		//Ret[k][j1].StrP = i;
		//Ret[k][j1].Idx = j;
	};
	//rst->Bookmark=bm;
	//TTable *Napr=new TTable(nullptr);
	//Napr->DatabaseName=rst->DatabaseName;
	//Napr->TableName=GetPartialName(rst->TableName)+"na.dbf";
	//if (Napr->Exists) {
	//	Napr->Open();
	//	Napr->First();
	//	while (!Napr->Eof) {
	//		if (Napr->FieldValues["YZN"]!=0 && Napr->FieldValues["YZK"] ==0) {
	//		} else {
	//			int i=Napr->FieldValues["YZN"];
	//			for (k=0;k<=2;k++) 
	//				if (pipes[i][k].EndP==Napr->FieldValues["YZK"]) {
	//					pipes[i][k].NaprStr=Napr->FieldValues["RA2"];
	//					pipes[i][k].NaprDop=Napr->FieldValues["DO2"];
	//					Napr->Next();
	//					pipes[i][k].NaprEnd=Napr->FieldValues["RA2"];
	//					break;
	//				}
	//		}
	//		Napr->Next();
	//	}
	//	Napr->Close();
	//}
	//delete Napr;
};

void CPipeArray::Rotate(CRotator* Rot)
{
	//Pipe *p;
	//for (int i=0;i<MaxPipes;i++)
	//	for (int j=0;j<3;j++) {
	//		p=&(pipes[i][j]);
	//		if (p->EndP>=0)
	//			Rot->Rotate(p->dx,p->dy,p->dz);
	//	}
	for (auto it = pipes.begin(); it != pipes.end(); ++it)
		Rot->Rotate(it->second.dx, it->second.dy, it->second.dz);
}

void CPipeArray::copy_pipes_1(CPipeArray* PipeArray, CRotator* Rot_1)
{
	*this = *PipeArray;
	//Pipe *p;
	//for (int i=0;i<MaxPipes;i++)
	//	for (int j=0;j<3;j++) {
	//		p=&(pipes[i][j]);
	//		if (p->EndP>=0)
	//			Rot_1->Rotate_1(p->dx,p->dy,p->dz);
	//	}
	Ret.clear();
	for (auto it = pipes.begin(); it != pipes.end(); ++it)
	{
		Rot_1->Rotate_1(it->second.dx, it->second.dy, it->second.dz);
		Ret.insert(ret_pair(it->second.EndP, it));
	}
}

const float eps = 0.001f;


bool CPipeArray::Pipe_check(const CPipeAndNode* pPnN, int i)
{
	bool Ok;
	const Pipe_type& pt = Pipe_types[i];
	float fDIAM = pPnN->m_DIAM;
	CString aNAMA = CString(pPnN->m_NAMA);

	Ok = (fabs(fDIAM - pt.Diam) < eps) &&
		(aNAMA == pt.NAMA) &&
		(fabs(pPnN->m_NTOS - pt.NTOS) < eps) &&
		(fabs(pPnN->m_VETR - pt.VETR) < eps) &&
		(fabs(pPnN->m_RATE - pt.RATE) < eps) &&
		(fabs(pPnN->m_RADA - pt.rada) < eps) &&
		(fabs(pPnN->m_VEPR - pt.VEPR) < eps) &&
		(fabs(pPnN->m_VEIZ - pt.VEIZ) < eps);
	float n = pPnN->m_NAGV;
	Ok = Ok && ((n < 0) == pt.Podzem);
	return Ok;
};

int CPipeArray::Set_pipe_type(const CPipeAndNode* pPnN)
{
	if (fabs(pPnN->m_NAYZ) < 1e-6f) return 0;
	for (unsigned i = 0; i < Pipe_types.size(); i++)
		if (Pipe_check(pPnN, i)) return i;
	// Не найдено трубы данного типа
	{
		Pipe_type p;
		Pipe_type* pt = &p;
		pt->Diam = pPnN->m_DIAM;
		pt->NAMA = pPnN->m_NAMA;
		pt->NTOS = pPnN->m_NTOS;
		pt->VETR = pPnN->m_VETR;
		pt->VEIZ = pPnN->m_VEIZ;
		pt->VEPR = pPnN->m_VEPR;
		pt->RATE = pPnN->m_RATE;
		pt->rada = pPnN->m_RADA;
		float n = pPnN->m_NAGV;
		pt->Podzem = (n < 0);
		Pipe_types.push_back(p);
		return int(Pipe_types.size()) - 1;
	}
}


bool CPipeArray::CheckConnectivity()
{
	Init();
	if (pipes.empty())
		return true;
	Scan(pipes.begin()->first);
	bool bFound;
	int i;
	FindNotDrawn(i, bFound);
	return !bFound;
}


void CPipeArray::Scan(int nStartP)
{
	CPipeArrayContext cnt;
	for (Pipe* p = &OutFirst(nStartP, cnt); HasOut(cnt);)
	{
		if (!p->Drawed)
		{
			p->Drawed = true;
			if (InCount(nStartP) <= 1 && OutCount(nStartP) <= 1)
			{
				p = &OutFirst(p->EndP, cnt);
				nStartP = p->EndP;
				continue;
			}
			Scan(p->EndP);
		}
		p = &OutNext(cnt);
	}
	for (Pipe* p = &InFirst(nStartP, cnt); HasIn(cnt);)
	{
		if (p->Drawed)
		{
			p->Drawed = true;
			if (InCount(nStartP) <= 1 && OutCount(p->StrP) <= 1)
			{
				p = &InFirst(p->StrP, cnt);
				nStartP = p->StrP;
				continue;
			}
			Scan(p->StrP);
		}
		p = &InNext(cnt);
	}
}

