#include "../include/matrix.h"
#include <algorithm>
#include <iostream>
#include <compare>
#include <cmath>
/* Constructors and Class Functions */
Matrix::Matrix() : m_row{0} , m_column{0} {}

Matrix::~Matrix() {
	for (int i{}; i < getRowSize(); i++)
		delete[] matrix[i];
	delete[] matrix;
}

Matrix::Matrix(int size) : Matrix(size , size) {
}

Matrix::Matrix(int row, int column) : m_row{ row }, m_column{ column }{

	matrix = new int* [m_row];

	for (int i{}; i < m_row; i++)
		matrix[i] = new int[m_column];

	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			matrix[i][j] = 0;
		}
	}


}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> a) {
	int row = a.size();
	int col{};
	for (auto& r : a) {
		for (auto& c : r) {
			col++;
		}
		break;
	}
	m_row = row;
	m_column = col;
	matrix = new int* [row];
	for (int i{}; i < row; i++)
		matrix[i] = new int[col];
	int i{};
	int j{};
	for (auto& r : a) {
		for (auto& p : r) {
			matrix[i][j] = p;
			j++;
		}
		j = 0;
		i++;
	}


}

Matrix::Matrix(const Matrix& m) {
	m_row =  m.m_row ;
	m_column = m.m_column ;
	matrix = new int* [m.m_row];
	for (int i{}; i < m.m_row; i++)
		matrix[i] = new int[m.m_column];
	for (int i{}; i < m.m_row; i++) {
		for (int j{}; j < m.m_column; j++) {
			matrix[i][j] = m.matrix[i][j];
		}
	}

}

int Matrix::getRowSize() {
	return m_row;


}

int Matrix::getColSize() {
	return m_column;

}

int Matrix::getRowCapacity() {
	for (int i{}; i < m_row + 2; i++) {
		if (pow(2,i) >= m_row && i != 0) {
			return pow(2,i);
		}
	}
}

int Matrix::getColCapacity() {
	for (int i{}; i < m_column + 2; i++) {
		if (pow(2,i) >= m_column && i != 0) {
			return pow(2,i);
		}
	}
}

int** Matrix::getMatrix() {
	
	return matrix;

}

const Matrix& Matrix::append(Matrix &m , int axis) {
	if (axis == 1) {
		Matrix temp(getRowSize() + m.getRowSize(), getColSize());

		for (int i{}; i < getRowSize(); i++) {
			for (int j{}; j < getColSize(); j++) {
				temp.matrix[i][j] = matrix[i][j];
				temp.matrix[i + m.getRowSize()][j] = m.matrix[i][j];
			}
		}
		
		//for (int i{}; i < getRowSize(); i++) {
		//	delete[] matrix[i];
		//}
		//delete[] matrix;

		//matrix = new int* [getRowSize() + m.getRowSize()];

		//for (int i{}; i < (getRowSize() + m.getRowSize()); i++) {
		//	matrix[i] = new int [getColSize() + m.getColSize()];
		//}

		for (int i{}; i < getRowSize(); i++)
			delete[] matrix[i];
		delete[] matrix;

		matrix = new int* [getRowSize() + m.getRowSize()];
		for (int p{}; p < (getRowSize() + m.getRowSize()); p++) {
			matrix[p] = new int[getColSize()];
		}

		(*this) = temp;

		return *this;

		//int p{};
		//for (; i < (getRowSize() + m.getRowSize()); i++) {
		//	for (int j{}; j < getColSize(); j++) {
		//		matrix[i][j] = temp[p][j];
		//	}
		//	p++;
		//	if (p == getRowSize())
		//		break;
		//}

		/*matrix = temp;*/

		//for (int i{}; i < getRowSize(); i++) {
		//	delete[] temp[i];
		//}
		//delete[] temp;

		//for (int i{}; i < (getRowSize() + m.getRowSize()); i++) {
		//	for (int j{}; j < (getColSize() + m.getColSize()); j++) {
		//		std::cout << matrix[i][j] << " ";
		//	}
		//	std::cout << std::endl;
		//}
	}
	if (axis == 0) {

		Matrix temp(getRowSize(), getColSize() + m.getColSize());

		for (int i{}; i < getRowSize(); i++) {
			for (int j{}; j < getColSize(); j++) {
				temp[i][j] = matrix[i][j];
				temp[i][j + m.getColSize()] = m.matrix[i][j];
				
			}
		}

		for (int i{}; i < getRowSize(); i++)
			delete[] matrix[i];
		delete[] matrix;

		matrix = new int* [getRowSize()];
		for (int p{}; p < getRowSize(); p++) {
			matrix[p] = new int[getColSize() + m.getColSize()];
		}

		(*this) = temp;


		return *this;

	}

}

void Matrix:: display() const {
	std::cout << (*this);
}

//const Matrix& Matrix::append(Matrix& m, int p) {
//	append(m);
//	return (*this);
//}

/* Operators */

Matrix Matrix::operator*(const Matrix& m) {
	if (m_column != m.m_row)
		throw ("Matrix Size is invalid");
	Matrix mul (m_row, m.m_column);
	for (int i{}; i < m_row; i++){
		for (int j{} ; j < m.m_column; j++){
			for (int k {}; k < m.m_row; k++){
				mul.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
			}
		}
	}
	return mul;
}

Matrix Matrix::operator+(const Matrix& m)
{
	//Sizes should match
	if (!(m_row == m.m_row && m_column == m.m_column))
		throw("Invalid Summation");
	// To store the sum of Matrices
	Matrix sum(m_row, m_column);

	// Traverse the Matrix x
	for (int i = 0; i < m_row; i++) {
		for (int j = 0; j < m_column; j++) {

			// Add the corresponding
			// blocks of Matrices
			sum.matrix[i][j] = matrix[i][j]+ m.matrix[i][j];
		}
	}
	return sum;
}

Matrix Matrix::operator-(const Matrix& m) {
	//Sizes should match
	if (!(m_row == m.m_row && m_column == m.m_column))
		throw("Invalid difference");
	// To store the sum of Matrices
	Matrix diff(m_row, m_column);

	// Traverse the Matrix x
	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {

			// Add the corresponding
			// blocks of Matrices
			diff.matrix[i][j] = matrix[i][j] - m.matrix[i][j];
		}
	}
	return diff;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (!(m_row == m.m_row && m_column == m.m_column))
		throw ("Invalid Difference");
	Matrix sum{*this};

	sum = (*this) + m;


	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			matrix[i][j] = sum.matrix[i][j];
		}
	}
	return *this;
}

Matrix& Matrix::operator++() {

	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			matrix[i][j] = matrix[i][j] + 1;
		}
	}
	return *this;
}

Matrix Matrix::operator++(int) {

	Matrix copy{ *this };

	++* this;

	return copy;
	//Matrix copy{ *this };
	//return ++*this;
	//return copy;
}

Matrix& Matrix::operator--() {
	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			matrix[i][j] = matrix[i][j] - 1;
		}
	}
	return *this;

}

Matrix Matrix::operator--(int) {
	Matrix copy{ *this };
	--* this;
	return copy;
}

bool Matrix::operator==(const Matrix& m) {
	if (m_row != m.m_row || m_column != m.m_column)
		throw("invalid Comparison");
	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			if (matrix[i][j] != m.matrix[i][j])
				return false;
		}
	}
	return true;
}

std::partial_ordering Matrix :: operator<=>(const Matrix& m) {
	int sum{};
	int sum2{};
	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			sum += matrix[i][j];
		}
	}

	for (int i{}; i < m.m_row; i++) {
		for (int j{}; j < m.m_column; j++) {
			sum2 += m.matrix[i][j];
		}
	}

	return sum <=> sum2;
}

Matrix Matrix::operator|(const Matrix& m) {
	if (m_row != m_column)
		throw("A is Not Square");
	double A[m_row][m_column];
	double b[m.m_row][1];

	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			A[i][j] = static_cast <double> (matrix[i][j]);
		}
	}

	for (int i{}; i < m.m_row; i++) {
		for (int j{}; j < m.m_column; j++) {
			b[i][j] = static_cast <double> (m.matrix[i][j]);
		}
	}

	int n{ m_row };
	for (int k{}; k < n - 1; k++) {
		for (int i = k + 1; i < n; i++) {
			double factor = A[i][k] / A[k][k];
			for (int j = k + 1; j < n; j++) {
				A[i][j] = A[i][j] - factor * A[k][j];
			}
			b[i][0] = b[i][0] - factor * b[k][0];
		}
	}

	// Backward substitution
	double ex[n][1]{};
	ex[n - 1][0] = b[n - 1][0] / A[n - 1][n - 1];
	for (int i = n - 2; i >= 0; i--) {
		double sum = b[i][0];
		for (int j = i + 1; j < n; j++) {
			sum = sum - A[i][j] * ex[j][0];
		}
		ex[i][0] = sum / A[i][i];
	}

	//for (int i{}; i < n; i++) {
	//	for (int j{}; j < 1; j++) {
	//		std::cout << ex[i][j] << " ";
	//	}
	//	std::cout << std::endl;
	//}
	Matrix x(m_row, 1);
	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			x.matrix[i][j] =  static_cast <int> (std::round(ex[i][j]));
		}
	}
	return x;
}

int*& Matrix::operator [](const int& index) {
	return matrix[index];
}

Matrix& Matrix::operator=(const Matrix& m) {
	if (m_row == 0 || m_column == 0) {
		matrix = new int* [m.m_row];
		for (int i{}; i < m.m_row; i++) {
			matrix[i] = new int[m.m_column];
		}
	}
	m_row = m.m_row;
	m_column = m.m_column;
	for (int i{}; i < m_row; i++) {
		for (int j{}; j < m_column; j++) {
			matrix[i][j] = m.matrix[i][j];
		}
	}
	return *this;

}

