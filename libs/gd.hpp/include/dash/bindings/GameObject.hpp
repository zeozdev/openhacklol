#pragma once

#include "../internal.hpp"
#include "cocos/CCGeometry.hpp"
#include "cocos/CCNode.hpp"

namespace gd {
    enum class GameObjectType {
        Solid = 0,
        Hazard = 2,
        InverseGravityPortal = 3,
        NormalGravityPortal = 4,
        ShipPortal = 5,
        CubePortal = 6,
        Decoration = 7,
        YellowJumpPad = 8,
        PinkJumpPad = 9,
        GravityPad = 10,
        YellowJumpRing = 11,
        PinkJumpRing = 12,
        GravityRing = 13,
        InverseMirrorPortal = 14,
        NormalMirrorPortal = 15,
        BallPortal = 16,
        RegularSizePortal = 17,
        MiniSizePortal = 18,
        UfoPortal = 19,
        Modifier = 20,
        Breakable = 21,
        SecretCoin = 22,
        DualPortal = 23,
        SoloPortal = 24,
        Slope = 25,
        WavePortal = 26,
        RobotPortal = 27,
        TeleportPortal = 28,
        GreenRing = 29,
        Collectible = 30,
        UserCoin = 31,
        DropRing = 32,
        SpiderPortal = 33,
        RedJumpPad = 34,
        RedJumpRing = 35,
        CustomRing = 36,
        DashRing = 37,
        GravityDashRing = 38,
        CollisionObject = 39,
        Special = 40,
        SwingPortal = 41,
        GravityTogglePortal = 42,
        SpiderOrb = 43,
        SpiderPad = 44,
        TeleportOrb = 46,
        AnimatedHazard = 47,
    };

    class GameObject : public cocos2d::CCNode {
    public:
        inline cocos2d::CCRect* getObjectRect() {
            SETUP_METHOD(cocos2d::CCRect*, "GameObject::getObjectRect", __thiscall, GameObject*);
            return method(this);
        }

        inline void determineSlopeDirection() {
            SETUP_METHOD(void, "GameObject::determineSlopeDirection", __thiscall, GameObject*);
            return method(this);
        }

        SETUP_MEMBER(uint32_t, m_objectID, "GameObject::m_objectID")
        SETUP_MEMBER(cocos2d::CCPoint, m_startPosition, "GameObject::m_startPosition")
        SETUP_MEMBER(GameObjectType, m_objectType, "GameObject::m_objectType")
    };
}