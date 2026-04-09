/*
** Project  : arcade
** File     : Caca.cpp
** Path     : lib
** Date     : 3/24/26  10:25AM
**
** Made by Léo Lacordaire
*/

#include "Caca.hpp"

Caca::Caca() : _window(NULL), _canvas(NULL) {}

Caca::~Caca() { Caca::stop(); }

void Caca::init()
{
    _window = caca_create_display(NULL);
    if (_window == NULL) {
        std::cout << "[ERROR]: cannot create window" << std::endl;
        _canvas = NULL;
        return;
    }

    _canvas = caca_get_canvas(_window);
    caca_set_display_title(_window, "Arcacade Project");
}

void Caca::stop()
{
    if (_window == NULL)
        return;

    caca_free_display(_window);
    _window = NULL;
    _canvas = NULL;
}

std::string Caca::getName()
{
    return "LibCaca";
}

void Caca::display()
{
    if (_window == NULL)
        return;
    caca_refresh_display(_window);
}

void Caca::clear()
{
    if (_canvas == NULL)
        return;
    caca_clear_canvas(_canvas);
}

int getColorPair(Color color)
{
    switch (color) {
        case Color::RED:     return CACA_RED;
        case Color::GREEN:   return CACA_GREEN;
        case Color::YELLOW:  return CACA_YELLOW;
        case Color::BLUE:    return CACA_BLUE;
        case Color::MAGENTA: return CACA_MAGENTA;
        case Color::CYAN:    return CACA_CYAN;
        case Color::WHITE:   return CACA_WHITE;
        case Color::BLACK:   return CACA_BLACK;
        default:             return CACA_WHITE;
    }
}

void Caca::drawEntity(const Entity &entity)
{
    if (_canvas == NULL)
        return;
    int pair = getColorPair(entity.color);
    caca_set_color_ansi(_canvas, pair, CACA_BLACK);
    caca_put_char(_canvas, (int)entity.x, (int)entity.y, entity.entChar);
}

void Caca::drawText(const Text &text)
{
    if (_canvas == NULL)
        return;
    int pair = getColorPair(text.color);
    caca_set_color_ansi(_canvas, pair, CACA_BLACK);
    caca_put_str(_canvas, text.x, text.y, text.text.c_str());
}

Input Caca::getInput()
{
    if (_window == NULL)
        return Input::EXIT;

    if (caca_get_event(_window, CACA_EVENT_KEY_PRESS, &_event, 0))
    {
        int key = caca_get_event_key_ch(&_event);

        if (key == 'q' || key == 'Q')
            return Input::EXIT;
        if (key == 'r' || key == 'R')
            return Input::RESTART;
        if (key == 'm' || key == 'M')
            return Input::MENU;
        if (key == CACA_KEY_RETURN || key == '\n' || key == '\r')
            return Input::ACTION;

        if (key == '1')
            return Input::PREV_LIB;
        if (key == '2')
            return Input::NEXT_LIB;
        if (key == '3')
            return Input::PREV_GAME;
        if (key == '4')
            return Input::NEXT_GAME;

        if (key == CACA_KEY_UP)
            return Input::UP;
        if (key == CACA_KEY_DOWN)
            return Input::DOWN;
        if (key == CACA_KEY_LEFT)
            return Input::LEFT;
        if (key == CACA_KEY_RIGHT)
            return Input::RIGHT;
    }
        return Input::NONE;

}

// Others
extern "C" IDisplay *createEntryPoint()
{
    return new Caca();
}

extern "C" void destroyEntryPoint(IDisplay *display)
{
    delete display;
}
