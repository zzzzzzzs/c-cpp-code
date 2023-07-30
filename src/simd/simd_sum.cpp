#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <immintrin.h> // Include the header for SIMD operations (AVX/AVX2)

double sum_with_simd(const std::vector<double>& arr) {
    const int vectorSize = 4; // Assuming AVX2, which operates on 256-bit registers (8 * double = 4 * 64-bit)
    const int numVectors = arr.size() / vectorSize;
    __m256d sumVec = _mm256_setzero_pd();

    for (int i = 0; i < numVectors; ++i) {
        __m256d dataVec = _mm256_loadu_pd(&arr[i * vectorSize]);
        sumVec = _mm256_add_pd(sumVec, dataVec);
    }

    // Sum all elements in the sumVec using horizontal addition
    __m128d low = _mm256_castpd256_pd128(sumVec);
    __m128d high = _mm256_extractf128_pd(sumVec, 1);
    __m128d sumVec128 = _mm_add_pd(low, high);
    double res[2];
    _mm_store_pd(res, sumVec128);
    double totalSum = res[0] + res[1];

    // Add any remaining elements in case arr.size() is not divisible by vectorSize
    for (int i = numVectors * vectorSize; i < arr.size(); ++i) {
        totalSum += arr[i];
    }

    return totalSum;
}

int main() {
    unsigned int size = 100000000;
    std::vector<double> arr(size);

    std::random_device rd;
    std::ranlux48_base gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // 生成随机数
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    std::cout << "开始计算" << std::endl;
    // 计时开始
    auto start = std::chrono::high_resolution_clock::now();

    double res = sum_with_simd(arr);

    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Sum: " << res << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
