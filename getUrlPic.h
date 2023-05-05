#ifndef GETURLPIC_H_
#define GETURLPIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "logs.h"

/** @brief Read the MD5 from the file and download the image locally
 *  @param filename The text file that holds the MD5
 *  @returns 0:success
 *  @note  None
 */
int getUrlPics(const char *filename);

/** @brief Download the image from the given url and save it locally
 *  @param url The url to download the image
 *  @param SavePicName The name of the save image
 *  @returns 0:success -1:failed
 *  @note  None
 */
int getUrlPic(const char *url,const char *SavePicName);

#endif