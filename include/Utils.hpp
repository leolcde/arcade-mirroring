/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#pragma once

#include <iostream>
#include <vector>
#include <string>

enum class Input
{
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

enum class Color
{
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

struct Entity
{
    // std::string name;
    float x;
    float y;
    float x_sfml;
    float y_sfml;
    char entChar;
    std::string spritePath;
    Color color;
};

struct Text
{
    float x;
    float y;
    std::string text;
    Color color;
};
