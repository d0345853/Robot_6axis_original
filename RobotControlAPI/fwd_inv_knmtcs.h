#define PI 3.141592653589793f

void crossP3x3(float u[3], float v[3], float output[3]);

void fwd_kinematics(float t[6], float output[4][4]);

void inv_kinematics(float input[4][4], unsigned char result[2], float output[2][6]);
/*
result --> 0,1,2
     0. input is not valid (out of range)
	   1. normal
	   2. J5= 0 or pi --> infinite number of J4&J6 combination
*/

void inv_kinematics_n(float input[4][4], unsigned char result[2], float output[2][6]);

float gripper(float input);
/*
 input in mm
 output in rad
*/
