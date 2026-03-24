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
const auto tick = std::chrono::milliseconds(200);

int launch_game(Input input, IGame *actual_game, IDisplay *actual_lib)
{
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
            return actual_game->getScore();
        }
    }

    // Display all game elements
    std::vector<Entity> entities = actual_game->getEntities();
    for (size_t i = 0; i < entities.size(); i++)
        actual_lib->drawEntity(entities[i]);
    std::vector<Text> texts = actual_game->getTexts();
    for (size_t i = 0; i < texts.size(); i++)
        actual_lib->drawText(texts[i]);
    return -1;
}
