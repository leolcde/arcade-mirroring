/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Sat, Mar, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     NCurses                                                                   *
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

#include <ncurses.h>
#include <map>
#include <sstream>
#include <iomanip>
#include "../../include/IDisplay.hpp"

class NCurses : public IDisplay {
    private:
        WINDOW* _window;
        int _width;
        int _height;
        int _cursor;

    public:
        NCurses();
        ~NCurses();

        void init() override;
        void stop() override;
        std::string getName() override;

        // Display methods
        void clear() override;
        void display() override;
        void drawEntity(const Entity &entity) override;
        void drawText(const Text &text) override;
        Input getInput() override;
};
