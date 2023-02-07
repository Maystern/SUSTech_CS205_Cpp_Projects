// g++ ex01.cpp -mavx2 -fopenmp -o run && ./run
#include <iostream>
#include "immintrin.h"
#include "omp.h"
# include "sys/time.h"
using std::cout;
using std::endl;
const int N = 1e8;
float a[N], b[N], c_BF[N], c_SIMD[N];
void vectorAdd_BF(float *v1, float *v2, float *res, size_t n) {
    for (size_t i = 0; i < n; i++)
        res[i] = v1[i] + v2[i];
}
void vectorAdd_SIMD(float *v1, float *v2, float *res, size_t n) {
    if (n >= 8) {
        // #pragma omp parallel for schedule(dynamic)
        for (size_t p = 0; p <= n - 8; p += 8) {
            _mm256_store_ps(res + p, _mm256_add_ps(
                _mm256_loadu_ps(v1 + p), 
                _mm256_loadu_ps(v2 + p))
            );
        }
    }
    for (size_t p = n - n % 8; p < n; p++)
        res[p] = v1[p] + v2[p];
}
bool checkError(float *v1, float *v2, size_t n) {
    for (size_t i = 0; i < n; i++)
        if (abs(v1[i] - v2[i]) > 1e-9) {
            cout << i << endl;
            printf("%.10f\n", v1[i]);
            printf("%.10f\n", v2[i]);
            return false;
        }
    return true;
}
int main() {
    cout << "loading data..." << endl;
    for (int i = 0; i < N; i++) {
        a[i] = b[i] = i;
        c_BF[i] = c_SIMD[i] = 0;
    }
    struct timeval start, end;
    long timeuse_BF, timeuse_SIMD;
    cout << "OK!" << endl;
    cout << "running vectorAdd_BF..." << endl;
    gettimeofday(&start, NULL);
    vectorAdd_BF(a, b, c_BF, N);
    gettimeofday(&end, NULL);
    timeuse_BF = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    cout << "OK!" << endl;
    cout << "vectorAdd_SIMD..." << endl;
    gettimeofday(&start, NULL);
    vectorAdd_SIMD(a, b, c_SIMD, N);
    gettimeofday(&end, NULL);
    timeuse_SIMD = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec-start.tv_usec;
    cout << "OK!" << endl;
    cout << "checking err <= 1e-9..." << endl;
    cout << checkError(c_BF, c_SIMD, N) << endl;
    cout << "Time of BF: " << timeuse_BF << "ms" << endl;
    cout << "Time of SIMD: " << timeuse_SIMD << "ms" << endl;
    return 0;
}