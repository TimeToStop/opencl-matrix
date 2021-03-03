#include "matrixtest.h"

MatrixTest::MatrixTest(const Matrix& a, const Matrix& b, const Matrix& c):
    _a(a),
    _b(b),
    _c(c)
{
}

MatrixTest::MatrixTest(const MatrixTest& other):
    _a(other._a),
    _b(other._b),
    _c(other._c)
{
}

MatrixTest::MatrixTest(MatrixTest&& other) noexcept:
    _a(std::move(other._a)),
    _b(std::move(other._b)),
    _c(std::move(other._c))
{
}

MatrixTest::~MatrixTest()
{
}

const Matrix& MatrixTest::a() const
{
    return _a;
}

const Matrix& MatrixTest::b() const
{
    return _b;
}

const Matrix& MatrixTest::c() const
{
    return _c;
}
