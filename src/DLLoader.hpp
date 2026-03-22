/* ------------------------------------------------------------------------------------ *
 *                                                                                      *
 * EPITECH PROJECT - Tue, Mar, 2026                                                     *
 * Title           - bs-arcarde                                                         *
 * Description     -                                                                    *
 *     DLLoader                                                                         *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ *
 *                                                                                      *
 *             ███████╗██████╗ ██╗████████╗███████╗ ██████╗██╗  ██╗                     *
 *             ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝██╔════╝██║  ██║                     *
 *             █████╗  ██████╔╝██║   ██║   █████╗  ██║     ███████║                     *
 *             ██╔══╝  ██╔═══╝ ██║   ██║   ██╔══╝  ██║     ██╔══██║                     *
 *             ███████╗██║     ██║   ██║   ███████╗╚██████╗██║  ██║                     *
 *             ╚══════╝╚═╝     ╚═╝   ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝                     *
 *                                                                                      *
 * ------------------------------------------------------------------------------------ */

#pragma once

#include <dlfcn.h>
#include "../include/IDisplay.hpp"

template <typename T>
class DLLoader {
    private:
        void *handle;

    public:
        DLLoader(const char *path)
        {
            handle = dlopen(path, RTLD_LAZY);
            if (!handle)
                handle = NULL;
        }

        ~DLLoader()
        {
            if (handle != NULL)
                dlclose(handle);
        }

        T *getInstance()
        {
            IDisplay *(*entryPointFunc)() = reinterpret_cast<IDisplay *(*)()>(dlsym(handle, "myEntryPoint"));
            if (dlerror() != NULL)
                return NULL;
            return entryPointFunc();
        }

};
