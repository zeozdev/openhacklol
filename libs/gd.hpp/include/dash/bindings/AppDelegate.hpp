#pragma once

#include "../internal.hpp"
#include "cocos/CCApplication.hpp"

namespace gd {
    class AppDelegate : cocos2d::CCApplication {
    public:
        inline static AppDelegate *get() {
            return static_cast<AppDelegate *>(cocos2d::CCApplication::sharedApplication());
        }

        inline void applicationWillEnterForeground() {
            SETUP_METHOD(void, "AppDelegate::applicationWillEnterForeground", __thiscall, AppDelegate*);
            return method(this);
        }

        inline void trySaveGame(bool unk) {
            SETUP_METHOD(void, "AppDelegate::trySaveGame", __thiscall, AppDelegate*, bool);
            return method(this, unk);
        }
    };
}