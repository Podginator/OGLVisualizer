#pragma once 

#include <stdexcept>
#include "Vector.h"
#include <ppl.h>

template <typename Type>
class Matrix
{
private:
	//use size_T for performant reasons.
	size_t _rows;
	size_t _cols;
	//use 1D array for performance (mild, barely noticeable, cast as the same)
	//Can perform 1 for loop for simple operations
	//Can hard copy and initialize easier. 
	Type* data;

	void HardCopy(const Matrix& copy);
	void CheckCompatibility(const Matrix& check) const;

public:
	//Assume matrix is more than 2x2, for now. 
	Matrix<Type>(size_t rows, size_t cols, const Type& init);
	//Include Destructor incase it's needed.
	//Make sure to destroy the data when it's gone.
	~Matrix<Type>();
	//Copy Constructor
	Matrix<Type>(const Matrix& copy);

	Matrix<Type>& operator=(const Matrix& right);
	//The operations on them should be performed with operator overloads rather than individual functions
	//Matrix -> Matrix
	Matrix<Type> operator+(const Matrix& right) const;
	Matrix<Type>& operator+=(const Matrix& right);
	Matrix<Type> operator-(const Matrix& right) const;
	Matrix<Type>& operator-=(const Matrix& right);
	Matrix<Type> operator*(const Matrix& right) const;
	Matrix<Type>& operator*=(const Matrix& right);

	//Matrix -> Scalar
	Matrix<Type> operator*(Type right) const;
	Matrix<Type>& operator*=(Type right);
	//Matrix -> Vector#
	//Vec2 operator*(const Vec2& right) const;
	Vector<Type,2> operator*(const Vector<Type,2>& right) const;
	//bool operator
	bool operator!=(const Matrix& right);
	bool operator==(const Matrix& right);

	Matrix<Type>& transpose();
	float Determinant() const;
	Matrix<Type>& inverse();

	//Get and Set individual setters.
	Type& operator()(int rows, int cols);
	//Const set.
	Type operator()(int rows, int cols) const;

	size_t getRows() const;
	size_t getCols() const;
};

#include "Matrix.cpp"

