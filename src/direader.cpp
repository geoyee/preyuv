#include <algorithm>
#include <dirent.h>
#include "direader.h"

// 按文件名大小排序
class StringOrderFunction_
{
public:
    bool operator()(const std::string &a, const std::string &b) const
    {
        if (a.size() == b.size())
            return a < b;
        else
            return a.size() < b.size();
    }
};

// 获取文件夹下所有图像路径
std::vector<std::string> readImages(const std::string &image_dir)
{

    std::vector<std::string> image_paths;
    DIR *dir;
    if ((dir = opendir(image_dir.c_str())) != nullptr)
    {
        dirent *dp;
        for (dp = readdir(dir); dp != nullptr; dp = readdir(dir))
        {
            const std::string img_file_name = dp->d_name;
            if (img_file_name == "." || img_file_name == "..")
                continue;
            // image_paths.emplace_back(image_dir + "/" + img_file_name);
            // 保存文件名，不包含后缀
            const size_t pos = img_file_name.find_last_of('.');
            if (pos != std::string::npos)
                image_paths.emplace_back(img_file_name.substr(0, pos));
            else
                image_paths.emplace_back(img_file_name);
        }
        closedir(dir);
    }
    std::sort(image_paths.begin(), image_paths.end(), StringOrderFunction_());
    return image_paths;
}
