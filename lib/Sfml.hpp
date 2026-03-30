/*
** Project  : arcade
** File     : Sfml.hpp
** Path     : lib/games
** Date     : 3/26/26  3:09PM
**
** Made by Léo Lacordaire
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <sstream>
#include <iomanip>
#include "../../include/IDisplay.hpp"

class Sfml : public IDisplay
{
    private:
        sf::RenderWindow _window;
        sf::Text _text;
        sf::Font _font;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Event _event;
        int _width;
        int _height;

    public:
        Sfml();
        ~Sfml();

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