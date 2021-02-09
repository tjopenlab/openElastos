#if !defined(AFX_SURE_H__A7AD9367_2724_4A40_B6CD_B5177B6333AF__INCLUDED_)
#define AFX_SURE_H__A7AD9367_2724_4A40_B6CD_B5177B6333AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sure.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSure dialog

class CSure : public CDialog
{
// Construction
public:
	CSure(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSure)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSure)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSure)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SURE_H__A7AD9367_2724_4A40_B6CD_B5177B6333AF__INCLUDED_)
