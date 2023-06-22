#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 定义Row结构体
struct Row {
    int join_key;
    // 其他列
    std::string col1;
    std::string col2;
};

// TODO SortMergeJoin 实现 
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

    // 将关系 R 和关系 S 中的行按照 join_key 值进行排序
    std::sort(R.begin(), R.end(), [](const auto& a, const auto& b) {
        return a.join_key < b.join_key;
    });
    std::sort(S.begin(), S.end(), [](const auto& a, const auto& b) {
        return a.join_key < b.join_key;
    });

    // Sort-Merge Join 阶段，遍历排好序的关系 R 和关系 S 并进行匹配
    vector<pair<Row, Row>> matched_rows;  // 存储匹配的行
    for (auto r_iter = R.begin(); r_iter != R.end(); ++r_iter) {
        auto s_iter = std::lower_bound(S.begin(), S.end(), *r_iter, [](const auto& a, const auto& b) {
            return a.join_key < b.join_key;
        });

        while (s_iter != S.end() && s_iter->join_key == r_iter->join_key) {
            // 对于 join_key 值相等的行进行匹配，并将其保存到向量中
            matched_rows.emplace_back(*r_iter, *s_iter);

            ++s_iter;
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
