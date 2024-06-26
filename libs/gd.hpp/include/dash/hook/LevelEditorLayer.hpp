#pragma once

#include "hook.hpp"
#include "../bindings/LevelEditorLayer.hpp"

namespace gd::hook::LevelEditorLayer {

    // LevelEditorLayer::onStopPlaytest

    inline static uintptr_t onStopPlaytest_addr = 0x0;
    inline static std::function<void(gd::LevelEditorLayer*)> onStopPlaytest_hook;

    /// @brief Calls the original LevelEditorLayer::onStopPlaytest function.
    inline static void onStopPlaytest(gd::LevelEditorLayer* self) {
        return reinterpret_cast<void (__thiscall *)(gd::LevelEditorLayer*)>(onStopPlaytest_addr)(self);
    }

    /// @brief Wrapper for the LevelEditorLayer::onStopPlaytest hook.
    inline void __fastcall onStopPlaytestHook(gd::LevelEditorLayer* self, int) { onStopPlaytest_hook(self); }

    /// @brief Installs the hook for LevelEditorLayer::onStopPlaytest.
    SETUP_HOOK("LevelEditorLayer::onStopPlaytest", void, onStopPlaytest, gd::LevelEditorLayer*)

    // LevelEditorLayer::updateVisibility

    inline static uintptr_t updateVisibility_addr = 0x0;
    inline static std::function<void(gd::LevelEditorLayer*, float)> updateVisibility_hook;

    /// @brief Calls the original LevelEditorLayer::updateVisibility function.
    inline static void updateVisibility(gd::LevelEditorLayer* self, float dt) {
        return reinterpret_cast<void (__thiscall *)(gd::LevelEditorLayer*, float)>(updateVisibility_addr)(self, dt);
    }

    /// @brief Wrapper for the LevelEditorLayer::updateVisibility hook.
    inline void __fastcall updateVisibilityHook(gd::LevelEditorLayer* self, int, float dt) { updateVisibility_hook(self, dt); }

    /// @brief Installs the hook for LevelEditorLayer::updateVisibility.
    SETUP_HOOK("LevelEditorLayer::updateVisibility", void, updateVisibility, gd::LevelEditorLayer*, float)

}