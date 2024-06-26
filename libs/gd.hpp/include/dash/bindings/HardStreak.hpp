#pragma once

#include "../internal.hpp"

#include "cocos/CCDrawNode.hpp"

namespace gd {
    class HardStreak : public cocos2d::CCDrawNode {
    public:
        inline void updateStroke(float dt) {
            SETUP_METHOD(void, "HardStreak::updateStroke", __thiscall, HardStreak *, float);
            method(this, dt);
        }

        SETUP_MEMBER(float, m_pulseSize, "HardStreak::m_pulseSize");
    };
}