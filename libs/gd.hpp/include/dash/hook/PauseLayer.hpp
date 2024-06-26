#pragma once

#include "hook.hpp"
#include "../bindings/PauseLayer.hpp"

namespace gd::hook::PauseLayer {

    // PauseLayer::customSetup

    inline static uintptr_t customSetup_addr = 0x0;
    inline static std::function<void(gd::PauseLayer*)> customSetup_hook;

    /// @brief Calls the original PauseLayer::customSetup function.
    inline static void customSetup(gd::PauseLayer* self) {
        return reinterpret_cast<void (__thiscall *)(gd::PauseLayer*)>(customSetup_addr)(self);
    }

    /// @brief Wrapper for the PauseLayer::customSetup hook.
    inline void __fastcall customSetupHook(gd::PauseLayer* self, int) { customSetup_hook(self); }

    /// @brief Installs the hook for PauseLayer::customSetup.
    SETUP_HOOK("PauseLayer::customSetup", void, customSetup, gd::PauseLayer*)

}