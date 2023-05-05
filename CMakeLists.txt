cmake_minimum_required(VERSION 2.6)
#创建工程
project(mqtt_faceAI)
set(CMAKE_CXX_FLAGS "-std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/home/wilson/mqtt_faceAI/include/mqttai)
include_directories(/home/wilson/spdlog/include)
link_directories(/home/wilson/mqtt_faceAI/lib)
link_directories(/usr/local/lib)

#SET(CMAKE_BUILD_TYPE "Debug")  
#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") 

add_executable(mqtt_faceAI main.cpp faceDetect.cpp getUrlPic.cpp json.cpp logs.cpp) #将程序生成可执行文件
target_link_libraries(mqtt_faceAI ${OpenCV_LIBS} pthread mqttapi mqttclient rt dl m curl) #链接lib文件到可执行文件中