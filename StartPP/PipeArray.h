#pragma once
#include <vector>
#include <map>

//enum TLookMode {LOOK_IN,LOOK_OUT};
enum TNodeElement
{
	elNone,
	elMertOp,
	elSkOp,
	elNaprOp,
	elCompOs,
	elCompUg,
	elArmat,
	elOtvodS,
	elOtvodI,
	elOtvodF,
	elDiamChange,
	elRast,
	elSg,
	elGestPd,
	elUprOp,
	elSelect,
	elTroinic
};

class CPipeAndNode;

// Единичный участок схемы
struct Pipe
{
	int StrP;
	int EndP; // Номер конечной точки участка (-1 - участок отсутствует)
	float dx, dy, dz; // Геометрич. размеры
	float Diam; // Диаметр в мм
	float VIZA; // Высота засыпки в м
	float VIZA2;
	float R_Otv; // Радиус отвода, м или длина компенсатора (ос. и угл.)

	TNodeElement MNEA; // Изделия
	TNodeElement MNEO; // Опоры
	TNodeElement TIDE; // Деформации

	bool Drawed, // Флаги просмотра и отрисовки для
	     Seen, // исключения циклов

	     Podzem, // Подземный ли участок
	     Podush; // Имеются ли подушки
	int P_type; // Тип трубы
	int INDX;
	//int i, j;
	float NaprStr, NaprEnd, NaprDop;
	CPipeAndNode* m_pPnN;
	Pipe() : StrP(0), EndP(0), dx(0), dy(0), dz(0), VIZA(0), VIZA2(0), R_Otv(0), MNEA(elNone), MNEO(elNone), TIDE(elNone),
	         Drawed(false), Seen(false), Podzem(false), Podush(false), P_type(0), INDX(0), NaprStr(0), NaprEnd(0), NaprDop(0),
	         m_pPnN(nullptr)
	{}
};

// Копия схемы в памяти

struct Pipe_type
{
public:
	Pipe_type() : Diam(0), NTOS(0), VETR(0), VEIZ(0), VEPR(0), RATE(0), rada(0), Podzem(false) {}
	float Diam;
	CString NAMA;
	float NTOS;
	float VETR;
	float VEIZ;
	float VEPR;
	float RATE;
	float rada;
	bool Podzem;
}; // Параметры для различных типов труб


class CPipeAndNode;
class CRotator;

typedef std::multimap<int, Pipe>::iterator pipe_iter;
typedef std::multimap<int, Pipe>::value_type pipe_pair;
typedef std::multimap<int, pipe_iter>::iterator ret_iter;
typedef std::multimap<int, pipe_iter>::value_type ret_pair;

class CPipeArrayContext
{
public:
	CPipeArrayContext(): PntNum(0),Idx(0) {}
	//TLookMode LookMode;
	//bool LookFirst;
	int PntNum;
	int Idx;
	//int PntSucNum;
	//int RetPntNum;
	//int RetPntSucNum;
	//pipe_iter it_pipe;
	//ret_iter it_ret;
};

typedef struct
{
	int StrP, EndP;
	int x1, y1, x2, y2;
	float dx, dy, dz;
	float Diam;
} Interval_;

class CPipeArray
{
private:
	std::multimap<int, Pipe> pipes;
	// Обратные ссылки на участки - по номеру конечной точки дает начальную точку
	// Участок для обратной ссылки
	// (чтобы определить участки, входящие в данный узел)
	std::multimap<int, pipe_iter> Ret;

public:
	// Тип трубы (общие параметры)
	// Массив типов труб
	std::vector<Interval_> Intervals;
	std::vector<Pipe_type> Pipe_types;
	//int Cur_pipe_type;
	void Rotate(CRotator* Rot);
	bool Pipe_check(const CPipeAndNode* pPnN, int i);
	int Set_pipe_type(const CPipeAndNode* pPnN);
	void copy_pipes(const std::vector<CPipeAndNode>& vec, const CRotator* Rot = nullptr);
	void copy_pipes_1(CPipeArray* PipeArray, CRotator* Rot);

	CPipeArray()
	{
	};

	CPipeArray(CPipeArray* PipeArray, CRotator* Rot)
	{
		*this = *PipeArray;
		Rotate(Rot);
	}

	CPipeArray(const std::vector<CPipeAndNode>& vec)
	{
		copy_pipes(vec);
	}

	inline int OutCount(int NodeNum)
	{
		return int(pipes.count(NodeNum));
	}

	bool HasOut(int NodeNum);
	bool HasOut(CPipeArrayContext cnt) const;
	bool HasOutNext(CPipeArrayContext cnt) const;
	Pipe& OutFirst(int NodeNum, CPipeArrayContext& cnt);
	Pipe& OutNext(CPipeArrayContext& cnt);

	inline int InCount(int NodeNum)
	{
		return int(Ret.count(NodeNum));
	}

	bool HasIn(int NodeNum);
	bool HasIn(CPipeArrayContext cnt) const;
	bool HasInNext(CPipeArrayContext cnt) const;
	Pipe& InFirst(int NodeNum, CPipeArrayContext& cnt);
	Pipe& InNext(CPipeArrayContext& cnt);

	void Init();
	void FindNotDrawn(int& i, bool& Found);
	//void  SetLookMode(int NodeNum, TLookMode lm, CPipeArrayContext & cnt);
	//bool HasNext(CPipeArrayContext & cnt);
	//Pipe &  GetPipe(CPipeArrayContext & cnt);
	bool CheckConnectivity(void);
	void Scan(int nStartP);

	std::multimap<int, Pipe>& GetPipes()
	{
		return pipes;
	}
};

