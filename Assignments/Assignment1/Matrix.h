#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class Matrix {
private:
    size_t rows;
    size_t cols;
    T* data;

public:
    // Constructors and Destructor
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    // Assignment Operators
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;

    // Access Operators
    T* operator[](size_t rowIndex);
    const T* operator[](size_t rowIndex) const;

    // Arithmetic Operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(T scalar) const;
    Matrix Hadamard(const Matrix& other) const; // Hadamard product

    // Other Operations
    Matrix transpose() const;
    void gaussianElimination();

    // Getters
    size_t numRows() const;
    size_t numCols() const;

    // Utility Functions
    void print() const;
};

#include "Matrix.ixx"

#endif /* MATRIX_H */

