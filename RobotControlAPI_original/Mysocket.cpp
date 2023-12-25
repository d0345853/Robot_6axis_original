// Mysocket.cpp : implementation file
//

#include "stdafx.h"
#include "Mysocket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysocket

CMysocket::CMysocket()
{
	count = 0;
	m_socket_flag=0;
}

CMysocket::~CMysocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CMysocket, CSocket)
	//{{AFX_MSG_MAP(CMysocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CMysocket member functions

void CMysocket::OnReceive(int nErrorCode) 
{
// 	count++;
// 	unsigned char buff[1024];
// 	int byte = Receive(buff, sizeof(buff));
// 	CString str,data_string;
// 
// 	for(int i = 0 ; i < byte ; i++)
// 	{
// 		data_string.Format("%c",buff[i]);
// 		str+=data_string;
// 	}
// 	receive_data = str;
// 	AfxMessageBox(receive_data);

	double buff[4];
	int byte = Receive(buff, sizeof(buff));
	CString str,data_string;
	
	for(int i = 0 ; i < 4 ; i++)
	{
		m_socket_buffer[m_socket_flag][i] = buff[i];

		data_string.Format("%f",buff[i]);
		str+=data_string;
	}
	m_socket_flag++;
	AfxMessageBox(str);

	CSocket::OnReceive(nErrorCode);
}

void CMysocket::Senddata()
{

}
