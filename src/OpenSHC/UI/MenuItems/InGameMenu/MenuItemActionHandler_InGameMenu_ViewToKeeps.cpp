#include "../InGameMenu.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_00b9840c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DWORD_00b98410.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004335A0
        void InGameMenu::MenuItemActionHandler_InGameMenu_ViewToKeeps(int param_1, ...)
        {
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE) {
                return;
            }
            // two wheel steps within a second count as one move: up views the next keep, down the own keep
            DWORD const now = timeGetTime();
            if (now - DWORD_00b98410::instance > 1000) {
                DWORD_00b98410::instance = now;
                DAT_00b9840c::instance = 0;
            }
            if (DAT_MouseState::instance.scrollEventData == 7) {
                if (DAT_00b9840c::instance < 0) {
                    DAT_00b9840c::instance = 0;
                }
                ++DAT_00b9840c::instance;
                if (DAT_00b9840c::instance == 2) {
                    DWORD_00b98410::instance = now;
                    DAT_00b9840c::instance = 0;
                    // the keep after the one viewed last, counting the map's keeps from 1
                    int keepNumber = 1;
                    int tileIndex = -1;
                    for (int i = 0; i < countof(DAT_GameState::instance.mapAndTime.playerKeepTile); ++i) {
                        if (DAT_GameState::instance.mapAndTime.playerKeepTile[i] > -1) {
                            if (keepNumber == DAT_GameCore::instance.viewedKeepIndex) {
                                tileIndex = i;
                            }
                            ++keepNumber;
                        }
                    }
                    if (tileIndex == -1) {
                        int const keep = DAT_GameState::instance
                                             .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                             .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                                             .id;
                        if (keep != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                                DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[keep].x + 2,
                                DAT_BuildingsState::instance.buildings[keep].y + 2);
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnTile,
                            DAT_ViewportRenderState::ptr)(DAT_GameState::instance.mapAndTime.playerKeepTile[tileIndex]);
                    }
                    ++DAT_GameCore::instance.viewedKeepIndex;
                    if (DAT_GameCore::instance.viewedKeepIndex >= keepNumber) {
                        DAT_GameCore::instance.viewedKeepIndex = 0;
                    }
                }
            }
            if (DAT_MouseState::instance.scrollEventData == 8) {
                if (DAT_00b9840c::instance > 0) {
                    DAT_00b9840c::instance = 0;
                }
                --DAT_00b9840c::instance;
                if (DAT_00b9840c::instance == -2) {
                    DWORD_00b98410::instance = now;
                    int const keep
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                              .id;
                    DAT_00b9840c::instance = 0;
                    if (keep != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::focusOnCoordinate,
                            DAT_ViewportRenderState::ptr)(DAT_BuildingsState::instance.buildings[keep].x + 2,
                            DAT_BuildingsState::instance.buildings[keep].y + 2);
                    }
                }
            }
        }

    }
}
}
