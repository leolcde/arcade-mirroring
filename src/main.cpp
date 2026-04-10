/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

static bool gameInProgress = false;
static DLLoader<IDisplay> *lib_loader = nullptr;
static DLLoader<IGame> *game_loader = nullptr;
static std::map<std::string, DLLoader<IGame> *> game_loaders_list;
static IDisplay *actual_lib;
static IGame *actual_game;

void launch_game(std::string game_name)
{
    if (game_loader != nullptr) {
        game_loader->destroyInstance(actual_game);
        delete game_loader;
    }
    game_loader = new DLLoader<IGame>(game_name.c_str());
    actual_game = game_loader->getInstance();
    if (actual_game != NULL) {
        actual_game->init();
        gameInProgress = true;
    } else {
        delete game_loader;
        game_loader = nullptr;
    }
}

void launch_lib(std::string lib_name)
{
    if (lib_loader != nullptr) {
        lib_loader->destroyInstance(actual_lib);
        delete lib_loader;
    }
    lib_loader = new DLLoader<IDisplay>(lib_name.c_str());
    actual_lib = lib_loader->getInstance();
    if (actual_lib != NULL) {
        actual_lib->init();
    } else {
        delete lib_loader;
        lib_loader = nullptr;
    }
}

void hotswap_game(std::string hotswap_result)
{
     // Find the previous game path from games_states to save the loader
    for (auto const &[key, val] : games_states)
        if (val == actual_game) { game_loaders_list[key] = game_loader; break; }
    if (games_states.find(hotswap_result) != games_states.end() && game_loaders_list.find(hotswap_result) != game_loaders_list.end()) {
        actual_game = games_states.find(hotswap_result)->second;
        game_loader = game_loaders_list.find(hotswap_result)->second;
    } else {
        game_loader = new DLLoader<IGame>(hotswap_result.c_str());
        actual_game = game_loader->getInstance();
        if (actual_game != NULL) actual_game->init();
    }
}

void save_score()
{
    int game_score = actual_game->getScore();
    if (actual_game->isGameOver()) {
        if (game_score > 5) {
            std::ofstream file("data/scores", std::ios::app);
            file << actual_game_name << " " << actual_username << " " << game_score << "\n";
        }
        game_loader->destroyInstance(actual_game);
        delete game_loader;
        game_loader = nullptr;
        gameInProgress = false;
    }
}


int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./arcade [lib_path.so]" << std::endl;
        return 84;
    }

    try {
        lib_loader = new DLLoader<IDisplay>(av[1]);
        actual_lib = lib_loader->getInstance();
        if (actual_lib == NULL)
            throw std::runtime_error("Invalid library");
        actual_lib->init();

        while (true) {
            actual_lib->clear();
            Input input = actual_lib->getInput();
            if (input == Input::EXIT) break;

            // Afficher le menu tant qu'un jeu n'est pas lancé sinon lancer le jeu
            if (gameInProgress == false) {
                std::string display_result = display_menu(actual_lib, input);
                if (last_menu_selection == "game" && display_result != "" && display_result != "None")
                    launch_game(display_result);
                if (last_menu_selection == "graphic" && display_result != "" && display_result != "None")
                    launch_lib(display_result);
            }

            // Afficher le jeu tant que pas de GameOver sinon remettre le menu
            if (gameInProgress == true) {
                std::string hotswap_result = run_game(input, actual_game, actual_lib);
                // Hotswap game and graphics
                if (hotswap_result != "None" && last_menu_selection == "game") hotswap_game(hotswap_result);
                if (hotswap_result != "None" && last_menu_selection == "graphic") launch_lib(hotswap_result);
                // Save score after game over
                save_score();
            }
            actual_lib->display();
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }
        lib_loader->destroyInstance(actual_lib);
    } catch (const std::exception &e) {
        std::cerr << "[ERROR]: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
