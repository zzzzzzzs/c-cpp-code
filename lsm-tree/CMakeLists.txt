cmake_minimum_required(VERSION 3.10)

project(lsm CXX C)

# 获取 src 目录下的所有源文件
file(GLOB SOURCE_FILES "src/*.cpp" "src/*.c")

# 添加可执行文件，并将所有源文件链接到可执行文件
add_executable(lsm ${SOURCE_FILES})
