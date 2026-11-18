#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00433370
        void InGameMenu::MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int button, ...)
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                return;
            }
            int const slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            int phase;
            int frame;
            if (DAT_GameCore::instance.taxesSettingUnk != 0) {
                DWORD const now = timeGetTime();
                if ((int)(now - DAT_GameCore::instance.taxestimeUnk) < 60) {
                    return;
                }
                phase = DAT_GameCore::instance.scribeAnimationPhase;
                DAT_GameCore::instance.taxestimeUnk = now;
                switch (phase) {
                case 2: {
                    int const target = (100 - DAT_GameState::instance.playerDataArray[slot].popularity / 100) / 10 + 1;
                    frame = DAT_GameCore::instance.scribeAnimationFrame;
                    if (frame > 11) {
                        frame = 6;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else if (frame > target) {
                        --frame;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else if (frame < target) {
                        ++frame;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                    break;
                }
                case 1:
                    ++DAT_GameCore::instance.scribeAnimationFrame2;
                    frame = DAT_GameCore::instance.scribeAnimationFrame;
                    break;
                case 0:
                    frame = DAT_GameCore::instance.scribeAnimationFrame;
                    if (frame < 6) {
                        ++frame;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else if (frame > 6) {
                        --frame;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else {
                        phase = 1;
                        DAT_GameCore::instance.scribeAnimationPhase = phase;
                    }
                    break;
                default:
                    frame = DAT_GameCore::instance.scribeAnimationFrame;
                    break;
                }
            } else {
                phase = DAT_GameCore::instance.scribeAnimationPhase;
                frame = DAT_GameCore::instance.scribeAnimationFrame;
            }
            switch (DAT_GameCore::instance.taxesSettingUnk) {
            case 0:
                frame = (100 - DAT_GameState::instance.playerDataArray[slot].popularity / 100) / 10 + 1;
                DAT_GameCore::instance.scribeAnimationFrame = frame;
                break;
            case 1:
                if (phase == 1) {
                    int const next = DAT_RenderingDefinedData::instance
                                         .ScribeAnimationFrames1[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (next != 0) {
                        frame = next;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                }
                break;
            case 2:
                if (phase == 1) {
                    int const next = DAT_RenderingDefinedData::instance
                                         .ScribeAnimationFrames2[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (next != 0) {
                        frame = next;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                }
                break;
            case 3:
                if (phase == 1) {
                    int const next = DAT_RenderingDefinedData::instance
                                         .ScribeAnimationFrames3[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (next != 0) {
                        frame = next;
                        DAT_GameCore::instance.scribeAnimationFrame = frame;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                }
                break;
            }
            if (DAT_GameCore::instance.scribeAnimationFrameCopy != frame
                || DAT_GameState::instance.mapAndTime.monthChanged != 0) {
                DAT_GameCore::instance.countdown = 1;
                DAT_GameCore::instance.scribeAnimationFrameCopy = frame;
            }
        }

    }
}
}
