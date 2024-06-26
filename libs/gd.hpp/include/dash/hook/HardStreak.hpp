#pragma once

#include "hook.hpp"
#include "../bindings/HardStreak.hpp"

namespace gd::hook::HardStreak {

    // HardStreak::updateStroke

    inline static uintptr_t updateStroke_addr = 0x0;
    inline static std::function<void(gd::HardStreak*, float)> updateStroke_hook;

    /// @brief Calls the original HardStreak::updateStroke function.
    inline static void updateStroke(gd::HardStreak* self, float dt) {
        return reinterpret_cast<void (__thiscall *)(gd::HardStreak*, float)>(updateStroke_addr)(self, dt);
    }

    /// @brief Wrapper for the HardStreak::updateStroke hook.
    inline void __fastcall updateStrokeHook(gd::HardStreak* self, int, float dt) { updateStroke_hook(self, dt); }

    /// @brief Installs the hook for HardStreak::updateStroke.
    SETUP_HOOK("HardStreak::updateStroke", void, updateStroke, gd::HardStreak*, float)

}