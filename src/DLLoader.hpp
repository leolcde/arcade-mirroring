/*
** Project  -  arcade
** Date     -  March 20th 2026
**
** Copyright (c) 2026 Jules Nourdin
*/

#pragma once

#include <dlfcn.h>
#include <iostream>
#include <stdexcept>
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
            if (!handle) {
                char *dlopen_error = dlerror();
                throw std::runtime_error(std::string("[DLLoader ERROR]: ") + (dlopen_error ? dlopen_error : "Failed to dlopen"));
            }
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

            dlerror();
            T *(*createEntryPointFunc)() = reinterpret_cast<T *(*)()>(dlsym(handle, "createEntryPoint"));
            char *dlsym_error = dlerror();
            if (dlsym_error) throw std::runtime_error(std::string("[DLLoader ERROR]: ") + dlsym_error);
            return createEntryPointFunc();
        }

        void destroyInstance(T *actual_lib)
        {
            if (handle == NULL)
                return;

            dlerror();
            void (*destroyEntryPointFunc)(T *) = reinterpret_cast<void (*)(T *)>(dlsym(handle, "destroyEntryPoint"));
            char *dlsym_error = dlerror();
            if (dlsym_error) throw std::runtime_error(std::string("[DLLoader ERROR]: ") + dlsym_error);
            destroyEntryPointFunc(actual_lib);
        }

};
