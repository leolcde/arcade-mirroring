/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Fri, Apr, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     Pacman                                                                           *
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


#pragma once

#include "../include/IGame.hpp"
#include <iostream>
#include <map>
#include <array>
#include <chrono>
#include <random>

enum class GhostState { 
    InBox, 
    Normal, 
    Frightened, 
    EyesReturning 
};

using Clock = std::chrono::steady_clock;

class Pacman : public IGame
{
    private:
        std::vector<std::string> _map;

        Entity _pac;
        Input _pacDir;
        Input _pacWantedDir;

        std::array<Entity, 4> _ghosts;
        std::array<Input,4> _ghostDirs;
        std::array<GhostState,4> _ghostState;

        Clock::time_point _startTime;
        Clock::time_point _lastPacMove;
        Clock::time_point _lastGhostMove;
        Clock::time_point _frightEndTime;
        Clock::time_point _ghostReleaseTime;
        std::array<Clock::time_point, 4> _healEndTime;

        int _pelletsLeft{0};
        int _score{0};
        bool _isGameOver{false};
        bool _isWin{false};
    
        std::vector<Text> _texts;
        std::vector<Entity> _renderEntities;


    public:
        Pacman();
        ~Pacman();

        void init() override;
        void stop() override;
        std::string getName() override;

        // Game methods
        void update(Input input) override;
        std::vector<Entity> &getEntities() override;
        std::vector<Text> &getTexts() override;
        int getScore() override;
        bool isGameOver() override;
};
