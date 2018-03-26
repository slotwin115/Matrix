#include "Matrix.h"
#include <iostream>
#include <typeinfo>
#include <string>
#include <ctime>

template<class T>
void print(mx::Matrix<T> &m, std::string msg)
{
	std::cout << "=======================================\n";
	std::cout << msg;
	std::cout << "\nRows = " << m.getRows() << " Cols = " << m.getCols() << "\n\n";
	for (int i = 0; i < m.getRows(); i++)
	{
		for (int j = 0; j < m.getCols(); j++)
			std::cout << m[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "=======================================\n\n";
}

void main()
{
	srand(time(nullptr));
	mx::Matrix<double> m1(3, 3), m2(2, 3);

	for (int i = 0; i < m1.getRows(); i++)
		for (int j = 0; j < m1.getCols(); j++)
			m1[i][j] = rand() % 10;

	for (int i = 0; i < m2.getRows(); i++)
		for (int j = 0; j < m2.getCols(); j++)
			m2[i][j] = rand() % 10;

	mx::Matrix<double> m;

	print(m1, "m1");
	print(m2, "m2");

	m = m2 * m1;

	print(m, "m = m2 * m1");

	m = m1 * m2.transpose();

	print(m, "m = m1 * m2^T");

	getchar();
}