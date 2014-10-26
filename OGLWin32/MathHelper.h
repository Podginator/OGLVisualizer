#pragma once

//Include all the Math Functions
#include "Matrix.h"
#define PI 3.1415926535897932384626433832795f


//Declare as Static Class
class MathHelper
{
public:
	MathHelper();
	//Rotations

	static float Pi(){ return 3.1415926535897932384626433832795f; }
	
	static Matrix<float>Matrix2Dtransform(float degree);
	//3D
	static Matrix<float>Matrix3DtransformX(float degree);
	static Matrix<float>Matrix3DtransformY(float degree);
	static Matrix<float>Matrix3DtransformZ(float degree);
	//4D
	static Matrix<float>Matrix4DtransformX(float degree);
	static Matrix<float>Matrix4DtransformY(float degree);
	static Matrix<float>Matrix4DtransformZ(float degree);


};