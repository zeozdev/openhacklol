#pragma once

#include "../internal.hpp"

#include "cocos/CCLayer.hpp"

namespace gd {
    class PauseLayer : public cocos2d::CCLayer {
    public:
        inline void customSetup() {
            SETUP_METHOD(void, "PauseLayer::customSetup", __thiscall, PauseLayer*);
            method(this);
        }
    };
}