#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows, cols;

public:
    Matrix(size_t _rows, size_t _cols) : rows(_rows), cols(_cols), data(_rows, std::vector<T>(_cols)) {}

    void clear() {
        for (auto& row : data) {
            row.clear();
        }
        data.clear();
    }



    void inputFromKeyboard() {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                std::cin >> data[i][j];
            }
        }
    }

    void fillRandom(T min, T max) {

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] = min + (rand() % static_cast<int>(max - min + 1));
            }
        }
    }

    void display() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    T findMax() const {
        T maxVal = data[0][0];
        for (const auto& row : data) {
            T localMax = *std::max_element(row.begin(), row.end());
            if (localMax > maxVal) maxVal = localMax;
        }
        return maxVal;
    }

    T findMin() const {
        T minVal = data[0][0];
        for (const auto& row : data) {
            T localMin = *std::min_element(row.begin(), row.end());
            if (localMin < minVal) minVal = localMin;
        }
        return minVal;
    }

    void sortRows() {
        for (auto& row : data) {
            std::sort(row.begin(), row.end());
        }
    }

    bool binarySearch(T value) const {
        for (const auto& row : data) {
            if (std::binary_search(row.begin(), row.end(), value)) {
                return true;
            }
        }
        return false;
    }

    void replaceValue(T old_value, T new_value) {
        for (auto& row : data) {
            for (auto& elem : row) {
                if (elem == old_value) {
                    elem = new_value;
                }
            }
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrix dimensions mismatch!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrix dimensions mismatch!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::runtime_error("Matrix dimensions mismatch for multiplication!");
        }
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;  // Initializing to 0
                for (size_t k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix operator/(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::runtime_error("Matrix dimensions mismatch!");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (other.data[i][j] == 0) {
                    throw std::runtime_error("Division by zero in matrix!");
                }
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

};

int main() {
    srand(time(NULL));
    Matrix<int> mat1(2, 2);
    cout << "Matrix 1 (random values):\n";
    mat1.fillRandom(1, 10);
    mat1.display();

    Matrix<int> mat2(2, 2);
    cout << "\nMatrix 2 (random values):\n";
    mat2.fillRandom(1, 10);
    mat2.display();

    Matrix<int> sum = mat1 + mat2;
    cout << "\nMatrix 1 + Matrix 2:\n";
    sum.display();

    Matrix<int> diff = mat1 - mat2;
    cout << "\nMatrix 1 - Matrix 2:\n";
    diff.display();

    Matrix<int> mult = mat1 * mat2;
    cout << "\nMatrix 1 * Matrix 2:\n";
    mult.display();

    bool divisionPossible = mat2.findMin() != 0;

    if (divisionPossible) {
        Matrix<int> div = mat1 / mat2;
        cout << "\nMatrix 1 / Matrix 2 (element-wise):\n";
        div.display();
    }
    else {
        cout << "\nError: Division by zero detected in Matrix 2.\n";
    }

    // Additional functionalities demo:
    cout << "\nMatrix 1 after sorting each row:\n";
    mat1.sortRows();
    mat1.display();

    int searchValue = 5;
    cout << "\nSearching for " << searchValue << " in Matrix 1: "
        << (mat1.binarySearch(searchValue) ? "Found" : "Not Found") << endl;

    cout << "\nReplacing 5 with 99 in Matrix 1:\n";
    mat1.replaceValue(5, 99);
    mat1.display();

    return 0;
}