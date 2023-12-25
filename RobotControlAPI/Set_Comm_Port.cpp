// Set_Comm_Port.cpp : implementation file
//

#include "stdafx.h"
#include "RobotControlAPI.h"
#include "Set_Comm_Port.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet_Comm_Port dialog


CSet_Comm_Port::CSet_Comm_Port(CWnd* pParent /*=NULL*/)
	: CDialog(CSet_Comm_Port::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSet_Comm_Port)
	m_DSP_Comm_Port = 8;
	m_D1_Comm_Port = 0;
	m_D2_Comm_Port = 0;
	m_D3_Comm_Port = 0;
	m_D4_Comm_Port = 0;
	m_D5_Comm_Port = 0;
	m_D6_Comm_Port = 0;
	//}}AFX_DATA_INIT
}


void CSet_Comm_Port::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet_Comm_Port)
	DDX_Text(pDX, IDC_EDIT_COMM_DSP, m_DSP_Comm_Port);
	DDX_Text(pDX, IDC_EDIT_COMM_D1, m_D1_Comm_Port);
	DDX_Text(pDX, IDC_EDIT_COMM_D2, m_D2_Comm_Port);
	DDX_Text(pDX, IDC_EDIT_COMM_D3, m_D3_Comm_Port);
	DDX_Text(pDX, IDC_EDIT_COMM_D4, m_D4_Comm_Port);
	DDX_Text(pDX, IDC_EDIT_COMM_D5, m_D5_Comm_Port);
	DDX_Text(pDX, IDC_EDIT_COMM_D6, m_D6_Comm_Port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSet_Comm_Port, CDialog)
	//{{AFX_MSG_MAP(CSet_Comm_Port)
	ON_EN_CHANGE(IDC_EDIT_COMM_DSP, OnChangeEditCommDsp)
	ON_EN_CHANGE(IDC_EDIT_COMM_D1, OnChangeEditCommD1)
	ON_EN_CHANGE(IDC_EDIT_COMM_D2, OnChangeEditCommD2)
	ON_EN_CHANGE(IDC_EDIT_COMM_D3, OnChangeEditCommD3)
	ON_EN_CHANGE(IDC_EDIT_COMM_D4, OnChangeEditCommD4)
	ON_EN_CHANGE(IDC_EDIT_COMM_D5, OnChangeEditCommD5)
	ON_EN_CHANGE(IDC_EDIT_COMM_D6, OnChangeEditCommD6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSet_Comm_Port message handlers

void CSet_Comm_Port::OnChangeEditCommDsp() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSet_Comm_Port::OnChangeEditCommD1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSet_Comm_Port::OnChangeEditCommD2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSet_Comm_Port::OnChangeEditCommD3() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSet_Comm_Port::OnChangeEditCommD4() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSet_Comm_Port::OnChangeEditCommD5() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CSet_Comm_Port::OnChangeEditCommD6() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
