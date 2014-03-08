// HemavathiHelp.cpp : implementation file
//

#include "stdafx.h"
#include "Kuvempu.h"
#include "HemavathiHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HemavathiHelp dialog


HemavathiHelp::HemavathiHelp(CWnd* pParent /*=NULL*/)
	: CDialog(HemavathiHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(HemavathiHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void HemavathiHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HemavathiHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HemavathiHelp, CDialog)
	//{{AFX_MSG_MAP(HemavathiHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HemavathiHelp message handlers
