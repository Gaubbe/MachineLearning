#pragma once

namespace maths {
class Matrix {
public:
	double* mElements;
private:
	unsigned int mRows;
	unsigned int mColumns;
public:
	Matrix(int rows, int columns);
	Matrix(const Matrix& copy);
	Matrix(Matrix&& other) noexcept;
	~Matrix();

	inline int GetRows() const { return mRows; }
	inline int GetColumns() const { return mColumns; }
	inline int GetSize() const { return mRows * mColumns; }

	//Operations
	void Add(const Matrix& other);
	void Subtract(const Matrix& other);
	void Multiply (const Matrix& other);
	void Divide(const Matrix& other);
	void Dot(const Matrix& other);

	static Matrix Add(const Matrix& a, const Matrix& b);
	static Matrix Subtract(const Matrix& a, const Matrix& b);
	static Matrix Multiply(const Matrix& a, const Matrix& b);
	static Matrix Divide(const Matrix& a, const Matrix& b);
	static Matrix Dot(const Matrix& a, const Matrix& b);

	void Transpose();

	static Matrix Transpose(const Matrix& matrix);

	//Operator overloads
	friend Matrix operator+(const Matrix& a, const Matrix& b);
	friend Matrix operator-(const Matrix& a, const Matrix& b);
	friend Matrix operator*(const Matrix& a, const Matrix& b);
	friend Matrix operator/(const Matrix& a, const Matrix& b);
	friend Matrix operator^(const Matrix& a, const Matrix& b);

	void operator+=(const Matrix& other);
	void operator-=(const Matrix& other);
	void operator*=(const Matrix& other);
	void operator/=(const Matrix& other);
	void operator^=(const Matrix& other);
};
}