// AlreadyExist.cpp : implementation file
//

#include "stdafx.h"
#include "Kuvempu.h"
#include "AlreadyExist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AlreadyExist dialog


AlreadyExist::AlreadyExist(CWnd* pParent /*=NULL*/)
	: CDialog(AlreadyExist::IDD, pParent)
{
	//{{AFX_DATA_INIT(AlreadyExist)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AlreadyExist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AlreadyExist)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AlreadyExist, CDialog)
	//{{AFX_MSG_MAP(AlreadyExist)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlreadyExist message handlers
