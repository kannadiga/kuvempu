#if !defined(AFX_CAUVERYHELP_H__D366C5D0_2DF4_463A_BFCB_04A2D4BBBC70__INCLUDED_)
#define AFX_CAUVERYHELP_H__D366C5D0_2DF4_463A_BFCB_04A2D4BBBC70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CauveryHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCauveryHelp dialog

class CCauveryHelp : public CDialog
{
// Construction
public:
	CCauveryHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCauveryHelp)
	enum { IDD = IDD_CAUVERY_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCauveryHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCauveryHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAUVERYHELP_H__D366C5D0_2DF4_463A_BFCB_04A2D4BBBC70__INCLUDED_)
