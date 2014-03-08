// Text_Converter.h : main header file for the TEXT_CONVERTER application
//

#if !defined(AFX_TEXT_CONVERTER_H__ECE6DBA5_BF36_11D6_94AD_9EB339936A45__INCLUDED_)
#define AFX_TEXT_CONVERTER_H__ECE6DBA5_BF36_11D6_94AD_9EB339936A45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CText_ConverterApp:
// See Text_Converter.cpp for the implementation of this class
//

class CText_ConverterApp : public CWinApp
{
public:
	CText_ConverterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CText_ConverterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CText_ConverterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXT_CONVERTER_H__ECE6DBA5_BF36_11D6_94AD_9EB339936A45__INCLUDED_)
