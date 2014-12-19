#include "MathHelper.h"




Matrix<float> MathHelper::Matrix2Dtransform(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(2, 2, 0.0f);
	res(0, 0) = cos(radians);
	res(0, 1) = -sin(radians);
	res(1, 0) = sin(radians);
	res(1, 1) = cos(radians);

	return res;
}


Matrix<float> MathHelper::Matrix3DtransformX(float degrees)
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

Matrix<float> MathHelper::Matrix3DtransformY(float degrees)
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

Matrix<float> MathHelper::Matrix3DtransformZ(float degrees)
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


Matrix<float> MathHelper::Matrix4DtransformZ(float degrees)
{

	float radians = degrees * PI / 180.0f;
	Matrix<float> res(3, 3, 0.0f);

	res(0, 0) = cos(radians);
	res(0, 1) = -sin(radians);
	res(1, 0) = sin(radians);
	res(1, 1) = cos(radians);
	res(2, 2) = 1.0f;
	res(3, 3) = 1.0f;

	return res;
}

Matrix<float> MathHelper::Matrix4DtransformX(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(4, 4, 0.0f);
	res(0, 0) = 1.0f;
	res(1, 1) = cos(radians);
	res(1, 2) = -sin(radians);
	res(2, 1) = sin(radians);
	res(2, 2) = cos(radians);
	res(3, 3) = 1.0f;

	return res;
}

Matrix<float> MathHelper::Matrix4DtransformY(float degrees)
{
	float radians = degrees * PI / 180.0f;
	Matrix<float> res(4, 4, 0.0f);
	res(0, 0) = cos(radians);
	res(0, 2) = sin(radians);
	res(1, 1) = 1.0f;
	res(2, 0) = -sin(radians);
	res(2, 2) = cos(radians);
	res(3, 3) = 1.0f;

	return res;
}

Matrix<float> MathHelper::Matrix4Dtranslate(float x, float y, float z)
{
	Matrix<float> res(4, 4, 0.0f);
	res(0, 0) = 1.f;
	res(1, 1) = 1.f;
	res(2, 2) = 1.0f;
	res(3, 3) = 1.0f;
	res(0, 3) = x;
	res(1, 3) = y;
	res(2, 3) = z;

	return res;
}

Matrix<float> MathHelper::Matrix4Dscale(float x, float y, float z)
{
	Matrix<float> res(4, 4, 0.0f);
	res(0, 0) = x;
	res(1, 1) = y;
	res(2, 2) = z;
	res(3, 3) = 1.0f;

	return res;
}