#include <immintrin.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Row {
    int join_key;
    std::string col1;
    std::string col2;
};

// 定义 AVX2 加速的匹配函数
inline __m256i simd_match(__m256i keys_r, __m256i keys_s) {
    // 使用 _mm256_cmpeq_epi32 函数比较两个AVX2向量相等的元素，并将结果保存在mask中
    __m256i mask = _mm256_cmpeq_epi32(keys_r, keys_s);
    // 使用 _mm256_movemask_epi8 函数将mask转换为int值并返回
    return _mm256_movemask_epi8(mask);
}

int main() {
    vector<Row> R = {   {1, "A", "B"}, 
                        {2, "C", "D"}, 
                        {3, "E", "F"},
                    };
    vector<Row> S = { 
                        {1, "G", "H"}, 
                        {4, "I", "J"}, 
                        {2, "K", "L"},
                        {2, "M", "N"},
                    };

    std::sort(R.begin(), R.end(), [](const auto& a, const auto& b) {
        return a.join_key < b.join_key;
    });
    std::sort(S.begin(), S.end(), [](const auto& a, const auto& b) {
        return a.join_key < b.join_key;
    });

    vector<pair<Row, Row>> matched_rows;

    // 使用 AVX2 向量化计算
    int r_size = R.size();
    int s_size = S.size();
    int simd_width = 8;  // 使用 AVX2 的 256-bit 寄存器，每个寄存器可以容纳 8 个 32-bit 整数
    for (int i = 0; i < r_size; i += simd_width) {
        __m256i keys_r = _mm256_set_epi32(
            R[i + 7].join_key, R[i + 6].join_key, R[i + 5].join_key, R[i + 4].join_key,
            R[i + 3].join_key, R[i + 2].join_key, R[i + 1].join_key, R[i].join_key
        );

        for (int j = 0; j < s_size; j += simd_width) {
            __m256i keys_s = _mm256_set_epi32(
                S[j + 7].join_key, S[j + 6].join_key, S[j + 5].join_key, S[j + 4].join_key,
                S[j + 3].join_key, S[j + 2].join_key, S[j + 1].join_key, S[j].join_key
            );

            __m256i mask = simd_match(keys_r, keys_s);

            // 遍历mask中的匹配结果，并将匹配的行保存到向量中
            for (int k = 0; k < simd_width; ++k) {
                int bit_mask = 1 << (k * 4);
                if (mask & bit_mask) {
                    matched_rows.emplace_back(R[i + k], S[j]);
                }
            }
        }
    }

    // 输出查询结果...
    std::cout << "Matched rows:" << std::endl;
    for (const auto& pair : matched_rows) {
        const Row& r = pair.first;
        const Row& s = pair.second;
        std::cout << r.join_key << ", " << r.col1 << ", " << r.col2 << ", "
                  << s.join_key << ", " << s.col1 << ", " << s.col2 << std::endl;
    }

    return 0;
}
