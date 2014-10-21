
#ifndef MATRIX_C_GUARD
#define MATRIX_C_GUARD

#include "Matrix.h"


//Constructor, Destructor.
template <typename Type>
Matrix<Type>::Matrix(size_t rows, size_t col, const Type& init)
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

template <typename Type>
Matrix<Type>::~Matrix()
{
	delete[] data;
}

template <typename Type>
Matrix<Type>::Matrix(const Matrix<Type>& copy)
{
	HardCopy(copy);
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator=(const Matrix<Type>& right)
{
	if (this != &right)
	{
		HardCopy(right);
	}

	return *this;
}

//Get-Set. Individual members.
template <typename Type>
Type Matrix<Type>::operator()(int row, int col) const
{
	return data[_cols* row + col];
}

template <typename Type>
Type& Matrix<Type>::operator()(int row, int col)
{
	return data[_cols * row + col];
}

template <typename Type>
size_t Matrix<Type>::getCols() const
{
	return _cols;
}

template <typename Type>
size_t Matrix<Type>::getRows() const
{
	return _rows;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type>& right) const
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

template <typename Type>
Matrix<Type>& Matrix<Type>::operator+=(const Matrix<Type>& right)
{

	CheckCompatibility(right);

	for (size_t i = 0; i < _rows; i++)
	{
		data[i] += right[i];
	}

	return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type>& right) const
{
	CheckCompatibility(right);

	Matrix res(_rows, _cols, 0);

	for (size_t i = 0; i < _rows*_cols; i++)
	{
		res.data[i] = data[i] - right.data[i];
	}

	return res;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator-=(const Matrix<Type>& right)
{

	CheckCompatibility(right);

	for (size_t i = 0; i < _rows; i++)
	{
		data[i] -= right.data[i];
	}

	return *this;
}

template <typename Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type>& right) const
{
	if (_cols != right._rows)
	{
		throw std::invalid_argument("Matrix A Rows not equal to Matrix Bs Rows.");
	}

	Matrix<Type> res = Matrix<Type>(right._rows, right._cols, 0.f);
	//Iterate first through the columns of our Matrix
	//Use Parallel for to increase speed gains
	concurrency::parallel_for(size_t(0), _rows, [&](size_t i)
	{
		//We have to multiply the first row by colums, so iterate through right colums
		
		for (size_t j = 0; j < right._cols; j++)
		{
			//Store as temp variable to avoid lots of memory writes.
			Type temp = 0.f; 
			for (size_t k = 0; k < _cols; k++)
			{
				temp += data[_cols* i + k] * right(k, j);
			}
			res(i, j) = temp;
		}
	});


	return res;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator*=(const Matrix<Type>& right)
{
	Matrix result = *this * right;
	*this = result;

	return *this;
}

template <typename Type>
Vector<Type, 2> Matrix<Type>::operator*(const Vector<Type, 2>& right) const
{
	//Model the Vector as a Matrix (We already deal with these)
	//Column Vector
	Matrix vec = Matrix(2, 1, 0);
	vec(0, 0) = right.X();
	vec(1, 0) = right.Y();
	//Then multiply it as you would a normal Matrix
	vec = (*this) * vec;
	return Vector<float,2>(vec(0, 0), vec(1, 0));
}


template <typename Type>
Matrix<Type> Matrix<Type>::operator*(Type right) const
{
	Matrix res(_rows, _cols, 0);

	for (size_t i = 0; i < _rows; i++){
		res.data[i] = data[i] * right;
	}

	return res;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::operator*=(Type right)
{
	for (size_t i = 0; i < _rows; i++){
		data[i] *= right;
	}

	return *this;
}

//Inspired by the algorithm posted here 
//http://paulbourke.net/miscellaneous/determinant/
template <typename Type>
float Matrix<Type>::Determinant() const
{
	//First check if it's a square matrix, if not then it can't work.
	if (_rows != _cols)
	{
		throw std::invalid_argument("Cannot determine Determinant of Non-square Matrix");
	}

	//Store result
	float result = 0.f;

	if (_rows == 1)
	{
		return (*this)(0, 0);
	}
	else if (_rows == 2)
	{
		return (*this)(0, 0)*(*this)(1, 1) - (*this)(0, 1)*(*this)(1, 0);
	}
	else
	{
		//create indexes for new array.
		int recI, recj;
		//Set up a new Matrix for recursion.
		Matrix<Type> rec(_rows - 1, _cols - 1, 0);
		for (int c = 0; c < _rows; c++)
		{
			reci = 0;
			for (int i = 1; i < _rows; i++)
			{
				recj = 0;
				for (int j = 0; j < _rows; j++)
				{
					if (j == c)
					{
						continue;
					}
					rec(subi, subj) = (*this)(i, j);
					recj++;
				}
				reci++;
			}
			result =  result + (pow(-1, c) * (*this)(0, c) * rec.Determinant());
		}
	}
	return result;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::inverse()
{

	return *this;
}

template <typename Type>
Matrix<Type>& Matrix<Type>::transpose()
{ 
	for (int i = 0; i < _rows; i++)
	{
		for (int j = 0; j < _cols; j++)
		{
			data[_cols * row + col] = data[_rows * row + col];
		}
	}

	return *this;
}

template <typename Type>
void Matrix<Type>::HardCopy(const Matrix<Type>& copy)
{
	this->_cols = copy._cols;
	this->_rows = copy._rows;

	data = new float[_rows*_cols];

	for (size_t i = 0; i < _rows*_cols; i++)
	{
		data[i] = copy.data[i];
	}
}

template <typename Type>
void Matrix<Type>::CheckCompatibility(const Matrix& check) const
{
	if ((this->_rows != check.getRows()) && (this->_cols != check.getCols()))
	{
		throw std::invalid_argument("Matrix not same length");
	}



}
#endif