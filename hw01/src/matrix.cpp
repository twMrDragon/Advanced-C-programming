#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

Matrix::Matrix(int size) : size(size)
{
    matrix = new double[size * size];
}

Matrix::~Matrix()
{
    delete[] matrix;
}

void Matrix::Set(int row, int col, double value)
{
    matrix[ToIndex(row, col)] = value;
}

double Matrix::Get(int row, int col)
{
    return matrix[ToIndex(row, col)];
}

double Matrix::Largest()
{
    double max = matrix[0];
    for (int i = 1; i < size * size; i++)
    {
        if (matrix[i] > max)
        {
            max = matrix[i];
        }
    }
    return max;
}

double Matrix::Smallest()
{
    double min = matrix[0];
    for (int i = 1; i < size * size; i++)
    {
        if (matrix[i] < min)
        {
            min = matrix[i];
        }
    }
    return min;
}

void Matrix::Transpose()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            std::swap(matrix[ToIndex(i, j)], matrix[ToIndex(j, i)]);
        }
    }
}

void Matrix::Rot90()
{
    int n = size;
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n - n / 2; j++)
        {
            std::swap(matrix[ToIndex(i, j)], matrix[ToIndex(j, n - i - 1)]);
            std::swap(matrix[ToIndex(i, j)], matrix[ToIndex(n - j - 1, i)]);
            std::swap(matrix[ToIndex(n - j - 1, i)], matrix[ToIndex(n - i - 1, n - j - 1)]);
        }
    }
}

std::vector<double> Matrix::GetRow(int row)
{
    std::vector<double> result;
    for (int j = 0; j < size; j++)
    {
        result.push_back(matrix[ToIndex(row, j)]);
    }
    return result;
}

std::vector<double> Matrix::GetCol(int col)
{
    std::vector<double> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(matrix[ToIndex(i, col)]);
    }
    return result;
}

std::vector<double> Matrix::GetDiagonal()
{
    std::vector<double> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(matrix[ToIndex(i, i)]);
    }
    return result;
}

std::vector<double> Matrix::GetInverseDiagonal()
{
    std::vector<double> result;
    for (int i = 0; i < size; i++)
    {
        result.push_back(matrix[ToIndex(i, size - i - 1)]);
    }
    return result;
}

double Matrix::CalculateDeterminant()
{
    if (size == 1)
        return matrix[0];

    double result = 0;
    for (int i = 0; i < size; i++)
    {
        Matrix subMatrix = Cofactor(0, i);
        double subDet = subMatrix.CalculateDeterminant();
        result += (i % 2 == 0 ? 1 : -1) * matrix[ToIndex(0, i)] * subDet;
    }
    return result;
}

Matrix Matrix::Cofactor(int row, int col)
{
    Matrix subMatrix(size - 1);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i != row && j != col)
            {
                int subRow = (i < row) ? i : i - 1;
                int subCol = (j < col) ? j : j - 1;
                subMatrix.Set(subRow, subCol, matrix[ToIndex(i, j)]);
            }
        }
    }
    return subMatrix;
}


Matrix Matrix::Adjugate()
{
    Matrix subMatrix(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Matrix cofactorMatrix = Cofactor(i, j);
            double cofactorDet = cofactorMatrix.CalculateDeterminant();
            subMatrix.Set(j, i, ((i + j) % 2 == 0 ? 1 : -1) * cofactorDet);
        }
    }
    subMatrix.Transpose();
    return subMatrix;
}


Matrix Matrix::Invert()
{
    double det = CalculateDeterminant();
    if (det == 0)
    {
        throw std::runtime_error("Matrix determinant is zero, cannot invert.");
    }
    Matrix adj = Adjugate();
    Matrix inv(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            inv.Set(i, j, adj.Get(i, j) / det);
        }
    }
    return inv;
}
