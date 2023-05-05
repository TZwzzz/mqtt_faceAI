#ifndef JSON_H_
#define JSON_H_

#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <pthread.h>
#include "faceDetect.h"
#include "logs.h"

/** @brief Format the ret_rect structure container as a json string
 *  @param ret_rect A container of type ret_rect to be formatted as a json string
 *  @returns A formatted json string
 *  @note  None
 */
std::string ret_rect_to_json(const std::vector<ret_rect>& ret_rect);

#endif


