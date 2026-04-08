/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Wed, Mar, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     Sd2                                                                              *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *       ▄▀▀█▄▄▄▄  ▄▀▀▄▀▀▀▄  ▄▀▀█▀▄    ▄▀▀▀█▀▀▄  ▄▀▀█▄▄▄▄  ▄▀▄▄▄▄   ▄▀▀▄ ▄▄             *
 *      ▐  ▄▀   ▐ █   █   █ █   █  █  █    █  ▐ ▐  ▄▀   ▐ █ █    ▌ █  █   ▄▀            *
 *        █▄▄▄▄▄  ▐  █▀▀▀▀  ▐   █  ▐  ▐   █       █▄▄▄▄▄  ▐ █      ▐  █▄▄▄█             *
 *        █    ▌     █          █        █        █    ▌    █         █   █             *
 *       ▄▀▄▄▄▄    ▄▀        ▄▀▀▀▀▀▄   ▄▀        ▄▀▄▄▄▄    ▄▀▄▄▄▄▀   ▄▀  ▄▀             *
 *       █    ▐   █         █       █ █          █    ▐   █     ▐   █   █               *
 *       ▐        ▐         ▐       ▐ ▐          ▐        ▐         ▐   ▐               *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#include "Sdl2.hpp"

static SDL_Color getColorPair(Color c);

Sdl2::Sdl2() : _window(nullptr), _width(1500), _height(1000), _renderer(nullptr), _font(nullptr)
{
    Sdl2::init();
}

Sdl2::~Sdl2()
{
    Sdl2::stop();
}

void Sdl2::init()
{
    //load window
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw runtime_error(SDL_GetError());
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
    if (_window == nullptr)
        throw runtime_error(SDL_GetError());

    //load renderer
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == nullptr)
        throw runtime_error(SDL_GetError());

    //load font
    if (TTF_Init() != 0)
        throw runtime_error(TTF_GetError());
    _font =  TTF_OpenFont("assets/Bungee-Regular.ttf", 24);
    if (_font == nullptr)
        throw runtime_error(TTF_GetError());
}

void Sdl2::stop()
{
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

std::string Sdl2::getName()
{
    return "Sdl2Lib";
}

void Sdl2::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void Sdl2::display()
{
   SDL_RenderPresent(_renderer);
}

void Sdl2::drawEntity(const Entity &entity)
{
    SDL_Color c = getColorPair(entity.color);
    SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);

    SDL_Rect r;
    r.x = (int)entity.x_sfml;
    r.y = (int)entity.y_sfml;
    r.w = 32;
    r.h = 32;

    SDL_RenderFillRect(_renderer, &r);
}

void Sdl2::drawText(const Text &text)
{
    SDL_Color c = getColorPair(text.color);

    SDL_Surface* surf = TTF_RenderUTF8_Blended(_font, text.text.c_str(), c);
    if (!surf)
        throw std::runtime_error(TTF_GetError());
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surf);
    if (!texture) {
        SDL_FreeSurface(surf);
        throw runtime_error(SDL_GetError());
    }

    SDL_Rect dst;
    dst.x = static_cast<int>(text.x);
    dst.y = static_cast<int>(text.y);
    dst.h = surf->h;
    dst.w = surf->w;

    SDL_FreeSurface(surf);
    SDL_RenderCopy(_renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

Input Sdl2::getInput()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
    
        if (e.type == SDL_QUIT)
            return Input::EXIT;

        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    
            switch (e.key.keysym.sym) {
                case SDLK_RETURN:
                case SDLK_KP_ENTER: return Input::ACTION;
                case SDLK_UP: return Input::UP;
                case SDLK_DOWN: return Input::DOWN;
                case SDLK_LEFT: return Input::LEFT;
                case SDLK_RIGHT: return Input::RIGHT;

                case SDLK_1: return Input::PREV_LIB;
                case SDLK_2: return Input::NEXT_LIB;
                case SDLK_3: return Input::PREV_GAME;
                case SDLK_4: return Input::NEXT_GAME;
                
                case SDLK_r: return Input::RESTART;
                case SDLK_m: return Input::MENU;
                case SDLK_q: return Input::EXIT;
                default: break;
            } 
        }
    }

    return Input::NONE;
}

SDL_Color getColorPair(Color c)
{
    switch (c) {
        case Color::RED: return {255, 0, 0, 255};
        case Color::GREEN: return {0, 255, 0, 255};
        case Color::YELLOW: return {255, 255, 0, 255};
        case Color::BLUE: return {0, 0, 255, 255};
        case Color::MAGENTA: return {255, 0, 255, 255};
        case Color::CYAN: return {0, 255, 255, 255};
        case Color::WHITE: return {255, 255, 255, 255};
        case Color::BLACK: return {0, 0, 0, 255};
        case Color::DEFAULT:
        default: return {255, 255, 255, 255};
    }
}

extern "C" IDisplay *createEntryPoint()
{
    return new Sdl2();
}

extern "C" void destroyEntryPoint(IDisplay *display)
{
    delete display;
}