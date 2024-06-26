#include "../pch.hpp"

#include "../../shared/hacks/custom-wave-trail/custom-wave-trail.hpp"

#include <Geode/modify/HardStreak.hpp>

namespace openhack::hooks {
    struct HardStreakHook : geode::Modify<HardStreakHook, HardStreak> {
        void updateStroke(float dt) {
            hacks::CustomWaveTrail::updateStroke(reinterpret_cast<gd::HardStreak *>(this));
            HardStreak::updateStroke(dt);
        }
    };
}