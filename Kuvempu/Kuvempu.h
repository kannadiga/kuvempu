// Kuvempu.h : main header file for the KUVEMPU application
//

#if !defined(AFX_KUVEMPU_H__B5905ACB_FCE3_4459_A30B_AAD1AEDBB9CC__INCLUDED_)
#define AFX_KUVEMPU_H__B5905ACB_FCE3_4459_A30B_AAD1AEDBB9CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKuvempuApp:
// See Kuvempu.cpp for the implementation of this class
//

class CKuvempuApp : public CWinApp
{
public:
	CKuvempuApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKuvempuApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKuvempuApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KUVEMPU_H__B5905ACB_FCE3_4459_A30B_AAD1AEDBB9CC__INCLUDED_)
