cmake_minimum_required(VERSION 3.16)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)

# 可执行文件输出到 bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR}/include)
#添加一个可执行目标
add_executable(test_scanner
    test/test_scanner.cpp
    src/offline/DirectoryScanner.cpp
)