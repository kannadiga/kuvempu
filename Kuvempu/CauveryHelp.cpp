// CauveryHelp.cpp : implementation file
//

#include "stdafx.h"
#include "Kuvempu.h"
#include "CauveryHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCauveryHelp dialog


CCauveryHelp::CCauveryHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CCauveryHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCauveryHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCauveryHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCauveryHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCauveryHelp, CDialog)
	//{{AFX_MSG_MAP(CCauveryHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCauveryHelp message handlers
