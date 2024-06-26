#pragma once

#include "hook.hpp"
#include "../bindings/GameObject.hpp"

namespace gd::hook::GameObject {

    // GameObject::determineSlopeDirection

    inline static uintptr_t determineSlopeDirection_addr = 0x0;
    inline static std::function<void(gd::GameObject*)> determineSlopeDirection_hook;

    /// @brief Calls the original GameObject::determineSlopeDirection function.
    inline static void determineSlopeDirection(gd::GameObject* self) {
        reinterpret_cast<void (__thiscall *)(gd::GameObject*)>(determineSlopeDirection_addr)(self);
    }

    /// @brief Wrapper for the GameObject::determineSlopeDirection hook.
    inline void __fastcall determineSlopeDirectionHook(gd::GameObject* self) { determineSlopeDirection_hook(self); }

    /// @brief Installs the hook for GameObject::determineSlopeDirection.
    SETUP_HOOK("GameObject::determineSlopeDirection", void, determineSlopeDirection, gd::GameObject*)

}