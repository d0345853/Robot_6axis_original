// RobotControlAPIView.h : interface of the CRobotControlAPIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROBOTCONTROLAPIVIEW_H__CDD6796E_A696_48EF_BF00_9858473DDA94__INCLUDED_)
#define AFX_ROBOTCONTROLAPIVIEW_H__CDD6796E_A696_48EF_BF00_9858473DDA94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Set_Comm_Port.h"
#include "Serial.h"
#include "fwd_inv_knmtcs.h"

//thread address
#define WM_THREAD (WM_USER + 20)
//package mode
#define Line 0x01
#define manual_JOG_theta 0x04
#define manual_JOG_coordinate 0x05

class CRobotControlAPIView : public CFormView
{
protected: // create from serialization only
	CRobotControlAPIView();
	DECLARE_DYNCREATE(CRobotControlAPIView)

public:
	//{{AFX_DATA(CRobotControlAPIView)
	enum { IDD = IDD_ROBOTCONTROLAPI_FORM };
	CListBox	m_list_PRG;
	CListBox	m_list_execute;
	CListBox	m_system_status;
	int		m_dtheta_unit;
	float		m_theta_J1;
	float		m_theta_J2;
	float		m_theta_J3;
	float		m_theta_J4;
	float		m_theta_J5;
	float		m_theta_J6;
	int		m_daxis_unit;
	float		m_axis_X;
	float		m_axis_Y;
	float		m_axis_Z;
	CString	m_cmd;
	int		m_waited_cmd_num;
	//}}AFX_DATA

// Attributes
public:
	CRobotControlAPIDoc* GetDocument();

	struct thread_struct
	{
		CWnd *wnd;
		bool isTerminate;
		HANDLE hThread;
	};


	//RS232
	CSerial m_Serial_DSP, m_Serial_D1, m_Serial_D2, m_Serial_D3, m_Serial_D4, m_Serial_D5, m_Serial_D6 ;
	//Second dialog
	CSet_Comm_Port m_port;
	//thread 
	thread_struct m_thread;
	//Robot language coding
	BOOL program_start;
	//dynamic memory array
	CArray<CString, CString> prog_code;
	CArray<double, double> pos_data[10];
	CArray<char, char> excute_buf;
	CArray<int, int> excute_cnt;
	//write txt
	FILE *fp;
	//listbox_cursel
	int status_cur;
	int prog_cur;
	int excute_cur;
	//Robot state
	BOOL isRobotMov; //True: robot is moving; False: robot is stop;
	//pulse
	int dpos[6]; //d pos
	int npos[6]; //now pos	
	//theta&coordinate
	float ntheta[6];
	float Ept[4][4];

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRobotControlAPIView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void LinePackage(int time, int pos[3], int rotate[3], int vel);
	void Manual_JOG_Coordinate_btn(int joint);
	void manual_JOG_theta_btn(int joint);
	void int2byte3(int src, unsigned char dst[3]);
	void int2byte2(int src , unsigned char dst[2]);
	void Update_HMI();
	static UINT DoThread(LPVOID pParam);
	afx_msg LRESULT OnThread(WPARAM wParam, LPARAM lParam);
	virtual ~CRobotControlAPIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRobotControlAPIView)
	afx_msg void OnButtonM1Rev();
	afx_msg void OnButtonM1Fwd();
	afx_msg void OnButtonInitDspDriverConnection();
	afx_msg void OnButtonM2Rev();
	afx_msg void OnButtonM2Fwd();
	afx_msg void OnButtonM3Rev();
	afx_msg void OnButtonM3Fwd();
	afx_msg void OnButtonM4Rev();
	afx_msg void OnButtonM4Fwd();
	afx_msg void OnButtonM5Rev();
	afx_msg void OnButtonM5Fwd();
	afx_msg void OnButtonM6Rev();
	afx_msg void OnButtonM6Fwd();
	afx_msg void OnChangeEdit6();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButtonXRev();
	afx_msg void OnChangeEditDaxis();
	afx_msg void OnButtonXFwd();
	afx_msg void OnButtonYRev();
	afx_msg void OnButtonYFwd();
	afx_msg void OnButtonZRev();
	afx_msg void OnButtonZFwd();
	afx_msg void OnButtonNewCmd();
	afx_msg void OnButtonRobotmoveManual();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RobotControlAPIView.cpp
inline CRobotControlAPIDoc* CRobotControlAPIView::GetDocument()
   { return (CRobotControlAPIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROBOTCONTROLAPIVIEW_H__CDD6796E_A696_48EF_BF00_9858473DDA94__INCLUDED_)
