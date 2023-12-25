// ImageProcess.h: interface for the CImageProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEPROCESS_H__2292B10C_3E2B_459E_97D2_53C899DC61D2__INCLUDED_)
#define AFX_IMAGEPROCESS_H__2292B10C_3E2B_459E_97D2_53C899DC61D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "cv.h"
//#include "highgui.h"



class CImageProcess  
{
public:
	struct FCC_OBJECT
	{
		CvPoint Center;
		CvPoint Bottom;
		int Area;	
		CvMat* Points;	
	};
typedef CArray<FCC_OBJECT, FCC_OBJECT> FCC_ARRAY;

public:
	void Workspace();
	void ImageProcedure();
	static void On_Mouse(int event, int x, int y, int flags, void *param);
	CImageProcess();
	virtual ~CImageProcess();

public:
	bool isCaptureImage();
	
public:
	void ObjectRecognize(IplImage *img, IplImage *gray);
	void ImageCalibration();
	void ClickMouse();

public:
	CvCapture *Capture;
	IplImage *Img;

	char *Source_window;
	char *Cut_window;
	char *Binary_window;
	char *Mouse_window;
	char *Workspace_window;
	
	
	IplImage *Cut_img;
	IplImage *Result_img;
	IplImage *Binary;
	IplImage *Workspace_img;

	CvPoint No_Calib_Pt[4];

public:
	void ObjectClassfied(IplImage *src, IplImage *gary, FCC_ARRAY *fcc_arr);
	int GetPixel(int x, int y, IplImage *img);
	void FastCC(IplImage *img, FCC_ARRAY *fcc_arr);
	CvPoint Object_cpt;
	CvPoint Est_pt;

	bool isCalibrate;
	bool isGetObject;
	bool isGetPrecizeObject;

	double Rectangle_theta;

	CvPoint object[2];
	CvPoint Circle_pos;
	CvPoint Rectangle_pos;


	int Result_Width, Result_Height, Shift_X, Shift_Y;
	
	
	double xResolution;
	double yResolution;
	double Curve_Parameters_object[4];


private:

	CvPoint Pt_TopLeft, Pt_DownRight;

	bool isGetRectangle;
};

#endif // !defined(AFX_IMAGEPROCESS_H__2292B10C_3E2B_459E_97D2_53C899DC61D2__INCLUDED_)
