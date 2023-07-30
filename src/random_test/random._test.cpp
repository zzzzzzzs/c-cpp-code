#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <chrono>
#include <omp.h>
#include <algorithm>
// g++ -o random_test random._test.cpp -fopenmp
// TODO 并行循环，速度非常快，比 python 的 @njit 快上一个数量级
double for_num() {
    unsigned int size = 100000000;
    std::vector<double> arr(size);

    std::random_device rd;
    std::ranlux48_base  gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    // 生成随机数
    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    // 对数组元素求和
    double res = 0.0;

    std::cout << "开始计算" << std::endl;
    // 计时开始
    auto start = std::chrono::high_resolution_clock::now();
    
    #pragma omp parallel  for reduction(+:res)
    for (int i = 0; i < size; ++i) {
        res += arr[i];
    }
    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    return res;
}

int main() {

     // 计时开始
    auto start = std::chrono::high_resolution_clock::now();

    double result = for_num();

    // 计时结束
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Sum: " << result << std::endl;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

    return 0;
}
