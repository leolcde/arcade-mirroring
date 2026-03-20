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
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include "../include/IDisplay.hpp"

class NCurses : public IDisplay {
    private:
        WINDOW* _window;
        int _width;
        int _height;
        int _cursor;
        std::vector<IDisplay *> _modules;

    public:
        NCurses(std::vector<IDisplay *>& modules);
        ~NCurses();

        void init() override;
        void stop() override;
        void render() override;
        RenderType getInput() override;
        std::string getName();
};
