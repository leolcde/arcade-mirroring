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
#include <map>

// Cell for resize when is graphic lib is not terminal displaying
#define CELL_W 20.0f
#define CELL_H 50.0f

std::vector<std::string> get_libs_from_dir(const std::string &path);
std::string display_menu(IDisplay *actual_lib, Input input);
int launch_game(Input input, IGame *actual_game, IDisplay *actual_lib);

extern std::vector<std::string> graphics_libs;
extern std::vector<std::string> games_libs;
extern std::string actual_username;
extern std::string last_menu_selection;
extern std::string actual_game_name;
