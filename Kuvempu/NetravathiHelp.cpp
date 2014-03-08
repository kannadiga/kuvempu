// NetravathiHelp.cpp : implementation file
//

#include "stdafx.h"
#include "Kuvempu.h"
#include "NetravathiHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NetravathiHelp dialog


NetravathiHelp::NetravathiHelp(CWnd* pParent /*=NULL*/)
	: CDialog(NetravathiHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(NetravathiHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void NetravathiHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NetravathiHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NetravathiHelp, CDialog)
	//{{AFX_MSG_MAP(NetravathiHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NetravathiHelp message handlers
