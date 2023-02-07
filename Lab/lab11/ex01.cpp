#include <iostream>
#include <memory>
using std::cerr;
using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::endl;
class Matrix {
    private:
        size_t rows, cols;
        shared_ptr<float> data;
    public:
        inline size_t getRows() const { return rows; }
        inline size_t getCols() const { return cols; }
        Matrix(size_t rows = 0, size_t cols = 0): rows(rows), cols(cols) {
            data = shared_ptr<float>(new float [rows * cols]);
        }
        float getElement(size_t row_id, size_t col_id) const{
            return data.get()[cols * row_id + col_id];
        }
        void setElement(size_t row_id, size_t col_id, float val) {
            data.get()[cols * row_id + col_id] = val;
        }
        void setElement(size_t num, float *val) {
            for (size_t i = 0; i < rows; i++) {
                for (size_t j = 0; j < cols; j++) {
                    data.get()[i * cols + j] = val[i * cols + j];
                }
            }
        }
        Matrix operator+ (const Matrix & m) {
            if (this->rows != m.getRows() || this->cols != m.getCols()) {
                cerr << "Error!" << endl;
                return *this;
            }
            Matrix res(m.getRows(), m.getCols());
            for (size_t i = 0; i < m.rows; i++) {
                for (size_t j = 0; j < m.cols; j++) {
                    res.setElement(i, j, this->getElement(i, j) + m.getElement(i, j));
                }
            }
            return res;
        }
        void show() {
            for (size_t i = 0; i < this->rows; i++) {
                for (size_t j = 0; j < this->cols; j++) {
                    cout << this->getElement(i, j) << " ";
                }
                cout << endl;
            }
        }
};
int main() {
    float val1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    float val2[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12};
    Matrix a(3, 4); a.setElement(12, val1);
    Matrix b(3, 4); b.setElement(12, val2);
    Matrix c = a + b; c.show();
    Matrix d = a; d.show();
    d = b; d.show();
    return 0;
}