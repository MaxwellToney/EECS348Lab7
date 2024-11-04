#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

class Matrix {
private:
    std::vector<std::vector<int>> data;
    int size;

public:
    Matrix(int n) : size(n) {
        data.resize(n, std::vector<int>(n, 0));
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file!" << std::endl;
            return;
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> data[i][j];
            }
        }
    }

    void display() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << std::setw(4) << elem;
            }
            std::cout << std::endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    int sumDiagonals() const {
        int sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += data[i][i]; // Main diagonal
            sum += data[i][size - 1 - i]; // Secondary diagonal
        }
        return sum;
    }

    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            std::swap(data[row1], data[row2]);
        } else {
            std::cerr << "Invalid row indices!" << std::endl;
        }
    }
};

int main() {
    int n;
    std::string filename;

    std::cout << "Enter the size of the matrix (N): ";
    std::cin >> n;

    Matrix matrixA(n);
    Matrix matrixB(n);
    
    std::cout << "Enter the filename to load the matrices: ";
    std::cin >> filename;

    matrixA.loadFromFile(filename);
    matrixB.loadFromFile(filename);

    std::cout << "Matrix A:" << std::endl;
    matrixA.display();

    std::cout << "Matrix B:" << std::endl;
    matrixB.display();

    Matrix sumMatrix = matrixA + matrixB;
    std::cout << "Sum of Matrix A and Matrix B:" << std::endl;
    sumMatrix.display();

    Matrix productMatrix = matrixA * matrixB;
    std::cout << "Product of Matrix A and Matrix B:" << std::endl;
    productMatrix.display();

    std::cout << "Sum of diagonal elements: " << sumMatrix.sumDiagonals() << std::endl;

    int row1, row2;
    std::cout << "Enter two row indices to swap: ";
    std::cin >> row1 >> row2;

    sumMatrix.swapRows(row1, row2);
    std::cout << "After swapping rows " << row1 << " and " << row2 << ":" << std::endl;
    sumMatrix.display();

    return 0;
}
