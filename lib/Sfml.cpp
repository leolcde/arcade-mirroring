/*
** Project  : arcade
** File     : Sfml.cpp
** Path     : lib/games
** Date     : 3/26/26  3:09PM
** 
** Made by Léo Lacordaire
*/

#include "Sfml.hpp"

Sfml::Sfml() : _width(1500), _height(1000)
{
    Sfml::init();
}

Sfml::~Sfml()
{
    Sfml::stop();
}

void Sfml::init()
{
    _window.create(sf::VideoMode(_width, _height), "Arcade");
    if (!_texture.loadFromFile("assets/square.png"))
        throw std::runtime_error("[ERROR]: Could not load texture");
    if (!_font.loadFromFile("assets/Bungee-Regular.ttf"))
        throw std::runtime_error("[ERROR]: Font not found");
}

void Sfml::stop()
{
    _window.close();
}

std::string Sfml::getName()
{
    return "SfmlLib";
}

void Sfml::clear()
{
    _window.clear(sf::Color::Black);
}

void Sfml::display()
{
    _window.display();
}

sf::Color getColorPair(Color color)
{
    switch (color) {
    case Color::RED:     return sf::Color::Red;
    case Color::GREEN:   return sf::Color::Green;
    case Color::YELLOW:  return sf::Color::Yellow;
    case Color::BLUE:    return sf::Color::Blue;
    case Color::MAGENTA: return sf::Color::Magenta;
    case Color::CYAN:    return sf::Color::Cyan;
    case Color::WHITE:   return sf::Color::White;
    case Color::BLACK:   return sf::Color::Black;
    default:             return sf::Color::White;
    }
}

void Sfml::drawEntity(const Entity& entity)
{
    _sprite.setTexture(_texture);
    _sprite.setPosition(entity.x, entity.y);
    _window.draw(_sprite);
}

void Sfml::drawText(const Text& text)
{
    sf::Color c = getColorPair(text.color);
    _text.setFont(_font);
    _text.setString(text.text);
    _text.setFillColor(c);
    _text.setPosition(text.x, text.y);
    _window.draw(_text);
}

Input Sfml::getInput()
{
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            return Input::EXIT;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        return Input::UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        return Input::DOWN;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        return Input::LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        return Input::RIGHT;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        return Input::PREV_LIB;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        return Input::NEXT_LIB;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        return Input::PREV_GAME;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
        return Input::NEXT_GAME;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return Input::RESTART;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
        return Input::MENU;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        return Input::EXIT;

    return Input::NONE;
}

extern "C" IDisplay *myEntryPoint()
{
    return new Sfml();
}
