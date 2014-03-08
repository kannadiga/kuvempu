#if !defined(AFX_SHARAVATHIHELP_H__9B0BEC30_BACD_479F_9D07_1B1C297E81EE__INCLUDED_)
#define AFX_SHARAVATHIHELP_H__9B0BEC30_BACD_479F_9D07_1B1C297E81EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SharavathiHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SharavathiHelp dialog

class SharavathiHelp : public CDialog
{
// Construction
public:
	SharavathiHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SharavathiHelp)
	enum { IDD = IDD_SHARAVATHI_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SharavathiHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SharavathiHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHARAVATHIHELP_H__9B0BEC30_BACD_479F_9D07_1B1C297E81EE__INCLUDED_)
