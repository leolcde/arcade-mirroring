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

const char *libs_list[] = {"lib/graphics/NCurses.so"};

int main()
{
    bool paused = false;

    int nb_libs = sizeof(libs_list) / sizeof(libs_list[0]);
    for (int i = 0; i < nb_libs; i++) {
        DLLoader<IDisplay> loader(libs_list[i]);
        IDisplay *actual_lib = loader.getInstance();
        if (actual_lib != NULL) {
            actual_lib->init();

            while (true) {
                actual_lib->clear();
                Input input = actual_lib->getInput();
                if (input == Input::EXIT) break;
                if (paused == false)
                    display_start_menu(actual_lib);
                actual_lib->display();
                std::this_thread::sleep_for(std::chrono::milliseconds(30));
            }

            actual_lib->stop();
            delete actual_lib;
        }
    }
    return 0;
}
