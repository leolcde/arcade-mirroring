/*
** Project  -  arcade
** Date     -  March 21st 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

static int current_category = 0; // 0: graphics, 1: games, 2: name
static size_t selected_graphic = 0;
static size_t selected_game = 0;
static int name_cursor = 0;

std::vector<std::pair<std::string, int>> get_leaderboard_for_game(const std::string &game_name)
{
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
    std::sort(scores.begin(), scores.end(), [](auto &a, auto &b) {return a.second > b.second;});
    return scores;
}

std::string input_handling(Input input)
{
    std::string selected_game_file = "./lib/arcade_" +  games_libs[selected_game] + ".so";
    std::string selected_graphic_file = "./lib/arcade_" +  graphics_libs[selected_graphic] + ".so";

    switch (input) {
        case Input::DOWN:
            switch (current_category) {
                case 0: if (selected_graphic < graphics_libs.size() - 1) selected_graphic++; break;
                case 1: if (selected_game < games_libs.size() - 1) selected_game++; break;
                case 2: actual_username[name_cursor] = (actual_username[name_cursor] == 'z') ? 'a' : actual_username[name_cursor] + 1; break;
            }
            break;
        case Input::UP:
            switch (current_category) {
                case 0: if (selected_graphic > 0) selected_graphic--; break;
                case 1: if (selected_game > 0) selected_game--; break;
                case 2: actual_username[name_cursor] = (actual_username[name_cursor] == 'a') ? 'z' : actual_username[name_cursor] - 1; break;
            }
            break;
        case Input::RIGHT:
            if (current_category < 2) {
                current_category++;
            } else if (current_category == 2) {
                if (name_cursor < (int)actual_username.length() - 1) name_cursor++;
                else if (actual_username.length() < 5) { actual_username += 'a'; name_cursor++; }
            }
            break;
        case Input::LEFT:
            if (current_category == 1) {
                current_category--;
            } else if (current_category == 2) {
                if (name_cursor > 0) name_cursor--;
                else current_category--;
            }
            break;
        case Input::ACTION:
            if (current_category == 1) { last_menu_selection = "game"; actual_game_name = games_libs.empty() ? "" : games_libs[selected_game]; return games_libs.empty() ? "None" : selected_game_file; }
            if (current_category == 0) { last_menu_selection = "graphic"; return graphics_libs.empty() ? "None" : selected_graphic_file; }
            break;
        case Input::NEXT_LIB:
            if (graphics_libs.empty()) return "None";
            selected_graphic = (selected_graphic + 1) % graphics_libs.size();
            last_menu_selection = "graphic";
            return "./lib/arcade_" + graphics_libs[selected_graphic] + ".so";
        case Input::PREV_LIB:
            if (graphics_libs.empty()) return "None";
            selected_graphic = (selected_graphic == 0) ? graphics_libs.size() - 1 : selected_graphic - 1;
            last_menu_selection = "graphic";
            return "./lib/arcade_" + graphics_libs[selected_graphic] + ".so";
        default:
            break;
    }
    return "";
}

std::string display_menu(IDisplay *actual_lib, Input input)
{
    std::string input_handling_res = input_handling(input);
    if (input_handling_res != "") { return input_handling_res; }

    float cell_w = (actual_lib->getName() == "SfmlLib" || actual_lib->getName() == "Sdl2Lib") ? CELL_W : 1.0f;
    float cell_h = (actual_lib->getName() == "SfmlLib" || actual_lib->getName() == "Sdl2Lib") ? CELL_H : 1.0f;

    actual_lib->drawText({28 * cell_w, 2 * cell_h, "=== ARCADE MENU ===", Color::MAGENTA});
    actual_lib->drawText({17 * cell_w, 5 * cell_h, "GRAPHICS LIBRARIES:", current_category == 0 ? Color::GREEN : Color::CYAN});

    if (graphics_libs.empty())
        actual_lib->drawText({19 * cell_w, 7 * cell_h, "No libs found...", Color::RED});
    for (size_t i = 0; i < graphics_libs.size(); ++i) {
        std::string prefix = (i == selected_graphic && current_category == 0) ? "[X] " : "[ ] ";
        actual_lib->drawText({19 * cell_w, (7 + i) * cell_h, prefix + graphics_libs[i], Color::WHITE});
    }

    actual_lib->drawText({40 * cell_w, 5 * cell_h, "GAMES LIBRARIES:", current_category == 1 ? Color::GREEN : Color::CYAN});

    if (games_libs.empty())
        actual_lib->drawText({42 * cell_w, 7 * cell_h, "No games found...", Color::RED});
    for (size_t i = 0; i < games_libs.size(); ++i) {
        std::string prefix = (i == selected_game && current_category == 1) ? "[X] " : "[ ] ";
        actual_lib->drawText({42 * cell_w, (7 + i) * cell_h, prefix + games_libs[i], Color::WHITE});
    }

    actual_lib->drawText({17 * cell_w, 12 * cell_h, "ENTER YOUR NAME:", current_category == 2 ? Color::GREEN : Color::YELLOW});
    std::string display_name = "> " + actual_username;
    if (current_category == 2) {
        display_name.insert(name_cursor + 2, "[");
        display_name.insert(name_cursor + 4, "]");
    } else
        display_name += "_";
    actual_lib->drawText({19 * cell_w, 14 * cell_h, display_name, Color::GREEN});

    actual_lib->drawText({40 * cell_w, 12 * cell_h, "LEADERBOARD:", Color::YELLOW});
    auto scores = get_leaderboard_for_game(games_libs.empty() ? "" : games_libs[selected_game]);
    if (scores.empty())
        actual_lib->drawText({42 * cell_w, 14 * cell_h, "No scores yet.", Color::WHITE});
    else {
        for (size_t i = 0; i < std::min(scores.size(), (size_t)5); ++i)
            actual_lib->drawText({42 * cell_w, (14 + i) * cell_h, std::to_string(i + 1) + ". " + scores[i].first + " - " + std::to_string(scores[i].second), Color::WHITE});
    }

    actual_lib->drawText({15 * cell_w, 17 * cell_h, "Use ARROWS to navigate & ENTER to start a game", Color::BLUE});
    actual_lib->drawText({30 * cell_w, 18 * cell_h, "Press 'Q' to quit", Color::RED});

    return "";
}
