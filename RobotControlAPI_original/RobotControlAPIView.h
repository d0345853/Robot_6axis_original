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
#include "ImageProcess.h"
#include "Mysocket.h"

//thread address
#define WM_THREAD (WM_USER + 20)
//package mode
#define Line 0x01
#define Circle 0x02
#define P2P 0x03
#define manual_JOG_theta 0x04
#define manual_JOG_coordinate 0x05
#define Autohome 0x06
#define P2P_t 0x07
#define Orientation 0x08
#define Gripper 0x09
#define unlock 0x10
#define Brake 0x11
#define Resume 0x12
#define Pause 0x13

#define MOVE_A_UP 100
#define MOVE_A_DOWN 101
#define MOVE_B_UP 102
#define MOVE_B_DOWN 103
#define OpenGrip 104
#define CloseGrip 105
#define OpenGrip 106
#define GoHome 107


class CRobotControlAPIView : public CFormView
{
protected: // create from serialization only
	CRobotControlAPIView();
	DECLARE_DYNCREATE(CRobotControlAPIView)

public:
	//{{AFX_DATA(CRobotControlAPIView)
	enum { IDD = IDD_ROBOTCONTROLAPI_FORM };
	CButton	m_button_loadparameters;
	CListBox	m_list_position;
	CListBox	m_list_PRG;
	CListBox	m_list_execute;
	CListBox	m_system_status;
	CString		m_cmd;
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
	int		m_edit_estX;
	int		m_edit_estY;
	int		m_edit_estZ;
	double	m_edit_circlex;
	double	m_edit_circley;
	double	m_edit_rectanglex;
	double	m_edit_rectangley;
	double	m_edit_rectangletheta;
	//}}AFX_DATA

// Attributes
public:
	CRobotControlAPIDoc* GetDocument();
	CImageProcess *pImageprocess;

	CMysocket m_socket;

	int m_socket_send;

	int State;
	int ObjectType;
	int isDrop;

	char *Image_name;

	FILE *Fp1;
	FILE *Fp2;

	//------------------------------------------------

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
	CArray<int, int> pos_data[10];
	CArray<char, char> excute_buf;
	CArray<int, int> excute_cnt;
	//write txt
	FILE *fp;
	FILE *fp2;
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

	int pre_buffer;

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
	void Rotate_J6(int pulse);
	void ImageCatch();
	void BrakePackage(unsigned char brake);
	void UnlockPackage();
	void GripperPackage(unsigned char grip);
	void GetObject();
	void OrientationPackage(int time, int rotate[3], int vel);
	void AutohomePackage();
	void CirclePackage(int time, int pos[3][3], int rotate[3], int vel);
	void P2P_tPackage(int time, int theta[], int vel);
	void run_Robot_PRG(CString cmd);
	void P2PPackage(int time, int pos[3], int rotate[3], int vel);
	void LinePackage(int time, int pos[3], int rotate[3], int vel);
	void Manual_JOG_Coordinate_btn(int axis, BOOL turn);
	void manual_JOG_theta_btn(int joint, BOOL turn);
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
	afx_msg void OnBUTTONtestP1();
	afx_msg void OnBUTTONtestP2();
	afx_msg void OnBUTTONtestP3();
	afx_msg void OnBUTTONtestP4();
	afx_msg void OnBUTTONtestP5();
	afx_msg void OnBUTTONtestP6();
	afx_msg void OnBUTTONtestP7();
	afx_msg void OnButtonInitPosition();
	afx_msg void OnButtonInitHome();
	afx_msg void OnButtonGetCircle();
	afx_msg void OnButtonGetRectangle();
	afx_msg void OnBUTTONtestP13();
	afx_msg void OnButton_get_Image_object();
	afx_msg void OnBUTTONgetcircle();
	afx_msg void OnBUTTONgetrectangle();
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
