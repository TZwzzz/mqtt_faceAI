#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include <iostream>
#include <pthread.h>

int main()
{
    int i = 0;
    spdlog::init_thread_pool(10000,1);
    auto file_logger = spdlog::rotating_logger_mt<spdlog::async_factory>("main.cpp_logger","../anyteck_logs/log",1024*1024*5,100);
    file_logger->set_level(spdlog::level::debug);
    while(i < 1000000)
    {
        file_logger->debug("Async message #{}",i);
        i++;
    }
    spdlog::drop_all();
    return 0;

}