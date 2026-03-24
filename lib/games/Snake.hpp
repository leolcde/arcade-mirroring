/*
** Project  -  arcade
** Date     -  March 23rd 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#pragma once

#include "../include/IGame.hpp"
#include <random>
#include <tuple>

class Snake : public IGame
{
    private:
        std::vector<Entity> _gameEntities;
        std::vector<Entity> _wallsEntities;
        std::vector<Entity> _renderEntities;
        std::vector<Text> _texts;
        int _score;
        Input _lastInput;
        bool _isGameOver;

    public:
        Snake();
        ~Snake();

        void init() override;
        void stop() override;
        std::string getName() override;

        // Game methods
        void update(Input input) override;
        std::vector<Entity> &getEntities() override;
        std::vector<Text> &getTexts() override;
        int getScore() override;
        bool isGameOver() override;
        bool entityOnSnake(Entity entity);
        void addSnakePart();
};
