/*
** Project  -  arcade
** Date     -  March 23rd 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

std::vector<std::string> graphics_libs = {"ncurses", "libcaca", "sfml", "sdl2"};
std::vector<std::string> games_libs = {"snake", "nibbler"};
std::map<std::string, IGame *> games_states = {};
std::string actual_game_name = "";
std::string actual_username = "guest";
std::string last_menu_selection = "";

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
