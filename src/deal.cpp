#include <fstream>
#include "libyuv.h"
#include "direader.h"
#include "deal.h"

// 将YUYV422格式的内存块保存为图片
void saveYUYV422(
    const std::string &yuyv_path, const std::string &save_path, const size_t &width, const size_t &height)
{
    char *data = loadImageToMemory(yuyv_path);
    cv::Mat argb(height, width, CV_8UC4);
    libyuv::YUY2ToARGB(
        reinterpret_cast<uint8_t *>(data), width * 2, argb.data, width * 4, width, height);
    cv::Mat mat(height, width, CV_8UC3);
    cv::cvtColor(argb, mat, cv::COLOR_RGBA2RGB);
    preProcessing(mat);
    cv::imwrite(save_path, mat);
}

// 添加图片到内存，失败返回空指针
char *loadImageToMemory(const std::string &path)
{
    std::ifstream ifs(path, std::ifstream::in | std::ios::binary);
    if (!ifs.is_open())
    {
        std::cout << "Open image failed!" << std::endl;
        return nullptr;
    }
    ifs.seekg(0, ifs.end);
    size_t size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    char *data = new char[size];
    ifs.read(data, size);
    if (!ifs)
    {
        std::cout << "Error: only " << ifs.gcount() << " could be read." << std::endl;
        delete[] data;
        return nullptr;
    }
    ifs.close();
    return data;
}

// 逆时针旋转90度
void preProcessing(cv::Mat &img)
{
    cv::transpose(img, img);
    cv::flip(img, img, 0);
}
