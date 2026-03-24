/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "NCurses.hpp"

NCurses::NCurses() : _window(NULL), _cursor(0)
{
    NCurses::init();
}

NCurses::~NCurses()
{
    NCurses::stop();
}

void NCurses::init()
{
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
    init_pair(10, COLOR_RED, COLOR_BLACK);
    init_pair(11, COLOR_CYAN, COLOR_BLACK);

    getmaxyx(stdscr, _height, _width);
    _window = stdscr;
}

void NCurses::stop()
{
    if (!isendwin()) endwin();
}

std::string NCurses::getName()
{
    return "NcursesLib";
}


// Display methods
void NCurses::clear()
{
    erase();
}

void NCurses::display()
{
    refresh();
}

int getColorPair(Color color)
{
    switch (color) {
        case Color::RED:     return 10;
        case Color::GREEN:   return 7;
        case Color::YELLOW:  return 8;
        case Color::BLUE:    return 3;
        case Color::MAGENTA: return 5;
        case Color::CYAN:    return 11;
        case Color::WHITE:   return 6;
        case Color::BLACK:   return 2;
        default:             return 6;
    }
}

void NCurses::drawEntity(const Entity &entity)
{
    int pair = getColorPair(entity.color);
    attron(COLOR_PAIR(pair));
    mvaddch((int)entity.y, (int)entity.x, entity.ncursesChar);
    attroff(COLOR_PAIR(pair));
}

void NCurses::drawText(const Text &text)
{
    int pair = getColorPair(text.color);
    attron(COLOR_PAIR(pair));
    mvprintw((int)text.y, (int)text.x, "%s", text.text.c_str());
    attroff(COLOR_PAIR(pair));
}

Input NCurses::getInput()
{
    int ch = getch();
    if (ch == KEY_UP) return Input::UP;
    if (ch == KEY_DOWN) return Input::DOWN;
    if (ch == KEY_LEFT) return Input::LEFT;
    if (ch == KEY_RIGHT) return Input::RIGHT;
    if (ch == KEY_ENTER || ch == '\n' || ch == '\r') return Input::ACTION;
    if (ch == '1') return Input::PREV_LIB;
    if (ch == '2') return Input::NEXT_LIB;
    if (ch == '3') return Input::PREV_GAME;
    if (ch == '4') return Input::NEXT_GAME;
    if (ch == 'r' || ch == 'R') return Input::RESTART;
    if (ch == 'm' || ch == 'M') return Input::MENU;
    if (ch == 'q' || ch == 'Q') return Input::EXIT;
    return Input::NONE;
}


// Others
extern "C" IDisplay *myEntryPoint()
{
    return new NCurses();
}
