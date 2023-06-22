#include <iostream>
#include <vector>

using namespace std;

// 定义Row结构体
struct Row {
    int join_key;
    // 其他列
    std::string col1;
    std::string col2;
};

// TODO LoopJoin 相当于= 
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

    // 执行连接操作
    vector<pair<Row, Row>> matched_rows;  // 存储匹配的行
    for (const auto& r : R) {
        // 遍历S表中的所有元组s，检查r和s的连接属性是否相等
        for (const auto& s : S) {
            if (r.join_key == s.join_key) {
                // 匹配到了
                matched_rows.emplace_back(r,s); // 将匹配行添加到向量中
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
