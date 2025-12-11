#include "matrix.hpp"
#include <stdexcept>
#include <string>
#include <thread>

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(rows * cols)
{
}

Matrix::~Matrix()
{
}

int Matrix::Get(int row, int col) const
{
    return data[row * cols + col];
}

void Matrix::Set(int row, int col, int value)
{
    data[row * cols + col] = value;
}

size_t Matrix::RowSize() const
{
    return rows;
}

size_t Matrix::ColumnSize() const
{
    return cols;
}

Matrix Matrix::SequentialMul(const Matrix &other) const
{
    if (cols != other.rows)
    {
        throw std::invalid_argument("Incompatible matrix sizes for multiplication.");
    }

    Matrix result(rows, other.cols);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < other.cols; ++j)
        {
            int sum = 0;
            for (size_t k = 0; k < cols; ++k)
            {
                sum += Get(i, k) * other.Get(k, j);
            }
            result.Set(i, j, sum);
        }
    }

    return result;
}

Matrix Matrix::MultiThreadMul(const Matrix &other) const
{
    if (cols != other.rows)
    {
        throw std::invalid_argument("Incompatible matrix sizes for multiplication.");
    }

    // 撈出 thread 數量
    size_t num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(num_threads);
    Matrix result(rows, other.cols);

    // 每個 thread 負責的 row 範圍
    size_t rows_per_thread = (rows + num_threads - 1) / num_threads;

    for (size_t t = 0; t < num_threads; ++t)
    {
        size_t start_row = t * rows_per_thread;
        size_t end_row = std::min(start_row + rows_per_thread, rows);
        threads[t] = std::thread([&, start_row, end_row]()
                                 {
        for (size_t i = start_row; i < end_row; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                int sum = 0;
                for (size_t k = 0; k < cols; ++k)
                    sum += Get(i, k) * other.Get(k, j);
                result.Set(i, j, sum);
            }
        } });
    }

    for (auto &th : threads)
        th.join();

    return result;
}

bool Matrix::operator==(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        return false;

    for (size_t r = 0; r < rows; ++r)
        for (size_t c = 0; c < cols; ++c)
            if (Get(r, c) != other.Get(r, c))
                return false;

    return true;
}