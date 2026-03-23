/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#pragma once

#include "Utils.hpp"

class IGame
{
    public:
        virtual ~IGame() = default;

        virtual void init() = 0;
        virtual void stop() = 0;
        virtual std::string getName() = 0;

        // Game methods
        virtual void updateInput(Input input) = 0;
        virtual void updateTick() = 0;
        virtual const std::vector<Entity> &getEntities() = 0;
        virtual const std::vector<Text> &getTexts() = 0;
        virtual int getScore() = 0;
        virtual bool isGameOver() = 0;

};
