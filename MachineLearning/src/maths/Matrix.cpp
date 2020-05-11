#include "Matrix.h"
#include <stdexcept>

namespace maths {
Matrix::Matrix(int rows, int columns):
	m_Rows(rows), m_Columns(columns)
{
	this->m_Elements = new double[getSize()];
}

Matrix::Matrix(const Matrix& copy):
	m_Rows(copy.getRows()), m_Columns(copy.getColumns())
{
	unsigned int size = copy.getSize();
	this->m_Elements = new double[size];

	for (unsigned int i = 0; i < size; i++) {
		this->m_Elements[i] = copy.m_Elements[i];
	}
}

Matrix::~Matrix()
{
	delete[] this->m_Elements;
}

void Matrix::add(const Matrix* other)
{
	unsigned int size = getSize();
	for (int i = 0; i < size; i++) {
		this->m_Elements[i] += other->m_Elements[i];
	}
}

void Matrix::subtract(const Matrix* other)
{
	unsigned int size = getSize();
	for (int i = 0; i < size; i++) {
		this->m_Elements[i] -= other->m_Elements[i];
	}
}

void Matrix::multiply(const Matrix* other)
{
	unsigned int size = getSize();
	for (int i = 0; i < size; i++) {
		this->m_Elements[i] *= other->m_Elements[i];
	}
}

void Matrix::divide(const Matrix* other)
{
	unsigned int size = getSize();
	for (int i = 0; i < size; i++) {
		this->m_Elements[i] /= other->m_Elements[i];
	}
}

void Matrix::dot(const Matrix* other)
{
	if (other->getRows() == this->m_Columns) {
		unsigned int newRows = this->m_Rows;
		unsigned int newColumns = other->getColumns();
		double* newElements = new double[newRows * newColumns];
		for (unsigned int y = 0; y < newRows; y++) {
			for (unsigned int x = 0; x < newColumns; x++) {
				double sum = 0;
				for (unsigned int e = 0; e < this->m_Columns; e++) {
					sum += this->m_Elements[e + y * this->m_Columns] * other->m_Elements[x + e * other->getColumns()];
				}
				newElements[x + y * newColumns] = sum;
			}
		}

		this->m_Rows = newRows;
		this->m_Columns = newColumns;
		delete[] this->m_Elements;
		this->m_Elements = newElements;
	} else {
		throw new std::invalid_argument("Matrix a's columns do not match matrix b's rows.");
	}
}

Matrix* Matrix::add(const Matrix* a, const Matrix* b)
{
	Matrix* result = new Matrix(*a);
	result->add(b);
	return result;
}

Matrix* Matrix::subtract(const Matrix* a, const Matrix* b)
{
	Matrix* result = new Matrix(*a);
	result->subtract(b);
	return result;
}

Matrix* Matrix::multiply(const Matrix* a, const Matrix* b)
{
	Matrix* result = new Matrix(*a);
	result->multiply(b);
	return result;
}

Matrix* Matrix::divide(const Matrix* a, const Matrix* b)
{
	Matrix* result = new Matrix(*a);
	result->divide(b);
	return result;
}

Matrix* Matrix::dot(const Matrix* a, const Matrix* b)
{
	Matrix* result = new Matrix(*a);
	result->dot(b);
	return result;
}

void Matrix::transpose()
{
	double* newElements = new double[this->m_Rows * this->m_Columns];
	for (unsigned int x = 0; x < this->m_Columns; x++) {
		for (unsigned int y = 0; y < this->m_Rows; y++) {
			newElements[y + x * this->m_Rows] = this->m_Elements[x + y * this->m_Columns];
		}
	}

	unsigned int temp = this->m_Rows;
	this->m_Rows = m_Columns;
	this->m_Columns = temp;
	delete[] this->m_Elements;
	this->m_Elements = newElements;
}

Matrix* Matrix::transpose(const Matrix* matrix)
{
	Matrix* result = new Matrix(*matrix);
	result->transpose();
	return result;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	Matrix* result = Matrix::add(&a, &b);
	Matrix copy(*result);
	delete result;
	return copy;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix* result = Matrix::subtract(&a, &b);
	Matrix copy(*result);
	delete result;
	return copy;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	Matrix* result = Matrix::multiply(&a, &b);
	Matrix copy(*result);
	delete result;
	return copy;
}

Matrix operator/(const Matrix& a, const Matrix& b)
{
	Matrix* result = Matrix::divide(&a, &b);
	Matrix copy(*result);
	delete result;
	return copy;
}

Matrix operator^(const Matrix& a, const Matrix& b)
{
	Matrix* result = Matrix::dot(&a, &b);
	Matrix copy(*result);
	delete result;
	return copy;
}

void Matrix::operator+=(const Matrix& other)
{
	this->add(&other);
}

void Matrix::operator-=(const Matrix& other)
{
	this->subtract(&other);
}

void Matrix::operator*=(const Matrix& other)
{
	this->multiply(&other);
}

void Matrix::operator/=(const Matrix& other)
{
	this->divide(&other);
}

void Matrix::operator^=(const Matrix& other)
{
	this->dot(&other);
}
}
