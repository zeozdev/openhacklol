#pragma once

#include <cstdint>
#include <string>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#elif ANDROID
#include <dlfcn.h>
#endif

namespace gd::utils {
    /// @brief Find the address of a symbol in a module.
    /// @param module The name of the module.
    /// @param symbol The name of the symbol.
    /// @return The address of the symbol or nullptr if it was not found.
    inline uintptr_t findSymbol(const char *symbol, const char *module) {
#ifdef WIN32
        auto moduleHandle = GetModuleHandleA(module);
        if (!moduleHandle) {
            return 0;
        }

        auto symbolAddress = reinterpret_cast<uintptr_t>(GetProcAddress(moduleHandle, symbol));
        if (!symbolAddress) {
            return 0;
        }

        return symbolAddress;
#elif ANDROID
        auto moduleHandle = dlopen(module, RTLD_NOW);
        if (!moduleHandle) {
            return 0;
        }

        auto symbolAddress = reinterpret_cast<uintptr_t>(dlsym(moduleHandle, symbol));
        dlclose(moduleHandle);

        return symbolAddress;
#endif
    }

    inline uintptr_t getByOffset(uintptr_t offset, const char *module) {
#ifdef WIN32
        auto moduleHandle = GetModuleHandleA(module);
        if (!moduleHandle) {
            return 0;
        }

        return reinterpret_cast<uintptr_t>(moduleHandle) + offset;
#elif ANDROID
        auto moduleHandle = dlopen(module, RTLD_NOW);
        if (!moduleHandle) {
            return 0;
        }

        auto symbolAddress = reinterpret_cast<uintptr_t>(dlsym(moduleHandle, "offset"));
        dlclose(moduleHandle);

        return symbolAddress;
#endif
    }
}