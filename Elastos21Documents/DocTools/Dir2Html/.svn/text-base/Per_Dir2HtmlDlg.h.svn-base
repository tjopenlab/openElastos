// Per_Dir2HtmlDlg.h : header file
//

#if !defined(AFX_PER_DIR2HTMLDLG_H__77D39776_00F7_4045_B273_4F1536230346__INCLUDED_)
#define AFX_PER_DIR2HTMLDLG_H__77D39776_00F7_4045_B273_4F1536230346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPer_Dir2HtmlDlg dialog

class CPer_Dir2HtmlDlg : public CDialog
{
// Construction
public:
	CPer_Dir2HtmlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPer_Dir2HtmlDlg)
	enum { IDD = IDD_PER_DIR2HTML_DIALOG };
	CString	m_path;
	CString	m_selectname;
	int		m_deep;
	BOOL	m_check;
	CString	m_name;
	int		m_type;
	int		m_deldeep;
	CString	m_delname;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPer_Dir2HtmlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPer_Dir2HtmlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreate();
	afx_msg void OnSee();
	afx_msg void OnAbout();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PER_DIR2HTMLDLG_H__77D39776_00F7_4045_B273_4F1536230346__INCLUDED_)
