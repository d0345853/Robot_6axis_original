// RobotControlAPIDoc.cpp : implementation of the CRobotControlAPIDoc class
//

#include "stdafx.h"
#include "RobotControlAPI.h"

#include "RobotControlAPIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIDoc

IMPLEMENT_DYNCREATE(CRobotControlAPIDoc, CDocument)

BEGIN_MESSAGE_MAP(CRobotControlAPIDoc, CDocument)
	//{{AFX_MSG_MAP(CRobotControlAPIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIDoc construction/destruction

CRobotControlAPIDoc::CRobotControlAPIDoc()
{
	// TODO: add one-time construction code here

}

CRobotControlAPIDoc::~CRobotControlAPIDoc()
{
}

BOOL CRobotControlAPIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIDoc serialization

void CRobotControlAPIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIDoc diagnostics

#ifdef _DEBUG
void CRobotControlAPIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRobotControlAPIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRobotControlAPIDoc commands
