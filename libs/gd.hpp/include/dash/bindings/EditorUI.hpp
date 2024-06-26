#pragma once

#include "../internal.hpp"

namespace gd {
    namespace cocos2d {
        class CCObject;
    }

    class EditorUI {
    public:
        inline void onPlaytest(cocos2d::CCObject* sender) {
            SETUP_METHOD(void, "EditorUI::onPlaytest", __thiscall, EditorUI *, cocos2d::CCObject*);
            method(this, sender);
        }
    };
}