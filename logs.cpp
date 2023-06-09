#include "logs.h"

#define FLUSH_TIME 1                                      // 定期刷新秒数
#define THREAD_QSIZE 8192                                 // 线程最大内存
#define THREAD_CNT 1                                      // 线程个数
#define LOG_FORMAT "[%Y-%m-%d %H:%M:%S.%e][%n][%t][%l]%v" // 日志格式

#define JSON_LOGS_NAME "jsonLogs"                     // 日志记录器名称
#define JSON_LOGS_PATH "./anyteck_logs/jsonLogs/logs" // 日志存储路径
#define JSON_LOGS_SIZE (1024 * 1024 * 5)              // 单个日志文件容量上限
#define JSON_LOGS_CNT 100                             // 日志文件最大个数

#define GETURLPIC_LOGS_NAME "getUrlPiclogs"
#define GETURLPIC_LOGS_PATH "./anyteck_logs/getUrlPicLogs/logs"
#define GETURLPIC_LOGS_SIZE (1024 * 1024 * 5)
#define GETURLPIC_LOGS_CNT 100

#define FACEDETECT_LOGS_NAME "faceDetectLogs"
#define FACEDETECT_LOGS_PATH "./anyteck_logs/faceDetectLogs/logs"
#define FACEDETECT_LOGS_SIZE (1024 * 1024 * 5)
#define FACEDETECT_LOGS_CNT 100

std::shared_ptr<spdlog::logger> jsonLogs;
std::shared_ptr<spdlog::logger> getUrlPicLogs;
std::shared_ptr<spdlog::logger> faceDetectLogs;

std::shared_ptr<spdlog::logger> get_jsonLogs()
{
    return jsonLogs;
}

std::shared_ptr<spdlog::logger> get_getUrlPicLogs()
{
    return getUrlPicLogs;
}

std::shared_ptr<spdlog::logger> get_faceDetectLogs()
{
    return faceDetectLogs;
}

int logs_init()
{
    int ret = -1;
    try
    {
        // 设置日志记录器的参数
        spdlog::init_thread_pool(THREAD_QSIZE, THREAD_CNT);    // 初始化线程池
        spdlog::flush_every(std::chrono::seconds(FLUSH_TIME)); // 定期刷新缓存

        // 创建文件 sink
        auto jsonSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(JSON_LOGS_PATH, JSON_LOGS_SIZE, JSON_LOGS_CNT);
        auto getUrlPicSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(GETURLPIC_LOGS_PATH, GETURLPIC_LOGS_SIZE, GETURLPIC_LOGS_CNT);
        auto faceDetectSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(FACEDETECT_LOGS_PATH, FACEDETECT_LOGS_SIZE, FACEDETECT_LOGS_CNT);

        // 创建异步记录器，并将 sink 添加到记录器中
        jsonLogs = std::make_shared<spdlog::async_logger>(JSON_LOGS_NAME, spdlog::sinks_init_list{jsonSink}, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        getUrlPicLogs = std::make_shared<spdlog::async_logger>(GETURLPIC_LOGS_NAME, spdlog::sinks_init_list{getUrlPicSink}, spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        faceDetectLogs = std::make_shared<spdlog::async_logger>(FACEDETECT_LOGS_NAME, spdlog::sinks_init_list{faceDetectSink}, spdlog::thread_pool(), spdlog::async_overflow_policy::block);

        // 设置日志格式
        jsonLogs->set_pattern(LOG_FORMAT);       
        getUrlPicLogs->set_pattern(LOG_FORMAT);  
        faceDetectLogs->set_pattern(LOG_FORMAT); 

        // 注册日志记录器
        spdlog::register_logger(jsonLogs);       
        spdlog::register_logger(getUrlPicLogs);  
        spdlog::register_logger(faceDetectLogs); 

        ret = 0;
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
    }
    return ret;
}
