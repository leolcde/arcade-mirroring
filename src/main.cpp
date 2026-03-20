/*
** EPITECH PROJECT, 2026
** bs-arcarde
** File description:
** main
*/

#include "DLLoader.hpp"

const char *libs_list[] = {"lib/lib1/lib1.so", "lib/lib2/lib2.so", "lib/lib3/lib3.so"};

int main()
{
    int nb_libs = sizeof(libs_list) / sizeof(libs_list[0]);
    for (int i = 0; i < nb_libs; i++) {
        DLLoader<IDisplay> loader(libs_list[i]);
        IDisplay *actual_lib = loader.getInstance();

        if (actual_lib != NULL) {
            actual_lib->init();
            actual_lib->stop();
            delete actual_lib;
        }
    }

    return 0;
}
