/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Fri, Mar, 2026                                                     *
 * Title           - bs-arcade                                                          *
 * Description     -                                                                    *
 *     IDisplay                                                                         *
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

class IDisplay {
    public:
        virtual ~IDisplay() = default;

        virtual void init() = 0;
        virtual void stop() = 0;
        virtual std::string getName() = 0;

        // Display methods
        virtual void clear() = 0;
        virtual void display() = 0;
        virtual void drawEntity(const Entity &entity) = 0;
        virtual void drawText(const Text &text) = 0;
        virtual Input getInput() = 0;
};
