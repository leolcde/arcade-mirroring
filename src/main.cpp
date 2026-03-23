/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#include "utils.hpp"

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
