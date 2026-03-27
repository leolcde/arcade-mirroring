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

// cellule pour imité la ncurses, après faut faire des calcul. Ex: 40 * CELL_W ou 10 * CELL_H
#define CELL_W 16.0f
#define CELL_H 24.0f

std::vector<std::string> get_libs_from_dir(const std::string &path);
std::string display_menu(IDisplay *actual_lib, Input input);
int launch_game(Input input, IGame *actual_game, IDisplay *actual_lib);

static std::vector<std::string> graphics_libs = get_libs_from_dir("./lib/graphics");
static std::vector<std::string> games_libs = get_libs_from_dir("./lib/games");
static std::string actual_username = "guest";
