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

#include "Pacman.hpp"

static constexpr int BOX_X0 = 14;
static constexpr int BOX_Y0 = 7;

static const std::array<std::pair<int,int>,4> GSPAWN = {{
    {BOX_X0 + 2, BOX_Y0 + 1},
    {BOX_X0 + 1, BOX_Y0 + 1},
    {BOX_X0 + 2, BOX_Y0 + 2},
    {BOX_X0 + 1, BOX_Y0 + 2}
}};

static const std::array<Color,4> GCOLOR = {
    Color::RED, Color::MAGENTA, Color::CYAN, Color::YELLOW
};

Pacman::Pacman()
{
    Pacman::init();
}

Pacman::~Pacman()
{
    Pacman::stop();
}

void Pacman::init()
{
    _pelletsLeft = 0;
    _score = 0;
    _isGameOver = false;
    _isWin = false;
    _texts.clear();
    _renderEntities.clear();
    
   static const std::vector<std::string> MAP = {
        "#################################", // 0
        "#o.............###.............o#", // 1
        "#.#####.######.###.######.#####.#", // 2
        "#.#####.######.###.######.#####.#", // 3
        "#...............................#", // 4
        "#.#####.###.#########.###.#####.#", // 5
        "#.......###.....#.....###.......#", // 6
        "#######.######..#..######.#######", // 7
        "#.............XXXXX.............#", // 8
        "#.............XGGGX.............#", // 9
        "#.............XGGGX.............#", // 10
        "#######.######.XXXXX.######.#####", // 11
        "#..............@................#", // 12
        "#.#####.######.###.######.#####.#", // 13
        "#.#####.######.###.######.#####.#", // 14
        "#o.............................o#", // 15
        "#################################"  // 16
    };
    _map = MAP;

    for (int y = 0; y < 17; y++) {
        for (int x = 0; x < 33; x++) {

            if (_map[y][x] == '.' || _map[y][x] == 'o')
                _pelletsLeft++;

            if (_map[y][x] == '@') {
                _pac.x = x;
                _pac.y = y;
                _pac.x_sfml = x;
                _pac.y_sfml = y;
                _map[y][x] = ' ';
            }
            if (_map[y][x] == 'G')
                _map[y][x] = ' ';
        }
    }

    _pac.entChar = '@';
    _pac.color = Color::YELLOW;
    _pac.spritePath = "assets/pacman.png";

    _pacDir = Input::LEFT;
    _pacWantedDir = _pacDir;
    
    auto now = Clock::now();
    _startTime = now;
    _lastPacMove = now;
    _lastGhostMove = now;
    _ghostReleaseTime = now + std::chrono::seconds(10);
    _frightEndTime = now;

    for (int i = 0; i < 4; i++) {
        _ghosts[i].x = GSPAWN[i].first;
        _ghosts[i]. y = GSPAWN[i].second;
        _ghosts[i].x_sfml = _ghosts[i].x;
        _ghosts[i].y_sfml = _ghosts[i].y;

        _ghosts[i].entChar = 'G';
        _ghosts[i].color = GCOLOR[i];
        _ghosts[i].spritePath = "assets/ghost.png";

        _ghostDirs[i] = Input::LEFT;
        _ghostState[i] = GhostState::InBox;
        _healEndTime[i] = now;
    }
}

std::string Pacman::getName()
{
    return "PacmanGame";
}
