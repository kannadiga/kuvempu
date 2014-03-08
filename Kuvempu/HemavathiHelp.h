#if !defined(AFX_HEMAVATHIHELP_H__B3321A5F_D3B6_4776_A44C_2819FF3C87C5__INCLUDED_)
#define AFX_HEMAVATHIHELP_H__B3321A5F_D3B6_4776_A44C_2819FF3C87C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HemavathiHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// HemavathiHelp dialog

class HemavathiHelp : public CDialog
{
// Construction
public:
	HemavathiHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(HemavathiHelp)
	enum { IDD = IDD_HEMAVATHI_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HemavathiHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(HemavathiHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HEMAVATHIHELP_H__B3321A5F_D3B6_4776_A44C_2819FF3C87C5__INCLUDED_)
