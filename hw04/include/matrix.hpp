#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <cstdlib>

class Matrix
{
private:
    size_t rows;
    size_t cols;
    std::vector<int> data;

public:
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    int Get(int row, int col) const;
    void Set(int row, int col, int value);
    size_t RowSize() const;
    size_t ColumnSize() const;
    Matrix SequentialMul(const Matrix &other) const;
    Matrix MultiThreadMul(const Matrix &other) const;
    bool operator==(const Matrix &other) const;
};
#endif // MATRIX_HPP