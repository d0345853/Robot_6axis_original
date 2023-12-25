#include "StdAfx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "fwd_inv_knmtcs.h"
	
const float jx_alpha[6]= 	{-PI/2	,0		,-PI/2	,-PI/2	,-PI/2	,0};
const float jx_d[6]=		{291	,0		,0		,334	,0		,218.5};
const float jx_a[6]=		{75		,270	,102	,0		,0		,0};
const float jx_ca[6]=		{0		,1		,0		,0		,0		,1};
const float jx_sa[6]=		{-1		,0		,-1		,-1		,-1		,0};

float A1[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
float A2[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
float A3[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
float A4[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
float A5[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
float A6[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};

void crossP3x3(float u[3], float v[3], float output[3]){
	float fbuf[3]={0,0,0};

	fbuf[0] = (u[1] * v[2]) - (u[2] * v[1]);
	fbuf[1] = (u[2] * v[0]) - (u[0] * v[2]);
	fbuf[2] = (u[0] * v[1]) - (u[1] * v[0]);

	output[0]=fbuf[0];
	output[1]=fbuf[1];
	output[2]=fbuf[2];
}

void DHmul(float A[4][4], float B[4][4], float output[4][4]){
	float DHbuf[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	float Abuf[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	float Bbuf[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	unsigned char i=0,j=0;

	for (i=0;i<3;i++){
		for (j=0;j<4;j++){
			Abuf[i][j]=A[i][j];
			Bbuf[i][j]=B[i][j];
		}
	}
	for (i=0;i<3;i++){
		for (j=0;j<4;j++){
			DHbuf[i][j]=Abuf[i][0]*Bbuf[0][j]
						+Abuf[i][1]*Bbuf[1][j]
						+Abuf[i][2]*Bbuf[2][j]
						+Abuf[i][3]*Bbuf[3][j];
			output[i][j]=DHbuf[i][j];
		}
	}
}

void DHcal(unsigned char input, float theta, float output[4][4]){
	float DHbuf[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	float ct=0,st=0;
	unsigned char i=0,j=0;

	ct=cos(theta);
	st=sin(theta);
	
	DHbuf[0][0] = ct;
	DHbuf[1][0] = st;
	DHbuf[0][1] = -st*jx_ca[input-1];
	DHbuf[1][1] = ct*jx_ca[input-1];
	DHbuf[2][1] = jx_sa[input-1];
	DHbuf[0][2] = st*jx_sa[input-1];
	DHbuf[1][2] = -ct*jx_sa[input-1];
	DHbuf[2][2] = jx_ca[input-1];
	DHbuf[0][3] = ct*jx_a[input-1];
	DHbuf[1][3] = st*jx_a[input-1];
	DHbuf[2][3] = jx_d[input-1];

	for (i=0;i<3;i++){
		for (j=0;j<4;j++){
			output[i][j]=DHbuf[i][j];
		}
	}
}

void inv_kinematics(float input[4][4], unsigned char result[2], float output[2][6]){
	unsigned char i=0,j=0;
	unsigned char rslt[2]={0,0};
	float fbuf=0,fbuf1=0;
	float Aep[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	float Abuf[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	float O4[3]={0,0,0},O4ij[2]={0,0};
	float O1ij_p[2]={0,0};
	float j1_p=0,j2_pp=0,j3_pp=0;
	float j5_ppp=0,j5_ppn=0,j4_ppp=0,j4_ppn=0,j6_ppp=0,j6_ppn=0;
	float d4a3=0;
	float e_p[2]={0,0};
	float b1=0,b2_pp=0,b3_pp=0,b4_p=0;
	float O5z_n[3]={0,0,0},O4y_pp[3]={0,0,0},O4z_ppp[3]={0,0,0};
	float O3y_pp[3]={0,0,0},O3x_pp[3]={0,0,0},O6x[3]={0,0,0},O6y[3]={0,0,0};

	for (i=0;i<3;i++){
		for (j=0;j<4;j++){
			Aep[i][j]=input[i][j];
		}
	}
	O6y[0]=Aep[0][1];O6y[1]=Aep[1][1];O6y[2]=Aep[2][1];
	O6x[0]=Aep[0][0];O6x[1]=Aep[1][0];O6x[2]=Aep[2][0];
	//Finding O4 position
	O4[0] = Aep[0][3] - Aep[0][2] * jx_d[5];
	O4[1] = Aep[1][3] - Aep[1][2] * jx_d[5];
	O4[2] = Aep[2][3] - Aep[2][2] * jx_d[5];
	O4ij[0]=sqrt(O4[0]*O4[0]+O4[1]*O4[1]);
	O4ij[1] = O4[2];
	d4a3=sqrt(jx_d[3] * jx_d[3] + jx_a[2] * jx_a[2]);
	//Solution (+)
	O1ij_p[0] = jx_a[0];
	O1ij_p[1] = jx_d[0];
	e_p[0]=(O4ij[0]-O1ij_p[0]);
	e_p[1]=(O4ij[1]-O1ij_p[1]);
	fbuf=e_p[0]*e_p[0]+e_p[1]*e_p[1];
	if (fbuf<=(d4a3+jx_a[1])*(d4a3+jx_a[1])){
		//Calculate j1(+)
		j1_p=atan2(O4[1],O4[0]);
		//Calculate j2(++),j3(++)
		b1=atan(jx_d[3]/jx_a[2]);
		b4_p=atan2(e_p[1],e_p[0]);
		fbuf1=(d4a3*d4a3+jx_a[1]*jx_a[1]-fbuf)/(2*d4a3*jx_a[1]);
		//special case check
		if (fbuf1>1)fbuf=1;
		else if (fbuf1<-1)fbuf=-1;
		b2_pp=acos(fbuf1);
		fbuf1=(fbuf+jx_a[1]*jx_a[1]-d4a3*d4a3)/(2*sqrt(fbuf)*jx_a[1]);
		//special case check
		if (fbuf1>1)fbuf=1;
		else if (fbuf1<-1)fbuf=-1;
		b3_pp=acos(fbuf1);
		j2_pp=b3_pp+b4_p;
		j3_pp=b1+b2_pp+PI;
		//Calculate j5(+++),j5(++-)
		DHcal(1,j1_p,A1);
		DHcal(2,j2_pp,A2);
		DHcal(3,j3_pp,A3);
		DHmul(A1,A2,Abuf);
		DHmul(Abuf,A3,Abuf);
		O4y_pp[0]=-Abuf[0][2];
		O4y_pp[1]=-Abuf[1][2];
		O4y_pp[2]=-Abuf[2][2];
		O5z_n[0]=-Aep[0][2];
		O5z_n[1]=-Aep[1][2];
		O5z_n[2]=-Aep[2][2];
		fbuf=(O5z_n[0]*O4y_pp[0])+(O5z_n[1]*O4y_pp[1])+(O5z_n[2]*O4y_pp[2]);
		if (fbuf>1)fbuf=1;
		else if (fbuf<-1)fbuf=-1;
		j5_ppp=acos(fbuf);
		j5_ppn=-j5_ppp;
		//Calculate j4(+++),j6(+++)
		crossP3x3(O4y_pp,O5z_n,O4z_ppp);
		fbuf=(O4z_ppp[0]*O4z_ppp[0])+(O4z_ppp[1]*O4z_ppp[1])+(O4z_ppp[2]*O4z_ppp[2]);
		if (fbuf<0.000001f){
			rslt[0]=2;
			//define O4z to be the same as O3y
			O4z_ppp[0]=Abuf[0][1];
			O4z_ppp[1]=Abuf[1][1];
			O4z_ppp[2]=Abuf[2][1];
		}
		else {
			rslt[0]=1;
			fbuf=sqrt(fbuf);
			O4z_ppp[0]=O4z_ppp[0]/fbuf;
			O4z_ppp[1]=O4z_ppp[1]/fbuf;
			O4z_ppp[2]=O4z_ppp[2]/fbuf;
		}
		O3y_pp[0]=Abuf[0][1];O3y_pp[1]=Abuf[1][1];O3y_pp[2]=Abuf[2][1];
		O3x_pp[0]=Abuf[0][0];O3x_pp[1]=Abuf[1][0];O3x_pp[2]=Abuf[2][0];
		fbuf1=(O4z_ppp[0]*O3y_pp[0])+(O4z_ppp[1]*O3y_pp[1])+(O4z_ppp[2]*O3y_pp[2]);
		if (fbuf1>1)fbuf1=1;
		else if (fbuf1<-1)fbuf1=-1;
		fbuf=(-O4z_ppp[0]*O3x_pp[0])+(-O4z_ppp[1]*O3x_pp[1])+(-O4z_ppp[2]*O3x_pp[2]);
		if (fbuf>1)fbuf=1;
		else if (fbuf<-1)fbuf=-1;
		j4_ppp=atan2(fbuf,fbuf1);
		fbuf1=(O4z_ppp[0]*O6y[0])+(O4z_ppp[1]*O6y[1])+(O4z_ppp[2]*O6y[2]);
		if (fbuf1>1)fbuf1=1;
		else if (fbuf1<-1)fbuf1=-1;
		fbuf=(O4z_ppp[0]*O6x[0])+(O4z_ppp[1]*O6x[1])+(O4z_ppp[2]*O6x[2]);
		if (fbuf>1)fbuf=1;
		else if (fbuf<-1)fbuf=-1;
		j6_ppp=atan2(fbuf,fbuf1);
		//Calculate j4(++-),j6(++-)
		if (rslt[0]==2){
			rslt[1]=2;
		}
		else {
			rslt[1]=1;
		}
		j4_ppn=PI+j4_ppp;
		j6_ppn=PI+j6_ppp;
	}
	//copy data to "result"
	for (i=0;i<2;i++)result[i]=rslt[i];
	//copy data to "output"
	output[0][0]=j1_p;output[1][0]=j1_p;
	output[0][1]=j2_pp;output[1][1]=j2_pp;
	output[0][2]=j3_pp;output[1][2]=j3_pp;
	output[0][3]=j4_ppp;output[0][4]=j5_ppp;output[0][5]=j6_ppp;
	output[1][3]=j4_ppn;output[1][4]=j5_ppn;output[1][5]=j6_ppn;
	for (i=0;i<2;i++){
		for (j=0;j<6;j++){
			if (output[i][j]>PI)output[i][j]=(-2*PI)+output[i][j];
			else if (output[i][j]<-PI)output[i][j]=(2*PI)+output[i][j];
		}
	}
}

void inv_kinematics_n(float input[4][4], unsigned char result[2], float output[2][6]){

     result [0]=1;
     result [1]=1;

	double a3p,d3p;  //fix joint3
	double x,y,z,E_tmp[4][4]={0};
	double theta[6]={0};	//final solution j1 to j6
	//variable for joint1
	double B1,C1,D1,vt1;
	//variable for joint3
	double B3,C3,D3,vt3,phi;
	//variable for joint2
	double B21,C21,D21,vt21,vt22,vt2;
	double B22,C22,D22,vt23,vt24;
	//variable for joint5
	double B5,C5,D5,vt5;
	//variable for joint6
	double B61,C61,D61,vt61,vt62;
	double B62,C62,D62,vt63,vt64,vt6;
	//variable for joint4
	double B41,C41,D41,vt41,vt42;
	double B42,C42,D42,vt43,vt44,vt4;
	//s solution number ,initial as 0 (first solution [+,+,+]) p.s s=0~3 checked
	int s=2;
	int i=0,j=0,k=0;
	double vA6_inverse[4][4] ;
	int n[8][3]={{1,1,1},{1,1,-1},{1,-1,1},{1,-1,-1},{-1,1,1},{-1,1,-1},{-1,-1,1},{-1,-1,-1}};   // 8 solutions (+,+,+)~(-,-,-)
	//fprintf('第1組解為(+,+,+)\n第2組解為(+,+,-)\n第3組解為(+,-,+)\n第4組解為(-,+,+)\n第5組解為(-,+,+)\n第6組解為(-,+,-)\n第7組解為(-,-,+)\n第8組解為(-,-,-)\n')
	//i = input('請輸入所要求第幾組解: ')


	//fix joint3
	d3p=jx_d[2]+jx_d[3]*cos(jx_alpha[2]);
	a3p=sqrt(pow(jx_a[2],2)+pow( (jx_d[3]*sin(jx_alpha[2])),2) );

	vA6_inverse[0][0]=0;
	vA6_inverse[0][1]=0;
	vA6_inverse[0][2]=0;
	vA6_inverse[0][3]=-jx_a[5];

	vA6_inverse[1][0]=0;
	vA6_inverse[1][1]=0;
	vA6_inverse[1][2]=0;
	vA6_inverse[1][3]=-jx_d[5]*sin(jx_alpha[5]);

	vA6_inverse[2][0]=0;
	vA6_inverse[2][1]=0;
	vA6_inverse[2][2]=0;
	vA6_inverse[2][3]=-jx_d[5]*cos(jx_alpha[5]);

	vA6_inverse[3][0]=0;
	vA6_inverse[3][1]=0;
	vA6_inverse[3][2]=0;
	vA6_inverse[3][3]=1;

	for (i=0 ; i<4 ; i++)
	{
		for (j=0 ; j<4 ;j++)
		{
			E_tmp[i][j]=input[i][0]*vA6_inverse[0][j]+input[i][1]*vA6_inverse[1][j]+input[i][2]*vA6_inverse[2][j]+input[i][3]*vA6_inverse[3][j];
		}
	}

	//or read x y z directly
	x=E_tmp[0][3];
	y=E_tmp[1][3];
	z=E_tmp[2][3];

	//選解
 	for (s=2 ; s<4 ; s++)
	{
 	////////////////////////////////////////////////////////////////////////////////

 		//=>theta 1
 				B1=-x*sin(jx_alpha[0]);
 				C1=y*sin(jx_alpha[0]);
 				D1=z*cos(jx_alpha[0])-jx_d[0]*cos(jx_alpha[0])-d3p-jx_d[1];

 				vt1=2*atan((B1+n[s][0]*sqrt(pow(B1,2)+pow(C1,2)-pow(D1,2)))/(C1+D1));
 				// vt1=2*atan((B1+1*sqrt(B1^2+C1^2-D1^2))/(C1+D1));
 				theta[0]=vt1*180/PI;

 				//=>theta 3

 				B3=0;
 				C3=2*jx_a[1]*a3p;
 				D3=pow(x,2)+pow(y,2)+pow(z,2)+pow(jx_a[0],2)+pow(jx_d[0],2)+pow(jx_d[1],2)-2*jx_a[0]*x*cos(vt1)-2*jx_a[0]*y*sin(vt1)-2*z*jx_d[0]-2*jx_d[1]*x*sin(vt1)*sin(jx_alpha[0])+2*jx_d[1]*y*cos(vt1)*sin(jx_alpha[0])+2*jx_d[0]*jx_d[1]-2*z*jx_d[1]*cos(jx_alpha[0])-pow(jx_a[1],2)-pow(a3p,2)-pow(d3p,2);
 				//str.Format("%f",D3);
 				//MessageBox(str);

 					vt3=2*atan((B3+n[s][1]*sqrt((pow(B3,2)+pow(C3,2)-pow(D3,2))))/(C3+D3));

 				//fix theta 3
 				phi=atan2(jx_d[3]*sin(jx_alpha[2]),jx_a[2]);
 				theta[2]=vt3*180/PI+phi*180/PI;


 				//=>theta 2

 				B21=-a3p*sin(vt3);
 				C21=a3p*cos(vt3)+jx_a[1];
 				D21=x*cos(vt1)+y*sin(vt1)-jx_a[0];

 				vt21=2*atan((B21+sqrt(pow(B21,2)+pow(C21,2)-pow(D21,2)))/(C21+D21));
 				vt22=2*atan((B21-sqrt(pow(B21,2)+pow(C21,2)-pow(D21,2)))/(C21+D21));


 				////////////////////////////////
 				B22=a3p*cos(vt3)+jx_a[1];
 				C22=a3p*sin(vt3);
 				D22=-(x*sin(vt1)*cos(jx_alpha[0])-y*cos(vt1)*cos(jx_alpha[0])-z*sin(jx_alpha[0])+jx_d[0]*sin(jx_alpha[0]));

 				vt23=2*atan((B22+sqrt(pow(B22,2)+pow(C22,2)-pow(D22,2)))/(C22+D22));
 				vt24=2*atan((B22-sqrt(pow(B22,2)+pow(C22,2)-pow(D22,2)))/(C22+D22));
		//vt2=17.97/180*PI;

		if (abs(vt21-vt23) < 0.0001)
		{
			vt2 = vt21;
		}
		   else if (abs(vt21-vt24) < 0.0001)
		   {
			   vt2 = vt21;
		   }
		   else
		   {
			   vt2=vt22;
		   }

		theta[1]=vt2*180/PI;


		//=>calculate R4*R5*R6

				double A1_inv[4][4];
				double A2_inv[4][4];
				double A3_inv[4][4];

				A1_inv[0][0] = cos(vt1);
				A1_inv[0][1] = sin(vt1);
				A1_inv[0][2] = 0;
				A1_inv[0][3] = -jx_a[0]	;
				A1_inv[1][0] = -sin(vt1)*cos(jx_alpha[0]);
				A1_inv[1][1] = cos(vt1)*cos(jx_alpha[0]);
				A1_inv[1][2] = sin(jx_alpha[0]);
				A1_inv[1][3] = -jx_d[0]*sin(jx_alpha[0]);

				A1_inv[2][0] = sin(vt1)*sin(jx_alpha[0]);
				A1_inv[2][1] = -cos(vt1)*sin(jx_alpha[0]);
				A1_inv[2][2] = cos(jx_alpha[0]);
				A1_inv[2][3] = -jx_d[0]*cos(jx_alpha[0]);
				A1_inv[3][0] = 0;
				A1_inv[3][1] = 0;
				A1_inv[3][2] = 0;
				A1_inv[3][3] = 1;


				A2_inv[0][0] = cos(vt2);
				A2_inv[0][1] = sin(vt2);
				A2_inv[0][2] = 0;
				A2_inv[0][3] = -jx_a[1];
				A2_inv[1][0] = -sin(vt2)*cos(jx_alpha[1]);
				A2_inv[1][1] = cos(vt2)*cos(jx_alpha[1]);
				A2_inv[1][2] = sin(jx_alpha[1]);
				A2_inv[1][3] = -jx_d[1]*sin(jx_alpha[1]);

				A2_inv[2][0] = sin(vt2)*sin(jx_alpha[1]);
				A2_inv[2][1] = -cos(vt2)*sin(jx_alpha[1]);
				A2_inv[2][2] = cos(jx_alpha[1]);
				A2_inv[2][3] = -jx_d[1]*cos(jx_alpha[1]);
				A2_inv[3][0] = 0;
				A2_inv[3][1] = 0;
				A2_inv[3][2] = 0;
				A2_inv[3][3] = 1;

				A3_inv[0][0] = cos(vt3+phi);
				A3_inv[0][1] = sin(vt3+phi);
				A3_inv[0][2] = 0;
				A3_inv[0][3] = -jx_a[2];
				A3_inv[1][0] = -sin(vt3+phi)*cos(jx_alpha[2]);
				A3_inv[1][1] = cos(vt3+phi)*cos(jx_alpha[2]);
				A3_inv[1][2] = sin(jx_alpha[2]);
				A3_inv[1][3] = -jx_d[2]*sin(jx_alpha[2]);

				A3_inv[2][0] = sin(vt3+phi)*sin(jx_alpha[2]);
				A3_inv[2][1] = -cos(vt3+phi)*sin(jx_alpha[2]);
				A3_inv[2][2] = cos(jx_alpha[2]);
				A3_inv[2][3] = -jx_d[2]*cos(jx_alpha[2]);
				A3_inv[3][0] = 0;
				A3_inv[3][1] = 0;
				A3_inv[3][2] = 0;
				A3_inv[3][3] = 1;

		double BM[4][4] = {0},BM_TEM[4][4]={0};

		//INV3*INV2
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++){

					BM_TEM[i][j] += A3_inv[i][k]*A2_inv[k][j];

				}
			}
			//	printf("\n");
		}

		//INV3&2*INV1
		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++){

					BM[i][j] += BM_TEM[i][k]*A1_inv[k][j];

				}
			}
		}

		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				BM_TEM[i][j] = 0;
			}
		}

		for(i=0;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++){

					BM_TEM[i][j] += BM[i][k]*input[k][j];

				}
			}
		}

		for (i=0;i<4;i++)
		{
			for (j=0;j<4;j++)
			{
				BM[i][j]=BM_TEM[i][j];
			}
		}

		////////////////////////////////////////////////解第五軸////////////////////////////////////////////////////////////

		B5 =0;
		C5 = -sin(jx_alpha[3])*sin(jx_alpha[4]);
		D5 = -(cos(jx_alpha[3])*cos(jx_alpha[4])-BM[2][1]*sin(jx_alpha[5])-BM[2][2]*cos(jx_alpha[5]));

		vt5 = 2*atan((B5+n[s][2]*sqrt((B5*B5)+(C5*C5)-(D5*D5)))/(C5+D5));
		theta[4] = vt5*180/PI;

		////////////////////////////////////////////////解第六軸///////////////////////////////////////////////////////////

		//[3,1] B61*sin(t6)+C61*cos(t6) = D61

		B61 = BM[2][1]*cos(jx_alpha[5])+BM[2][2]*sin(jx_alpha[5]);
		C61 = -BM[2][0];
		D61 = -sin(jx_alpha[3])*sin(vt5);

		vt61 = 2*atan((B61+sqrt(abs(B61*B61+C61*C61-D61*D61)))/(C61+D61)) ;
		vt62 = 2*atan((B61-sqrt(abs(B61*B61+C61*C61-D61*D61)))/(C61+D61)) ;


		//[3,2] B62*sin(t6)+C62*cos(t6) = D62

		B62 = -BM[2][0];
		C62 = -BM[2][1]*cos(jx_alpha[5])+BM[2][2]*sin(jx_alpha[5]);
		D62 = -(sin(jx_alpha[3])*cos(vt5)*cos(jx_alpha[4])+cos(jx_alpha[3])*sin(jx_alpha[4]));

		vt63 = 2*atan((B62+sqrt((B62*B62+C62*C62-D62*D62)))/(C62+D62));
		vt64 = 2*atan((B62-sqrt((B62*B62+C62*C62-D62*D62)))/(C62+D62));

		 if (abs(vt61-vt63) < 0.0001)
		 {
			vt6 = vt61;
		 }
		   else if (abs(vt61-vt64) < 0.0001)
		   {
			vt6 = vt61;
		   }
		   else
		   {
			 vt6=vt62;
		   }

		theta[5] = vt6*180/PI;


		//[1,3] B41*sin(t4)+C41*cos(t4)=D41

		B41 = cos(jx_alpha[3])*cos(vt5)*sin(vt5)+sin(jx_alpha[3])*cos(jx_alpha[4]);
		C41 = sin(vt5)*sin(jx_alpha[4]);
		D41 = -(-BM[0][1]*sin(jx_alpha[5])-BM[0][2]*cos(jx_alpha[5]));

		vt41 = 2*atan((B41+sqrt(B41*B41+C41*C41-D41*D41))/(C41+D41));
		vt42 = 2*atan((B41-sqrt(B41*B41+C41*C41-D41*D41))/(C41+D41));

		//[2,3] B41*sin(t4)+C41*cos(t4)=D41

		B42 = sin(vt5)*sin(jx_alpha[4]);
		C42 = -cos(jx_alpha[3])*cos(vt5)*sin(jx_alpha[4])-sin(jx_alpha[3])*cos(jx_alpha[4]);
		D42 = -(-BM[1][1]*sin(jx_alpha[5])-BM[1][2]*cos(jx_alpha[5]));

		vt43 = (2*atan((B42+sqrt(abs(B42*B42+C42*C42-D42*D42)))/(C42+D42)));
		vt44 = (2*atan((B42-sqrt(abs(B42*B42+C42*C42-D42*D42)))/(C42+D42)));


		if (abs((int)(vt41-vt43))<0.0001)
		{
			vt4 = vt41;
		}
		else if (abs((int)(vt41-vt44))<0.0001)
		{
			vt4 = vt41;
		}
		else
		{
			vt4 = vt42;
		}

		theta[3] = (float)(vt4*180/PI);
     //////////////////////////////////////////////////////

     switch (s)
		{
		case 2:
			output[0][0]   = theta[0]*PI/180;
			output[0][1]  = theta[1]*PI/180;
			output[0][2]  = theta[2]*PI/180;
			output[0][3] = theta[3]*PI/180;
			output[0][4] = theta[4]*PI/180;
			output[0][5] = theta[5]*PI/180;
			break;
		case 3:
			output[1][0]   = theta[0]*PI/180;
			output[1][1]  = theta[1]*PI/180;
			output[1][2]  = theta[2]*PI/180;
			output[1][3] = theta[3]*PI/180;
			output[1][4] = theta[4]*PI/180;
			output[1][5] = theta[5]*PI/180;
			break;
        }
     }
}




void fwd_kinematics(float t[6], float output[4][4]){
	float Abuf[4][4]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,1}};
	unsigned short int i=0,j=0;

	DHcal(1,t[0],A1);
	DHcal(2,t[1],A2);
	DHcal(3,t[2],A3);
	DHcal(4,t[3],A4);
	DHcal(5,t[4],A5);
	DHcal(6,t[5],A6);
	DHmul(A1,A2,Abuf);
	DHmul(Abuf,A3,Abuf);
	DHmul(Abuf,A4,Abuf);
	DHmul(Abuf,A5,Abuf);
	DHmul(Abuf,A6,Abuf);
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			output[i][j]=Abuf[i][j];
		}
	}
}
