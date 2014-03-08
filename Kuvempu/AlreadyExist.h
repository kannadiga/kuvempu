#if !defined(AFX_ALREADYEXIST_H__9A2260F7_62E4_4894_B31F_AAD30F6F6EDA__INCLUDED_)
#define AFX_ALREADYEXIST_H__9A2260F7_62E4_4894_B31F_AAD30F6F6EDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlreadyExist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AlreadyExist dialog

class AlreadyExist : public CDialog
{
// Construction
public:
	AlreadyExist(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AlreadyExist)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlreadyExist)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AlreadyExist)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALREADYEXIST_H__9A2260F7_62E4_4894_B31F_AAD30F6F6EDA__INCLUDED_)
