/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Fri, Mar, 2026                                                     *
 * Title           - bs-arcade                                                          *
 * Description     -                                                                    *
 *     IGame                                                                         *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *             ███████╗██████╗ ██╗████████╗███████╗ ██████╗██╗  ██╗                     *
 *             ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝██╔════╝██║  ██║                     *
 *             █████╗  ██████╔╝██║   ██║   █████╗  ██║     ███████║                     *
 *             ██╔══╝  ██╔═══╝ ██║   ██║   ██╔══╝  ██║     ██╔══██║                     *
 *             ███████╗██║     ██║   ██║   ███████╗╚██████╗██║  ██║                     *
 *             ╚══════╝╚═╝     ╚═╝   ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝                     *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#pragma once

#include "Utils.hpp"

class IGame
{
    public:
        virtual ~IGame() = default;

        virtual void init() = 0;
        virtual void stop() = 0;
        virtual std::string getName() = 0;

        virtual void update(Input input) = 0;
        virtual const std::vector<Entity> &getEntities() = 0;
        virtual const std::vector<Text> &getTexts() = 0;
        virtual int getScore() = 0;
        virtual bool isGameOver() = 0;

};
