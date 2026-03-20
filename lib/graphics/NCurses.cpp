/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Sat, Mar, 2026                                                     *
 * Title           - arcade                                                             *
 * Description     -                                                                    *
 *     NCurses                                                                   *
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

#include "NCurses.hpp"

NCurses::NCurses(std::vector<IDisplay*>& modules) : _window(NULL), _cursor(0), _modules(modules) {}

NCurses::~NCurses()
{
    this->NCurses::stop();
}

void NCurses::init() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    start_color();
    mousemask(BUTTON1_CLICKED, NULL);

    printf("\033[?1000h\n");

    // Couleurs des thèmes
    init_pair(1, 220, 18); // Main theme
    init_pair(2, 220, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_GREEN, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
    init_pair(9, 214, COLOR_BLACK);

    getmaxyx(stdscr, _height, _width);
    _window = stdscr;
}

void NCurses::stop() {
    if (!isendwin()) endwin();
}

void NCurses::render() {
    erase();
    for (size_t i = 0; i < _modules.size(); ++i) {
        IDisplay* m = _modules[i];
    }
    refresh();
}

RenderType NCurses::getInput() {
    int ch = getch();
    if (ch == 'q' || ch == 'Q') return RenderType::EXIT;
    if (ch == 'n' || ch == 'N') return RenderType::NCURSES;
    return RenderType::NCURSES;
}

std::string NCurses::getName()
{
    return "NcursesLib";
}

extern "C" IDisplay *myEntryPoint()
{
    std::vector<IDisplay*> modules;
    return new NCurses(modules);
}
