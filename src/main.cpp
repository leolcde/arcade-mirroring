/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

int main(int ac, char **av)
{
    bool gameInProgress = false;
    DLLoader<IDisplay> *lib_loader = nullptr;
    DLLoader<IGame> *game_loader = nullptr;
    IDisplay *actual_lib;
    IGame *actual_game;

    if (ac != 2) {
        std::cerr << "Usage: ./arcade [lib_path.so]" << std::endl;
        return 84;
    }

    lib_loader = new DLLoader<IDisplay>(av[1]);
    actual_lib = lib_loader->getInstance();
    if (actual_lib == NULL) {
        std::cerr << "Error: invalid library" << std::endl;
        return 84;
    }
    actual_lib->init();

    while (true) {
        actual_lib->clear();
        Input input = actual_lib->getInput();
        if (input == Input::EXIT) break;
        // Afficher le menu tant qu'un jeu n'est pas lancé sinon lancer le jeu
        if (gameInProgress == false) {
            std::string display_result = display_menu(actual_lib, input);
            // std::ofstream debug_log("debug.log", std::ios::app);
            // debug_log << "Testing condition: " << last_menu_selection << " / " << display_result << std::endl;
            // debug_log.close();
            if (last_menu_selection == "game" && display_result != "" && display_result != "None") {
                if (game_loader != nullptr) {
                    game_loader->destroyInstance(actual_game);
                    delete game_loader;
                }
                game_loader = new DLLoader<IGame>(display_result.c_str());
                actual_game = game_loader->getInstance();
                if (actual_game != NULL) {
                    actual_game->init();
                    gameInProgress = true;
                } else {
                    delete game_loader;
                    game_loader = nullptr;
                }
            }
            if (last_menu_selection == "graphic" && display_result != "" && display_result != "None") {
                lib_loader->destroyInstance(actual_lib);
                delete lib_loader;
                lib_loader = new DLLoader<IDisplay>(display_result.c_str());
                actual_lib = lib_loader->getInstance();
                if (actual_lib != NULL) {
                    actual_lib->init();
                } else {
                    delete lib_loader;
                    lib_loader = nullptr;
                }
            }
        }
        // Afficher le jeu tant que pas de GameOver sinon remettre le menu
        if (gameInProgress == true) {
            int game_score = launch_game(input, actual_game, actual_lib);
            if (game_score != -1 && game_score > 5) {
                std::ofstream file("data/scores", std::ios::app);
                file << actual_game_name << " " << actual_username << " " << game_score << "\n";
                game_loader->destroyInstance(actual_game);
                delete game_loader;
                gameInProgress = false;
            }
        }
        actual_lib->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    lib_loader->destroyInstance(actual_lib);
    return 0;
}
