#ifndef LOGS_H_
#define LOGS_H_

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

/** @brief Initialize the logger
 *  @param None
 *  @returns 0:successfully Other:failed
 *  @note  None
 */
int logs_init();

/** @brief Log record
 *  @param None
 *  @returns None
 *  @note  Usage example:get_jsonLogs()->info("ret_rect_to_json() return: {}", json_str);
 */
std::shared_ptr<spdlog::logger> get_jsonLogs();
std::shared_ptr<spdlog::logger> get_getUrlPicLogs();
std::shared_ptr<spdlog::logger> get_faceDetectLogs();

#endif