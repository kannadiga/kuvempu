// KuvempuDlg.h : header file
//

#if !defined(AFX_KUVEMPUDLG_H__3962F62B_2BB1_4975_8214_4F82FEF653B9__INCLUDED_)
#define AFX_KUVEMPUDLG_H__3962F62B_2BB1_4975_8214_4F82FEF653B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BmpButton.h"
#include "systemtray.h"
/////////////////////////////////////////////////////////////////////////////
// CKuvempuDlg dialog

class CKuvempuDlg : public CDialog
{

	// Construction
public:
	CKuvempuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKuvempuDlg)
	enum { IDD = IDD_KUVEMPU_DIALOG };

	CBmpButton	m_ButtonNetravathi;
	CBmpButton	m_ButtonSharavathi;
	CBmpButton	m_ButtonCauvery;
	CBmpButton	m_ButtonHemavathi;

//	CBmpButton	m_ButtonSystemTray;
	CBmpButton	m_ButtonConverter;

	CBmpButton	m_ButtonClose;

	CButton m_CheckNetravathi;
//	CBmpButton	m_exitButton;
//	CBmpButton	m_dateButton;

//	CFont m_fntTitle;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKuvempuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    HRGN BitmapRegion(HBITMAP hBitmap,COLORREF cTransparentColor=RGB(0,0,0),
						BOOL bIsTransparent=TRUE);
	// Generated message map functions
	//{{AFX_MSG(CKuvempuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnSetFont 	(WPARAM wParam, LPARAM lParam);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCancelMode();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnAbout();
	afx_msg void OnHelp_Kuvempu();
	afx_msg void OnHemavathi();
	afx_msg void OnSharavathi();
	afx_msg void OnNetravathi();
	afx_msg void OnCauvery();
	afx_msg void OnConverter();
	afx_msg void OnClose();
	afx_msg void OnOpen();
	afx_msg void OnKuvempu_Kannada();
	afx_msg void OnSetToTray();
	afx_msg void ResteButton();
	afx_msg void CheckForInstance();
	afx_msg void OnHemavathiHelp();
	afx_msg void OnButton2();
	afx_msg void OnNetravathiHelp();
	afx_msg void OnCauveryHelp();
	afx_msg void OnSharavathiHelp();
	//}}AFX_MSG

	afx_msg LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);

	afx_msg void OnUPdateHemavathi(CCmdUI*);
	afx_msg void OnUPdateSharavathi(CCmdUI*);
	afx_msg void OnUPdateNetravathi(CCmdUI*);
	afx_msg void OnUPdateCauvery(CCmdUI*);
	afx_msg void SetToolTip(CString);
	afx_msg void Set_To_Tray();

public :
	CSystemTray	m_TrayIcon;
	CString		m_strStatus;
	CString ToolTip ;
	int Set_Tray ;
private :
	HICON		m_Icon;
	afx_msg void OnUpdateCheck(CCmdUI*);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KUVEMPUDLG_H__3962F62B_2BB1_4975_8214_4F82FEF653B9__INCLUDED_)
