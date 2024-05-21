#include <iostream>
#include "Matrix.h"

/**
 * Name : Jephte Pierre
 * Date: February 9, 2024
 *
 * Description: The goal of this assignment is to get familiar with classes in C++, in particular: the big 5, operator overloading, error
 * handling, and templates. This will be done through designing a fully functional Matrix class.
 *
 */

int main()
{
    // Test Matrix class
    Matrix<int> mat1(3, 3);
    Matrix<int> mat2(3, 3);

    // Perform operations and test functionalities
    Matrix<int> sum = mat1 + mat2;
    std::cout << "Addition test passed." << std::endl;

    Matrix<int> diff = mat1 - mat2;
    std::cout << "Subtraction test passed." << std::endl;

    Matrix<int> scalar_mult = mat1 * 5;
    std::cout << "Scalar multiplication test passed. " << std::endl;

    Matrix<int> hadamard_product = mat1.Hadamard(mat2);
    std::cout << "Hadamard product test passed." << std::endl;

    Matrix<int> transposed = mat1.transpose();
    std::cout << "Transpose test passed. " << std::endl;

    Matrix<int> product = mat1 * mat2;
    std::cout << "Matrix multiplication test passed." << std::endl;

    //  Gaussian elimination
    Matrix<int> gaussian_mat(3, 3);

    // gaussian_mat with values
    gaussian_mat.gaussianElimination();
    std::cout << "Gaussian elimination test passed." << std::endl;

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
