#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildMenu {

            using Map::Units::UnitType;

            // FUNCTION: STRONGHOLDCRUSADER 0x00446920
            void MenuItemActionHandler_BuildMenu_UnitActionButtons(int button, ...)
            {
                if (DAT_GameSynchronyState::instance.syncStatus != 0) {
                    return;
                }
                if (DAT_GameSynchronyState::instance.saveRelated != 0) {
                    return;
                }
                // The player in a local: it keeps the player's data offset in a register for button 22.
                int const player = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                if (DAT_GameState::instance.playerDataArray[player].lordKilledByPlayerID != 0) {
                    return;
                }
                if (DAT_GameState::instance.playerDataArray[player].playerDeathRelated != 0) {
                    if (DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY) {
                        return;
                    }
                    if (DAT_GameState::instance.mapAndTime.gameOver != player) {
                        return;
                    }
                }
                MACRO_CALL(Helpers_Func::SetTribesPatrolButtonPressed)(FALSE);
                // Most buttons set a unit control mode and the cursor image for it; 3 and 8 also queue a command for
                // the selected units, 30 and 31 only queue one.
                switch (button) {
                case 1:
                    DAT_UnitsState::instance.pendingUnitControlMode = 1;
                    DAT_UnitsState::instance.unitControlsRelated = 1;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                    return;
                case 3:
                    DAT_UnitsState::instance.unitControlsRelated = 1;
                    DAT_UnitsState::instance.pendingUnitControlMode = 1;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 3);
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                    return;
                case 4:
                    DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                    DAT_UnitsState::instance.pendingUnitControlMode = 4;
                    DAT_UnitsState::instance.unitControlsRelated = 4;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                    DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                    return;
                case 20:
                    // Only with an engineer selected.
                    if (MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::returnFirstSelectedEngineer, DAT_UnitsState::ptr)()) {
                        DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                        DAT_UnitsState::instance.pendingUnitControlMode = 20;
                        DAT_UnitsState::instance.unitControlsRelated = 20;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                        DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                        return;
                    }
                    DAT_StopHandlingMenuItems::instance = 0;
                    return;
                case 5: {
                    // An engineer carrying a resource takes mode 20, as button 20 does; tunnelers dig a tunnel.
                    if (MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getSelectedEngineerCarryingResource, DAT_UnitsState::ptr)()) {
                        DAT_TileMapState::instance.uiSelectedUnitIDUnk = 0;
                        DAT_UnitsState::instance.pendingUnitControlMode = 20;
                        DAT_UnitsState::instance.unitControlsRelated = 20;
                        DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                        DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                        return;
                    }
                    if (MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::selectionContainsTunnelersOnly, DAT_UnitsState::ptr)()) {
                        MACRO_CALL(General_Func::MenuItemActionHandler_General_ToolbarButtonPressed)(
                            Commands::M_MAPPER_TUNNEL_CONSTRUCTION);
                        return;
                    }
                    UnitType const unitType = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                    int const engineID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getFirstSelectedCatapultOrTrebuchetID, DAT_UnitsState::ptr)();
                    if ((unitType == Map::Units::UT_S_CATAPULT || unitType == Map::Units::UT_S_TREBUCHET)
                        && DAT_UnitsState::instance.units[engineID]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            == 0) {
                        return;
                    }
                    DAT_UnitsState::instance.pendingUnitControlMode = 5;
                    DAT_UnitsState::instance.unitControlsRelated = 5;
                    DAT_TileMapState::instance.field_0x554a08 = 15;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                    DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                    return;
                }
                case 22: {
                    // Throw a cow: needs a cow and a manned catapult or trebuchet.
                    if (DAT_GameState::instance.playerDataArray[player].availableCows <= 0) {
                        return;
                    }
                    UnitType const unitType = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)();
                    int const engineID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getFirstSelectedCatapultOrTrebuchetID, DAT_UnitsState::ptr)();
                    if ((unitType != Map::Units::UT_S_CATAPULT && unitType != Map::Units::UT_S_TREBUCHET)
                        || DAT_UnitsState::instance.units[engineID]
                                .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                            == 0) {
                        return;
                    }
                    DAT_UnitsState::instance.pendingUnitControlMode = 22;
                    DAT_UnitsState::instance.unitControlsRelated = 22;
                    DAT_TileMapState::instance.field_0x554a08 = 15;
                    DAT_TileMapState::instance.cursorOverlayImageBase = 32;
                    DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                    return;
                }
                case 8:
                    DAT_UnitsState::instance.pendingUnitControlMode = 8;
                    DAT_UnitsState::instance.unitControlsRelated = 8;
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 8);
                    DAT_TileMapState::instance.cursorOverlayImageBase = 0;
                    DAT_TileMapState::instance.cursorOverlayGmID = DE::SHCDE::GM_CURSORS;
                    return;
                case 30:
                    // Patrol, only when the first selected unit is the player's (UT_INVALID means another player's).
                    if (MACRO_CALL_MEMBER(
                            Map::Units::UnitsState_Func::getUnitTypeOfFirstSelectedUnit, DAT_UnitsState::ptr)()
                        != Map::Units::UT_INVALID) {
                        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                            DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 30);
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::playPatrolCommandSpeech, DAT_TribesState::ptr)(
                            DAT_TribesState::instance.DAT_CurrentTribeID);
                        return;
                    }
                    DAT_StopHandlingMenuItems::instance = 0;
                    return;
                case 31:
                    MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::queueDisbandAndAttackCommand2Params,
                        DAT_UnitsState::ptr)(DAT_TribesState::instance.DAT_CurrentTribeID, 31);
                    return;
                }
            }

        }
    }
}
}
