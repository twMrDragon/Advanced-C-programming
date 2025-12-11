#include <iostream>
#include "matrix.hpp"
#include <cstdlib>
#include <ctime>
#include "Stopwatch.h"
#include <functional>
#include <thread>
#include <fstream>

template <typename T>
struct MeasureResult
{
    T value;
    double time_ms;
};

void PrintMatrix(const Matrix &matrix)
{
    for (size_t i = 0; i < matrix.RowSize(); ++i)
    {
        for (size_t j = 0; j < matrix.ColumnSize(); ++j)
        {
            std::cout << matrix.Get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
void FillMatrix(Matrix &matrix, int min, int max)
{
    for (size_t i = 0; i < matrix.RowSize(); ++i)
    {
        for (size_t j = 0; j < matrix.ColumnSize(); ++j)
        {
            int value = min + rand() % (max - min + 1);
            matrix.Set(i, j, value);
        }
    }
}
template <typename T>
MeasureResult<T> MeasureTime(std::function<T()> func)
{
    Stopwatch stopwatch;
    T result = func();
    double end = stopwatch.read();

    return MeasureResult<T>{result, end * 1000.0};
}

void WriteTestData(std::vector<int> sizes, std::vector<double> seq_times, std::vector<double> mt_times)
{
    std::ofstream file("output.csv");
    file << "Size,SequentialTime(ms),MultiThreadTime(ms)\n";
    for (size_t i = 0; i < sizes.size(); ++i)
    {
        file << sizes[i] << "," << seq_times[i] << "," << mt_times[i] << "\n";
    }
    file.close();
}

void TEST()
{
    size_t n = 1000;
    std::vector<int> sizes;
    std::vector<double> seq_times;
    std::vector<double> mt_times;

    for (size_t i = 10; i <= 1000; i += 10)
    {
        std::cout << "Size = " << i << " ..." << std::endl;
        Matrix matrix1(n, i);
        FillMatrix(matrix1, 1, 99);
        Matrix matrix2(i, n);
        FillMatrix(matrix2, 1, 99);

        MeasureResult<Matrix> result1 = MeasureTime<Matrix>([&]
                                                            { return matrix1.SequentialMul(matrix2); });
        MeasureResult<Matrix> result2 = MeasureTime<Matrix>([&]
                                                            { return matrix1.MultiThreadMul(matrix2); });
        sizes.push_back(i);
        seq_times.push_back(result1.time_ms);
        mt_times.push_back(result2.time_ms);
    }

    WriteTestData(sizes, seq_times, mt_times);
}

int main()
{
    srand(time(0));

    Matrix matrix1(1000, 500);
    FillMatrix(matrix1, 1, 99);
    Matrix matrix2(500, 1000);
    FillMatrix(matrix2, 1, 99);

    // Matrix result1 = matrix1.SequentialMul(matrix2);
    // Matrix result2 = matrix1.MultiThreadMul(matrix2);
    // std::cout << (result1 == result2) << std::endl;

    TEST();

    return 0;
}
