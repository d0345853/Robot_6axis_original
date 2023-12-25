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
	m_dtheta_unit = 0;
	m_theta_J1 = 0.0;
	m_theta_J2 = 0.0;
	m_theta_J3 = 0.0;
	m_theta_J4 = 0.0;
	m_theta_J5 = 0.0;
	m_theta_J6 = 0.0;
	m_daxis_unit = 0;
	m_axis_X = 0.0;
	m_axis_Y = 0.0;
	m_axis_Z = 0.0;
	m_cmd = _T("");
	m_waited_cmd_num = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CRobotControlAPIView::~CRobotControlAPIView()
{
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
	DDX_Control(pDX, IDC_LIST_PRG, m_list_PRG);
	DDX_Control(pDX, IDC_LIST_EXECUTE, m_list_execute);
	DDX_Control(pDX, IDC_LIST_STATUS, m_system_status);
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
	DDX_Text(pDX, IDC_EDIT_NEW_CMD, m_cmd);
	DDX_Text(pDX, IDC_EDIT_WAITED_CMD_NUM, m_waited_cmd_num);
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
	SetTimer(1,2000, NULL);
//Robot state
	isRobotMov = FALSE;
//npos initial
	for(int i=0; i<6; i++) npos[i]=0;
//initial cursor
	status_cur = 0;
	prog_cur = 0;
	excute_cur = 0;
	
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
			ptr++;
			if(ptr==20)
			{
				/* dpos package ///////////////////////
					0xff		theta1~6		 0xfe
					 0	 123 456 789 012 345 678  9  
				*/ ////////////////////////////////////
				for(int i=1; i<=16; i=i+3)
				{
					int dpos_t = (rec_data[i]%64)*250*250 + (rec_data[i+1])*250 + rec_data[i+2]; //7'6543210
					if(rec_data[i]/64 == 1) dpos_t=-dpos_t;
					pthis->dpos[i/3]=dpos_t;
				}

				//Update 
				pthis->Update_HMI();
				//Set Robot is stopping state
				pthis->isRobotMov = FALSE;

				ptr=0;
			}else;
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
			}else;
		}else;

		//return LPVOID pParam (pthis)
		//wnd->PostMessage(WM_THREAD, 1, 0);
		//Wait for function signal response
		WaitForSingleObject(pthis->m_thread.hThread, 1);
	}
	return 0;
}

LRESULT CRobotControlAPIView::OnThread(WPARAM wParam, LPARAM lParam)
{	
	return 0;
}

void CRobotControlAPIView::OnButtonInitDspDriverConnection() 
{
	
	//if(m_Serial_DSP.Open(m_port.m_DSP_Comm_Port, 1000000))
	if(m_Serial_DSP.Open(8, 1000000))
	{
		m_system_status.InsertString(-1,6);
		m_system_status.SetCurSel(status_cur);
		status_cur++;
	}
	
// 	if(m_Serial_D1.Open(m_port.m_D1_Comm_Port, 9600))
// 	{
// 		m_system_status.InsertString(0,"Connecting D1 ...");
// 	}
// 		m_Serial_D2.Open(m_port.m_D2_Comm_Port, 9600) &&
// 		m_Serial_D3.Open(m_port.m_D3_Comm_Port, 9600) &&
// 		m_Serial_D4.Open(m_port.m_D4_Comm_Port, 9600) &&
// 		m_Serial_D5.Open(m_port.m_D5_Comm_Port, 9600) &&
// 		m_Serial_D6.Open(m_port.m_D6_Comm_Port, 9600) )
	
}

////////////////////////////////////////////////////////////////////////////
// Manual_JOG_theta/coordinate_Button
/*
	m_dtheta_unit = XXXX
	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG, Time, J1, J2, J3, J4, J5, J6, 0xfe);
*/

void CRobotControlAPIView::OnButtonM1Rev() 
{	
	unsigned char out[2];
	int2byte2(m_dtheta_unit,out);
	
	int i;
	int length =15;
	unsigned char package[15];

	for(i=0; i<length; i++) package[i]=0;
	package[0]=0xff;
	package[1]=manual_JOG_theta;
	package[2]=out[1];
	package[3]=out[0];
	package[14]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	
	
	//manual_JOG_theta_btn(1);

// 	char cBuf0[38];
// 	int m_dtheta = -m_dtheta_unit;
// 	
// 	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, m_dtheta, 0, 0, 0, 0, 0, 0xfe);
// 	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM1Fwd() 
{
	unsigned char out[2];
	int2byte2(m_dtheta_unit,out);
	
	int i;
	int length =15;
	unsigned char package[15];

	for(i=0; i<length; i++) package[i]=0;
	package[0]=0xff;
	package[1]=manual_JOG_theta;
	package[2]=out[1];
	package[3]=out[0];
	package[14]=0xfe;
	
	for(i=0; i<length; i++) excute_buf.Add(package[i]);
	excute_cnt.Add(length);	

	//manual_JOG_theta_btn(1);

// 	char cBuf0[38];
// 	int m_dtheta = m_dtheta_unit;
// 	
// 	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, m_dtheta, 0, 0, 0, 0, 0, 0xfe);
// 	m_Serial_DSP.SendData(cBuf0,37);
}


void CRobotControlAPIView::OnButtonM2Rev() //Line1
{
	int time;
	int pos[3];
	int rotate[3];
	int vel;
	//LinePackage(int time, int pos[3], int rotate[3], int vel);
	LinePackage(time, pos, rotate, vel);

// 	char cBuf0[38];
// 	int m_dtheta = -m_dtheta_unit;
// 	
// 	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, m_dtheta, 0, 0, 0, 0, 0xfe);
// 	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM2Fwd() //Line2
{
// 	char cBuf0[38];
// 	int m_dtheta = m_dtheta_unit;
// 
// 	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, m_dtheta, 0, 0, 0, 0, 0xfe);
// 	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM3Rev() 
{
	char cBuf0[38];
	int m_dtheta = -m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, m_dtheta, 0, 0, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM3Fwd() 
{
	char cBuf0[38];
	int m_dtheta = m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, m_dtheta, 0, 0, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM4Rev() 
{
	char cBuf0[38];
	int m_dtheta = -m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, 0, m_dtheta, 0, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM4Fwd() 
{
	char cBuf0[38];
	int m_dtheta = m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, 0, m_dtheta, 0, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM5Rev() 
{
	char cBuf0[38];
	int m_dtheta = -m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, 0, 0, m_dtheta, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM5Fwd() 
{
	char cBuf0[38];
	int m_dtheta = m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, 0, 0, m_dtheta, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM6Rev() 
{
	char cBuf0[38];
	int m_dtheta = -m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, 0, 0, 0, m_dtheta, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

void CRobotControlAPIView::OnButtonM6Fwd() 
{
	char cBuf0[38];
	int m_dtheta = m_dtheta_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_theta, 0, 0, 0, 0, 0, 0, m_dtheta, 0xfe);
	m_Serial_DSP.SendData(cBuf0,37);
}

/*
	m_daxis_unit = XXXX
	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%05d%05d%05d%c", 0xff, manual_JOG_axis, Time, x, y, z, 0xfe);
*/

void CRobotControlAPIView::OnButtonXRev() 
{
	char cBuf0[23];
	int m_daxis = -m_daxis_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%c", 0xff, manual_JOG_coordinate, 0, m_daxis, 0, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,22);
}

void CRobotControlAPIView::OnButtonXFwd() 
{
	char cBuf0[23];
	int m_daxis = m_daxis_unit;

	sprintf(cBuf0, "%c%c%04d%05d%05d%05d%c", 0xff, manual_JOG_coordinate, 0, m_daxis, 0, 0, 0xfe);
	m_Serial_DSP.SendData(cBuf0,22);
}

void CRobotControlAPIView::OnButtonYRev() 
{
	// TODO: Add your control notification handler code here
	
}

void CRobotControlAPIView::OnButtonYFwd() 
{
	// TODO: Add your control notification handler code here
	
}

void CRobotControlAPIView::OnButtonZRev() 
{
	// TODO: Add your control notification handler code here
	
}

void CRobotControlAPIView::OnButtonZFwd() 
{
	// TODO: Add your control notification handler code here
	
}

void CRobotControlAPIView::OnChangeEdit6() 
{
	UpdateData(TRUE);
	if(m_dtheta_unit>8999)
	{
		m_dtheta_unit=8999;
		AfxMessageBox("The max value is 8999 !");
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
	if(m_daxis_unit>8999)
	{
		m_daxis_unit=8999;
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
	m_waited_cmd_num = excute_cnt.GetSize();
	UpdateData(FALSE);

	CFormView::OnTimer(nIDEvent);
}

void CRobotControlAPIView::OnButtonNewCmd() 
{
	UpdateData(TRUE);
	int i;
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

				//save position////////////////////
				double pos_id = int(script[1]-48)*100.0+int(script[2]-48)*10.0+int(script[3]-48)*1.0;
				pos_data[0].Add(pos_id);
				pos_data[1].Add(m_axis_X);
				pos_data[2].Add(m_axis_Y);
				pos_data[3].Add(m_axis_Z);
				pos_data[4].Add(m_theta_J1);
				pos_data[5].Add(m_theta_J2);
				pos_data[6].Add(m_theta_J3);
				pos_data[7].Add(m_theta_J4);
				pos_data[8].Add(m_theta_J5);
				pos_data[9].Add(m_theta_J6);
				////////////////////////////////////
			} else
			{
				str.Format("Error: SAV PXXX");
			}
			break;
		}
	case 'F':
		{
			// FINd // FIN PXXX
			//         01234567
			if (strlen(m_cmd) == 8 && buf[1] == 'I' && buf[2] == 'N')
			{
				for (i = 4; i <= 7; i++)
				{
					script[i - 4] = buf[i];
				}
				script[i - 4] = '\0';
				str.Format("Point ID: %s data is showed below!", script);
				
				double pos_id = script[1]*100+script[2]*10+script[3];
				int index=-1;
				for (i = 0; i < pos_data[0].GetSize(); i++)
				{
					if(pos_data[0].GetAt(i)==pos_id)
					{
						index=i;
						break;
					}
				}
				//¨ú¥XPXXXªºdata
				if(index>0)
				{
					for(i=0; i<10; i++)
					{
						tmp.Format("%d; ", pos_data[i].GetAt(index));
						str += tmp;
					}
				}
				else{
					str.Format("No indicated point");
				}	
			} 
			else{
				str.Format("Error: FIN PXXX");
			}
			break;
		}
	case 'B':
		{
			// BEGig // BEG PRGXXXX
			//          01234567890
			if (strlen(m_cmd) == 11 && buf[1] == 'E' && buf[2] == 'G')
			{
				prog_code.RemoveAll();
				program_start = 1;
				for (i = 4; i <= 10; i++)
				{
					script[i - 4] = buf[i];
				}
				script[i - 4] = '\0';
				str.Format("Program Name: %s Added!", script);

				//open file///////////////////////
				tmp.Format("%s", script);
				fp = fopen(tmp+".txt","w");
				//write pos data
				CString str2;
				str2="PXXX;\tX;\tY;\tZ;\tJ1;\tJ2;\tJ3;\tJ4;\tJ5;\tJ6;\t";
				fprintf(fp,"%s\n",str2);
				str2="";

				for (i = 0; i < pos_data[0].GetSize(); i++)
 				{
					for(int j=0; j<10; j++)
 					{
						CString tmp2="";
						if(j==0)tmp2.Format("P%03d;\t", int(pos_data[j].GetAt(i)));
						else tmp2.Format("%2.2f;\t", pos_data[j].GetAt(i));

						str2 += tmp2;
 					}
 					fprintf(fp,"%s\n",str2);
					str2="";
 				}
				fprintf(fp,"\nBEG %s\n",tmp);
				/////////////////////////////////
			} else
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
				str.Format("Program Ended, Code Saved! Program code: ");
				for (i = 0; i < prog_code.GetSize(); i++)
				{
					tmp.Format("%s; ", prog_code[i]);
					fprintf(fp,"%s;\n",tmp);
					str += tmp;
				}
				program_start = 0;
				fprintf(fp,"END");
				fclose(fp);
			} else
			{
				str.Format("Error: END or Check if BEG PRGXXXX Initiated!");
			}
			break;
		}
	case 'M':
		{
			// MOVe // MOV LIN PXXX TTTT // 2ms TTTT // Line
			// MOVe // MOV P2P PXXX TTTT // 2ms TTTT // Point-to-Point
			// MOVe // MOV CIR PXXX PXXX PXXX TTTT // 2ms TTTT // 3-Point form circle
			//         012345678901234567890123456
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
					str.Format("Move to %s in %3.3f seconds with a Line trajectory", script, atoi(time_val)*0.002);
					prog_code.Add(m_cmd);
				} else if (buf[4] == 'P' && buf[5] == '2' && buf[6] == 'P')
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
					str.Format("Move to %s in %3.3f seconds directly", script, atoi(time_val)*0.002);
					prog_code.Add(m_cmd);
				} else if (buf[4] == 'C' && buf[5] == 'I' && buf[6] == 'R')
				{
					for (i = 8; i <= 21; i++)
					{
						script[i - 8] = buf[i];
					}
					script[i - 18] = '\0';
					for (i = 23; i <= 26; i++)
					{
						time_val[i - 26] = buf[i];
					}
					time_val[i - 26] = '\0';
					str.Format("Move a circle in %3.3f seconds with points: %s,", atoi(time_val)*0.002, script);
					prog_code.Add(m_cmd);
				} else
				{
					str.Format("Error: Please Indicate LIN, P2P or CIR");
				}
				m_list_PRG.InsertString(-1, m_cmd);
			} else
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
					str.Format("Execute Program Name: %s!", script);
				} else
				{
					str.Format("Error: RUN PRGXXXX");
				}
			} else if (buf[1] == 'E')
			{
				if (m_cmd == "RES")
				{
					str.Format("Resume a Pasue Program");
				} else
				{
					str.Format("Error: PAU!");
				}
			} else
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
		npos[i] = npos[i] + dpos[i];
		ntheta[i] = (float)npos[i]*3.14/180/1000;
	}
	m_theta_J1 = float(npos[0])/1000; //unit:deg
	m_theta_J2 = float(npos[1])/1000;
	m_theta_J3 = float(npos[2])/1000;
	m_theta_J4 = float(npos[3])/1000;
	m_theta_J5 = float(npos[4])/1000;
	m_theta_J6 = float(npos[5])/1000;

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
		byteH = byteH + 1<<7;
	
	dst[1]=byteH;
	dst[0]=byteL;
}

void CRobotControlAPIView::int2byte3(int src, unsigned char dst[3])
{
	//int convert to 3bytes
	int src_val = abs(src);
	unsigned char byte3 = src_val/62500;
	unsigned char byte2 = src_val/250;
	unsigned char byte1 = src_val%250;

	if(src<0)
		byte3 = byte3 + 1<<7;
	
	dst[2]=byte3;
	dst[1]=byte2;
	dst[0]=byte1;
}

void CRobotControlAPIView::OnButtonRobotmoveManual() 
{
	isRobotMov = FALSE;
}

void CRobotControlAPIView::manual_JOG_theta_btn(int joint)
{
	unsigned char out[2];
	int2byte2(m_dtheta_unit,out);
	
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

void CRobotControlAPIView::Manual_JOG_Coordinate_btn(int joint)
{
	
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
