/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Sat, Mar, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     Utils                                                                            *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *         ░        ░       ░░        ░        ░        ░░      ░░  ░░░░  ░             *
 *         ▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒             *
 *         ▓      ▓▓▓       ▓▓▓▓▓  ▓▓▓▓▓▓▓  ▓▓▓▓      ▓▓▓  ▓▓▓▓▓▓▓        ▓             *
 *         █  ███████  ██████████  ███████  ████  ███████  ████  █  ████  █             *
 *         █        █  ███████        ████  ████        ██      ██  ████  █             *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#pragma once

#include <iostream>
#include <vector>
#include <string>

enum class Input {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACTION,
    NEXT_LIB,
    PREV_LIB,
    NEXT_GAME,
    PREV_GAME,
    RESTART,
    MENU,
    EXIT
};

enum class Color {
    DEFAULT = 0,
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

struct Entity {
    float x;
    float y;
    char ncursesChar;
    std::string spritePath;
    Color color;
};

struct Text {
    float x;
    float y;
    std::string text;
    Color color;
};
