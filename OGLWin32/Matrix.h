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

	void HardCopy(const Matrix& copy)
	{
		this->_cols = copy._cols;
		this->_rows = copy._rows;

		data = new float[_rows*_cols];

		for (size_t i = 0; i < _rows*_cols; i++)
		{
			data[i] = copy.data[i];
		}
	}
	void CheckCompatibility(const Matrix& check) const
	{
		if ((this->_rows != check.getRows()) && (this->_cols != check.getCols()))
		{
			throw std::invalid_argument("Matrix not same length");
		}
	}



public:
	//Assume matrix is more than 2x2, for now. 
	Matrix<Type>(size_t rows, size_t cols, const Type& init)
	{
		_rows = rows;
		_cols = cols;
		data = new Type[rows*cols];

		//Initialize them 
		for (size_t i = 0; i < rows*cols; i++)
		{
			data[i] = init;
		}
	}
	//Include Destructor incase it's needed.
	//Make sure to destroy the data when it's gone.
	~Matrix<Type>()
	{
		delete[] data;
	}
	//Copy Constructor
	Matrix<Type>(const Matrix& copy)
	{
		HardCopy(copy);
	}

	Matrix<Type>& operator=(const Matrix& right)
	{
		if (this != &right)
		{
			HardCopy(right);
		}

		return *this;
	}
	//The operations on them should be performed with operator overloads rather than individual functions
	//Matrix -> Matrix
	Matrix<Type> operator+(const Matrix& right) const
	{
		CheckCompatibility(right);
		Matrix<Type> res(_rows, _cols, 0);
		for (size_t i = 0; i < _rows*_cols; i++)
		{
			res.data[i] = data[i] + right.data[i];
		}
		return res;
	}

	Matrix<Type>& operator+=(const Matrix& right)
	{
		CheckCompatibility(right);
		for (size_t i = 0; i < _rows; i++)
		{
			data[i] += right[i];
		}
		return *this;
	}

	Matrix<Type> operator-(const Matrix& right) const
	{
		CheckCompatibility(right);
		Matrix res(_rows, _cols, 0);
		for (size_t i = 0; i < _rows*_cols; i++)
		{
			res.data[i] = data[i] - right.data[i];
		}
		return res;
	}
	Matrix<Type>& operator-=(const Matrix& right)
	{
		CheckCompatibility(right);
		for (size_t i = 0; i < _rows; i++)
		{
			data[i] -= right.data[i];
		}

		return *this;
	}
	Matrix<Type> operator*(const Matrix& right) const
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
	Matrix<Type>& operator*=(const Matrix& right)
	{
		Matrix result = *this * right;
		*this = result;

		return *this;
	}

	//Matrix -> Scalar
	Matrix<Type> operator*(Type right) const
	{
		Matrix res(_rows, _cols, 0);
		for (size_t i = 0; i < _rows; i++){
			res.data[i] = data[i] * right;
		}

		return res;
	}
	Matrix<Type>& operator*=(Type right)
	{
		for (size_t i = 0; i < _rows; i++)
		{
			data[i] *= right;
		}

		return *this;
	}
	//Matrix -> Vector#
	//Vec2 operator*(const Vec2& right) const;
	Vector<Type, 2> operator*(const Vector<Type, 2>& right) const
	{
		//Model the Vector as a Matrix (We already deal with these)
		//Column Vector
		Matrix vec = Matrix(2, 1, 0);
		vec(0, 0) = right.X();
		vec(1, 0) = right.Y();
		//Then multiply it as you would a normal Matrix
		vec = (*this) * vec;
		return Vector<float, 2>(vec(0, 0), vec(1, 0));
	}
	//bool operator
	bool operator!=(const Matrix& right);
	bool operator==(const Matrix& right);

	Matrix<Type>& transpose()
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

	//Inspired by the algorithm posted here 
	//http://paulbourke.net/miscellaneous/determinant/
	float Determinant() const
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
			//create indexes for new matrix.
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
				//Do this recursively until Determinant is found.
				result = result + (pow(-1, c) * (*this)(0, c) * rec.Determinant());
			}
		}
		return result;
	}
	Matrix<Type>& inverse()
	{
		return *this;
	}

	//Get and Set individual setters.
	Type& operator()(int rows, int cols){ return data[_cols * rows + cols]; }
	//Const set.
	Type operator()(int rows, int cols) const { return data[_cols* rows + cols]; }

	size_t getRows() const { return _cols; }
	size_t getCols() const { return _rows; }
};


