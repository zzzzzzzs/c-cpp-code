#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

// 内存层级
std::map<int, int> memTable;

// 磁盘层级
std::vector<std::pair<int, int>> diskTable;

// 内存层级大小阈值
const int MEMTABLE_THRESHOLD = 5;

// 将内存层级数据刷入磁盘层级
void FlushMemTableToDisk() {
    for (const auto& entry : memTable) {
        diskTable.push_back(entry);
    }
    memTable.clear();
    std::sort(diskTable.begin(), diskTable.end());
}

// 将键值对插入内存层级
void Insert(int key, int value) {
    memTable[key] = value;
    if (memTable.size() >= MEMTABLE_THRESHOLD) {
        FlushMemTableToDisk();
    }
}

// 根据键查找值
int Lookup(int key) {
    int value = -1;
    
    // 先在内存层级查找
    auto memIt = memTable.find(key);
    if (memIt != memTable.end()) {
        value = memIt->second;
    } else {
        // 然后在磁盘层级查找
        auto diskIt = std::lower_bound(diskTable.begin(), diskTable.end(), std::make_pair(key, 0));
        if (diskIt != diskTable.end() && diskIt->first == key) {
            value = diskIt->second;
        }
    }
    
    return value;
}

int main() {
    Insert(1, 100);
    Insert(2, 200);
    Insert(3, 300);

    // 查找键1的值
    int result = Lookup(1);
    if (result != -1) {
        std::cout << "键1的值为: " << result << std::endl;
    } else {
        std::cout << "未找到键1" << std::endl;
    }

    // 查找键4的值
    result = Lookup(4);
    if (result != -1) {
        std::cout << "键4的值为: " << result << std::endl;
    } else {
        std::cout << "未找到键4" << std::endl;
    }

    return 0;
}
