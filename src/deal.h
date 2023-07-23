#ifndef DEAL_H
#define DEAL_H

#include <iostream>
#include <string>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

void saveYUYV422(
    const std::string &yuyv_path, const std::string &save_path, const size_t &width, const size_t &height);
char *loadImageToMemory(const std::string &path);
void preProcessing(cv::Mat &img);

#endif // DEAL_H
