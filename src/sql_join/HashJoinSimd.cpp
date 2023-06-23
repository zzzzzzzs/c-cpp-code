#include <iostream>
#include <vector>
#include <unordered_map>
#include <immintrin.h> // 包含 SIMD 指令集

using namespace std;

// 定义Row结构体
struct Row {
    int join_key;
    // 其他列
    std::string col1;
    std::string col2;
};

// TODO HashJoinSIMD 相当于 = 
int main() {
     // 定义R表和S表
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

    // 构建哈希表
    unordered_map<int, const Row*> hash_table;
    for (const auto& r : R) {
        hash_table[r.join_key] = &r;
    }

    // 执行连接操作
    vector<pair<Row, Row>> matched_rows;  // 存储匹配的行
    __m256i join_key_vec; // 定义存储键值的向量
    for (const auto& s : S) {
        // 将键值转化为向量进行处理
        join_key_vec = _mm256_set1_epi32(s.join_key);
        for (const auto& r : R) {
            if (_mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(_mm256_setr_epi32(r.join_key, 0, 0, 0, 0, 0, 0, 0), join_key_vec)))) {
                // 匹配到了
                matched_rows.emplace_back(r, s); // 将匹配行添加到向量中
            }
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
