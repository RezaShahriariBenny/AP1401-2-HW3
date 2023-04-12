#ifndef MATRIX_H
#define MATRIX_H
#ifndef MATRIX_H
#define MATRIX_H
#include <initializer_list>
#include <compare>
#include <iostream>

class Matrix {
public:
	/* Constructors and Class Functions */

	Matrix(); //constructor
	~Matrix(); //destructor
	Matrix(int size); //constructor with 1 parameter
	Matrix(int row, int column); //constructor with 2 parameter
	Matrix(std::initializer_list<std::initializer_list<double>> a); //constructor initializer list
	Matrix(const Matrix& m); //copy constructor
	int getRowSize(); //Row Size
	int getColSize(); //Col Size
	int getRowCapacity(); //Row Cap
	int getColCapacity(); //Col Cap
	int** getMatrix(); //printout matrix
	const Matrix& append(Matrix&, int axis = 0);
	void display() const;

	/* Operators : */

	Matrix operator*(const Matrix&);
	Matrix operator+(const Matrix&);
	Matrix operator-(const Matrix&);
	Matrix& operator+=(const Matrix&);
	Matrix& operator++();
	Matrix operator++(int);
	Matrix& operator--();
	Matrix operator--(int);
	bool operator==(const Matrix&);
	std::partial_ordering operator<=>(const Matrix&);
	Matrix operator|(const Matrix&);
	int* & operator[](const int&);
	Matrix& operator=(const Matrix&);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
		os << "This is the Matrix :" << std::endl;
		for (int i{}; i < m.m_row; i++) {
			for (int j{}; j < m.m_column; j++) {
				os << m.matrix[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}





private:
	int** matrix{};
	int m_row{};
	int m_column{};



};


#endif // !MATRIX_H



#endif // !MATRIX_H