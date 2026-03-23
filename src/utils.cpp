/*
** Project  -  arcade
** Date     -  March 23rd 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

std::vector<std::string> get_libs_from_dir(const std::string &path)
{
    std::vector<std::string> libs;
    DIR *dir = opendir(path.c_str());
    if (dir == nullptr) return libs;

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name.length() > 3 && name.substr(name.length() - 3) == ".so")
            libs.push_back(name);
    }
    closedir(dir);
    return libs;
}
