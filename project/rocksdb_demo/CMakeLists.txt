cmake_minimum_required(VERSION 3.10)
# 设置 C++ 编译器为 Clang
set(CMAKE_CXX_COMPILER "clang++")

# 设置 C 编译器为 Clang
set(CMAKE_C_COMPILER "clang")

# 包含 RocksDB 头文件
include_directories(/usr/include/rocksdb)

# 启用 ASan
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g -O1")

project(rocksdb_demo CXX C)

# 获取 src 目录下的所有源文件
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.c")

# 添加可执行文件，并将所有源文件链接到可执行文件
add_executable(rocksdb_demo ${SOURCE_FILES})

# 查找并链接 RocksDB 库
find_library(ROCKSDB_LIBRARY rocksdb)
if(NOT ROCKSDB_LIBRARY)
    message(FATAL_ERROR "RocksDB library not found")
else()
    target_link_libraries(rocksdb_demo ${ROCKSDB_LIBRARY})
endif()