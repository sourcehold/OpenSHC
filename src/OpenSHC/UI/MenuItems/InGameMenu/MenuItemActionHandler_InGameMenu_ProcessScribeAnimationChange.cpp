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
        void InGameMenu::MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int unused, ...)
        {
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR
                || DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                return;
            }
            int const slot = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            // while a tax setting is animated: one step every 60 milliseconds
            if (DAT_GameCore::instance.taxesSettingUnk != 0) {
                DWORD const now = timeGetTime();
                if ((int)(now - DAT_GameCore::instance.taxestimeUnk) < 60) {
                    return;
                }
                DAT_GameCore::instance.taxestimeUnk = now;
                // the phase is read from the global at each use: kept in a local, it takes the register the original
                // keeps the zero in
                switch (DAT_GameCore::instance.scribeAnimationPhase) {
                case 0:
                    // to frame 6 first, then phase 1
                    if (DAT_GameCore::instance.scribeAnimationFrame < 6) {
                        ++DAT_GameCore::instance.scribeAnimationFrame;
                    } else if (DAT_GameCore::instance.scribeAnimationFrame > 6) {
                        --DAT_GameCore::instance.scribeAnimationFrame;
                    } else {
                        DAT_GameCore::instance.scribeAnimationPhase = 1;
                    }
                    break;
                case 1:
                    // the next entry of the setting's sequence (below)
                    ++DAT_GameCore::instance.scribeAnimationFrame2;
                    break;
                case 2: {
                    // back to the frame that shows the popularity; there the animation ends
                    int const target = (100 - DAT_GameState::instance.playerDataArray[slot].popularity / 100) / 10 + 1;
                    // a frame of a sequence (12 and up; the popularity's are 1 to 11): to frame 6 first
                    if (DAT_GameCore::instance.scribeAnimationFrame > 11) {
                        DAT_GameCore::instance.scribeAnimationFrame = 6;
                    } else if (DAT_GameCore::instance.scribeAnimationFrame > target) {
                        --DAT_GameCore::instance.scribeAnimationFrame;
                    } else if (DAT_GameCore::instance.scribeAnimationFrame < target) {
                        ++DAT_GameCore::instance.scribeAnimationFrame;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                    break;
                }
                }
            }
            // no setting: the frame that shows the popularity. Settings 1 to 3 in phase 1: the frame from the setting's
            // sequence, which a 0 ends.
            switch (DAT_GameCore::instance.taxesSettingUnk) {
            case 0:
                DAT_GameCore::instance.scribeAnimationFrame
                    = (100 - DAT_GameState::instance.playerDataArray[slot].popularity / 100) / 10 + 1;
                break;
            case 1:
                if (DAT_GameCore::instance.scribeAnimationPhase == 1) {
                    int const entry = DAT_RenderingDefinedData::instance
                                          .ScribeAnimationFrames1[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (entry != 0) {
                        DAT_GameCore::instance.scribeAnimationFrame = entry;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                }
                break;
            case 2:
                if (DAT_GameCore::instance.scribeAnimationPhase == 1) {
                    int const entry = DAT_RenderingDefinedData::instance
                                          .ScribeAnimationFrames2[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (entry != 0) {
                        DAT_GameCore::instance.scribeAnimationFrame = entry;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                }
                break;
            case 3:
                if (DAT_GameCore::instance.scribeAnimationPhase == 1) {
                    int const entry = DAT_RenderingDefinedData::instance
                                          .ScribeAnimationFrames3[DAT_GameCore::instance.scribeAnimationFrame2];
                    if (entry != 0) {
                        DAT_GameCore::instance.scribeAnimationFrame = entry;
                    } else {
                        DAT_GameCore::instance.taxesSettingUnk = 0;
                    }
                }
                break;
            }
            // the frame changed, or the month did
            if (DAT_GameCore::instance.scribeAnimationFrameCopy != DAT_GameCore::instance.scribeAnimationFrame
                || DAT_GameState::instance.mapAndTime.monthChanged != 0) {
                DAT_GameCore::instance.countdown = 1;
                DAT_GameCore::instance.scribeAnimationFrameCopy = DAT_GameCore::instance.scribeAnimationFrame;
            }
        }

    }
}
}
