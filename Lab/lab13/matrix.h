#include <cstddef>
#include <iostream>
#define MAXROWS 5
#define MAXCOLS 5
using namespace std;
template<class T>
class Matrix {
    private:
        T matrix[MAXROWS][MAXCOLS];
        size_t rows, cols;
    public:
        Matrix(size_t row = MAXROWS, size_t col = MAXCOLS);
        void printMatrix();
        void setMatrix(T[][MAXCOLS]);
        void addMatrix(T[][MAXCOLS]);
};
template<class T> Matrix<T>::Matrix(size_t row, size_t col) {
    rows = row; cols = col;
    for (size_t i = 0; i < MAXROWS; i++)
        for (size_t j = 0; j < MAXCOLS; j++) {
            matrix[i][j] = T();
        }
}
template<class T> void Matrix<T>::printMatrix() {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
template<class T> void Matrix<T>::setMatrix(T tmp[][MAXCOLS]) {
    for (size_t i = 0; i < MAXROWS; i++)
        for (size_t j = 0; j < MAXCOLS; j++) {
            matrix[i][j] = tmp[i][j];
        }
}
template<class T> void Matrix<T>::addMatrix(T tmp[][MAXCOLS]) {
    for (size_t i = 0; i < MAXROWS; i++)
        for (size_t j = 0; j < MAXCOLS; j++) {
            matrix[i][j] += tmp[i][j];
        }
}