/*
** Project  -  arcade
** Date     -  March 23rd 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "DLLoader.hpp"
#include <vector>
#include <string>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>

std::vector<std::string> get_libs_from_dir(const std::string &path);
std::string display_menu(IDisplay *actual_lib, Input input);
int launch_game(Input input, IGame *actual_game, IDisplay *actual_lib);

static std::vector<std::string> graphics_libs = get_libs_from_dir("./lib/graphics");
static std::vector<std::string> games_libs = get_libs_from_dir("./lib/games");
static std::string actual_username = "guest";
