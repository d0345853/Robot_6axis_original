#if !defined(AFX_SET_COMM_PORT_H__FF907A02_15F8_4E93_B881_22AAC8A3BB77__INCLUDED_)
#define AFX_SET_COMM_PORT_H__FF907A02_15F8_4E93_B881_22AAC8A3BB77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set_Comm_Port.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSet_Comm_Port dialog

class CSet_Comm_Port : public CDialog
{
// Construction
public:
	CSet_Comm_Port(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSet_Comm_Port)
	enum { IDD = IDD_DIALOG_SET_COMM_PORT };
	int		m_DSP_Comm_Port;
	int		m_D1_Comm_Port;
	int		m_D2_Comm_Port;
	int		m_D3_Comm_Port;
	int		m_D4_Comm_Port;
	int		m_D5_Comm_Port;
	int		m_D6_Comm_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSet_Comm_Port)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSet_Comm_Port)
	afx_msg void OnChangeEditCommDsp();
	afx_msg void OnChangeEditCommD1();
	afx_msg void OnChangeEditCommD2();
	afx_msg void OnChangeEditCommD3();
	afx_msg void OnChangeEditCommD4();
	afx_msg void OnChangeEditCommD5();
	afx_msg void OnChangeEditCommD6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_COMM_PORT_H__FF907A02_15F8_4E93_B881_22AAC8A3BB77__INCLUDED_)
