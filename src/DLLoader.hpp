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
            if (handle == NULL)
                return NULL;
            T *(*createEntryPointFunc)() = reinterpret_cast<T *(*)()>(dlsym(handle, "createEntryPoint"));
            if (createEntryPointFunc == NULL)
                return NULL;
            return createEntryPointFunc();
        }

        void destroyInstance(T *actual_lib)
        {
            if (handle == NULL)
                return;
            void (*destroyEntryPointFunc)(T *) = reinterpret_cast<void (*)(T *)>(dlsym(handle, "destroyEntryPoint"));
            if (destroyEntryPointFunc == NULL)
                throw std::runtime_error("Failed to destroy entity");
            destroyEntryPointFunc(actual_lib);
        }

};
