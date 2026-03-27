/*
** Project  -  arcade
** Date     -  March 21st 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"
#include "../lib/graphics/Sfml.hpp"

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
            if (current_category == 1) { return games_libs.empty() ? "None" : "./lib/games/" + games_libs[selected_game]; }
            break;
        default:
            break;
    }
    return "";
}

void sfmlMenuDisplay(IDisplay *actual_lib)
{
    actual_lib->drawText({500, 100, "=== ARCADE MENU ===", Color::MAGENTA});

    actual_lib->drawText({200, 200, "GRAPHICS LIBRARIES:", current_category == 0 ? Color::GREEN : Color::CYAN});
    if (graphics_libs.empty())
        actual_lib->drawText({19, 7, "No libs found...", Color::RED});
    for (size_t i = 0; i < graphics_libs.size(); ++i) {
        std::string prefix = (i == selected_graphic && current_category == 0) ? "[X] " : "[ ] ";
        actual_lib->drawText({19, 7.0f + i, prefix + graphics_libs[i], Color::WHITE});
    }

    actual_lib->drawText({900, 200, "GAMES LIBRARIES:", current_category == 1 ? Color::GREEN : Color::CYAN});
    if (games_libs.empty())
        actual_lib->drawText({42, 7, "No games found...", Color::RED});
    for (size_t i = 0; i < games_libs.size(); ++i) {
        std::string prefix = (i == selected_game && current_category == 1) ? "[X] " : "[ ] ";
        actual_lib->drawText({42, 7.0f + i, prefix + games_libs[i], Color::WHITE});
    }

    actual_lib->drawText({17, 10, "ENTER YOUR NAME:", current_category == 2 ? Color::GREEN : Color::YELLOW});
    std::string display_name = "> " + actual_username;
    if (current_category == 2) {
        display_name.insert(name_cursor + 2, "[");
        display_name.insert(name_cursor + 4, "]");
    } else
        display_name += "_";
    actual_lib->drawText({19, 12, display_name, Color::GREEN});

    actual_lib->drawText({40, 10, "LEADERBOARD:", Color::YELLOW});
    auto scores = get_leaderboard_for_game(games_libs.empty() ? "" : games_libs[selected_game]);
    if (scores.empty())
        actual_lib->drawText({42, 12, "No scores yet.", Color::WHITE});
    else {
        for (size_t i = 0; i < std::min(scores.size(), (size_t)5); ++i)
            actual_lib->drawText({42, 12.0f + i, std::to_string(i + 1) + ". " + scores[i].first + " - " + std::to_string(scores[i].second), Color::WHITE});
    }

    actual_lib->drawText({15, 15, "Use ARROWS to navigate & ENTER to start a game", Color::BLUE});
    actual_lib->drawText({30, 16, "Press 'Q' to quit", Color::RED});
}

std::string display_menu(IDisplay *actual_lib, Input input)
{
    std::string input_handling_res = input_handling(input);
    if (input_handling_res != "") { return input_handling_res; }

    // Menu display
    if (actual_lib->getName() == "SfmlLib")
        sfmlMenuDisplay(actual_lib);
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
    std::string display_name = "> " + actual_username;
    if (current_category == 2) {
        display_name.insert(name_cursor + 2, "[");
        display_name.insert(name_cursor + 4, "]");
    } else
        display_name += "_";
    actual_lib->drawText({19, 12, display_name, Color::GREEN});

    actual_lib->drawText({40, 10, "LEADERBOARD:", Color::YELLOW});
    auto scores = get_leaderboard_for_game(games_libs.empty() ? "" : games_libs[selected_game]);
    if (scores.empty())
        actual_lib->drawText({42, 12, "No scores yet.", Color::WHITE});
    else {
        for (size_t i = 0; i < std::min(scores.size(), (size_t)5); ++i)
            actual_lib->drawText({42, 12.0f + i, std::to_string(i + 1) + ". " + scores[i].first + " - " + std::to_string(scores[i].second), Color::WHITE});
    }

    actual_lib->drawText({15, 15, "Use ARROWS to navigate & ENTER to start a game", Color::BLUE});
    actual_lib->drawText({30, 16, "Press 'Q' to quit", Color::RED});
    return "";
}
