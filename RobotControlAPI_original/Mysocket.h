#if !defined(AFX_MYSOCKET_H__1FEB5BA5_9ED7_401C_A462_C5A25F2B15E2__INCLUDED_)
#define AFX_MYSOCKET_H__1FEB5BA5_9ED7_401C_A462_C5A25F2B15E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mysocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CMysocket command target

class CMysocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CMysocket();
	virtual ~CMysocket();
	CString receive_data;
	int count;
	CString t;

	double m_socket_buffer[10000][4];
	int m_socket_flag;
// Overrides
public:
	void Senddata();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CMysocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSOCKET_H__1FEB5BA5_9ED7_401C_A462_C5A25F2B15E2__INCLUDED_)
