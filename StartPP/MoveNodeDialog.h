#pragma once

#include "Pipe.h"
#include "wxcrafter.h"

// диалоговое окно CMoveNodeDialog

class CMoveNodeDialog : public CMoveNodeBaseDialog
{
public:
	CMoveNodeDialog(CWnd* pParent, CPipes& pipes); // стандартный конструктор
	virtual ~CMoveNodeDialog();

public:
	CPipes& m_pipes;
	//CStatic m_sNode;
	float m_nDist;
	BOOL OnInitDialog();
	bool OnOK();
	void EndModal(int retcode) wxOVERRIDE;
	
};

