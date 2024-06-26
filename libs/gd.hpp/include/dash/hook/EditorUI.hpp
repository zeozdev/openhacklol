#pragma once

#include "hook.hpp"
#include "../bindings/EditorUI.hpp"

namespace gd::hook::EditorUI {

    // EditorUI::onPlaytest

    inline static uintptr_t onPlaytest_addr = 0x0;
    inline static std::function<void(gd::EditorUI*, cocos2d::CCObject*)> onPlaytest_hook;

    /// @brief Calls the original EditorUI::onPlaytest function.
    inline static void onPlaytest(gd::EditorUI* self, cocos2d::CCObject* sender) {
        return reinterpret_cast<void (__thiscall *)(gd::EditorUI*, cocos2d::CCObject*)>(onPlaytest_addr)(self, sender);
    }

    /// @brief Wrapper for the EditorUI::onPlaytest hook.
    inline void __fastcall onPlaytestHook(gd::EditorUI* self, int, cocos2d::CCObject* sender) { onPlaytest_hook(self, sender); }

    /// @brief Installs the hook for EditorUI::onPlaytest.
    SETUP_HOOK("EditorUI::onPlaytest", void, onPlaytest, gd::EditorUI*, cocos2d::CCObject*)

}