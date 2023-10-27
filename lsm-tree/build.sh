#!/bin/bash

# 设置项目名称
project_name="lsm_tree"

# 创建一个构建目录
build_dir="build"

# 检查构建目录是否存在，如果不存在就创建
if [ ! -d "$build_dir" ]; then
    mkdir "$build_dir"
fi

# 进入构建目录
cd "$build_dir"

# 调用CMake生成Makefile
cmake ..

# 使用make编译项目
make

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功！可执行文件位于 $PWD"
else
    echo "编译失败，请检查错误信息。"
fi
