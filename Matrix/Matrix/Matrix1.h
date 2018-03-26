//#ifndef MATRIX1_H
//#define MATRIX1_H
//
//namespace mx
//{
//	template<typename T>
//	class Matrix
//	{
//	private:
//		T **matrix;
//		int rows;
//		int cols;
//	public:
//		Matrix();
//		Matrix(int rows, int cols, bool identity = false);
//		Matrix(const Matrix &m);
//		~Matrix();
//
//		void setRows(int rows);
//		int getRows();
//		void setCols(int cols);
//		int getCols();
//
//		//		Matrix transpose();
//		//		double determinant();
//
//		T* operator[](int index)
//		{
//			if (index < rows)
//				return matrix[index];
//			else
//				return nullptr;
//		}
//
//		//		Matrix& operator=(const Matrix &m);
//		//		Matrix& operator+=(const Matrix &rv);
//		//		friend Matrix operator+(Matrix lv, const Matrix	&rv);
//		//		Matrix& operator-=(const Matrix &rv);
//		//		friend Matrix operator-(Matrix lv, const Matrix	&rv);
//		//		Matrix& operator*=(const Matrix &rv);
//		//		friend Matrix operator*(Matrix lv, const Matrix	&rv);
//		//		Matrix& operator/=(const Matrix &rv);
//		//		friend Matrix operator/(Matrix lv, const Matrix	&rv);
//	};
//
//	template<typename T>
//	inline Matrix<T>::Matrix()
//	{
//		rows = cols = 0;
//		matrix = nullptr;
//	}
//
//	template<typename T>
//	inline Matrix<T>::Matrix(int rows, int cols, bool identity)
//	{
//		// if not zero
//		if (rows > 0 && cols > 0)
//		{
//			this->rows = rows;
//			this->cols = cols;
//
//			matrix = new T *[rows];
//			for (int i = 0; i < cols; i++)
//				matrix[i] = new T[cols];
//
//			if (identity && rows == cols)
//			{
//				for (int i = 0; i < rows; i++)
//				{
//					for (int j = 0; j < cols; j++)
//					{
//						if (i == j)
//							matrix[i][j] = 1;
//						else
//							matrix[i][j] = 0;
//					}
//				}
//			}
//			else
//			{
//				for (int i = 0; i < rows; i++)
//					for (int j = 0; j < cols; j++)
//						matrix[i][j] = 0;
//			}
//		}
//		else
//		{
//			this->rows = this->cols = 0;
//			this->matrix = nullptr;
//		}
//	}
//
//	template<typename T>
//	inline Matrix<T>::Matrix(const Matrix & m)
//	{
//
//	}
//
//	template<typename T>
//	inline Matrix<T>::~Matrix()
//	{
//		for (int i = 0; i < rows; i++)
//			delete[] matrix[i];
//		delete[] matrix;
//	}
//
//	template<typename T>
//	inline void Matrix<T>::setRows(int rows)
//	{
//		this->rows = rows;
//	}
//
//	template<typename T>
//	inline int Matrix<T>::getRows()
//	{
//		return rows;
//	}
//
//	template<typename T>
//	inline void Matrix<T>::setCols(int cols)
//	{
//		this->cols = cols;
//	}
//
//	template<typename T>
//	inline int Matrix<T>::getCols()
//	{
//		return cols;
//	}
//}
//
//
//#endif // !MATRIX1_H
//
