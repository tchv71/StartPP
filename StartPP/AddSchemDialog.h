#ifndef CADDSCHEMDIALOG_H
#define CADDSCHEMDIALOG_H
#include "wxcrafter.h"

class CVecPnN;

class CAddSchemDlg : public CAddSchemBaseDialog
{
public:
    CAddSchemDlg(wxWindow* parent, CVecPnN& p, CVecPnN& pNew);
    virtual ~CAddSchemDlg();
	BOOL OnInitDialog();
	void EndModal(int retcode) override;
protected:
	CVecPnN& m_p;
	CVecPnN& m_pNew;

};
#endif // CADDSCHEMDIALOG_H
