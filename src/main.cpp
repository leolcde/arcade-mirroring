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
    IDisplay *actual_lib;
    DLLoader<IGame>* game_loader = nullptr;
    IGame *actual_game;

    if (ac != 2) {
        std::cerr << "Usage: ./arcade [lib_path.so]" << std::endl;
        return 84;
    }

    DLLoader<IDisplay> lib_loader(av[1]);
    actual_lib = lib_loader.getInstance();
    if (actual_lib == NULL) {
        std::cerr << "Error: invalid library" << std::endl;
        return 84;
    }

    while (true) {
        actual_lib->clear();
        Input input = actual_lib->getInput();
        if (input == Input::EXIT) break;
        // Afficher le menu tant qu'un jeu n'est pas lancé sinon lancer le jeu
        if (gameInProgress == false) {
            std::string game_name = display_menu(actual_lib, input);
            if (game_name != "" && game_name != "None") {
                game_loader = new DLLoader<IGame>(game_name.c_str());
                actual_game = game_loader->getInstance();
                if (actual_game != NULL) {
                    gameInProgress = true;
                } else {
                    delete game_loader;
                    game_loader = nullptr;
                }
            }
        }
        // Afficher le jeu tant que pas de GameOver sinon remettre le menu
        if (gameInProgress == true) {
            int game_score = launch_game(input, actual_game, actual_lib);
            if (game_score != -1) {
                std::ofstream file("data/scores", std::ios::app);
                file << actual_game->getName() << " " << actual_username << " " << game_score << "\n";
                delete actual_game;
                delete game_loader;
                gameInProgress = false;
            }
        }
        actual_lib->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    delete actual_lib;
    return 0;
}
