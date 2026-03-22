/*
** EPITECH PROJECT, 2026
** bs-arcarde
** File description:
** main
*/

#include "DLLoader.hpp"
#include "start_menu.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <thread>

int main(int ac, char **av)
{
    bool paused = false;

    if (ac != 2) {
        std::cerr << "Usage: ./arcade [lib_path.so]" << std::endl;
        return 84;
    }

    DLLoader<IDisplay> loader(av[1]);
    IDisplay *actual_lib = loader.getInstance();
    if (actual_lib == NULL) {
        std::cerr << "Error: invalid library" << std::endl;
        return 84;
    }

    actual_lib->init();
    while (true) {
        actual_lib->clear();
        Input input = actual_lib->getInput();
        if (input == Input::EXIT) break;
        if (paused == false)
            display_start_menu(actual_lib, input);
        actual_lib->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    actual_lib->stop();
    delete actual_lib;
    return 0;
}
