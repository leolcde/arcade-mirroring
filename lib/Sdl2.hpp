/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     Sdl2                                                                             *
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

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/IDisplay.hpp"

class Sdl2 : public IDisplay
{
    private:
        SDL_Window* _window;
        int _width;
        int _height;
        SDL_Renderer* _renderer;
        TTF_Font* _font;

    public:
        Sdl2();
        ~Sdl2();

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
