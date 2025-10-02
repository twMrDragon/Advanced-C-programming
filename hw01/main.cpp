#include <iostream>
#include <iomanip>
#include <ctime>
#include "./include/matrix.hpp"

void fillMatrixWithRandom(Matrix &matrix, int min, int max);
void printMatrix(Matrix &matrix);
void printArray(std::vector<double> arr);

int main()
{
    Matrix matrix(4);
    fillMatrixWithRandom(matrix, 1, 9);

    std::cout << "Original Matrix:" << std::endl;
    printMatrix(matrix);
    std::cout << std::endl;

    std::cout << "Largest: " << matrix.Largest() << std::endl;
    std::cout << "Smallest: " << matrix.Smallest() << std::endl;
    std::cout << std::endl;

    matrix.Transpose();
    std::cout << "Transposed Matrix:" << std::endl;
    printMatrix(matrix);
    std::cout << std::endl;

    matrix.Rot90();
    std::cout << "Rotated 90 Degrees Matrix:" << std::endl;
    printMatrix(matrix);
    std::cout << std::endl;

    std::vector<double> row = matrix.GetRow(2);
    std::cout << "Row with index 2: ";
    printArray(row);
    std::cout << std::endl;

    std::vector<double> col = matrix.GetCol(2);
    std::cout << "Column with index 2: ";
    printArray(col);
    std::cout << std::endl;

    std::vector<double> diag = matrix.GetDiagonal();
    std::cout << "Main Diagonal: ";
    printArray(diag);
    std::cout << std::endl;

    std::vector<double> invDiag = matrix.GetInverseDiagonal();
    std::cout << "Inverse Diagonal: ";
    printArray(invDiag);
    std::cout << std::endl;

    int det = matrix.CalculateDeterminant();
    std::cout << "Determinant: " << det << std::endl;
    std::cout << std::endl;

    Matrix inv = matrix.Invert();
    std::cout << "Inverted Matrix:" << std::endl;
    printMatrix(inv);

    return 0;
}

void fillMatrixWithRandom(Matrix &matrix, int min, int max)
{
    srand(time(0));
    int size = matrix.GetSize();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int value = rand() % (max - min + 1) + min;
            matrix.Set(i, j, value);
        }
    }
}

void printMatrix(Matrix &matrix)
{
    int size = matrix.GetSize();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            std::cout << std::setw(2) << matrix.Get(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void printArray(std::vector<double> arr)
{
    for (unsigned int i = 0; i < arr.size(); i++)
    {
        std::cout << std::setw(2) << arr[i] << " ";
    }
    std::cout << std::endl;
}