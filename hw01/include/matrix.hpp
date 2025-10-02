#pragma once

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix
{
public:
    Matrix(int size);
    ~Matrix();
    int GetSize() const { return size; }
    void Set(int row, int col, double value);
    double Get(int row, int col);
    // 最大值
    double Largest();
    // 最小值
    double Smallest();
    // 轉置
    void Transpose();
    // 順時針旋轉90度
    void Rot90();
    // 取得指定列
    std::vector<double> GetRow(int row);
    // 取得指定行
    std::vector<double> GetCol(int col);
    // 取得主對角線
    std::vector<double> GetDiagonal();
    // 取得副對角線
    std::vector<double> GetInverseDiagonal();
    // 計算行列式
    double CalculateDeterminant();
    // 反矩陣
    Matrix Invert();

private:
    double *matrix = nullptr;
    int size = 0;
    int ToIndex(int row, int col) const { return row * size + col; }
    Matrix Cofactor(int row, int col);
    Matrix Adjugate();
};

#endif // MATRIX_H