// ImageProcess.cpp: implementation of the CImageProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RobotControlAPI.h"
#include "ImageProcess.h"

#include "cv.h"
#include "highgui.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageProcess::CImageProcess()
{
//	Capture = cvCaptureFromCAM(0);

	Source_window = "Source_window";
	Cut_window = "Cut_window";
	Binary_window = "Binary_window";
	Mouse_window = "Mouse_window";
	Workspace_window = "Workspace_window";
// 
// 	if(Capture)
// 	{
// 		cvNamedWindow(Source_window, CV_WINDOW_AUTOSIZE);
// 		cvNamedWindow(Cut_window, CV_WINDOW_AUTOSIZE);
// 		cvNamedWindow(Binary_window, CV_WINDOW_AUTOSIZE);
// 		cvNamedWindow(Mouse_window, CV_WINDOW_AUTOSIZE);			
// 	}
		

	Pt_TopLeft = cvPoint(0, 0);
	Pt_DownRight = cvPoint(0, 0);

	isGetRectangle = false;
	isGetObject = false;
	isGetPrecizeObject = false;
	isCalibrate = false;

	
}

CImageProcess::~CImageProcess()
{
	cvDestroyAllWindows();
	cvReleaseCapture(&Capture);
}

void CImageProcess::On_Mouse(int event, int x, int y, int flags, void *param)
{
	CImageProcess *temp = (CImageProcess*)param;
	
	IplImage *img = cvCreateImage(cvGetSize(temp->Img), 8, 3);
	cvCopy(temp->Img, img);
	static int layer = 0;
	
	
	if(event == CV_EVENT_LBUTTONUP)
	{
		temp->No_Calib_Pt[layer] = cvPoint(x, y);
	}
	if(event == CV_EVENT_RBUTTONUP)
	{
		layer += 1;
		if(layer > 3)
			layer = 3;
	}
	
	
	cvCircle(img, temp->No_Calib_Pt[0], 3, cvScalar(255, 0, 0), -1);
	cvCircle(img, temp->No_Calib_Pt[1], 3, cvScalar(0, 255, 0), -1);
	cvCircle(img, temp->No_Calib_Pt[2], 3, cvScalar(0, 0, 255), -1);
	cvCircle(img, temp->No_Calib_Pt[3], 3, cvScalar(255, 255, 0), -1);
	
	cvLine(img, temp->No_Calib_Pt[0], temp->No_Calib_Pt[1], cvScalar(0, 255, 255), 1);
	cvLine(img, temp->No_Calib_Pt[0], temp->No_Calib_Pt[2], cvScalar(0, 255, 255), 1);
	cvLine(img, temp->No_Calib_Pt[1], temp->No_Calib_Pt[3], cvScalar(0, 255, 255), 1);
	cvLine(img, temp->No_Calib_Pt[2], temp->No_Calib_Pt[3], cvScalar(0, 255, 255), 1);
	
	CvFont font = cvFont(1, 1);
	CString str;
	str.Format("[%d, %d]", temp->No_Calib_Pt[0].x, temp->No_Calib_Pt[0].y);
	cvPutText(img, str, cvPoint(temp->No_Calib_Pt[0].x, temp->No_Calib_Pt[0].y - 10), &font, cvScalar(255, 0, 0));
	str.Format("[%d, %d]", temp->No_Calib_Pt[1].x, temp->No_Calib_Pt[1].y);
	cvPutText(img, str, cvPoint(temp->No_Calib_Pt[1].x, temp->No_Calib_Pt[1].y - 10), &font, cvScalar(0, 255, 0));
	str.Format("[%d, %d]", temp->No_Calib_Pt[2].x, temp->No_Calib_Pt[2].y);
	cvPutText(img, str, cvPoint(temp->No_Calib_Pt[2].x, temp->No_Calib_Pt[2].y - 10), &font, cvScalar(0, 0, 255));
	str.Format("[%d, %d]", temp->No_Calib_Pt[3].x, temp->No_Calib_Pt[3].y);
	cvPutText(img, str, cvPoint(temp->No_Calib_Pt[3].x, temp->No_Calib_Pt[3].y - 10), &font, cvScalar(255, 255, 0));
	
	int dx = temp->No_Calib_Pt[0].x - temp->No_Calib_Pt[1].x;
	int dy = temp->No_Calib_Pt[0].y - temp->No_Calib_Pt[1].y;
	int lenth01 = sqrt(dx*dx + dy*dy);
	double slope01 = dy/(double)dx;
	
	dx = temp->No_Calib_Pt[0].x - temp->No_Calib_Pt[2].x;
	dy = temp->No_Calib_Pt[0].y - temp->No_Calib_Pt[2].y;
	int lenth02 = sqrt(dx*dx + dy*dy);
	double slope02 = dy/(double)dx;
	
	dx = temp->No_Calib_Pt[1].x - temp->No_Calib_Pt[3].x;
	dy = temp->No_Calib_Pt[1].y - temp->No_Calib_Pt[3].y;
	int lenth13 = sqrt(dx*dx + dy*dy);
	double slope13 = dy/(double)dx;
	
	dx = temp->No_Calib_Pt[2].x - temp->No_Calib_Pt[3].x;
	dy = temp->No_Calib_Pt[2].y - temp->No_Calib_Pt[3].y;
	int lenth23 = sqrt(dx*dx + dy*dy);
	double slope23 = dy/(double)dx;
	
	
	str.Format("%d/%3.2f", lenth01, slope01);
	cvPutText(img, str, cvPoint((temp->No_Calib_Pt[0].x + temp->No_Calib_Pt[1].x)/2, temp->No_Calib_Pt[0].y - 10), &font, cvScalar(0, 255, 255));
	str.Format("%d/%3.2f", lenth02, slope02);
	cvPutText(img, str, cvPoint(temp->No_Calib_Pt[0].x - 10, (temp->No_Calib_Pt[0].y + temp->No_Calib_Pt[2].y)/2), &font, cvScalar(0, 255, 255));
	str.Format("%d/%3.2f", lenth13, slope13);
	cvPutText(img, str, cvPoint(temp->No_Calib_Pt[1].x + 10, (temp->No_Calib_Pt[1].y + temp->No_Calib_Pt[3].y)/2), &font, cvScalar(0, 255, 255));
	str.Format("%d/%3.2f", lenth23, slope23);
	cvPutText(img, str, cvPoint((temp->No_Calib_Pt[2].x + temp->No_Calib_Pt[3].x)/2, temp->No_Calib_Pt[3].y + 10), &font, cvScalar(0, 255, 255));
	
	cvShowImage(temp->Mouse_window, img);
	cvReleaseImage(&img);
}

void CImageProcess::ImageProcedure()
{
	if(isCalibrate)
	{
		IplImage *gray_scale = cvCreateImage(cvGetSize(Result_img), 8, 1);
		cvZero(gray_scale);

		ObjectRecognize(Result_img, gray_scale);
	//	
		cvErode(gray_scale, gray_scale, NULL, 2);
		cvDilate(gray_scale, gray_scale, NULL, 1);

		FCC_ARRAY fcc_arr;
		FastCC(gray_scale, &fcc_arr);
		ObjectClassfied(Result_img, gray_scale, &fcc_arr);


		cvShowImage(Binary_window, gray_scale);
		cvShowImage(Source_window, Result_img);
		cvReleaseImage(&gray_scale);

	}

}

void CImageProcess::Workspace()
{
	#define WORK_WIDTH 920
	#define WORK_HEIGHT 270
	
	Workspace_img = cvCreateImage(cvSize(WORK_WIDTH, WORK_HEIGHT), 8, 3);
	int i, j;
	
	for(i = 0; i < Workspace_img->width; i++)
	{
		for(j = 0; j < Workspace_img->height; j++)
		{
			Workspace_img->imageData[j * Workspace_img->widthStep + i * Workspace_img->nChannels + 2] = (unsigned char)255;
			Workspace_img->imageData[j * Workspace_img->widthStep + i * Workspace_img->nChannels + 1] = (unsigned char)255;
			Workspace_img->imageData[j * Workspace_img->widthStep + i * Workspace_img->nChannels + 0] = (unsigned char)255;
		}
	}
	
	int unit = 10;
	for(i = 0; i < WORK_WIDTH; i += unit)
	{
		cvLine(Workspace_img, cvPoint(i, 0), cvPoint(i, Workspace_img->height), cvScalar(0, 0, 0), 1);
		if(i < WORK_HEIGHT)
		{
			cvLine(Workspace_img, cvPoint(0, i), cvPoint(Workspace_img->width, i), cvScalar(0, 0, 0), 1);
		}
	}

	int tx = cvRound(Object_cpt.x * WORK_WIDTH / Result_img->width);//2:x makeup point
	int ty = cvRound(Object_cpt.y * WORK_HEIGHT / Result_img->height);//4:y makeup point
 	Est_pt.x = cvRound((27*unit - ty) * 295 / WORK_HEIGHT);//+35;
 	Est_pt.y = cvRound((46*unit-tx) * 900 / WORK_WIDTH) - 15;//-60;
	cvCircle(Workspace_img, cvPoint(tx, ty), 5, cvScalar(255, 255, 0), -1);

	CvFont font = cvFont(1, 1);
	CString str;
	str.Format("[%d, %d]", Est_pt.x, Est_pt.y);
	cvPutText(Workspace_img, str, cvPoint(tx, ty - 10), &font, cvScalar(255, 0, 0));

	
	cvCircle(Workspace_img, cvPoint(46*unit , 27*unit), 5, cvScalar(255, 0, 255), -1);
	
	cvShowImage(Workspace_window, Workspace_img);
	cvReleaseImage(&Workspace_img);
}

bool CImageProcess::isCaptureImage()
{
	Capture = cvCaptureFromCAM(0);
	Img = cvQueryFrame(Capture);

	if(Img)
	{
		cvLine(Img, cvPoint(Img->width/2, 0), cvPoint(Img->width/2, Img->height), cvScalar(0, 255, 0), 1);
		cvLine(Img, cvPoint(0, Img->height/2), cvPoint(Img->width, Img->height/2), cvScalar(0, 255, 0), 1);
		cvShowImage(Source_window, Img);
		cvShowImage(Mouse_window, Img);
		return true;
	}
	return false;
}



void CImageProcess::ClickMouse()
{
	if(Img)
		cvSetMouseCallback(Mouse_window, On_Mouse, this);
}

void CImageProcess::ImageCalibration()
{
	CvPoint2D32f src_vertices[4];
	
	src_vertices[0] = cvPoint2D32f(double(No_Calib_Pt[0].x), double(No_Calib_Pt[0].y));
	src_vertices[1] = cvPoint2D32f(double(No_Calib_Pt[1].x), double(No_Calib_Pt[1].y));
	src_vertices[2] = cvPoint2D32f(double(No_Calib_Pt[2].x), double(No_Calib_Pt[2].y));
    src_vertices[3] = cvPoint2D32f(double(No_Calib_Pt[3].x), double(No_Calib_Pt[3].y));
	
	CvPoint2D32f dst_vertices[4];

	double IW;  
	double IH;  

	if(double(No_Calib_Pt[1].x) - double(No_Calib_Pt[0].x) > double(No_Calib_Pt[3].x) - double(No_Calib_Pt[2].x))
		IW = fabs(double(No_Calib_Pt[1].x) - double(No_Calib_Pt[0].x));
	else
		IW = fabs(double(No_Calib_Pt[3].x) - double(No_Calib_Pt[2].x));

	if(double(No_Calib_Pt[2].y) - double(No_Calib_Pt[0].y) > double(No_Calib_Pt[3].y) - double(No_Calib_Pt[1].y))
		IH = fabs(double(No_Calib_Pt[2].y) - double(No_Calib_Pt[0].y));
	else
		IH = fabs(double(No_Calib_Pt[3].y) - double(No_Calib_Pt[1].y));


	dst_vertices[0] = cvPoint2D32f(0, 0);
	dst_vertices[1] = cvPoint2D32f(IW, 0);
	dst_vertices[2] = cvPoint2D32f(0, IH);
    dst_vertices[3] = cvPoint2D32f(IW, IH);
	
	Cut_img = cvCreateImage(cvSize(IW, IH), 8, 3);
	
	int i, j;
	for(i = No_Calib_Pt[0].x; i < No_Calib_Pt[3].x; i++)
	{
		for(j = No_Calib_Pt[0].y; j < No_Calib_Pt[3].y; j++)
		{
			uchar *ptr = cvPtr2D(Img, j, i);
			int r = *(ptr+2);
			int g = *(ptr+1);
			int b = *ptr;
			
			Cut_img->imageData[(j - No_Calib_Pt[0].y)*Cut_img->widthStep + (i - No_Calib_Pt[0].x)*Cut_img->nChannels+2] = (unsigned char)r;
			Cut_img->imageData[(j - No_Calib_Pt[0].y)*Cut_img->widthStep + (i - No_Calib_Pt[0].x)*Cut_img->nChannels+1] = (unsigned char)g;
			Cut_img->imageData[(j - No_Calib_Pt[0].y)*Cut_img->widthStep + (i - No_Calib_Pt[0].x)*Cut_img->nChannels+0] = (unsigned char)b;
		}
	}
	
	CvMat *warp_mat = cvCreateMat( 3, 3, CV_32FC1);
	cvGetPerspectiveTransform(src_vertices, dst_vertices, warp_mat);
	
	
	cvWarpPerspective(Img, Cut_img, warp_mat);

	Result_img = cvCreateImage(cvGetSize(Cut_img), 8, 3);
	cvCopy(Cut_img, Result_img);
	
	int width = Cut_img->width;
	int height = Cut_img->height;

	double l1 = width / (double)GRIDWIDTH;
	double l2 = height / (double)GRIDHEIGHT;
	
	for(i = 0; i < width; i += 5)
	{
		cvLine(Cut_img, cvPoint(cvRound(l1*i), 0), cvPoint(cvRound(l1*i), Cut_img->height), cvScalar(255, 0, 0), 1);
	}
	isCalibrate = true;
	
	xResolution = 1 / l1;
	yResolution = 1 / l2;
	
	
	cvNamedWindow(Cut_window, CV_WINDOW_AUTOSIZE);
	cvShowImage(Cut_window, Cut_img);
	cvDestroyWindow(Mouse_window);
}

void CImageProcess::ObjectRecognize(IplImage *img, IplImage *gray)
{
	IplImage *hsv = cvCreateImage(cvGetSize(img), 8, 3);
	cvCvtColor(img, hsv, CV_RGB2HSV);
	
	int i, j;
	for(i = 0; i < hsv->width; i++)
	{
		for(j = 0; j < hsv->height; j++)
		{
			uchar *ptr = cvPtr2D(hsv, j, i);
			int h = *ptr;
			int s = *(ptr+1);
			int v = *(ptr+2);
			
			double x_temp = s/255.0;
			
			double x3 = x_temp*x_temp*x_temp;
			double x2 = x_temp*x_temp;
			double x =  x_temp;
			
			double a1 = Curve_Parameters_object[0];
			double a2 = Curve_Parameters_object[1];
			double a3 = Curve_Parameters_object[2];
			double a4 = Curve_Parameters_object[3];
			
			int y = int((a4*x3 + a3*x2 + a2*x + a1)*255);
			if(h > y-10 && h < y+10)
			{
				gray->imageData[j * gray->widthStep + i * gray->nChannels] = (unsigned char)255;
			}
		}
	}
	
	cvReleaseImage(&hsv);
}

void CImageProcess::FastCC(IplImage *img, FCC_ARRAY *fcc_arr)
{
	// = = = = = fast connected component = = = = = //
	BOOL FCC_DebugMode = false;
	// initialize tables	
	int i, j;
	//src matrix init
	unsigned int** src;
	src = new unsigned int *[img->width];
	for(i = 0; i < img->width; i++){
		src[i] = new unsigned int [img->height];
	}

	int	*rtable	=	new int	[img->height*img->width/4];
	int	*next	=	new int	[img->height*img->width/4];
	int	*tail	=	new int	[img->height*img->width/4];
	for(i = 0; i < img->height*img->width / 4; i++){
		rtable[i]	= i;	// representative label table
		next[i]		= -1;
		tail[i]		= i;    
	}
	// processing
	int min_height = 0;
	int max_height = img->height;
	int start = 1;
	int	label = start;	// 0 is background
	int	c1, c2, c3, c4, r1, r2, temp;	// t: temp
	for(j = min_height; j < max_height; j++){	// processing from the top-left corner
		for(i = 0; i < img->width; i++){
			// adjustment
			int c0 = GetPixel(i, j, img);	// current point
			if(c0 > start)
			{
				if(i-1 >= 0){
					c1 = src[i-1][j];
				}else{
					c1 = -1;
				}
				if(i-1 >= 0 && j-1 >= 0){
					c2 = src[i-1][j-1];
				}else{
					c2 = -1;
				}
				if(j-1 >= 0){
					c3 = src[i][j-1];
				}else{
					c3 = -1;
				}
				if(i+1 < img->width && j-1 >= 0){
					c4 = src[i+1][j-1];
				}else{
					c4 = -1;
				}
				// object
				if(c3 > 0){	// is labeled foreground
					src[i][j] = c3;
				}else if(c1 > 0)
				{
					src[i][j] = c1;
					if(c4 > 0)
					{	// = = = = = resolve = = = = = //
						r1 = rtable[c4];
						r2 = rtable[c1];
						if(r1 < r2)
						{			
							temp = r2;
							while(temp != -1){
								rtable[temp] = r1;	
								temp = next[temp];
							}
							next[tail[r1]] = r2;
							tail[r1] = tail[r2];
						}else if(r2 < r1)
						{	
							temp = r1;
							while(temp != -1){
								rtable[temp] = r2;	
								temp = next[temp];
							}
							next[tail[r2]] = r1;
							tail[r2] = tail[r1];
						}
					}
				}else if(c2 > 0)
				{
					src[i][j] = c2;
					if(c4 > 0){
						// = = = = = resolve = = = = = //
						r1 = rtable[c2];
						r2 = rtable[c4];
						if(r1 < r2){			
							temp = r2;
							while(temp != -1){
								rtable[temp] = r1;	
								temp = next[temp];
							}
							next[tail[r1]] = r2;
							tail[r1] = tail[r2];
						}else if(r2 < r1){
							temp = r1;
							while(temp != -1){
								rtable[temp] = r2;	
								temp = next[temp];
							}
							next[tail[r2]] = r1;
							tail[r2] = tail[r1];
						}
					}
				}else if(c4 > 0){
					src[i][j] = c4;
				}else{
					src[i][j] = label;
					label = label + 1;
				}
			}
		}
	}
	int *area = new int[label];
	for(i = 0; i < label; i++){
		area[i] = 0;
	}
	CArray<CvPoint, CvPoint> *point = new CArray<CvPoint, CvPoint>[label];
	// refine
	for(j = min_height; j < max_height; j++)
	{
		for(i = 0; i < img->width; i++)
		{
			int data = src[i][j];
			if(data > 0 && data < label){
				int val = rtable[(int)data];
				area[val]++;
				point[val].Add(cvPoint(i, j));
			}
		}
	}
	//加入FastCC物件
	for(i = 0; i < label; i++)
	{
		int x, y, cnt;
		x = y = cnt = 0;
		if(area[i] > 10)
		{
			FCC_OBJECT fcc_obj;
			fcc_obj.Area = area[i];
			
			CvMat* points = cvCreateMat(area[i], 1, CV_32FC2);
			for(j = 0; j < area[i]; j++)
			{
				x += point[i].GetAt(j).x;
				y += point[i].GetAt(j).y;
				cnt += 1;
				
				if(point[i].GetAt(j).y > fcc_obj.Bottom.y)
					fcc_obj.Bottom = point[i].GetAt(j);
				CV_MAT_ELEM(*points, CvPoint2D32f, j, 0) = cvPoint2D32f(point[i].GetAt(j).x, point[i].GetAt(j).y); 
			}
			if(cnt > 0)
			{
				fcc_obj.Center.x = int(x / (double)cnt);
				fcc_obj.Center.y = int(y / (double)cnt);
			}
			fcc_obj.Points = points;
			fcc_arr->Add(fcc_obj);
		}
	}
	// release space
	for(i = 0; i < img->width; i++){
		delete src[i];// = new unsigned int [img->height];
	}
	delete	[] src;
	delete	[]	area;
	for(i = 0; i < label; i++){
		point[i].RemoveAll();
	}
	delete	[]	point;
	delete	[]	rtable;
	delete	[]	next;
	delete	[]	tail;
}

int CImageProcess::GetPixel(int x, int y, IplImage *img)
{
	if(x > 0 && y > 0 && x < img->width && y < img->height)
	{
		int data = 0;
		int ptr = y*img->widthStep + img->nChannels*x;			
		data = (unsigned char)img->imageData[ptr];
		
		return data;
	}else
	{
		return -1;
	}	
}

void CImageProcess::ObjectClassfied(IplImage *src, IplImage *gary, FCC_ARRAY *fcc_arr)
{
	int size = fcc_arr->GetSize();
	int CircleIndex = 0;
	int i;
	
	int check_cnt = 0;
	int r = 0;
	double last_circle = 0;

	if(size > 0)
	{
		//circle
		for(i = 0; i < size; i++)
		{
			object[i] = fcc_arr->GetAt(i).Center;
			cvCircle(src, object[i], 2, CV_RGB(255, 0, 0), -1);

			int now_r = 0;
			//int datas = fcc_arr->GetAt(i).Points->rows;
			if(fcc_arr->GetAt(i).Area > 100)
			{
				now_r = 0;
				for(int k = fcc_arr->GetAt(i).Center.y; k > 0; k--)
				{
					uchar *ptr = cvPtr2D(gary, k, fcc_arr->GetAt(i).Center.x);
					if(*ptr == 0)
						break;
					else
						now_r += 1;
				}
				
				double realcircle;
				if(now_r > 0)	
					realcircle = fcc_arr->GetAt(i).Area / (double)(now_r*now_r);
				if(fabs(realcircle - 3.14159) < 1.0)
				{
					r = now_r;
					check_cnt += 1;
					if(check_cnt == 2)
					{
						if(fabs(realcircle - 3.14159) < last_circle)
						{
							CircleIndex = i;
						}
						else
						{
							if(i == 1)
								CircleIndex = i-1;
							else
								CircleIndex = i;
						}
					}
					last_circle = fabs(realcircle - 3.14159);
				}
			}
		}
	}
	
	cvCircle(src, object[CircleIndex], r, CV_RGB(255, 0, 0), 1);
	Circle_pos = object[CircleIndex];
// 	Rectangle_pos = object[1-CircleIndex];
// 
// 	if(size > 0)
// 	{
// 		//rectangle
// 		CvPoint rec_center = fcc_arr->GetAt(1-CircleIndex).Center;
// 		CvPoint rec_bottom = fcc_arr->GetAt(1-CircleIndex).Bottom;
// 		
// 		int dx = (rec_center.x - rec_bottom.x);
// 		int dy = (rec_center.y - rec_bottom.y);
// 		Rectangle_theta = atan2(dy, dx) * 180.0 / acos(-1);
// 		
// 		cvLine(src, rec_bottom, rec_center, CV_RGB(255, 0, 0), 1);
// 	}
}
