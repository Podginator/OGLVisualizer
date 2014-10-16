
#ifndef MATRIX_C_GUARD
#define MATRIX_C_GUARD

#include "Matrix.h"


//Constructor, Destructor.
template <typename Type> Matrix<Type>::Matrix(size_t rows, size_t col, const Type& init)
{
	_rows = rows;
	_cols = col;
	data = new Type[rows*col];

	//Initialize them 
	for (size_t i = 0; i < rows*col; i++)
	{
		data[i] = init;
	}
}

template <typename Type> Matrix<Type>::~Matrix()
{
	delete[] data;
}

template <typename Type> Matrix<Type>::Matrix(const Matrix<Type>& copy)
{
	HardCopy(copy);
}

template <typename Type> Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& right)
{
	if (this != &right)
	{
		HardCopy(right);
	}

	return *this;
}

//Get-Set. Individual members.
template <typename Type> const Type Matrix<Type>::operator()(int row, int col) const
{
	return data[_cols* row + col];
}

template <typename Type> Type& Matrix<Type>::operator()(int row, int col)
{
	return data[_cols * row + col];
}

template <typename Type> const size_t Matrix<Type>::getCols() const
{
	return _cols;
}

template <typename Type> const size_t Matrix<Type>::getRows() const
{
	return _rows;
}

template <typename Type> const Matrix<Type> Matrix<Type>::operator+(const Matrix<Type>& right) const
{
	//First check the two are compatible (N.length == N1.length)
	CheckCompatibility(right);

	Matrix<Type> res(_rows, _cols, 0);

	for (size_t i = 0; i < _rows*_cols; i++)
	{
		res.data[i] = data[i] + right.data[i];
	}

	return res;
}

template <typename Type> Matrix<Type>& Matrix<Type>::operator+=(const Matrix<Type>& right)
{

	CheckCompatibility(right);

	for (size_t i = 0; i < _rows; i++)
	{
		data[i] += right[i];
	}

	return *this;
}

template <typename Type> const Matrix<Type> Matrix<Type>::operator-(const Matrix<Type>& right) const
{
	CheckCompatibility(right);

	Matrix res(_rows, _cols, 0);

	for (size_t i = 0; i < _rows*_cols; i++)
	{
		res.data[i] = data[i] - right.data[i];
	}

	return res;
}

template <typename Type> Matrix<Type>& Matrix<Type>::operator-=(const Matrix<Type>& right)
{

	CheckCompatibility(right);

	for (size_t i = 0; i < _rows; i++)
	{
		data[i] -= right.data[i];
	}

	return *this;
}

template <typename Type> const Matrix<Type> Matrix<Type>::operator*(const Matrix<Type>& right) const
{
	if (_cols != right.getRows())
	{
		throw std::invalid_argument("Matrix A Rows not equal to Matrix Bs Rows.");
	}

	Matrix<Type> res = Matrix<Type>(right.getRows(), right.getCols(), 0.f);
	//Iterate first through the columns of our Matrix
	for (size_t i = 0; i < _rows; i++)
	{
		//We have to multiply the first row by colums, so iterate through right colums
		for (size_t j = 0; j < right.getCols(); j++)
		{
			//Then we get each element in the array and dot product them together.
			for (size_t k = 0; k < _cols; k++)
			{
				res(i, j) += data[_cols* i + k] * right(k, j);
			}
		}
	}

	return res;
}

template <typename Type> Matrix<Type>& Matrix<Type>::operator*=(const Matrix<Type>& right)
{
	Matrix result = *this * right;
	*this = result;

	return *this;
}

template <typename Type> const Vec2 Matrix<Type>::operator*(const Vec2& right) const
{
	//Model the Vector as a Matrix (We already deal with these)
	//Column Vector
	Matrix vec = Matrix(2, 1, 0);
	vec(0, 0) = right.X();
	vec(1, 0) = right.Y();
	//Then multiply it as you would a normal Matrix
	vec = (*this) * vec;
	return Vec2(vec(0, 0), vec(1, 0));
}

template <typename Type> const Matrix<Type> Matrix<Type>::operator*(Type right) const
{
	Matrix res(_rows, _cols, 0);

	for (size_t i = 0; i < _rows; i++){
		res.data[i] = data[i] * right;
	}

	return res;
}

template <typename Type> Matrix<Type>& Matrix<Type>::operator*=(Type right)
{
	for (size_t i = 0; i < _rows; i++){
		data[i] *= right;
	}

	return *this;
}

//Calculate the Determinant
//So, this is kind of difficult for a number of reasons
//You need 
template <typename Type> const float Matrix<Type>::Determinant() const
{
	return 0.0f;
}

template <typename Type> Matrix<Type>& Matrix<Type>::inverse()
{

	return *this;
}

template <typename Type> void Matrix<Type>::HardCopy(const Matrix<Type>& copy)
{
	this->_cols = copy._cols;
	this->_rows = copy._rows;

	data = new float[_rows*_cols];

	for (size_t i = 0; i < _rows*_cols; i++)
	{
		data[i] = copy.data[i];
	}
}

template <typename Type> const void Matrix<Type>::CheckCompatibility(const Matrix& check) const
{
	if ((this->_rows != check.getRows()) && (this->_cols != check.getCols()))
	{
		throw std::invalid_argument("Matrix not same length");
	}

}
#endif