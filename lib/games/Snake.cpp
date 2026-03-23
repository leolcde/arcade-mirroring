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

Snake::Snake() : _score(0), _lastInput(Input::NONE), _isGameOver(false)
{
    Snake::init();
}

Snake::~Snake()
{
    Snake::stop();
}

void Snake::init()
{
    // First apple
    Entity apple;
    apple.color = Color::RED;
    apple.ncursesChar = '*';
    apple.x = dist_apple(gen);
    apple.y = dist_apple(gen);
    _entities.push_back(apple);

    // Init small snake
    Entity newSnakePart;
    newSnakePart.color = Color::GREEN;
    newSnakePart.ncursesChar = '@';
    newSnakePart.x = dist_snake(gen);
    newSnakePart.y = dist_snake(gen);
    _entities.push_back(newSnakePart);
    for (int i = 1; i <= 2; i++) {
        newSnakePart.ncursesChar = '0';
        newSnakePart.x = _entities[1].x - i;
        newSnakePart.y = _entities[1].y;
        _entities.push_back(newSnakePart);
    }

    // Verify apple not generate on snake
    while (entityOnSnake(_entities[0])) {
        _entities[0].x = dist_apple(gen);
        _entities[0].y = dist_apple(gen);
    }
}

void Snake::stop() {}

std::string Snake::getName()
{
    return "SnakeGame";
}


// Game methods
bool Snake::entityOnSnake(Entity entity)
{
    for (size_t i = 1; i < _entities.size(); ++i) {
        if (_entities[i].x == entity.x && _entities[i].y == entity.y)
            return true;
    }
    return false;
}

void Snake::addSnakePart()
{
    Entity newSnakePart;
    newSnakePart.color = Color::GREEN;
    newSnakePart.ncursesChar = '0';
    Entity lastSnakePart = _entities[_entities.size() - 1];
    Entity penultimateSnakePart = _entities[_entities.size() - 2];
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
    _entities.push_back(newSnakePart);
}

void Snake::updateInput(Input input)
{
    _lastInput = input;
}

void Snake::updateTick()
{
    // Move snake body
    std::pair<float, float> lastPos = {_entities[1].x, _entities[1].y};
    std::pair<float, float> nextPos;
    if (_lastInput == Input::UP) { _entities[1].y -= 1; }
    if (_lastInput == Input::DOWN) { _entities[1].y += 1; }
    if (_lastInput == Input::RIGHT) { _entities[1].x += 1; }
    if (_lastInput == Input::LEFT) { _entities[1].x -= 1; }
    for (int i = 2; i < _entities.size(); i++) {
        nextPos = {_entities[i].x, _entities[i].y};
        _entities[i].x = lastPos.first;
        _entities[i].y = lastPos.second;
        lastPos = nextPos;
    }

    // Verify if snake eat apple
    if (_entities[1].x == _entities[0].x && _entities[1].y == _entities[0].y) {
        _score += 1;
        addSnakePart();
        // Generate new apple
        while (entityOnSnake(_entities[0])) {
            _entities[0].x = dist_apple(gen);
            _entities[0].y = dist_apple(gen);
        }
    }

    // Verify if snake hit walls
    if (_entities[1].x == 0 || _entities[1].x == 16 || _entities[1].y == 0 || _entities[1].y == 16)
        _isGameOver = true;
    // Verify if snake eat himself
    if (entityOnSnake(_entities[1]))
        _isGameOver = true;
}

const std::vector<Entity> &Snake::getEntities() { return _entities; }

const std::vector<Text> &Snake::getTexts() { return _texts; }

int Snake::getScore() { return _score; }

bool Snake::isGameOver() { return _isGameOver; }
