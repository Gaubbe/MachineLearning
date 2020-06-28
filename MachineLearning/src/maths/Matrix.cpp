#include "Matrix.h"
#include <immintrin.h>
#include <math.h>
#include <algorithm>

#include <vector>
#include <thread>

#define MAX_THREADS 4

namespace maths {
Matrix::Matrix(int rows, int columns):
	mRows(rows), mColumns(columns)
{
	this->mElements = new double[GetSize()];
}

Matrix::Matrix(const Matrix& copy):
	mRows(copy.GetRows()), mColumns(copy.GetColumns())
{
	unsigned int size = copy.GetSize();
	this->mElements = new double[size];

	for (unsigned int i = 0; i < size; i++) {
		this->mElements[i] = copy.mElements[i];
	}
}

Matrix::Matrix(Matrix&& other) noexcept
{
	this->mRows = other.GetRows();
	this->mColumns = other.GetColumns();
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
	unsigned int size = GetSize();
	for (unsigned int i = 0; i < size; i++) {
		this->mElements[i] += other.mElements[i];
	}
}

void Matrix::Subtract(const Matrix& other)
{
	unsigned int size = GetSize();
	for (unsigned int i = 0; i < size; i++) {
		this->mElements[i] -= other.mElements[i];
	}
}

void Matrix::Multiply(const Matrix& other)
{
	unsigned int size = GetSize();
	for (unsigned int i = 0; i < size; i++) {
		this->mElements[i] *= other.mElements[i];
	}
}

void Matrix::Divide(const Matrix& other)
{
	unsigned int size = GetSize();
	for (unsigned int i = 0; i < size; i++) {
		this->mElements[i] /= other.mElements[i];
	}
}

void Matrix::Dot(const Matrix& other)
{
	if (other.GetRows() == this->mColumns) {
		unsigned int newRows = this->mRows;
		unsigned int newColumns = other.GetColumns();
		double* newElements = new double[newRows * newColumns];
		
		CalcualteDotProduct(*this, other, newElements);

		this->mRows = newRows;
		this->mColumns = newColumns;
		delete[] this->mElements;
		this->mElements = newElements;
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

void Matrix::CalcualteDotProduct(const Matrix& a, const Matrix& b, double* result)
{
	std::vector<std::thread> threads;
	
	float rowsPerThread = (float)a.mRows / MAX_THREADS;

	for (unsigned int i = 0; i < MAX_THREADS; i++) {
		unsigned int startRow = round(rowsPerThread) * i;
		unsigned int endRows = round(rowsPerThread) * (i + 1);

		threads.push_back(std::thread(Matrix::CalculateSectionOfDotProduct, a, b, startRow, endRows, result));
	}

	for (unsigned int i = 0; i < MAX_THREADS; i++)
		threads[i].join();
}

void Matrix::CalculateSectionOfDotProduct(const Matrix& a, const Matrix& b, unsigned int startRow, unsigned int endRow, double* result)
{
	for (unsigned int i = startRow; i < endRow; i++) {
		for (unsigned int j = 0; j < b.mColumns; j+=4) {
			unsigned short elementsToWrite = (unsigned short)std::min(4, 4 - (((int)j + 4) - (int)b.mColumns));

			__m256d _sum = _mm256_setzero_pd();
			for (unsigned int k = 0; k < a.mColumns; k++) {
				__m256d _a = _mm256_set1_pd(a.mElements[k + i * a.mColumns]);
				__m256d _b = _mm256_load_pd(b.mElements + (j + k * b.mColumns));
				_sum = _mm256_add_pd(_sum, _mm256_mul_pd(_a, _b));
			}

			for(unsigned short e = 0; e < elementsToWrite; e++)
				result[j + e + i * b.mColumns] = _sum.m256d_f64[e];
		}
	}
}
}
