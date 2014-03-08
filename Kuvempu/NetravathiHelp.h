#if !defined(AFX_NETRAVATHIHELP_H__B452D48E_58C4_4A8B_81BC_EC524F9E6CB0__INCLUDED_)
#define AFX_NETRAVATHIHELP_H__B452D48E_58C4_4A8B_81BC_EC524F9E6CB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetravathiHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NetravathiHelp dialog

class NetravathiHelp : public CDialog
{
// Construction
public:
	NetravathiHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NetravathiHelp)
	enum { IDD = IDD_NETRAVATHI_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NetravathiHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NetravathiHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETRAVATHIHELP_H__B452D48E_58C4_4A8B_81BC_EC524F9E6CB0__INCLUDED_)
