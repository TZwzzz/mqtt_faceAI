cmake_minimum_required(VERSION 2.6)
#创建工程
project(spdlog_project)
set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(/home/wilson/spdlog/include)
#link_directories(/usr/local/lib)

add_executable(app main.cpp) #将程序生成可执行文件
target_link_libraries(app pthread)