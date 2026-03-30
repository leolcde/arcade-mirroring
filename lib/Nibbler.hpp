/*
** Project  : arcade
** File     : Nibbler.hpp
** Path     : lib/games
** Date     : 3/25/26  3:09PM
**
** Made by Léo Lacordaire
*/

#pragma once

#include "../include/IGame.hpp"
#include <random>
#include <tuple>

class Nibbler : public IGame
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
        Nibbler();
        ~Nibbler();

        void init() override;
        void stop() override;
        std::string getName() override;

        // Game methods
        void update(Input input) override;
        std::vector<Entity> &getEntities() override;
        std::vector<Text> &getTexts() override;
        int getScore() override;
        bool isGameOver() override;
        bool entityOnNibbler(Entity entity);
        bool entityOnWall(Entity entity);
        void addNibblerPart();
};