#include <iostream>
#include <string>
#include <vector>
#include "deal.h"
#include "direader.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: ./Convert <yuyv_input_dir> <jpeg_save_dir>" << std::endl;
        return -1;
    }

    std::string input_dir = argv[1];
    std::string save_dir = argv[2];

    std::vector<std::string> image_names = readImages(input_dir);
    for (std::string &image_name : image_names)
    {
        std::string image_path = input_dir + "/" + image_name + ".yuv";
        std::string save_path = save_dir + "/" + image_name + ".jpg";
        saveYUYV422(image_path, save_path, 320, 240);
        std::cout << "Convert " << image_path << " to " << save_path << std::endl;
    }

    return 0;
}