/*
** Project  : arcade
** File     : Nibbler.cpp
** Path     : lib/games
** Date     : 3/25/26  3:09PM
**
** Made by Léo Lacordaire
*/

#include "Nibbler.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dist_snake(5, 10);
static std::uniform_int_distribution<> dist_apple(1, 15);

Nibbler::Nibbler() {}

Nibbler::~Nibbler() { Nibbler::stop(); }

void Nibbler::init()
{
    _gameEntities.clear();
    _wallsEntities.clear();
    _renderEntities.clear();
    _texts.clear();
    _score = 0;
    _lastInput = Input::NONE;
    _isGameOver = false;

    // First apple
    Entity apple;
    apple.color = Color::RED;
    apple.entChar = '*';
    apple.spritePath = "assets/apple.png";
    apple.x = dist_apple(gen);
    apple.y = dist_apple(gen);
    _gameEntities.push_back(apple);

    // Init small snake
    Entity newNibblerPart;
    newNibblerPart.color = Color::GREEN;
    newNibblerPart.entChar = '@';
    newNibblerPart.spritePath = "assets/snake.png";
    newNibblerPart.x = dist_snake(gen);
    newNibblerPart.y = dist_snake(gen);
    _gameEntities.push_back(newNibblerPart);
    for (int i = 1; i <= 2; i++) {
        newNibblerPart.entChar = '0';
        newNibblerPart.spritePath = "assets/snake.png";
        newNibblerPart.x = _gameEntities[1].x - i;
        newNibblerPart.y = _gameEntities[1].y;
        _gameEntities.push_back(newNibblerPart);
    }

    // Verify apple not generate on snake
    while (entityOnNibbler(_gameEntities[0])) {
        _gameEntities[0].x = dist_apple(gen);
        _gameEntities[0].y = dist_apple(gen);
    }

    // Init wall parts
    Entity newWallPart;
    newWallPart.color = Color::BLUE;
    newWallPart.entChar = 'X';
    newWallPart.spritePath = "assets/wall.jpg";
    for (int i = 0; i <= 16; i += 16) {
        for (int j = 0; j <= 32; j++) {
            newWallPart.x = j;
            newWallPart.y = i;
            _wallsEntities.push_back(newWallPart);
        }
    }
    for (int i = 0; i <= 32; i += 32) {
        for (int j = 0; j <= 16; j++) {
            newWallPart.x = i;
            newWallPart.y = j;
            _wallsEntities.push_back(newWallPart);
        }
    }

	// init intern walls
    for (int j = 3; j <= 7; j++) { newWallPart.x = j; newWallPart.y = 3; _wallsEntities.push_back(newWallPart); }
    for (int i = 3; i <= 7; i++) { newWallPart.x = 3; newWallPart.y = i; _wallsEntities.push_back(newWallPart); }

    for (int j = 25; j <= 29; j++) { newWallPart.x = j; newWallPart.y = 3; _wallsEntities.push_back(newWallPart); }
    for (int i = 3; i <= 7; i++) { newWallPart.x = 29; newWallPart.y = i; _wallsEntities.push_back(newWallPart); }

    for (int j = 3; j <= 7; j++) { newWallPart.x = j; newWallPart.y = 13; _wallsEntities.push_back(newWallPart); }
    for (int i = 9; i <= 13; i++) { newWallPart.x = 3; newWallPart.y = i; _wallsEntities.push_back(newWallPart); }

    for (int j = 25; j <= 29; j++) { newWallPart.x = j; newWallPart.y = 13; _wallsEntities.push_back(newWallPart); }
    for (int i = 9; i <= 13; i++) { newWallPart.x = 29; newWallPart.y = i; _wallsEntities.push_back(newWallPart); }

    for (int j = 12; j <= 20; j++) { newWallPart.x = j; newWallPart.y = 8;  _wallsEntities.push_back(newWallPart); }
    for (int i = 4;  i <= 12;  i++) { newWallPart.x = 16; newWallPart.y = i; _wallsEntities.push_back(newWallPart); }

	// Verify apple not generate on walls or snake
	while (entityOnWall(_gameEntities[0]) || entityOnNibbler(_gameEntities[0])) {
    	_gameEntities[0].x = dist_apple(gen);
    	_gameEntities[0].y = dist_apple(gen);
	}

    // Init score display
    Text newTextPart;
    newTextPart.color = Color::MAGENTA;
    newTextPart.text = "Score : 0";
    newTextPart.x = 12;
    newTextPart.y = 18;
    _texts.push_back(newTextPart);
}

void Nibbler::stop() {}

std::string Nibbler::getName() { return "NibblerGame"; }

// Game methods
bool Nibbler::entityOnNibbler(Entity entity)
{
    for (size_t i = 1; i < _gameEntities.size(); ++i) {
        if (_gameEntities[i].x == entity.x && _gameEntities[i].y == entity.y)
            return true;
    }
    return false;
}

bool Nibbler::entityOnWall(Entity entity)
{
    for (const Entity &wall : _wallsEntities) {
        if (wall.x == entity.x && wall.y == entity.y)
            return true;
    }
    return false;
}

void Nibbler::addNibblerPart()
{
    Entity newNibblerPart;
    newNibblerPart.color = Color::GREEN;
    newNibblerPart.entChar = '0';
    newNibblerPart.spritePath = "assets/snake.png";
    Entity lastNibblerPart = _gameEntities[_gameEntities.size() - 1];
    Entity penultimateNibblerPart = _gameEntities[_gameEntities.size() - 2];
    if (lastNibblerPart.y < penultimateNibblerPart.y) {
        newNibblerPart.x = lastNibblerPart.x;
        newNibblerPart.y = lastNibblerPart.y - 1;
    }
    if (lastNibblerPart.y > penultimateNibblerPart.y) {
        newNibblerPart.x = lastNibblerPart.x;
        newNibblerPart.y = lastNibblerPart.y + 1;
    }
    if (lastNibblerPart.x < penultimateNibblerPart.x) {
        newNibblerPart.x = lastNibblerPart.x - 1;
        newNibblerPart.y = lastNibblerPart.y;
    }
    if (lastNibblerPart.x > penultimateNibblerPart.x) {
        newNibblerPart.x = lastNibblerPart.x + 1;
        newNibblerPart.y = lastNibblerPart.y;
    }
    _gameEntities.push_back(newNibblerPart);
}

void Nibbler::update(Input input)
{
    // Dont change input if it make nibbler die
    if (input == Input::UP && _lastInput != Input::DOWN)
        _lastInput = input;
    else if (input == Input::DOWN && _lastInput != Input::UP)
        _lastInput = input;
    else if (input == Input::LEFT && _lastInput != Input::RIGHT)
        _lastInput = input;
    else if (input == Input::RIGHT && _lastInput != Input::LEFT)
        _lastInput = input;

    if (_lastInput == Input::NONE || _lastInput == Input::ACTION)
        return;

    // Move snake body
    std::pair<float, float> lastPos = {_gameEntities[1].x, _gameEntities[1].y};
    std::pair<float, float> nextPos;
    if (_lastInput == Input::UP) { _gameEntities[1].y -= 1; }
    if (_lastInput == Input::DOWN) { _gameEntities[1].y += 1; }
    if (_lastInput == Input::RIGHT) { _gameEntities[1].x += 1; }
    if (_lastInput == Input::LEFT) { _gameEntities[1].x -= 1; }
    for (size_t i = 2; i < _gameEntities.size(); i++) {
        nextPos = {_gameEntities[i].x, _gameEntities[i].y};
        _gameEntities[i].x = lastPos.first;
        _gameEntities[i].y = lastPos.second;
        lastPos = nextPos;
    }

    // Verify if snake eat apple
    if (_gameEntities[1].x == _gameEntities[0].x && _gameEntities[1].y == _gameEntities[0].y) {
        _score += 1;
        std::string score_text = "Score : " + std::to_string(_score);
        _texts[0].text = score_text;
        addNibblerPart();
        // Generate new apple
        _gameEntities[0].x = dist_apple(gen);
        _gameEntities[0].y = dist_apple(gen);
        while (entityOnNibbler(_gameEntities[0]) || entityOnWall(_gameEntities[0])) {
            _gameEntities[0].x = dist_apple(gen);
            _gameEntities[0].y = dist_apple(gen);
        }
    }

    // Verify if snake hit walls
    for (const Entity &wall : _wallsEntities) {
    	if (_gameEntities[1].x == wall.x && _gameEntities[1].y == wall.y) {
        	_isGameOver = true;
        	break;
    	}
	}
    // Verify if snake eat himself
    for (size_t i = 2; i < _gameEntities.size(); ++i)
        if (_gameEntities[1].x == _gameEntities[i].x && _gameEntities[1].y == _gameEntities[i].y) { _isGameOver = true; }
}

std::vector<Entity> &Nibbler::getEntities() {
    _renderEntities = _gameEntities;
    _renderEntities.insert(_renderEntities.end(), _wallsEntities.begin(), _wallsEntities.end());
    return _renderEntities;
}

std::vector<Text> &Nibbler::getTexts() { return _texts; }

int Nibbler::getScore() { return _score; }

bool Nibbler::isGameOver() { return _isGameOver; }


// Others
extern "C" IGame *createEntryPoint()
{
    return new Nibbler();
}

extern "C" void destroyEntryPoint(IGame *game)
{
    delete game;
}
