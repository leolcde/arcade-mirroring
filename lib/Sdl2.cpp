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

Sdl2::Sdl2() : _window(nullptr), _renderer(nullptr), _texture(nullptr), _font(nullptr),  _width(1500), _height(1000)
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

    //load texture
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
        throw runtime_error(IMG_GetError());
    SDL_Surface* surf = IMG_Load("assets/square.png");
    if (surf == nullptr)
        throw runtime_error(SDL_GetError());
    _texture = SDL_CreateTextureFromSurface(_renderer, surf);
    SDL_FreeSurface(surf);
    if (_texture == nullptr)
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
    SDL_DestroyTexture(_texture);
    IMG_Quit();
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
    
}

void Sdl2::drawText(const Text &text)
{
    
}

Input Sdl2::getInput()
{
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
    
        if (e.type == SDL_QUIT)
            return Input::EXIT;

        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    
            switch (e.key.keysym.sym) {
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
}

extern "C" IDisplay *myEntryPoint()
{
    return new Sdl2();
}