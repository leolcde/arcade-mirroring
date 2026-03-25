/*
** Project  : arcade
** File     : Caca.hpp
** Path     : lib/graphics
** Date     : 3/24/26  10:26AM
**
** Made by Léo Lacordaire
*/

#pragma once

#include "../../include/IDisplay.hpp"
#include <caca.h>

using namespace std;

class Caca : public IDisplay
{
    private:
        caca_display_t *_window;
		caca_canvas_t  *_canvas;
        caca_event_t _event;

    public:
        Caca();
        ~Caca();

        void init() override;
        void stop() override;
        std::string getName() override;

		// Display methods
        void clear() override;
        void display() override;
        void drawEntity(const Entity &entity) override;
        void drawText(const Text &text) override;
        Input getInput() override;
};
