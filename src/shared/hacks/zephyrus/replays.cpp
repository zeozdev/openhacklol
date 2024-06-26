#include "replays.hpp"
#include "../../menu/menu.hpp"

#ifndef OPENHACK_GEODE

#include <cocos2d.h>

#endif

namespace openhack::hacks {

    static zephyrus::Zephyrus s_replayEngine;
    static bool s_levelFinished = false;

    void Zephyrus::onInit() {
        // Set the default value
        config::setIfEmpty("zephyrus.state", 0);
        config::setIfEmpty("zephyrus.fixFrames", true);
        config::setIfEmpty("zephyrus.rotationFix", true);
        // config::setIfEmpty("zephyrus.fixMode", 2);

        // Initialize Zephyrus
        s_replayEngine = zephyrus::Zephyrus();
        s_replayEngine.setGetFrameMethod([]() -> uint32_t {
            auto *playLayer = gd::PlayLayer::get();
            if (playLayer == nullptr) return 0;
            auto frame = static_cast<uint32_t>(playLayer->m_dTime() * 240.0f);
            return frame;
        });

        s_replayEngine.setHandleButtonMethod([](int player, int button, bool pressed) {
            auto *playLayer = gd::PlayLayer::get();
            if (playLayer == nullptr) return;
            playLayer->handleButton(
                    pressed,
                    static_cast<gd::PlayerButton>(button),
                    player == 0 ?
                    playLayer->m_player1() : playLayer->m_player2());
        });

        s_replayEngine.setFixPlayerMethod([](int player, const zephyrus::Macro::FrameFix::PlayerData &data) {
            auto *playLayer = gd::PlayLayer::get();
            if (playLayer == nullptr) return;
            auto *playerObj = player == 0 ?
                              playLayer->m_player1() : playLayer->m_player2();

            if (playerObj == nullptr || s_levelFinished) return;

            // set position
            auto*playerSpr = reinterpret_cast<cocos2d::CCSprite*>(playerObj);
            playerObj->m_position().x = data.x;
            playerObj->m_position().y = data.y;
            playerObj->m_yAccel(data.ySpeed);
            playerSpr->setPosition({data.x, data.y});

            if (config::get<bool>("zephyrus.rotationFix", true)) {
                playerSpr->setRotation(data.rotation);
            }
        });

        s_replayEngine.setRequestMacroFixMethod([]() -> zephyrus::Macro::FrameFix {
            auto *playLayer = gd::PlayLayer::get();
            if (playLayer == nullptr) return zephyrus::Macro::FrameFix(0, {0, 0, 0, 0});

            auto *player1 = playLayer->m_player1();
            auto *player2 = playLayer->m_player2();

            if (player1 == nullptr) return zephyrus::Macro::FrameFix(0, {0, 0, 0, 0});

            zephyrus::Macro::FrameFix::PlayerData player1Data = {
                    player1->m_position().x,
                    player1->m_position().y,
                    player1->m_yAccel(),
                    reinterpret_cast<cocos2d::CCSprite *>(player1)->getRotation()
            };

            if (player2 == nullptr) return {0, player1Data};

            zephyrus::Macro::FrameFix::PlayerData player2Data = {
                    player2->m_position().x,
                    player2->m_position().y,
                    player2->m_yAccel(),
                    reinterpret_cast<cocos2d::CCSprite *>(player2)->getRotation()
            };

            return {0, player1Data, player2Data};
        });

        s_replayEngine.setState(static_cast<zephyrus::BotState>(config::get<int>("zephyrus.state")));
        //s_replayEngine.setFixMode(static_cast<zephyrus::BotFixMode>(config::get<int>("zephyrus.fixMode")));
        s_replayEngine.setFixMode(config::get<bool>("zephyrus.fixFrames") ? zephyrus::BotFixMode::EveryFrame : zephyrus::BotFixMode::None);

        // Create window
        menu::addWindow("Replays (beta)", [&]() {
            gui::width(120);
            if (gui::combo("State", "zephyrus.state", "Disabled\0Playing\0Recording\0\0")) {
                s_replayEngine.setState(static_cast<zephyrus::BotState>(config::get<int>("zephyrus.state")));
            }
            gui::tooltip("Disabled: The bot is disabled\n"
                         "Playing: The bot is playing a macro\n"
                         "Recording: The bot is recording a macro");

//            if (gui::combo("Fix Mode", "zephyrus.fixMode", "None\0Every Action\0Every Frame\0\0")) {
//                s_replayEngine.setFixMode(static_cast<zephyrus::BotFixMode>(config::get<int>("zephyrus.fixMode")));
//            }
            gui::width();

            if (gui::checkbox("Fix Frames", "zephyrus.fixFrames")) {
                s_replayEngine.setFixMode(config::get<bool>("zephyrus.fixFrames") ? zephyrus::BotFixMode::EveryFrame : zephyrus::BotFixMode::None);
            }
            gui::tooltip("Fixes the player's position every frame, resulting in a more accurate replay.");

            gui::checkbox("Rotation Fix", "zephyrus.rotationFix");
            gui::tooltip("Attempts to fix the player's rotation during replays.");

            if (gui::button("Clear")) {
                s_replayEngine.setMacro(zephyrus::Macro());
            }
            gui::tooltip("Clear current macro buffer.");

            if (gui::button("Load", ImVec2(0.5f, 0))) {
                zephyrus::Macro macro;
                auto result = utils::filePickerDialog("Macro files (*.zr, *.gdr)\0*.zr;*.gdr\0\0", "Load Macro");
                if (!result.empty()) {
                    if (zephyrus::readFromFile(result, macro)) {
                        s_replayEngine.setMacro(macro);
                        L_TRACE("Loaded macro with {} frames", macro.getFrames().size());
                    } else {
                        L_TRACE("Failed to load macro");
                    }
                }
            }
            gui::tooltip("Load a macro from a file.\n\nNote: This will overwrite the current macro.");

            ImGui::SameLine(0, 2);

            if (gui::button("Save")) {
                if (s_replayEngine.getMacro().getFrames().empty()) return;
                auto result = utils::fileSaveDialog("Zephyrus Macro (*.zr)\0*.zr\0\0", "Save Macro");
                if (!result.empty()) {
                    if (!utils::endsWith(result.string(), ".zr")) result += ".zr";
                    zephyrus::writeToFile(s_replayEngine.getMacro(), result);
                }
            }
            gui::tooltip("Save the current macro to a file.\nRight click to export as .gdr.");
            if (ImGui::IsItemClicked(1)) {
                auto result = utils::fileSaveDialog("GDReplay (*.gdr)\0*.gdr\0\0", "Export Macro");
                if (!result.empty()) {
                    if (!utils::endsWith(result.string(), ".gdr")) result += ".gdr";
                    zephyrus::writeToFile(s_replayEngine.getMacro(), result);
                }
            }

            ImGui::Text("Macro actions: %d", s_replayEngine.getMacro().getFrames().size());
            ImGui::Text("Frame: %d", s_replayEngine.getFrame());
        });
    }

    void Zephyrus::update() {}

    bool Zephyrus::isCheating() {
        return s_replayEngine.getState() == zephyrus::BotState::Playing
                && !s_replayEngine.getMacro().getFrames().empty();
    }

    void Zephyrus::PlayerObjectPushButton(gd::PlayerObject *player, int buttonIndex) {
        auto *playLayer = gd::PlayLayer::get();
        if (playLayer == nullptr) return;
        s_replayEngine.PlayerObjectPushButton(
                player == playLayer->m_player2() ? 1 : 0,
                buttonIndex);
    }

    void Zephyrus::PlayerObjectReleaseButton(gd::PlayerObject *player, int buttonIndex) {
        auto *playLayer = gd::PlayLayer::get();
        if (playLayer == nullptr) return;
        s_replayEngine.PlayerObjectReleaseButton(
                player == playLayer->m_player2() ? 1 : 0,
                buttonIndex);
    }

    void Zephyrus::GJBaseGameLayerProcessCommands() {
        auto *playLayer = gd::PlayLayer::get();
        if (playLayer == nullptr) return;
        s_replayEngine.GJBaseGameLayerProcessCommands();
    }

    void Zephyrus::PlayLayerResetLevel() {
        auto *playLayer = gd::PlayLayer::get();
        if (playLayer == nullptr) return;
        s_levelFinished = false;
        s_replayEngine.PlayLayerResetLevel();
    }

    void Zephyrus::endAnimation() {
        s_levelFinished = true;
    }

}