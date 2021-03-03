#pragma once
#include <vector>

#include "../src/matrix.h"

class MatrixTest
{
public:
	MatrixTest(const Matrix& a, const Matrix& b, const Matrix& c);
	MatrixTest(const MatrixTest& other);
	MatrixTest(MatrixTest&& other) noexcept;
	~MatrixTest();

	const Matrix& a() const;
	const Matrix& b() const;
	const Matrix& c() const;

private:
	Matrix _a;
	Matrix _b;
	Matrix _c;
};

