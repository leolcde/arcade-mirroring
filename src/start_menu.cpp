/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Sun, Mar, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     start_menu                                                                       *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *       _|_|_|_|  _|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|    _|           *
 *       _|        _|    _|    _|        _|      _|        _|        _|    _|           *
 *       _|_|_|    _|_|_|      _|        _|      _|_|_|    _|        _|_|_|_|           *
 *       _|        _|          _|        _|      _|        _|        _|    _|           *
 *       _|_|_|_|  _|        _|_|_|      _|      _|_|_|_|    _|_|_|  _|    _|           *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "DLLoader.hpp"
#include <vector>
#include <string>
#include <dirent.h>

std::vector<std::string> get_libs_from_dir(const std::string &path) {
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

void display_start_menu(IDisplay *actual_lib)
{
    std::vector<std::string> graphics_libs = get_libs_from_dir("./lib/graphics");
    std::vector<std::string> games_libs = get_libs_from_dir("./lib/games");

    actual_lib->drawText({15, 2, "=== ARCADE MENU ===", Color::MAGENTA});

    actual_lib->drawText({2, 5, "GRAPHICS LIBRARIES:", Color::CYAN});
    if (graphics_libs.empty())
        actual_lib->drawText({4, 7, "No libs found...", Color::RED});
    for (size_t i = 0; i < graphics_libs.size(); ++i)
        actual_lib->drawText({4, 7.0f + i, "[ ] " + graphics_libs[i], Color::WHITE});

    actual_lib->drawText({25, 5, "GAMES LIBRARIES:", Color::CYAN});
    if (games_libs.empty())
        actual_lib->drawText({27, 7, "No games found...", Color::RED});
    for (size_t i = 0; i < games_libs.size(); ++i)
        actual_lib->drawText({27, 7.0f + i, "[ ] " + games_libs[i], Color::WHITE});

    actual_lib->drawText({2, 13, "LEADERBOARD:", Color::YELLOW});
    actual_lib->drawText({4, 15, "1. Jules - 9999", Color::WHITE});
    actual_lib->drawText({4, 16, "2. Paul  - 4200", Color::WHITE});
    actual_lib->drawText({4, 17, "3. Anna  - 2142", Color::WHITE});

    actual_lib->drawText({25, 13, "ENTER YOUR NAME:", Color::YELLOW});
    actual_lib->drawText({27, 15, "> jules_", Color::GREEN});

    actual_lib->drawText({10, 21, "Press '1'/'2' to change lib", Color::BLUE});
    actual_lib->drawText({10, 22, "Press 'Q' to quit", Color::RED});
}
