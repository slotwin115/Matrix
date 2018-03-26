#ifndef MATRIX_H 
#define MATRIX_H

#include <vector>
#include <typeinfo>

namespace mx
{
	template<typename T>
	class Matrix
	{
	private:
		std::vector<std::vector<T>> matrix;
		int rows, cols;
		void clear();

	public:
		Matrix();
		Matrix(int rows, int cols, bool identity = false);
		Matrix(const Matrix<T> &m);
		~Matrix();

		void setRows(int rows);
		int getRows() const;
		void setCols(int cols);
		int getCols() const;

		Matrix<T> transpose();
		double determinant();
		Matrix<T> inverse();

		std::vector<T>& operator[](int index);
		const std::vector<T>& operator[](int index) const;
		Matrix<T>& operator=(const Matrix<T> &m);
		Matrix<T>& operator+=(const Matrix<T> &rv);
		Matrix<T>& operator-=(const Matrix<T> &rv);
		Matrix<T>& operator*=(const Matrix<T> &rv);
		Matrix<T>& operator/=(const Matrix<T> &rv);

		template<typename U>
		Matrix<T>& operator*=(const U &rv);
		template<typename U>
		Matrix<T>& operator/=(const U &rv);
	};

	template<typename T>
	mx::Matrix<T> operator+(mx::Matrix<T> lv, const mx::Matrix<T> &rv);
	template<typename T>
	Matrix<T> operator-(Matrix<T> lv, const Matrix<T> &rv);
	template<typename T>
	Matrix<T> operator*(Matrix<T> lv, const Matrix<T> &rv);
	template<typename T, typename U>
	Matrix<T> operator*(Matrix<T> lv, const U &rv);
	template<typename T, typename U>
	Matrix<T> operator/(Matrix<T> lv, const U &rv);
	template<typename T, typename U>
	Matrix<T> operator*(const U &rv, Matrix<T> lv);



	template<typename T>
	inline Matrix<T>::Matrix()
	{
		rows = cols = 0;
	}

	template<typename T>
	inline Matrix<T>::Matrix(int rows, int cols, bool identity)
	{
		if (rows > 0 && cols > 0)
		{
			this->rows = rows;
			this->cols = cols;

			matrix.resize(rows);
			std::vector<std::vector<T>>::iterator mit;
			for (mit = matrix.begin(); mit != matrix.end(); mit++)
				mit->resize(cols);

			if (identity && rows == cols)
			{
				for (int i = 0; i < rows; i++)
					matrix[i][i] = 1;
			}
		}
		else
		{
			this->rows = this->cols = 0;
		}
	}

	template<typename T>
	inline Matrix<T>::Matrix(const Matrix<T> &m)
	{
		*this = m;
	}

	template<typename T>
	inline Matrix<T>::~Matrix()
	{
		clear();
	}

	template<typename T>
	inline void Matrix<T>::clear()
	{
		rows = cols = 0;
		std::vector<std::vector<T>>::iterator mit;
		for (mit = matrix.begin(); mit != matrix.end(); mit++)
			mit->clear();
		matrix.clear();
	}

	template<typename T>
	inline void Matrix<T>::setRows(int rows)
	{
		if (rows > 0)
		{
			this->rows = rows;
			matrix.resize(rows);
		}
		else
		{
			this->rows = 0;
		}
	}

	template<typename T>
	inline int Matrix<T>::getRows() const
	{
		return rows;
	}

	template<typename T>
	inline void Matrix<T>::setCols(int cols)
	{
		if (cols > 0)
		{
			this->cols = cols;
			for (int i = 0; i < rows; i++)
				matrix[i].resize(cols);
		}
		else
		{
			this->cols = 0;
			matrix.resize(cols);
		}
	}

	template<typename T>
	inline int Matrix<T>::getCols() const
	{
		return cols;
	}

	template<typename T>
	inline Matrix<T> Matrix<T>::transpose()
	{
		Matrix<T> t(cols, rows);
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				t[j][i] = matrix[i][j];
		
		return t;
	}

	template<typename T>
	inline double Matrix<T>::determinant()
	{
		double det = 1.0;

		if (rows > 0 && cols > 0 && rows == cols)
		{
			if (rows == 1)
			{
				det = matrix[0][0];
			}
			else
			{
				//LU
				std::vector<std::vector<T>> matrixU;
				matrixU = matrix;
				double ratio;

				for (int i = 0; i < rows; i++)
				{
					for (int j = 0; j < i; j++)
					{
						if (i > 0)
						{
							ratio = matrixU[i][j] / matrixU[j][j];
							for (int k = 0; k < cols; k++)
								matrixU[i][k] += matrixU[j][k] * ratio * -1;
						}
						else
							continue;
					}
				}

				for (int i = 0; i < rows; i++)
					det *= matrixU[i][i];

				return det;
			}
		}

		return 0.0;
	}

	template<typename T>
	Matrix<T> Matrix<T>::inverse()
	{
		T det = determinant();
		if (det)
		{
			Matrix<T> adjugateMatrix(rows, cols), tmp(rows - 1, cols - 1);
			for (int I = 0; I < rows; I++)
			{
				for (int J = 0; J < rows; J++)
				{
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < rows; j++)
							if (i != I && j != J)
							{
								if(i > I && j < J)
									tmp[i - 1][j] = matrix[i][j];
								else if (i < I && j > J)
									tmp[i][j - 1] = matrix[i][j];
								else if(i > I && j > J)
									tmp[i - 1][j - 1] = matrix[i][j];
								else
									tmp[i][j] = matrix[i][j];
							}

					T tmpDet = tmp.determinant();
					if ((I + J) % 2 != 0)
						tmpDet *= -1;

					adjugateMatrix[I][J] = tmpDet;
				}
			}

			return adjugateMatrix.transpose() * 1 / det;
		}



		return Matrix<T>();
	}

	template<typename T>
	inline std::vector<T>& Matrix<T>::operator[](int index)
	{
		return matrix[index];
	}

	template<typename T>
	inline const std::vector<T>& Matrix<T>::operator[](int index) const
	{
		return matrix[index];
	}

	template<typename T>
	inline Matrix<T>& Matrix<T>::operator=(const Matrix<T> &m)
	{
		setRows(m.getRows());
		setCols(m.getCols());
		
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				this->matrix[i][j] = m[i][j];

		return *this;
	}

	template<typename T>
	inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T> &rv)
	{
		if (rows == rv.getRows() && cols == rv.getCols())
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < rows; j++)
					matrix[i][j] += rv[i][j];
		}

		return *this;
	}

	template<typename T>
	inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T> &rv)
	{
		if (rows == rv.getRows() && cols == rv.getCols())
		{
			for (int i = 0; i < rows; i++)
				for (int j = 0; j < rows; j++)
					matrix[i][j] -= rv[i][j];
		}

		return *this;
	}

	template<typename T>
	inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T> &rv)
	{
		if (cols == rv.getRows())
		{
			Matrix<T> tmp = *this;
			setCols(rv.getCols());
			int innerD = rv.getRows();
			T accumulator = 0;

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					for (int k = 0; k < innerD; k++)
					{
						accumulator += (tmp[i][k] * rv[k][j]);
					}
					matrix[i][j] = accumulator;
					accumulator = 0;
				}
			}
		}

		return *this;
	}

	template<typename T>
	inline Matrix<T>& Matrix<T>::operator/=(const Matrix<T> &rv)
	{
		if (cols == rv.getRows())
		{
			Matrix<T> tmp = *this;
			setCols(rv.getCols());
			int innerD = rv.getRows();
			T accumulator = 0;

			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					for (int k = 0; k < innerD; k++)
					{
						accumulator += (tmp[i][k] / rv[k][j]);
					}
					matrix[i][j] = accumulator;
					accumulator = 0;
				}
			}
		}

		return *this;
	}

	template<typename T>
	template<typename U>
	inline Matrix<T>& Matrix<T>::operator*=(const U & rv)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < rows; j++)
				matrix[i][j] *= rv;

		return *this;
	}

	template<typename T>
	template<typename U>
	Matrix<T>& Matrix<T>::operator/=(const U &rv)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < rows; j++)
				matrix[i][j] /= rv;

		return *this;
	}

	template<typename T>
	Matrix<T> operator+(Matrix<T> lv, const Matrix<T>& rv)
	{
		lv += rv;
		return lv;
	}

	template<typename T>
	Matrix<T> operator-(Matrix<T> lv, const Matrix<T> &rv)
	{
		lv -= rv;
		return lv;
	}

	template<typename T>
	Matrix<T> operator*(Matrix<T> lv, const Matrix<T> &rv)
	{
		lv *= rv;
		return lv;
	}

	template<typename T, typename U>
	Matrix<T> operator*(Matrix<T> lv, const U &rv)
	{
		lv *= rv;
		return lv;
	}

	template<typename T, typename U>
	Matrix<T> operator/(Matrix<T> lv, const U &rv)
	{
		lv /= rv;
		return lv;
	}

	template<typename T, typename U>
	Matrix<T> operator*(const U &rv, Matrix<T> lv)
	{
		lv *= rv;
		return lv;
	}
}

#endif // !MATRIX_H

