/*
** Project  -  arcade
** Date     -  March 23rd 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "Snake.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dist_snake(5, 10);
static std::uniform_int_distribution<> dist_apple(1, 15);

Snake::Snake() {}

Snake::~Snake() { Snake::stop(); }

void Snake::init()
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
    // apple.name = "apple";
    apple.color = Color::RED;
    apple.entChar = '*';
    apple.spritePath = "assets/apple.png";
    apple.x = dist_apple(gen);
    apple.y = dist_apple(gen);
    _gameEntities.push_back(apple);

    // Init small snake
    Entity newSnakePart;
    // newSnakePart.name = "SnakePart";
    newSnakePart.color = Color::GREEN;
    newSnakePart.entChar = '@';
    newSnakePart.spritePath = "assets/snake.png";
    newSnakePart.x = dist_snake(gen);
    newSnakePart.y = dist_snake(gen);
    _gameEntities.push_back(newSnakePart);
    for (int i = 1; i <= 2; i++) {
        newSnakePart.entChar = '0';
        newSnakePart.spritePath = "assets/snake.png";
        newSnakePart.x = _gameEntities[1].x - i;
        newSnakePart.y = _gameEntities[1].y;
        _gameEntities.push_back(newSnakePart);
    }

    // Verify apple not generate on snake
    while (entityOnSnake(_gameEntities[0])) {
        _gameEntities[0].x = dist_apple(gen);
        _gameEntities[0].y = dist_apple(gen);
    }

    // Init wall parts
    Entity newWallPart;
    // newWallPart.name = "WallPart";
    newWallPart.color = Color::WHITE;
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

    // Init score display
    Text newTextPart;
    newTextPart.color = Color::MAGENTA;
    newTextPart.text = "Score : 0";
    newTextPart.x = 12;
    newTextPart.y = 18;
    _texts.push_back(newTextPart);
}

void Snake::stop() {}

std::string Snake::getName() { return "SnakeGame"; }


// Game methods
bool Snake::entityOnSnake(Entity entity)
{
    for (size_t i = 1; i < _gameEntities.size(); ++i) {
        if (_gameEntities[i].x == entity.x && _gameEntities[i].y == entity.y)
            return true;
    }
    return false;
}

void Snake::addSnakePart()
{
    Entity newSnakePart;
    newSnakePart.color = Color::GREEN;
    newSnakePart.entChar = '0';
    newSnakePart.spritePath = "assets/snake.png";
    Entity lastSnakePart = _gameEntities[_gameEntities.size() - 1];
    Entity penultimateSnakePart = _gameEntities[_gameEntities.size() - 2];
    if (lastSnakePart.y < penultimateSnakePart.y) {
        newSnakePart.x = lastSnakePart.x;
        newSnakePart.y = lastSnakePart.y - 1;
    }
    if (lastSnakePart.y > penultimateSnakePart.y) {
        newSnakePart.x = lastSnakePart.x;
        newSnakePart.y = lastSnakePart.y + 1;
    }
    if (lastSnakePart.x < penultimateSnakePart.x) {
        newSnakePart.x = lastSnakePart.x - 1;
        newSnakePart.y = lastSnakePart.y;
    }
    if (lastSnakePart.x > penultimateSnakePart.x) {
        newSnakePart.x = lastSnakePart.x + 1;
        newSnakePart.y = lastSnakePart.y;
    }
    _gameEntities.push_back(newSnakePart);
}

void Snake::update(Input input)
{
    if (input == Input::UP || input == Input::DOWN || input == Input::LEFT || input == Input::RIGHT)
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
        addSnakePart();
        // Generate new apple
        while (entityOnSnake(_gameEntities[0])) {
            _gameEntities[0].x = dist_apple(gen);
            _gameEntities[0].y = dist_apple(gen);
        }
    }

    // Verify if snake hit walls
    if (_gameEntities[1].x == 0 || _gameEntities[1].x == 32 || _gameEntities[1].y == 0 || _gameEntities[1].y == 16)
        _isGameOver = true;
    // Verify if snake eat himself
    for (size_t i = 2; i < _gameEntities.size(); ++i)
        if (_gameEntities[1].x == _gameEntities[i].x && _gameEntities[1].y == _gameEntities[i].y) { _isGameOver = true; }
}

std::vector<Entity> &Snake::getEntities() {
    _renderEntities = _gameEntities;
    _renderEntities.insert(_renderEntities.end(), _wallsEntities.begin(), _wallsEntities.end());
    return _renderEntities;
}

std::vector<Text> &Snake::getTexts() { return _texts; }

int Snake::getScore() { return _score; }

bool Snake::isGameOver() { return _isGameOver; }

// Others
extern "C" IGame *createEntryPoint()
{
    return new Snake();
}

extern "C" void destroyEntryPoint(IGame *game)
{
    delete game;
}