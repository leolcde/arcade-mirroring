/*
** Project  -  arcade
** Date     -  March 23rd 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

using Clock = std::chrono::steady_clock;
static auto last_time = Clock::now();
static auto accumulator = std::chrono::milliseconds(0);
static std::size_t selected_game;
static std::size_t selected_graphic;
const auto tick = std::chrono::milliseconds(200);

std::string run_game(Input input, IGame *actual_game, IDisplay *actual_lib)
{
    // Games hotswap
    if (input == Input::NEXT_GAME || input == Input::PREV_GAME) {
        if (games_libs.empty()) return "None";
        games_states.insert({"./lib/arcade_" + games_libs[selected_game] + ".so", actual_game});
        if (input == Input::NEXT_GAME) selected_game = (selected_game + 1) % games_libs.size();
        if (input == Input::PREV_GAME) selected_game = (selected_game == 0) ? games_libs.size() - 1 : selected_game - 1;
        last_menu_selection = "game";
        return "./lib/arcade_" + games_libs[selected_game] + ".so";
    }
    if (input == Input::NEXT_LIB || input == Input::PREV_LIB) {
        if (graphics_libs.empty()) return "None";
        if (input == Input::NEXT_LIB) selected_graphic = (selected_graphic + 1) % graphics_libs.size();
        if (input == Input::PREV_LIB) selected_graphic = (selected_graphic == 0) ? graphics_libs.size() - 1 : selected_graphic - 1;
        last_menu_selection = "graphic";
        return "./lib/arcade_" + graphics_libs[selected_graphic] + ".so";
    }

    // Update game logic every tick or update now if directional input
    auto now = Clock::now();
    accumulator += std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time);
    last_time = now;
    if ((input == Input::UP || input == Input::DOWN || input == Input::LEFT || input == Input::RIGHT) && accumulator < tick)
        accumulator = tick;
    while (accumulator >= tick) {
        accumulator -= tick;
        actual_game->update(input);
        if (actual_game->isGameOver()) {
            accumulator = std::chrono::milliseconds(0);
            return "None";
        }
    }

    // Display all game elements
    std::vector<Entity> entities = actual_game->getEntities();
    for (size_t i = 0; i < entities.size(); i++)
        actual_lib->drawEntity(entities[i]);
    std::vector<Text> texts = actual_game->getTexts();
    for (size_t i = 0; i < texts.size(); i++)
        actual_lib->drawText(texts[i]);
    return "None";
}
