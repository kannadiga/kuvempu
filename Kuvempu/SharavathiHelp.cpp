// SharavathiHelp.cpp : implementation file
//

#include "stdafx.h"
#include "Kuvempu.h"
#include "SharavathiHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SharavathiHelp dialog


SharavathiHelp::SharavathiHelp(CWnd* pParent /*=NULL*/)
	: CDialog(SharavathiHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(SharavathiHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SharavathiHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SharavathiHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SharavathiHelp, CDialog)
	//{{AFX_MSG_MAP(SharavathiHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SharavathiHelp message handlers
