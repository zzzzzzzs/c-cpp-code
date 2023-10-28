#!/bin/bash

build_project() {
    local build_dir="build_debug"

    # 检查构建目录是否存在，如果不存在就创建
    if [ ! -d "$build_dir" ]; then
        mkdir "$build_dir"
    fi

    # 进入构建目录
    cd "$build_dir"

    # 检查是否已经生成Makefile
    if [ ! -f "Makefile" ]; then
        cmake ..
    fi

    # 使用make编译项目
    make

    # 检查编译是否成功
    if [ $? -eq 0 ]; then
        echo "编译成功！可执行文件位于 $PWD"
    else
        echo "编译失败，请检查错误信息。"
    fi
}

clean_project() {
    local build_dir="build_debug"

    # 清理构建目录
    echo "Cleaning..."
    rm -rf "$build_dir"
    echo "Clean is OK!"
}

main() {
    if [ "$1" = "--clean" ]; then
        clean_project
    else
        build_project
    fi
}


# 调用main函数并传入参数
main "$1"