/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#pragma once

#include <dlfcn.h>
#include "../include/IDisplay.hpp"
#include "../include/IGame.hpp"

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
            T *(*entryPointFunc)() = reinterpret_cast<T *(*)()>(dlsym(handle, "myEntryPoint"));
            if (dlerror() != NULL)
                return NULL;
            return entryPointFunc();
        }

};
