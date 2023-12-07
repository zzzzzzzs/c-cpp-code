#include <rocksdb/db.h>
#include <iostream>

// 安装 rocksdb
// sudo apt-get update
// sudo apt-get install librocksdb-dev
int main() {
    rocksdb::DB* db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "./testdb", &db);
    if (status.ok()) {
        std::cout << "RocksDB opened successfully." << std::endl;
    } else {
        std::cerr << "Error opening RocksDB: " << status.ToString() << std::endl;
    }

     std::unique_ptr<rocksdb::DB> db_ptr(db);

    // 写入数据
    std::string key = "myKey";
    // std::string value = "myValue";
    // status = db_ptr->Put(rocksdb::WriteOptions(), key, value);
    // if (!status.ok()) {
    //     std::cerr << "写入失败: " << status.ToString() << std::endl;
    // } else {
    //     std::cout << "数据写入成功" << std::endl;
    // }

    // 读取数据
    std::string read_value;
    status = db_ptr->Get(rocksdb::ReadOptions(), key, &read_value);
    if (!status.ok()) {
        std::cerr << "读取失败: " << status.ToString() << std::endl;
    } else {
        std::cout << "读取的数据: " << read_value << std::endl;
    }

    return 0;
}
