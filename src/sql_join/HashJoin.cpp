#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 定义Row结构体
struct Row {
    int join_key;
    // 其他列
    std::string col1;
    std::string col2;
};

// TODO HashJoin 相当于 = 
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
    for (const auto& s : S) {
        auto it = hash_table.find(s.join_key);
        if (it != hash_table.end()) {
            // 匹配到了
            const Row* r = it->second;
            // 连接R表和S表中的匹配行
            matched_rows.emplace_back(*r, s); // 将匹配行添加到向量中
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
