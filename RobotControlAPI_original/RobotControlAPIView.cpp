// RobotControlAPIView.cpp : implementation of the CRobotControlAPIView class
//

#include "stdafx.h"
#include "RobotControlAPI.h"

#include "RobotControlAPIDoc.h"
#include "RobotControlAPIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIView

IMPLEMENT_DYNCREATE(CRobotControlAPIView, CFormView)

BEGIN_MESSAGE_MAP(CRobotControlAPIView, CFormView)
	//{{AFX_MSG_MAP(CRobotControlAPIView)
	ON_BN_CLICKED(IDC_BUTTON_M1_REV, OnButtonM1Rev)
	ON_BN_CLICKED(IDC_BUTTON_M1_FWD, OnButtonM1Fwd)
	ON_BN_CLICKED(IDC_BUTTON_INIT_DSP_DRIVER_CONNECTION, OnButtonInitDspDriverConnection)
	ON_BN_CLICKED(IDC_BUTTON_M2_REV, OnButtonM2Rev)
	ON_BN_CLICKED(IDC_BUTTON_M2_FWD, OnButtonM2Fwd)
	ON_BN_CLICKED(IDC_BUTTON_M3_REV, OnButtonM3Rev)
	ON_BN_CLICKED(IDC_BUTTON_M3_FWD, OnButtonM3Fwd)
	ON_BN_CLICKED(IDC_BUTTON_M4_REV, OnButtonM4Rev)
	ON_BN_CLICKED(IDC_BUTTON_M4_FWD, OnButtonM4Fwd)
	ON_BN_CLICKED(IDC_BUTTON_M5_REV, OnButtonM5Rev)
	ON_BN_CLICKED(IDC_BUTTON_M5_FWD, OnButtonM5Fwd)
	ON_BN_CLICKED(IDC_BUTTON_M6_REV, OnButtonM6Rev)
	ON_BN_CLICKED(IDC_BUTTON_M6_FWD, OnButtonM6Fwd)
	ON_EN_CHANGE(IDC_EDIT6, OnChangeEdit6)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_X_REV, OnButtonXRev)
	ON_EN_CHANGE(IDC_EDIT_DAXIS, OnChangeEditDaxis)
	ON_BN_CLICKED(IDC_BUTTON_X_FWD, OnButtonXFwd)
	ON_BN_CLICKED(IDC_BUTTON_Y_REV, OnButtonYRev)
	ON_BN_CLICKED(IDC_BUTTON_Y_FWD, OnButtonYFwd)
	ON_BN_CLICKED(IDC_BUTTON_Z_REV, OnButtonZRev)
	ON_BN_CLICKED(IDC_BUTTON_Z_FWD, OnButtonZFwd)
	ON_BN_CLICKED(IDC_BUTTON_NEW_CMD, OnButtonNewCmd)
	ON_BN_CLICKED(IDC_BUTTON_ROBOTMOVE_MANUAL, OnButtonRobotmoveManual)
	ON_BN_CLICKED(IDC_BUTTON_test_P1, OnBUTTONtestP1)
	ON_BN_CLICKED(IDC_BUTTON_test_P2, OnBUTTONtestP2)
	ON_BN_CLICKED(IDC_BUTTON_test_P3, OnBUTTONtestP3)
	ON_BN_CLICKED(IDC_BUTTON_test_P4, OnBUTTONtestP4)
	ON_BN_CLICKED(IDC_BUTTON_test_P5, OnBUTTONtestP5)
	ON_BN_CLICKED(IDC_BUTTON_test_P6, OnBUTTONtestP6)
	ON_BN_CLICKED(IDC_BUTTON_test_P7, OnBUTTONtestP7)
	ON_BN_CLICKED(IDC_BUTTON25, OnButtonInitPosition)
	ON_BN_CLICKED(IDC_BUTTON26, OnButtonInitHome)
	ON_BN_CLICKED(IDC_BUTTON31, OnButtonGetCircle)
	ON_BN_CLICKED(IDC_BUTTON32, OnButtonGetRectangle)
	ON_BN_CLICKED(IDC_BUTTON_test_P13, OnBUTTONtestP13)
	ON_BN_CLICKED(IDC_BUTTON36, OnButton_get_Image_object)
	ON_BN_CLICKED(IDC_BUTTON_get_circle, OnBUTTONgetcircle)
	ON_BN_CLICKED(IDC_BUTTON_get_rectangle, OnBUTTONgetrectangle)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_MESSAGE(WM_THREAD, OnThread)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIView construction/destruction

CRobotControlAPIView::CRobotControlAPIView()
	: CFormView(CRobotControlAPIView::IDD)
{
	//{{AFX_DATA_INIT(CRobotControlAPIView)
	m_cmd = _T("");
	m_dtheta_unit = 0;
	m_theta_J1 = 0.0;
	m_theta_J2 = 0.0;
	m_theta_J3 = 0.0;
	m_theta_J4 = 0.0;
	m_theta_J5 = 0.0;
	m_theta_J6 = 0.0;
	m_daxis_unit = 100;
	m_axis_X = 0.0;
	m_axis_Y = 0.0;
	m_axis_Z = 0.0;
	m_edit_estX = 0;
	m_edit_estY = 0;
	m_edit_estZ = 0;
	m_edit_circlex = 0.0;
	m_edit_circley = 0.0;
	m_edit_rectanglex = 0.0;
	m_edit_rectangley = 0.0;
	m_edit_rectangletheta = 0.0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

	pImageprocess = new CImageProcess;
	State = 0;
	ObjectType = 0;
	
	isDrop = false;

	//Image_name = "Picture.jpg";

}

CRobotControlAPIView::~CRobotControlAPIView()
{
	delete pImageprocess;
	m_thread.isTerminate = true;
	m_Serial_DSP.Close();
	m_Serial_D1.Close();
	m_Serial_D2.Close();
	m_Serial_D3.Close();
	m_Serial_D4.Close();
	m_Serial_D5.Close();
	m_Serial_D6.Close();
}

void CRobotControlAPIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRobotControlAPIView)
	DDX_Control(pDX, IDC_LIST_POSITION, m_list_position);
	DDX_Control(pDX, IDC_LIST_PRG, m_list_PRG);
	DDX_Control(pDX, IDC_LIST_EXECUTE, m_list_execute);
	DDX_Control(pDX, IDC_LIST_STATUS, m_system_status);
	DDX_Text(pDX, IDC_EDIT_NEW_CMD, m_cmd);
	DDX_Text(pDX, IDC_EDIT6, m_dtheta_unit);
	DDX_Text(pDX, IDC_EDIT7, m_theta_J1);
	DDX_Text(pDX, IDC_EDIT8, m_theta_J2);
	DDX_Text(pDX, IDC_EDIT9, m_theta_J3);
	DDX_Text(pDX, IDC_EDIT10, m_theta_J4);
	DDX_Text(pDX, IDC_EDIT11, m_theta_J5);
	DDX_Text(pDX, IDC_EDIT12, m_theta_J6);
	DDX_Text(pDX, IDC_EDIT_DAXIS, m_daxis_unit);
	DDX_Text(pDX, IDC_EDIT_X_AXIS, m_axis_X);
	DDX_Text(pDX, IDC_EDIT_Y_AXIS, m_axis_Y);
	DDX_Text(pDX, IDC_EDIT_Z_AXIS, m_axis_Z);
	DDX_Text(pDX, IDC_EDIT19, m_edit_estX);
	DDX_Text(pDX, IDC_EDIT20, m_edit_estY);
	DDX_Text(pDX, IDC_EDIT21, m_edit_estZ);
	DDX_Text(pDX, IDC_EDIT22, m_edit_circlex);
	DDX_Text(pDX, IDC_EDIT23, m_edit_circley);
	DDX_Text(pDX, IDC_EDIT24, m_edit_rectanglex);
	DDX_Text(pDX, IDC_EDIT25, m_edit_rectangley);
	DDX_Text(pDX, IDC_EDIT26, m_edit_rectangletheta);
	//}}AFX_DATA_MAP
}

BOOL CRobotControlAPIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CRobotControlAPIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
//second dialog
	m_port.DoModal();
//begin thread
	m_thread.isTerminate = false;
	m_thread.wnd = this;
 	m_thread.hThread = CreateEvent( 0, 1, 0, "MyEvent");
	AfxBeginThread(DoThread,(LPVOID) this);
//robot language is not using
	program_start=0;
//timer: show waited cmd
	SetTimer(1,500, NULL);
//Robot state
	isRobotMov = FALSE;
//npos initial
	for(int i=0; i<6; i++) npos[i]=0;
//initial cursor
	status_cur = 0;
	prog_cur = 0;
	excute_cur = 0;

	pre_buffer=0;

	m_socket.Create(8081, SOCK_DGRAM);
	SetTimer(200, 100, NULL);

	m_socket_send=0;

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIView printing

BOOL CRobotControlAPIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRobotControlAPIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRobotControlAPIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CRobotControlAPIView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIView diagnostics

#ifdef _DEBUG
void CRobotControlAPIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRobotControlAPIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CRobotControlAPIDoc* CRobotControlAPIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRobotControlAPIDoc)));
	return (CRobotControlAPIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIView message handlers

UINT CRobotControlAPIView::DoThread(LPVOID pParam)
{
	CRobotControlAPIView *pthis = (CRobotControlAPIView *)pParam;
	CWnd *wnd = pthis->m_thread.wnd;
	
	int ptr=0;
	unsigned char rec_data[1000];
	char send_cmd[128];
	int length;

	while(!pthis->m_thread.isTerminate)
	{
		//Receive
		ptr=0;
		while( pthis->m_Serial_DSP.ReadDataWaiting()>0 )
		{
			pthis->m_Serial_DSP.ReadData(&rec_data[ptr],1);
			//Alarm?
 			if(rec_data[ptr]==251 || rec_data[ptr]==252 || rec_data[ptr]==253)
			{
				CString alarm;
				alarm.Format("Alarm Occured! %d",rec_data[ptr]);
				pthis->m_system_status.InsertString(-1,alarm);
				pthis->m_system_status.SetCurSel(pthis->status_cur);
				pthis->status_cur++;

				pthis->m_thread.isTerminate=true;
				pthis->m_Serial_DSP.Close();
 			}

			ptr++;
			if(ptr==20 && rec_data[0]==0xff && rec_data[19]==0xfe)
			{
				/* dpos package ///////////////////////
					0xff		theta1~6		 0xfe
					 0	 123 456 789 012 345 678  9  
				*/ ////////////////////////////////////
				for(int i=1; i<=16; i=i+3)
				{
					pthis->dpos[i/3]=(rec_data[i])*250*250 + (rec_data[i+1])*250 + rec_data[i+2]; //7'6543210
				}
				//Update 
				//pthis->Update_HMI();
				//return LPVOID pParam (pthis)
				wnd->PostMessage(WM_THREAD, 1, 0);
				//Set Robot is stopping state
				pthis->isRobotMov = FALSE;
				//Set to 0
				ptr=0;
			}
		}

		//Send a new command to robot
		if(pthis->isRobotMov == FALSE)
		{
			//Fetch form excute buffer and send command to DSP
			if(pthis->excute_cnt.GetSize()>0)
			{
				length = pthis->excute_cnt.GetAt(0);
				pthis->excute_cnt.RemoveAt(0);
				for(int i=0; i<length; i++)
				{
					send_cmd[i]=pthis->excute_buf.GetAt(0);
					pthis->excute_buf.RemoveAt(0);
				}
				pthis->m_Serial_DSP.SendData(send_cmd,length);
				pthis->isRobotMov = TRUE;
			}
		}

		//return LPVOID pParam (pthis)
		//wnd->PostMessage(WM_THREAD, 1, 0);
		//Wait for function signal response
		WaitForSingleObject(pthis->m_thread.hThread, 1);
	}
	return 0;
}

LRESULT CRobotControlAPIView::OnThread(WPARAM wParam, LPARAM lParam)
{	
	Update_HMI();
	return 0;
}

void CRobotControlAPIView::OnButtonInitDspDriverConnection() 
{
	//if(m_Serial_DSP.Open(m_port.m_DSP_Comm_Port, 1000000))
	if(m_Serial_DSP.Open(8, 1000000))
	{
		m_system_status.InsertString(-1,"DSP connected!");
		m_system_status.SetCurSel(status_cur);
		status_cur++;
	}
}

////////////////////////////////////////////////////////////////////////////
// Manual_JOG_theta/coordinate_Button
/*
	m_dtheta_unit = XXXX
	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG, Time, J1, J2, J3, J4, J5, J6, 0xfe);
*/

void CRobotControlAPIView::OnButtonM1Rev() 
{		
	manual_JOG_theta_btn(1,0);
}

void CRobotControlAPIView::OnButtonM1Fwd() 
{
	manual_JOG_theta_btn(1,1);
}

void CRobotControlAPIView::OnButtonM2Rev() //Line1
{
	manual_JOG_theta_btn(2,0);
}

void CRobotControlAPIView::OnButtonM2Fwd() //Line2
{
	manual_JOG_theta_btn(2,1);
}

void CRobotControlAPIView::OnButtonM3Rev() 
{
	manual_JOG_theta_btn(3,0);
}

void CRobotControlAPIView::OnButtonM3Fwd() 
{
	manual_JOG_theta_btn(3,1);
}

void CRobotControlAPIView::OnButtonM4Rev() 
{
	manual_JOG_theta_btn(4,0);
}

void CRobotControlAPIView::OnButtonM4Fwd() 
{
	manual_JOG_theta_btn(4,1);
}

void CRobotControlAPIView::OnButtonM5Rev() 
{
	manual_JOG_theta_btn(5,0);
}

void CRobotControlAPIView::OnButtonM5Fwd() 
{
	manual_JOG_theta_btn(5,1);
}

void CRobotControlAPIView::OnButtonM6Rev() 
{
	manual_JOG_theta_btn(6,0);
}

void CRobotControlAPIView::OnButtonM6Fwd() 
{
	manual_JOG_theta_btn(6,1);
}

/*
	m_daxis_unit = XXXX
	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_axis, Time, x, y, z, 0xfe);
*/

void CRobotControlAPIView::OnButtonXRev() 
{
	Manual_JOG_Coordinate_btn(1,0);
}

void CRobotControlAPIView::OnButtonXFwd() 
{
	Manual_JOG_Coordinate_btn(1,1);
}

void CRobotControlAPIView::OnButtonYRev() 
{
	Manual_JOG_Coordinate_btn(2,0);
}

void CRobotControlAPIView::OnButtonYFwd() 
{	
	Manual_JOG_Coordinate_btn(2,1);
}

void CRobotControlAPIView::OnButtonZRev() 
{
	Manual_JOG_Coordinate_btn(3,0);	
}

void CRobotControlAPIView::OnButtonZFwd() 
{
	Manual_JOG_Coordinate_btn(3,1);	
}

void CRobotControlAPIView::OnChangeEdit6() 
{
	UpdateData(TRUE);
	if(m_dtheta_unit>9999)
	{
		m_dtheta_unit=9999;
		AfxMessageBox("The max value is 9999 !");
	}
	if(m_dtheta_unit<0)
	{
		m_dtheta_unit=0;
		AfxMessageBox("The min value is 0 !");
	}
	UpdateData(FALSE);
}

void CRobotControlAPIView::OnChangeEditDaxis() 
{
	UpdateData(TRUE);
	if(m_daxis_unit>9999)
	{
		m_daxis_unit=9999;
		AfxMessageBox("The max value is 8999 !");
	}
	if(m_daxis_unit<0)
	{
		m_daxis_unit=0;
		AfxMessageBox("The min value is 0 !");
	}
	UpdateData(FALSE);	
}

void CRobotControlAPIView::OnTimer(UINT nIDEvent) 
{
	//show waited cmd
	if(nIDEvent == 1)
	{
		CString waited_cmd_num;
		waited_cmd_num.Format("%d",excute_cnt.GetSize());
		m_system_status.InsertString(-1,waited_cmd_num);
		m_system_status.SetCurSel(status_cur);
		status_cur++;
	}
	
	if(nIDEvent == 100)
	{
		GetObject();
		UpdateData(0);
	}

	if(nIDEvent == 200)
	{
		if(m_socket_send < m_socket.m_socket_flag)
		{
			double data[4];
			data[0]=m_socket.m_socket_buffer[m_socket_send][0];
			data[1]=m_socket.m_socket_buffer[m_socket_send][1];
			data[2]=m_socket.m_socket_buffer[m_socket_send][2];
			data[3]=m_socket.m_socket_buffer[m_socket_send][3];

			int offset_x = 13000;
			int offset_y = 0;
			
			int init_x = 40900-offset_x;
			int init_y = 0;
			int init_z = 44450;
			
			int work_height = -24690;
			int work_safe_height = -19690;
			
			int scale = 1000; //1cm to 0.01mm

			int obj_x = data[1]*scale;
			int obj_y = data[2]*scale;

			double angle = data[3];

			if(data[0]==1) // Image Home
			{
				OnButtonInitPosition();
			}
			else if(data[0]==2) //Robot Home
			{
				OnButtonInitHome(); 
			}
			else if(data[0]==3) //A_UP/ open
			{
				int x = init_x + obj_x;
				int y = init_y + obj_y;
				int z = init_z + work_safe_height;
				
				int time=5000;
				int pos[3]={x, y, z};
				int rotate[3]={180,180,0};
				int vel=50;
				P2PPackage(time, pos, rotate, vel);	
				GripperPackage(1); //open
			}
			else if(data[0]==4) //A_DN / close
			{
				int x = init_x + obj_x;
				int y = init_y + obj_y;
				int z = init_z + work_safe_height;
				
				int time=5000;
				int pos[3]={x, y, z};
				int rotate[3]={180,180,0};
				int vel=50;
				LinePackage(time, pos, rotate, vel);	
				GripperPackage(0); //close
			}
			else if(data[0]==5) //A_UP
			{
				int x = init_x + obj_x;
				int y = init_y + obj_y;
				int z = init_z + work_safe_height;
				
				int time=5000;
				int pos[3]={x, y, z};
				int rotate[3]={180,180,0};
				int vel=50;
				P2PPackage(time, pos, rotate, vel);
			}
			else if(data[0]==6) //B_UP
			{
				int x = init_x + obj_x;
				int y = init_y + obj_y;
				int z = init_z + work_safe_height;
				
				int time=5000;
				int pos[3]={x, y, z};
				int rotate[3]={180,180,0};
				int vel=50;
				P2PPackage(time, pos, rotate, vel);
			}
			else if(data[0]==7) //B_DN/ open
			{
				int x = init_x + obj_x;
				int y = init_y + obj_y;
				int z = init_z + work_safe_height;
				
				int time=5000;
				int pos[3]={x, y, z};
				int rotate[3]={180,180,0};
				int vel=50;
				LinePackage(time, pos, rotate, vel);	
				GripperPackage(1); //open
			}
			else if(data[0]==8) //B_UP/ close
			{
				int x = init_x + obj_x;
				int y = init_y + obj_y;
				int z = init_z + work_safe_height;
				
				int time=5000;
				int pos[3]={x, y, z};
				int rotate[3]={180,180,0};
				int vel=50;
				P2PPackage(time, pos, rotate, vel);	
				GripperPackage(0); //close
			}
			else if(data[0]==9) //Rotate j6
			{
				int pulse_total=angle*1000;
				while(1)
				{
					if(pulse_total>0)
					{
						if(pulse_total>=5000)
						{
							pulse_total=pulse_total-5000;
							Rotate_J6(5000);
						}
						else
						{
							Rotate_J6(pulse_total);
							pulse_total=0;
						}
					}
					else if(pulse_total<0)
					{
						if(pulse_total<=-5000)
						{
							pulse_total=pulse_total+5000;
							Rotate_J6(-5000);
						}
						else
						{
							Rotate_J6(pulse_total);
							pulse_total=0;
						}
					}
					else if(pulse_total==0)
					{
						break;
					}
				}
			}
			m_socket_send++;
		}
		else
		{
			//No more package
		}
	}

 	

	CFormView::OnTimer(nIDEvent);
}

void CRobotControlAPIView::OnButtonNewCmd() 
{
	UpdateData(TRUE);
	int i,j;
	CString str, tmp;
	char script[128], time_val[128];
	char buf[128];
	sprintf(buf, "%s", m_cmd);

	switch (buf[0])
	{
	case 'S':
		{
			// SAVe // SAV PXXX
			//         01234567
			if (strlen(m_cmd) == 8 && buf[1] == 'A' && buf[2] == 'V')
			{
				for (i = 4; i <= 7; i++)
				{
					script[i - 4] = buf[i];
				}
				script[i - 4] = '\0';
				str.Format("Point ID: %s Saved!", script);	

				//Save position
				double pos_id = int(script[1]-48)*100+int(script[2]-48)*10+int(script[3]-48)*1;
				pos_data[0].Add(int(pos_id));
				pos_data[1].Add(int(m_axis_X*100.0)); //XYZ
				pos_data[2].Add(int(m_axis_Y*100.0));
				pos_data[3].Add(int(m_axis_Z*100.0));
				pos_data[4].Add(int(m_theta_J1*1000.0)); //J1~6
				pos_data[5].Add(int(m_theta_J2*1000.0));
				pos_data[6].Add(int(m_theta_J3*1000.0));
				pos_data[7].Add(int(m_theta_J4*1000.0));
				pos_data[8].Add(int(m_theta_J5*1000.0));
				pos_data[9].Add(int(m_theta_J6*1000.0));
				

				//Add to ListBox
				CString pos_inform;
				pos_inform.Format("P%03d,  X:%05d,  Y:%05d,  Z:%05d, J1:%06d, J2:%06d, J3:%06d, J4:%06d, J5:%06d, J6:%06d",
					int(pos_id),int(m_axis_X*100.0),int(m_axis_Y*100.0),int(m_axis_Z*100.0),
					int(m_theta_J1*1000.0), int(m_theta_J2*1000.0), int(m_theta_J3*1000.0), 
					int(m_theta_J4*1000.0), int(m_theta_J5*1000.0) ,int(m_theta_J6*1000.0));
				m_list_position.InsertString(-1, pos_inform);

			} else
			{
				str.Format("Error: SAV PXXX");
			}
			break;
		}
	case 'B':
		{
			// BEGig // BEG PRGXXXX
			//          01234567890
			if (strlen(m_cmd) == 11 && buf[1] == 'E' && buf[2] == 'G')
			{
				//Clear = Only prog_code
				m_list_PRG.ResetContent();
				prog_code.RemoveAll();

				//Start to write robot language
				program_start = 1;
				
				for (i = 7; i <= 10; i++)
				{
					script[i - 7] = buf[i];
				}
				script[i - 7] = '\0';
				str.Format("Program Name: PRG%s Added!", script);
				m_list_PRG.InsertString(-1,m_cmd); //ListBox

				//Open file
				tmp.Format("PRG%s", script);
				fp = fopen(tmp+".txt","w"); //PRG

				tmp.Format("POS%s", script);
				fp2 = fopen(tmp+".txt","w"); //POS

				//Write pos data
				CString str2;
				str2="PXXX;\tX:\tY:\tZ:\tJ1;\tJ2;\tJ3;\tJ4;\tJ5;\tJ6;\t";
				fprintf(fp2,"%s\n",str2);
				str2="";

				//Print position to POS file
				for (i = 0; i < pos_data[0].GetSize(); i++)
 				{
					CString tmp2="";
					tmp2.Format("%03d\t", pos_data[0].GetAt(i) );
					str2 += tmp2;

					for(j=1; j<4; j++)
 					{
						tmp2="";
						tmp2.Format("%05d\t", pos_data[j].GetAt(i) );
						str2 += tmp2;
 					}
					for(j=4; j<10; j++)
					{
						tmp2="";
						tmp2.Format("%06d\t", pos_data[j].GetAt(i) );
						str2 += tmp2;
 					}
 					fprintf(fp2,"%s\n",str2);
					str2="";
 				}
				//Print begin to PRG file
				fprintf(fp,"BEG PRG%s\n",script);
			} 
			else
			{
				str.Format("Error: BEG PRGXXXX");
			}
			break;
		}
	case 'E':
		{
			// END
			if (m_cmd == "END" && program_start)
			{
				str.Format("Program Ended, Code Saved!");
				
				//Print program to PRG file
				for (i = 0; i < prog_code.GetSize(); i++)
				{
					tmp.Format("%s ", prog_code[i]);
					fprintf(fp,"%s\n",tmp);
					str += tmp;
				}

				//End of robot language
				program_start = 0;
				fprintf(fp,"END");

				m_list_PRG.InsertString(-1,m_cmd); //ListBox

				//Close PRG & POS file
				fclose(fp);
				fclose(fp2);
			} else
			{
				str.Format("Error: END or Check if BEG PRGXXXX Initiated!");
			}
			break;
		}
	case 'M':
		{
			// MOV // MOV LIN PXXX TTTT			   // Line
			// MOV // MOV P2P PXXX TTTT			   // Point-to-Point
			// MOV // MOV CIR PXXX PXXX PXXX TTTT  // 3-Point form circle
			//        012345678901234567890123456
			if ((strlen(m_cmd) == 17)||(strlen(m_cmd) == 27) && program_start)
			{
				if (buf[4] == 'L' && buf[5] == 'I' && buf[6] == 'N')
				{
					for (i = 8; i <= 11; i++)
					{
						script[i - 8] = buf[i];
					}
					script[i - 8] = '\0';

					for (i = 13; i <= 16; i++)
					{
						time_val[i - 13] = buf[i];
					}
					time_val[i - 13] = '\0';

					//
					str.Format("Move to %s in %3.3f seconds with a Line trajectory", script, atoi(time_val)*0.002);
					
					//Save program
					prog_code.Add(m_cmd);
					//ListBox
					m_list_PRG.InsertString(-1, m_cmd);
				} 
				else if (buf[4] == 'P' && buf[5] == '2' && buf[6] == 'P')
				{
					for (i = 8; i <= 11; i++)
					{
						script[i - 8] = buf[i];
					}
					script[i - 8] = '\0';

					for (i = 13; i <= 16; i++)
					{
						time_val[i - 13] = buf[i];
					}
					time_val[i - 13] = '\0';

					//
					str.Format("Move to %s in %3.3f seconds directly. Saved!", script, atoi(time_val)*0.001);					
					//Save program
					prog_code.Add(m_cmd);
					//ListBox
					m_list_PRG.InsertString(-1, m_cmd);
				} 
				else if (buf[4] == 'C' && buf[5] == 'I' && buf[6] == 'R')
				{
					for (i = 8; i <= 21; i++)
					{
						script[i - 8] = buf[i];
					}
					script[i - 8] = '\0';

					for (i = 23; i <= 26; i++)
					{
						time_val[i - 26] = buf[i];
					}
					time_val[i - 26] = '\0';

					//
					str.Format("Move a circle in %3.3f seconds with points: %s,", atoi(time_val)*0.002, script);
					//Save program
					prog_code.Add(m_cmd);
					//ListBox
					m_list_PRG.InsertString(-1, m_cmd);
				} 
				else
				{
					str.Format("Error: Please Indicate MOV + LIN, P2P or CIR");
				}
			} 
			else
			{
				str.Format("Error: MOV LIN PXXX TTTT, MOV P2P PXXX TTTT or MOV CIR PXXX PXXX PXXX TTTT");
			}
			break;
		}
	case 'R':
		{
			// RUN // RUN PRGXXXX
			//        01234567890
			if (buf[1] == 'U')
			{
				if (strlen(m_cmd) == 11 && buf[2] == 'N')
				{
					for (i = 4; i <= 10; i++)
					{
						script[i - 4] = buf[i];
					}
					script[i - 4] = '\0';

					//
					str.Format("Execute Program Name: %s!", script);		
					//Decode and output cmd
					for (i = 0; i < prog_code.GetSize(); i++)
					{
						run_Robot_PRG(prog_code[i]);
					}
				} 
				else
				{
					str.Format("Error: RUN PRGXXXX");
				}
			} 
			////////////////////////////////////////
			else if (buf[1] == 'E') //resume
			{
				if (m_cmd == "RES")
				{
					str.Format("Resume a Pasue Program");
				} else
				{
					str.Format("Error: PAU!");
				}
			} 
			/////////////////////////////////////////
			else
			{
				str.Format("Error: USE RUN or RES!");
			} 
			break;
		}
	case 'P':
		{
			// PAUse
			if (m_cmd == "PAU")
			{
				str.Format("Pause Current Program");
			} else
			{
				str.Format("Error: PAU!");
			}
			break;
		}
	case 'T':
		{
			// TeRMinate
			if (m_cmd == "TRM")
			{
				str.Format("Terminate Current Program");
			} else
			{
				str.Format("Error: PAU!");
			}
			break;
		}
	case 'L':
		{
			// LoaD // LD PRGXXXX
			//         0123456789
			if (strlen(m_cmd) == 10 && buf[1] == 'D')
			{
				//Clear = Only prog_code
				m_list_PRG.ResetContent();
				m_list_position.ResetContent();
				prog_code.RemoveAll();
				pos_data->RemoveAll();

				//Get Name
				for (i = 6; i <= 9; i++)
				{
					script[i - 6] = buf[i];
				}
				script[i - 6] = '\0';
				str.Format("%s", script);

				CString file1;
				file1.Format("PRG%s",str);

 				CString file2;
 				file2.Format("POS%s",str);

				FILE *Fp1 = fopen(file1+".txt", "r");
				FILE *Fp2 = fopen(file2+".txt", "r");

				char str2;
				char tmp[50];
				int i=0;
				CString str3="",str4="";

				//Load File1
				while(1)
				{
					if(fscanf(Fp1,"%c",&str2) != EOF)
					{
						if(str2 != 10)
						{
							tmp[i] = str2;
							i++;
						}
						else
						{
							tmp[i]='\0';
							i=0;
							str3.Format("%s",tmp);
							m_list_PRG.InsertString(-1, str3);
							prog_code.Add(str3);
						}											
					}
					else
					{
						tmp[i]='\0';
						i=0;
						str3.Format("%s",tmp);
						m_list_PRG.InsertString(-1, str3);
						prog_code.Add(str3);
						break;
					}
				}
				
				int pos_value=0;
				int pos_tmp[10];

				//Load File2
				while(1)
				{
					if(fscanf(Fp2,"%c",&str2) != EOF)
					{
						if(str2 == 10)
							break;											
					}
					else 
						break;
				}

				i=0;
				while(1)
				{
					if(fscanf(Fp2,"%d", &pos_value) != EOF)
					{
						if(i==10) 
						{
							i=0;
						}
						pos_data[i].Add(pos_value);
						pos_tmp[i] = pos_value;
						
						if(i==9)
						{
							str3.Format("P%03d, X:%05d, Y:%05d, Z:%05d, J1:%06d, J2:%06d, J3:%06d, J4:%06d, J5:%06d, J6:%06d", pos_tmp[0], pos_tmp[1], pos_tmp[2], pos_tmp[3], pos_tmp[4], pos_tmp[5], pos_tmp[6], pos_tmp[7], pos_tmp[8], pos_tmp[9]);
							m_list_position.InsertString(-1, str3);
						}										
						i++;
					}
					else
						break;
				}
				fclose(Fp1);
				fclose(Fp2);
			} else
			{
				str.Format("Error: LD PRGXXXX");
			}
			break;
		}
	case 'G':
		{
			// Grip // G X
			//         012
			if (strlen(m_cmd) == 3 && program_start)
			{
					script[0] = buf[2];
					script[1] = '\0';
					
					//Save program
					prog_code.Add(m_cmd);
					//ListBox
					m_list_PRG.InsertString(-1, m_cmd);
			} else
			{
				str.Format("Error: G X");
			}
			break;
			
		}
	default:
		{
			str.Format("Error!!");
			break;
		}
	}
	m_list_execute.InsertString(-1, str);
}

void CRobotControlAPIView::Update_HMI()
{
	//Update theta
	for(int i=0; i<6; i++) 
	{
		npos[i] = dpos[i];
		ntheta[i] = (float)npos[i]*PI/180.0/1000.0;
	}
	m_theta_J1 = float(npos[0])/1000.0; //unit:deg
	m_theta_J2 = float(npos[1])/1000.0;
	m_theta_J3 = float(npos[2])/1000.0;
	m_theta_J4 = float(npos[3])/1000.0;
	m_theta_J5 = float(npos[4])/1000.0;
	m_theta_J6 = float(npos[5])/1000.0;

	//Update coordinate
	fwd_kinematics(ntheta, Ept);
	m_axis_X = Ept[0][3]; //unit:mm
	m_axis_Y = Ept[1][3];
	m_axis_Z = Ept[2][3];
	
	UpdateData(FALSE);
}

void CRobotControlAPIView::int2byte2(int src, unsigned char dst[2])
{
	//int convert to 2bytes
	int src_val = abs(src);
	unsigned char byteH = src_val/250;
	unsigned char byteL = src_val%250;
	
	if(src<0)
		byteH = byteH + 128;
	
	dst[1]=byteH;
	dst[0]=byteL;
}

void CRobotControlAPIView::int2byte3(int src, unsigned char dst[3])
{
	//int convert to 3bytes
	int src_val = abs(src);
	unsigned char byte1 = src_val%250;
	unsigned char byte2 = (src_val/250)%250;
	unsigned char byte3 = src_val/62500;
	
	if(src<0)
		byte3 = byte3 + 128;
	
	dst[2]=byte3;
	dst[1]=byte2;
	dst[0]=byte1;
}

void CRobotControlAPIView::OnButtonRobotmoveManual() 
{
	isRobotMov = FALSE;
}

void CRobotControlAPIView::manual_JOG_theta_btn(int joint, BOOL turn)
{
	unsigned char out[2];

	int m_dtheta_signed;
	if(turn==1) //Fwd
	{
		m_dtheta_signed = m_dtheta_unit;
	}
	else //Rev
	{
		m_dtheta_signed = -m_dtheta_unit;
	}
	int2byte2(m_dtheta_signed,out);
	
	int i;
	int length =15;
	unsigned char package[15];
	
	for(i=0; i<length; i++) package[i]=0;
	package[0]=0xff;
	package[1]=manual_JOG_theta;
	package[14]=0xfe;
	for(i=0; i<length; i++)
	{
		package[joint*2]=out[1];
		package[joint*2+1]=out[0];
	}
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);
}

void CRobotControlAPIView::Manual_JOG_Coordinate_btn(int axis, BOOL turn)
{
	unsigned char out[2];
	
	int m_daxis_signed;
	if(turn==1) //Fwd
	{
		m_daxis_signed = m_daxis_unit;
	}
	else //Rev
	{
		m_daxis_signed = -m_daxis_unit;
	}
	int2byte2(m_daxis_signed,out);
	
	int i;
	int length =9;
	unsigned char package[9];
	
	for(i=0; i<length; i++) package[i]=0;
	package[0]=0xff;
	package[1]=manual_JOG_coordinate;
	package[8]=0xfe;
	for(i=0; i<length; i++)
	{
		package[axis*2]=out[1];
		package[axis*2+1]=out[0];
	}
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);
}

void CRobotControlAPIView::LinePackage(int time, int pos[3], int rotate[3], int vel)
{
	int i;
	int length =21;
	unsigned char package[21];

	//encode
	unsigned char time_package[2];
	int2byte2(time,time_package);
	unsigned char posx_package[3];
	int2byte3(pos[0],posx_package);
	unsigned char posy_package[3];
	int2byte3(pos[1],posy_package);
	unsigned char posz_package[3];
	int2byte3(pos[2],posz_package);
	unsigned char rotate_row_package[2];
	int2byte2(rotate[0],rotate_row_package);
	unsigned char rotate_yaw_package[2];
	int2byte2(rotate[1],rotate_yaw_package);
	unsigned char rotate_pitch_package[2];
	int2byte2(rotate[2],rotate_pitch_package);
	
	//packaging
	package[0]=0xff;
	package[1]=Line;
	package[2]=time_package[1];//time
	package[3]=time_package[0];
	package[4]=posx_package[2];//X
	package[5]=posx_package[1];
	package[6]=posx_package[0];
	package[7]=posy_package[2];//Y
	package[8]=posy_package[1];
	package[9]=posy_package[0];
	package[10]=posz_package[2];//Z
	package[11]=posz_package[1];
	package[12]=posz_package[0];
	package[13]=rotate_row_package[1];//row
	package[14]=rotate_row_package[0];
	package[15]=rotate_yaw_package[1];//yaw
	package[16]=rotate_yaw_package[0];
	package[17]=rotate_pitch_package[1];//pitch
	package[18]=rotate_pitch_package[0];
	package[19]=(unsigned char)vel;
	package[20]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::OnBUTTONtestP1() 
{
	int time=5000;
	int pos[3]={40900,15000,34450}; //0.01mm
	//int pos[3]={60915,0,0}; //0.01mm
	int rotate[3]={200,180,0};
	int vel=50;
	LinePackage(time, pos, rotate, vel);
}

void CRobotControlAPIView::OnBUTTONtestP2()
{
	int time=4000; //ms
	int theta[6]={0,270000,0,0,90000,0}; //0.001 deg
	int vel=50; 
	P2P_tPackage(time, theta, vel);	
}

void CRobotControlAPIView::OnBUTTONtestP3() 
{
	UnlockPackage();
}

void CRobotControlAPIView::OnBUTTONtestP4() 
{
	int time=5000;
	int pos[3]={40900,-15000,34450}; //0.01mm
	//int pos[3]={60915,0,0}; //0.01mm
	int rotate[3]={160,180,0};
	int vel=50;
	LinePackage(time, pos, rotate, vel);
}

void CRobotControlAPIView::OnBUTTONtestP5() 
{
	int time=4000;
	int rotate[3]={100,180,0};
	int vel=50;
	OrientationPackage(time, rotate, vel);
}

void CRobotControlAPIView::OnBUTTONtestP6() 
{
	static bool sw=0;
	sw=!sw;
	GripperPackage(sw);
}

void CRobotControlAPIView::OnBUTTONtestP7() 
{
	static bool sw=0;
	sw=!sw;
	BrakePackage(sw);
}

void CRobotControlAPIView::P2PPackage(int time, int pos[], int rotate[], int vel)
{
	int i;
	int length =21;
	unsigned char package[21];
	
	//encode
	unsigned char time_package[2];
	int2byte2(time,time_package);
	unsigned char posx_package[3];
	int2byte3(pos[0],posx_package);
	unsigned char posy_package[3];
	int2byte3(pos[1],posy_package);
	unsigned char posz_package[3];
	int2byte3(pos[2],posz_package);
	unsigned char rotate_row_package[2];
	int2byte2(rotate[0],rotate_row_package);
	unsigned char rotate_yaw_package[2];
	int2byte2(rotate[1],rotate_yaw_package);
	unsigned char rotate_pitch_package[2];
	int2byte2(rotate[2],rotate_pitch_package);
	
	//packaging
	package[0]=0xff;
	package[1]=P2P;
	package[2]=time_package[1];//time
	package[3]=time_package[0];
	package[4]=posx_package[2];//X
	package[5]=posx_package[1];
	package[6]=posx_package[0];
	package[7]=posy_package[2];//Y
	package[8]=posy_package[1];
	package[9]=posy_package[0];
	package[10]=posz_package[2];//Z
	package[11]=posz_package[1];
	package[12]=posz_package[0];
	package[13]=rotate_row_package[1];//row
	package[14]=rotate_row_package[0];
	package[15]=rotate_yaw_package[1];//yaw
	package[16]=rotate_yaw_package[0];
	package[17]=rotate_pitch_package[1];//pitch
	package[18]=rotate_pitch_package[0];
	package[19]=(unsigned char)vel;
	package[20]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::run_Robot_PRG(CString cmd)
{
	// G   // G X
	// MOV // MOV LIN PXXX TTTT			   // Line
	// MOV // MOV P2P PXXX TTTT			   // Point-to-Point
	// MOV // MOV CIR PXXX PXXX PXXX TTTT  // 3-Point form circle
	//        012345678901234567890123456
	char buf[128],script[128],time_val[128];
	sprintf(buf, "%s", cmd);
	int i,j,k;
	int theta[6];
	int pos[3];
	
	if(buf[0] == 'G')
	{
		//On Off
		unsigned char grip = buf[2]-48;
		GripperPackage(grip);
	}
	else if (buf[4] == 'P' && buf[5] == '2' && buf[6] == 'P')
	{
		//Pos ID
		int pos_id = int(buf[9]-48)*100+int(buf[10]-48)*10+int(buf[11]-48)*1;
		
		//Time
		int time = int(buf[13]-48)*1000+int(buf[14]-48)*100+int(buf[15]-48)*10+int(buf[16]-48)*1;
		
		//Get theta
		for (i = 0; i < pos_data[0].GetSize(); i++)
		{
			if(pos_id == pos_data[0].GetAt(i))
			{
				for(j=0;j<6;j++) //theta 1~6
				{
					theta[j] = pos_data[j+4].GetAt(i);
				}	
			}
		}
		P2P_tPackage(time, theta, 50);
	}
	else if (buf[4] == 'L' && buf[5] == 'I' && buf[6] == 'N')
	{
		
		//Pos ID
		int pos_id = int(buf[9]-48)*100+int(buf[10]-48)*10+int(buf[11]-48)*1;
		
		//Time
		int time = int(buf[13]-48)*1000+int(buf[14]-48)*100+int(buf[15]-48)*10+int(buf[16]-48)*1;
		
		//Get pos
		for (i = 0; i < pos_data[0].GetSize(); i++)
		{
			if(pos_id == pos_data[0].GetAt(i))
			{
				for(j=0;j<3;j++)
				{
					pos[j] = pos_data[j+1].GetAt(i);
				}	
			}
		}
		int rotate[3]={180,180,0};
		LinePackage(time, pos, rotate, 50);
	}
	else if (buf[4] == 'C' && buf[5] == 'I' && buf[6] == 'R')
	{
		
		//Pos ID
		int pos_id[3];
		pos_id[0] = int(buf[9]-48)*100+int(buf[10]-48)*10+int(buf[11]-48)*1;
		pos_id[1] = int(buf[14]-48)*100+int(buf[15]-48)*10+int(buf[16]-48)*1;
		pos_id[2] = int(buf[19]-48)*100+int(buf[20]-48)*10+int(buf[21]-48)*1;
		
		//Time
		int time = int(buf[23]-48)*1000+int(buf[24]-48)*100+int(buf[25]-48)*10+int(buf[26]-48)*1;
		
		int pos3[3][3];
		//Get pos
		for(k = 0; k < 3; k++)
		{
			for (i = 0; i < pos_data[0].GetSize(); i++)
			{
				if(pos_id[k] == pos_data[0].GetAt(i))
				{
					for(j=0;j<3;j++)
					{
						pos3[k][j] = pos_data[j+1].GetAt(i);
					}	
				}
			}
		}
		
		int rotate[3]={180,180,0};
		CirclePackage(time, pos3, rotate, 50);
	}
}

void CRobotControlAPIView::P2P_tPackage(int time, int theta[], int vel)
{
	int i;
	int length =24;
	unsigned char package[24];
	
	//encode
	unsigned char time_package[2];
	int2byte2(time,time_package);

	unsigned char theta_package[6][3];
	int2byte3(theta[0],theta_package[0]);
	int2byte3(theta[1],theta_package[1]);
	int2byte3(theta[2],theta_package[2]);
	int2byte3(theta[3],theta_package[3]);
	int2byte3(theta[4],theta_package[4]);
	int2byte3(theta[5],theta_package[5]);
	
	//packaging
	package[0]=0xff;
	package[1]=P2P_t;
	package[2]=time_package[1];//time
	package[3]=time_package[0];
	package[4]=theta_package[0][2];//theta1
	package[5]=theta_package[0][1];
	package[6]=theta_package[0][0];
	package[7]=theta_package[1][2];//theta2
	package[8]=theta_package[1][1];
	package[9]=theta_package[1][0];
	package[10]=theta_package[2][2];//theta3
	package[11]=theta_package[2][1];
	package[12]=theta_package[2][0];
	package[13]=theta_package[3][2];//theta4
	package[14]=theta_package[3][1];
	package[15]=theta_package[3][0];
	package[16]=theta_package[4][2];//theta5
	package[17]=theta_package[4][1];
	package[18]=theta_package[4][0];
	package[19]=theta_package[5][2];//theta6
	package[20]=theta_package[5][1];
	package[21]=theta_package[5][0];
	package[22]=(unsigned char)vel;
	package[23]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}



void CRobotControlAPIView::CirclePackage(int time, int pos[][3], int rotate[], int vel)
{
	int i;
	int length =39;
	unsigned char package[39];
	
	//encode
	unsigned char time_package[2]; //time
	int2byte2(time,time_package);

	unsigned char pos1x_package[3]; //pos1
	int2byte3(pos[0][0],pos1x_package); 
	unsigned char pos1y_package[3];
	int2byte3(pos[0][1],pos1y_package);
	unsigned char pos1z_package[3];
	int2byte3(pos[0][2],pos1z_package);

	unsigned char pos2x_package[3]; //pos2
	int2byte3(pos[1][0],pos2x_package); 
	unsigned char pos2y_package[3];
	int2byte3(pos[1][1],pos2y_package);
	unsigned char pos2z_package[3];
	int2byte3(pos[1][2],pos2z_package);

	unsigned char pos3x_package[3]; //pos3
	int2byte3(pos[2][0],pos3x_package); 
	unsigned char pos3y_package[3];
	int2byte3(pos[2][1],pos3y_package);
	unsigned char pos3z_package[3];
	int2byte3(pos[2][2],pos3z_package);

	unsigned char rotate_row_package[2]; //rotate
	int2byte2(rotate[0],rotate_row_package);
	unsigned char rotate_yaw_package[2];
	int2byte2(rotate[1],rotate_yaw_package);
	unsigned char rotate_pitch_package[2];
	int2byte2(rotate[2],rotate_pitch_package);
	
	//packaging
	package[0]=0xff;
	package[1]=Circle;
	package[2]=time_package[1];//time
	package[3]=time_package[0];

	package[4]=pos1x_package[2];//X1
	package[5]=pos1x_package[1];
	package[6]=pos1x_package[0];
	package[7]=pos1y_package[2];//Y1
	package[8]=pos1y_package[1];
	package[9]=pos1y_package[0];
	package[10]=pos1z_package[2];//Z1
	package[11]=pos1z_package[1];
	package[12]=pos1z_package[0];

	package[13]=pos2x_package[2];//X2
	package[14]=pos2x_package[1];
	package[15]=pos2x_package[0];
	package[16]=pos2y_package[2];//Y2
	package[17]=pos2y_package[1];
	package[18]=pos2y_package[0];
	package[19]=pos2z_package[2];//Z2
	package[20]=pos2z_package[1];
	package[21]=pos2z_package[0];

	package[22]=pos3x_package[2];//X3
	package[23]=pos3x_package[1];
	package[24]=pos3x_package[0];
	package[25]=pos3y_package[2];//Y3
	package[26]=pos3y_package[1];
	package[27]=pos3y_package[0];
	package[28]=pos3z_package[2];//Z3
	package[29]=pos3z_package[1];
	package[30]=pos3z_package[0];

	package[31]=rotate_row_package[1];//row
	package[32]=rotate_row_package[0];
	package[33]=rotate_yaw_package[1];//yaw
	package[34]=rotate_yaw_package[0];
	package[35]=rotate_pitch_package[1];//pitch
	package[36]=rotate_pitch_package[0];
	package[37]=(unsigned char)vel;
	package[38]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::AutohomePackage()
{
	int i;
	int length =3;
	unsigned char package[3];

	//packaging
	package[0]=0xff;
	package[1]=Autohome;
	package[2]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::OrientationPackage(int time, int rotate[], int vel)
{
	int i;
	int length =12;
	unsigned char package[12];
	
	//encode
	unsigned char time_package[2];
	int2byte2(time,time_package);
	unsigned char rotate_row_package[2];
	int2byte2(rotate[0],rotate_row_package);
	unsigned char rotate_yaw_package[2];
	int2byte2(rotate[1],rotate_yaw_package);
	unsigned char rotate_pitch_package[2];
	int2byte2(rotate[2],rotate_pitch_package);
	
	//packaging
	package[0]=0xff;
	package[1]=Orientation;
	package[2]=time_package[1];//time
	package[3]=time_package[0];
	package[4]=rotate_row_package[1];//row
	package[5]=rotate_row_package[0];
	package[6]=rotate_yaw_package[1];//yaw
	package[7]=rotate_yaw_package[0];
	package[8]=rotate_pitch_package[1];//pitch
	package[9]=rotate_pitch_package[0];
	package[10]=(unsigned char)vel;
	package[11]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);
}

void CRobotControlAPIView::OnButtonInitPosition() 
{
	int time=5000; //ms
	int theta[6]={270000,270000,0,0,90000,0}; //0.001 deg
	int vel=50; 
	P2P_tPackage(time, theta, vel);
}

void CRobotControlAPIView::OnButtonInitHome() 
{
	// TODO: Add your control notification handler code here
	int time=5000; //ms
	int theta[6]={0,270000,0,0,90000,0}; //0.001 deg
	int vel=50; 
	P2P_tPackage(time, theta, vel);
}

void CRobotControlAPIView::OnButtonGetCircle() 
{
	// TODO: Add your control notification handler code here
	ObjectType = 1;
	State = MOVEA;
	SetTimer(100, 100, NULL);
}

void CRobotControlAPIView::OnButtonGetRectangle() 
{
	// TODO: Add your control notification handler code here
	ObjectType = 2;
	State = MOVEA;
	SetTimer(100, 100, NULL);
}


void CRobotControlAPIView::GetObject()
{
	if(!isRobotMov)
	{
		int init_x = 40900;
		int init_y = 0;
		int init_z = 34500;

		int offsetx = 0;
		int offsety = 0;

		int scale = 1000;

		int obj_x, obj_y;
		if(ObjectType == 1)
		{
			obj_x = m_edit_circlex*scale + offsetx ;
			obj_y = m_edit_circley*scale + offsety ;
		}
		else if(ObjectType == 2)
		{
			obj_x = m_edit_rectanglex*scale + offsetx ;
			obj_y = m_edit_rectangley*scale + offsety ;
		}
		
		if(State == MOVEA)
		{
			int x = init_x + obj_x;
			int y = init_y + obj_y;
			int z = init_z - 9500;
			
			int time=5000;		//Unit:ms
			int pos[3]={x, y, z}; //0.01mm
			//int pos[3]={60915,0,0}; //0.01mm
			int rotate[3]={180,180,0};
			int vel=50;
			P2PPackage(time, pos, rotate, vel);

			GripperPackage(1);

			if(ObjectType == 1)
				State = Zdown;
			else if(ObjectType == 2)
				State = RotateGripper;
		}
		else if(State == MOVEB)
		{
			int x = init_x + 10*scale;
			int y = init_y - 25*scale;
			int z = init_z - 9500;
			
			int time=5000;		//Unit:ms
			int pos[3]={x, y, z}; //0.01mm
			//int pos[3]={60915,0,0}; //0.01mm
			int rotate[3]={180,180,0};
			int vel=50;
			P2PPackage(time, pos, rotate, vel);
			
			isDrop = true;
			if(ObjectType == 1)
				State = Zdown;
			else if(ObjectType == 2)
				State = RotateGripper;
		}
		else if(State == Zup)
		{
			int x;
			int y;
			int z;
			if(!isDrop)
			{
				x = init_x + obj_x;
				y = init_y + obj_y;
				z = init_z - 9500;
			}
			else
			{
				x = init_x + 10*scale;
				y = init_y - 25*scale;
				z = init_z;
			}
			
			int time=5000;		//Unit:ms
			int pos[3]={x, y, z}; //0.01mm
			//int pos[3]={60915,0,0}; //0.01mm
			int rotate[3]={180,180,0};
			int vel=50;
			P2PPackage(time, pos, rotate, vel);

			if(!isDrop)
				State = MOVEB;
			else
				State = HOME;
		}
		else if(State == Zdown)
		{
			int x;
			int y;
			int z;
			if(!isDrop)
			{
				x = init_x + obj_x;
				y = init_y + obj_y;
				z = 20142;
			}
			else
			{
				x = init_x + 10*scale;
				y = init_y - 25*scale;
				z = 20142;
			}

			
			int time=5000;		//Unit:ms
			int pos[3]={x, y, z}; //0.01mm
			//int pos[3]={60915,0,0}; //0.01mm
			int rotate[3]={180,180,0};
			int vel=50;
			P2PPackage(time, pos, rotate, vel);

			if(!isDrop)
				State = CloseGripper;
			else
				State = OpenGripper;
		}
		else if(State == RotateGripper)
		{
			if(!isDrop)
			{
				//State = Zdown;
			}
			else
			{

			}
				State = Zdown;
		}
		else if(State == OpenGripper)
		{
			GripperPackage(1);
			if(!isDrop)
			{
			}
			else
			{
			}
				
			State = Zup;
		}
		else if(State == CloseGripper)
		{
			GripperPackage(0);
			State = Zup;
		}
		else if(State == HOME)
		{
			int time=3000; //ms
			int theta[6]={0,270000,0,0,90000,0}; //0.001 deg
			int vel=50; 
			P2P_tPackage(time, theta, vel);
		}
	}
}

void CRobotControlAPIView::GripperPackage(unsigned char grip)
{
	int i;
	int length =4;
	unsigned char package[4];
	
	//packaging
	package[0]=0xff;
	package[1]=Gripper;
	package[2]=grip;
	package[3]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::UnlockPackage()
{
	int i;
	int length =3;
	unsigned char package[3];
	
	//packaging
	package[0]=0xff;
	package[1]=unlock;
	package[2]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::BrakePackage(unsigned char brake)
{
	int i;
	int length =4;
	unsigned char package[4];
	
	//packaging
	package[0]=0xff;
	package[1]=Brake;
	package[2]=brake;
	package[3]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
}

void CRobotControlAPIView::OnBUTTONtestP13() 
{
	int time=4000;
	int rotate[3]={260,180,0};
	int vel=50;
	OrientationPackage(time, rotate, vel);
}

void CRobotControlAPIView::OnButton_get_Image_object() 
{
	// TODO: Add your control notification handler code here
	//Get Object
	Fp2 = fopen("Output.txt", "r");
	double object[5]={0};
	
	int i;
	for(i = 0; i < 5; i++)
	{
		float temp1;
		if(fscanf(Fp2,"%f\n", &temp1) != EOF)
		{
			object[i] = double(temp1);
		}
		else
			break;
	}
	fclose(Fp2);

	m_edit_circlex = object[0];
	m_edit_circley = object[1];
	m_edit_rectanglex = object[2];
	m_edit_rectangley = object[3];
	m_edit_rectangletheta = object[4];

	if(m_edit_rectangletheta>90) m_edit_rectangletheta=m_edit_rectangletheta-180;
	else if(m_edit_rectangletheta<-90) m_edit_rectangletheta=m_edit_rectangletheta+180;
	UpdateData(FALSE);
}

void CRobotControlAPIView::OnBUTTONgetcircle() 
{
	// TODO: Add your control notification handler code here
	ObjectType = 1;
	State = MOVE_A_UP;
	if(!isRobotMov) ImageCatch();
}

void CRobotControlAPIView::OnBUTTONgetrectangle() 
{
	// TODO: Add your control notification handler code here
	ObjectType = 2;
	State = MOVE_A_UP;	
	if(!isRobotMov) ImageCatch();
}

void CRobotControlAPIView::ImageCatch()
{
	int offset_x = 13000;
	int offset_y = 0;

	int init_x = 40900-offset_x;
	int init_y = 0;
	int init_z = 44450;

	int work_height = -24690;
	int work_safe_height = -19690;

	int scale = 1000; //1cm to 0.01mm

	////////////////////////////////
	
	int obj_x, obj_y;
	if(ObjectType == 1)
	{
		obj_x = m_edit_circlex*scale;
		obj_y = m_edit_circley*scale;
	}
	else if(ObjectType == 2)
	{
		obj_x = m_edit_rectanglex*scale;
		obj_y = m_edit_rectangley*scale;
	}

	double angle = m_edit_rectangletheta;
	
	//MOVE_A_UP
	{
		int x = init_x + obj_x;
		int y = init_y + obj_y;
		int z = init_z + work_safe_height;
		
		int time=5000;
		int pos[3]={x, y, z};
		int rotate[3]={180,180,0};
		int vel=50;
		P2PPackage(time, pos, rotate, vel);	
		GripperPackage(1); //open
	}

	//MOVE_A_DOWN
	{
		int x = init_x + obj_x;
		int y = init_y + obj_y;
		int z = init_z + work_height;
		
		int time=5000;
		int pos[3]={x, y, z};
		int rotate[3]={180,180,0};
		int vel=50;
		LinePackage(time, pos, rotate, vel);	
		GripperPackage(0); //close
	}

	//MOVE_A_UP
	{
		int x = init_x + obj_x;
		int y = init_y + obj_y;
		int z = init_z + work_safe_height;
		
		int time=5000;
		int pos[3]={x, y, z};
		int rotate[3]={180,180,0};
		int vel=50;
		LinePackage(time, pos, rotate, vel);
	}
	

	{	
		int x = init_x + 10*scale;
		int y = init_y - 25*scale;
		int z = init_z + work_safe_height;
		
		int time=5000;
		int pos[3]={x, y, z};
		int rotate[3]={180,180,0};
		int vel=50;
		P2PPackage(time, pos, rotate, vel);
	}

	if(ObjectType == 2)
	{
		int pulse_total=angle*1000;
		while(1)
		{
			if(pulse_total>0)
			{
				if(pulse_total>=5000)
				{
					pulse_total=pulse_total-5000;
					Rotate_J6(5000);
				}
				else
				{
					Rotate_J6(pulse_total);
					pulse_total=0;
				}
			}
			else if(pulse_total<0)
			{
				if(pulse_total<=-5000)
				{
					pulse_total=pulse_total+5000;
					Rotate_J6(-5000);
				}
				else
				{
					Rotate_J6(pulse_total);
					pulse_total=0;
				}
			}
			else if(pulse_total==0)
			{
				break;
			}
		}
	}

	//MOVE_B_DOWN
	{
		int x = init_x + 10*scale;
		int y = init_y - 25*scale;
		int z = init_z + work_height;
		
		int time=5000;
		int pos[3]={x, y, z};
		int rotate[3]={180,180,0};
		int vel=50;
		LinePackage(time, pos, rotate, vel);
		GripperPackage(1); //open
	}

	//MOVE_B_UP
	{
		int x = init_x + 10*scale;
		int y = init_y - 25*scale;
		int z = init_z + work_safe_height;
		
		int time=5000;
		int pos[3]={x, y, z};
		int rotate[3]={180,180,0};
		int vel=50;
		LinePackage(time, pos, rotate, vel);
		GripperPackage(0); //close
	}

	//Go_Home
	{
		OnButtonInitHome();
	}
	
	
	// 	if(ObjectType == 1)
	// 		State = Zdown;
	// 	else if(ObjectType == 2)
	// 		State = RotateGripper;
}

void CRobotControlAPIView::Rotate_J6(int pulse)
{
	unsigned char out[2];
	
	int2byte2(pulse,out);
	
	int i;
	int length =15;
	unsigned char package[15];
	
	for(i=0; i<length; i++) package[i]=0;
	package[0]=0xff;
	package[1]=manual_JOG_theta;
	package[14]=0xfe;
	for(i=0; i<length; i++)
	{
		package[6*2]=out[1];
		package[6*2+1]=out[0];
	}
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);
}
