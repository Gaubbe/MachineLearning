#include "Matrix.h"
#include <stdexcept>

namespace maths {
Matrix::Matrix(int rows, int columns):
	mRows(rows), mColumns(columns)
{
	this->mElements = new double[GetSize()];
}

Matrix::Matrix(const Matrix& copy):
	mRows(copy.mRows), mColumns(copy.mColumns)
{
	unsigned int size = copy.GetSize();
	this->mElements = new double[size];

	for (unsigned int i = 0; i < size; i++) {
		this->mElements[i] = copy.mElements[i];
	}
}

Matrix::Matrix(Matrix&& other) noexcept
{
	this->mRows = other.mRows;
	this->mColumns = other.mColumns;
	this->mElements = other.mElements;

	other.mElements = nullptr;
	other.mRows = 0;
	other.mColumns = 0;
}

Matrix::~Matrix()
{
	delete[] this->mElements;
}

void Matrix::Add(const Matrix& other)
{
	if(this->mRows != other.mRows || this->mColumns != other.mColumns)
		throw new std::invalid_argument("Matrix a's rows and columns do not match matrix b's rows and columns.");

	unsigned int size = GetSize();
	for (int i = 0; i < size; i++) {
		this->mElements[i] += other.mElements[i];
	}
}

void Matrix::Subtract(const Matrix& other)
{
	if (this->mRows != other.mRows || this->mColumns != other.mColumns)
		throw new std::invalid_argument("Matrix a's rows and columns do not match matrix b's rows and columns.");

	unsigned int size = GetSize();
	for (int i = 0; i < size; i++) {
		this->mElements[i] -= other.mElements[i];
	}
}

void Matrix::Multiply(const Matrix& other)
{
	if (this->mRows != other.mRows || this->mColumns != other.mColumns)
		throw new std::invalid_argument("Matrix a's rows and columns do not match matrix b's rows and columns.");

	unsigned int size = GetSize();
	for (int i = 0; i < size; i++) {
		this->mElements[i] *= other.mElements[i];
	}
}

void Matrix::Divide(const Matrix& other)
{
	if (this->mRows != other.mRows || this->mColumns != other.mColumns)
		throw new std::invalid_argument("Matrix a's rows and columns do not match matrix b's rows and columns.");

	unsigned int size = GetSize();
	for (int i = 0; i < size; i++) {
		this->mElements[i] /= other.mElements[i];
	}
}

void Matrix::Dot(const Matrix& other)
{
	if (other.mRows == this->mColumns) {
		unsigned int newRows = this->mRows;
		unsigned int newColumns = other.mColumns;
		double* newElements = new double[newRows * newColumns];
		for (unsigned int y = 0; y < newRows; y++) {
			for (unsigned int x = 0; x < newColumns; x++) {
				double sum = 0;
				for (unsigned int e = 0; e < this->mColumns; e++) {
					sum += this->mElements[e + y * this->mColumns] * other.mElements[x + e * other.mColumns];
				}
				newElements[x + y * newColumns] = sum;
			}
		}

		this->mRows = newRows;
		this->mColumns = newColumns;
		delete[] this->mElements;
		this->mElements = newElements;
	} else {
		throw new std::invalid_argument("Matrix a's columns do not match matrix b's rows.");
	}
}

Matrix Matrix::Add(const Matrix& a, const Matrix& b)
{
	Matrix result(a);
	result.Add(b);
	return result;
}

Matrix Matrix::Subtract(const Matrix& a, const Matrix& b)
{
	Matrix result(a);
	result.Subtract(b);
	return result;
}

Matrix Matrix::Multiply(const Matrix& a, const Matrix& b)
{
	Matrix result(a);
	result.Multiply(b);
	return result;
}

Matrix Matrix::Divide(const Matrix& a, const Matrix& b)
{
	Matrix result(a);
	result.Divide(b);
	return result;
}

Matrix Matrix::Dot(const Matrix& a, const Matrix& b)
{
	Matrix result(a);
	result.Dot(b);
	return result;
}

void Matrix::Transpose()
{
	double* newElements = new double[this->mRows * this->mColumns];
	for (unsigned int x = 0; x < this->mColumns; x++) {
		for (unsigned int y = 0; y < this->mRows; y++) {
			newElements[y + x * this->mRows] = this->mElements[x + y * this->mColumns];
		}
	}

	unsigned int temp = this->mRows;
	this->mRows = mColumns;
	this->mColumns = temp;
	delete[] this->mElements;
	this->mElements = newElements;
}

Matrix Matrix::Transpose(const Matrix& matrix)
{
	Matrix result(matrix);
	result.Transpose();
	return result;
}

Matrix operator+(const Matrix& a, const Matrix& b)
{
	return Matrix::Add(a, b);
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	return Matrix::Subtract(a, b);
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
	return Matrix::Multiply(a, b);
}

Matrix operator/(const Matrix& a, const Matrix& b)
{
	return Matrix::Divide(a, b);
}

Matrix operator^(const Matrix& a, const Matrix& b)
{
	return Matrix::Dot(a, b);
}

void Matrix::operator+=(const Matrix& other)
{
	this->Add(other);
}

void Matrix::operator-=(const Matrix& other)
{
	this->Subtract(other);
}

void Matrix::operator*=(const Matrix& other)
{
	this->Multiply(other);
}

void Matrix::operator/=(const Matrix& other)
{
	this->Divide(other);
}

void Matrix::operator^=(const Matrix& other)
{
	this->Dot(other);
}
}
