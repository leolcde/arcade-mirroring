#include "DLLoader.hpp"
#include "start_menu.hpp"
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <algorithm>

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

static std::vector<std::pair<std::string, int>> get_scores_for_game(const std::string& game_name) {
    std::vector<std::pair<std::string, int>> scores;
    std::ifstream file("data/scores");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string game, name;
        int score;
        if (iss >> game >> name >> score && game == game_name)
            scores.push_back({name, score});
    }
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b) {return a.second > b.second;});
    return scores;
}

void display_start_menu(IDisplay *actual_lib, Input input)
{
    static std::vector<std::string> graphics_libs = get_libs_from_dir("./lib/graphics");
    static std::vector<std::string> games_libs = get_libs_from_dir("./lib/games");
    static int current_category = 0; // 0: graphics, 1: games, 2: name
    static size_t selected_graphic = 0;
    static size_t selected_game = 0;
    static std::string player_name = "guest";
    static int name_cursor = 0;

    // Interactive handling
    if (input == Input::DOWN) {
        if (current_category == 0 && selected_graphic < graphics_libs.size() - 1) selected_graphic++;
        else if (current_category == 1 && selected_game < games_libs.size() - 1) selected_game++;
        else if (current_category == 2) {
            if (player_name[name_cursor] < 'z') player_name[name_cursor]++;
            else if (player_name[name_cursor] == 'z') player_name[name_cursor] = 'a';
        }
    } else if (input == Input::UP) {
        if (current_category == 0 && selected_graphic > 0) selected_graphic--;
        else if (current_category == 1 && selected_game > 0) selected_game--;
        else if (current_category == 2) {
            if (player_name[name_cursor] > 'a') player_name[name_cursor]--;
            else if (player_name[name_cursor] == 'a') player_name[name_cursor] = 'z';
        }
    } else if (input == Input::RIGHT) {
        if (current_category < 2) current_category++;
        else if (current_category == 2 && name_cursor < (int)player_name.length() - 1) name_cursor++;
        else if (current_category == 2 && player_name.length() < 5) { player_name += 'a'; name_cursor++; }
    } else if (input == Input::LEFT) {
        if (current_category > 0 && current_category != 2) current_category--;
        else if (current_category == 2 && name_cursor > 0) name_cursor--;
        else if (current_category == 2 && name_cursor == 0) current_category--;
    } else if (input == Input::ACTION) {
        if (current_category == 2) {
            std::ofstream file("data/scores", std::ios::app);
            std::string game = games_libs.empty() ? "None" : games_libs[selected_game];
            file << game << " " << player_name << " 0\n";
        }
    }

    // Menu display
    actual_lib->drawText({28, 2, "=== ARCADE MENU ===", Color::MAGENTA});

    actual_lib->drawText({17, 5, "GRAPHICS LIBRARIES:", current_category == 0 ? Color::GREEN : Color::CYAN});
    if (graphics_libs.empty())
        actual_lib->drawText({19, 7, "No libs found...", Color::RED});
    for (size_t i = 0; i < graphics_libs.size(); ++i) {
        std::string prefix = (i == selected_graphic && current_category == 0) ? "[X] " : "[ ] ";
        actual_lib->drawText({19, 7.0f + i, prefix + graphics_libs[i], Color::WHITE});
    }

    actual_lib->drawText({40, 5, "GAMES LIBRARIES:", current_category == 1 ? Color::GREEN : Color::CYAN});
    if (games_libs.empty())
        actual_lib->drawText({42, 7, "No games found...", Color::RED});
    for (size_t i = 0; i < games_libs.size(); ++i) {
        std::string prefix = (i == selected_game && current_category == 1) ? "[X] " : "[ ] ";
        actual_lib->drawText({42, 7.0f + i, prefix + games_libs[i], Color::WHITE});
    }

    actual_lib->drawText({17, 10, "ENTER YOUR NAME:", current_category == 2 ? Color::GREEN : Color::YELLOW});
    std::string display_name = "> " + player_name;
    if (current_category == 2) {
        display_name.insert(name_cursor + 2, "[");
        display_name.insert(name_cursor + 4, "]");
    } else
        display_name += "_";
    actual_lib->drawText({19, 12, display_name, Color::GREEN});

    actual_lib->drawText({40, 10, "LEADERBOARD:", Color::YELLOW});
    auto scores = get_scores_for_game(games_libs.empty() ? "" : games_libs[selected_game]);
    if (scores.empty())
        actual_lib->drawText({42, 12, "No scores yet.", Color::WHITE});
    else {
        for (size_t i = 0; i < std::min(scores.size(), (size_t)5); ++i)
            actual_lib->drawText({42, 12.0f + i, std::to_string(i + 1) + ". " + scores[i].first + " - " + std::to_string(scores[i].second), Color::WHITE});
    }

    actual_lib->drawText({15, 15, "Use ARROWS to navigate & ENTER to start a game", Color::BLUE});
    actual_lib->drawText({30, 16, "Press 'Q' to quit", Color::RED});
}
