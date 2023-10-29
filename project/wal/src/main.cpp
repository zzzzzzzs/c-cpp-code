#include <iostream>
#include <fstream>
#include <string>

class Wal {
public:
    Wal(const std::string& logFileName, const std::string& dataFileName) :
        _logFileName(logFileName), _dataFileName(dataFileName) {
        // 打开日志文件，如果不存在则创建
        _logFile.open(_logFileName, std::ios::out | std::ios::app);
        // 打开数据文件，如果不存在则创建
        _dataFile.open(_dataFileName, std::ios::out | std::ios::app);
    }

    ~Wal() {
        // 关闭日志文件和数据文件
        _logFile.close();
        _dataFile.close();
    }

    // 写入事务到日志
    void write_transaction(const std::string& transaction) {
        if (_logFile.is_open()) {
            _logFile << transaction << std::endl;
            _logFile.flush();  // 确保数据被立即写入磁盘
        } else {
            std::cerr << "Unable to write to log file." << std::endl;
        }
    }

    // 提交事务，写入数据文件
    void commit(const std::string& data) {
        if (_dataFile.is_open()) {
            _dataFile << data << std::endl;
            _dataFile.flush();  // 确保数据被立即写入磁盘
        } else {
            std::cerr << "Unable to write to data file." << std::endl;
        }
    }

    // 回滚事务
    void rollback() {
        // 撤销上一次写入的事务
        if (_logFile.is_open()) {
            _logFile.seekp(0, std::ios::end);  // 移动到文件末尾
            _logFile << "Rollback" << std::endl;
            _logFile.flush();  // 确保数据被立即写入磁盘
        } else {
            std::cerr << "Unable to write to log file." << std::endl;
        }
    }

    // 从日志文件中恢复数据
    void recover_data() {
        std::ifstream logFile(_logFileName);
        if (logFile.is_open()) {
            std::string line;
            while (std::getline(logFile, line)) {
                if (line != "Rollback") {
                    commit(line);
                }
            }
            logFile.close();
        } else {
            std::cerr << "Unable to open log file for reading." << std::endl;
        }
    }

private:
    std::string _logFileName;
    std::string _dataFileName;
    std::ofstream _logFile;
    std::ofstream _dataFile;
};

int main() {
    // 创建一个WAL对象，指定日志文件名和数据文件名
    Wal wal("mydatabase.wal", "mydatabase.dat");

    // 模拟事务
    wal.write_transaction("Transaction 1: Write data 123");
    wal.commit("Data 123");
    wal.write_transaction("Transaction 2: Update data 456");
    wal.rollback(); // 回滚上一个事务
    wal.write_transaction("Transaction 3: Write data 789");
    wal.commit("Data 789");

    // 恢复数据
    wal.recover_data();

    return 0;
}
