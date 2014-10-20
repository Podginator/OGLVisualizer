#pragma once

//Include all the Math Functions
#include "Matrix.h"
#define PI 3.1415926535897932384626433832795f


//Declare as Static Class
template <typename Type> class MathHelper
{
public:
	MathHelper();
	//Rotations
	static Matrix<float>Matrix2Dtransform(float degree);
	//3D
	static Matrix<float>Matrix3DtransformX(float degree);
	static Matrix<float>Matrix3DtransformY(float degree);
	static Matrix<float>Matrix3DtransformZ(float degree);
	//4D
	static Matrix<float>Matrix4DtransformX(float degree);
	static Matrix<float>Matrix4DtransformY(float degree);
	static Matrix<float>Matrix4DtransformZ(float degree);

	//Scaling Matrices
	static Matrix<Type> Matrix2DScale(Type x, Type y);
	static Matrix<Type> Matrix3DScale(Type x, Type y);
	static Matrix<Type> Matrix4DScale(Type x, Type y);

};