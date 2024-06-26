#pragma once

#include "../internal.hpp"

#include "GameManager.hpp"
#include "GJGameState.hpp"
#include "GJBaseGameLayer.hpp"

namespace gd {
    class GJGameLevel;

    class LevelEditorLayer : public GJBaseGameLayer {
    public:
        inline static LevelEditorLayer *get() {
            return GameManager::sharedState()->m_levelEditorLayer();
        }

        inline void updateVisibility(float dt) {
            SETUP_METHOD(void, "LevelEditorLayer::updateVisibility", __thiscall, LevelEditorLayer *, float);
            method(this, dt);
        }

        inline void onStopPlaytest() {
            SETUP_METHOD(void, "LevelEditorLayer::onStopPlaytest", __thiscall, LevelEditorLayer *);
            method(this);
        }
    };
}