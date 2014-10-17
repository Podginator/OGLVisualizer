#include "MathHelper.h"


MathHelper<float>::MathHelper()
{

}
Matrix<float> MathHelper<float>::Matrix2Dtransform(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(2, 2, 0.0f);
	res(0, 0) = cos(radians);
	res(0, 1) = -sin(radians);
	res(1, 0) = sin(radians);
	res(1, 1) = cos(radians);

	return res;
}


Matrix<float> MathHelper<float>::Matrix3DtransformX(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(3, 3, 0.0f);

	res(0, 0) = 1.0f;
	res(1, 1) = cos(radians);
	res(1, 2) = -sin(radians);
	res(2, 1) = sin(radians);
	res(2, 2) = cos(radians);

	return res;
}

Matrix<float> MathHelper<float>::Matrix3DtransformY(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(3, 3, 0.0f);

	res(0, 0) = cos(radians);
	res(0, 2) = -sin(radians);
	res(1, 2) = 1.0f;
	res(2, 0) = -sin(radians);
	res(2, 2) = cos(radians);

	return res;
}

Matrix<float> MathHelper<float>::Matrix3DtransformZ(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(3, 3, 0.0f);

	res(0, 0) = cos(radians);
	res(0, 1) = -sin(radians);
	res(1, 0) = sin(radians);
	res(1, 1) = cos(radians);
	res(2, 2) = 1.0f;

	return res;
}


Matrix<float> MathHelper<float>::Matrix4DtransformZ(float degrees)
{

	float radians = degrees * PI / 180.0f;
	Matrix<float> res(4, 4, 0.0f);
	res = Matrix3DtransformZ(degrees);
	res(3, 3) = 1.0f;

	return res;
}

Matrix<float> MathHelper<float>::Matrix4DtransformX(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(4, 4, 0.0f);
	res = Matrix3DtransformX(degrees);
	res(3, 3) = 1.0f;

	return res;
}

Matrix<float> MathHelper<float>::Matrix4DtransformY(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(4, 4, 0.0f);
	res = Matrix3DtransformY(degrees);
	res(3, 3) = 1.0f;

	return res;
}