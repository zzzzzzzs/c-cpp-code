#include <iostream>
#include <vector>
#include <unordered_map>
#include <immintrin.h>

// 定义Row结构体
struct Row {
    int join_key;
    // 其他列
    std::string col1;
    std::string col2;
};

// 使用 AVX 指令集进行哈希表查找
template<int N>
void hash_lookup(const std::vector<Row>& R, const __m256i& join_keys, std::array<const Row*, N>& results) {
    constexpr int NumLanes = sizeof(__m256i) / sizeof(int);
    std::unordered_map<int, const Row*> hash_table;

    for (const auto& r : R) {
        hash_table[r.join_key] = &r;
    }

    for (int i = 0; i < NumLanes; ++i) {
        int join_key[N];
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(join_key), join_keys);

        if (i >= N) break;

        const auto it = hash_table.find(join_key[i]);
        if (it != hash_table.end()) {
            results[i] = it->second;
        } else {
            results[i] = nullptr;
        }
    }
}

// TODO HashJoin 相当于 =
int main() {
     // 定义R表和S表
    std::vector<Row> R = {   {1, "A", "B"}, 
                             {2, "C", "D"}, 
                             {3, "E", "F"},
                         };
    std::vector<Row> S = { 
                             {1, "G", "H"}, 
                             {4, "I", "J"}, 
                             {2, "K", "L"},
                             {2, "M", "N"},
                         };

    // 执行连接操作
    std::vector<std::pair<Row, Row>> matched_rows;  // 存储匹配的行

    const __m256i JoinKeysS = _mm256_set_epi32(S[3].join_key, S[2].join_key, S[1].join_key, S[0].join_key,
                                               0, 0, 0, 0);
    std::array<const Row*, 4> ResultsR{}; // 将数组大小设置为4
    hash_lookup<4>(R, JoinKeysS, ResultsR);

    // 使用 AVX 指令集进行匹配操作
    for (int i = 0; i < 4; ++i) {
        const Row* r = ResultsR[i];
        if (r != nullptr) {
            matched_rows.emplace_back(*r, S[i]);
        }
    }

    // 输出查询结果...
    std::cout << "Matched rows:" << std::endl;
    for (const auto& pair : matched_rows) {
        const Row& r = pair.first;
        const Row& s = pair.second;
        std::cout << r.join_key << ", " << r.col1 << ", " << r.col2 << ", "
                  << s.join_key << ", " << s.col1 << ", " << s.col2 << std::endl; // 打印匹配行的详细信息
    }

    return 0;
}