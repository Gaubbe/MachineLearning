#pragma once

namespace maths {
class Matrix {
public:
	double* m_Elements;
private:
	unsigned int m_Rows;
	unsigned int m_Columns;
public:
	Matrix(int rows, int columns);
	Matrix(const Matrix& copy);
	~Matrix();

	inline int getRows() const { return m_Rows; }
	inline int getColumns() const { return m_Columns; }
	inline int getSize() const { return m_Rows * m_Columns; }

	//Operations
	void add(const Matrix* other);
	void subtract(const Matrix* other);
	void multiply (const Matrix* other);
	void divide(const Matrix* other);
	void dot(const Matrix* other);

	static Matrix* add(const Matrix* a, const Matrix* b);
	static Matrix* subtract(const Matrix* a, const Matrix* b);
	static Matrix* multiply(const Matrix* a, const Matrix* b);
	static Matrix* divide(const Matrix* a, const Matrix* b);
	static Matrix* dot(const Matrix* a, const Matrix* b);

	void transpose();

	static Matrix* transpose(const Matrix* matrix);

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