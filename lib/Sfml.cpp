/*
** Project  : arcade
** File     : Sfml.cpp
** Path     : lib/games
** Date     : 3/26/26  3:09PM
**
** Made by Léo Lacordaire
*/

#include "Sfml.hpp"

Sfml::Sfml() : _width(1500), _height(1000) {}

Sfml::~Sfml() { Sfml::stop(); }

void Sfml::init()
{
    _window.create(sf::VideoMode(_width, _height), "Arcade");
    _window.setFramerateLimit(60);
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
    _dt = _clock.restart().asSeconds();
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
    if (!_texture.loadFromFile(entity.spritePath))
    {
        std::cerr << entity.spritePath << std::endl;
        throw std::runtime_error("[ERROR ]: Could not load texture");
    }

    _sprite.setTexture(_texture);

    if (entity.entChar == 'X' || entity.entChar == '@' || entity.entChar == '0' || entity.entChar == '*') {
        sf::Vector2u texSize = _texture.getSize();
        _sprite.setScale(
            55.f / texSize.x,
            85.f / texSize.y
        );
    } else {
        _sprite.setScale(1.f, 1.f);
    }
    _sprite.setPosition(entity.x * 46.f, entity.y * 62.f);
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
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
            case sf::Keyboard::Enter:  return Input::ACTION;
            case sf::Keyboard::Up:     return Input::UP;
            case sf::Keyboard::Down:   return Input::DOWN;
            case sf::Keyboard::Left:   return Input::LEFT;
            case sf::Keyboard::Right:  return Input::RIGHT;
            case sf::Keyboard::Num1:   return Input::PREV_LIB;
            case sf::Keyboard::Num2:   return Input::NEXT_LIB;
            case sf::Keyboard::Num3:   return Input::PREV_GAME;
            case sf::Keyboard::Num4:   return Input::NEXT_GAME;
            case sf::Keyboard::R:      return Input::RESTART;
            case sf::Keyboard::M:      return Input::MENU;
            case sf::Keyboard::Q:      return Input::EXIT;
            default: break;
            }
        }
    }
    return Input::NONE;
}

// Others
extern "C" IDisplay *createEntryPoint()
{
    return new Sfml();
}

extern "C" void destroyEntryPoint(IDisplay *display)
{
    delete display;
}
